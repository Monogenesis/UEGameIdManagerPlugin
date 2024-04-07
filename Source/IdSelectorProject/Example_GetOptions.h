// (c) Monogenesis

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Example_GetOptions.generated.h"


UCLASS(Blueprintable)
class IDSELECTORPROJECT_API UExample_GetOptions : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(GetOptions="GameIdManager.GameIdManagerConfig.GetMyIdList"))
	FName MyIdName;
};
