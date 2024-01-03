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
	UPathfindingGridComponent();
	
	UPROPERTY(EditAnywhere, Category="Grid")
	float GridNodeSize;
	
	UPROPERTY(EditAnywhere, Category="Grid")
	FBox Bounds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Grid")
	TArray<FNodeGrid> Nodes;

	UPROPERTY(EditAnywhere, Category="Grid")
	AActor* StartPoint;

	UPROPERTY(EditAnywhere, Category="Grid")
	AActor* EndPoint;

	FVector GetBoundsMinWorldPosition() const;
	FVector GetBoundsMaxWorldPosition() const;
	FNodeGrid FindClosestNode(FVector Location) const;
	
private:
	UFUNCTION(BlueprintCallable, CallInEditor)
	void BakeGrid();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void ResetGrid();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void CalculatePath();
	
	int FindNodeIDAlongSpecificAxis(const double& Position, const double& BoundsMin, int CountNodes) const;
};
