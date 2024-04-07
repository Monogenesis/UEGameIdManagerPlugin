// (c) Monogenesis

#include "GameIdManagerConfig.h"

TArray<FName> UGameIdManagerConfig::GetMyIdList()
{
	return GetGameIDs("MyIdList", true);
}

TArray<FName> UGameIdManagerConfig::GetGameIDs(FName Category, bool IncludeNoneId)
{
	static const UGameIdManagerConfig* GameIDConfig = GetDefault<UGameIdManagerConfig>();
	if (const FGameIdSetConfig* IdSetConfig = GameIDConfig->GameIdConfigs.Find(Category))
	{
		return GetSortedIDs(IdSetConfig->GameIDs, IncludeNoneId);
	}
	UE_LOG(LogTemp, Error, TEXT("%s not found in GameIdConfigs"), *Category.ToString());
	return {};
}


TArray<FName> UGameIdManagerConfig::GetSortedIDs(TArray<FName> IDList, bool IncludeNoneId)
{
	if (IncludeNoneId)
	{
		IDList.AddUnique(NAME_None);
	}
	IDList.Sort([](const FName& A, const FName& B)
	{
		if (A.IsNone())
		{
			return true;
		}
		else if (B.IsNone())
		{
			return false;
		}
		else
		{
			return A.Compare(B) < 0;
		}
	});
	return IDList;
}

void UGameIdManagerConfig::AddGameID(FName Category, FName GameId)
{
	static UGameIdManagerConfig* GameIDConfig = GetMutableDefault<UGameIdManagerConfig>();
	GameIDConfig->GameIdConfigs.FindOrAdd(Category).GameIDs.AddUnique(GameId);
	GameIDConfig->SaveConfigToInI();
}

const TMap<FName, FGameIdSetConfig>& UGameIdManagerConfig::GetGameIdConfigs()
{
	static const UGameIdManagerConfig* GameIDConfig = GetDefault<UGameIdManagerConfig>();
	return GameIDConfig->GameIdConfigs;
}

void UGameIdManagerConfig::SaveConfigToInI()
{
	FString DefaultConfigFilename = GetDefaultConfigFilename();
	SaveConfig(CPF_Config, *DefaultConfigFilename);
}
