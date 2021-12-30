namespace DataTool
{
    partial class ExportMenu
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
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.TxtDataFileTypeName = new System.Windows.Forms.TextBox();
            this.TxtDataFileName = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView
            // 
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Location = new System.Drawing.Point(12, 48);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.RowTemplate.Height = 23;
            this.dataGridView.Size = new System.Drawing.Size(760, 506);
            this.dataGridView.TabIndex = 0;
            // 
            // TxtDataFileTypeName
            // 
            this.TxtDataFileTypeName.Location = new System.Drawing.Point(12, 12);
            this.TxtDataFileTypeName.Name = "TxtDataFileTypeName";
            this.TxtDataFileTypeName.Size = new System.Drawing.Size(299, 21);
            this.TxtDataFileTypeName.TabIndex = 1;
            // 
            // TxtDataFileName
            // 
            this.TxtDataFileName.Location = new System.Drawing.Point(317, 12);
            this.TxtDataFileName.Name = "TxtDataFileName";
            this.TxtDataFileName.Size = new System.Drawing.Size(455, 21);
            this.TxtDataFileName.TabIndex = 2;
            // 
            // ExportMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 566);
            this.Controls.Add(this.TxtDataFileName);
            this.Controls.Add(this.TxtDataFileTypeName);
            this.Controls.Add(this.dataGridView);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ExportMenu";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "DataView";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView;
        private System.Windows.Forms.TextBox TxtDataFileTypeName;
        private System.Windows.Forms.TextBox TxtDataFileName;
    }
}