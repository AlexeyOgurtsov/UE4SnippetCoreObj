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

	double const SecondsElapsed = GetSecondsElapsed();
	bool const bTimeOver = IsTimeOver();

	// ~bShouldLog calculation Begin
	bool bShouldLog = false;
	if(bAlwaysLog)
	{
		bShouldLog = true;
	}
	else if(bTimeOver)
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
	else if(IsTimeOver())
	{
		M_LOG(TEXT("***** STOPPED because time over (%lf seconds elapsed, time quota is %s))"), SecondsElapsed, (MaxSeconds.IsSet() ? *FString::SanitizeFloat(MaxSeconds.GetValue()) : *FString(TEXT("No quota"))));
		return true;
	}
	else if(MaxIters.IsSet() && UpdateIndex == MaxIters.GetValue())
	{
		M_LOG(TEXT("**** STOPPED because max iters gained"));
		return true;
	}
	LastObjectState.UpdateFrom(ObjectToLog);
	return false;
}

bool FLogObjectUntilInvalidLatentCommand::IsTimeOver() const
{
	if(MaxSeconds.IsSet())
	{
		return (GetSecondsElapsed() >= MaxSeconds.GetValue());
	}
	else
	{
		return false;
	}
}

double FLogObjectUntilInvalidLatentCommand::GetSecondsElapsed() const
{
	return FPlatformTime::Seconds() - StartTime;
}