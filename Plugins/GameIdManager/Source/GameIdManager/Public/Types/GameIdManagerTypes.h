// (c) Spaceflower

#pragma once

#include "GameIdManagerTypes.generated.h"

USTRUCT(BlueprintType)
struct FGameIdPinConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, config)
	FName ValidPinName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, config)
	TArray<FString> ValidBlueprintNodeNames;
};

USTRUCT(BlueprintType)
struct FGameIdSetConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, config)
	TArray<FName> GameIDs = {};
	UPROPERTY(BlueprintReadWrite, EditAnywhere, config, meta=(TitleProperty = "ValidPinName"))
	TArray<FGameIdPinConfig> PinConfigs = {};
};