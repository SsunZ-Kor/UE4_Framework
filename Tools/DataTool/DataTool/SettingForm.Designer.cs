namespace DataTool
{
    partial class SettingForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.settingKeyBtn = new System.Windows.Forms.Button();
            this.uploadKeyToDBBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // settingKeyBtn
            // 
            this.settingKeyBtn.Location = new System.Drawing.Point(85, 49);
            this.settingKeyBtn.Name = "settingKeyBtn";
            this.settingKeyBtn.Size = new System.Drawing.Size(94, 35);
            this.settingKeyBtn.TabIndex = 56;
            this.settingKeyBtn.Text = "MakeKey";
            this.settingKeyBtn.UseVisualStyleBackColor = true;
            this.settingKeyBtn.Click += new System.EventHandler(this.OnClickChangeKey);
            // 
            // uploadKeyToDBBtn
            // 
            this.uploadKeyToDBBtn.Location = new System.Drawing.Point(85, 103);
            this.uploadKeyToDBBtn.Name = "uploadKeyToDBBtn";
            this.uploadKeyToDBBtn.Size = new System.Drawing.Size(94, 35);
            this.uploadKeyToDBBtn.TabIndex = 57;
            this.uploadKeyToDBBtn.Text = "KeyToDB";
            this.uploadKeyToDBBtn.UseVisualStyleBackColor = true;
            this.uploadKeyToDBBtn.Click += new System.EventHandler(this.OnClickUploadKeyToDB);
            // 
            // SettingForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(278, 186);
            this.Controls.Add(this.uploadKeyToDBBtn);
            this.Controls.Add(this.settingKeyBtn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "SettingForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "설정";
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button settingKeyBtn;
        private System.Windows.Forms.Button uploadKeyToDBBtn;
    }
}