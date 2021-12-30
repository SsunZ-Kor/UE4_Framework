using DataTool.Global;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataTool
{
    public partial class DataFileClassManager
    {
        public void MakeLocalizationFiles()
        {
            if (!m_bDirtyLZLanguage)
                return;

            if (string.IsNullOrWhiteSpace(m_strCppRootPath))
                m_strCppRootPath = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CPP_CLASS_ROOT);

            if (!Directory.Exists(m_strCppRootPath))
                Directory.CreateDirectory(m_strCppRootPath);

            MakeDataFileHeader();
            MakeDataFileEnum();
            MakeDataFileContainer();
            MakeDataFileFactoryH();
            MakeDatafileFactoryCpp();

            m_bDirtyCommonFile = false;

            if (m_bDirtyDataFile)
            {
                MakeDataFileBaseH();
                MakeDataFileBaseCpp();
                SaveDataFiles();
            }

            MakeLocalizationH();
            MakeLocalizationCpp();            

            SaveLZDataLanguage();
        }

        private void MakeLocalizationH()
        {
            string strPath = m_strCppRootPath + string.Format("C{0}.h", GlobalVar.DATAFILETYPENAME_LOCALIZATION);

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Generated only one time when file is not exists.");
                writer.WriteLine("// Drum");
                writer.WriteLine("#pragma once");
                writer.WriteLine();
                writer.WriteLine("enum class ELanguage : uint8;");
                writer.WriteLine();

                writer.WriteLine(string.Format("class DATALOADLIB_API C{0}", GlobalVar.DATAFILETYPENAME_LOCALIZATION));
                writer.WriteLine("{");
                writer.WriteLine("public:");
                writer.WriteLine("\tFString ID;");

                for(int i = 1; i < m_listLZLanguages.Count; ++i)
                {
                    writer.WriteLine(string.Format("\tFString {0};", m_listLZLanguages[i]));
                }
                writer.WriteLine();
                writer.WriteLine("\tvoid SetInfo(const struct FRowDataInfo& fInfo);");
                writer.WriteLine();
                writer.WriteLine("\tconst FString& GetLanguage(int nIndex) const;");
                writer.WriteLine();
                writer.WriteLine("\tconst FString& GetLanguage(ELanguage eLanguage) const;");

                writer.WriteLine();
                writer.WriteLine("\tstatic FString KEY_EMPTY;");                
                writer.WriteLine("};");
            }            
        }

        private void MakeLocalizationCpp()
        {
            string strPath = m_strCppRootPath + string.Format("C{0}.cpp", GlobalVar.DATAFILETYPENAME_LOCALIZATION);

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Generated only one time when file is not exists.");
                writer.WriteLine("// Drum");
                writer.WriteLine(string.Format("#include \"C{0}.h\"", GlobalVar.DATAFILETYPENAME_LOCALIZATION));
                writer.WriteLine("#include \"DataFileEnum.h\"");
                writer.WriteLine("#include \"DataLoadLib/GlobalDataStruct.h\"");
                writer.WriteLine();
                writer.WriteLine("FString CLocalizationData::KEY_EMPTY = TEXT(\"NONE\");");
                writer.WriteLine();
                writer.WriteLine("void CLocalizationData::SetInfo(const FRowDataInfo& fInfo)");
                writer.WriteLine("{");
                writer.WriteLine("\tID = fInfo.arrColData[0];");
                for(int i = 1; i < m_listLZLanguages.Count; ++i)
                    writer.WriteLine(string.Format("\t{0} = fInfo.arrColData[static_cast<int32>(ELanguage::{0})];", m_listLZLanguages[i]));
                writer.WriteLine("}");
                writer.WriteLine();

                writer.WriteLine("const FString& CLocalizationData::GetLanguage(int nIndex) const");
                writer.WriteLine("{");
                writer.WriteLine("\treturn GetLanguage(static_cast<ELanguage>(nIndex));");
                writer.WriteLine("}");
                writer.WriteLine();

                writer.WriteLine("const FString& CLocalizationData::GetLanguage(ELanguage eLanguage) const");
                writer.WriteLine("{");
                writer.WriteLine("\tswitch (eLanguage)");
                writer.WriteLine("\t{");
                for (int i = 1; i < m_listLZLanguages.Count; ++i)
                    writer.WriteLine(string.Format("\tcase ELanguage::{0}: return {0};", m_listLZLanguages[i]));
                writer.WriteLine("\t}");
                writer.WriteLine();
                writer.WriteLine("\treturn KEY_EMPTY;");
                writer.WriteLine("}");
            }
        }
    }
}
