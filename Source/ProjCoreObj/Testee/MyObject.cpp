#include "MyObject.h"

#include "Util/Core/LogUtilLib.h"


void UMyObject::RegisterDependencies()
{
	M_LOGFUNC_MSG(TEXT("%s"), *ULogUtilLib::GetNameAndClassSafe(this));
	Super::RegisterDependencies();
}

//void UMyObject::Register(const TCHAR* PackageName, const TCHAR* Name)
//{
//	M_LOGFUNC_MSG(TEXT("%s"), *ULogUtilLib::GetNameAndClassSafe(this));
//	Super::Register(PackageName, Name);
//}

void UMyObject::DeferredRegister(UClass* UClassStaticClass, const TCHAR* PackageName, const TCHAR* Name)
{
	M_LOGFUNC_MSG(TEXT("%s"), *ULogUtilLib::GetNameAndClassSafe(this));
	Super::DeferredRegister(UClassStaticClass, PackageName, Name);
}

void UMyObject::BeginDestroy()
{
	M_LOGFUNC_MSG(TEXT("%s"), *ULogUtilLib::GetNameAndClassSafe(this));
	Super::BeginDestroy();
}

void UMyObject::FinishDestroy()
{
	M_LOGFUNC_MSG(TEXT("%s"), *ULogUtilLib::GetNameAndClassSafe(this));
	Super::FinishDestroy();
}