#include "Tests/AutomationCommon.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(BinaryDataSourceTest, "DrumTest.DataLoadLib.Test1",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool BinaryDataSourceTest::RunTest(const FString& Parameters)
{
	GLog->Log("DrumTest.DataLoadLib.Test1");
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(BinaryDataSourceTest2, "DrumTest.DataLoadLib.Test2",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool BinaryDataSourceTest2::RunTest(const FString& Parameters)
{
	GLog->Log("DrumTest.DataLoadLib.Test2");
	return false;
}
