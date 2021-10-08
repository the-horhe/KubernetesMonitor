// Fill out your copyright notice in the Description page of Project Settings.
// TODO: Base Async action class

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "KuberMonitorGameModeBase.h"

#include "DescribePodAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPodDescribeReceived, const FString&, LogText, bool, bSuccess);

/**
 * 
 */
UCLASS()
class KUBERMONITOR_API UDescribePodAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "HTTP", WorldContext = "WorldContextObject"))
	static UDescribePodAction* DescribePods(UObject* WorldContextObject, FString ApiHost, FString PodName, FString NameSpace);

	UPROPERTY(BlueprintAssignable)
	FOnPodDescribeReceived OnDescribeReceived;

	FString ApiHost;
	FString PodName;
	FString NameSpace;

protected:
	void HandleRequestCompleted(FString ResponseString, bool bSuccess);

};
