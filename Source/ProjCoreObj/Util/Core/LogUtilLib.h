#pragma once

#include "MyDebugMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogUtilLib.generated.h"

UENUM(BlueprintType)
enum class EMyLogObjectFlags : uint8
{
	None UMETA(DisplayName="None"),

	SuppressNameAndClass         = 1 << 0 UMETA(DisplayName="Suppress name and class"),

	InternalObjectFlags          = 1 << 1 UMETA(DisplayName="Internal object flags"),
	ObjectFlags                  = 1 << 2 UMETA(DisplayName="Object flags"),

	FullGroupName = 1 << 3 UMETA(DisplayName="Full group name"),
	Outer = 1 << 4 UMETA(DisplayName="Outer"),

	Full = InternalObjectFlags | ObjectFlags | Outer | FullGroupName UMETA(DisplayName="Full"), // Provide maximal info when logging

	Default = ObjectFlags | Outer UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(EMyLogObjectFlags);

UCLASS()
class ULogUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	ULogUtilLib();

	/**
	* Returns name and class of the object.
	* WARNING: nullptr object is invalid.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClass(const UObject* InObject);

	/**
	* Returns name and class of the object.
	* WARNING: nullptr object is valid.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassSafe(const UObject* InObject);

	/**
	* Returns name and class of the object, enclosed in brackets.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassScoped(const UObject* InObject);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetYesNo(bool bYes);
	
	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogObjectSafe(const UObject* InObject, EMyLogObjectFlags InFlags = EMyLogObjectFlags::Default);
	
	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogObjectSafeIf(bool bInShouldLog, const UObject* InObject, EMyLogObjectFlags InFlags = EMyLogObjectFlags::Default);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogObjectSafeIfFlags(ELogFlags InLogFlags, const UObject* InObject, EMyLogObjectFlags InFlags = EMyLogObjectFlags::Default);

	static FString GetInternalObjectFlagsString(EInternalObjectFlags InFlags);
	static FString GetInternalObjectFlagsStringScoped(EInternalObjectFlags InFlags);
	static FString GetObjectFlagsString(EObjectFlags InFlags);
	static FString GetObjectFlagsStringScoped(EObjectFlags InFlags);
};

// ~Logging macros End
