#include "Testee/MyObject.h"
#include "TestUtil.h"
#include "Util/Core/LogUtilLib.h"

#include <UObject/Package.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestObjectCreate, "MyTests.Object.Create", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext);

// ~Single object tests Begin
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestObjectMarkPendingKill, "MyTests.Object.MarkPendingKill", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext);
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestObjectAddToRoot, "MyTests.Object.AddToRoot", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext);
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestQuickEditor, "MyTests.QuickEditor", EAutomationTestFlags::SmokeFilter | EAutomationTestFlags::EditorContext);
// ~Single object tests End

// ~Package tests Begin
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestPackage_Transient, "MyTests.Package.Transient", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext | EAutomationTestFlags::HighPriorityAndAbove);
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestPackage_CustomPackage, "MyTests.Package.CustomPackage", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext | EAutomationTestFlags::HighPriorityAndAbove);
// ~Package Tests End

bool FMyTestPackage_Transient::RunTest(const FString& Parameters)
{
	M_LOGFUNC();
	{
		M_LOGBLOCK(TEXT("******************* Logging transient package"));
		ULogUtilLib::LogObjectSafe(GetTransientPackage(), EMyLogObjectFlags::Full);
	}
	return true;
}

bool FMyTestPackage_CustomPackage::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	UPackage* MyPackage = nullptr;
	
	{
		M_LOGBLOCK(TEXT("******************* Create custom package"));
		MyPackage = CreatePackage(nullptr, nullptr);
	}

	{
		M_LOGBLOCK(TEXT("******************* Logging custom package"));
		ULogUtilLib::LogObjectSafe(MyPackage, EMyLogObjectFlags::Full);
	}

	{
		M_LOGBLOCK(TEXT("******************* Issuing command for checking state of the package"));
		ADD_LATENT_AUTOMATION_COMMAND(FLogObjectUntilInvalidLatentCommand{MyPackage});
	}

	UObject* MyObj = nullptr;
	{
		M_LOGBLOCK(TEXT("***************** Creating UObject inside MyPackage"));
		MyObj = NewObject<UMyObject>(MyPackage);
	}

	{
		M_LOGBLOCK(TEXT("***************** Issuing command for checking UObject"))
		ADD_LATENT_AUTOMATION_COMMAND(FLogObjectUntilInvalidLatentCommand{MyObj});
	}

	return true;
}

bool FMyTestObjectMarkPendingKill::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	UObject* Obj = nullptr;
	{
		M_LOGBLOCK(TEXT("******************** Logging object creation"));
		Obj = NewObject<UMyObject>(GetTransientPackage());
		ULogUtilLib::LogObjectSafe(Obj, EMyLogObjectFlags::Full);
	}

	{

		M_LOGBLOCK(TEXT("******************** Marking pending kill"));
		Obj->MarkPendingKill();
		ULogUtilLib::LogYesNo(FString(TEXT("IsPendingKill")), Obj->IsPendingKill());
		ULogUtilLib::LogObjectSafe(Obj, EMyLogObjectFlags::Full);
	}

	{
		ADD_LATENT_AUTOMATION_COMMAND(FLogObjectUntilInvalidLatentCommand{Obj});
	}
	return true;
}

bool FMyTestObjectAddToRoot::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	UObject* Obj = nullptr;
	{
		M_LOGBLOCK(TEXT("******************** Logging object creation"));
		Obj = NewObject<UMyObject>(GetTransientPackage());
		ULogUtilLib::LogObjectSafe(Obj, EMyLogObjectFlags::Full);
	}

	{

		M_LOGBLOCK(TEXT("******************** Add to root"));
		Obj->AddToRoot();
		ULogUtilLib::LogYesNo(FString(TEXT("IsRooted")), Obj->IsRooted());
		ULogUtilLib::LogObjectSafe(Obj, EMyLogObjectFlags::Full);
	}

	{
		ADD_LATENT_AUTOMATION_COMMAND(FLogObjectUntilInvalidLatentCommand{Obj});
	}

	{
		M_LOGBLOCK(TEXT("******************** Remove from root"));
		// What will be if we forgot to remove object from Root?
		Obj->RemoveFromRoot();
		ULogUtilLib::LogObjectSafe(Obj, EMyLogObjectFlags::Full);
	}
	return true;
}

bool FMyTestObjectCreate::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	

	{
		M_LOGBLOCK(TEXT("******************* Create UObject in transient package"));
		UObject* const MyObj_InTransientPackage = NewObject<UMyObject>(GetTransientPackage());
		{
			M_LOGBLOCK(TEXT("Default logging"));
			ULogUtilLib::LogObjectSafe(MyObj_InTransientPackage, EMyLogObjectFlags::Default);
		}
		{
			M_LOGBLOCK(TEXT("Full logging"));
			ULogUtilLib::LogObjectSafe(MyObj_InTransientPackage, EMyLogObjectFlags::Full);
		}
		ADD_LATENT_AUTOMATION_COMMAND(FLogObjectUntilInvalidLatentCommand{MyObj_InTransientPackage});
	}

	return true;
}

bool FMyTestQuickEditor::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	M_LOG(TEXT("Here you place ANY test (quick placeholder for tests)"));

	return true;
}
