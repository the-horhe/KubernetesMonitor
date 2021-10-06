// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KuberMonitorGameModeBase.h"
#include "Kubernetes/KubernetesApi.h"

#include "BlueprintHelper.generated.h"

/**
 * 
 */
UCLASS()
class KUBERMONITOR_API UBlueprintHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Blueprint helper")
	static FLinearColor GenerateColorFromString(FString InputString);
};
