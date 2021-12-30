#include "Tests/AutomationCommon.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(DataLoadEditorTest, "DrumTest.DataLoadEditor.Test1",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool DataLoadEditorTest::RunTest(const FString& Parameters)
{
	GLog->Log("DrumTest.DataLoadEditor.Test1");
	return true;
}