// Copyright 2020 - Trifolium Digital Limited

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"

#include "DDCInfo.generated.h"


/**
 * Object which is used in a details view to edit DDC settings for the given cache.
 */
UCLASS(transient)
class UDDCInfo : public UObject
{
GENERATED_BODY()

public:

	/** Serialisation of data to and from an ini file. */
	void LoadFromIniString(const FString& IniString);
	FString SaveForIniString() const;
	
	// Path to use for the filesystem DDC
	UPROPERTY(EditAnywhere, Category=PathInformation, meta=(NoResetToDefault))
	FDirectoryPath Path;

	// An environment variable that if set will be used instead of path. E.g. UE-LocalDataCachePath=d:\DDC. ('None' disables the DDC)
	UPROPERTY(EditAnywhere, Category = PathInformation, meta = (NoResetToDefault))
	FString EnvPathOverride;

	// A command line argument used in preference to the default/envvar setting.E.g. -SharedDataCachePath=\\someshare\folder
	UPROPERTY(EditAnywhere, Category = PathInformation, meta = (NoResetToDefault))
	FString CommandlineOverride;

	// Editor user setting that overrides the default/envvar command line values
	UPROPERTY(EditAnywhere, Category = PathInformation, meta = (NoResetToDefault))
	FString EditorOverrideSetting;

	// Can data be written to this layer
	UPROPERTY(EditAnywhere, Category = FileSystemInformation, meta = (NoResetToDefault))
	bool bIsReadOnly = false;

	// Perform a cleanup of old files on launch
	UPROPERTY(EditAnywhere, Category = Cleanup, meta = (NoResetToDefault))
	bool bClean = false;

	// Nuke the DDC and start over
	UPROPERTY(EditAnywhere, Category = Cleanup, meta = (NoResetToDefault))
	bool bFlush = false;

	// Don't keep transient data in the DDC
	UPROPERTY(EditAnywhere, Category = Cleanup, meta = (NoResetToDefault))
	bool bPurgeTransient = false;

	// Clean up old files (happens on a background thread)
	UPROPERTY(EditAnywhere, Category = Cleanup, meta = (NoResetToDefault))
	bool bDeleteUnused = false;

	// Age after which files are removed
	UPROPERTY(EditAnywhere, Category = Cleanup, meta = (NoResetToDefault))
	int32 UnusedFileAge;

	// Max number of folders to clean in a session. - 1 = Unlimited
	UPROPERTY(EditAnywhere, Category = Cleanup, meta = (NoResetToDefault))
	int32 FoldersToClean;

//#if ENGINE_MINOR_VERSION >= 26

	// 4.26+ If the path does not exist a warning prompt will be shown.This is useful for shared DDCs where the mount may have dropped
	UPROPERTY(EditAnywhere, Category = FileSystemInformation, meta = (NoResetToDefault))
	bool bPromptIfMissing = false;
	
	// 4.26+ If access times are < this value in ms then some operations will be disabled to improve performance.
	UPROPERTY(EditAnywhere, Category = FileSystemInformation, meta = (NoResetToDefault))
	float ConsiderSlowAtMS = 50.0f;

//#endif // ENGINE_MINOR_VERSION >= 26

	// How many files to check a second.
	UPROPERTY(EditAnywhere, Category = FileSystemInformation, meta = (NoResetToDefault))
	int32 MaxFileChecksPerSec;
};