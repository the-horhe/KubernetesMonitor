#include "KuberMonitorGameState.h"

TArray<FPodModel> AKuberMonitorGameState::GetNewPods(TArray<FPodModel>* FullPodsList) const
{
	TArray<FPodModel> NewPods;
	for (FPodModel ListPod : *FullPodsList) {

		bool IsPodKnown = false;
		for (FPodModel SnapshotPod : PodsSnapshot) { // TODO: Replace with TArray.FindByPredicate
			if (SnapshotPod.Name == ListPod.Name) {
				IsPodKnown = true;
				break;
			}
		}

		if (!IsPodKnown) {
			NewPods.Add(ListPod);
			UE_LOG(LogTemp, Warning, TEXT("New POD: %s"), *ListPod.Name);
		}
	}

	return NewPods;
}

TArray<FPodModel> AKuberMonitorGameState::GetPhaseChangedPods(TArray<FPodModel>* FullPodsList) const
{
	return TArray<FPodModel>();
}

TArray<FPodModel> AKuberMonitorGameState::GetDeletedPods(TArray<FPodModel>* FullPodsList) const
{
	TArray<FPodModel> DeletedPods;
	for (FPodModel SnapshotPod : PodsSnapshot) {

		UE_LOG(LogTemp, Warning, TEXT("-- Snapshot pod: %s"), *SnapshotPod.Name);

		bool IsPodFoundInList = false;
		for (FPodModel ListPod : *FullPodsList) { // TODO: Replace with TArray.FindByPredicate
			if (SnapshotPod.Name == ListPod.Name) {
				IsPodFoundInList = true;
				break;
			}
		}

		if (!IsPodFoundInList) {
			DeletedPods.Add(SnapshotPod);
			UE_LOG(LogTemp, Warning, TEXT("Pod missing is snapshot: %s"), *SnapshotPod.Name);
		}
	}

	return DeletedPods;
}

FStateDiff AKuberMonitorGameState::GetStateDiff(TArray<FPodModel>* FullPodsList)
{
	FStateDiff StateDiff = FStateDiff();

	StateDiff.NewPods = GetNewPods(FullPodsList);
	StateDiff.DeletedPods = GetDeletedPods(FullPodsList);
	StateDiff.PhaseChangedPods = GetPhaseChangedPods(FullPodsList);

	PodsSnapshot = *FullPodsList;

	return StateDiff;
}
