// Fill out your copyright notice in the Description page of Project Settings.


#include "Kubernetes/AsyncActions/DescribePodAction.h"

void UDescribePodAction::Activate()
{
	// Create HTTP Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb("GET");
	auto Url = ApiHost + "/api/v1/namespaces/" + NameSpace + "/pods/" + PodName;
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

UDescribePodAction* UDescribePodAction::DescribePods(UObject* WorldContextObject, FString ApiHost, FString PodName, FString NameSpace)
{
	// Create Action Instance for Blueprint System
	UDescribePodAction* Action = NewObject<UDescribePodAction>();

	Action->ApiHost = ApiHost;
	Action->PodName = PodName;
	Action->NameSpace = NameSpace;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}

void UDescribePodAction::HandleRequestCompleted(FString ResponseString, bool bSuccess)
{
	OnDescribeReceived.Broadcast(ResponseString, bSuccess);
}
