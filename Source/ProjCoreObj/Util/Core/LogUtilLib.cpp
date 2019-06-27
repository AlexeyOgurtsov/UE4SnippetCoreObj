#include "LogUtilLib.h"

DEFINE_LOG_CATEGORY(MyLog);

ULogUtilLib::ULogUtilLib()
{
}

FString ULogUtilLib::GetNameAndClass(const UObject* const InObject)
{
	checkf(InObject, TEXT("nullptr is invalid when using  %s, use Safe version instead"), __FUNCTION__);
	TArray<FStringFormatArg> FormatArgs;
	FormatArgs.Add(InObject->GetName());
	FormatArgs.Add(InObject->GetClass()->GetName());
	return FString::Format(TEXT("name=\"{0}\" class=\"{1}\""), FormatArgs);
}

FString ULogUtilLib::GetNameAndClassSafe(const UObject* const InObject)
{
	if(nullptr == InObject)
	{
		return FString(TEXT("nullptr"));
	}
	return GetNameAndClass(InObject);
}

FString ULogUtilLib::GetNameAndClassScoped(const UObject* const InObject)
{
	check(InObject);
	FString Result;
	Result.Append(TEXT("("));
	Result.Append(GetNameAndClass(InObject));
	Result.Append(TEXT(")"));
	return Result;
}

FString ULogUtilLib::GetYesNo(bool const bYes)
{
	return bYes ? FString(TEXT("YES")) : FString(TEXT("no"));
}

void ULogUtilLib::LogObjectSafe(const UObject* const InObject, EMyLogObjectFlags const InFlags)
{
	return LogObjectSafeIf(true, InObject, InFlags);
}

void ULogUtilLib::LogObjectSafeIf(bool const bInShouldLog, const UObject* const InObject, EMyLogObjectFlags const InFlags)
{
	if(bInShouldLog == false)
	{
		return;
	}

	M_LOGFUNC();
	M_LOG(TEXT("Logging object {%s}"), *GetNameAndClassSafe(InObject));
	// GetFullName DO safe to call on nullptr pointers:
	if( (InFlags & EMyLogObjectFlags::SuppressNameAndClass) == EMyLogObjectFlags::None )
	{
		M_LOG(TEXT("FullName: {%s}"), *InObject->GetFullName());
	}
	if(InObject)
	{
		if(false == InObject->IsValidLowLevelFast(false))
		{
			M_LOG_ERROR(TEXT("Object is invalid Low-level NON_RECURSIVE (IsValidLowLevelFast(false) returned false)"));
		}
		if(false == InObject->IsValidLowLevelFast(true))
		{
			M_LOG_ERROR(TEXT("Object is invalid Low-level RECURSIVE (IsValidLowLevelFast(true) returned false)"));
		}
		if( (InFlags & EMyLogObjectFlags::FullGroupName) != EMyLogObjectFlags::None )
		{
			M_LOG(TEXT("FullGroupName: {%s}"), *InObject->GetFullGroupName(/*bStartWithOuter*/true));
		}
		if( (InFlags & EMyLogObjectFlags::Outer) != EMyLogObjectFlags::None )
		{
			M_LOG(TEXT("Outer: {%s}"), *GetNameAndClassSafe(InObject->GetOuter()));
		}
		if( (InFlags & EMyLogObjectFlags::ObjectFlags) != EMyLogObjectFlags::None )
		{
			M_LOG(TEXT("Flags: %s"), *GetObjectFlagsStringScoped(InObject->GetFlags()));
		}
		if( (InFlags & EMyLogObjectFlags::InternalObjectFlags) != EMyLogObjectFlags::None )
		{
			M_LOG(TEXT("Internal Flags: %s"), *GetInternalObjectFlagsStringScoped(InObject->GetInternalFlags()));
		}
	}

}	
void ULogUtilLib::LogObjectSafeIfFlags(ELogFlags InLogFlags, const UObject* InObject, EMyLogObjectFlags InFlags)
{
	bool const bShouldLog = UMyLoggingTypes::ShouldLogVerbosity(InLogFlags, ELogVerbosity::Type::Log);
	LogObjectSafeIf(bShouldLog, InObject, InFlags);
}

FString ULogUtilLib::GetInternalObjectFlagsStringScoped(EInternalObjectFlags const InFlags)
{
	return FString::Printf(TEXT("{%s}"), *GetInternalObjectFlagsString(InFlags));
}

FString ULogUtilLib::GetInternalObjectFlagsString(EInternalObjectFlags const InFlags)
{
	FString S;
	if(InFlags == EInternalObjectFlags::None)
	{
		return FString(TEXT("None"));
	}
	else
	{
		if((InFlags & EInternalObjectFlags::ReachableInCluster) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("ReachableInCluster | "));
		}
		if((InFlags & EInternalObjectFlags::ClusterRoot)  != EInternalObjectFlags::None)
		{
			S.Append(TEXT("ClusterRoot | "));
		}
		if((InFlags & EInternalObjectFlags::Native) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("Native | "));
		}
		if((InFlags & EInternalObjectFlags::Async) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("Async | "));
		}
		if((InFlags & EInternalObjectFlags::AsyncLoading) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("AsyncLoading | "));
		}
		if((InFlags & EInternalObjectFlags::Unreachable) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("Unreachable | "));
		}
		if((InFlags & EInternalObjectFlags::PendingKill) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("PendingKill | "));
		}
		if((InFlags & EInternalObjectFlags::RootSet) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("RootSet | "));
		}
	}
	return S;
}

FString ULogUtilLib::GetObjectFlagsStringScoped(EObjectFlags const InFlags)
{
	return FString::Printf(TEXT("{%s}"), *GetObjectFlagsString(InFlags));
}

FString ULogUtilLib::GetObjectFlagsString(EObjectFlags const InFlags)
{
	FString S;
	if(InFlags == EObjectFlags::RF_NoFlags)
	{
		return FString(TEXT("None"));
	}
	else
	{
		if((InFlags & EObjectFlags::RF_Public) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Public | "));
		}
		if((InFlags & EObjectFlags::RF_Standalone) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Standalone | "));
		}
		if((InFlags & EObjectFlags::RF_MarkAsNative) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("MarkAsNative | "));
		}
		if((InFlags & EObjectFlags::RF_Transactional) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Transactional | "));
		}
		if((InFlags & EObjectFlags::RF_ClassDefaultObject) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("ClassDefaultObject | "));
		}
		if((InFlags & EObjectFlags::RF_ArchetypeObject) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("ArchetypeObject | "));
		}
		if((InFlags & EObjectFlags::RF_Transient) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Transient | "));
		}
		if((InFlags & EObjectFlags::RF_MarkAsRootSet) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("MarkAsRootSet | "));
		}
		if((InFlags & EObjectFlags::RF_TagGarbageTemp) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("TagGarbageTemp | "));
		}
		if((InFlags & EObjectFlags::RF_NeedInitialization) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NeedInitialization | "));
		}
		if((InFlags & EObjectFlags::RF_NeedLoad) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NeedLoad | "));
		}
		if((InFlags & EObjectFlags::RF_KeepForCooker) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("KeepForCooker | "));
		}
		if((InFlags & EObjectFlags::RF_NeedPostLoad) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NeedPostLoad | "));
		}
		if((InFlags & EObjectFlags::RF_NeedPostLoadSubobjects) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NeedPostLoadSubobjects | "));
		}
		if((InFlags & EObjectFlags::RF_NewerVersionExists) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NewerVersionExists | "));
		}
		if((InFlags & EObjectFlags::RF_BeginDestroyed) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("BeginDestroyed | "));
		}
		if((InFlags & EObjectFlags::RF_FinishDestroyed) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("FinishDestroyed | "));
		}
		if((InFlags & EObjectFlags::RF_BeingRegenerated) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("BeingRegenerated | "));
		}
		if((InFlags & EObjectFlags::RF_DefaultSubObject) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("DefaultSubObject | "));
		}
		if((InFlags & EObjectFlags::RF_WasLoaded) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("WasLoaded | "));
		}
		if((InFlags & EObjectFlags::RF_TextExportTransient) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("TextExportTransient | "));
		}
		if((InFlags & EObjectFlags::RF_LoadCompleted) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("LoadCompleted | "));
		}
		if((InFlags & EObjectFlags::RF_InheritableComponentTemplate) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("InheritableComponentTemplate | "));
		}
		if((InFlags & EObjectFlags::RF_DuplicateTransient) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("DuplicateTransient | "));
		}
		if((InFlags & EObjectFlags::RF_StrongRefOnFrame) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("StrongRefOnFrame | "));
		}
		if((InFlags & EObjectFlags::RF_NonPIEDuplicateTransient) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NonPIEDuplicateTransient | "));
		}
		if((InFlags & EObjectFlags::RF_Dynamic) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Dynamic | "));
		}
		if((InFlags & EObjectFlags::RF_WillBeLoaded) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("WillBeLoaded | "));
		}
		return S;
	}
}
