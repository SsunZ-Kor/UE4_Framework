namespace DataTool
{
    partial class dataTool2
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.LabelStatusLine = new System.Windows.Forms.Label();
            this.SheetGroup = new System.Windows.Forms.GroupBox();
            this.SheetPanel = new System.Windows.Forms.Panel();
            this.BtnSelectAll = new System.Windows.Forms.Button();
            this.BtnExportClient = new System.Windows.Forms.Button();
            this.BtnUnSelectAll = new System.Windows.Forms.Button();
            this.BtnDoAll = new System.Windows.Forms.Button();
            this.BtnMakeProtoEnum = new System.Windows.Forms.Button();
            this.BtnLoadExcelFile = new System.Windows.Forms.Button();
            this.BtnLoadDataFile = new System.Windows.Forms.Button();
            this.BtnExportServer = new System.Windows.Forms.Button();
            this.BtnConstData = new System.Windows.Forms.Button();
            this.BtnDoData = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.BtnLoadExcelGroupFile = new System.Windows.Forms.Button();
            this.BtnLocalization = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.allContentsLZ = new System.Windows.Forms.Button();
            this.BtnLzSingle = new System.Windows.Forms.Button();
            this.BtnSystemLocalization = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.ServerNameComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.BtnProtocolData = new System.Windows.Forms.Button();
            this.DeleteAllData = new System.Windows.Forms.Button();
            this.SheetGroup.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(821, 24);
            this.menuStrip1.TabIndex = 2;
            // 
            // LabelStatusLine
            // 
            this.LabelStatusLine.AutoSize = true;
            this.LabelStatusLine.Location = new System.Drawing.Point(4, 9);
            this.LabelStatusLine.Name = "LabelStatusLine";
            this.LabelStatusLine.Size = new System.Drawing.Size(95, 12);
            this.LabelStatusLine.TabIndex = 3;
            this.LabelStatusLine.Text = "LabelStatusLine";
            // 
            // SheetGroup
            // 
            this.SheetGroup.Controls.Add(this.SheetPanel);
            this.SheetGroup.Location = new System.Drawing.Point(6, 127);
            this.SheetGroup.Name = "SheetGroup";
            this.SheetGroup.Size = new System.Drawing.Size(147, 194);
            this.SheetGroup.TabIndex = 9;
            this.SheetGroup.TabStop = false;
            this.SheetGroup.Text = "SheetGroup";
            // 
            // SheetPanel
            // 
            this.SheetPanel.AutoScroll = true;
            this.SheetPanel.Location = new System.Drawing.Point(6, 20);
            this.SheetPanel.Name = "SheetPanel";
            this.SheetPanel.Size = new System.Drawing.Size(133, 159);
            this.SheetPanel.TabIndex = 0;
            // 
            // BtnSelectAll
            // 
            this.BtnSelectAll.Location = new System.Drawing.Point(6, 88);
            this.BtnSelectAll.Name = "BtnSelectAll";
            this.BtnSelectAll.Size = new System.Drawing.Size(75, 23);
            this.BtnSelectAll.TabIndex = 11;
            this.BtnSelectAll.Text = "모두 선택";
            this.BtnSelectAll.UseVisualStyleBackColor = true;
            this.BtnSelectAll.Visible = false;
            this.BtnSelectAll.Click += new System.EventHandler(this.OnClickSelectAll);
            // 
            // BtnExportClient
            // 
            this.BtnExportClient.Location = new System.Drawing.Point(21, 82);
            this.BtnExportClient.Name = "BtnExportClient";
            this.BtnExportClient.Size = new System.Drawing.Size(190, 37);
            this.BtnExportClient.TabIndex = 12;
            this.BtnExportClient.Text = "Build Client Data";
            this.BtnExportClient.UseVisualStyleBackColor = true;
            this.BtnExportClient.Click += new System.EventHandler(this.OnClickExportClient);
            // 
            // BtnUnSelectAll
            // 
            this.BtnUnSelectAll.Location = new System.Drawing.Point(87, 88);
            this.BtnUnSelectAll.Name = "BtnUnSelectAll";
            this.BtnUnSelectAll.Size = new System.Drawing.Size(75, 23);
            this.BtnUnSelectAll.TabIndex = 13;
            this.BtnUnSelectAll.Text = "모두 해제";
            this.BtnUnSelectAll.UseVisualStyleBackColor = true;
            this.BtnUnSelectAll.Visible = false;
            this.BtnUnSelectAll.Click += new System.EventHandler(this.OnClickUnSelectAll);
            // 
            // BtnDoAll
            // 
            this.BtnDoAll.Location = new System.Drawing.Point(696, 189);
            this.BtnDoAll.Name = "BtnDoAll";
            this.BtnDoAll.Size = new System.Drawing.Size(104, 132);
            this.BtnDoAll.TabIndex = 14;
            this.BtnDoAll.Text = "Clear Directory\r\nAll Data\r\nAll VN\r\nConstData Build";
            this.BtnDoAll.UseVisualStyleBackColor = true;
            this.BtnDoAll.Visible = false;
            this.BtnDoAll.Click += new System.EventHandler(this.OnClickDoAll);
            // 
            // BtnMakeProtoEnum
            // 
            this.BtnMakeProtoEnum.Location = new System.Drawing.Point(167, 140);
            this.BtnMakeProtoEnum.Name = "BtnMakeProtoEnum";
            this.BtnMakeProtoEnum.Size = new System.Drawing.Size(138, 51);
            this.BtnMakeProtoEnum.TabIndex = 16;
            this.BtnMakeProtoEnum.Text = "Make Enum";
            this.BtnMakeProtoEnum.UseVisualStyleBackColor = true;
            this.BtnMakeProtoEnum.Click += new System.EventHandler(this.OnClickMakeEnum);
            // 
            // BtnLoadExcelFile
            // 
            this.BtnLoadExcelFile.Location = new System.Drawing.Point(21, 20);
            this.BtnLoadExcelFile.Name = "BtnLoadExcelFile";
            this.BtnLoadExcelFile.Size = new System.Drawing.Size(88, 37);
            this.BtnLoadExcelFile.TabIndex = 17;
            this.BtnLoadExcelFile.Text = "Load Single Excel";
            this.BtnLoadExcelFile.UseVisualStyleBackColor = true;
            this.BtnLoadExcelFile.Click += new System.EventHandler(this.OnClickLoadExcelFile);
            // 
            // BtnLoadDataFile
            // 
            this.BtnLoadDataFile.Location = new System.Drawing.Point(223, 20);
            this.BtnLoadDataFile.Name = "BtnLoadDataFile";
            this.BtnLoadDataFile.Size = new System.Drawing.Size(88, 37);
            this.BtnLoadDataFile.TabIndex = 18;
            this.BtnLoadDataFile.Text = "Load Single Data";
            this.BtnLoadDataFile.UseVisualStyleBackColor = true;
            this.BtnLoadDataFile.Click += new System.EventHandler(this.OnClickLoadDataFile);
            // 
            // BtnExportServer
            // 
            this.BtnExportServer.Location = new System.Drawing.Point(223, 82);
            this.BtnExportServer.Name = "BtnExportServer";
            this.BtnExportServer.Size = new System.Drawing.Size(88, 37);
            this.BtnExportServer.TabIndex = 19;
            this.BtnExportServer.Text = "Build Server Data";
            this.BtnExportServer.UseVisualStyleBackColor = true;
            this.BtnExportServer.Visible = false;
            this.BtnExportServer.Click += new System.EventHandler(this.OnClickExportServer);
            // 
            // BtnConstData
            // 
            this.BtnConstData.Location = new System.Drawing.Point(167, 197);
            this.BtnConstData.Name = "BtnConstData";
            this.BtnConstData.Size = new System.Drawing.Size(138, 49);
            this.BtnConstData.TabIndex = 22;
            this.BtnConstData.Text = "ConstData";
            this.BtnConstData.UseVisualStyleBackColor = true;
            this.BtnConstData.Click += new System.EventHandler(this.OnClickConstDataFile);
            // 
            // BtnDoData
            // 
            this.BtnDoData.Location = new System.Drawing.Point(696, 36);
            this.BtnDoData.Name = "BtnDoData";
            this.BtnDoData.Size = new System.Drawing.Size(104, 61);
            this.BtnDoData.TabIndex = 24;
            this.BtnDoData.Text = "All Data Build";
            this.BtnDoData.UseVisualStyleBackColor = true;
            this.BtnDoData.Click += new System.EventHandler(this.OnClickDataAll);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.BtnLoadExcelGroupFile);
            this.groupBox1.Controls.Add(this.BtnLoadExcelFile);
            this.groupBox1.Controls.Add(this.BtnExportClient);
            this.groupBox1.Controls.Add(this.BtnLoadDataFile);
            this.groupBox1.Controls.Add(this.BtnExportServer);
            this.groupBox1.Location = new System.Drawing.Point(346, 27);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(329, 132);
            this.groupBox1.TabIndex = 26;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Single Excel and Data Process";
            // 
            // BtnLoadExcelGroupFile
            // 
            this.BtnLoadExcelGroupFile.Location = new System.Drawing.Point(123, 20);
            this.BtnLoadExcelGroupFile.Name = "BtnLoadExcelGroupFile";
            this.BtnLoadExcelGroupFile.Size = new System.Drawing.Size(88, 37);
            this.BtnLoadExcelGroupFile.TabIndex = 27;
            this.BtnLoadExcelGroupFile.Text = "Load Single Group Excel";
            this.BtnLoadExcelGroupFile.UseVisualStyleBackColor = true;
            this.BtnLoadExcelGroupFile.Visible = false;
            this.BtnLoadExcelGroupFile.Click += new System.EventHandler(this.OnClickLoadGroupFile);
            // 
            // BtnLocalization
            // 
            this.BtnLocalization.Location = new System.Drawing.Point(177, 80);
            this.BtnLocalization.Name = "BtnLocalization";
            this.BtnLocalization.Size = new System.Drawing.Size(133, 37);
            this.BtnLocalization.TabIndex = 20;
            this.BtnLocalization.Text = "All System \r\n+ All Contents";
            this.BtnLocalization.UseVisualStyleBackColor = true;
            this.BtnLocalization.Visible = false;
            this.BtnLocalization.Click += new System.EventHandler(this.OnClickLocalizationFile);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.allContentsLZ);
            this.groupBox2.Controls.Add(this.BtnLzSingle);
            this.groupBox2.Controls.Add(this.BtnLocalization);
            this.groupBox2.Controls.Add(this.BtnSystemLocalization);
            this.groupBox2.Location = new System.Drawing.Point(346, 189);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(329, 132);
            this.groupBox2.TabIndex = 27;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Localization";
            // 
            // allContentsLZ
            // 
            this.allContentsLZ.Location = new System.Drawing.Point(21, 80);
            this.allContentsLZ.Name = "allContentsLZ";
            this.allContentsLZ.Size = new System.Drawing.Size(138, 37);
            this.allContentsLZ.TabIndex = 30;
            this.allContentsLZ.Text = "ALL Contents LZ";
            this.allContentsLZ.UseVisualStyleBackColor = true;
            this.allContentsLZ.Click += new System.EventHandler(this.ButtonAllContentsLZ);
            // 
            // BtnLzSingle
            // 
            this.BtnLzSingle.Location = new System.Drawing.Point(21, 20);
            this.BtnLzSingle.Name = "BtnLzSingle";
            this.BtnLzSingle.Size = new System.Drawing.Size(138, 37);
            this.BtnLzSingle.TabIndex = 26;
            this.BtnLzSingle.Text = "Contents LZ";
            this.BtnLzSingle.UseVisualStyleBackColor = true;
            this.BtnLzSingle.Click += new System.EventHandler(this.OnClickLzSingle);
            // 
            // BtnSystemLocalization
            // 
            this.BtnSystemLocalization.Location = new System.Drawing.Point(177, 20);
            this.BtnSystemLocalization.Name = "BtnSystemLocalization";
            this.BtnSystemLocalization.Size = new System.Drawing.Size(133, 37);
            this.BtnSystemLocalization.TabIndex = 29;
            this.BtnSystemLocalization.Text = "All System LZ";
            this.BtnSystemLocalization.UseVisualStyleBackColor = true;
            this.BtnSystemLocalization.Visible = false;
            this.BtnSystemLocalization.Click += new System.EventHandler(this.OnClickLzSystem);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(6, 36);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(299, 25);
            this.progressBar1.TabIndex = 32;
            // 
            // ServerNameComboBox
            // 
            this.ServerNameComboBox.FormattingEnabled = true;
            this.ServerNameComboBox.Items.AddRange(new object[] {
            "none",
            "local",
            "dev",
            "qa"});
            this.ServerNameComboBox.Location = new System.Drawing.Point(231, 91);
            this.ServerNameComboBox.Name = "ServerNameComboBox";
            this.ServerNameComboBox.Size = new System.Drawing.Size(75, 20);
            this.ServerNameComboBox.TabIndex = 33;
            this.ServerNameComboBox.Visible = false;
            this.ServerNameComboBox.SelectedIndexChanged += new System.EventHandler(this.ServerNameComboBox_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(168, 94);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 12);
            this.label1.TabIndex = 34;
            this.label1.Text = "서버 선택";
            this.label1.Visible = false;
            // 
            // BtnProtocolData
            // 
            this.BtnProtocolData.BackColor = System.Drawing.Color.Red;
            this.BtnProtocolData.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.BtnProtocolData.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.BtnProtocolData.Location = new System.Drawing.Point(167, 252);
            this.BtnProtocolData.Name = "BtnProtocolData";
            this.BtnProtocolData.Size = new System.Drawing.Size(138, 54);
            this.BtnProtocolData.TabIndex = 35;
            this.BtnProtocolData.Text = "ProtocolData";
            this.BtnProtocolData.UseVisualStyleBackColor = false;
            this.BtnProtocolData.Visible = false;
            this.BtnProtocolData.Click += new System.EventHandler(this.BtnProtocolData_Click);
            // 
            // DeleteAllData
            // 
            this.DeleteAllData.Location = new System.Drawing.Point(696, 103);
            this.DeleteAllData.Name = "DeleteAllData";
            this.DeleteAllData.Size = new System.Drawing.Size(104, 61);
            this.DeleteAllData.TabIndex = 36;
            this.DeleteAllData.Text = "Clear All Data Directory";
            this.DeleteAllData.UseVisualStyleBackColor = true;
            this.DeleteAllData.Visible = false;
            this.DeleteAllData.Click += new System.EventHandler(this.DeleteAllData_Click);
            // 
            // dataTool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(821, 347);
            this.Controls.Add(this.DeleteAllData);
            this.Controls.Add(this.BtnProtocolData);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ServerNameComboBox);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.BtnMakeProtoEnum);
            this.Controls.Add(this.BtnDoAll);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.BtnDoData);
            this.Controls.Add(this.BtnConstData);
            this.Controls.Add(this.BtnUnSelectAll);
            this.Controls.Add(this.BtnSelectAll);
            this.Controls.Add(this.SheetGroup);
            this.Controls.Add(this.LabelStatusLine);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "dataTool";
            this.Text = "데이터 툴";
            this.SheetGroup.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Label LabelStatusLine;
        private System.Windows.Forms.GroupBox SheetGroup;
        public System.Windows.Forms.Panel SheetPanel;
        private System.Windows.Forms.Button BtnSelectAll;
        private System.Windows.Forms.Button BtnExportClient;
        private System.Windows.Forms.Button BtnUnSelectAll;
        private System.Windows.Forms.Button BtnDoAll;
        private System.Windows.Forms.Button BtnMakeProtoEnum;
        private System.Windows.Forms.Button BtnLoadExcelFile;
        private System.Windows.Forms.Button BtnLoadDataFile;
        private System.Windows.Forms.Button BtnExportServer;
        private System.Windows.Forms.Button BtnConstData;
        private System.Windows.Forms.Button BtnDoData;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button BtnLoadExcelGroupFile;
        private System.Windows.Forms.Button BtnLocalization;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button BtnLzSingle;
        private System.Windows.Forms.Button BtnSystemLocalization;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.ComboBox ServerNameComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button BtnProtocolData;
        private System.Windows.Forms.Button DeleteAllData;
        private System.Windows.Forms.Button allContentsLZ;
    }
}

