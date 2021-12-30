using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data;
using DataLoadLib.Global;
using System.IO;
using System.Text.RegularExpressions;

namespace DataTool.Global
{
    class DBInfo
    {
        public string host { get; private set; } 
        public string database { get; private set; }
        public string uid { get; private set; }
        public string pwd { get; private set; }

        public DBInfo(string host, string database, string uid, string pwd)
        {
            this.host = host;
            this.database = database;
            this.uid = uid;
            this.pwd = pwd;
        }
    }

    class DBManager
    {
        SqlConnection connection;
        DBInfo dbInfo;

        public DBManager(string serverName)
        {
            MakeDBInfos(serverName);

            if (serverName == "none")
                return;

            connection = new SqlConnection(string.Format("Server = {0}; Database={1}; uid={2}; pwd={3}", dbInfo.host, dbInfo.database, dbInfo.uid, dbInfo.pwd));
        }

        ~DBManager()
        {
        }

        public SqlConnection GetConnection()
        {
            return connection;
        }

        public void CreateTable(SheetData cSheetData)
        {
            StringBuilder stringBuilder = new StringBuilder();
            try
            {
                stringBuilder.AppendFormat("IF OBJECT_ID ('{0}','U') IS NULL", cSheetData.strName);
                stringBuilder.AppendLine().Append("BEGIN").AppendLine();
                stringBuilder.AppendFormat("CREATE TABLE {0} (", cSheetData.strName);

                bool isContainsStatus = false;

                foreach (ColData colData in cSheetData.listColData)
                {
                    if (colData.eTargetType == ETargetType.CLIENT || colData.eTargetType == ETargetType.NONE || colData.eTargetType == ETargetType.MAX)
                        continue;

                    stringBuilder.AppendLine();

                    string colName = ToLowercaseNaming(colData.strExcelColName);

                    switch (colData.eDataType)
                    {
                        case EDataType.INT:
                        case EDataType.ENUM:                        
                            stringBuilder.AppendFormat("[{0}] INT NOT NULL ,", colName);
                            break;
                        case EDataType.FLOAT:
                            stringBuilder.AppendFormat("[{0}] FLOAT NOT NULL ,", colName);
                            break;
                        case EDataType.BOOL:
                            stringBuilder.AppendFormat("[{0}] BIT NOT NULL ,", colName);
                            break;
                        case EDataType.STRING:
                            if(colName.Contains("_dt") || colName.Contains("_date"))
                            {
                                stringBuilder.AppendFormat("[{0}] DATETIME2(0) NULL ,", colName);
                            }
                            else if (colName == "status")
                            {
                                isContainsStatus = true;
                                stringBuilder.AppendFormat("[{0}] NVARCHAR(1) NOT NULL DEFAULT 'A' ,", colName);
                            }
                            else
                            {
                                stringBuilder.AppendFormat("[{0}] NVARCHAR(50) NOT NULL ,", colName);
                            }
                            break;

                        default:
                            throw new System.Exception(string.Format("{0} 시트 UID : {1}컬럼 데이터 타입이 잘못 되었습니다.", cSheetData.strName, colData.strExcelColName));
                    }
                }

                if (!isContainsStatus)
                {
                    stringBuilder.AppendFormat("[status] NVARCHAR(1) NOT NULL DEFAULT 'A' ,");
                }

                stringBuilder.AppendFormat("[reg_dt] DATETIME2(0) NOT NULL DEFAULT GETDATE(), ");
                stringBuilder.AppendFormat("PRIMARY KEY ([{0}]) );", cSheetData.listColData[0].strExcelColName);
                stringBuilder.AppendLine().Append("END");
            }
            catch ( Exception e)
            {
                throw new System.Exception(string.Format("{0} 테이블 create 쿼리 생성에 실패했습니다. 이유 : {1}.", cSheetData.strName, e.Message));
            }

            ExecuteQuery(stringBuilder.ToString(), cSheetData.strName);
        }

        public static string ToLowercaseNaming(string str)
        {
            var r = new Regex(@"
            (?<=[A-Z])(?=[A-Z][a-z]) |
                (?<=[^A-Z])(?=[A-Z]) |
                (?<=[A-Za-z])(?=[^A-Za-z])", RegexOptions.IgnorePatternWhitespace);

            string lowerStr = r.Replace(str, "_").ToLower();

            bool runLoop = true;

            while (runLoop)
            {
                string beforStr = lowerStr;
                lowerStr = lowerStr.Replace("__", "_");

                if (beforStr.Equals(lowerStr))
                {
                    runLoop = false;
                }
            }

            return lowerStr;
        }

        public void InsertData(SheetData cSheetData)
        {
            const int INSERT_ROW_ONE_TIME = 500;
            int rowSplitCount = cSheetData.nRowCount / INSERT_ROW_ONE_TIME + 1;

            for (int i = 0; i < rowSplitCount; i++)
            {
                StringBuilder stringBuilder = new StringBuilder();
                try
                {
                    stringBuilder.AppendFormat("insert into {0}(", cSheetData.strName);
                    foreach (ColData colData in cSheetData.listColData)
                    {
                        if (colData.eTargetType == ETargetType.CLIENT || colData.eTargetType == ETargetType.NONE || colData.eTargetType == ETargetType.MAX)
                            continue;

                        stringBuilder.Append("[").Append(ToLowercaseNaming(colData.strExcelColName)).Append("],");
                    }

                    stringBuilder.Length--;
                    stringBuilder.AppendFormat(") values ");

                    int temMaxRowCount = cSheetData.nRowCount > (i + 1) * INSERT_ROW_ONE_TIME ? (i + 1) * INSERT_ROW_ONE_TIME : cSheetData.nRowCount;

                    for (int nRow = i * INSERT_ROW_ONE_TIME; nRow < temMaxRowCount; ++nRow)
                    {
                        stringBuilder.AppendLine();
                        stringBuilder.Append("(");
                        for (int nCol = 0; nCol < cSheetData.nColCount; ++nCol)
                        {
                            var colData = cSheetData.listColData[nCol];
                            if (colData.eTargetType == ETargetType.CLIENT || colData.eTargetType == ETargetType.NONE || colData.eTargetType == ETargetType.MAX)
                                continue;

                            if (cSheetData.arrCellData[nRow, nCol] == null)
                            {
                                throw new System.Exception(string.Format("{0} 시트 UID : {1} {2} 컬럼 데이터 타입이 잘못 되었습니다.",
                                        cSheetData.strName, cSheetData.arrCellData[nRow, 0].GetIntValue(), colData.strExcelColName));
                            }

                            switch (colData.eDataType)
                            {
                                case EDataType.INT:
                                case EDataType.ENUM:
                                    stringBuilder.Append(cSheetData.arrCellData[nRow, nCol].GetIntValue()).Append(",");
                                    break;
                                case EDataType.FLOAT:
                                    stringBuilder.Append(cSheetData.arrCellData[nRow, nCol].GetFloatValue()).Append(",");
                                    break;
                                case EDataType.BOOL:
                                    int boolValue = cSheetData.arrCellData[nRow, nCol].GetBoolValue() ? 1: 0;
                                    stringBuilder.Append(boolValue).Append(",");
                                    break;
                                case EDataType.STRING:
                                    if (cSheetData.arrCellData[nRow, nCol].GetStrValue() == "null" || cSheetData.arrCellData[nRow, nCol].GetStrValue() == "NULL")
                                    {
                                        stringBuilder.AppendFormat("{0},", cSheetData.arrCellData[nRow, nCol].GetStrValue());
                                    }
                                    else
                                    {
                                        stringBuilder.AppendFormat("N'{0}',", cSheetData.arrCellData[nRow, nCol].GetStrValue());
                                    }
                                    break;

                                default:
                                    throw new System.Exception(string.Format("{0} 시트 UID : {1} {2} 컬럼 데이터 타입이 잘못 되었습니다.", cSheetData.strName, cSheetData.arrCellData[nRow, 0].GetIntValue(), colData.strExcelColName));
                            }
                        }
                        stringBuilder.Length--;
                        stringBuilder.Append("),");
                    }
                    stringBuilder.Length--;
                }
                catch (Exception e)
                {
                    throw new System.Exception(string.Format("{0} insert 쿼리 생성에 실패했습니다. 이유 : {1}.", cSheetData.strName, e.Message));
                }

                ExecuteQuery(stringBuilder.ToString(), cSheetData.strName);
            }
        }

        public void DeleteData(SheetData cSheetData)
        {
            ExecuteQuery(string.Format("delete from {0} where {1} IS NOT NULL", cSheetData.strName, cSheetData.listColData[0].strExcelColName), cSheetData.strName);
        }
        private int ExecuteQuery(string query, string sheetName)
        {
            try
            {
                return new SqlCommand(query, connection).ExecuteNonQuery();
            }
            catch (Exception e)
            {
                if (!Directory.Exists(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_LOG)))
                    Directory.CreateDirectory(GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_LOG));

                using (StreamWriter writer = new StreamWriter(File.Open(string.Format("{0}/{1}.log", GlobalFunctions.MakeAbsolutePath(GlobalVar.PATH_SERVER_LOG), sheetName), FileMode.Append), new UTF8Encoding(false)))
                {
                    writer.Write(e.Message);
                    writer.WriteLine();
                    writer.Write(e.ToString());
                    writer.WriteLine();
                    writer.Write(query);
                    writer.WriteLine();
                    writer.Close();
                }
                throw e;
            }
        }

        private void MakeDBInfos(string serverName)
        {
            switch (serverName)
            {
                case "none":
                    break;
                case "qa":
                    dbInfo = new DBInfo("172.20.40.22", "5qa_da_data_db", "SA", "Spwj7720!");
                    break;
                case "real":
                    dbInfo = new DBInfo("172.20.40.225", "dev_da_data_db", "SA", "Spwj7720!");
                    break;
                case "local":
                    dbInfo = new DBInfo("172.20.41.156", "local_da_data_db", "SA", "Spwj7720!");
                    break;
                case "dev":
                default:
                    dbInfo = new DBInfo("172.20.40.224", "dev_da_data_db", "SA", "Spwj7720!");
                    break;
            }
        }
    }

}
