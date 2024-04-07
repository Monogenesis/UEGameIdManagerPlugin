// (c) Monogenesis

#include "GameIdManagerGraphPin.h"
#include "SSearchableComboBox.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "KismetPins/SGraphPinString.h"

void SGameIdManagerGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, const TArray<TSharedPtr<FString>>& InNameList)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	NameList = InNameList;
}

TSharedRef<SWidget> SGameIdManagerGraphPin::GetDefaultValueWidget()
{
	TSharedPtr<FString> CurrentlySelectedName;
	FString PreviousSelection = *GraphPinObj->GetDefaultAsString();

	if (GraphPinObj)
	{
		for (TSharedPtr<FString> ListNamePtr : NameList)
		{
			if (PreviousSelection == *ListNamePtr.Get())
			{
				CurrentlySelectedName = ListNamePtr;
				break;
			}
		}
	}
	if (CurrentlySelectedName.IsValid() == false)
	{
		CurrentlySelectedName = MakeShareable(new FString(PreviousSelection));
	}

	return SAssignNew(SearchableComboBox, SSearchableComboBox)
	          		.ContentPadding(FMargin(6.0f, 2.0f))
	          		.OptionsSource(&NameList)
					.OnGenerateWidget(this, &SGameIdManagerGraphPin::OnGenerateComboWidget)
	          		.Content()
	                                                          [
		                                                          SNew(STextBlock)
		                                                          .Text_Lambda([this] { return FText::FromString(*SearchableComboBox->GetSelectedItem().Get()); })
		                                                          .Font(FCoreStyle::GetDefaultFontStyle("Regular", 9))
	                                                          ]
				    .InitiallySelectedItem(CurrentlySelectedName)
					.OnComboBoxOpening(this, &SGameIdManagerGraphPin::OnComboBoxOpened)
				    .OnSelectionChanged(this, &SGameIdManagerGraphPin::OnNameSelected);
}

TSharedRef<SWidget> SGameIdManagerGraphPin::OnGenerateComboWidget(TSharedPtr<FString> String)
{
	return SNew(STextBlock)
				.Text_Lambda([String] { return FText::FromString(*String.Get()); })
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 9));
}

void SGameIdManagerGraphPin::OnComboBoxOpened()
{
	FString PinString = GraphPinObj->GetDefaultAsString();
	int32 NameCount = NameList.Num();
	for (int32 NameIndex = 0; NameIndex < NameCount; ++NameIndex)
	{
		if (PinString == *NameList[NameIndex].Get())
		{
			SearchableComboBox->SetSelectedItem(NameList[NameIndex]);
		}
	}

	SearchableComboBox->RefreshOptions();
}

void SGameIdManagerGraphPin::OnNameSelected(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	FString Name = ItemSelected.IsValid() ? *ItemSelected : TEXT("");
	if (const UEdGraphSchema* Schema = (GraphPinObj ? GraphPinObj->GetSchema() : NULL))
	{
		FString NameAsString = Name;
		if (GraphPinObj->GetDefaultAsString() != NameAsString)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeNameListPinValue", "Change Name List Pin Value"));
			GraphPinObj->Modify();
			Schema->TrySetDefaultValue(*GraphPinObj, NameAsString);
		}
	}
}
