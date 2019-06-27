#include "Misc/AutomationTest.h"
#include "Util/Core/LogUtilLib.h"

#include "Testee/MyObject.h"

#include <UObject/Package.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestObjectCreate, "MyTests.Object.Create", EAutomationTestFlags::SmokeFilter | EAutomationTestFlags::EditorContext);
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestQuickEditor, "MyTests.QuickEditor", EAutomationTestFlags::SmokeFilter | EAutomationTestFlags::EditorContext);

bool FMyTestObjectCreate::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	{
		M_LOGBLOCK(TEXT("Log nullptr UObject"));
		ULogUtilLib::LogObjectSafe(nullptr);
	}

	{
		M_LOGBLOCK(TEXT("Create UObject in transient package"));
		UObject* const MyObj_InTransientPackage = NewObject<UMyObject>(GetTransientPackage());
		{
			M_LOGBLOCK(TEXT("Default logging"));
			ULogUtilLib::LogObjectSafe(MyObj_InTransientPackage, EMyLogObjectFlags::Default);
		}
		{
			M_LOGBLOCK(TEXT("Full logging"));
			ULogUtilLib::LogObjectSafe(MyObj_InTransientPackage, EMyLogObjectFlags::Full);
		}
	}

	return true;
}

bool FMyTestQuickEditor::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	M_LOG(TEXT("Here you place ANY test (quick placeholder for tests)"));

	return true;
}
