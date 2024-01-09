// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridArray.h"
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

	//TODO: make const
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Grid")
	UGridArray* GridArray;

	UPROPERTY(EditAnywhere, Category="Grid")
	AActor* StartPoint;

	UPROPERTY(EditAnywhere, Category="Grid")
	AActor* EndPoint;

	const FNodeGrid* FindClosestNode(FVector Location) const;
	void FindNeighbours(const FNodeGrid& Origin, TArray<FNodeGrid>& Neighbours) const;
	FBox GetBounds() const;
	void SetBounds(FBox NewBounds);
	
private:
	UPROPERTY(EditAnywhere, Category="Grid")
	FBox Bounds;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void BakeGrid();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void ResetGrid();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void CalculatePath();
};
