// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"

#include "KubernetesDrive.generated.h"

UENUM(BlueprintType)
enum PodStatus { Pending, Running, Succeeded, Failed, Unknown };

// STRUCTURES
// TODO: Move models to separate class

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
};

// END STRUCTURES

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPodsUpdateEvent, TArray<FPodModel>, PodsArray);

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

	UPROPERTY(EditAnywhere)
	FString Host = "";

	UFUNCTION()
	void UpdatePodsStatus();

	void OnPodsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintAssignable)
	FPodsUpdateEvent OnPodsUpdate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
