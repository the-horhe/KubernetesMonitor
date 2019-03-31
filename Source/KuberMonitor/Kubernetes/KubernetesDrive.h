// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "PodModel.h"
#include "KuberMonitorGameState.h"
#include "KuberMonitorGameModeBase.h"

#include "KubernetesDrive.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPodsUpdateEvent, FStateDiff, StateDiff);

// TODO: move gamestate interraction to separate class
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KUBERMONITOR_API UKubernetesDrive : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKubernetesDrive();
	FHttpModule* Http;

	UPROPERTY(EditAnywhere)
	float RefreshDelay = 10.f;

	UFUNCTION()
	void UpdatePodsStatus();

	void OnPodsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintAssignable)
	FPodsUpdateEvent OnPodsUpdate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle;

	AKuberMonitorGameState* GameState;
	AKuberMonitorGameModeBase* GameMode;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	const FString NAMESPACE_HEADER = "unreal-kubernetes-namespace";


};
