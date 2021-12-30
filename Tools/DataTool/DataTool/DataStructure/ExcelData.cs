using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DataTool.Global;
using DataLoadLib.Global;

namespace DataTool
{
    public class CellData
    {
        private int         m_nValue = 0;
        private float       m_fValue = 0;
        private long        m_lValue = 0;
        private string      m_strValue = string.Empty;
        private bool        m_bValue = false;

        private EDataType   m_eDataType = EDataType.MAX;

        public string GetString()
        {
            string ret = string.Empty;
            switch(m_eDataType)
            {
            case EDataType.INT:
                ret = m_nValue.ToString();
                break;
            case EDataType.FLOAT:
                ret = m_fValue.ToString();
                break;
            case EDataType.STRING:
                ret = m_strValue;
                break;
            case EDataType.LONG:
                ret = m_lValue.ToString();
                break;
            case EDataType.BOOL:
                ret = m_bValue.ToString();
                break;
            }
            return ret;
        }

        public int GetIntValue()
        {
            return m_nValue;
        }

        public float GetFloatValue()
        {
            return m_fValue;
        }

        public string GetStrValue()
        {
            return m_strValue;
        }

        public long GetLongValue()
        {
            return m_lValue;
        }

        public bool GetBoolValue()
        {
            return m_bValue;
        }

        public bool SetValue(string text, EDataType dataType)
        {
            m_eDataType = dataType;            
            text = text.TrimEnd();
            switch(dataType)
            {
            case EDataType.INT:
                if(string.IsNullOrEmpty(text) == true)
                    m_nValue = 0;                     
                else
                {
                    if(int.TryParse(text, out m_nValue) == false)
                        return false;
                }                
                break;
            case EDataType.FLOAT:
                if(string.IsNullOrEmpty(text) == true)
                    m_fValue = 0;                     
                else
                {
                    if(float.TryParse(text, out m_fValue) == false)
                        return false;
                }
                break;
            case EDataType.LONG:
                if(string.IsNullOrEmpty(text) == true)
                    m_lValue = 0;
                else
                {
                    if(long.TryParse(text, out m_lValue) == false)
                        return false;
                }
                break;
            case EDataType.STRING:
                m_strValue = text;
                break;
            case EDataType.BOOL:
                if (string.IsNullOrEmpty(text) == true)
                    m_bValue = false;
                else
                {
                    if (bool.TryParse(text, out m_bValue) == false)
                        return false;
                }
                break;
            }

            return true;
        }
    }
    public class ColData
    {
        public EDataType        eDataType = EDataType.NONE;
        public ETargetType      eTargetType = ETargetType.NONE;
        public string           strExcelColName = string.Empty;
        public string           strTypeName = string.Empty;
        public int              nColIndex = 0;
        public string           strMemo = string.Empty;                
    }


    public class SheetData
    {
        public string                   strName = string.Empty;
        public List<ColData>            listColData = new List<ColData>();
        public CellData[,]              arrCellData = null;        
        public int                      nRowCount = 0;
        public int                      nColCount = 0;
    }
}
