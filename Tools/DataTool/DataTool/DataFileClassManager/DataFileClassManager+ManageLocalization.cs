using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataTool
{
    public partial class DataFileClassManager
    {
        private void LoadLZDataLanguage()
        {
            try
            {
                if (File.Exists(FILENAME_LZDATA_LANGUAGES))
                {
                    using (StreamReader reader = new StreamReader(FILENAME_LZDATA_LANGUAGES))
                    {
                        while (!reader.EndOfStream)
                        {
                            string strValue = reader.ReadLine();

                            if (m_listLZLanguages.Contains(strValue))
                                continue;

                            m_listLZLanguages.Add(strValue);
                        }
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(e.Message);
            }
        }

        private void SaveLZDataLanguage()
        {
            try
            {
                if (m_bDirtyLZLanguage)
                {
                    using (StreamWriter writer = new StreamWriter(FILENAME_LZDATA_LANGUAGES))
                    {
                        foreach (var value in m_listLZLanguages)
                        {
                            writer.WriteLine(value);
                        }
                    }

                    m_bDirtyLZLanguage = false;
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(e.Message);
            }
        }

        private void DeleteLZDataLanguage()
        {
            try
            {
                if (File.Exists(FILENAME_LZDATA_LANGUAGES))
                {
                    File.Delete(FILENAME_LZDATA_LANGUAGES);
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(e.Message);
            }
        }

        public void SetLZLanguage(List<ColData> listColData, bool bForced = false)
        {
            if (!bForced && m_listLZLanguages.Count == listColData.Count)
                return;

            if(m_listLZLanguages.Count == 0)
                m_bDirtyCommonFile = true;

            m_listLZLanguages.Clear();
            
            for(int i = 0; i < listColData.Count; ++i)
            {
                if (i == 0)
                    m_listLZLanguages.Insert(0, "None");
                else
                    m_listLZLanguages.Add(listColData[i].strExcelColName);
            }

            m_bDirtyLZLanguage = true;
        }
    }   
}
