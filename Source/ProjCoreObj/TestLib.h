#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestLib.generated.h"

UCLASS()
class UTestLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Test)
	static void QuickTest();
};