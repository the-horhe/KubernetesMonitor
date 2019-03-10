// Fill out your copyright notice in the Description page of Project Settings.

#include "KubernetesDrive.h"

// Sets default values for this component's properties
UKubernetesDrive::UKubernetesDrive()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Http = &FHttpModule::Get();
}


void UKubernetesDrive::UpdatePodsStatus()
{
	if (Host == "") {
		UE_LOG(LogTemp, Error, TEXT("Host no defined"));
		return;
	}

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UKubernetesDrive::OnPodsResponseReceived);
	//This is the url on which to process the request 
	Request->SetURL(Host + "/api/v1/namespaces/retail-partners-dev/pods?limit=500"); // TODO: host should be a parameter
	Request->SetVerb("GET");
	Request->ProcessRequest();

}

void UKubernetesDrive::OnPodsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//Create a pointer to hold the json serialized data 
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data 
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FString RawResponse = Response->GetContentAsString();

	UE_LOG(LogTemp, Warning, TEXT("Raw response: %s"), *RawResponse);

	//Deserialize the json data given Reader and the actual object to deserialize 
	if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
		TArray<FPodModel> PodsArray;
		TArray<TSharedPtr<FJsonValue>> Items = JsonObject->GetArrayField("items");
		for (TSharedPtr<FJsonValue> PodDefinition : Items) {
			FPodModel PodModel;
			auto Metadata = PodDefinition->AsObject()->GetObjectField("metadata");
			PodModel.Name = Metadata->GetStringField("name");
			PodModel.Namespace = Metadata->GetStringField("namespace");
			PodModel.App = Metadata->GetObjectField("labels")->GetStringField("app");

			auto Status = PodDefinition->AsObject()->GetObjectField("status");
			PodModel.Phase = Status->GetStringField("phase");

			PodsArray.Add(PodModel);
		}

		FStateDiff Diff = GameState->GetStateDiff(&PodsArray);

		OnPodsUpdate.Broadcast(PodsArray);
	}
}

// Called when the game starts
void UKubernetesDrive::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UKubernetesDrive::UpdatePodsStatus, RefreshDelay, true, 0.f);
	GameState = GetWorld()->GetGameState<AKuberMonitorGameState>();
}


// Called every frame
void UKubernetesDrive::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

