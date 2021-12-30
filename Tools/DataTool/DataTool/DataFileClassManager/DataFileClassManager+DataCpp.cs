using System;
using System.IO;
using DataTool.Global;

namespace DataTool
{
    public partial class DataFileClassManager
    {
        private string m_strCppRootPath = string.Empty;

        public void MakeDataCppFiles()
        {
            if (!m_bDirtyDataFile)
                return;

            if(string.IsNullOrWhiteSpace(m_strCppRootPath))
                m_strCppRootPath = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CPP_CLASS_ROOT);

            if (!Directory.Exists(m_strCppRootPath))
                Directory.CreateDirectory(m_strCppRootPath);

            MakeDataFileHeader();
            MakeDataFileEnum();
            MakeDataFileContainer();
            MakeDataFileFactoryH();
            MakeDatafileFactoryCpp();

            m_bDirtyCommonFile = false;

            MakeDataFileBaseH();
            MakeDataFileBaseCpp();

            if(m_bDirtyLZLanguage)
            {
                MakeLocalizationH();
                MakeLocalizationCpp();
                SaveLZDataLanguage();
            }    

            SaveDataFiles();
        }       

        private void MakeDataFileBaseH()
        {
            string strPath = m_strCppRootPath + "CDataFileBase.h";

            if (File.Exists(strPath) && !m_bDirtyDataFileBase)
                return;

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Generated only one time when file is not exists.");
                writer.WriteLine("// Drum");
                writer.WriteLine("#pragma once");
                writer.WriteLine();
                writer.WriteLine("#include \"DataFileEnum.h\"");
                writer.WriteLine("#include \"DataLoadLib/GlobalDataStruct.h\"");
                if(m_bMadeEnum)
                    writer.WriteLine("#include \"DataStructure/DataTypeEnum.h\"");
                writer.WriteLine();

                writer.WriteLine("class DATALOADLIB_API CDataFileBase");
                writer.WriteLine("{");
                writer.WriteLine("public:");
                writer.WriteLine("\tint32 ID;");
                writer.WriteLine();
                writer.WriteLine("\tvirtual ~CDataFileBase() { }");
                writer.WriteLine();                
                writer.WriteLine("\tvirtual void SetInfo(const FRowDataInfo& fInfo);");
                writer.WriteLine();
                writer.WriteLine("\tstatic EDataFileEnum GetEnum();");
                writer.WriteLine("};");
            }
        }

        private void MakeDataFileBaseCpp()
        {
            string strPath = m_strCppRootPath + "CDataFileBase.cpp";

            if (File.Exists(strPath) && !m_bDirtyDataFileBase)
                return;

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Generated only one time when file is not exists.");
                writer.WriteLine("// Drum");
                writer.WriteLine("#include \"CDataFileBase.h\"");

                writer.WriteLine();
                writer.WriteLine("void CDataFileBase::SetInfo(const FRowDataInfo& fInfo)");
                writer.WriteLine("{");
                writer.WriteLine("\tID = FCString::Atoi(*fInfo.arrColData[0]);");
                writer.WriteLine("}");

                writer.WriteLine();
                writer.WriteLine("EDataFileEnum CDataFileBase::GetEnum()");
                writer.WriteLine("{");
                writer.WriteLine("\treturn EDataFileEnum::MAX;");
                writer.WriteLine("}");
            }
        }
    }
}
