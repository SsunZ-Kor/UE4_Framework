using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Threading;

using DataTool.Global;
using DataLoadLib.Global;
using Excel = Microsoft.Office.Interop.Excel;
using System.IO;
using System.Windows.Forms;

namespace DataTool
{
    public class CProtocolData : CDataBase
    {
        class ProtoData
        {
            public string name;
            public int cmd;
            public string dataType;
            public string data;

            public ProtoData(string name, int cmd, string dataType, string data)
            {
                this.name = name;
                this.cmd = cmd;
                this.dataType = dataType;
                this.data = data;
            }
        }

        class StructureData
        {
            public string name;
            public string dataType;
            public string data;

            public StructureData(string name, string dataType, string data)
            {
                this.name = name;
                this.dataType = dataType;
                this.data = data;
            }
        }
        public SheetData ShardStructSheetDatas { get; protected set; } = null;
        public SheetData ProtocolDescSheetDatas { get; protected set; } = null;

        Dictionary<string, List<StructureData>> structureDatas = new Dictionary<string, List<StructureData>>();

        // key : sheetName , protocolName, cmd
        private Dictionary<string, Dictionary<string, Dictionary<int, List<ProtoData>>>> reqProtoDatas = new Dictionary<string, Dictionary<string, Dictionary<int, List<ProtoData>>>>();
        private Dictionary<string, Dictionary<string, Dictionary<int, List<ProtoData>>>> respProtoDatas = new Dictionary<string, Dictionary<string, Dictionary<int, List<ProtoData>>>>();

        public CProtocolData(ExcelManager cMgr, string strFile, EventHandler cEvtHandler) 
            : base(cMgr, strFile, cEvtHandler)
        {
            Type = EExcelType.TYPE;
        }

        public override void LoadExcel()
        {
            //try
            //{
            //    if (m_cMgr == null || string.IsNullOrEmpty(FullFileName))
            //        return;

            //    SetExcelApplicationReset();

            //    m_cEvtHandler?.ChangeStatus?.Invoke(string.Format(GlobalVar.FMT_LOADING_FILE, FullFileName));

            //    Excel.Range excelRange;
            //    m_excelWorkBook = m_excelApplication.Workbooks.Open(FullFileName, 0, true);

            //    int nIndex = 0;

            //    SheetDatas = new List<SheetData>();

            //    foreach (Excel.Worksheet sheet in m_excelWorkBook.Sheets)
            //    {
            //        SheetData cData = new SheetData();
            //        string strName = sheet.Name;
            //        bool isSetData = false;

            //        excelRange = sheet.get_Range("A1").SpecialCells(Excel.XlCellType.xlCellTypeLastCell);

            //        if (GlobalFunctions.IsTableSheet(sheet.Name))
            //        {
            //            cData = new SheetData();
            //            SetStruct(sheet, ref cData, excelRange);
            //        } 
            //        else if (GlobalFunctions.IsSharedStructureSheet(sheet.Name))
            //        {
            //            cData = new SheetData();
            //            SetSharedStruct(sheet, ref cData, excelRange);

            //            cData.strName = strName;
            //            ShardStructSheetDatas = cData;

            //            isSetData = true;
            //        }
            //        else if (IsProtocolDesc(sheet.Name))
            //        {
            //            cData = new SheetData();
            //            SetProtocolDescStruct(sheet, ref cData, excelRange);

            //            cData.strName = strName;
            //            ProtocolDescSheetDatas = cData;

            //            isSetData = true;
            //        }

            //        if (cData != null && cData.listColData != null && cData.listColData.Count > 0 && isSetData == false)
            //        {
            //            cData.strName = strName;
            //            SheetDatas.Add(cData);
            //        }

            //        ++nIndex;
            //    }

            //    m_cEvtHandler?.ChangeProgress?.Invoke();
            //    m_cEvtHandler?.ChangeStatus?.Invoke(string.Format(GlobalVar.FMT_LOADEND_FILE, FullFileName));
            //    ClearExcelApplication();
            //} 
            //catch (Exception e)
            //{
            //    m_cEvtHandler.ShowMessageBox?.Invoke(e.Message);
            //}
            //finally
            //{
            //    ClearExcelApplication();
            //}
            
        }

        private bool IsProtocolDesc(string strSheetName)
        {
            if (strSheetName.StartsWith("_$$_"))
                return true;

            return false;
        }

        #region Protocol

        protected override bool SetStruct(Excel.Worksheet sheet, ref SheetData cSheetData, Excel.Range range)
        {
            try
            {
                if (range.Row <= 1 || range.Column < 4)
                {
                    cSheetData.nRowCount = 0;
                    cSheetData.nColCount = 0;
                    cSheetData.listColData.Clear();
                    cSheetData.arrCellData = null;

                    return false;
                }
                // 참조 테이블 정보 가져오기
                for (int nColl = 0; nColl < range.Column; ++nColl)
                {
                    Excel.Range dataRange;
                    dataRange = sheet.get_Range(GlobalFunctions.GetCellName(1, nColl));
                    string strExcelColName = dataRange.Text;

                    var cData = new ColData();
                    cData.strExcelColName = strExcelColName;
                    cData.strTypeName = string.Empty;
                    cData.nColIndex = nColl;
                    cData.eDataType = GlobalFunctions.GetProtocolDataType(strExcelColName);
                    cData.eTargetType = ETargetType.ALL;

                    if (cData.eDataType == EDataType.MAX)
                        continue;

                    cSheetData.listColData.Add(cData);
                }

                cSheetData.nRowCount = range.Row - 1;
                cSheetData.nColCount = cSheetData.listColData.Count;
                cSheetData.arrCellData = new CellData[cSheetData.nRowCount, cSheetData.nColCount];

                for (int nRow = 2; nRow <= range.Row; ++nRow)
                {
                    int nIndex = 0;
                    for (int nCol = 0; nCol < cSheetData.nColCount; ++nCol)
                    {
                        if (cSheetData.listColData[nCol].eDataType == EDataType.MAX)
                            continue;

                        Excel.Range dataRange;
                        dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow, cSheetData.listColData[nCol].nColIndex));

                        CellData cData = new CellData();
                        cData.SetValue(dataRange.Text, cSheetData.listColData[nCol].eDataType);
                        cSheetData.arrCellData[nRow - 2, nIndex++] = cData;
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CProtocolData:SetStruct(), {0}, {1}", cSheetData.strName, e.Message));
            }
            
            return true;
        }

        public override void MakeSourceCode()
        {
            try
            {
                m_cEvtHandler?.ChangeStatus?.Invoke(string.Format(GlobalVar.FMT_PROCESS_FILE, "Protocol"));
                foreach (SheetData sheetData in this.SheetDatas)
                {
                    if (sheetData == null)
                        continue;

                    MakeDataDictionary(sheetData);                    
                }
                MakeSharedStructDataDictionary();

                WriteSharedStructJavaFile();
                WriteSharedStructCSFile();

                WriteJavaFile();
                WriteCSFile();

                WriteProtocolDescDataToJavaEnumFile();
                WriteProtocolDescDataToJavaScriptEnumFile();
            }
            catch (Exception e)
            {
                m_cEvtHandler?.ShowMessageBox?.Invoke(e.Message);
            }
            
        }

        private void MakeDataDictionary(SheetData sheetData)
        {
            try
            {
                string beforName = "_init_";
                int beforCmd = 99999999;
                                
                Dictionary<string, Dictionary<int, List<ProtoData>>> reqProtoSheetDatas = new Dictionary<string, Dictionary<int, List<ProtoData>>>();                
                Dictionary<string, Dictionary<int, List<ProtoData>>> respProtoSheetDatas = new Dictionary<string, Dictionary<int, List<ProtoData>>>();

                for (int row = 0; row < sheetData.nRowCount; row++)
                {
                    string protocolName = sheetData.arrCellData[row, 0].GetStrValue();

                    string name = sheetData.arrCellData[row, 0].GetStrValue();
                    int cmd = sheetData.arrCellData[row, 1].GetIntValue();
                    string dataType = sheetData.arrCellData[row, 2].GetStrValue();
                    string data = sheetData.arrCellData[row, 3].GetStrValue();

                    if (string.IsNullOrWhiteSpace(name))
                    {
                        if (beforName == "_init_")
                            continue;
                        else
                            name = beforName;
                    }
                    else
                    {
                        beforName = name;
                    }

                    if (cmd == 0 && beforCmd != 99999999)
                        cmd = beforCmd;
                    else
                        beforCmd = cmd;

                    if (string.IsNullOrWhiteSpace(dataType) || string.IsNullOrWhiteSpace(data))
                    {
                        if (reqProtoSheetDatas.ContainsKey(name))
                        {
                            if(reqProtoSheetDatas[name].ContainsKey(cmd))
                                continue;
                        }

                        if (respProtoSheetDatas.ContainsKey(name))
                        {
                            if (respProtoSheetDatas[name].ContainsKey(cmd))
                                continue;
                        }
                    }

                    ProtoData protoData = new ProtoData(name, cmd, dataType, data);

                    if (!reqProtoSheetDatas.ContainsKey(name) && !respProtoSheetDatas.ContainsKey(name))
                    {
                        reqProtoSheetDatas.Add(name, new Dictionary<int, List<ProtoData>>());
                        reqProtoSheetDatas[name].Add(cmd, new List<ProtoData>());
                        reqProtoSheetDatas[name][cmd].Add(protoData);
                    }
                    else if (reqProtoSheetDatas.ContainsKey(name) && respProtoSheetDatas.ContainsKey(name))
                    {
                        respProtoSheetDatas[name][cmd].Add(protoData);
                    }
                    else if (reqProtoSheetDatas.ContainsKey(name) && !respProtoSheetDatas.ContainsKey(name))
                    {
                        if (!reqProtoSheetDatas[name].ContainsKey(cmd))
                        {
                            respProtoSheetDatas.Add(name, new Dictionary<int, List<ProtoData>>());
                            respProtoSheetDatas[name].Add(cmd, new List<ProtoData>());
                            respProtoSheetDatas[name][cmd].Add(protoData);
                        }
                        else if (reqProtoSheetDatas[name].ContainsKey(cmd))
                        {
                            reqProtoSheetDatas[name][cmd].Add(protoData);
                        }
                    }
                }

                reqProtoDatas.Add(sheetData.strName, reqProtoSheetDatas);
                respProtoDatas.Add(sheetData.strName, respProtoSheetDatas);
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("MakeDataDictionary() fail, {0} 데이타가 잘못됐습니다, {1} , ", sheetData.strName, e.Message));
            }
        }


        private void WriteCSFile()
        {
            try
            {
                if (!Directory.Exists(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_PROTOCOL_CS_FILE)))
                    Directory.CreateDirectory(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_PROTOCOL_CS_FILE));

                foreach (KeyValuePair<string, Dictionary<string, Dictionary<int, List<ProtoData>>>> reqProtoSheetData in reqProtoDatas)
                {
                    string sheetName = reqProtoSheetData.Key.Trim();
                    string reqFileName = string.Format("{0}/Protocol_{1}.cs", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_PROTOCOL_CS_FILE), sheetName);

                    using (StreamWriter file = new StreamWriter(File.Open(reqFileName, FileMode.Create), Encoding.Unicode))
                    {
                        //file.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                        file.WriteLine("");
                        file.WriteLine("using System.Collections.Generic;");
                        file.WriteLine("using DataFileEnum;");
                        file.WriteLine("namespace ProjectS.Protocol");
                        file.WriteLine("{");

                        foreach (KeyValuePair<string, Dictionary<int, List<ProtoData>>> datas in reqProtoSheetData.Value)
                        {
                            foreach (KeyValuePair<int, List<ProtoData>> dataList in datas.Value)
                            {
                                file.WriteLine("\t/// <summary>");
                                file.WriteLine(string.Format("\t/// {0} : {1}", sheetName, dataList.Key));
                                file.WriteLine("\t/// </summary>");
                                file.WriteLine(string.Format("\tpublic class {0} : CProtocolBase", m_cMgr.LowerFirstChar(datas.Key)));
                                file.WriteLine("\t{");
                                
                                foreach (ProtoData data in dataList.Value)
                                {
                                    file.WriteLine("\t"+m_cMgr.MakeLineOfCSCodeByDataType(data.dataType, data.data));
                                }
                                file.WriteLine("");
                                file.WriteLine(string.Format("\t\tpublic {0}()", m_cMgr.LowerFirstChar(datas.Key)));
                                file.WriteLine("\t\t{");
                                file.WriteLine(string.Format("\t\t\t this.cmd = {0};", dataList.Key));
                                file.WriteLine("\t\t}");
                                file.WriteLine("");
                                //start resp

                                file.WriteLine("\t\tpublic class result : CResponseDataBase");
                                file.WriteLine("\t\t{");
                                if (!respProtoDatas[sheetName][datas.Key].ContainsKey(dataList.Key + 1))
                                {
                                    throw new System.Exception(string.Format("resp cmd 는 req cmd+1 이여야 합니다. {0},{1} , ", sheetName, datas.Key));
                                }

                                foreach (ProtoData data in respProtoDatas[sheetName][datas.Key][dataList.Key+1])
                                {
                                    file.WriteLine("\t\t" + m_cMgr.MakeLineOfCSCodeByDataType(data.dataType, data.data));
                                }
                                file.WriteLine("\t\t}");

                                //end resp

                                file.WriteLine("\t}");
                            }
                        }

                        file.WriteLine("}");
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CProtocolData:WriteCSFile(), {0}",  e.Message));
            }
        }

        private void WriteJavaFile()
        {
            try
            {
                foreach (KeyValuePair<string, Dictionary<string, Dictionary<int, List<ProtoData>>>> reqProtoSheetData in reqProtoDatas)
                {
                    if (reqProtoSheetData.Key == "LoginServer" || reqProtoSheetData.Key == "ChatServer")
                        continue;

                    foreach (KeyValuePair<string, Dictionary<int, List<ProtoData>>> datas in reqProtoSheetData.Value)
                    {
                        string className = m_cMgr.UpperFirstChar(datas.Key.Trim());
                        string reqFileName = string.Format("{0}/{1}Req.java", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_PROTOCOL_DATA), className);

                        using (StreamWriter reqFile = new StreamWriter(File.Open(reqFileName, FileMode.Create), new UTF8Encoding(false)))
                        {
                            //reqFile.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                            reqFile.WriteLine("");

                            reqFile.WriteLine("package snowpipe.game.server.protocol.generated;");
                            reqFile.WriteLine();
                            reqFile.WriteLine("import snowpipe.common.protocol.generated.sharedStructure.*;");
                            reqFile.WriteLine("import snowpipe.common.protocol.Req;");
                            reqFile.WriteLine("import java.util.List;");
                            reqFile.WriteLine("import java.util.Date;");
                            reqFile.WriteLine();

                            reqFile.WriteLine(string.Format("public class {0}Req extends Req", className));
                            reqFile.WriteLine("{");

                            foreach (List<ProtoData> dataList in datas.Value.Values)
                            {
                                foreach (ProtoData data in dataList)
                                {
                                    reqFile.WriteLine(m_cMgr.MakeLineOfJavaCodeByDataType(data.dataType, data.data));
                                }
                            }

                            reqFile.WriteLine("\t@Override");
                            reqFile.WriteLine("\tpublic boolean isReceivedAllField()");
                            reqFile.WriteLine("\t{");
                            reqFile.WriteLine("\t\treturn true;");
                            reqFile.WriteLine("\t}");

                            reqFile.WriteLine("}");
                        }
                    }
                }

                foreach (KeyValuePair<string, Dictionary<string, Dictionary<int, List<ProtoData>>>> respProtoSheetData in respProtoDatas)
                {
                    if (respProtoSheetData.Key == "LoginServer" || respProtoSheetData.Key == "ChatServer")
                        continue;

                    foreach (KeyValuePair<string, Dictionary<int, List<ProtoData>>> datas in respProtoSheetData.Value)
                    {
                        string className = m_cMgr.UpperFirstChar(datas.Key.Trim());
                        string respFileName = string.Format("{0}/{1}Resp.java", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_PROTOCOL_DATA), className);

                        using (StreamWriter respFile = new StreamWriter(File.Open(respFileName, FileMode.Create), new UTF8Encoding(false)))
                        {
                            //respFile.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                            respFile.WriteLine("");

                            respFile.WriteLine("package snowpipe.game.server.protocol.generated;");
                            respFile.WriteLine();
                            respFile.WriteLine("import snowpipe.common.server.Resp;");                            
                            
                            respFile.WriteLine();

                            respFile.WriteLine(string.Format("public class {0}Resp extends Resp<{0}RespData>", className));
                            respFile.WriteLine("{");

                            respFile.WriteLine(string.Format("\tpublic {0}Resp()", className));
                            respFile.WriteLine("\t{");
                            respFile.WriteLine(string.Format("\t\tsuper(new {0}RespData());", className));
                            respFile.WriteLine("\t}");

                            respFile.WriteLine("}");
                            respFile.WriteLine();
                        }

                        string respDataFileName = string.Format("{0}/{1}RespData.java", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_PROTOCOL_DATA), className);

                        List<string> constructStringList = new List<string>();

                        using (StreamWriter respDataFile = new StreamWriter(File.Open(respDataFileName, FileMode.Create), new UTF8Encoding(false)))
                        {
                            respDataFile.WriteLine("package snowpipe.game.server.protocol.generated;");
                            respDataFile.WriteLine();
                            respDataFile.WriteLine("import snowpipe.common.protocol.generated.sharedStructure.*;");                            
                            respDataFile.WriteLine("import snowpipe.game.server.service.common.RespData;");
                            respDataFile.WriteLine("import java.util.*;");

                            respDataFile.WriteLine("public class {0}RespData extends RespData", className);
                            respDataFile.WriteLine("{");

                            foreach (List<ProtoData> dataList in datas.Value.Values)
                            {
                                foreach (ProtoData data in dataList)
                                {
                                    respDataFile.WriteLine(m_cMgr.MakeLineOfJavaCodeByDataType(data.dataType, data.data, constructStringList));
                                }
                            }

                            respDataFile.WriteLine("\tpublic {0}RespData()",className);
                            respDataFile.WriteLine("\t{");
                            foreach(string str in constructStringList){
                                respDataFile.WriteLine("\t{0}", str);
                            }
                            respDataFile.WriteLine("\t}");



                            respDataFile.WriteLine("}");
                        }
                    }
                }

            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CProtocolData:WriteJavaFile(), {0}", e.Message));
            }
        }

        #endregion

        #region SharedStruct
        private bool SetSharedStruct(Excel.Worksheet sheet, ref SheetData cSheetData, Excel.Range range)
        {
            try
            {
                if (range.Row <= 1 || range.Column < 3)
                {
                    cSheetData.nRowCount = 0;
                    cSheetData.nColCount = 0;
                    cSheetData.listColData.Clear();
                    cSheetData.arrCellData = null;

                    return false;
                }

                // 참조 테이블 정보 가져오기
                for (int nColl = 0; nColl < range.Column; ++nColl)
                {
                    Excel.Range dataRange;
                    dataRange = sheet.get_Range(GlobalFunctions.GetCellName(1, nColl));
                    string strExcelColName = dataRange.Text;

                    var cData = new ColData();
                    cData.strExcelColName = strExcelColName;
                    cData.strTypeName = string.Empty;
                    cData.nColIndex = nColl;
                    cData.eDataType = GlobalFunctions.GetProtocolDataType(strExcelColName);
                    cData.eTargetType = ETargetType.ALL;

                    if (cData.eDataType == EDataType.MAX)
                        continue;

                    cSheetData.listColData.Add(cData);
                }

                cSheetData.nRowCount = range.Row - 1;
                cSheetData.nColCount = cSheetData.listColData.Count;
                cSheetData.arrCellData = new CellData[cSheetData.nRowCount, cSheetData.nColCount];

                for (int nRow = 2; nRow <= range.Row; ++nRow)
                {
                    int nIndex = 0;
                    for (int nCol = 0; nCol < cSheetData.nColCount; ++nCol)
                    {
                        if (cSheetData.listColData[nCol].eDataType == EDataType.MAX)
                            continue;

                        Excel.Range dataRange;
                        dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow, cSheetData.listColData[nCol].nColIndex));

                        CellData cData = new CellData();
                        cData.SetValue(dataRange.Text, cSheetData.listColData[nCol].eDataType);
                        cSheetData.arrCellData[nRow - 2, nIndex++] = cData;
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CSharedStructureData:SetStruct(), {0}, {1}", cSheetData.strName, e.Message));
            }

            return true;
        }

        private void MakeSharedStructDataDictionary()
        {
            string beforName = "_init_";

            try
            {
                for (int row = 0; row < ShardStructSheetDatas.nRowCount; row++)
                {
                    string name = ShardStructSheetDatas.arrCellData[row, 0].GetStrValue();
                    string dataType = ShardStructSheetDatas.arrCellData[row, 1].GetStrValue();
                    string data = ShardStructSheetDatas.arrCellData[row, 2].GetStrValue();

                    if (string.IsNullOrWhiteSpace(name))
                    {
                        if (beforName == "_init_")
                            continue;
                        else
                            name = beforName;
                    }
                    else
                    {
                        beforName = name;
                    }

                    if (string.IsNullOrWhiteSpace(dataType) || string.IsNullOrWhiteSpace(data))
                    {
                        if (structureDatas.ContainsKey(name))
                            continue;
                    }

                    if (!structureDatas.ContainsKey(name))
                        structureDatas.Add(name, new List<StructureData>());

                    structureDatas[name].Add(new StructureData(name, dataType, data));
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CSharedStructureData:MakeDataDictionary(), {0}, {1}", ShardStructSheetDatas.strName, e.Message));
            }
        }

        private void WriteSharedStructJavaFile()
        {
            try
            {
                foreach (KeyValuePair<string, List<StructureData>> datas in structureDatas)
                {
                    string className = datas.Key.Trim();
                    string fileName = string.Format("{0}/{1}.java", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_SHARED_DATA), className);
                    using (StreamWriter file = new StreamWriter(File.Open(fileName, FileMode.Create), new UTF8Encoding(false)))
                    {
                        //file.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                        file.WriteLine("");

                        file.WriteLine("package snowpipe.common.protocol.generated.sharedStructure;");
                        file.WriteLine();

                        file.WriteLine("import java.util.*;");                        
                        file.WriteLine();

                        file.WriteLine(string.Format("public class {0}", className));
                        file.WriteLine("{");

                        List<string> constructStringList = new List<string>();

                        foreach (StructureData data in datas.Value)
                        {
                            file.WriteLine(m_cMgr.MakeLineOfJavaCodeByDataType(data.dataType, data.data, constructStringList));
                        }

                        file.WriteLine("\tpublic {0}()", className);
                        file.WriteLine("\t{");
                        foreach (string str in constructStringList)
                        {
                            file.WriteLine("\t{0}", str);
                        }
                        file.WriteLine("\t}");

                        file.WriteLine("}");
                    }

                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CSharedStructureData:WriteJavaFile(), {0}", e.Message));
            }
        }

        private void WriteSharedStructCSFile()
        {
            try
            {
                if (!Directory.Exists(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_PROTOCOL_CS_FILE)))
                    Directory.CreateDirectory(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_PROTOCOL_CS_FILE));

                string fileName = string.Format("{0}/Protocol_SharedData.cs", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_CLIENT_PROTOCOL_CS_FILE));
                using (StreamWriter file = new StreamWriter(File.Open(fileName, FileMode.Create), Encoding.Unicode))
                {
                    //file.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                    file.WriteLine("");

                    file.WriteLine("using System.Collections.Generic;");
                    file.WriteLine("using UnityEngine;");
                    file.WriteLine("using DataFileEnum;");
                    file.WriteLine("using System;");
                    file.WriteLine("");
                    file.WriteLine("namespace ProjectS.Protocol");
                    file.WriteLine("{");

                    foreach (KeyValuePair<string, List<StructureData>> datas in structureDatas)
                    {
                        file.WriteLine(string.Format("\tpublic class {0}", datas.Key));
                        file.WriteLine("\t{");

                        foreach (StructureData data in datas.Value)
                        {
                            file.WriteLine("\t" + m_cMgr.MakeLineOfCSCodeByDataType(data.dataType, data.data));
                        }

                        file.WriteLine("\t}");
                    }

                    file.WriteLine("}");
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CSharedStructureData:WriteCSFile(), {0}", e.Message));
            }
        }

        #endregion

        #region ProtocolDesc
        private bool SetProtocolDescStruct(Excel.Worksheet sheet, ref SheetData cSheetData, Excel.Range range)
        {
            try
            {
                if (range.Row <= 1 || range.Column < 3)
                {
                    cSheetData.nRowCount = 0;
                    cSheetData.nColCount = 0;
                    cSheetData.listColData.Clear();
                    cSheetData.arrCellData = null;

                    return false;
                }

                // 참조 테이블 정보 가져오기
                for (int nColl = 0; nColl < range.Column; ++nColl)
                {

                    Excel.Range dataRange;
                    dataRange = sheet.get_Range(GlobalFunctions.GetCellName(1, nColl));
                    string strExcelColName = dataRange.Text;

                    if (string.IsNullOrWhiteSpace(strExcelColName))
                        continue;

                    var cData = new ColData();
                    cData.strExcelColName = strExcelColName;
                    cData.strTypeName = string.Empty;
                    cData.nColIndex = nColl;
                    cData.eDataType = GlobalFunctions.GetProtocolDescDataType(strExcelColName);
                    cData.eTargetType = ETargetType.ALL;

                    cSheetData.listColData.Add(cData);
                }

                cSheetData.nRowCount = range.Row - 1;
                cSheetData.nColCount = cSheetData.listColData.Count;
                cSheetData.arrCellData = new CellData[cSheetData.nRowCount, cSheetData.nColCount];

                for (int nRow = 2; nRow <= range.Row; ++nRow)
                {
                    int nIndex = 0;
                    for (int nCol = 0; nCol < cSheetData.nColCount; ++nCol)
                    {
                        if (cSheetData.listColData[nCol].eDataType == EDataType.MAX)
                            continue;

                        Excel.Range dataRange;
                        dataRange = sheet.get_Range(GlobalFunctions.GetCellName(nRow, cSheetData.listColData[nCol].nColIndex));

                        CellData cData = new CellData();
                        cData.SetValue(dataRange.Text, cSheetData.listColData[nCol].eDataType);
                        cSheetData.arrCellData[nRow - 2, nIndex++] = cData;
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CProtocolData:SetProtocolDescStruct(), {0}, {1}", cSheetData.strName, e.Message));
            }

            return true;
        }

        private void WriteProtocolDescDataToJavaEnumFile()
        {
            try
            {
                string strEnumName = "Protocol";
                string strFileName = string.Format("{0}/{1}.java", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_PROTOCOL_DESC_DATA), strEnumName);

                using (StreamWriter file = new StreamWriter(File.Open(strFileName, FileMode.Create), new UTF8Encoding(false)))
                {
                    if (ProtocolDescSheetDatas == null || ProtocolDescSheetDatas.listColData == null || ProtocolDescSheetDatas.arrCellData == null)
                        return;

                    //file.WriteLine(string.Format("// Generate By DataTool. {0}", DateTime.Now));
                    file.WriteLine("");
                    file.WriteLine("package snowpipe.common.protocol.generated;");
                    file.WriteLine("");
                    file.WriteLine("import java.util.Map;");
                    file.WriteLine("import java.util.HashMap;");

                    file.WriteLine(string.Format("public enum {0}", strEnumName));
                    file.WriteLine("{");
                    for (int i = 0; i < ProtocolDescSheetDatas.nRowCount; ++i)
                    {
                        if (ProtocolDescSheetDatas.arrCellData[i, 0] != null)
                        {
                            string name = ProtocolDescSheetDatas.arrCellData[i, 0].GetStrValue();
                            int value = ProtocolDescSheetDatas.arrCellData[i, 1].GetIntValue();

                            if (string.IsNullOrEmpty(name))
                                continue;

                            if (value >= 100000 && value < 200000)
                            {
                                if (ProtocolDescSheetDatas.listColData.Count > 2 && ProtocolDescSheetDatas.listColData[2].eDataType != EDataType.MAX)
                                {
                                    string desc = ProtocolDescSheetDatas.arrCellData[i, 2].GetStrValue();
                                    if (string.IsNullOrEmpty(desc))
                                        file.WriteLine(string.Format("\t{0}({1},\"\",true),", name, value));
                                    else
                                        file.WriteLine(string.Format("\t{0}({1},\"{2}\",true),", name, value, desc));
                                }
                                else
                                {
                                    file.WriteLine(string.Format("\t{0}({1},\"\",true),", name, value));
                                }
                            }
                            else
                            {
                                if (ProtocolDescSheetDatas.listColData.Count > 2 && ProtocolDescSheetDatas.listColData[2].eDataType != EDataType.MAX)
                                {
                                    string desc = ProtocolDescSheetDatas.arrCellData[i, 2].GetStrValue();
                                    if (string.IsNullOrEmpty(desc))
                                        file.WriteLine(string.Format("\t{0}({1},\"\"),", name, value));
                                    else
                                        file.WriteLine(string.Format("\t{0}({1},\"{2}\"),", name, value, desc));
                                }
                                else
                                {
                                    file.WriteLine(string.Format("\t{0}({1},\"\"),", name, value));
                                }
                            }

                        }
                    }
                    file.WriteLine("\t;");
                    file.WriteLine("");
                    file.WriteLine("private static final Map<Integer, Protocol> VALUE_AND_TYPE_MAP = new HashMap<>();");
                    file.WriteLine("static { for(Protocol type:values()) { VALUE_AND_TYPE_MAP.put(type.getValue(), type); } }");
                    file.WriteLine("private final int value;");
                    file.WriteLine("private final String description;");
                    file.WriteLine("private final boolean isBotProtocol;");
                    file.WriteLine("private Protocol(int protocolNo, String description) { this(protocolNo, description, false);}");
                    file.WriteLine("private Protocol(int protocolNo, String description, boolean isBotProtocol) { this.value = protocolNo; this.description = description; this.isBotProtocol = isBotProtocol;}");
                    file.WriteLine("public int getValue() { return value; }");
                    file.WriteLine("public String getDescription() { return description; }");
                    file.WriteLine("public int getRespValue() { return value+1; }");
                    file.WriteLine("public static Protocol valueOf(int protocolNo) { if(!VALUE_AND_TYPE_MAP.containsKey(protocolNo)) { throw new RuntimeException(\"invalid protocolNo: \" + protocolNo); } return VALUE_AND_TYPE_MAP.get(protocolNo); }");
                    file.WriteLine("public boolean isBotProtocol(){ return isBotProtocol; }");
                    file.WriteLine("public static boolean isExistProtocol(int protocolNo){ return VALUE_AND_TYPE_MAP.containsKey(protocolNo); }");
                    file.WriteLine("}");

                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CTypeData:WriteTypeDataToJavaEnumFile(), {0}, {1}", ProtocolDescSheetDatas.strName, e.Message));
            }
        }

        private void WriteProtocolDescDataToJavaScriptEnumFile()
        {
            try
            {
                string strEnumName = "Protocol";
                string strFileName = string.Format("{0}/{1}.js", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_ADMIN_PROTOCOL_DATA), strEnumName);

                using (StreamWriter file = new StreamWriter(File.Open(strFileName, FileMode.Create), new UTF8Encoding(false)))
                {
                    if (ProtocolDescSheetDatas == null || ProtocolDescSheetDatas.listColData == null || ProtocolDescSheetDatas.arrCellData == null)
                        return;

                    for (int i = 0; i < ProtocolDescSheetDatas.nRowCount; ++i)
                    {
                        if (ProtocolDescSheetDatas.arrCellData[i, 0] != null)
                        {
                            string name = ProtocolDescSheetDatas.arrCellData[i, 0].GetStrValue();
                            int value = ProtocolDescSheetDatas.arrCellData[i, 1].GetIntValue();

                            if (string.IsNullOrEmpty(name))
                                continue;

                            if (ProtocolDescSheetDatas.listColData.Count > 2 && ProtocolDescSheetDatas.listColData[2].eDataType != EDataType.MAX)
                            {
                                string desc = ProtocolDescSheetDatas.arrCellData[i, 2].GetStrValue();
                                if (string.IsNullOrEmpty(desc))
                                    file.WriteLine(string.Format("const protocol_{0} = {1};),", name, value));
                                else
                                    file.WriteLine(string.Format("const protocol_{0} = {1}; //{2}", name, value, desc));
                            }
                            else
                            {
                                file.WriteLine(string.Format("const protocol_{0} = {1};),", name, value));
                            }
                        }
                    }
                }
            }
            catch (Exception e)
            {
                throw new System.Exception(string.Format("CTypeData:WriteProtocolDescDataToJavaScriptEnumFile(), {0}, {1}", ProtocolDescSheetDatas.strName, e.Message));
            }
        }
        #endregion
    }
}
