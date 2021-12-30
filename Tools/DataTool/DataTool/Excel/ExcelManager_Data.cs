using DataLoadLib.Global;
using DataTool.Global;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DataTool
{
    partial class ExcelManager
    {

        #region Type Data

        public CTypeData GetTypeData(string strTypeName)
        {
            var strFullFileName = GlobalFunctions.GetFullExcelEnumFileName(strTypeName);

            if (strFullFileName == null)
                return null;

            if (m_dicTypeData.ContainsKey(strFullFileName))
                return m_dicTypeData[strFullFileName];

            return null;
        }

        public void SetTypeData(string strFileName)
        {
            var strFullFileName = GlobalFunctions.GetFullExcelEnumFileName(strFileName);
            if (string.IsNullOrEmpty(strFullFileName))
                return;

            if (m_dicTypeData.ContainsKey(strFullFileName))
                m_dicTypeData.Remove(strFullFileName);

            CTypeData cData = new CTypeData(this, strFullFileName, m_cEvtHandler);

            if(cData.failedOpenExcel)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke("엑셀이 실행중 입니다.");
                return;
            }    

            m_dicTypeData.Add(strFullFileName, cData);

            cData.LoadExcel();
        }

        public void SetAllTypeData()
        {
            List<string> listFiles = GlobalFunctions.GetAllExcelEnumFile();

            if (listFiles == null || listFiles.Count == 0)
                return;

            List<Thread> threads = new List<Thread>();

            foreach (string fileName in listFiles)
            {
                SetTypeData(fileName);
            }
        }

        public void WriteAllTypeData()
        {
            //TODO :
            //WriteAllServerJavaTypeData();
            //WriteAllClientCsTypeData();
            WriteAllClientCppTypeData();
        }

        public void WriteAllServerJavaTypeData()
        {
            if (!Directory.Exists(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_SHARED_DATA)))
                Directory.CreateDirectory(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_SHARED_DATA));

            foreach (KeyValuePair<string, CTypeData> typeData in m_dicTypeData)
            {
                typeData.Value.WriteFileServerJavaFile();
            }
        }

        public void WriteAllClientCsTypeData()
        {
            if (!Directory.Exists(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CS_FILE)))
                Directory.CreateDirectory(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CS_FILE));

            string strFileName = string.Format("{0}/{1}", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CS_FILE), GlobalVar.EXPORT_CS_ENUM_NAME);

            using (StreamWriter file = new StreamWriter(File.Open(strFileName, FileMode.Create), Encoding.Unicode))
            {
                //file.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                file.WriteLine("");

                file.WriteLine("namespace DataFileEnum");
                file.WriteLine("{");
                file.WriteLine();

                foreach (KeyValuePair<string, CTypeData> typeData in m_dicTypeData)
                {
                    typeData.Value.WriteFileClientCsFile(file);
                    file.WriteLine("");
                }

                file.WriteLine();
                file.WriteLine("}");
            }
        }

        public void WriteAllClientCppTypeData()
        {
            if (!Directory.Exists(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CPP_DATASTRUCTURE_FILE)))
                Directory.CreateDirectory(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CPP_DATASTRUCTURE_FILE));

            string strFileName = string.Format("{0}/{1}", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CPP_DATASTRUCTURE_FILE), GlobalVar.EXPORT_CPP_ENUM_NAME);

            try
            {
                using (StreamWriter file = new StreamWriter(File.Open(strFileName, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
                {
                    file.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                    file.WriteLine("// Drum");
                    file.WriteLine("#pragma once");
                    file.WriteLine("");

                    foreach (KeyValuePair<string, CTypeData> typeData in m_dicTypeData)
                    {
                        typeData.Value.WriteFileClientCppFile(file);
                        file.WriteLine("");
                    }
                }
            }
            catch(Exception e)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke(e.Message);
            }

            m_cFileMgr.SetMadeEnum();
        }

        #endregion //Type Data

        #region Table Data

        public CTableData GetTableData(string strFullFileName)
        {
            if (m_dicTableData.ContainsKey(strFullFileName))
                return m_dicTableData[strFullFileName];

            return null;
        }

        public void SetTableData(string strFullFileName, EExcelType excelType)
        {
            if (GlobalFunctions.CheckExcelFile(strFullFileName))
                return;

            if (string.IsNullOrEmpty(strFullFileName))
                return;

            CTableData cData;

            if (m_dicTableData.ContainsKey(strFullFileName))
            {
                cData = m_dicTableData[strFullFileName];
            }
            else
            {
                if (excelType == EExcelType.TABLE)
                {
                    cData = new CTableData(this, strFullFileName, m_cEvtHandler);
                }
                else
                {
                    cData = new CGroupData(this, strFullFileName, m_cEvtHandler);
                }

                if (cData.failedOpenExcel)
                {
                    m_cEvtHandler?.ShowMessageBox?.Invoke("엑셀이 실행중 입니다.");
                    return;
                }

                m_dicTableData.Add(strFullFileName, cData);
            }

            cData.LoadExcel();
        }

        public void SetAllTableData()
        {
            try
            {
                List<Thread> threads = new List<Thread>();

                List<string> arrTableFiles = new List<string>(Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_DATA)));
                //List<string> arrGroupFiles = new List<string>(Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_GROUP_DATA)));

                //if ((arrTableFiles == null && arrGroupFiles == null) || arrTableFiles.Count + arrGroupFiles.Count == 0)
                if (arrTableFiles == null || arrTableFiles.Count == 0)
                {
                    MessageBox.Show("Excel Table이 없습니다. 경로 설정을 다시 해주세요.");
                    return;
                }

                foreach (string strFullFileName in arrTableFiles)
                {
                    Thread thread = new Thread(() => SetTableData(strFullFileName, EExcelType.TABLE));
                    threads.Add(thread);
                }

                //foreach (string strFullFileName in arrGroupFiles)
                //{
                //    Thread thread = new Thread(() => SetTableData(strFullFileName, EExcelType.GROUP));
                //    threads.Add(thread);
                //}

                RunAsThreadPooling(threads);
            }
            catch (Exception e)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke(e.Message);
            }
        }       

        public void DoAllExcelTableFiles()
        {
            SetAllTypeData();
            WriteAllTypeData();            

            SetAllTableData();

            //SaveTableDataFile(false, ETargetType.ALL);
            SaveTableDataFile(ETargetType.CLIENT);

            DoAllConstData();
        }

        public bool IsChecked(string sheetName)
        {
            List<CheckBox> checkBoxs = new List<CheckBox>();
            if (m_dicCheckBoxList.TryGetValue(sheetName, out checkBoxs))
            {
                foreach (CheckBox checkBox in checkBoxs)
                {
                    if (checkBox.Text == sheetName && checkBox.Checked)
                        return true;
                }
            }
            return false;
        }

        public void SaveFileByType(SheetData sheetData ,EExcelType excelType, ETargetType targetType)
        {
            try
            {
                if (targetType == ETargetType.ALL || targetType == ETargetType.CLIENT)
                {
                    if (excelType == EExcelType.TABLE)
                    {
                        SaveClientDataFileEnc(sheetData, GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_DATA));
                    }
                    else
                    {
                        SaveClientGroupFilesEnc(sheetData, GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_GROUP_DATA));
                    }
                }

                if (targetType == ETargetType.ALL || targetType == ETargetType.SERVER)
                    SaveServerDataFile(sheetData, GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_SHARED_DATA));

                m_cEvtHandler?.ChangeProgress?.Invoke();
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("SaveFileByType() - {0}", e.Message));
            }            
        }

        public void SaveTableDataFile(string strFileName, ETargetType eType)
        {
            if (GlobalFunctions.CheckExcelFile(strFileName))
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke("엑셀 파일이 아닙니다. : " + strFileName);
                return;
            }

            CTableData cData;

            if (!m_dicTableData.ContainsKey(strFileName))
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke("데이터 로드에 문제가 있습니다. : " + strFileName);
                return;
            }

            cData = m_dicTableData[strFileName];

            try
            {
                cData.MakeClientDataFile();
                cData.MakeSourceCode();
            }
            catch (Exception e)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke(string.Format("SaveTableDataFile() {0}", e.Message));
            }

            if (cData.IsNeedToEnumParse && !m_cFileMgr.IsMadeEnum())
                m_parent.SetAddEnumJob(strFileName);

            m_cFileMgr.MakeDataCppFiles();
        }

        public void SaveTableDataFile(ETargetType eType)
        {
            try
            {
                List<Thread> threads = new List<Thread>();

                foreach (KeyValuePair<string, CTableData> tableData in m_dicTableData)
                {
                    threads.Add(new Thread(() =>
                    {
                        tableData.Value.MakeClientDataFile();
                        tableData.Value.MakeSourceCode();
                    }));
                }

                RunAsThreadPooling(threads);
            }
            catch(Exception e)
            {
                //if(bShowCheckMessageBox)
                //    m_cEvtHandler?.ShowMessageBox?.Invoke(string.Format("SaveTableDataFile() {0}", e.Message));
            }

            m_cFileMgr.MakeDataCppFiles();
        }

        #endregion 

        #region Localization Data

        public CLocalizationData GetLocalizationData(string strFileName)
        {
            if (m_dicLocalizationData.ContainsKey(strFileName))
                return m_dicLocalizationData[strFileName];

            return null;
        }

        public void SetLocalizationData(string strFileName)
        {
            if (m_dicLocalizationData.ContainsKey(strFileName))
                m_dicLocalizationData.Remove(strFileName);

            CLocalizationData cData = new CLocalizationData(this, strFileName, m_cEvtHandler);

            if (cData.failedOpenExcel)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke("엑셀이 실행중 입니다.");
                return;
            }

            m_dicLocalizationData.Add(strFileName, cData);

            cData.LoadExcel();
        }

        public void WriteLocalizationData(string strFileName)
        {
            List<string> arrFiles = new List<string>();
            arrFiles.Add(strFileName);

            DoLocalizationDatas(arrFiles);
        }

        //public void WriteLocalizationData(List<SheetData> SheetDatas, bool isSystemLocal = false)
        //{
        //    foreach(SheetData sheetData in SheetDatas)
        //    {
        //        if (isSystemLocal)
        //        {
        //            SaveClientDataFileEnc(sheetData, GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_SYSTEM_LOCAL_DATA), false, false);
        //        } 
        //        else
        //        {
        //            SaveClientDataFileEnc(sheetData, GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_LOCAL_DATA), false, true);
        //        }                                
        //    }

        //    m_cEvtHandler?.ChangeProgress?.Invoke();
        //}

        public void DoLocalizationDatas(List<string> arrFiles, bool isSystemLocal = false)
        {
            try
            {
                m_dicLocalizationData.Clear();

                List<Thread> threads = new List<Thread>();

                foreach (string fileName in arrFiles)
                {
                    //threads.Add(new Thread(() => { SetLocalizationData(fileName); }));
                    SetLocalizationData(fileName);
                }

                //RunAsThreadPooling(threads);

                threads.Clear();


                foreach (var tableData in m_dicLocalizationData)
                {
                    threads.Add(new Thread(() =>
                    {
                        tableData.Value.MakeClientDataFile("LocalizationData");
                    }));
                }

                RunAsThreadPooling(threads);
            }
            catch(Exception e)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke(string.Format("DoLocalizationDatas() {0}", e.Message));
            }

            m_cFileMgr.MakeLocalizationFiles();


            //foreach (KeyValuePair<string, CLocalizationData> localizationData in m_dicLocalizationData)
            //{



            //    threads.Add(new Thread(() => WriteLocalizationData(localizationData.Value.SheetDatas, isSystemLocal)));
            //}

            //RunAsThreadPooling(threads);
        }

        public void DoAllLocalizationData()
        {
            DoLocalizationData();
            //DoSystemLocalizationData();
        }

        public void DoLocalizationData()
        {
            List<string> arrFiles = new List<string>();
            arrFiles.AddRange(Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_LOCAL_DATA)));

            DoLocalizationDatas(arrFiles);
        }

        public void DoSystemLocalizationData()
        {
            List<string> arrFiles = new List<string>();
            arrFiles.AddRange(Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_SYS_LOCAL_DATA)));

            DoLocalizationDatas(arrFiles, true);
        }

        #endregion 

        #region Const Data

        public CConstData GetConstData(string strFileName)
        {
            if (m_dicConstData.ContainsKey(strFileName))
                return m_dicConstData[strFileName];

            return null;
        }

        public void SetConstData(string strFileName)
        {

            if (m_dicConstData.ContainsKey(strFileName))
                m_dicConstData.Remove(strFileName);

            CConstData cData = new CConstData(this, strFileName, m_cEvtHandler);

            if (cData.failedOpenExcel)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke("엑셀이 실행중 입니다.");
                return;
            }

            m_dicConstData.Add(strFileName, cData);

            cData.LoadExcel();
        }

        public void DoAllConstData()
        {
            var arrFiles = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_CONST_DATA));
            List<Thread> threads = new List<Thread>();

            foreach (string fileName in arrFiles)
            {
                threads.Add(new Thread(() => { SetConstData(fileName); }));
            }

            RunAsThreadPooling(threads);
            threads.Clear();

            //foreach (KeyValuePair<string, CConstData> constData in m_dicConstData)
            //{
            //    Thread thread = new Thread(() =>
            //    {
            //        foreach (SheetData sheetData in constData.Value.SheetDatas)
            //        {
            //            if (sheetData == null)
            //                continue;

            //            SaveClientDataFileEnc(sheetData, GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_DATA));
            //            SaveCSharpConstFile(sheetData);
            //            SaveJavaConstFile(sheetData);
            //        }

            //        m_cEvtHandler?.ChangeProgress?.Invoke();
            //    });
            //    threads.Add(thread);
            //}
            //RunAsThreadPooling(threads);

            //List<Thread> threads = new List<Thread>();

            foreach (KeyValuePair<string, CConstData> constData in m_dicConstData)
            {
                threads.Add(new Thread(() =>
                {
                    constData.Value.MakeClientDataFile();
                    constData.Value.MakeSourceCode();
                }));
            }

            RunAsThreadPooling(threads);

            //try
            //{
                
            //}
            //catch (Exception e)
            //{
            //     //m_cEvtHandler?.ShowMessageBox?.Invoke(string.Format("SaveTableDataFile() {0}", e.Message));
            //}

            m_cFileMgr.MakeDataCppFiles();
        }
        #endregion 


        #region protocol data
        public void SetProtocolData(string strFileName)
        {

            if (m_dicProtocolData.ContainsKey(strFileName))
                m_dicProtocolData.Remove(strFileName);

            CProtocolData cData = new CProtocolData(this, strFileName, m_cEvtHandler);

            if (cData.failedOpenExcel)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke("엑셀이 실행중 입니다.");
                return;
            }

            m_dicProtocolData.Add(strFileName, cData);

            cData.LoadExcel();
        }

        public void DoAllProtocolData()
        {
            var arrFiles = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_PROTOCOL_DATA));
            List<Thread> threads = new List<Thread>();

            foreach (string fileName in arrFiles)
            {
                threads.Add(new Thread(() => { SetProtocolData(fileName); }));
            }

            RunAsThreadPooling(threads);
            threads.Clear();

            foreach (KeyValuePair<string, CProtocolData> protocolData in m_dicProtocolData)
            {
                Thread thread = new Thread(() =>
                {                    
                    protocolData.Value.MakeSourceCode();
                    m_cEvtHandler?.ChangeProgress?.Invoke();
                });
                threads.Add(thread);
            }
            RunAsThreadPooling(threads);
        }
        


        #endregion
        public void RunAsThreadPooling(List<Thread> threads)
        {
            List<Thread> runThreads = new List<Thread>();

            while (!(threads.Count == 0 && runThreads.Count == 0))
            {
                if (runThreads.Count < 5 && threads.Count != 0)
                {
                    runThreads.Add(threads.First());

                    threads.RemoveAt(0);

                    runThreads.Last().Start();
                }

                for (int i = 0; i < runThreads.Count; i++)
                {
                    if (!runThreads[i].IsAlive)
                    {
                        runThreads.RemoveAt(i);
                        break;
                    }
                }
            }
        }
    }
}