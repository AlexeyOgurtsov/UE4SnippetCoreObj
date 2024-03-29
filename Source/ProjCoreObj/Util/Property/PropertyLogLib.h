#pragma once

#include "Util/Core/LogUtilLib.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PropertyLogLib.generated.h"

UENUM(BlueprintType)
enum class EFieldStringFlags : uint8
{
	None = 0 UMETA(DisplayName="None"),
	ExcludeOwner = 1 << 0 UMETA(DisplayName="Exclude owner")
};
ENUM_CLASS_FLAGS(EFieldStringFlags);

UENUM()
enum class EPropertyValueStringFlags
{
	None = 0 UMETA(DisplayName="None")
};
ENUM_CLASS_FLAGS(EPropertyValueStringFlags);

UCLASS()
class UPropertyLogLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Returns field string representation.
	*
	* @param InField: Field can NOT be nullptr.
	*/
	static FString GetFieldString(const UField* InField, EFieldStringFlags InFlags = EFieldStringFlags::None);

	/**
	* Returns field string representation. 
	*
	* @param InField: Field can be nullptr.
	*/
	static FString GetFieldStringSafe(const UField* InField, EFieldStringFlags InFlags = EFieldStringFlags::None);

	/**
	* Logs property values of the given struct.
	*/
	static void LogStructPropertyValues(const UStruct* InStruct, const void* InStructValue);

	/**
	* Logs value of the given property.
	*/
	static void LogPropertyValue(const UProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags = EPropertyValueStringFlags::None);

	/**
	* Returns property value string representation.
	*/
	static FString GetPropertyValueString(const UProperty* InProperty, const void* InValue, EPropertyValueStringFlags InFlags = EPropertyValueStringFlags::None);

	/**
	* Returns array property value string representation.
	*/
	static FString GetArrayPropertyValueString(const UArrayProperty* InProperty, const void* InValue, EPropertyValueStringFlags InFlags = EPropertyValueStringFlags::None);
	
	/**
	* Returns map property value string representation.
	*/
	static FString GetMapPropertyValueString(const UMapProperty* InProperty, const void* InValue, EPropertyValueStringFlags InFlags = EPropertyValueStringFlags::None);
	
	/**
	* Returns set property value string representation.
	*/
	static FString GetSetPropertyValueString(const USetProperty* InProperty, const void* InValue, EPropertyValueStringFlags InFlags = EPropertyValueStringFlags::None);
};