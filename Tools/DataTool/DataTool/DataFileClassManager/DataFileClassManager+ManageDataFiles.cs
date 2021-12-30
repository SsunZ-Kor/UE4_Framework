using DataTool.Global;
using System;
using System.IO;

namespace DataTool
{
    public partial class DataFileClassManager
    {
        private void LoadDataFiles()
        {
            try
            {
                if (File.Exists(FILENAME_DATA_FILES))
                {
                    using (StreamReader reader = new StreamReader(FILENAME_DATA_FILES))
                    {
                        if(reader.EndOfStream)
                            m_bMadeEnum = false;
                        else
                        {
                            int nValue = int.Parse(reader.ReadLine());
                            m_bMadeEnum = nValue > 0;
                        }
                        
                        while (!reader.EndOfStream)
                        {
                            string strValue = reader.ReadLine();
                            if (strValue == GlobalVar.DATAFILETYPENAME_CONSTDATA)
                                m_bUseConst = true;

                            if (m_listDataFiles.Contains(strValue))
                                continue;

                            m_listDataFiles.Add(strValue);
                        }
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(e.Message);
            }
        }

        private void SaveDataFiles()
        {
            try
            {
                if (m_bDirtyDataFile)
                {
                    using (StreamWriter writer = new StreamWriter(FILENAME_DATA_FILES))
                    {
                        writer.WriteLine(m_bMadeEnum ? "1" : "0");
                        foreach (var value in m_listDataFiles)
                        {
                            writer.WriteLine(value);
                        }
                    }

                    m_bDirtyDataFile = false;
                    m_bDirtyDataFileBase = false;
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(e.Message);
            }
        }

        private void DeleteDataFiles()
        {
            try
            {
                if(File.Exists(FILENAME_DATA_FILES))
                {
                    File.Delete(FILENAME_DATA_FILES);
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(e.Message);
            }
        }

        public bool ExistsDataFile(string strFileName)
        {
            return m_listDataFiles.Contains(strFileName);
        }

        public int GetIndexOrAddDataFile(string strFileName)
        {
            strFileName = GlobalFunctions.MakeCamelString(strFileName);

            if (strFileName == GlobalVar.DATAFILETYPENAME_LOCALIZATION)
                return -1;
                        
            if (strFileName == GlobalVar.DATAFILETYPENAME_CONSTDATA)
            {
                if(!m_bUseConst)
                {
                    m_bUseConst = true;
                    m_bDirtyDataFile = true;
                    m_bDirtyCommonFile = true;

                    if (m_listDataFiles.Contains(strFileName))
                        m_listDataFiles.Remove(strFileName);

                    m_listDataFiles.Insert(0, strFileName);
                }

                return 0;
            }

            if (m_listDataFiles.Contains(strFileName))
            {
                int nCurIndex = m_listDataFiles.IndexOf(strFileName);
                return m_bUseConst ? nCurIndex : nCurIndex + 1;
            }

            m_bDirtyDataFile = true;
            int nCount = m_listDataFiles.Count;
            m_listDataFiles.Add(strFileName);

            if (nCount == 0)
                m_bDirtyCommonFile = true;

            return m_bUseConst ? nCount : nCount + 1;
        }

        public string GetValueDataFile(int nIndex)
        {
            if (nIndex < 0)
                return GlobalVar.DATAFILETYPENAME_LOCALIZATION;

            if (nIndex == 0)
                return GlobalVar.DATAFILETYPENAME_CONSTDATA;

            if(!m_bUseConst)
                --nIndex;

            if (0 <= nIndex || nIndex < m_listDataFiles.Count)
                return m_listDataFiles[nIndex];

            return string.Empty;
        }
    }
}
