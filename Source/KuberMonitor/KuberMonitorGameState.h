#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Kubernetes/PodModel.h"
#include "StateDiff.h"

#include "KuberMonitorGameState.generated.h"

UCLASS()
class KUBERMONITOR_API AKuberMonitorGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	TArray<FPodModel> PodsSnapshot;
	TArray<FPodModel> GetNewPods(TArray<FPodModel>*) const;
	TArray<FPodModel> GetDeletedPods(TArray<FPodModel>*) const;
	TArray<FPodModel> GetPhaseChangedPods(TArray<FPodModel>*) const;
	
public:
	 FStateDiff GetStateDiff(TArray<FPodModel>*);
};
