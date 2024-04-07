// (c) Monogenesis

#include "GameIdManagerEditor.h"
#include "GameIdPinFactory.h"

#define LOCTEXT_NAMESPACE "FGameIdManagerEditorModule"

void FGameIdManagerEditorModule::StartupModule()
{
	GameIdPinFactory = MakeShareable(new FGameIdPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(GameIdPinFactory);
}

void FGameIdManagerEditorModule::ShutdownModule()
{
	FEdGraphUtilities::UnregisterVisualPinFactory(GameIdPinFactory);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FGameIdManagerEditorModule, GameIdManagerEditor)