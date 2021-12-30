using System;
using DataTool.Global;
using System.Threading;
using Excel = Microsoft.Office.Interop.Excel;
using System.IO;
using System.Collections.Generic;

namespace DataTool
{
    public abstract partial class CDataBase
    {
        protected   ExcelManager        m_cMgr = null;
        protected   EventHandler        m_cEvtHandler = null;

        protected   Excel.Application   m_Excel = null;
        //protected Excel.Workbook m_excelWorkBook = null;
        //protected Excel.Application m_excelApplication = null;

        public List<SheetData> SheetDatas { get; protected set; } = null;
        public EExcelType Type { get; protected set; } = EExcelType.MAX;

        public string FullFileName { get; private set; } = string.Empty;

        public bool failedOpenExcel = false;
        
        public CDataBase(ExcelManager cMgr, string strFile, EventHandler cEvtHandler)
        {
            if(string.IsNullOrEmpty(strFile) || !GlobalFunctions.CheckRunningExcelFile(strFile))
            {
                failedOpenExcel = true;

                if (string.IsNullOrEmpty(strFile))
                    cEvtHandler?.ChangeStatus?.Invoke("Empty file");
                else
                {
                    cEvtHandler?.ChangeStatus?.Invoke("Running Excel");     
                }
                    
                return;
            }

            m_cMgr = cMgr;
            FullFileName = strFile;
            m_cEvtHandler = cEvtHandler;
            cEvtHandler?.ChangeStatus?.Invoke(string.Format(GlobalVar.FMT_INITIAL_FILE, FullFileName));


            //if (m_excelApplication == null)
            //    SetExcelApplicationReset();
        }

        ~CDataBase()
        {
            if(m_Excel != null)
            {
                m_Excel.Quit();
                m_Excel = null;
            }            
            //ClearExcelApplication();
        }

        protected virtual bool SetStruct(Excel.Worksheet sheet, ref SheetData cSheetData, Excel.Range range) { return false; }

        public virtual void MakeSourceCode() { }

        public void ClearExcelWorkBook()
        {
            if (m_Excel == null)
                return;

            m_Excel.Workbooks.Close();
            m_Excel.Quit();
            m_Excel = null;
        }
        //public virtual void SetExcelApplicationReset()
        //{
        //    if (m_excelApplication != null)
        //    {
        //        ClearExcelApplication();
        //    }

        //    m_excelApplication = new Excel.Application();
        //}

        //public virtual void ClearExcelApplication()
        //{
        //    if (m_excelWorkBook != null)
        //    {
        //        m_excelWorkBook.Close(false);
        //        m_excelWorkBook = null;
        //    }

        //    if (m_excelApplication != null)
        //    {
        //        m_excelApplication.Quit();
        //        m_excelApplication = null;
        //    }
        //}

        protected List<ColData> MakeCamelColData(List<ColData> colDatas)
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
                    strExcelColName = GlobalFunctions.MakeCamelString(colData.strExcelColName)
                };
                tempColDatas.Add(data);
            }
            return tempColDatas;
        }
    }
}
