using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DataTool.Global;
using DataLoadLib.Global;

namespace DataTool
{
    public partial class ExportMenu : Form
    {
        public ExportMenu(List<DataInfo[]> listDataInfo, string strFileName, string strTypeName)
        {
            InitializeComponent();

            if (string.IsNullOrEmpty(strFileName))
                TxtDataFileName.Enabled = false;
            else
            {
                TxtDataFileName.Enabled = true;
                TxtDataFileName.Text = string.Format("FileName : {0}", strFileName);
            }

            if (string.IsNullOrEmpty(strTypeName))
                TxtDataFileTypeName.Enabled = false;
            else
            {
                TxtDataFileTypeName.Enabled = true;
                TxtDataFileTypeName.Text = string.Format("DataFileType : {0}", strTypeName);
            }

            dataGridView.ColumnCount = listDataInfo[0].Length;

            for(int i = 0 ; i < listDataInfo[0].Length ; ++i)
            {
                dataGridView.Columns[i].Name = i.ToString();
            }

            List<string> listRow = new List<string>();
            for(int row = 0 ; row < listDataInfo.Count ; ++row)
            {
                listRow.Clear();
                for(int col = 0 ; col < listDataInfo[0].Length ; ++col)
                {
                    listRow.Add(GlobalFunctions.GetDataInfoString(listDataInfo[row][col].eDataType, listDataInfo[row][col]));
                }
                dataGridView.Rows.Add(listRow.ToArray());
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
