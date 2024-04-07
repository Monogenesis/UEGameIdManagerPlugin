// (c) Monogenesis

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"

class SSearchableComboBox;

class GAMEIDMANAGEREDITOR_API SGameIdManagerGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGameIdManagerGraphPin)
	{
	}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, const TArray<TSharedPtr<FString>>& InNameList);
	TSharedRef<SWidget> OnGenerateComboWidget(TSharedPtr<FString> String);
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	void OnComboBoxOpened();
	void OnNameSelected(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);

private:
	TArray<TSharedPtr<FString>> NameList;
	TSharedPtr<SSearchableComboBox> SearchableComboBox;
};
