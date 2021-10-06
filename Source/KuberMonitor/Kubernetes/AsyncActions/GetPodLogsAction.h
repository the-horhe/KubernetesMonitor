// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "KuberMonitorGameModeBase.h"

#include "GetPodLogsAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPodLogsReceived, const FString&, LogText, bool, bSuccess);

/**
 * 
 */
UCLASS()
class KUBERMONITOR_API UGetPodLogsAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "HTTP", WorldContext = "WorldContextObject"))
	static UGetPodLogsAction* GetPodLogs(UObject* WorldContextObject, FString ApiHost, FString PodName, FString NameSpace, int LogLines);

	UPROPERTY(BlueprintAssignable)
	FOnPodLogsReceived OnLogsReceived;

	FString ApiHost;
	FString PodName;
	FString NameSpace;
	int LogLines;

protected:
	void HandleRequestCompleted(FString ResponseString, bool bSuccess);

};
