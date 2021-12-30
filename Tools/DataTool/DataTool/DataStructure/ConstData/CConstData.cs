using DataTool.Global;

namespace DataTool
{
    public partial class CConstData : CDataBase
    {
        public CConstData(ExcelManager cMgr, string strFile, EventHandler cEvtHandler) 
            : base(cMgr, strFile, cEvtHandler)
        {
            Type = EExcelType.CONSTDATA;
        }

        public override void MakeClientDataFile(string strDataFileType = "")
        {
            base.MakeClientDataFile(GlobalVar.DATAFILETYPENAME_CONSTDATA);
        }

        public override void MakeSourceCode()
        {
            MakeCppSourceCode();
        }
    }
}
