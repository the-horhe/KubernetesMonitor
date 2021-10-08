// Fill out your copyright notice in the Description page of Project Settings.


#include "Kubernetes/AsyncActions/GetPodEvens.h"

void UGetPodEvens::Activate()
{
	// Create HTTP Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb("GET");
	auto Url = ApiHost + "/api/v1/namespaces/" + NameSpace + "/events?fieldSelector=involvedObject.name%3D" + PodName + "%2CinvolvedObject.namespace%3D" + NameSpace;
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

UGetPodEvens* UGetPodEvens::GetEvents(UObject* WorldContextObject, FString ApiHost, FString PodName, FString NameSpace)
{
	// Create Action Instance for Blueprint System
	UGetPodEvens* Action = NewObject<UGetPodEvens>();

	Action->ApiHost = ApiHost;
	Action->PodName = PodName;
	Action->NameSpace = NameSpace;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}

void UGetPodEvens::HandleRequestCompleted(FString ResponseString, bool bSuccess)
{
	FOnEventsReceived.Broadcast(ResponseString, bSuccess);
}
