// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeGrid.h"
#include "Components/ActorComponent.h"
#include "PathfindingGridComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PATHFINDING_API UPathfindingGridComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, Category="Grid")
	FBox Bounds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Grid")
	TArray<FNodeGrid> Nodes;
	
	UPathfindingGridComponent();
	
private:
	UPROPERTY(EditAnywhere, Category="Grid")
	float GridNodeSize;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void Bake();
};
