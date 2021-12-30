using System;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DataTool.Global;
using System.Diagnostics;
using System.Collections.Generic;
using System.Threading;
using System.IO;

namespace DataTool
{
    public partial class dataTool : Form
    {
        private ExcelManager    m_excelManger = null;

        //TODO : 쓰레드 관련 정리할 때 풀로 관리하기
        private bool m_bAddEnumJob = false;

        public dataTool()
        {
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            GlobalFunctions.LoadSettingFiles();
            m_excelManger = new ExcelManager(this, OnProgressChange, OnLoadingEnd, OnStatusChange, OnShowMessageBox);

            //this.ServerNameComboBox.SelectedIndex = 0;

            SetWaitState();

            Text = Application.StartupPath + " - 데이터 툴";
        }

        #region Action Activator

        private void SetAllActionDisable()
        {
            SetSelectBtnsEnable(false);
            SetTopBtnsEnable(false);
            SetFunctionBtnsEnable(false);
            SetExcelDataBtnsEnable(false);

            //this.ServerNameComboBox.Enabled = false;
        }

        private void SetAllActionEable()
        {
            SetSelectBtnsEnable(true);
            SetTopBtnsEnable(true);
            SetFunctionBtnsEnable(true);
            SetExcelDataBtnsEnable(true);

            //this.ServerNameComboBox.Enabled = true;
        }

        private void SetWaitState()
        {
            SetSelectBtnsEnable(false);
            SetTopBtnsEnable(true);
            SetFunctionBtnsEnable(true);
            SetExcelDataBtnsEnable(false);

            //this.ServerNameComboBox.Enabled = true;

            this.LabelStatusLine.Text = string.Empty;
        }

        public void SetSelectBtnsEnable(bool bEnable)
        {
            //this.BtnSelectAll.Enabled = bEnable;
            //this.BtnUnSelectAll.Enabled = bEnable;
        }

        private void SetTopBtnsEnable(bool bEnable)
        {
            this.BtnLoadAndBuildExcelFile.Enabled = bEnable;
            this.BtnLoadDataFile.Enabled = bEnable;
            this.BtnLoadLZDataFile.Enabled = bEnable;
            //this.BtnLoadExcelGroupFile.Enabled = bEnable;
        }

        private void SetFunctionBtnsEnable(bool bEnable)
        {
            //this.BtnDoAll.Enabled = bEnable;
            this.BtnMakeProtoEnum.Enabled = bEnable;
            this.BtnConstData.Enabled = bEnable;
            //this.BtnLocalization.Enabled = bEnable;
            //this.BtnSystemLocalization.Enabled = bEnable;
            this.BtnLzSingle.Enabled = bEnable;
            //this.BtnProtocolData.Enabled = bEnable;
            this.BtnDoData.Enabled = bEnable;
            this.DeleteAllData.Enabled = bEnable;
            this.allContentsLZ.Enabled = bEnable;
            this.BtnAll.Enabled = bEnable;            
        }

        private void SetExcelDataBtnsEnable(bool bEnable)
        {
            //this.BtnExportServer.Enabled = bEnable;
            //this.BtnExportClient.Enabled = bEnable;
        }

        #endregion Action Activator

        #region Buttons

        //private void OnClickSelectAll(object sender, EventArgs e)
        //{
        //    m_excelManger.SelectAll(true);
        //}

        //private void OnClickUnSelectAll(object sender, EventArgs e)
        //{
        //    m_excelManger.SelectAll(false);
        //}

        //private void OnClickExportClient(object sender, EventArgs e)
        //{
        //    int excelTableFileCount = m_excelManger.m_dicTableData.Count * 2;            
        //    InitProgressBar(excelTableFileCount);

        //    new Thread(() =>
        //    {
        //        m_excelManger.SaveTableDataFile(true, ETargetType.CLIENT);
        //        m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB);
        //    }).Start();
            
        //}

        //private void OnClickExportServer(object sender, EventArgs e)
        //{
        //    int excelTableFileCount = m_excelManger.m_dicTableData.Count * 2;
        //    InitProgressBar(excelTableFileCount);

        //    new Thread(() =>
        //    {
        //        m_excelManger.SaveTableDataFile(true, ETargetType.SERVER);
        //        m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB);
        //    }).Start();
        //}

        private void OnClickLoadExcelFile(object sender, EventArgs e)
        {
            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_DATA);
            if(nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, GlobalVar.PATH_EXCEL_DATA));
                return;
            }

            InitProgressBar();

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Excel File(*.xlsx)|*.xlsx";
            dlg.InitialDirectory = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_DATA);
            if(dlg.ShowDialog() == DialogResult.OK)
            {
                SetStatusText(string.Format(GlobalVar.FMT_LOADING_FILE, dlg.FileName));

                m_excelManger.ClearCheckBox();

                m_excelManger.SetTableData(dlg.FileName, EExcelType.TABLE);

                SetStatusText(string.Format(GlobalVar.FMT_LOADEND_FILE, dlg.FileName));

                if(!string.IsNullOrEmpty(dlg.FileName))
                {
                    SetSelectBtnsEnable(true);
                    SetExcelDataBtnsEnable(true);
                }

                m_excelManger.SaveTableDataFile(dlg.FileName, ETargetType.CLIENT);
            }

            if (m_bAddEnumJob)
                m_excelManger.SetStatusText("Enum File을 체크하고 있습니다.");
            else
            {
                if(string.IsNullOrEmpty(dlg.FileName))
                    SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load And Build Single Excel] : Cancel");
                else
                    SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load And Build Single Excel] : " + dlg.FileName);

                GC.Collect();
            }
        }


        //private void OnClickLoadGroupFile(object sender, EventArgs e)
        //{
        //    InitProgressBar();

        //    OpenFileDialog dlg = new OpenFileDialog();
        //    dlg.Filter = "Excel File(*.xlsx)|*.xlsx";
        //    dlg.InitialDirectory = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_GROUP_DATA);
        //    if (dlg.ShowDialog() == DialogResult.OK)
        //    {
        //        SetStatusText(string.Format(GlobalVar.FMT_LOADING_FILE, dlg.FileName));

        //        m_excelManger.m_dicTableData.Clear();                

        //        m_excelManger.ClearCheckBox();

        //        m_excelManger.SetTableData(dlg.FileName, EExcelType.GROUP);

        //        SetStatusText(string.Format(GlobalVar.FMT_LOADEND_FILE, dlg.FileName));

        //        if (!string.IsNullOrEmpty(dlg.FileName))
        //        {
        //            SetSelectBtnsEnable(true);
        //            SetExcelDataBtnsEnable(true);
        //        }
        //    }

        //    //if(m_bAddJob)
        //    //    m_excelManger.SetStatusText("Enum File을 체크하고 있습니다.");
        //    //else
        //        m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB);
        //}

        private void OnClickLoadDataFile(object sender, EventArgs e)
        {
            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_CLIENT_DATA);
            if (nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, GlobalVar.PATH_CLIENT_DATA));
                return;
            }

            InitProgressBar();

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.InitialDirectory = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_DATA);
            dlg.Filter = string.Format("Data File(*{0})|*{0}", GlobalVar.DataExtension);

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                SetStatusText(string.Format(GlobalVar.FMT_LOADING_FILE, dlg.FileName));

                m_excelManger.LoadDataFile(dlg.FileName);

                SetStatusText(string.Format(GlobalVar.FMT_LOADEND_FILE, dlg.FileName));
            }

            if (string.IsNullOrEmpty(dlg.FileName))
                SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load Single Data] : Cancel");
            else
                SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load Single Data] : " + dlg.FileName);

            GC.Collect();
        }

        private void OnClickLoadLZDataFile(object sender, EventArgs e)
        {
            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_CLIENT_LOCALIZATION);
            if (nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, GlobalVar.PATH_CLIENT_LOCALIZATION));
                return;
            }

            InitProgressBar();

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.InitialDirectory = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_LOCALIZATION);
            dlg.Filter = string.Format("Data File(*{0})|*{0}", GlobalVar.DataExtension);

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                SetStatusText(string.Format(GlobalVar.FMT_LOADING_FILE, dlg.FileName));

                m_excelManger.LoadDataFile(dlg.FileName);

                SetStatusText(string.Format(GlobalVar.FMT_LOADEND_FILE, dlg.FileName));
            }

            if (string.IsNullOrEmpty(dlg.FileName))
                SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load Single LZ Data] : Cancel");
            else
                SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load Single LZ Data] : " + dlg.FileName);

            GC.Collect();
        }

        private void OnClickMakeEnum(object sender, EventArgs e)
        {
            MakeAllEnum();
        }

        public void SetAddEnumJob(string strPrevFileName)
        {
            m_bAddEnumJob = true;
            MakeAllEnum(strPrevFileName);
        }

        private void MakeAllEnum(string strPrevFileName = "")
        {
            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_ENUM_DATA);
            if(nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, GlobalVar.PATH_EXCEL_ENUM_DATA));
                m_bAddEnumJob = false;
                return;
            }

            InitProgressBar(nCount);

            new Thread(() =>
            {
                m_excelManger.SetAllTypeData();
                m_excelManger.WriteAllTypeData();


                if (m_bAddEnumJob)
                {
                    m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load And Build Single Excel] : " + strPrevFileName + " [Make Enum]");
                    m_bAddEnumJob = false;
                }
                else
                    m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Make Enum]");

                GC.Collect();
            }).Start();
        }

        private void OnClickConstDataFile(object sender, EventArgs e)
        {
            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_CONST_DATA);

            if(nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, GlobalVar.PATH_EXCEL_CONST_DATA));
                return;
            }

            InitProgressBar(nCount);

            new Thread(() =>
            {
                m_excelManger.DoAllConstData();

                m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [ConstData]");

                GC.Collect();
            }).Start();
        }

        private void OnClickDataAll(object sender, EventArgs e)
        {
            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_DATA);
            nCount += GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_ENUM_DATA);
            nCount += GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_CONST_DATA);

            //int excelGroupFileCount = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_GROUP_DATA)).Length * 2;

            if (nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, "ExcelData, EnumData, ConstData 중 아무 것도 없습니다."));
                return;
            }

            //InitProgressBar(excelEnumFileProgressCount + excelGroupFileCount + excelTableFileCount);
            InitProgressBar(nCount);

            new Thread(() =>
            {
                m_excelManger.DoAllExcelTableFiles();
                m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [All Data Build] : [Make Enum], [Load And Build Excels], [ConstData]");

                GC.Collect();
            }).Start();
        }

        
        //private void BtnProtocolData_Click(object sender, EventArgs e)
        //{
        //    int excelFileProgressCount = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_PROTOCOL_DATA)).Length * 4;

        //    InitProgressBar(excelFileProgressCount);

        //    new Thread(() =>
        //    {                
        //        m_excelManger.DoAllProtocolData();

        //        m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB);
        //    }).Start();
        //}

        //private void OnClickLzSystem(object sender, EventArgs e)
        //{
        //    int excelFileProgressCount = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_SYS_LOCAL_DATA)).Length;

        //    InitProgressBar(excelFileProgressCount*2);

        //    new Thread(() =>
        //    {
        //        m_excelManger.DoSystemLocalizationData();

        //        m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB);
        //    }).Start();            
        //}

        private void OnClickLzSingle(object sender, EventArgs e)
        {
            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_LOCAL_DATA, true);
            if (nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, GlobalVar.PATH_EXCEL_LOCAL_DATA));
                return;
            }

            InitProgressBar();

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Excel File(*.xlsx)|*.xlsx";
            dlg.InitialDirectory = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_LOCAL_DATA);
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                SetStatusText(string.Format(GlobalVar.FMT_LOADING_FILE, dlg.FileName));

                //m_excelManger.SetLocalizationData(dlg.FileName);
                m_excelManger.WriteLocalizationData(dlg.FileName);
            }

            if (string.IsNullOrEmpty(dlg.FileName))
                SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load And Build Single LZ] : Cancel");
            else
                SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Load And Build Single LZ] : " + dlg.FileName);

            GC.Collect();
        }

        //private void OnClickLocalizationFile(object sender, EventArgs e)
        //{
        //    int excelLocalizationFileProgressCount = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_LOCAL_DATA)).Length * 3;
        //    int excelSystemLocalizationFileProgressCount = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_SYS_LOCAL_DATA)).Length * 3;
            
        //    InitProgressBar(excelLocalizationFileProgressCount + excelSystemLocalizationFileProgressCount);

        //    new Thread(() =>
        //    {
        //        m_excelManger.DoAllLocalizationData();
        //        m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB);
        //    }).Start();
        //}

        private void OnClickAllContentsLZ(object sender, EventArgs e)
        {
            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_LOCAL_DATA, true);
            if (nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, GlobalVar.PATH_EXCEL_LOCAL_DATA));
                return;
            }

            InitProgressBar(nCount);

            new Thread(() =>
            {
                m_excelManger.DoLocalizationData();
                m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [ALL LZ Build]");

                GC.Collect();
            }).Start();
        }

        private void OnClickDeleteAllData(object sender, EventArgs e)
        {
            InitProgressBar();

            m_excelManger.DeleteAllDataDirectory(true);
            SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Clear All Data And Script]");

            GC.Collect();
        }

        private void OnClickDoAll(object sender, EventArgs e)
        {
            m_excelManger.DeleteAllDataDirectory();

            int nCount = GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_DATA);
            nCount += GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_ENUM_DATA);
            nCount += GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_CONST_DATA);
            nCount += GetInDirectoryFileCount(GlobalVar.PATH_EXCEL_LOCAL_DATA, true);
            //int excelLocalizationFileProgressCount = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_LOCAL_DATA)).Length * 3;
            //int excelSystemLocalizationFileProgressCount = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_SYS_LOCAL_DATA)).Length * 3;
            //int excelProtoFileProgressCount = Directory.GetFiles(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_EXCEL_PROTOCOL_DATA)).Length * 4;

            if (nCount == 0)
            {
                SetStatusText(string.Format(GlobalVar.FMT_NO_SETTING_FILE, "ExcelData, EnumData, ConstData, LocalizationData 중 아무 것도 없습니다."));
                return;
            }

            InitProgressBar(nCount);

            new Thread(() =>
            {
                //m_excelManger.DoAllProtocolData();
                m_excelManger.DoAllExcelTableFiles();
                m_excelManger.DoAllLocalizationData();

                m_excelManger.SetStatusText(GlobalVar.TXT_END_ALL_JOB + " [Build ALL]");

                GC.Collect();
            }).Start();
        }

        #endregion Buttons 

        private int GetInDirectoryFileCount(string strRelativePath, bool bLZData = false)
        {
            string strAbsolutePath = GlobalFunctions.MakeAbsolutePath(strRelativePath);

            if (Directory.Exists(strAbsolutePath))
                return bLZData ? Directory.GetFiles(strAbsolutePath).Length * 3 : Directory.GetFiles(strAbsolutePath).Length * 2;

            return 0;
        }

        private void InitProgressBar(int max)
        {
            progressBar1.Value = 0;
            progressBar1.Minimum = 0;
            progressBar1.Maximum = max;

            SetAllActionDisable();
        }

        private void InitProgressBar()
        {
            progressBar1.Value = 0;
            progressBar1.Minimum = 0;
            progressBar1.Maximum = 9999;

            SetAllActionDisable();
        }

        public void SetStatusText(string strText)
        {
            this.LabelStatusLine.Text = strText;
            if (strText.Contains(GlobalVar.TXT_END_ALL_JOB))
            {
                this.progressBar1.Value = this.progressBar1.Maximum;
                SetAllActionEable();
            }
        }
        
        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosing(e);            
        }

        public void AddProgressCount()
        {
            if (this.LabelStatusLine.Text == GlobalVar.TXT_END_ALL_JOB)
            {
                return;
            }
            if(this.progressBar1.Value + 1 < this.progressBar1.Maximum)
                this.progressBar1.Value++;
        }


        private void OnStatusChange(string strMsg) => this.Invoke((Action)(() => SetStatusText(strMsg)));
        private void OnProgressChange() => this.Invoke((Action)(() => AddProgressCount()));
        private void OnLoadingEnd(string strFullFileName) => this.Invoke((Action)(() => CallbackLoading(strFullFileName)));
        private void OnShowMessageBox(string message) => this.Invoke((Action)(() => ShowMessageBox(message)));

        private void CallbackLoading(string strFullFileName)
        {
            var cLoadedExcel = m_excelManger.GetTableData(strFullFileName);

            if(cLoadedExcel.Type == EExcelType.MAX)
                return;            

            for (int i = 0 ; i < cLoadedExcel.SheetDatas.Count ; ++i)
            {
                var cSheetData = cLoadedExcel.SheetDatas[i];
                if(cSheetData == null || cSheetData.arrCellData == null || string.IsNullOrEmpty(cSheetData.strName))
                    continue;

                CheckBox cCheckBox = new CheckBox
                {
                    Location = new Point(20, 5 + (25 * i)),
                    Text = cSheetData.strName,
                    AutoSize = true,
                    Checked = true
                };
                //SheetPanel.Controls.Add(cCheckBox);
                m_excelManger.AddCheckBox(cCheckBox);
            }
        }

        private void ShowMessageBox(string message)
        {
            MessageBox.Show(message);
        }

        //private void ServerNameComboBox_SelectedIndexChanged(object sender, EventArgs e)
        //{
        //    GlobalVar.serverName = ServerNameComboBox.SelectedItem as string;
        //}






    }
}
