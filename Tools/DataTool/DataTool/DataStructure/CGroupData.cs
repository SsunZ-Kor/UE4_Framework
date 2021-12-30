using DataTool.Global;

namespace DataTool
{
    public class CGroupData : CTableData
    {
        public CGroupData(ExcelManager cMgr, string strFile, EventHandler cEvtHandler) 
            : base(cMgr, strFile, cEvtHandler)
        {
            Type = EExcelType.GROUP;
        }        
    }
}
