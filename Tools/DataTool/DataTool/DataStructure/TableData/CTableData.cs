using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Threading;

using DataTool.Global;
using DataLoadLib.Global;

using System.IO;

namespace DataTool
{
    public partial class CTableData : CDataBase
    {
        public bool IsNeedToEnumParse { get; private set; } = false;
        public CTableData(ExcelManager cMgr, string strFile, EventHandler cEvtHandler) 
            : base(cMgr, strFile, cEvtHandler)
        {
            Type = EExcelType.TABLE;
        }

        public override void LoadExcel()
        {
            base.LoadExcel();

            m_cEvtHandler?.LoadEnd?.Invoke(FullFileName);
        }

        public override void MakeSourceCode()
        {
            MakeCppSourceCode();
        }
    }
}
