using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DataTool
{
    public partial class LogForm : Form
    {
        public LogForm()
        {
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            this.LabelLog.Text = string.Empty;
        }

        public void SetText(string strLog)
        {
            this.LabelLog.Text = strLog;
        }
    }
}
