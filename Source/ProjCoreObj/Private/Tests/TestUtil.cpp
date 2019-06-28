#include "TestUtil.h"
#include "Util/Core/LogUtilLib.h"

FMyObjectState::FMyObjectState(const UObject* InObject) 
{
	UpdateFrom(InObject);
}

void FMyObjectState::UpdateFrom(const UObject* InObject)
{
	check(InObject);
	Flags = InObject->GetFlags();
	InternalFlags = InObject->GetInternalFlags();
}

bool FMyObjectState::HasStateChanged(const UObject* InObject)
{
	if(InObject == nullptr) { return true; }
	bool const bObjectInvalid = (false == InObject->IsValidLowLevel());
	bool const bFlagsChanged = bObjectInvalid ? false : ( (Flags != InObject->GetFlags()) || (InternalFlags != InObject->GetInternalFlags()) );
	return bFlagsChanged;
}

bool FLogObjectUntilInvalidLatentCommand::Update()
{
	bool const bAlwaysLog = (Flags & ELogObjectCommandFlags::AlwaysLog) != ELogObjectCommandFlags::None;
	bool const bObjectInvalid = (false == ObjectToLog->IsValidLowLevel());

	// ~bShouldLog calculation Begin
	bool bShouldLog = false;
	if(bAlwaysLog)
	{
		bShouldLog = true;
	}
	else if(bObjectInvalid)
	{
		bShouldLog = true;
	}
	else if(LastObjectState.HasStateChanged(ObjectToLog))
	{
		bShouldLog = true;
	}
	if(bShouldLog)
	{
		ULogUtilLib::LogObjectSafe(ObjectToLog, EMyLogObjectFlags::Full);
	}
	// ~bShouldLog calcuation End

	M_LOG_IF(bShouldLog, TEXT("**** Waiting until object is invalid"));
	M_LOG_IF(bShouldLog, TEXT("**** UpdateIndex=%d"), UpdateIndex);

	UpdateIndex++;
	if(bObjectInvalid)
	{
		return true; // Stop
	}
	if(MaxIters.IsSet() && UpdateIndex == MaxIters.GetValue())
	{
		M_LOG(TEXT("**** STOPPED because max iters gained"));
		return true;
	}
	LastObjectState.UpdateFrom(ObjectToLog);
	return false;
}