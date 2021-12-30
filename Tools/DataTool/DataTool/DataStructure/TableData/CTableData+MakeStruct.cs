using DataLoadLib.Global;
using DataTool.Global;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Excel = Microsoft.Office.Interop.Excel;

namespace DataTool
{
    public partial class CTableData
    {

        protected override bool SetStruct(Excel.Worksheet sheet, ref SheetData cSheetData, Excel.Range range)
        {
            try
            {
                if (range.Row < 4)
                {
                    cSheetData.nRowCount = 0;
                    cSheetData.nColCount = 0;
                    cSheetData.listColData.Clear();
                    cSheetData.arrCellData = null;

                    return false;
                }

                int nCollMaxIndex = 0;

                List<string> listTypeName = new List<string>();
                List<int> listSkipIndex = new List<int>();

                // 참조 테이블 정보 가져오기
                for (int nColl = 0; nColl < range.Column; ++nColl)
                {
                    Excel.Range dataRange = sheet.get_Range(GlobalFunctions.GetCellName(3, nColl));
                    if (string.IsNullOrEmpty(dataRange.Text))
                    {
                        Excel.Range tempDataRange = sheet.get_Range(GlobalFunctions.GetCellName(3, nColl + 1));
                        if (!string.IsNullOrEmpty(tempDataRange.Text))
                        {
                            throw new System.Exception(string.Format("{0} - col: {1} row: {2} {3}에 오류가 있습니다.",
                                        sheet.Name, nColl, 3, dataRange.Text));
                        }

                        nCollMaxIndex = nColl;
                        break;
                    }
                    EDataType eType = GlobalFunctions.GetDataType(dataRange.Text);

                    if (eType == EDataType.MAX)
                    {
                        throw new System.Exception(string.Format("{0} - col: {1} row: {2} {3}에 오류가 있습니다.",
                                        sheet.Name, nColl, 3, dataRange.Text));
                    }

                    if (eType == EDataType.NONE)
                    {
                        listSkipIndex.Add(nColl);
                        continue;
                    }

                    Excel.Range targetRange = sheet.get_Range(GlobalFunctions.GetCellName(2, nColl));
                    ETargetType eTargetType = GlobalFunctions.GetTargetType(targetRange.Text);

                    if (eTargetType == ETargetType.NONE || eTargetType == ETargetType.MAX)
                    {
                        listSkipIndex.Add(nColl);
                        continue;
                    }

                    ColData cData = new ColData();

                    cData.strTypeName = eType == EDataType.ENUM ? dataRange.Text : string.Empty;
                    if (!string.IsNullOrEmpty(cData.strTypeName) && !listTypeName.Contains(cData.strTypeName))
                        listTypeName.Add(cData.strTypeName);

                    cData.eTargetType = eTargetType;

                    Excel.Range nameRange = sheet.get_Range(GlobalFunctions.GetCellName(1, nColl));
                    cData.strExcelColName = nameRange.Text;
                    cData.nColIndex = nColl;
                    cData.eDataType = eType;

                    if (nameRange.Comment != null)
                        cData.strMemo = nameRange.Comment.Text().Replace("\n", " ");

                    cSheetData.listColData.Add(cData);
                }

                int nRowMaxIndex = 0;

                for (int nRow = 4; nRow <= range.Row; ++nRow)
                {
                    Excel.Range dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow, 0));
                    string strIndex = dataRange.Text;
                    if (string.IsNullOrEmpty(strIndex))
                        break;

                    try
                    {
                        int nValue = int.Parse(strIndex);
                    }
                    catch
                    {
                        break;
                    }

                    ++nRowMaxIndex;
                }

                if (nCollMaxIndex == 0)
                    nCollMaxIndex = range.Column;

                cSheetData.nRowCount = nRowMaxIndex;
                cSheetData.nColCount = nCollMaxIndex - listSkipIndex.Count;
                cSheetData.arrCellData = new CellData[cSheetData.nRowCount, cSheetData.nColCount];

                if (listTypeName.Count > 0)
                {
                    for (int i = 0; i < listTypeName.Count; ++i)
                    {
                        if (m_cMgr.GetTypeData(listTypeName[i]) == null)
                            m_cMgr.SetTypeData(listTypeName[i]);
                    }
                }

                for (int nRow = 0; nRow < nRowMaxIndex; ++nRow)
                {
                    int nIndex = 0;

                    for (int nCol = 0; nCol < nCollMaxIndex; ++nCol)
                    {
                        if (listSkipIndex.Contains(nCol))
                            continue;

                        var cColData = cSheetData.listColData[nIndex];

                        Excel.Range dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow + 4, nCol));
                        CellData cData = new CellData();

                        int nID = 0;

                        if (cColData.eDataType == EDataType.ENUM)
                        {
                            string strData = dataRange.Text;
                            strData = strData.Trim();

                            if (string.IsNullOrWhiteSpace(strData))
                            {
                                cData.SetValue("0".ToString(), EDataType.INT);
                                cSheetData.arrCellData[nRow, nIndex++] = cData;
                            }
                            else
                            {
                                var cTypeData = m_cMgr.GetTypeData(cColData.strTypeName);
                                if (cTypeData == null || cTypeData.SheetDatas == null ||
                                    cTypeData.SheetDatas.Count == 0 || cTypeData.SheetDatas[0] == null)
                                {
                                    throw new System.Exception(string.Format("{0} - {1}에 오류가 있습니다.",
                                        sheet.Name, cColData.strTypeName));
                                }

                                var cTypeSheet = cTypeData.SheetDatas[0];
                                bool isFound = false;

                                for (int nType = 0; nType < cTypeSheet.nRowCount; ++nType)
                                {
                                    if (cTypeSheet.arrCellData[nType, 1] == null)
                                        break;

                                    if (string.Compare(strData, cTypeSheet.arrCellData[nType, 1].GetStrValue()) == 0)
                                    {
                                        cData.SetValue(cTypeSheet.arrCellData[nType, 0].GetIntValue().ToString(), EDataType.INT);
                                        cSheetData.arrCellData[nRow, nIndex++] = cData;

                                        isFound = true;
                                        break;
                                    }
                                }

                                if (!isFound)
                                {
                                    throw new System.Exception(string.Format("{0} - col: {1} row: {2} {3}에 오류가 있습니다.",
                                        sheet.Name, nIndex, nRow, strData));
                                }
                            }
                        }
                        else
                        {
                            cData.SetValue(dataRange.Text, cColData.eDataType);
                            cSheetData.arrCellData[nRow, nIndex++] = cData;

                            if (nCol == 0)
                                nID = int.Parse(dataRange.Text);
                        }
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CTableData:SetStruct() , {0} ", e.Message));
            }

            return true;
        }
    }
}
