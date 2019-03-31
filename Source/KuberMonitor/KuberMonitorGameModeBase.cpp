// Fill out your copyright notice in the Description page of Project Settings.

#include "KuberMonitorGameModeBase.h"

FString AKuberMonitorGameModeBase::GetKubernetesApiUrl() const
{
	return KubernetesApiBaseUrl;
}

void AKuberMonitorGameModeBase::SetNamespaceList(FString NSList)
{
	NamespaceList = NSList;
}

FString AKuberMonitorGameModeBase::GetNamespaceList() const
{
	return NamespaceList;
}

void AKuberMonitorGameModeBase::SetKubernetesApiUrl(FString Url)
{
	KubernetesApiBaseUrl = Url;
}
