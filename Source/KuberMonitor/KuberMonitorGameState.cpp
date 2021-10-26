#include "KuberMonitorGameState.h"

TArray<FPodModel> AKuberMonitorGameState::GetNewPods(TArray<FPodModel>* PodsList, FString Namespace) const
{
	const TArray<FPodModel>* NamespaceSnapshotPods = PodsSnapshot.Find(Namespace);
	if (!NamespaceSnapshotPods) {
		return *PodsList;
	}

	TArray<FPodModel> NewPods;
	for (FPodModel ListPod : *PodsList) {

		bool IsPodKnown = false;
		for (FPodModel SnapshotPod : *NamespaceSnapshotPods) { // TODO: Replace with TArray.FindByPredicate
			if (SnapshotPod.Name == ListPod.Name) {
				IsPodKnown = true;
				break;
			}
		}

		if (!IsPodKnown) {
			NewPods.Add(ListPod);
			UE_LOG(LogTemp, Warning, TEXT("New POD: %s"), *ListPod.Name);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("POD: %s is KNOWN"), *ListPod.Name);
		}

	}

	return NewPods;
}

TArray<FPodModel> AKuberMonitorGameState::GetPhaseChangedPods(TArray<FPodModel>* PodsList, FString Namespace) const
{
	const TArray<FPodModel>* NamespaceSnapshotPods = PodsSnapshot.Find(Namespace);
	if (!NamespaceSnapshotPods) {
		return TArray<FPodModel>();
	}

	TArray<FPodModel> PhaseChangedPods;
	for (FPodModel SnapshotPod : *NamespaceSnapshotPods) {
		for (FPodModel ListPod : *PodsList) { // TODO: Replace with TArray.FindByPredicate
			UE_LOG(LogTemp, Warning, TEXT("Pod %s phase is phase: %s"), *ListPod.Name, *ListPod.Phase);

			if (SnapshotPod.Name == ListPod.Name && SnapshotPod.Phase != ListPod.Phase) {
				UE_LOG(LogTemp, Warning, TEXT("Pod changed phase: %s"), *ListPod.Name);
				PhaseChangedPods.Add(ListPod);
			}
		}
	}

	return PhaseChangedPods;
}

TArray<FPodModel> AKuberMonitorGameState::GetDeletedPods(TArray<FPodModel>* PodsList, FString Namespace) const
{
	const TArray<FPodModel>* NamespaceSnapshotPods = PodsSnapshot.Find(Namespace);
	if (!NamespaceSnapshotPods) {
		return TArray<FPodModel>();
	}
	
	TArray<FPodModel> DeletedPods;
	for (FPodModel SnapshotPod : *NamespaceSnapshotPods) {
		bool IsPodFoundInList = false;
		for (FPodModel ListPod : *PodsList) { // TODO: Replace with TArray.FindByPredicate
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

FStateDiff AKuberMonitorGameState::GetStateDiff(TArray<FPodModel>* PodsList, FString* Namespace)
{
	FStateDiff StateDiff = FStateDiff();

	UE_LOG(LogTemp, Warning, TEXT("GETTIN STATE DIFF"));

	StateDiff.NewPods = GetNewPods(PodsList, *Namespace);
	StateDiff.DeletedPods = GetDeletedPods(PodsList, *Namespace);
	StateDiff.PhaseChangedPods = GetPhaseChangedPods(PodsList, *Namespace);

	PodsSnapshot.Add(*Namespace, *PodsList);

	return StateDiff;
}
