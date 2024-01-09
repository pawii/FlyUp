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

public:
	void Initialize(int GridXSize, int GridYSize, int GridZSize);
	void Empty();
	void Set(int X, int Y, int Z, const FNodeGrid& Node);
	const FNodeGrid* Get(int X, int Y, int Z) const;
	bool Contains(int X, int Y, int Z) const;
	int GetXSize() const;
	int GetYSize() const;
	int GetZSize() const;

	TArray<FNodeGrid>::RangedForIteratorType begin();
	TArray<FNodeGrid>::RangedForIteratorType end();

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
