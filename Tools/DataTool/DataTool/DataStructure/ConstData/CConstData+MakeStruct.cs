using DataLoadLib.Global;
using DataTool.Global;
using System;
using Excel = Microsoft.Office.Interop.Excel;

namespace DataTool
{
    public partial class CConstData
    {
        protected override bool SetStruct(Excel.Worksheet sheet, ref SheetData cSheetData, Excel.Range range)
        {
            try
            {
                if (range.Row < 2)
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

                    ColData colData = new ColData();

                    colData.strExcelColName = strExcelColName;
                    colData.strTypeName = string.Empty;
                    colData.nColIndex = nColl;
                    colData.eTargetType = ETargetType.ALL;

                    switch (strExcelColName)
                    {
                        case "DataId": colData.eDataType = EDataType.INT; break;
                        case "FieldName": colData.eDataType = EDataType.STRING; break;
                        case "IntValue": colData.eDataType = EDataType.INT; break;
                        case "StrValue": colData.eDataType = EDataType.STRING; break;
                        default: colData.eDataType = EDataType.MAX; break;
                    }

                    cSheetData.listColData.Add(colData);
                }

                int nRowMaxIndex = 0;
                for (int nRow = 2; nRow <= range.Row; ++nRow)
                {
                    Excel.Range dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow, 0));
                    try
                    {
                        int.Parse(dataRange.Text);
                        ++nRowMaxIndex;
                    }
                    catch (Exception e)
                    {
                        throw new System.Exception(e.Message);
                    }
                }

                cSheetData.nRowCount = nRowMaxIndex;
                cSheetData.nColCount = cSheetData.listColData.Count;
                cSheetData.arrCellData = new CellData[cSheetData.nRowCount, cSheetData.nColCount];

                for (int nRow = 0; nRow < nRowMaxIndex; ++nRow)
                {
                    int nIndex = 0;
                    for (int nCol = 0; nCol < cSheetData.nColCount; ++nCol)
                    {
                        if (cSheetData.listColData[nCol].eDataType == EDataType.MAX)
                            continue;

                        Excel.Range dataRange;
                        dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow + 2, nCol));

                        CellData cData = new CellData();
                        cData.SetValue(dataRange.Text, cSheetData.listColData[nCol].eDataType);
                        cSheetData.arrCellData[nRow, nIndex++] = cData;
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CConstData:SetStruct(), {0}, {1}", cSheetData.strName, e.Message));
            }
            return true;
        }
    }
}
