#pragma once

#include "CoreMinimal.h"

#include "PodModel.generated.h"

USTRUCT(BlueprintType)
struct FPodModel
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString Namespace;

	UPROPERTY(BlueprintReadOnly)
	FString App;

	// @see https://kubernetes.io/docs/concepts/workloads/pods/pod-lifecycle/#pod-phase
	// TODO: enum
	UPROPERTY(BlueprintReadOnly)
	FString Phase;

    // Pod "Ready" condition met
    // https://kubernetes.io/docs/concepts/workloads/pods/pod-lifecycle/#pod-conditions
	UPROPERTY(BlueprintReadOnly)
	bool IsReady = false;
};