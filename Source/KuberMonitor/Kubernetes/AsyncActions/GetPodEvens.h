// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "KuberMonitorGameModeBase.h"

#include "GetPodEvens.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPodEventsReceived, const FString&, LogText, bool, bSuccess);
/**
 * TODO: Rename to get pod events action
 */
UCLASS()
class KUBERMONITOR_API UGetPodEvens : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "HTTP", WorldContext = "WorldContextObject"))
	static UGetPodEvens* GetEvents(UObject* WorldContextObject, FString ApiHost, FString PodName, FString NameSpace);

	UPROPERTY(BlueprintAssignable)
	FOnPodEventsReceived FOnEventsReceived;

	FString ApiHost;
	FString PodName;
	FString NameSpace;

protected:
	void HandleRequestCompleted(FString ResponseString, bool bSuccess);

};
