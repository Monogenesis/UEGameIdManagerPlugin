// (c) Monogenesis

#include "GameIdPinFactory.h"
#include "EdGraphSchema_K2.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "GameIdManagerGraphPin.h"
#include "GameIdManagerConfig.h"

TSharedPtr<SGraphPin> FGameIdPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	if (InPin && InPin->GetOwningNode())
	{
		if (InPin->LinkedTo.Num() == 0 && InPin->PinType.PinCategory == K2Schema->PC_Name || InPin->PinType.PinCategory == K2Schema->PC_String)
		{
			FString NodeName = InPin->GetOwningNode()->GetNodeTitle(ENodeTitleType::MenuTitle).ToString();
			// FName FunctionName = FName(InPin->GetOwningNode()->GetNodeTitle(ENodeTitleType::ListView).ToString());
			FName PinName = FName(InPin->GetName());

			TArray<TSharedPtr<FString>> NameListForPin;
			for (TPair<FName, FGameIdSetConfig> IdConfigKvP : UGameIdManagerConfig::GetGameIdConfigs())
			{
				if (GetGameIDIfValid(IdConfigKvP.Value, PinName, NodeName, K2Schema, NameListForPin))
				{
					break;
				}
			}

			if (NameListForPin.Num() > 0)
			{
				return SNew(SGameIdManagerGraphPin, InPin, NameListForPin);
			}
		}
	}
	return nullptr;
}

bool FGameIdPinFactory::GetGameIDIfValid(const FGameIdSetConfig& PinConfig, FName PinName, FString NodeName, const UEdGraphSchema_K2* K2Schema, TArray<TSharedPtr<FString>>& OutGameID) const
{
	bool Result = false;
	for (FGameIdPinConfig Config : PinConfig.PinConfigs)
	{
		bool NodeOk = Config.ValidPinName.IsEqual(PinName);
		if (NodeOk)
		{
			NodeOk = Config.ValidBlueprintNodeNames.Num() == 0 || Config.ValidBlueprintNodeNames.Contains(NodeName);
			if (NodeOk == false)
			{
				NodeName.RemoveSpacesInline();
				NodeOk = Config.ValidBlueprintNodeNames.Contains(NodeName);
			}
			if (NodeOk)
			{
				TArray<FName> SortedIDs = UGameIdManagerConfig::GetSortedIDs(PinConfig.GameIDs, true);
				OutGameID.Reserve(SortedIDs.Num());
				for (FName Name : SortedIDs)
				{
					OutGameID.Add(MakeShareable(new FString(Name.ToString())));
				}
				Result = true;
			}
		}
	}
	return Result;
}
