#include "KuberMonitorGameState.h"

TArray<FPodModel> AKuberMonitorGameState::GetNewPods(TArray<FPodModel>* FullPodsList) const
{
	TArray<FPodModel> NewPods;
	for (FPodModel Pod : *FullPodsList) {
		UE_LOG(LogTemp, Warning, TEXT("New Pods Itarrator: %s"), *Pod.Name);
	}

	return TArray<FPodModel>();
}

TArray<FPodModel> AKuberMonitorGameState::GetPhaseChangedPods(TArray<FPodModel>* FullPodsList) const
{
	return TArray<FPodModel>();
}

TArray<FPodModel> AKuberMonitorGameState::GetDeletedPods(TArray<FPodModel>* FullPodsList) const
{
	return TArray<FPodModel>();
}

FStateDiff AKuberMonitorGameState::GetStateDiff(TArray<FPodModel>* FullPodsList)
{
	FStateDiff StateDiff = FStateDiff();

	StateDiff.NewPods = GetNewPods(FullPodsList);
	StateDiff.DeletedPods = GetDeletedPods(FullPodsList);
	StateDiff.PhaseChangedPods = GetPhaseChangedPods(FullPodsList);

	return StateDiff;
}
