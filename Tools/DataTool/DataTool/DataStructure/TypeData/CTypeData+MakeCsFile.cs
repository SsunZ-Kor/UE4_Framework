using System;
using DataLoadLib.Global;
using System.IO;

namespace DataTool
{
    public partial class CTypeData
    {
        public void WriteFileClientCsFile(StreamWriter file)
        {
            foreach (SheetData cSheetData in this.SheetDatas)
            {
                try
                {
                    if (cSheetData == null || cSheetData.listColData == null || cSheetData.arrCellData == null)
                        return;

                    string strEnumName = "E" + cSheetData.strName.Split('_')[1];

                    file.WriteLine(string.Format("\tpublic enum {0}", strEnumName));
                    file.WriteLine("\t{");
                    for (int i = 0; i < cSheetData.nRowCount; ++i)
                    {
                        if (cSheetData.arrCellData[i, 0] != null)
                        {
                            int nValue = cSheetData.arrCellData[i, 0].GetIntValue();
                            string strTypeName = cSheetData.arrCellData[i, 1].GetStrValue();

                            if (string.IsNullOrEmpty(strTypeName))
                                continue;

                            if (cSheetData.listColData.Count > 2 && cSheetData.listColData[2].eDataType != EDataType.MAX)
                            {
                                string strComment = cSheetData.arrCellData[i, 2].GetStrValue();
                                if (string.IsNullOrEmpty(strComment))
                                    file.WriteLine(string.Format("\t\t{0} = {1},", strTypeName, nValue));
                                else
                                    file.WriteLine(string.Format("\t\t{0} = {1},\t//{2}", strTypeName, nValue, strComment));
                            }
                            else
                            {
                                file.WriteLine(string.Format("\t\t{0} = {1},", strTypeName, nValue));
                            }
                        }
                    }
                    file.WriteLine("\t}");
                }
                catch (Exception e)
                {
                    throw new System.Exception(string.Format("CTypeData:WriteTypeDataToCSEnumFile(), {0}, {1}", cSheetData.strName, e.Message));
                }
            }
        }
    }
}
