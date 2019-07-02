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
	FString Host = GameMode->GetKubernetesApiUrl();
	FString NamespaceListString = GameMode->GetNamespaceList();
	TArray<FString> NamespaceList;

	if (Host == "" || NamespaceListString == "") {
		UE_LOG(LogTemp, Error, TEXT("Host or namespace not defined"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *NamespaceListString);
	NamespaceListString.ParseIntoArray(NamespaceList, TEXT(","), true);
	for (FString Namespace : NamespaceList) {
		UE_LOG(LogTemp, Warning, TEXT("Request for host '%s' and NS: %s"), *Host, *Namespace);
		TSharedRef<IHttpRequest> Request = Http->CreateRequest();
		Request->OnProcessRequestComplete().BindUObject(this, &UKubernetesDrive::OnPodsResponseReceived);
		//This is the url on which to process the request 
		Request->SetURL(Host + "/api/v1/namespaces/" + Namespace + "/pods?limit=500");
		Request->SetVerb("GET");
		Request->SetHeader(NAMESPACE_HEADER, Namespace);
		Request->ProcessRequest();
	}
}

void UKubernetesDrive::OnPodsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid response"));
		return;
	}

	//Create a pointer to hold the json serialized data 
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data 
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FString RawResponse = Response->GetContentAsString();
	FString Namespace = Request->GetHeader(NAMESPACE_HEADER);

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

		FStateDiff Diff = GameState->GetStateDiff(&PodsArray, &Namespace);
		OnPodsUpdate.Broadcast(Diff);
	}
}

// Called when the game starts
void UKubernetesDrive::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UKubernetesDrive::UpdatePodsStatus, RefreshDelay, true, 0.f);
	GameState = GetWorld()->GetGameState<AKuberMonitorGameState>();
	GameMode = GetWorld()->GetAuthGameMode<AKuberMonitorGameModeBase>();
}


// Called every frame
void UKubernetesDrive::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

