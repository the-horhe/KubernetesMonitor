// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "KuberMonitorGameModeBase.generated.h"

/**
 * TODO: move settings to dedicated class
 */
UCLASS()
class KUBERMONITOR_API AKuberMonitorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void SetKubernetesApiUrl(FString Url);

	UFUNCTION(BlueprintCallable)
	FString GetKubernetesApiUrl() const;

	UFUNCTION(BlueprintCallable)
	void SetNamespaceList(FString NSList);

	UFUNCTION(BlueprintCallable)
	FString GetNamespaceList() const;

private:
	FString KubernetesApiBaseUrl;
	FString NamespaceList;

};
