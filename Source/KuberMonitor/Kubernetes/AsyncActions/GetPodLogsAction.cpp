// Fill out your copyright notice in the Description page of Project Settings.


#include "Kubernetes/AsyncActions/GetPodLogsAction.h"

void UGetPodLogsAction::Activate()
{
	// Create HTTP Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb("GET");
	auto Url = ApiHost + "/api/v1/namespaces/" + NameSpace + "/pods/" + PodName + "/log?tailLines=" + FString::FromInt(LogLines);
	UE_LOG(LogTemp, Warning, TEXT("LogUrl: %s"), *Url);

	Request->SetURL(Url);

	// Setup Async response
	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			FString ResponseString = "";
			if (bSuccess)
			{
				ResponseString = Response->GetContentAsString();
			}

			this->HandleRequestCompleted(ResponseString, bSuccess);
		});

	// Handle actual request
	Request->ProcessRequest();
}

UGetPodLogsAction* UGetPodLogsAction::GetPodLogs(UObject* WorldContextObject, FString ApiHost, FString PodName, FString NameSpace, int LogLines)
{
	// Create Action Instance for Blueprint System
	UGetPodLogsAction* Action = NewObject<UGetPodLogsAction>();
	
	Action->ApiHost = ApiHost;
	Action->PodName = PodName;
	Action->NameSpace = NameSpace;
	Action->LogLines = LogLines;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}

void UGetPodLogsAction::HandleRequestCompleted(FString ResponseString, bool bSuccess)
{
	OnLogsReceived.Broadcast(ResponseString, bSuccess);
}
