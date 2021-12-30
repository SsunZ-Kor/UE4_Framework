using System.Collections.Generic;
using System.Windows.Forms;
using System;
using System.IO;
using DataTool.Global;
using DataLoadLib.Global;

namespace DataTool
{
    public partial class ExcelManager
    {
        private dataTool            m_parent = null;

        //private Action<string> m_onStatusChange = null;
        //private Action<string> m_onLoadEnd = null;
        //private Action<string> m_onShowMessageBox = null;
        //private Action m_onProgressChange = null;

        //Key : full file name
        public Dictionary<string, CTypeData> m_dicTypeData { get; private set; } = new Dictionary<string, CTypeData>();
        //Key : full file name
        public Dictionary<string, CTableData> m_dicTableData { get; private set; } = new Dictionary<string, CTableData>();
        //Key : full file name
        public Dictionary<string, CConstData> m_dicConstData { get; private set; } = new Dictionary<string, CConstData>();
        public Dictionary<string, CLocalizationData> m_dicLocalizationData { get; private set; } = new Dictionary<string, CLocalizationData>();        
        public Dictionary<string, CProtocolData> m_dicProtocolData { get; private set; } = new Dictionary<string, CProtocolData>();

        //Key : full file name
        private Dictionary<string, List<CheckBox>> m_dicCheckBoxList = new Dictionary<string, List<CheckBox>>();

        private DataFileClassManager m_cFileMgr = null;
        private EventHandler m_cEvtHandler = null;

        public ExcelManager(dataTool parent, Action onProgressChange, Action<string> onLoadEnd, Action<string> onStatusChange, Action<string> onShowMessageBox)
        {
            m_parent = parent;

            //m_onStatusChange = onStatusChange;
            //m_onProgressChange = onProgressChange;
            //m_onLoadEnd = onLoadEnd;
            //m_onShowMessageBox = onShowMessageBox;

            m_cFileMgr = DataFileClassManager.Insatance;

            m_cEvtHandler = new EventHandler();
            m_cEvtHandler.ChangeProgress = onProgressChange;
            m_cEvtHandler.LoadEnd = onLoadEnd;
            m_cEvtHandler.ChangeStatus = onStatusChange;
            m_cEvtHandler.ShowMessageBox = onShowMessageBox;
        }        
        

        public void AddCheckBox(CheckBox checkBox)
        {
            if (!m_dicCheckBoxList.ContainsKey(checkBox.Text))
            {
                List<CheckBox> checkBoxeList = new List<CheckBox>();
                checkBoxeList.Add(checkBox);
                m_dicCheckBoxList.Add(checkBox.Text, checkBoxeList);
            }

        }        

        #region Load Data File
        public string LoadDataFile(string fileName)
        {
            //#if !DEBUG
            try
            //#endif
            {
                List<DataInfo[]> listDataInfo = null;
                int nDataFileType = 0;
                if(DataLoadLib.DataLoadClass.DataLoad(fileName, out listDataInfo, out nDataFileType, false, GlobalVar.EncKey) == true)
                {
                    MessageBox.Show("데이터 파일을 불러왔습니다");
                    //DrawDataGrid(listDataInfo, Path.GetFileNameWithoutExtension(fileName), nDataFileType);
                    DrawDataGrid(listDataInfo, fileName, nDataFileType);

                    return fileName;
                }
            }
            //#if !DEBUG
            catch(System.Exception ex)
            {
                MessageBox.Show(string.Format("데이터 파일 불러오기 실패 이유 : {0}", ex.Message));
            }
            //#endif
            return string.Empty;
        }

        private void DrawDataGrid(List<DataInfo[]> listDataInfo, string strFileName, int nDataFileType)
        {
            if(listDataInfo == null)
                return;

            ExportMenu export_menu = new ExportMenu(listDataInfo, strFileName, m_cFileMgr.GetValueDataFile(nDataFileType));
            export_menu.ShowDialog();
        }
        
        #endregion Load Data File


        public void SelectAll(bool check)
        {
            foreach(List<CheckBox> checkBoxes in m_dicCheckBoxList.Values)
            {
                foreach(CheckBox checkBox in checkBoxes)
                {
                    checkBox.Checked = check;
                }
            }

        }

        public void ClearCheckBox()
        {
            //foreach (List<CheckBox> checkBoxes in m_dicCheckBoxList.Values)
            //{
            //    foreach (CheckBox checkBox in checkBoxes)
            //    {
            //        m_parent.SheetPanel.Controls.Remove(checkBox);
            //    }
            //    checkBoxes.Clear();
            //}
            m_dicCheckBoxList.Clear();
        }

        public void DeleteAllDataDirectory(bool bClearSettingFiles = false)
        {
            DeleteDirectory(GlobalVar.PATH_CLIENT_DATA);
            DeleteDirectory(GlobalVar.PATH_CLIENT_LOCALIZATION);
            DeleteDirectory(GlobalVar.PATH_CLIENT_CPP_CLASS_ROOT);

            if (bClearSettingFiles)
                m_cFileMgr.ClearFiles();
            else
                m_cFileMgr.SetAllDirty();
        }

        private void DeleteDirectory(string path)
        {
            string relativePath = GlobalFunctions.MakeAbsolutePath(path);

            if (Directory.Exists(relativePath))
                Directory.Delete(relativePath, true);

            m_cEvtHandler.ChangeProgress?.Invoke();
        }

        public void SetStatusText(string strText)
        {
            m_cEvtHandler.ChangeStatus?.Invoke(strText);
        }
    }

}
