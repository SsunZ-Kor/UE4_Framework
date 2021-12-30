using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataTool.Global;

namespace DataTool
{
    public class CExcelData
    {
        public SheetData[]      arrSheetData = null;
        public EExcelType       eExcelType = EExcelType.MAX;

        public SheetData GetSheetData(string strSheetName)
        {
            for(int i = 0 ; i < arrSheetData.Length ; ++i)
            {
                if(string.Compare(arrSheetData[i].strName, strSheetName) == 0)
                    return arrSheetData[i];
            }

            throw new System.Exception(string.Format("{0} 시트를 찾을수 없습니다.", strSheetName));
        }
    }
}
