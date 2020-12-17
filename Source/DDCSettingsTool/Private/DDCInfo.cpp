// Copyright 2020 - Trifolium Digital Limited

#include "DDCInfo.h"


void UDDCInfo::LoadFromIniString(const FString& IniString)
{
	FParse::Value(*IniString, TEXT("Path="), Path.Path);
	FParse::Value(*IniString, TEXT("EnvPathOverride="), EnvPathOverride);
	FParse::Value(*IniString, TEXT("CommandLineOverride="), CommandlineOverride);
	FParse::Value(*IniString, TEXT("EditorOverrideSetting="), EditorOverrideSetting);
	FParse::Bool(*IniString, TEXT("ReadOnly="), bIsReadOnly);
	FParse::Bool(*IniString, TEXT("Clean="), bClean);
	FParse::Bool(*IniString, TEXT("Flush="), bFlush);
	FParse::Bool(*IniString, TEXT("PurgeTransient="), bPurgeTransient);
	FParse::Bool(*IniString, TEXT("DeleteUnused="), bDeleteUnused);
	FParse::Value(*IniString, TEXT("UnusedFileAge="), UnusedFileAge);
	FParse::Value(*IniString, TEXT("FoldersToClean="), FoldersToClean);
	FParse::Value(*IniString, TEXT("MaxFileChecksPerSec="), MaxFileChecksPerSec);

#if ENGINE_MINOR_VERSION >= 26
	FParse::Value(*IniString, TEXT("ConsiderSlowAt="), ConsiderSlowAtMS);
	FParse::Bool(*IniString, TEXT("PromptIfMissing="), bPromptIfMissing);
#endif // ENGINE_MINOR_VERSION >= 26
}


FString UDDCInfo::SaveForIniString() const
{
	auto BoolAlpha = [](bool bInVal) { return (bInVal ? TEXT("true") : TEXT("false")); };
	FString FormattedString;
	{
		FormattedString += TEXT("(Type=FileSystem");
		
		FormattedString += FString::Printf(TEXT(", Path=%s"), *Path.Path);
		FormattedString += FString::Printf(TEXT(", EnvPathOverride=%s"), *EnvPathOverride);
		FormattedString += FString::Printf(TEXT(", CommandLineOverride=%s"), *CommandlineOverride);
		FormattedString += FString::Printf(TEXT(", EditorOverrideSetting=%s"), *EditorOverrideSetting);
		FormattedString += FString::Printf(TEXT(", ReadOnly=%s"), BoolAlpha(bIsReadOnly));
		FormattedString += FString::Printf(TEXT(", Clean=%s"), BoolAlpha(bClean));
		FormattedString += FString::Printf(TEXT(", Flush=%s"), BoolAlpha(bFlush));
		FormattedString += FString::Printf(TEXT(", PurgeTransient=%s"), BoolAlpha(bPurgeTransient));
		FormattedString += FString::Printf(TEXT(", DeleteUnused=%s"), BoolAlpha(bDeleteUnused));
		FormattedString += FString::Printf(TEXT(", UnusedFileAge=%d"), UnusedFileAge);
		FormattedString += FString::Printf(TEXT(", FoldersToClean=%d"), FoldersToClean);
		FormattedString += FString::Printf(TEXT(", MaxFileChecksPerSec=%d"), MaxFileChecksPerSec);

#if ENGINE_MINOR_VERSION >= 26
		FormattedString += FString::Printf(TEXT(", ConsiderSlowAt=%.2f"), ConsiderSlowAtMS);
		FormattedString += FString::Printf(TEXT(", PromptIfMissing=%s"), BoolAlpha(bPromptIfMissing));
#endif // ENGINE_MINOR_VERSION >= 26

		FormattedString += TEXT(")");
	}
	return FormattedString;
}
