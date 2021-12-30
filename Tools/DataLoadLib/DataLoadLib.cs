using System.Collections.Generic;
using System;
using System.IO;
using System.Text;
using DataLoadLib.Global;
using System.Security.Cryptography;

namespace DataLoadLib
{
    public class DataLoadClass
    {
        private static bool DataLoad(BinaryReader reader, out List<DataInfo[]> listDataInfo, out int nDataFileType)
        {
            bool bRet = true;
            try
            {
                int nRowCount = 0;
                int nColCount = 0;

                nDataFileType = reader.ReadInt32();
                nRowCount = reader.ReadInt32();
                nColCount = reader.ReadInt32();
                
                listDataInfo = new List<DataInfo[]>(nRowCount);

                for (int nRow = 0; nRow < nRowCount; ++nRow)
                {
                    DataInfo[] datas = new DataInfo[nColCount];
                    listDataInfo.Add(datas);
                }

                for (int nCol = 0; nCol < nColCount; ++nCol)
                {
                    EDataType eDataType = (EDataType)reader.ReadInt32();

                    for (int nRow = 0; nRow < nRowCount; ++nRow)
                    {
                        listDataInfo[nRow][nCol].eDataType = eDataType;

                        switch (eDataType)
                        {
                        case EDataType.INT:
                            listDataInfo[nRow][nCol].nValue = reader.ReadInt32();
                            break;
                        case EDataType.FLOAT:
                            listDataInfo[nRow][nCol].fValue = reader.ReadSingle();
                            break;
                        case EDataType.STRING:
                            int size = reader.ReadInt32();
                            byte[] bytes = reader.ReadBytes(size);
                            char[] chars = new char[bytes.Length / sizeof(char)];
                            System.Buffer.BlockCopy(bytes, 0, chars, 0, bytes.Length);
                            listDataInfo[nRow][nCol].strValue = new string(chars).Replace("\\n", "\n");
                            break;
                        case EDataType.LONG:
                            listDataInfo[nRow][nCol].lValue = reader.ReadInt64();
                            break;
                        case EDataType.BOOL:
                            int intBool = reader.ReadInt32();
                            if (intBool == 1)
                            {
                                listDataInfo[nRow][nCol].bValue = true;
                            } 
                            else
                            {
                                listDataInfo[nRow][nCol].bValue = false;
                            }
                            break;
                        default:
                        throw new System.Exception(string.Format("{0}행 {1}열 데이터 타입이 잘못 되었습니다 : {2}\n", nRow, nCol, eDataType));
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
                bRet = false;
                throw new Exception(ex.ToString());
            }

            return bRet;
        }

        private static bool DataLoadWithDebug(BinaryReader reader, out List<DataInfo[]> listDataInfo, out int nDataFileType)
        {
            string strLog = "";
            bool bRet = true;
            try
            {
                int nRowCount = 0;
                int nColCount = 0;

                nDataFileType = reader.ReadInt32();
                nRowCount = reader.ReadInt32();
                nColCount = reader.ReadInt32();

                strLog += nRowCount + ", ";
                strLog += nColCount + ", ";

                listDataInfo = new List<DataInfo[]>(nRowCount);

                for(int nRow = 0 ; nRow < nRowCount ; ++nRow)
                {
                    DataInfo[] datas = new DataInfo[nColCount];
                    listDataInfo.Add(datas);
                }

                for(int nCol = 0 ; nCol < nColCount ; ++nCol)
                {
                    EDataType eDataType = (EDataType)reader.ReadInt32();
                    strLog += eDataType.ToString() + ", ";

                    for(int nRow = 0 ; nRow < nRowCount ; ++nRow)
                    {
                        listDataInfo[nRow][nCol].eDataType = eDataType;

                        switch(eDataType)
                        {
                        case EDataType.INT:
                            listDataInfo[nRow][nCol].nValue = reader.ReadInt32();
                            strLog += listDataInfo[nRow][nCol].nValue.ToString() + ", ";
                            break;
                        case EDataType.FLOAT:
                            listDataInfo[nRow][nCol].fValue = reader.ReadSingle();
                            strLog += listDataInfo[nRow][nCol].fValue.ToString() + ", ";
                            break;
                        case EDataType.STRING:
                            int size = reader.ReadInt32();
                            byte[] bytes = reader.ReadBytes(size);
                            char[] chars = new char[bytes.Length / sizeof(char)];
                            System.Buffer.BlockCopy(bytes, 0, chars, 0, bytes.Length);
                            listDataInfo[nRow][nCol].strValue = new string(chars).Replace("\\n", "\n");

                            strLog += listDataInfo[nRow][nCol].strValue + ", ";
                            break;
                        case EDataType.LONG:
                            listDataInfo[nRow][nCol].lValue = reader.ReadInt64();
                            strLog += listDataInfo[nRow][nCol].lValue.ToString() + ", ";
                            break;
                        case EDataType.BOOL:
                            int intBool = reader.ReadInt32();
                            if (intBool == 1)
                            {
                                listDataInfo[nRow][nCol].bValue = true;
                            }
                            else
                            {
                                listDataInfo[nRow][nCol].bValue = false;
                            }
                            strLog += listDataInfo[nRow][nCol].bValue.ToString() + ", ";
                            break;
                            default:
                            throw new System.Exception(string.Format("{0}행 {1}열 데이터 타입이 잘못 되었습니다 : {2}\n{3}", nRow, nCol, eDataType, strLog));
                        }
                    }
                }
            }
            catch(System.Exception ex)
            {
                bRet = false;
                throw new Exception(strLog);
            }

            return bRet;
        }

        public static bool DataLoadOriginal(Stream stream, out List<DataInfo[]> listDataInfo, out int nDataFileType, bool bDebug = false)
        {
            bool bRet = true;
            
            try
            {
                using(BinaryReader reader = new BinaryReader(stream))
                {
                    if(bDebug)
                        DataLoadWithDebug(reader, out listDataInfo, out nDataFileType);
                    else
                        DataLoad(reader, out listDataInfo, out nDataFileType);
                }
            }
            catch(Exception e)
            {
                bRet = false;
                listDataInfo = new List<DataInfo[]>();
                throw new System.Exception(string.Format("DataLoadOriginal ERROR : {0}", e.Message));
            }

            return bRet;
        }

        public static bool DataLoadDecryptor(Stream stream, out List<DataInfo[]> listDataInfo, out int nDataFileType, string strKey, bool bDebug = false)
        {
            bool bRet = true;

            AesCryptoServiceProvider rc2 = new AesCryptoServiceProvider();
            int nSize = strKey.Length;
            if(nSize != 32)
                throw new System.Exception(string.Format("Key Size ERROR : [{0}]", nSize));                

            rc2.KeySize = 256;
            rc2.Key = ASCIIEncoding.ASCII.GetBytes(strKey);
            rc2.IV = GlobalVariable.SECURE_KEY;
            try
            {
                using(CryptoStream cs = new CryptoStream(stream, rc2.CreateDecryptor(), CryptoStreamMode.Read))
                {
                    try
                    {
                        using(BinaryReader reader = new BinaryReader(cs))
                        {
                            if(bDebug)
                                DataLoadWithDebug(reader, out listDataInfo, out nDataFileType);
                            else
                                DataLoad(reader, out listDataInfo, out nDataFileType);
                        }
                    }
                    catch(Exception e)
                    {
                        bRet = false;
                        listDataInfo = new List<DataInfo[]>();
                        throw new System.Exception(string.Format("Binary Reader ERROR : {0}", e.Message));
                    }
                }
            }
            catch(Exception e)
            {
                bRet = false;
                listDataInfo = new List<DataInfo[]>();
                throw new System.Exception(string.Format("CryptoStream ERROR : {0}", e.Message));
            }

            return bRet;
        }

        public static bool DataLoad(string strFileName, out List<DataInfo[]> listDataInfo, out int nDataFileType, bool bEncrypted = true, string strKey = "")
        {
            bool ret = true;
            
            try
            {
                using (FileStream fs = new FileStream(strFileName, FileMode.Open))
                {
                    if(bEncrypted)
                        return DataLoadDecryptor(fs, out listDataInfo, out nDataFileType, strKey, true);
                    else
                        return DataLoadOriginal(fs, out listDataInfo, out nDataFileType, true);
                }               
            }
            catch (System.Exception ex)
            {
                ret = false;
                listDataInfo = new List<DataInfo[]>();
                throw new System.Exception(string.Format("{0} 파일 {1}", strFileName, ex.Message));
            }
            
            return ret;
        }                   
    }
}
