// Copyright 2020 - Trifolium Digital Limited

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"


/**
 *
 */
struct FDDCData
{
	FDDCData() = default;
	FDDCData(const FString& InCacheName);
	
	void LoadFromIniString(const FString& IniString);
	FString SaveForIniString() const;

	// The name of this cache. I.e. Local or Shared
	FString CacheName;
	
	// Path to use for the filesystem DDC
	FString Path;

	// An environment variable that if set will be used instead of path.E.g. UE-LocalDataCachePath=d:\DDC. ('None' disables the DDC)
	FString EnvPathOverride;

	// A command line argument used in preference to the default/envvar setting.E.g. -SharedDataCachePath=\\someshare\folder
	FString CommandlineOverride;

	// Editor user setting that overrides the default/envvarcommand line values
	FString EditorOverrideSetting;

	// Can data be written to this layer
	bool bIsReadOnly = false;

	// Perform a cleanup of old files on launch
	bool bClean = false;

	// Nuke the DDCand start over
	bool bFlush = false;

	// Don't keep transient data in the DDC
	bool bPurgeTransient = false;

	// Clean up old files (happens on a background thread)
	bool bDeleteUnused = false;

	// Age after which files are removed
	int32 UnusedFileAge;

	// Max number of folders to clean in a session. - 1 = Unlimited
	int32 FoldersToClean;

#if ENGINE_MINOR_VERSION >= 26
	// 4.26+ If the path does not exist a warning prompt will be shown.This is useful for shared DDCs where the mount may have dropped
	bool bPromptIfMissing = false;
	
	// 4.26+ If access times are < this value in ms then some operations will be disabled to improve performance.
	float ConsiderSlowAtMS = 50.0f;
#endif // ENGINE_MINOR_VERSION >= 26

	// How many files to check a second.
	int32 MaxFileChecksPerSec;
};