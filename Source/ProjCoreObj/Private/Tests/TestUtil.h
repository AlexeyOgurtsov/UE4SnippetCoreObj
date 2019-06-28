#pragma once

#include "Misc/AutomationTest.h"
#include "UObject/ObjectMacros.h"

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
	FLogObjectUntilInvalidLatentCommand(const UObject* InObjectToLog, ELogObjectCommandFlags InFlags = ELogObjectCommandFlags::Default, TOptional<int32> InMaxIters = TOptional<int32>()) 
	: ObjectToLog{InObjectToLog}
	, MaxIters{InMaxIters}
	, Flags{InFlags}
	, LastObjectState{InObjectToLog}
	{
		check(InObjectToLog);
	}

	bool Update() override;

private:
	const UObject* ObjectToLog;
	int32 UpdateIndex = 0;
	TOptional<int32> MaxIters;
	ELogObjectCommandFlags Flags;
	FMyObjectState LastObjectState;
};
