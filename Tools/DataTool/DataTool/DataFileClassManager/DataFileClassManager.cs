using System;
using System.Collections.Generic;
using System.IO;
using DataTool.Global;

namespace DataTool
{
    public partial class DataFileClassManager
    {
        #region Singleton
        private static DataFileClassManager _Instance;
        private static object _lock = new object();

        public static DataFileClassManager Insatance
        {
            get
            {
                lock(_lock)
                {
                    if (_Instance == null)
                        _Instance = new DataFileClassManager();
                }

                return _Instance;
            }
        }

        #endregion Singleton

        private static string   FILENAME_DATA_FILES = "DataFileClass.ini";
        private static string   FILENAME_LZDATA_LANGUAGES = "DataFileLocalization.ini";

        private List<string>    m_listDataFiles = new List<string>();
        private List<string>    m_listLZLanguages = new List<string>();

        private bool            m_bMadeEnum = false;
        private bool            m_bUseConst = false;

        private bool            m_bDirtyCommonFile = false;
        private bool            m_bDirtyDataFile = false;
        private bool            m_bDirtyDataFileBase = false;
        private bool            m_bDirtyLZLanguage = false;        

        private DataFileClassManager()
        {
            LoadDataFiles();
            LoadLZDataLanguage();
        }

        ~DataFileClassManager()
        {
            SaveDataFiles();
        }

        public void SetAllDirty()
        {
            m_bDirtyCommonFile = true;
            m_bDirtyDataFile = true;
            m_bDirtyDataFileBase = true;
            m_bDirtyLZLanguage = true;
        }

        public void ClearFiles()
        {
            DeleteDataFiles();
            DeleteLZDataLanguage();

            m_listDataFiles.Clear();
            m_listLZLanguages.Clear();

            m_bMadeEnum = false;
            m_bUseConst = false;

            m_bDirtyCommonFile = false;
            m_bDirtyDataFile = false;
            m_bDirtyDataFileBase = false;
            m_bDirtyLZLanguage = false;
        }

        public bool IsMadeEnum()
        {
            return m_bMadeEnum;
        }

        public void SetMadeEnum()
        {
            if(!m_bMadeEnum)
            {
                m_bDirtyDataFile = true;
                m_bDirtyDataFileBase = true;
                m_bMadeEnum = true;

                MakeDataCppFiles();
            }
        }
    }
}
