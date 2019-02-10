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
	UE_LOG(LogTemp, Warning, TEXT("POD STATUS"));
}

void UKubernetesDrive::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
}

// Called when the game starts
void UKubernetesDrive::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UKubernetesDrive::UpdatePodsStatus, RefreshDelay, true, 0.f);
}


// Called every frame
void UKubernetesDrive::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

