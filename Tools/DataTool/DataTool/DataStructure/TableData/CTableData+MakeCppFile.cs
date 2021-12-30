using DataLoadLib.Global;
using DataTool.Global;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataTool
{
    public partial class CTableData
    {
        private void MakeCppSourceCode()
        {
            IsNeedToEnumParse = false;

            foreach (var cSheetData in SheetDatas)
            {
                string relativePath = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CPP_DATASTRUCTURE_FILE);

                if (!Directory.Exists(relativePath))
                    Directory.CreateDirectory(relativePath);

                string camelSheetName = GlobalFunctions.MakeCamelString(cSheetData.strName);

                string strPath = string.Format("{0}/C{1}.h", relativePath, camelSheetName);

                using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), Encoding.Unicode))
                {
                    writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                    writer.WriteLine("// Drum.");
                    writer.WriteLine("");
                    writer.WriteLine("#pragma once");
                    writer.WriteLine("#include \"../CDataFileBase.h\"");
                    writer.WriteLine("");
                    writer.WriteLine(string.Format("class DATALOADLIB_API C{0} : public CDataFileBase", camelSheetName));
                    writer.WriteLine("{");
                    writer.WriteLine("public:");

                    var listColData = MakeCamelColData(cSheetData.listColData);

                    int nIndex = 1;
                    for (int i = nIndex; i < listColData.Count; ++i)
                    {
                        if (listColData[i].eTargetType != ETargetType.CLIENT && listColData[i].eTargetType != ETargetType.ALL)
                            continue;

                        var eType = listColData[i].eDataType;
                        switch (eType)
                        {
                            case EDataType.INT:
                                writer.WriteLine(string.Format("\tint32 {0};", listColData[i].strExcelColName));
                                break;
                            case EDataType.FLOAT:
                                writer.WriteLine(string.Format("\tfloat {0};", listColData[i].strExcelColName));
                                break;
                            case EDataType.STRING:
                                writer.WriteLine(string.Format("\tFString {0};", listColData[i].strExcelColName));
                                break;
                            case EDataType.LONG:
                                writer.WriteLine(string.Format("\tint64 {0};", listColData[i].strExcelColName));
                                break;
                            case EDataType.ENUM:
                                string strTypeName = "E" + listColData[i].strTypeName.Split('_')[1];
                                writer.WriteLine(string.Format("\t{0} {1};", strTypeName, listColData[i].strExcelColName));
                                IsNeedToEnumParse = true;
                                break;
                            case EDataType.BOOL:
                                writer.WriteLine(string.Format("\tbool {0};", listColData[i].strExcelColName));
                                break;
                            default:
                                break;
                        }
                    }

                    writer.WriteLine();
                    writer.WriteLine("\tvirtual void SetInfo(const struct FRowDataInfo& fInfo) override;");
                    writer.WriteLine();
                    writer.WriteLine("\tstatic EDataFileEnum GetEnum();");
                    writer.WriteLine("};");
                }

                strPath = string.Format("{0}/C{1}.cpp", relativePath, camelSheetName);

                using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), Encoding.Unicode))
                {
                    writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                    writer.WriteLine("// Drum.");
                    writer.WriteLine("");

                    writer.WriteLine(string.Format("#include \"C{0}.h\"", camelSheetName));
                    writer.WriteLine("");
                    writer.WriteLine(string.Format("void C{0}::SetInfo(const FRowDataInfo& fInfo)", camelSheetName));
                    writer.WriteLine("{");
                    writer.WriteLine("\tCDataFileBase::SetInfo(fInfo);");
                    writer.WriteLine("");

                    var listColData = MakeCamelColData(cSheetData.listColData);

                    int nIndex = 1;
                    for (int i = nIndex; i < listColData.Count; ++i)
                    {
                        if (listColData[i].eTargetType != ETargetType.CLIENT && listColData[i].eTargetType != ETargetType.ALL)
                            continue;

                        var eType = listColData[i].eDataType;
                        switch (eType)
                        {
                            case EDataType.ENUM:
                                string strTypeName = "E" + listColData[i].strTypeName.Split('_')[1];
                                writer.WriteLine(string.Format("\t{0} = static_cast<{2}>(FCString::Atoi(*fInfo.arrColData[{1}]));", listColData[i].strExcelColName, nIndex++, strTypeName));
                                break;
                            case EDataType.FLOAT:
                                writer.WriteLine(string.Format("\t{0} = FCString::Atof(*fInfo.arrColData[{1}]);", listColData[i].strExcelColName, nIndex++));
                                break;
                            case EDataType.INT:
                                writer.WriteLine(string.Format("\t{0} = FCString::Atoi(*fInfo.arrColData[{1}]);", listColData[i].strExcelColName, nIndex++));
                                break;
                            case EDataType.STRING:
                                writer.WriteLine(string.Format("\t{0} = fInfo.arrColData[{1}];", listColData[i].strExcelColName, nIndex++));
                                break;
                            case EDataType.LONG:
                                writer.WriteLine(string.Format("\t{0} = FCString::Atoi64(*fInfo.arrColData[{1}]);", listColData[i].strExcelColName, nIndex++));
                                break;
                            case EDataType.BOOL:
                                writer.WriteLine(string.Format("\t{0} = FCString::Atoi(*fInfo.arrColData[{1}]) == 1 ? true : false;", listColData[i].strExcelColName, nIndex++));
                                break;
                        }
                    }
                    writer.WriteLine("}");
                    writer.WriteLine();
                    writer.WriteLine(string.Format("EDataFileEnum C{0}::GetEnum()", camelSheetName));
                    writer.WriteLine("{");
                    writer.WriteLine(string.Format("\treturn EDataFileEnum::{0};", camelSheetName));
                    writer.WriteLine("}");
                }
            }
        }
    }
}
