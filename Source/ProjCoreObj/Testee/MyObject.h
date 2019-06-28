#pragma once

#include "MyObject.generated.h"

UCLASS()
class UMyObject : public UObject
{
	GENERATED_BODY()

protected:
	// ~ UObjectBase Begin
	virtual void RegisterDependencies() override;
	//virtual void Register(const TCHAR* PackageName, const TCHAR* Name) override;
	virtual void DeferredRegister(UClass* UClassStaticClass, const TCHAR* PackageName, const TCHAR* Name) override;
	// ~ UObjectBase End

	// ~UObject Begin
	virtual void BeginDestroy() override;
	virtual void FinishDestroy() override;
	// ~UObject End
};