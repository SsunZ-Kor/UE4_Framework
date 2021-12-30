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
    public partial class CConstData
    {
        private void MakeCppSourceCode()
        {
            if (SheetDatas.Count == 0 || SheetDatas[0] == null)
                return;

            var cSheetData = SheetDatas[0];

            string relativePath = GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_CPP_DATASTRUCTURE_FILE);

            if (!Directory.Exists(relativePath))
                Directory.CreateDirectory(relativePath);

            string strPath = string.Format("{0}/CConstData.h", relativePath);

            string strCppFunction = "void CConstData::SetInfo(const TArray<FRowDataInfo>& TableInfo)\n{\n";

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), Encoding.Unicode))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Drum.");
                writer.WriteLine();
                writer.WriteLine("#pragma once");
                writer.WriteLine();
                writer.WriteLine("class CConstData\n{\npublic:");

                for (int nRow = 0; nRow < cSheetData.nRowCount; ++nRow)
                {
                    if (cSheetData.arrCellData[nRow, 0] == null)
                    {
                        throw new System.Exception("Error");
                    }

                    string strName = cSheetData.arrCellData[nRow, 1].GetStrValue();
                    int nValue = cSheetData.arrCellData[nRow, 2].GetIntValue();
                    string strValue = cSheetData.arrCellData[nRow, 3].GetStrValue();

                    if (string.IsNullOrEmpty(strValue))
                    {
                        writer.WriteLine("\tint32 {0};", strName);
                        strCppFunction += string.Format("\t{0} = FCString::Atoi(*TableInfo[{1}].arrColData[2]);\n", strName, nRow);
                    }
                    else
                    {
                        writer.WriteLine("\tFString {0};", strName);
                        strCppFunction += string.Format("\t{0} = TableInfo[{1}].arrColData[3];\n", strName, nRow);
                    }
                }

                writer.WriteLine();
                writer.WriteLine("\tvoid SetInfo(const TArray<struct FRowDataInfo>& TableInfo);");
                writer.WriteLine("};");
            }

            strPath = string.Format("{0}/CConstData.cpp", relativePath);

            using (StreamWriter writer = new StreamWriter(File.Open(strPath, FileMode.Create), Encoding.Unicode))
            {
                writer.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                writer.WriteLine("// Drum.");
                writer.WriteLine("");

                writer.WriteLine("#include \"CConstData.h\"");
                writer.WriteLine("#include \"DataLoadLib/GlobalDataStruct.h\"");
                writer.WriteLine("");
                writer.Write(strCppFunction);
                writer.WriteLine("}");
            }
        }
    }
}
