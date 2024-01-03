#pragma once

#include "CoreMinimal.h"
#include "NodeGrid.generated.h"

USTRUCT(BlueprintType)
struct PATHFINDING_API FNodeGrid
{
	GENERATED_USTRUCT_BODY()

public:
	FNodeGrid();
	~FNodeGrid();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector WorldPosition;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Size;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bWalkable;

	int GCost;

	int HCost;

	int CalculateFCost() const;
};
