namespace DataTool
{
    partial class LogForm
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
            if(disposing && ( components != null ))
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
            this.LabelLog = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // LabelLog
            // 
            this.LabelLog.Location = new System.Drawing.Point(12, 9);
            this.LabelLog.Name = "LabelLog";
            this.LabelLog.Size = new System.Drawing.Size(686, 712);
            this.LabelLog.TabIndex = 21;
            // 
            // LogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(710, 730);
            this.Controls.Add(this.LabelLog);
            this.Name = "LogForm";
            this.Text = "LogForm";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label LabelLog;
    }
}