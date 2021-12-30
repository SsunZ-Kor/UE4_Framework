using System;
using System.Collections.Generic;
using DataTool.Global;
using DataLoadLib.Global;
using Excel = Microsoft.Office.Interop.Excel;

namespace DataTool
{
    public partial class CLocalizationData
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

                List<int> listSkipIndex = new List<int>();

                // 참조 테이블 정보 가져오기
                for (int nColl = 0; nColl < range.Column; ++nColl)
                {
                    Excel.Range dataRange;
                    dataRange = sheet.get_Range(GlobalFunctions.GetCellName(1, nColl));

                    string strExcelColName = dataRange.Text;

                    if (GlobalFunctions.IsSkipColumn(strExcelColName))
                    {
                        listSkipIndex.Add(nColl);
                        continue;
                    }

                    ColData cData = new ColData();
                    cData.strExcelColName = strExcelColName;
                    cData.strTypeName = string.Empty;
                    cData.nColIndex = nColl;
                    cData.eTargetType = ETargetType.CLIENT;
                    cData.eDataType = EDataType.STRING;

                    cSheetData.listColData.Add(cData);
                }

                int nRowMaxIndex = 0;
                for (int nRow = 2; nRow <= range.Row; ++nRow)
                {
                    Excel.Range dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow, 0));
                    string strIndex = dataRange.Text;
                    if (string.IsNullOrEmpty(strIndex))
                        break;

                    ++nRowMaxIndex;
                }

                cSheetData.nRowCount = nRowMaxIndex;
                cSheetData.nColCount = range.Column - listSkipIndex.Count;
                cSheetData.arrCellData = new CellData[cSheetData.nRowCount, cSheetData.nColCount];

                for (int nRow = 0; nRow < nRowMaxIndex; ++nRow)
                {
                    int nIndex = 0;
                    for (int nCol = 0; nCol < range.Column; ++nCol)
                    {
                        if (listSkipIndex.Contains(nCol))
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
                m_cEvtHandler?.ShowMessageBox?.Invoke(e.Message);
            }

            if(cSheetData != null && cSheetData.listColData != null)
            {
                DataFileClassManager.Insatance.SetLZLanguage(cSheetData.listColData);
            }

            return true;
        }
    }
}