using DataTool.Global;

namespace DataTool
{
    public partial class CLocalizationData : CDataBase
    {
        public CLocalizationData(ExcelManager cMgr, string strFile, EventHandler cEvtHandler) 
            : base(cMgr, strFile, cEvtHandler)
        {
            Type = EExcelType.TYPE;
        }

        public override void MakeClientDataFile(string strDataFileType = "")
        {
            base.MakeClientDataFile(GlobalVar.DATAFILETYPENAME_LOCALIZATION);
        }

        protected override string GetFilePath()
        {
            return GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_LOCALIZATION);
        }
    }
}
