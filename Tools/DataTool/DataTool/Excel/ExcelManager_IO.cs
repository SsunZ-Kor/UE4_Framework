using DataLoadLib.Global;
using DataTool.Global;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DataTool
{
    partial class ExcelManager
    {
        #region SaveDataFile

        private int CheckTargetCount(List<ColData> listColData, ETargetType eType)
        {
            if(listColData == null || listColData.Count == 0 || eType == ETargetType.NONE || eType == ETargetType.MAX)
                return 0;

            int nCount = 0;
            for(int i = 0 ; i < listColData.Count ; ++i)
            {
                if(listColData[i].eTargetType == eType || listColData[i].eTargetType == ETargetType.ALL)
                    ++nCount;
            }
            return nCount;
        }

        private int GetGroupColIndex(List<ColData> listCol)
        {
            for(int i = 0 ; i < listCol.Count ; ++i)
            {
                if(string.Compare(listCol[i].strExcelColName, "group_id") == 0)
                    return i;
            }

            return -1;
        }

        private void GetGroupValueAndCount(CellData[,] arrCell, int nGroupCol, int nRowCount, ref List<int> listValue, ref List<int> listCount)
        {
            for(int i = 0 ; i < nRowCount ; ++i)
            {
                int nValue = arrCell[i, nGroupCol].GetIntValue();

                if(listValue.Contains(nValue))
                {
                    int nIndex = listValue.IndexOf(nValue);
                    ++listCount[nIndex];
                }
                else
                {
                    listValue.Add(nValue);
                    listCount.Add(1);
                }
            }
        }

        private void SaveServerDataFile(SheetData cSheetData, string strFilePath)
        {
            if(cSheetData == null || cSheetData.listColData == null || cSheetData.listColData.Count == 0 || cSheetData.arrCellData == null)
                throw new System.Exception(string.Format("{0} 시트가 존재 하지 않거나 데이타가 잘못됐습니다.", cSheetData.strName));

            if (cSheetData.listColData[0].eTargetType == ETargetType.CLIENT)
                return;

            if(CheckTargetCount(cSheetData.listColData, ETargetType.SERVER) <= 1)
                return;

                if (!Directory.Exists(strFilePath))
                    Directory.CreateDirectory(strFilePath);

            string strFileName = string.Format("{0}/{1}{2}", strFilePath, cSheetData.strName, GlobalVar.CSVExtention);
            //WriteFileServer(cSheetData, strFileName);
            InsertFileDataToDb(cSheetData);
        }

        private void InsertFileDataToDb(SheetData cSheetData)
        {
            try
            {
                DBManager dbManager = new DBManager(GlobalVar.serverName);

                if (GlobalVar.serverName == "none")
                    return;

                dbManager.GetConnection().Open();

                //  테이블이 없으면 생성
                dbManager.CreateTable(cSheetData);

                // 테이블 비우기
                dbManager.DeleteData(cSheetData);

                dbManager.InsertData(cSheetData);

                dbManager.GetConnection().Close();
            }
            catch (Exception e)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke(string.Format("InsertFileDataToDb() {0}", e.Message));
            }
        }

        private void WriteFileServer(SheetData cSheetData, string strFileName)
        {
            StringBuilder sb = new StringBuilder();
            try
            {
                using(StreamWriter writer = new StreamWriter(File.Open(strFileName, FileMode.Create), new UTF8Encoding(false)))
                {
                    var listCollData = cSheetData.listColData;

                    for(int i = 0 ; i < listCollData.Count ; ++i)
                    {
                        if(listCollData[i].eTargetType == ETargetType.CLIENT || listCollData[i].eTargetType == ETargetType.NONE || listCollData[i].eTargetType == ETargetType.MAX)
                            continue;

                        if(i != 0)
                            sb.Append('\t');

                        sb.Append(listCollData[i].strExcelColName);
                    }

                    sb.Append("\r\n");

                    for(int nRow = 0 ; nRow < cSheetData.nRowCount ; ++nRow)
                    {
                        for(int nCol = 0 ; nCol < cSheetData.nColCount ; ++nCol)
                        {
                            if(cSheetData.arrCellData[nRow, nCol] == null)
                            {
                                //continue;
                                throw new System.Exception(string.Format("{0} 시트 UID : {1} {2} 컬럼 데이터 타입이 잘못 되었습니다.",
                                    cSheetData.strName, cSheetData.arrCellData[nRow, 0].GetIntValue(), cSheetData.listColData[nCol].strExcelColName));
                            }

                            if(listCollData[nCol].eTargetType == ETargetType.CLIENT || listCollData[nCol].eTargetType == ETargetType.NONE || listCollData[nCol].eTargetType == ETargetType.MAX)
                                continue;

                            if(nCol != 0)
                                sb.Append('\t');

                            switch(listCollData[nCol].eDataType)
                            {
                            case EDataType.INT:
                            case EDataType.ENUM:
                                sb.Append(cSheetData.arrCellData[nRow, nCol].GetIntValue());
                                break;
                            case EDataType.FLOAT:
                                sb.Append(cSheetData.arrCellData[nRow, nCol].GetFloatValue());
                                break;
                            case EDataType.STRING:
                                sb.Append(cSheetData.arrCellData[nRow, nCol].GetStrValue());
                                break;

                            default:
                                throw new System.Exception(string.Format("{0} 시트 UID : {1} {2} 컬럼 데이터 타입이 잘못 되었습니다.", cSheetData.strName, cSheetData.arrCellData[nRow, 0].GetIntValue(), cSheetData.listColData[nCol].strExcelColName));
                            }
                        }
                        sb.Append("\r\n");
                    }

                    writer.Write(sb.ToString());

                    writer.Close();
                }
            }
            catch(Exception e)
            {
                throw new System.Exception(string.Format("{0} 시트 쓰기에 실패했습니다. 이유 : {1}.", cSheetData.strName, e.Message));
            }
        }

        #endregion SaveDataFile
    }
}
