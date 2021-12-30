using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using DataTool.Global;
using Excel = Microsoft.Office.Interop.Excel;

namespace DataTool
{
    public partial class CDataBase
    {
        public virtual void LoadExcel()
        {
            try
            {
                if (m_cMgr == null || string.IsNullOrEmpty(FullFileName))
                    return;

                if (m_Excel == null)
                    m_Excel = new Excel.Application();

                m_cEvtHandler?.ChangeStatus?.Invoke(string.Format(GlobalVar.FMT_LOADING_FILE, FullFileName));

                Excel.Range excelRange;
                var workBook = m_Excel.Workbooks.Open(FullFileName, 0, true);

                int nIndex = 0;

                SheetDatas = new List<SheetData>();

                foreach (Excel.Worksheet sheet in workBook.Sheets)
                {
                    SheetData cData = new SheetData();
                    string strName = sheet.Name;

                    excelRange = sheet.get_Range("A1").SpecialCells(Excel.XlCellType.xlCellTypeLastCell);

                    if (GlobalFunctions.IsTableSheet(sheet.Name))
                    {
                        cData = new SheetData();
                        SetStruct(sheet, ref cData, excelRange);
                    }

                    if (cData != null && cData.listColData != null && cData.listColData.Count > 0)
                    {
                        cData.strName = strName;
                        SheetDatas.Add(cData);
                    }

                    ++nIndex;
                }

                m_cEvtHandler?.ChangeProgress?.Invoke();
                m_cEvtHandler?.ChangeStatus?.Invoke(string.Format(GlobalVar.FMT_LOADEND_FILE, FullFileName));                
            }
            catch (Exception e)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke(e.Message);
            }
            finally
            {
                ClearExcelWorkBook();
            }
        }
    }
}
