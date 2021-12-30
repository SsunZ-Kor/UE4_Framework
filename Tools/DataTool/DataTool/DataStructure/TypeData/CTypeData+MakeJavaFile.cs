using System;
using DataTool.Global;
using DataLoadLib.Global;
using System.Threading;
using System.IO;

namespace DataTool
{
    public partial class CTypeData
    {
        public void WriteFileServerJavaFile()
        {
            foreach (SheetData cSheetData in this.SheetDatas)
            {
                new Thread(() =>
                {
                    string strEnumName = cSheetData.strName.Split('_')[1];
                    string strFileName = string.Format("{0}/{1}.java", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_SHARED_DATA), strEnumName);

                    using (StreamWriter file = new StreamWriter(File.Open(strFileName, FileMode.Create), new System.Text.UTF8Encoding(false)))
                    {
                        file.WriteLine("package snowpipe.common.protocol.generated.sharedStructure;");
                        file.WriteLine("import java.util.HashMap;");
                        file.WriteLine("import java.util.Map;");
                        file.WriteLine("import snowpipe.common.*;");
                        file.WriteLine();

                        try
                        {
                            if (cSheetData == null || cSheetData.listColData == null || cSheetData.arrCellData == null)
                                return;

                            file.WriteLine(string.Format("public enum {0} implements IntegerEnum", strEnumName));
                            file.WriteLine("{");
                            for (int i = 0; i < cSheetData.nRowCount; ++i)
                            {
                                if (cSheetData.arrCellData[i, 0] != null)
                                {
                                    int nValue = cSheetData.arrCellData[i, 0].GetIntValue();
                                    string strTypeName = cSheetData.arrCellData[i, 1].GetStrValue();

                                    if (string.IsNullOrEmpty(strTypeName))
                                        continue;

                                    string strComment = "";
                                    if (cSheetData.listColData.Count > 2 && cSheetData.listColData[2].eDataType != EDataType.MAX)
                                    {
                                        if (!string.IsNullOrEmpty(cSheetData.arrCellData[i, 2].GetStrValue()))
                                            strComment = cSheetData.arrCellData[i, 2].GetStrValue();
                                    }

                                    file.WriteLine(string.Format("\t{0}({1},\"{2}\"),", strTypeName, nValue, strComment));
                                }
                            }
                            file.WriteLine("\t;");
                            file.WriteLine("");

                            file.WriteLine(string.Format("private static final Map<Integer, {0}> VALUE_AND_TYPE_MAP = new HashMap<>();", strEnumName));
                            file.WriteLine(string.Format("static {{ for({0} type:values()) {{ VALUE_AND_TYPE_MAP.put(type.getValue(), type); }} }}", strEnumName));
                            file.WriteLine("private int value;");
                            file.WriteLine("private String name;");
                            file.WriteLine("private String description;");
                            file.WriteLine(string.Format("private {0}(int typeValue, String description) {{ this.value = typeValue; this.description = description; this.name = this.toString();}}", strEnumName));
                            file.WriteLine("public int getValue() { return value; }");
                            file.WriteLine("public String getName() { return name; }");
                            file.WriteLine("public String getDescription() { return description; }");
                            file.WriteLine(string.Format("public static {0} valueOf(int typeValue) {{ if(!VALUE_AND_TYPE_MAP.containsKey(typeValue)) {{ throw new RuntimeException(\"invalid typeValue: \" + typeValue); }} return VALUE_AND_TYPE_MAP.get(typeValue); }}", strEnumName));

                            file.WriteLine("}");
                        }
                        catch (Exception e)
                        {
                            throw new System.Exception(string.Format("CTypeData:WriteTypeDataToJavaEnumFile(), {0}, {1}", cSheetData.strName, e.Message));
                        }

                        file.WriteLine();
                    }
                }).Start();
            }
        }
    }
}
