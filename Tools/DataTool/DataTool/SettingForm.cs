using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DataTool.Global;

namespace DataTool
{
    public partial class SettingForm : Form
    {
        public enum EPathName
        {
            ExcelData,
            EnumType,               //Enum Type Path
            GroupData,              //Group Data Path
            LocalizationData,       //Localization Path
            SystemData,             //Localization System Path
            Duty,
            ProtoData,              //Proto Data Path
            ConstData,              //Const Data Path
            ServerData,             //Server Data Save Path
            EServerConstPath,       //Use EServerConstPath
            AB_GameData,            //Client Data Save Path
            GameDataStructs,        //Client Code Save Path
            AB_Localization,        //Localization Data Save Path
            System,                 //Localization Data System Path
            LocalizationDuty,       //Localization Data Duty Path
            VisualNovel,            //VNRoot
            ShareWithServer,        //Client proto build target
            EServerProtoPath,       //Use EServerProtoPath
        }

        private enum EServerPathName
        {
            Server = 0,
            code,
            bfproject,
            trunk,
            BFMultiModule,
            End
        }

        private enum EServerConstPath
        {
            BFCommon = 0,
            src,
            main,
            java,
            com,
            ihkim,
            bf,
            common,
            constdata,
            End
        }

        #region Form Btn Handler

        private void OnClickOK(object sender, EventArgs e)
        {
            Close();
        }

        private void OnClickChangeKey(object sender, EventArgs e)
        {
            if(GlobalVar.HaveAuthority)
            {
                GlobalFunctions.MakeKey();

                MessageBox.Show(string.Format("키 추출 완료\n{0}\n{1}", GlobalVar.EncKeyVer, GlobalVar.EncKey));
            }
            else
                MessageBox.Show(string.Format("권한이 없습니다."));

        }

        private void OnClickUploadKeyToDB(object sender, EventArgs e)
        {
            if(GlobalVar.HaveAuthority)
            {
                if(GlobalFunctions.RunDBEncrypt())
                    MessageBox.Show(string.Format("Upload 완료"));
            }
            else
                MessageBox.Show(string.Format("권한이 없습니다."));
        }

        #endregion Form Btn Handler

    }
}
