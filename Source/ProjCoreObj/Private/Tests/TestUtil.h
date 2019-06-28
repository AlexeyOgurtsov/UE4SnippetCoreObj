#pragma once

#include "Misc/AutomationTest.h"
#include "UObject/ObjectMacros.h"
#include "GenericPlatform/GenericPlatformTime.h"

class UObject;

enum class ELogObjectCommandFlags
{
	None = 0,
	LogWhenFlagsChange = 1 << 0,
	AlwaysLog = 1 << 1,
	Default = LogWhenFlagsChange
};
ENUM_CLASS_FLAGS(ELogObjectCommandFlags);

struct FMyObjectState
{
	EObjectFlags Flags;
	EInternalObjectFlags InternalFlags;

	FMyObjectState(const UObject* InObject);
	void UpdateFrom(const UObject* InObject);
	bool HasStateChanged(const UObject* InObject);
};

/**
* TODO: How to get elapsed time?
*/
class FLogObjectUntilInvalidLatentCommand : public IAutomationLatentCommand
{
public:
	FLogObjectUntilInvalidLatentCommand(const UObject* InObjectToLog, ELogObjectCommandFlags InFlags = ELogObjectCommandFlags::Default, TOptional<double> InMaxSeconds = 60.0, TOptional<int32> InMaxIters = 5000) 
	: StartTime {FPlatformTime::Seconds()}
	, MaxSeconds{InMaxSeconds}
	, UpdateIndex{0}
	, ObjectToLog{InObjectToLog}
	, MaxIters{InMaxIters}
	, Flags{InFlags}
	, LastObjectState{InObjectToLog}
	{
		check(InObjectToLog);
	}

	bool Update() override;

private:
	double GetSecondsElapsed() const;
	bool IsTimeOver() const;

	double StartTime;
	TOptional<double> MaxSeconds;

	int32 UpdateIndex;

	const UObject* ObjectToLog;
	TOptional<int32> MaxIters;
	ELogObjectCommandFlags Flags;
	FMyObjectState LastObjectState;
};
