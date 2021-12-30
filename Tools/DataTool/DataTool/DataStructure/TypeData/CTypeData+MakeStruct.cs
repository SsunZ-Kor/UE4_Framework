using System;
using Excel = Microsoft.Office.Interop.Excel;
using DataTool.Global;
using DataLoadLib.Global;

namespace DataTool
{
    public partial class CTypeData
    {
        protected override bool SetStruct(Excel.Worksheet sheet, ref SheetData cSheetData, Excel.Range range)
        {
            try
            {
                if (range.Row <= 1 || range.Column < 2)
                {
                    cSheetData.nRowCount = 0;
                    cSheetData.nColCount = 0;
                    cSheetData.listColData.Clear();
                    cSheetData.arrCellData = null;

                    return false;
                }

                // 참조 테이블 정보 가져오기
                for (int nColl = 0; nColl < range.Column; ++nColl)
                {


                    Excel.Range dataRange;
                    dataRange = sheet.get_Range(GlobalFunctions.GetCellName(1, nColl));
                    string strExcelColName = dataRange.Text;

                    if (string.IsNullOrWhiteSpace(strExcelColName))
                        continue;

                    var cData = new ColData();
                    cData.strExcelColName = strExcelColName;
                    cData.strTypeName = string.Empty;
                    cData.nColIndex = nColl;
                    cData.eDataType = GlobalFunctions.GetEnumDataType(strExcelColName);
                    cData.eTargetType = ETargetType.ALL;

                    cSheetData.listColData.Add(cData);
                }

                cSheetData.nRowCount = range.Row - 1;
                cSheetData.nColCount = range.Column;
                cSheetData.arrCellData = new CellData[cSheetData.nRowCount, cSheetData.nColCount];

                for (int nRow = 2; nRow <= range.Row; ++nRow)
                {
                    int nIndex = 0;
                    for (int nCol = 0; nCol < range.Column; ++nCol)
                    {
                        if (cSheetData.listColData[nCol].eDataType == EDataType.MAX)
                            continue;

                        Excel.Range dataRange;
                        dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow, nCol));

                        CellData cData = new CellData();
                        cData.SetValue(dataRange.Text, cSheetData.listColData[nCol].eDataType);
                        cSheetData.arrCellData[nRow - 2, nIndex++] = cData;
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CTypeData:SetStruct(), {0}, {1}", cSheetData.strName, e.Message));
            }

            return true;
        }
    }
}
