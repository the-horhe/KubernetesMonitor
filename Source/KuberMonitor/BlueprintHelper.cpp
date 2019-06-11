// Fill out your copyright notice in the Description page of Project Settings.

#include "BlueprintHelper.h"

FLinearColor UBlueprintHelper::GenerateColorFromString(FString InputString) {
	uint32 StringHash = GetTypeHash(InputString);

	int R = StringHash % 1000 % 255;
	int G = (StringHash / 1000) % 1000 % 255;
	int B = (StringHash / 1000000) % 1000 % 255;

	FLinearColor Color = FLinearColor();
	Color.R = R;
	Color.G = G;
	Color.B = B;

	UE_LOG(LogTemp, Warning, TEXT("Hash: %u"), StringHash);
	UE_LOG(LogTemp, Warning, TEXT("R: %u G: %u B: %u"), R, G, B);
	UE_LOG(LogTemp, Warning, TEXT("COLOR: R: %F G: %F B: %F"), Color.R, Color.G, Color.B);
	
	return Color;
}