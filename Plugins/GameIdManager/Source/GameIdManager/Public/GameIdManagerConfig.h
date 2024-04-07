// (c) Monogenesis

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Types/GameIdManagerTypes.h"
#include "GameIdManagerConfig.generated.h"

UCLASS(config=GameIdManager, defaultconfig, meta = (DisplayName = "Game Id Manager"))
class GAMEIDMANAGER_API UGameIdManagerConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFUNCTION()	static TArray<FName> GetMyIdList();

	UFUNCTION()	static TArray<FName> GetGameIDs(FName Category, bool IncludeNoneId);
	UFUNCTION()	static TArray<FName> GetSortedIDs(TArray<FName> IDList, bool IncludeNoneId);
	UFUNCTION()	static const TMap<FName, FGameIdSetConfig>& GetGameIdConfigs();
	static void AddGameID(FName Category, FName GameId);
	void SaveConfigToInI();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, config)
	TMap<FName, FGameIdSetConfig> GameIdConfigs;
};
