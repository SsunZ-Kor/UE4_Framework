using DataLoadLib.Global;
using DataTool.Global;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;

namespace DataTool
{
    partial class ExcelManager
    {
        private void SaveCSharpStructFile(SheetData cSheetData)
        {
            string relativePath = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CS_FILE);

            if (!Directory.Exists(relativePath))
                Directory.CreateDirectory(relativePath);

            string camelSheetName = MakeCamelString(cSheetData.strName);

            string strPath = string.Format("{0}/C{1}.cs", relativePath, camelSheetName);

            using(StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), Encoding.Unicode))
            {
                ////writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("");
                writer.WriteLine("using DataLoadLib.Global;");
                writer.WriteLine("using System.Collections.Generic;");
                writer.WriteLine("using DataFileEnum;");
                writer.WriteLine("");
                writer.WriteLine("namespace DataFileEnum");
                writer.WriteLine("{");
                writer.WriteLine(string.Format("\tpublic class C{0} : CDataFileBase", camelSheetName));
                writer.WriteLine("\t{");

                var listColData = MakeCamelColData(cSheetData.listColData);
                int nIndex = 1;
                for(int i = nIndex ; i < listColData.Count ; ++i)
                {
                    if(listColData[i].eTargetType != ETargetType.CLIENT && listColData[i].eTargetType != ETargetType.ALL)
                        continue;

                    var eType = listColData[i].eDataType;
                    switch(eType)
                    {
                    case EDataType.ENUM:
                        string strTypeName = "E"+listColData[i].strTypeName.Split('_')[1];
                        writer.WriteLine(string.Format("\t\tpublic {0} {1} {2}", strTypeName, listColData[i].strExcelColName, "{ get; private set; }"));
                        break;
                    case EDataType.FLOAT:
                    case EDataType.INT:
                    case EDataType.STRING:
                    case EDataType.LONG:
                    case EDataType.BOOL:
                            string strType = listColData[i].eDataType.ToString().ToLower();
                        writer.WriteLine(string.Format("\t\tpublic {0} {1} {2}", strType, listColData[i].strExcelColName, "{ get; private set; }"));
                        break;
                    }
                }

                writer.WriteLine("");
                writer.WriteLine(string.Format("\t\tpublic C{0}(TableInfo cInfo) : base(cInfo) {1}", camelSheetName, "{ }"));
                writer.WriteLine("");
                writer.WriteLine("\t\tprotected override void SetInfo(TableInfo cInfo)");
                writer.WriteLine("\t\t{");
                
                for(int i = nIndex ; i < listColData.Count ; ++i)
                {
                    if(listColData[i].eTargetType != ETargetType.CLIENT && listColData[i].eTargetType != ETargetType.ALL)
                        continue;

                    var eType = listColData[i].eDataType;
                    switch(eType)
                    {
                    case EDataType.ENUM:
                        string strTypeName = "E"+listColData[i].strTypeName.Split('_')[1];
                        writer.WriteLine(string.Format("\t\t\tthis.{0} = ({1})cInfo.GetIntValue({2});", listColData[i].strExcelColName, strTypeName, nIndex++));
                        break;
                    case EDataType.FLOAT:
                        writer.WriteLine(string.Format("\t\t\tthis.{0} = cInfo.GetFloatValue({1});", listColData[i].strExcelColName, nIndex++));
                        break;
                    case EDataType.INT:
                        writer.WriteLine(string.Format("\t\t\tthis.{0} = cInfo.GetIntValue({1});", listColData[i].strExcelColName, nIndex++));
                        break;
                    case EDataType.STRING:
                        writer.WriteLine(string.Format("\t\t\tthis.{0} = cInfo.GetStrValue({1});", listColData[i].strExcelColName, nIndex++));
                        break;
                    case EDataType.LONG:
                        writer.WriteLine(string.Format("\t\t\tthis.{0} = cInfo.GetFloatValue({1});", listColData[i].strExcelColName, nIndex++));
                        break;
                    case EDataType.BOOL:
                        writer.WriteLine(string.Format("\t\t\tthis.{0} = cInfo.GetBoolValue({1});", listColData[i].strExcelColName, nIndex++));
                        break;
                    }
                }

                writer.WriteLine("\t\t}");
                writer.WriteLine("\t}");
                writer.WriteLine("}");
            }
        }

        private List<ColData> MakeCamelColData(List<ColData> colDatas)
        {
            List<ColData> tempColDatas = new List<ColData>();
            
            foreach (ColData colData in colDatas)
            {
                ColData data = new ColData
                {
                    eDataType = colData.eDataType,
                    eTargetType = colData.eTargetType,
                    nColIndex = colData.nColIndex,
                    strMemo = colData.strMemo,
                    strTypeName = colData.strTypeName,
                    strExcelColName = MakeCamelString(colData.strExcelColName)
                };
                tempColDatas.Add(data);
            }
            return tempColDatas;
        } 

        public string MakeCamelString(string str)
        {
            if (string.IsNullOrWhiteSpace(str))
                return "";


            string[] strSplits = str.Split('_');

            StringBuilder stringBuilder = new StringBuilder();

            foreach(string subSplit in strSplits)
            {
                stringBuilder.Append(UpperFirstChar(subSplit));
            }

            return stringBuilder.ToString();
        }

        public string UpperFirstChar(string str)
        {
            string first = str.Substring(0, 1);
            string remain = str.Substring(1);
            return new CultureInfo("en-US", false).TextInfo.ToUpper(first) + remain;
        }

        public string LowerFirstChar(string str)
        {
            string first = str.Substring(0, 1);
            string remain = str.Substring(1);
            return new CultureInfo("en-US", false).TextInfo.ToLower(first) + remain;
        }

        public string MakeLineOfCSCodeByDataType(string dataType, string dataName)
        {
            if (string.IsNullOrWhiteSpace(dataName) || string.IsNullOrWhiteSpace(dataName))
                return "";

            return string.Format("\tpublic {0} {1};", GetCSDataType(dataType, true), dataName);
        }

        private string GetCSDataType(string dataType, bool isFirst)
        {
            switch (dataType.Trim())
            {
                case "int":
                case "Int":
                case "INT":
                     return "int";
                case "long":
                case "Long":
                case "LONG":
                    return "long";
                case "float":
                case "Float":
                case "FLOAT":
                    return "float";
                case "double":
                case "Double":
                case "DOUBLE":
                    return "double";
                case "boolean":
                case "Boolean":
                case "BOOLEAN":
                case "bool":
                case "Bool":
                case "BOOL":
                    return "bool";
                case "string":
                case "String":
                case "STRING":
                    return "string";
                case "date":
                case "Date":
                case "DATE":
                    return "DateTime";
                default:
                    if (dataType.Trim().StartsWith("array") || dataType.Trim().StartsWith("Array") || dataType.Trim().StartsWith("ARRAY")
                        || dataType.Trim().StartsWith("list") || dataType.Trim().StartsWith("List") || dataType.Trim().StartsWith("LIST"))
                    {
                        int startIndex = dataType.IndexOf("<") + 1;
                        int endIndex = dataType.LastIndexOf(">");

                        if (startIndex < 0 || endIndex < 0)
                        {
                            return dataType;
                        }

                        string typeName = dataType.Substring(startIndex, endIndex - startIndex);

                        return string.Format("{0}[]", GetCSDataType(typeName, false));
                    }
                    else if (dataType.Trim().EndsWith("[]"))
                    {
                        int startIndex = 0;
                        int endIndex = dataType.LastIndexOf("[");

                        if (startIndex < 0 || endIndex < 0)
                        {
                            return dataType;
                        }

                        string typeName = dataType.Substring(startIndex, endIndex - startIndex);

                        return string.Format("{0}[]", GetCSDataType(typeName, false));
                    }
                    return dataType;
            }
        }

        public string MakeLineOfJavaCodeByDataType(string dataType, string dataName, List<string> outList = null)
        {
            if (string.IsNullOrWhiteSpace(dataName) || string.IsNullOrWhiteSpace(dataName))
                return "";

            string javaDataType = GetJavaDataType(dataType, true);

            if (outList != null && javaDataType.Contains("List"))
                outList.Add(string.Format("\t{0} = new Array{1}();", dataName, javaDataType));
            else if (outList != null && !isDefaultType(javaDataType))
                outList.Add(string.Format("\t{0} = new {1}();", dataName, javaDataType));

            return string.Format("\tpublic {0} {1};", GetJavaDataType(dataType, true), dataName);
        }     
        
        private bool isDefaultType(string dataType)
        {
            switch (dataType.Trim())
            {
                case "int":
                case "Int":
                case "INT":                    
                case "long":
                case "Long":
                case "LONG":                  
                case "float":
                case "Float":
                case "FLOAT":                   
                case "double":
                case "Double":
                case "DOUBLE":                  
                case "boolean":
                case "Boolean":
                case "BOOLEAN":
                case "bool":
                case "Bool":
                case "BOOL":                    
                case "string":
                case "String":
                case "STRING":                    
                case "date":
                case "Date":
                case "DATE":
                    return true;
                default:                    
                    return false;
            }
        }

        private string GetJavaDataType(string dataType, bool isFirst)
        {
            switch (dataType.Trim())
            {
                case "int":
                case "Int":
                case "INT":
                    if (isFirst)
                        return "int";
                    else
                        return "Integer";
                case "long":
                case "Long":
                case "LONG":
                    if (isFirst)
                        return "long";
                    else
                        return "Long";
                case "float":
                case "Float":
                case "FLOAT":
                    if (isFirst)
                        return "float";
                    else
                        return "Float";
                case "double":
                case "Double":
                case "DOUBLE":
                    if (isFirst)
                        return "double";
                    else
                        return "Double";
                case "boolean":
                case "Boolean":
                case "BOOLEAN":
                case "bool":
                case "Bool":
                case "BOOL":
                    if (isFirst)
                        return "boolean";
                    else
                        return "Boolean";
                case "string":
                case "String":
                case "STRING":
                    return "String";                
                case "date":
                case "Date":
                case "DATE":
                    return "Date";                    
                default:
                    if (dataType.Trim().StartsWith("array") || dataType.Trim().StartsWith("Array") || dataType.Trim().StartsWith("ARRAY") 
                        || dataType.Trim().StartsWith("list") || dataType.Trim().StartsWith("List") || dataType.Trim().StartsWith("LIST"))
                    {
                        int startIndex = dataType.IndexOf("<") + 1;
                        int endIndex = dataType.LastIndexOf(">");

                        if (startIndex < 0 || endIndex < 0)
                        {
                            return dataType;
                        }

                        string typeName = dataType.Substring(startIndex, endIndex - startIndex);

                        return string.Format("List<{0}>", GetJavaDataType(typeName, false));
                    } 
                    else if(dataType.Trim().EndsWith("[]"))
                    {
                        int startIndex = 0;
                        int endIndex = dataType.LastIndexOf("[");

                        if (startIndex < 0 || endIndex < 0)
                        {
                            return dataType;
                        }

                        string typeName = dataType.Substring(startIndex, endIndex - startIndex);

                        return string.Format("List<{0}>", GetJavaDataType(typeName, false));
                    }
                    return dataType;
            }
        }

        private void SaveCSharpConstFile(SheetData cSheetData)
        {
            string relativePath = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CS_FILE);

            if (!Directory.Exists(relativePath))
                Directory.CreateDirectory(relativePath);            

            string strPath = string.Format("{0}/C{1}.cs", relativePath, cSheetData.strName);

            using(StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), Encoding.Unicode))
            {
                //writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("");

                writer.WriteLine("using DataLoadLib.Global;");
                writer.WriteLine("");
                writer.WriteLine("namespace DataFileEnum");
                writer.WriteLine("{");
                writer.WriteLine("\tpublic static class CConstData");
                writer.WriteLine("\t{");

                string strInitializer = "\t\tpublic static void SetInfo(int[] arrIntData, string[] arrStrData)\n\t\t{\n";

                for(int nRow = 0 ; nRow < cSheetData.nRowCount ; ++nRow)
                {
                    if(cSheetData.arrCellData[nRow, 0] == null)
                    {
                        throw new System.Exception("Error");
                    }

                    string strName = cSheetData.arrCellData[nRow, 1].GetStrValue();
                    int nValue = cSheetData.arrCellData[nRow, 2].GetIntValue();
                    string strValue = cSheetData.arrCellData[nRow, 3].GetStrValue();

                    if(string.IsNullOrEmpty(strValue))
                    {
                        writer.WriteLine("\t\tpublic static int {0} = {1};", strName, nValue);
                        strInitializer += string.Format("\t\t\t{0} = arrIntData[{1}];\n", strName, nRow);
                    }
                    else
                    {
                        writer.WriteLine("\t\tpublic static string {0} = \"{1}\";", strName, strValue);
                        strInitializer += string.Format("\t\t\t{0} = string.Copy(arrStrData[{1}]);\n", strName, nRow);
                    }
                }

                writer.WriteLine("");
                writer.Write(strInitializer);
                writer.WriteLine("\t\t}");
                writer.WriteLine("\t}");
                writer.WriteLine("}");
            }
        }

        private void SaveJavaConstFile(SheetData cSheetData)
        {
            string relativePath = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_CONST_DATA);

            if (!Directory.Exists(relativePath))
                Directory.CreateDirectory(relativePath);

            string strPath = string.Format("{0}/{1}.java", relativePath, cSheetData.strName);

            UTF8Encoding encoding = new UTF8Encoding(false);
            using(StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), encoding))
            {
                //writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("");

                writer.WriteLine("package snowpipe.common.constdata.generated;");
                writer.WriteLine("");
                writer.WriteLine("public final class ConstData");
                writer.WriteLine("{");

                for(int nRow = 0 ; nRow < cSheetData.nRowCount ; ++nRow)
                {
                    if(cSheetData.arrCellData[nRow, 0] == null)
                    {
                        throw new System.Exception("Error");
                    }

                    string strName = cSheetData.arrCellData[nRow, 1].GetStrValue();
                    int nValue = cSheetData.arrCellData[nRow, 2].GetIntValue();
                    string strValue = cSheetData.arrCellData[nRow, 3].GetStrValue();

                    if(string.IsNullOrEmpty(strValue))
                        writer.WriteLine("\tpublic static final int {0} = {1};", strName, nValue);
                    else
                        writer.WriteLine("\tpublic static final String {0} = \"{1}\";", strName, strValue);
                }

                writer.WriteLine("}");
            }
        }
    }
}
