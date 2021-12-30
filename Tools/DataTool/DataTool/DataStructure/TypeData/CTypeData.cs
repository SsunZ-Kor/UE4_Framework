using DataTool.Global;

namespace DataTool
{
    public partial class CTypeData : CDataBase
    {
        public CTypeData(ExcelManager cMgr, string strFile, EventHandler cEvtHandlaer) 
            : base(cMgr, strFile, cEvtHandlaer)
        {
            Type = EExcelType.TYPE;
        }
    }
}
