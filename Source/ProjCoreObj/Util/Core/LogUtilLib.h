#pragma once

#include "MyDebugMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextProperty.h"
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

	// ~Value logging Begin
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetYesNo(bool bYes);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyYesNo(const FString& InKey, bool bInValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogYesNo(const FString& InKey, bool bInValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogYesNoIf(bool bInShouldLog, const FString& InKey, bool bInValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogYesNoIfFlags(ELogFlags InLogFlags, const FString& InKey, bool bInValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogFloat(const FString& InKey, float InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogFloatIf(bool bInShouldLog, const FString& InKey, float InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogFloatIfFlags(ELogFlags InFlags, const FString& InKey, float InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyFloat(const FString& InKey, float InValue);

	static void LogDouble(const FString& InKey, double InValue);
	static void LogDoubleIf(bool bInShouldLog, const FString& InKey, double InValue);
	static void LogDoubleIfFlags(ELogFlags InFlags, const FString& InKey, double InValue);

	static FString GetKeyDouble(const FString& InKey, double InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogInt32(const FString& InKey, int32 InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogInt32If(bool bInShouldLog, const FString& InKey, int32 InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogInt32IfFlags(ELogFlags InLogFlags, const FString& InKey, int32 InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyInt32(const FString& InKey, int32 InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogString(const FString& InKey, const FString& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogStringIf(bool bInShouldLog, const FString& InKey, const FString& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogStringIfFlags(ELogFlags InLogFlags, const FString& InKey, const FString& InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyString(const FString& InKey, const FString& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogText(const FString& InKey, const FText& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogTextIf(bool bInShouldLog, const FString& InKey, const FText& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogTextIfFlags(ELogFlags InLogFlags, const FString& InKey, const FText& InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyText(const FString& InKey, const FText& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogName(const FString& InKey, const FName& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogNameIf(bool bInShouldLog, const FString& InKey, const FName& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogNameIfFlags(ELogFlags InLogFlags, const FString& InKey, const FName& InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyName(const FString& InKey, const FName& InValue);
	// ~Value logging End
	
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
