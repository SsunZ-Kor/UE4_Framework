using System.Text;

namespace DataLoadLib.Global
{   
    public enum EDataType { NONE, INT, FLOAT, STRING, LONG, ENUM, BOOL,MAX };

    public enum EZoneType { None, ZoneKr, ZoneGlobal, ZoneJp};

    public class GlobalVariable
    {
        public const int MAX_STRING_COUNT = 256;
        public static byte[] SECURE_KEY = ASCIIEncoding.ASCII.GetBytes("*AAmxi:EpfHiyRni");
    }

    public struct DataInfo
    {
        public int nValue;
        public float fValue;
        public string strValue;
        public long lValue;
        public bool bValue;
        public EDataType eDataType;
    }

    public class TableInfo
    {
        private string[] arrSTR = null;
        private int[] arrINT = null;
        private float[] arrFLOAT = null;
        private long[] arrLONG = null;
        private bool[] arrBOOL = null;
        private int[] arrIndex = null;
        
        public string GetStrValue(int nIndex)
        {
            return arrSTR[arrIndex[nIndex]];
        }

        public int GetIntValue(int nIndex)
        {
            return arrINT[arrIndex[nIndex]];
        }

        public float GetFloatValue(int nIndex)
        {
            return arrFLOAT[arrIndex[nIndex]];
        }

        public bool GetBoolValue(int nIndex)
        {
            return arrBOOL[arrIndex[nIndex]];
        }

        public void SetValue(DataInfo[] arrDataInfos)
        {
            int nINTCount = 0;
            int nFLOATCount = 0;
            int nSTRCount = 0;
            int nLONGCount = 0;
            int nBOOLCount = 0;

            arrIndex = new int[arrDataInfos.Length];

            for (int i = 0; i < arrDataInfos.Length; ++i)
            {
                switch (arrDataInfos[i].eDataType)
                {
                case EDataType.FLOAT:
                    arrIndex[i] = nFLOATCount++;
                    break;
                case EDataType.INT:
                    arrIndex[i] = nINTCount++;
                    break;
                case EDataType.STRING:
                    arrIndex[i] = nSTRCount++;
                    break;
                case EDataType.LONG:
                    arrIndex[i] = nLONGCount++;
                    break;
                case EDataType.BOOL:
                    arrIndex[i] = nBOOLCount++;
                    break;
                }
            }

            if (nINTCount != 0)
                arrINT = new int[nINTCount];

            if (nFLOATCount != 0)
                arrFLOAT = new float[nFLOATCount];

            if (nSTRCount != 0)
                arrSTR = new string[nSTRCount];

            if(nLONGCount != 0)
                arrLONG = new long[nLONGCount];

            if (nBOOLCount != 0)
                arrBOOL = new bool[nBOOLCount];


            nINTCount = 0;
            nFLOATCount = 0;
            nSTRCount = 0;
            nLONGCount = 0;
            nBOOLCount = 0;

            for (int i = 0; i < arrDataInfos.Length; ++i)
            {
                switch (arrDataInfos[i].eDataType)
                {
                case EDataType.FLOAT:
                    arrFLOAT[nFLOATCount++] = arrDataInfos[i].fValue;
                    break;
                case EDataType.INT:
                    arrINT[nINTCount++] = arrDataInfos[i].nValue;
                    break;
                case EDataType.STRING:
                    arrSTR[nSTRCount++] = arrDataInfos[i].strValue;
                    break;
                case EDataType.LONG:
                    arrLONG[nLONGCount++] = arrDataInfos[i].lValue;
                    break;
                case EDataType.BOOL:
                    arrBOOL[nBOOLCount++] = arrDataInfos[i].bValue;
                    break;
                }
            }
        }
    }
}
