#pragma once

#include "CoreMinimal.h"
#include "NodeGrid.generated.h"

USTRUCT(BlueprintType)
struct FNodeGrid
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector WorldPosition;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Size;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bWalkable;
};
