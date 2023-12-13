// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PathfindingGridComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PATHFINDING_API UPathfindingGridComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPathfindingGridComponent();

	UPROPERTY(EditAnywhere, Category="Grid")
	FBox Bounds;
	
private:
	UPROPERTY(EditAnywhere, Category="Grid")
	float GridNodeSize;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void Bake();

};
