// (c) Monogenesis

#pragma once

#include "EdGraphUtilities.h"

struct FGameIdSetConfig;

class FGameIdPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;
	bool GetGameIDIfValid(const FGameIdSetConfig& PinConfig, FName PinName, FString NodeName, const UEdGraphSchema_K2* K2Schema, TArray<TSharedPtr<FString>>& OutGameID) const;
};
