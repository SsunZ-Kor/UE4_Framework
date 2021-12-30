using System;
using System.IO;
using DataTool.Global;

namespace DataTool
{
    public partial class DataFileClassManager
    {
        private void MakeDataFileHeader()
        {
            string strPath = m_strCppRootPath + "DataFileHeader.h";

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Drum");
                writer.WriteLine("#pragma once");
                writer.WriteLine();

                foreach (var value in m_listDataFiles)
                {
                    writer.WriteLine(string.Format("#include \"DataStructure/C{0}.h\"", value));
                }

                if (m_listLZLanguages.Count > 0)
                    writer.WriteLine("#include \"CLocalizationData.h\"");
            }
        }

        private void MakeDataFileEnum()
        {
            string strPath = m_strCppRootPath + "DataFileEnum.h";

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Drum");
                writer.WriteLine("#pragma once");

                if (m_listDataFiles.Count > 0)
                {
                    writer.WriteLine();
                    writer.WriteLine("UENUM()");
                    writer.WriteLine("enum class EDataFileEnum : uint8");
                    writer.WriteLine("{");

                    //Data Files
                    for (int i = 0 ; i < m_listDataFiles.Count; ++i)
                    {
                        if(m_bUseConst)
                            writer.WriteLine(string.Format("\t{0} = {1},", m_listDataFiles[i], i));
                        else
                            writer.WriteLine(string.Format("\t{0} = {1},", m_listDataFiles[i], i + 1));
                    }
                    writer.WriteLine("\tMAX,");
                    writer.WriteLine("};");
                }

                //Localization Data
                if (m_listLZLanguages.Count > 0)
                {
                    writer.WriteLine();
                    writer.WriteLine("UENUM()");
                    writer.WriteLine("enum class ELanguage : uint8");
                    writer.WriteLine("{");

                    for (int i = 0; i < m_listLZLanguages.Count; ++i)
                    {
                        writer.WriteLine(string.Format("\t{0} = {1},", m_listLZLanguages[i], i));
                    }
                    writer.WriteLine("};");
                }
            }
        }

        private void MakeDataFileContainer()
        {
            string strPath = m_strCppRootPath + "CDataFileContainer.h";

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Drum");
                writer.WriteLine("#pragma once");
                writer.WriteLine("#include \"DataFileHeader.h\"");
                writer.WriteLine();
                writer.WriteLine("class DATALOADLIB_API CDataFileContainer");
                writer.WriteLine("{");
                writer.WriteLine("\tfriend class CDataFileFactory;");
                writer.WriteLine();
                writer.WriteLine("private:");

                //Data Files
                foreach (var value in m_listDataFiles)
                {
                    if(value == GlobalVar.DATAFILETYPENAME_CONSTDATA)
                        writer.WriteLine(string.Format("\tC{0}* {0};", GlobalVar.DATAFILETYPENAME_CONSTDATA));
                    else
                        writer.WriteLine(string.Format("\tTMap<int32, C{0}*> Map{0};", value));
                }

                //Localization Data
                if (m_listLZLanguages.Count > 0)
                {
                    writer.WriteLine(string.Format("\tTMap<FString, C{0}*> Map{0};", GlobalVar.DATAFILETYPENAME_LOCALIZATION));
                }

                writer.WriteLine("};");
            }
        }

        private void MakeDataFileFactoryH()
        {
            string strPath = m_strCppRootPath + "CDataFileFactory.h";

            if (File.Exists(strPath) && !m_bDirtyCommonFile)
                return;

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Generated only one time when file is not exists.");
                writer.WriteLine("// Drum");
                writer.WriteLine("#pragma once");
                writer.WriteLine();
                writer.WriteLine("#include \"CDataFileBase.h\"");
                writer.WriteLine("#include \"DataFileEnum.h\"");
                writer.WriteLine("#include \"CDataFileContainer.h\"");
                writer.WriteLine("#include \"DataLoadLib/BinaryDataSource.h\"");
                writer.WriteLine();

                writer.WriteLine("class DATALOADLIB_API CDataFileFactory");
                writer.WriteLine("{");
                writer.WriteLine("private:");
                writer.WriteLine("\tCDataFileContainer* m_pContainer;");
                writer.WriteLine();

                writer.WriteLine("\tCDataFileFactory()");
                writer.WriteLine("\t{");
                writer.WriteLine("\t\tm_pContainer = new CDataFileContainer();");
                writer.WriteLine("\t}");
                writer.WriteLine();

                writer.WriteLine("\t~CDataFileFactory()");
                writer.WriteLine("\t{");
                writer.WriteLine("\t\tClearAllDataFiles();");
                writer.WriteLine("\t}");
                writer.WriteLine();
                
                writer.WriteLine("\ttemplate<typename TValue>");
                writer.WriteLine("\tvoid CreateDataFile(const UBinaryDataSource* uData, TMap<int32, TValue*>& map)");
                writer.WriteLine("\t{");
                writer.WriteLine("\t\tfor(auto& rowData : uData->TableInfo)");
                writer.WriteLine("\t\t{");
                writer.WriteLine("\t\t\tTValue* cData = new TValue();");
                writer.WriteLine("\t\t\tcData->SetInfo(rowData);");
                writer.WriteLine();
                writer.WriteLine("\t\t\tmap.Add(cData->ID, cData);");
                writer.WriteLine("\t\t}");
                writer.WriteLine("\t}");
                writer.WriteLine();

                writer.WriteLine("\ttemplate<typename TKey, typename TValue>");
                writer.WriteLine("\tvoid ClearAllDataFiles(TMap<TKey, TValue*>& map)");
                writer.WriteLine("\t{");
                writer.WriteLine("\t\tfor(auto& tuple : map)");
                writer.WriteLine("\t\t{");
                writer.WriteLine("\t\t\tif(tuple.Value != nullptr)");
                writer.WriteLine("\t\t\t\tdelete tuple.Value;");
                writer.WriteLine();
                writer.WriteLine("\t\t\ttuple.Value = nullptr;");
                writer.WriteLine("\t\t}");
                writer.WriteLine();
                writer.WriteLine("\t\tmap.Reset();");
                writer.WriteLine("\t}");
                writer.WriteLine();

                writer.WriteLine("public:");
                writer.WriteLine("\tvoid ClearAllDataFiles();");
                writer.WriteLine();                

                if(m_listDataFiles.Count > 0)
                {
                    writer.WriteLine("\tvoid* CreateDataFile(EDataFileEnum eData, const UBinaryDataSource* uData);");
                    writer.WriteLine();
                    writer.WriteLine("\tconst CDataFileBase* GetData(EDataFileEnum eData, int32 nKey) const;");
                    writer.WriteLine();
                }

                if(m_bUseConst)
                {
                    writer.WriteLine("\tconst CConstData* GetConstData() const;");
                    writer.WriteLine();
                }

                if(m_listLZLanguages.Count > 0)
                {
                    writer.WriteLine("\tvoid CreateLocalizationFile(const UBinaryDataSource* uData);");
                    writer.WriteLine();
                    writer.WriteLine("\tconst TMap<FString, class CLocalizationData*>* GetLocalizationMap() const;");
                    writer.WriteLine();
                }
                
                writer.WriteLine("\tstatic CDataFileFactory* Instance() ");
                writer.WriteLine("\t{");
                writer.WriteLine("\t\tstatic CDataFileFactory* instance = new CDataFileFactory();");
                writer.WriteLine("\t\treturn instance;");
                writer.WriteLine("\t}");
                writer.WriteLine("};");
            }
        }

        private void MakeDatafileFactoryCpp()
        {
            string strPath = m_strCppRootPath + "CDataFileFactory.cpp";

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), GlobalVar.CLIENT_TEXT_CPP_ENCODING))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Drum");
                writer.WriteLine("#include \"CDataFileFactory.h\"");
                writer.WriteLine();

                writer.WriteLine("void CDataFileFactory::ClearAllDataFiles()");
                writer.WriteLine("{");
                writer.WriteLine("\tif(m_pContainer == nullptr)");
                writer.WriteLine("\t\treturn;");
                writer.WriteLine();

                foreach (var value in m_listDataFiles)
                {
                    if (value == GlobalVar.DATAFILETYPENAME_CONSTDATA)
                    {
                        writer.WriteLine(string.Format("\tif(m_pContainer->{0} != nullptr)", GlobalVar.DATAFILETYPENAME_CONSTDATA));
                        writer.WriteLine("\t{");
                        writer.WriteLine(string.Format("\t\tdelete m_pContainer->{0};", GlobalVar.DATAFILETYPENAME_CONSTDATA));
                        writer.WriteLine(string.Format("\t\tm_pContainer->{0} = nullptr;", GlobalVar.DATAFILETYPENAME_CONSTDATA));
                        writer.WriteLine("\t}");
                        writer.WriteLine();
                    }
                    else
                        writer.WriteLine(string.Format("\tClearAllDataFiles(m_pContainer->Map{0});", value));
                }

                if (m_listLZLanguages.Count > 0)
                {
                    writer.WriteLine();
                    writer.WriteLine(string.Format("\tClearAllDataFiles(m_pContainer->Map{0});", GlobalVar.DATAFILETYPENAME_LOCALIZATION));
                }

                writer.WriteLine();
                writer.WriteLine("\tdelete m_pContainer;");
                writer.WriteLine("\tm_pContainer = nullptr;");
                writer.WriteLine("}");
                writer.WriteLine();

                if (m_listDataFiles.Count > 0)
                {
                    writer.WriteLine("void* CDataFileFactory::CreateDataFile(EDataFileEnum eData, const UBinaryDataSource* uData)");
                    writer.WriteLine("{");
                    writer.WriteLine("\tif(uData == nullptr)");
                    writer.WriteLine("\t\treturn nullptr;");
                    writer.WriteLine();
                    writer.WriteLine("\tif(m_pContainer == nullptr)");
                    writer.WriteLine("\t\tm_pContainer = new CDataFileContainer();");
                    writer.WriteLine();

                    writer.WriteLine("\tswitch (eData)");
                    writer.WriteLine("\t{");
                    //
                    foreach (var value in m_listDataFiles)
                    {
                        writer.WriteLine(string.Format("\tcase EDataFileEnum::{0}:", value));

                        if (value == GlobalVar.DATAFILETYPENAME_CONSTDATA)
                        {
                            writer.WriteLine("\t\tif(m_pContainer->ConstData == nullptr)");
                            writer.WriteLine("\t\t\tm_pContainer->ConstData = new CConstData();");
                            writer.WriteLine("\t\tm_pContainer->ConstData->SetInfo(uData->TableInfo);");
                            writer.WriteLine("\t\treturn nullptr;");
                        }
                        else
                        {
                            writer.WriteLine(string.Format("\t\tCreateDataFile<C{0}>(uData, m_pContainer->Map{0});", value));
                            writer.WriteLine(string.Format("\t\treturn &m_pContainer->Map{0};", value));
                        }
                    }
                    //
                    writer.WriteLine("\t}");
                    writer.WriteLine();

                    writer.WriteLine("\treturn nullptr;");
                    writer.WriteLine("}");
                    writer.WriteLine();

                    writer.WriteLine("const CDataFileBase* CDataFileFactory::GetData(EDataFileEnum eData, int32 nKey) const");
                    writer.WriteLine("{");
                    writer.WriteLine("\tif(m_pContainer == nullptr)");
                    writer.WriteLine("\t\treturn nullptr;");
                    writer.WriteLine();

                    writer.WriteLine("\tswitch (eData)");
                    writer.WriteLine("\t{");
                    //
                    foreach (var value in m_listDataFiles)
                    {
                        writer.WriteLine(string.Format("\tcase EDataFileEnum::{0}:", value));
                        if (value == "ConstData")
                        {
                            writer.WriteLine("\t\treturn nullptr;");
                        }
                        else
                        {
                            writer.WriteLine(string.Format("\t\treturn m_pContainer->Map{0}.Contains(nKey) ?", value));
                            writer.WriteLine(string.Format("\t\t\tm_pContainer->Map{0}[nKey] : nullptr;", value));
                        }
                    }
                    //
                    writer.WriteLine("\t}");
                    writer.WriteLine();

                    writer.WriteLine("\treturn nullptr;");
                    writer.WriteLine("}");
                    writer.WriteLine();
                }

                if (m_bUseConst)
                {
                    writer.WriteLine("const CConstData* CDataFileFactory::GetConstData() const");
                    writer.WriteLine("{");
                    writer.WriteLine("\tif(m_pContainer == nullptr)");
                    writer.WriteLine("\t\treturn nullptr;");
                    writer.WriteLine();
                    writer.WriteLine("\treturn m_pContainer->ConstData;	");
                    writer.WriteLine("}");
                    writer.WriteLine();
                }

                if(m_listLZLanguages.Count > 0)
                {
                    writer.WriteLine("void CDataFileFactory::CreateLocalizationFile(const UBinaryDataSource* uData)");
                    writer.WriteLine("{");
                    writer.WriteLine("\tif(uData == nullptr)");
                    writer.WriteLine("\t\treturn;");
                    writer.WriteLine();
                    writer.WriteLine("\tif(m_pContainer == nullptr)");
                    writer.WriteLine("\t\tm_pContainer = new CDataFileContainer();");
                    writer.WriteLine();
                    writer.WriteLine("\tfor(auto& rowData : uData->TableInfo)");
                    writer.WriteLine("\t{");
                    writer.WriteLine("\t\tCLocalizationData* cData = new CLocalizationData();");
                    writer.WriteLine("\t\tcData->SetInfo(rowData);");
                    writer.WriteLine();
                    writer.WriteLine("\t\tif(m_pContainer->MapLocalizationData.Contains(cData->ID))");
                    writer.WriteLine("\t\t{");
                    writer.WriteLine("\t\t\tdelete cData;");
                    writer.WriteLine("\t\t\tcontinue;");
                    writer.WriteLine("\t\t}");
                    writer.WriteLine();
                    writer.WriteLine("\t\tm_pContainer->MapLocalizationData.Add(cData->ID, cData);");
                    writer.WriteLine("\t}");
                    writer.WriteLine("}");
                    writer.WriteLine();

                    writer.WriteLine("const TMap<FString, CLocalizationData*>* CDataFileFactory::GetLocalizationMap() const");
                    writer.WriteLine("{");
                    writer.WriteLine("\tif(m_pContainer == nullptr)");
                    writer.WriteLine("\t\treturn nullptr;");
                    writer.WriteLine();
                    writer.WriteLine("\treturn &m_pContainer->MapLocalizationData;");
                    writer.WriteLine("}");
                    writer.WriteLine();
                }
            }
        }
    }
}