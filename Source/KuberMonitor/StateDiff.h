#pragma once

#include "CoreMinimal.h"
#include "Kubernetes/PodModel.h"

#include "StateDiff.generated.h"

USTRUCT(BlueprintType)
struct FStateDiff
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<FPodModel> NewPods;

	UPROPERTY(BlueprintReadOnly)
		TArray<FPodModel> DeletedPods;

	UPROPERTY(BlueprintReadOnly)
		TArray<FPodModel> PhaseChangedPods;
};