// (c) Monogenesis

#pragma once

#include "CoreMinimal.h"

class FGameIdPinFactory;

class FGameIdManagerEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedPtr<FGameIdPinFactory> GameIdPinFactory;

};
