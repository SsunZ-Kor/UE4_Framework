using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Win32;
using DataLoadLib.Global;
using System.IO;
using System.Data.SqlClient;
using System.Data;
using System.Globalization;

namespace DataTool.Global
{
    class GlobalFunctions
    {
        public static void LoadSettingFiles()
        {
            try
            {
                //if (GlobalVar.USE_KEY)
                    LoadOrMakeKey();                    
            }
            catch(Exception e)
            {
                throw new System.Exception(e.Message);
            }
        }

        private static char[] AllowChar = "$%#@!*abcdefghijklmnopqrstuvwxyz1234567890?;:ABCDEFGHIJKLMNOPQRSTUVWXYZ^&".ToCharArray();

        public static void LoadOrMakeKey()
        {
            if (string.IsNullOrEmpty(GlobalVar.EncKey))
            {
                if (File.Exists(GlobalVar.FILE_NAME_KEY))
                {
                    using (StreamReader reader = new StreamReader("Key.txt"))
                    {
                        string strValue = reader.ReadLine();
                        GlobalVar.EncKeyVer = strValue;
                        strValue = reader.ReadLine();
                        GlobalVar.EncKey = strValue;
                    }
                }
                else
                {
                    MakeKey();
                }
            }
        }

        public static void MakeKey()
        {
            GlobalVar.EncKeyVer = GetRandomText(GlobalVar.KeyVerSize);
            GlobalVar.EncKey = GetRandomText(GlobalVar.KeySize);
            
            try
            {
                using(StreamWriter writer = new StreamWriter("Key.txt"))
                {
                    writer.WriteLine(GlobalVar.EncKeyVer);
                    writer.WriteLine(GlobalVar.EncKey);                    
                }
            }
            catch(Exception e)
            {
                throw new System.Exception(e.Message);                
            }

        }

        public static bool RunDBEncrypt()
        {
            string strToolPath = string.Format("{0}/{1}", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_DATA), GlobalVar.ENCRYPT_BATCH_NAME);
            System.Diagnostics.ProcessStartInfo cProcess = new System.Diagnostics.ProcessStartInfo();
            cProcess.FileName = string.Format("{0}/{1}.bat", strToolPath, GlobalVar.ENCRYPT_BATCH_NAME);
            cProcess.UseShellExecute = false;
            cProcess.RedirectStandardError = true;
            cProcess.RedirectStandardOutput = true;
            cProcess.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            cProcess.Arguments = string.Format("\"{0}\" \"{1}\" \"{2}\"", strToolPath, GlobalVar.EncKeyVer, GlobalVar.EncKey);
            cProcess.CreateNoWindow = true;
            
            string strOutput = string.Empty;
            string strError = string.Empty;
            try
            {
                using(System.Diagnostics.Process process = System.Diagnostics.Process.Start(cProcess))
                {
                    using(StreamReader reader = process.StandardError)
                        strError = reader.ReadToEnd();

                    using(StreamReader reader = process.StandardOutput)
                        strOutput = reader.ReadToEnd();
                }
            }
            catch(Exception e)
            {
                throw new System.Exception(e.Message);                
            }

            if(string.IsNullOrEmpty(strError))
            {
                return true;
            }
            else
            {
                LogForm cForm = new LogForm();
                cForm.SetText(string.Format(GlobalVar.FMT_LOG, "RunDBEncrypt", strOutput, strError));
                cForm.ShowDialog();

                return false;
            }
        }


        private static string GetRandomText(int nLength)
        {
            var ran = new Random(DateTime.Now.Millisecond);
            var sb = new StringBuilder();

            for(int i = 0 ; i < nLength ; ++i)
            {
                int nRanNum = ran.Next(0, AllowChar.Length);
                sb.Append(AllowChar[nRanNum]);
            }

            return sb.ToString();
        }


        public static List<string> GetAllExcelEnumFile()
        {
            var arrFiles = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_ENUM_DATA));

            if(arrFiles == null || arrFiles.Length == 0)
                return null;

            List<string> listFiles = new List<string>();
            for(int i = 0 ; i < arrFiles.Length ; ++i)
            {
                if(CheckEnumFile(arrFiles[i]))
                    listFiles.Add(arrFiles[i]);
            }

            return listFiles;
        }

        public static string GetFullExcelEnumFileName(string strFileName)
        {
            var arrFiles = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_ENUM_DATA));

            if(arrFiles == null || arrFiles.Length == 0)
                return null;
            
            for(int i = 0 ; i < arrFiles.Length ; ++i)
            {
                if(arrFiles[i].Contains(strFileName) && CheckEnumFile(arrFiles[i]))
                    return arrFiles[i];                
            }

            return null;
        }

        public static EExcelType GetExcelType(string strFileName)
        {
            if(IsEnumFile(strFileName))
                return EExcelType.TYPE;

            if(IsLocalizationFile(strFileName))
                return EExcelType.LOCALIZATION;

            return EExcelType.TABLE;
        }

        public static bool IsEnumFile(string strFileName)
        {
            if(string.IsNullOrEmpty(strFileName))
                return false;
                
            string strName = Path.GetFileNameWithoutExtension(strFileName);

            return IsEnumName(strName);
        }

        public static bool IsEnumName(string strName)
        {
            if(string.IsNullOrEmpty(strName))
                return false;
            return strName.Contains("enum_");
        }

        public static bool IsLocalizationFile(string strFileName)
        {
            if(string.IsNullOrEmpty(strFileName))
                return false;

            string strName = Path.GetFileNameWithoutExtension(strFileName);
            return strName.Contains("LZ_");
        }

        public static bool CheckEnumFile(string strFileName)
        {
            if(string.IsNullOrEmpty(strFileName))
                return false;
            
            return CheckRunningExcelFile(strFileName) && IsEnumFile(strFileName);
        }

        public static bool CheckRunningExcelFile(string strFileName)
        {
            if(strFileName.Contains("~$"))
                return false;

            return true;
        }

        public static string GetCellName(int nRow, int nCol)
        {
            string str = string.Empty;

            int i = nCol / 26;
            int j = nCol % 26;

            if (i == 0)
            {
                return string.Format("{0}{1}", Convert.ToChar(j + 65), nRow);
            }
            else
                return string.Format("{0}{1}{2}", Convert.ToChar(i + 64), Convert.ToChar(j + 65), nRow);
        }

        public static string GetRefSheetName(string formula)
        {
            int firstIndex = formula.IndexOf('(') + 1;
            int endIndex = formula.IndexOf('!');

            if (endIndex == -1 || firstIndex == -1)
                return string.Empty;

            string str = formula.Substring(firstIndex, endIndex - firstIndex);
            return str;
        }

        public static EDataType GetEnumDataType(string text)
        {
            if(string.Compare(text, "ID", true) == 0)
                return EDataType.INT;
            else if(string.Compare(text, "S_Type", true) == 0)
                return EDataType.STRING;
            else if(string.Compare(text, "Comment", true) == 0)
                return EDataType.STRING;
            else
                return EDataType.MAX;
        }

        public static EDataType GetProtocolDescDataType(string text)
        {
            if (string.Compare(text, "name", true) == 0)
                return EDataType.STRING;
            else if (string.Compare(text, "value", true) == 0)
                return EDataType.INT;
            else if (string.Compare(text, "Description", true) == 0)
                return EDataType.STRING;
            else
                return EDataType.MAX;
        }

        public static EDataType GetProtocolDataType(string text)
        {
            if (string.Compare(text, "Cmd", true) == 0)
                return EDataType.INT;
            else if (string.Compare(text, "Name", true) == 0)
                return EDataType.STRING;
            else if (string.Compare(text, "DataType", true) == 0)
                return EDataType.STRING;
            else if (string.Compare(text, "Data", true) == 0)
                return EDataType.STRING;
            else
                return EDataType.MAX;
        }

        public static EDataType GetDataType(string strText)
        {
            if(string.IsNullOrEmpty(strText))
                return EDataType.NONE;

            for(EDataType eType = EDataType.NONE ; eType < EDataType.MAX ; ++eType)
            {
                if (string.Compare(strText, eType.ToString(), true) == 0)
                {
                    return eType;
                }
            }

            if(IsEnumName(strText))
            {
                return EDataType.ENUM;
            }

            return EDataType.MAX;
        }

        public static ETargetType GetTargetType(string strText)
        {
            for(ETargetType eType = 0 ; eType < ETargetType.MAX ; ++eType)
            {
                if(string.Compare(strText, eType.ToString(), true) == 0)
                {
                    return eType;
                }
            }

            return ETargetType.MAX;
        }

        public static bool IsTableSheet(string strSheetName)
        {
            if (strSheetName.StartsWith("_"))
                return false;
            
            if (strSheetName.Contains("Temp") || strSheetName.Contains("Scheme") || strSheetName.Contains("Schema") || strSheetName.Contains("Sheet"))
                return false;

            foreach(char c in strSheetName.ToCharArray())
            {
                if(char.GetUnicodeCategory(c) == System.Globalization.UnicodeCategory.OtherLetter)
                    return false;
            }

            return true;
        }
        public static bool IsSharedStructureSheet(string name)
        {
            if (name.StartsWith("_$_"))
                return true;

            return false;
        }

        public static bool IsSkipColumn(string strColName)
        {
            if(string.IsNullOrEmpty(strColName))
                return true;

            if(strColName.Contains("*") || strColName.Contains("&"))
                return true;

            return false;
        }

        public static string GetDataInfoString(EDataType eType, DataInfo cInfo)
        {
            switch(eType)
            {
            case EDataType.INT:
                return cInfo.nValue.ToString();
            case EDataType.FLOAT:
                return cInfo.fValue.ToString();
            case EDataType.STRING:
                return cInfo.strValue;
            case EDataType.LONG:
                return cInfo.lValue.ToString();
            case EDataType.BOOL:
                return cInfo.bValue.ToString();
            }

            return string.Empty;
        }

        public static int GetTargetExceptionCount(List<ColData> listCollData, ETargetType eType)
        {
            int nExceptionCount = 0;

            for(int i = 0 ; i < listCollData.Count ; ++i)
            {
                switch(listCollData[i].eTargetType)
                {
                case ETargetType.MAX:
                case ETargetType.NONE:
                    ++nExceptionCount;
                    break;
                case ETargetType.CLIENT:
                case ETargetType.SERVER:
                    if(listCollData[i].eTargetType != eType)
                        ++nExceptionCount;
                    break;
                }
            }

            return nExceptionCount;
        }

        public static string MakeAbsolutePath(string path)
        {
            return Path.GetFullPath(System.Windows.Forms.Application.StartupPath + path);
        }

        public static string MakeCamelString(string str)
        {
            if (string.IsNullOrWhiteSpace(str))
                return "";


            string[] strSplits = str.Split('_');

            StringBuilder stringBuilder = new StringBuilder();

            foreach (string subSplit in strSplits)
            {
                stringBuilder.Append(UpperFirstChar(subSplit));
            }

            return stringBuilder.ToString();
        }

        public static string UpperFirstChar(string str)
        {
            string first = str.Substring(0, 1);
            string remain = str.Substring(1);
            return new CultureInfo("en-US", false).TextInfo.ToUpper(first) + remain;
        }

        public static bool CheckExcelFile(string strFullFileName)
        {
            if (strFullFileName.Contains(".xlsx"))
                return false;

            return true;
        }

        public static SqlConnection GetSqlConnection()
        {
            return new SqlConnection("Server = 172.20.40.225; Database=dev_da_data_db;uid=SA;pwd=Spwj7720!");
        }

    }
}
