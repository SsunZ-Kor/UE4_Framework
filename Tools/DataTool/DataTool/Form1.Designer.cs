namespace DataTool
{
    partial class dataTool
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
            this.BtnMakeProtoEnum = new System.Windows.Forms.Button();
            this.BtnLoadAndBuildExcelFile = new System.Windows.Forms.Button();
            this.BtnLoadDataFile = new System.Windows.Forms.Button();
            this.BtnConstData = new System.Windows.Forms.Button();
            this.BtnDoData = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.allContentsLZ = new System.Windows.Forms.Button();
            this.BtnLzSingle = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.DeleteAllData = new System.Windows.Forms.Button();
            this.BtnLoadLZDataFile = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.BtnAll = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(498, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Visible = false;
            // 
            // LabelStatusLine
            // 
            this.LabelStatusLine.Location = new System.Drawing.Point(7, 18);
            this.LabelStatusLine.Name = "LabelStatusLine";
            this.LabelStatusLine.Size = new System.Drawing.Size(460, 59);
            this.LabelStatusLine.TabIndex = 3;
            this.LabelStatusLine.Text = "LabelStatusLine";
            // 
            // BtnMakeProtoEnum
            // 
            this.BtnMakeProtoEnum.Location = new System.Drawing.Point(21, 20);
            this.BtnMakeProtoEnum.Name = "BtnMakeProtoEnum";
            this.BtnMakeProtoEnum.Size = new System.Drawing.Size(138, 38);
            this.BtnMakeProtoEnum.TabIndex = 16;
            this.BtnMakeProtoEnum.Text = "Make Enum";
            this.BtnMakeProtoEnum.UseVisualStyleBackColor = true;
            this.BtnMakeProtoEnum.Click += new System.EventHandler(this.OnClickMakeEnum);
            // 
            // BtnLoadAndBuildExcelFile
            // 
            this.BtnLoadAndBuildExcelFile.Location = new System.Drawing.Point(173, 20);
            this.BtnLoadAndBuildExcelFile.Name = "BtnLoadAndBuildExcelFile";
            this.BtnLoadAndBuildExcelFile.Size = new System.Drawing.Size(138, 37);
            this.BtnLoadAndBuildExcelFile.TabIndex = 17;
            this.BtnLoadAndBuildExcelFile.Text = "Load And Build Single Excel";
            this.BtnLoadAndBuildExcelFile.UseVisualStyleBackColor = true;
            this.BtnLoadAndBuildExcelFile.Click += new System.EventHandler(this.OnClickLoadExcelFile);
            // 
            // BtnLoadDataFile
            // 
            this.BtnLoadDataFile.Location = new System.Drawing.Point(23, 73);
            this.BtnLoadDataFile.Name = "BtnLoadDataFile";
            this.BtnLoadDataFile.Size = new System.Drawing.Size(88, 37);
            this.BtnLoadDataFile.TabIndex = 18;
            this.BtnLoadDataFile.Text = "Load Single Data";
            this.BtnLoadDataFile.UseVisualStyleBackColor = true;
            this.BtnLoadDataFile.Click += new System.EventHandler(this.OnClickLoadDataFile);
            // 
            // BtnConstData
            // 
            this.BtnConstData.Location = new System.Drawing.Point(21, 73);
            this.BtnConstData.Name = "BtnConstData";
            this.BtnConstData.Size = new System.Drawing.Size(138, 37);
            this.BtnConstData.TabIndex = 22;
            this.BtnConstData.Text = "ConstData";
            this.BtnConstData.UseVisualStyleBackColor = true;
            this.BtnConstData.Click += new System.EventHandler(this.OnClickConstDataFile);
            // 
            // BtnDoData
            // 
            this.BtnDoData.BackColor = System.Drawing.SystemColors.Highlight;
            this.BtnDoData.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.BtnDoData.Location = new System.Drawing.Point(173, 73);
            this.BtnDoData.Name = "BtnDoData";
            this.BtnDoData.Size = new System.Drawing.Size(138, 37);
            this.BtnDoData.TabIndex = 24;
            this.BtnDoData.Text = "All Data Build";
            this.BtnDoData.UseVisualStyleBackColor = false;
            this.BtnDoData.Click += new System.EventHandler(this.OnClickDataAll);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.BtnLoadAndBuildExcelFile);
            this.groupBox1.Controls.Add(this.BtnMakeProtoEnum);
            this.groupBox1.Controls.Add(this.BtnConstData);
            this.groupBox1.Controls.Add(this.BtnDoData);
            this.groupBox1.Location = new System.Drawing.Point(6, 144);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(329, 122);
            this.groupBox1.TabIndex = 26;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Single Excel and Data Process";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.allContentsLZ);
            this.groupBox2.Controls.Add(this.BtnLzSingle);
            this.groupBox2.Location = new System.Drawing.Point(6, 272);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(329, 69);
            this.groupBox2.TabIndex = 27;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Localization";
            // 
            // allContentsLZ
            // 
            this.allContentsLZ.BackColor = System.Drawing.SystemColors.Highlight;
            this.allContentsLZ.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.allContentsLZ.Location = new System.Drawing.Point(173, 20);
            this.allContentsLZ.Name = "allContentsLZ";
            this.allContentsLZ.Size = new System.Drawing.Size(138, 37);
            this.allContentsLZ.TabIndex = 30;
            this.allContentsLZ.Text = "ALL LZ Build";
            this.allContentsLZ.UseVisualStyleBackColor = false;
            this.allContentsLZ.Click += new System.EventHandler(this.OnClickAllContentsLZ);
            // 
            // BtnLzSingle
            // 
            this.BtnLzSingle.Location = new System.Drawing.Point(21, 20);
            this.BtnLzSingle.Name = "BtnLzSingle";
            this.BtnLzSingle.Size = new System.Drawing.Size(138, 37);
            this.BtnLzSingle.TabIndex = 26;
            this.BtnLzSingle.Text = "Load And Build Single LZ";
            this.BtnLzSingle.UseVisualStyleBackColor = true;
            this.BtnLzSingle.Click += new System.EventHandler(this.OnClickLzSingle);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(12, 97);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(329, 25);
            this.progressBar1.TabIndex = 32;
            // 
            // DeleteAllData
            // 
            this.DeleteAllData.Location = new System.Drawing.Point(23, 20);
            this.DeleteAllData.Name = "DeleteAllData";
            this.DeleteAllData.Size = new System.Drawing.Size(88, 47);
            this.DeleteAllData.TabIndex = 36;
            this.DeleteAllData.Text = "Clear All Data And Script";
            this.DeleteAllData.UseVisualStyleBackColor = true;
            this.DeleteAllData.Click += new System.EventHandler(this.OnClickDeleteAllData);
            // 
            // BtnLoadLZDataFile
            // 
            this.BtnLoadLZDataFile.Location = new System.Drawing.Point(23, 116);
            this.BtnLoadLZDataFile.Name = "BtnLoadLZDataFile";
            this.BtnLoadLZDataFile.Size = new System.Drawing.Size(88, 37);
            this.BtnLoadLZDataFile.TabIndex = 37;
            this.BtnLoadLZDataFile.Text = "Load Single LZ Data";
            this.BtnLoadLZDataFile.UseVisualStyleBackColor = true;
            this.BtnLoadLZDataFile.Click += new System.EventHandler(this.OnClickLoadLZDataFile);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.DeleteAllData);
            this.groupBox3.Controls.Add(this.BtnLoadLZDataFile);
            this.groupBox3.Controls.Add(this.BtnLoadDataFile);
            this.groupBox3.Location = new System.Drawing.Point(353, 97);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(133, 169);
            this.groupBox3.TabIndex = 27;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Debugging";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.LabelStatusLine);
            this.groupBox4.Location = new System.Drawing.Point(12, 6);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(474, 85);
            this.groupBox4.TabIndex = 33;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Status Message";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.BtnAll);
            this.groupBox5.Location = new System.Drawing.Point(353, 272);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(133, 69);
            this.groupBox5.TabIndex = 38;
            this.groupBox5.TabStop = false;
            // 
            // BtnAll
            // 
            this.BtnAll.BackColor = System.Drawing.Color.Yellow;
            this.BtnAll.Font = new System.Drawing.Font("굴림", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.BtnAll.ForeColor = System.Drawing.Color.Blue;
            this.BtnAll.Location = new System.Drawing.Point(23, 20);
            this.BtnAll.Name = "BtnAll";
            this.BtnAll.Size = new System.Drawing.Size(88, 37);
            this.BtnAll.TabIndex = 36;
            this.BtnAll.Text = "Build ALL";
            this.BtnAll.UseVisualStyleBackColor = false;
            this.BtnAll.Click += new System.EventHandler(this.OnClickDoAll);
            // 
            // dataTool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(498, 353);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "dataTool";
            this.Text = "데이터 툴";
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Label LabelStatusLine;
        private System.Windows.Forms.Button BtnMakeProtoEnum;
        private System.Windows.Forms.Button BtnLoadAndBuildExcelFile;
        private System.Windows.Forms.Button BtnLoadDataFile;
        private System.Windows.Forms.Button BtnConstData;
        private System.Windows.Forms.Button BtnDoData;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button BtnLzSingle;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Button DeleteAllData;
        private System.Windows.Forms.Button allContentsLZ;
        private System.Windows.Forms.Button BtnLoadLZDataFile;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Button BtnAll;
    }
}

