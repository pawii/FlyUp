// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeGrid.h"
#include "GridArray.generated.h"

/**
 * 
 */
UCLASS()
class PATHFINDING_API UGridArray : public UObject
{
	GENERATED_BODY()

	void Initialize(int XSize, int YSize, int ZSize);
	void Set(int X, int Y, int Z, const FNodeGrid& Node);
	FNodeGrid& Get(int X, int Y, int Z);
	bool Contains(int X, int Y, int Z) const;

private:
	UPROPERTY()
	int XSize;
	
	UPROPERTY()
	int YSize;
	
	UPROPERTY()
	int ZSize;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FNodeGrid> Nodes;

	int CalculateInnerArrayId(int X, int Y, int Z) const;
};
