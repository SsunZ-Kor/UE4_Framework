#include "CDirectoryStatVisitor.h"
#include "CBinaryDataRegistry.h"
#include "DataLoadEditor/DataLoadEditorInfo.h"
#include "../DataLoadEditorInfo.h"

CDirectoryStatVisitor::CDirectoryStatVisitor()
	: m_arrExtention({ DataLoadEditorInfo::BYTE_EXTS, DataLoadEditorInfo::UASSET_EXTS })
{ }

bool CDirectoryStatVisitor::Visit(const TCHAR* FilenameOrDirectory, const FFileStatData& StatData)
{
	for(int i = 0 ; i < m_arrExtention.Num() ; ++i)
	{
		if(FPaths::GetExtension(FilenameOrDirectory).Equals(m_arrExtention[i]))
		{
			LOGDLE(TEXT("Name : '%s' Stat Size '%lld' ModificationTime : '%s' ModifyTick : '%lld'"),
				FilenameOrDirectory,
				StatData.FileSize,
				*StatData.ModificationTime.ToString(),
				StatData.ModificationTime.GetTicks());

			auto* reg = CBinaryDataRegistry::Instance();
			if(reg == nullptr)
				return false;

			reg->CheckFiles(FString(FilenameOrDirectory), StatData, i);
			
			return true;
		}
	}	

	return true;
}