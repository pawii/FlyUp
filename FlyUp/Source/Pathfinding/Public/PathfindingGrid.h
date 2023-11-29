// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathfindingGrid.generated.h"

UCLASS()
class PATHFINDING_API APathfindingGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	APathfindingGrid();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void BuildGrid();

protected:
	virtual void BeginPlay() override;
};
