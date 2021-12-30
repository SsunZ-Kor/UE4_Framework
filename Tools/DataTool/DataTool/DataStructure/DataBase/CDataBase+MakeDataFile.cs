using DataLoadLib.Global;
using DataTool.Global;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataTool
{
    public partial class CDataBase
    {
        public virtual void MakeClientDataFile(string strDataFileType = "")
        {
            bool bFixDataFileType = !string.IsNullOrEmpty(strDataFileType);

            foreach(var cSheetData in SheetDatas)
            {
                if (cSheetData == null || cSheetData.listColData == null || cSheetData.listColData.Count == 0 || cSheetData.arrCellData == null)
                {
                    throw new System.Exception(string.Format("{0} 시트가 존재 하지 않거나 데이타가 잘못됐습니다.", cSheetData.strName));
                }

                if (CheckTargetCount(cSheetData.listColData, ETargetType.CLIENT) == 0)
                    return;

                string strFilePath = GetFilePath();
                if (!Directory.Exists(strFilePath))
                    Directory.CreateDirectory(strFilePath);

                string strDataFileName = GlobalFunctions.MakeCamelString(cSheetData.strName);

                //string strDataFileType = GlobalFunctions.MakeCamelString(cSheetData.strName);

                string strFileName = string.Format("{0}/{1}{2}", strFilePath, strDataFileName, GlobalVar.DataExtension);
                int nRowCount = cSheetData.nRowCount;
                try
                {
                    using (BinaryWriter writer = new BinaryWriter(File.Open(strFileName, FileMode.Create)))
                    {
                        int nMinusCol = GlobalFunctions.GetTargetExceptionCount(cSheetData.listColData, ETargetType.CLIENT);

                        int nDataFileTypeIndex = DataFileClassManager.Insatance.GetIndexOrAddDataFile(
                            bFixDataFileType ? strDataFileType : strDataFileName);

                        writer.Write(nDataFileTypeIndex);
                        writer.Write(nRowCount);
                        writer.Write(cSheetData.nColCount - nMinusCol);

                        for (int nCol = 0; nCol < cSheetData.nColCount; ++nCol)
                        {
                            if (nCol >= cSheetData.listColData.Count)
                                continue;
                            if (cSheetData.listColData[nCol].eTargetType == ETargetType.SERVER)
                                continue;

                            var eDataType = cSheetData.listColData[nCol].eDataType;
                            var eTargetType = cSheetData.listColData[nCol].eTargetType;

                            writer.Write(eDataType == EDataType.ENUM ? (int)EDataType.INT : (int)eDataType);

                            for (int nRow = 0; nRow < cSheetData.nRowCount; ++nRow)
                            {
                                if (cSheetData.arrCellData[nRow, nCol] == null)
                                {
                                    throw new System.Exception(string.Format("{0} 시트 UID : {1} 컬럼 {2} 행 데이터가 없습니다.",
                                            cSheetData.strName, cSheetData.listColData[nCol].strExcelColName, nRow));
                                }

                                if (string.IsNullOrWhiteSpace(cSheetData.listColData[nCol].strExcelColName))
                                    continue;

                                switch (eDataType)
                                {
                                    case EDataType.INT:
                                    case EDataType.ENUM:
                                        int nValue = cSheetData.arrCellData[nRow, nCol].GetIntValue();
                                        writer.Write(nValue);
                                        break;
                                    case EDataType.FLOAT:
                                        float fValue = cSheetData.arrCellData[nRow, nCol].GetFloatValue();
                                        writer.Write(fValue);
                                        break;
                                    case EDataType.STRING:
                                        int size = cSheetData.arrCellData[nRow, nCol].GetStrValue().Length * sizeof(char);
                                        writer.Write(size);
                                        byte[] bytes = new byte[size];
                                        string strValue = cSheetData.arrCellData[nRow, nCol].GetStrValue();
                                        System.Buffer.BlockCopy(strValue.ToCharArray(), 0, bytes, 0, bytes.Length);

                                        writer.Write(bytes, 0, bytes.Length);
                                        break;
                                    case EDataType.BOOL:
                                        bool bValue = cSheetData.arrCellData[nRow, nCol].GetBoolValue();
                                        writer.Write(bValue ? 1 : 0);
                                        break;
                                    case EDataType.LONG:
                                        long lValue = cSheetData.arrCellData[nRow, nCol].GetLongValue();
                                        writer.Write(lValue);
                                        break;
                                    default:
                                        throw new System.Exception(string.Format("{0} 시트 UID : {1} {2} 컬럼 데이터 타입이 잘못 되었습니다.", cSheetData.strName, cSheetData.arrCellData[nRow, 0].GetIntValue(), cSheetData.listColData[nCol].strExcelColName));
                                }
                            }
                        }

                        writer.Close();
                    }
                }
                catch (Exception e)
                {
                    throw new Exception(e.Message);
                }
            }
        }

        protected int CheckTargetCount(List<ColData> listColData, ETargetType eType)
        {
            if (listColData == null || listColData.Count == 0 || eType == ETargetType.NONE || eType == ETargetType.MAX)
                return 0;

            int nCount = 0;
            for (int i = 0; i < listColData.Count; ++i)
            {
                if (listColData[i].eTargetType == eType || listColData[i].eTargetType == ETargetType.ALL)
                    ++nCount;
            }
            return nCount;
        }

        protected virtual string GetFilePath()
        {
            return GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_DATA);
        }
    }
}
