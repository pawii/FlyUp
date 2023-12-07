#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"

struct HPathfindingGridVisProxy : public HComponentVisProxy
{
	DECLARE_HIT_PROXY();

	HPathfindingGridVisProxy (const UActorComponent* InComponent)
	: HComponentVisProxy(InComponent, HPP_Wireframe)
	{}
};

struct HPathfindingGridProxy : public HPathfindingGridVisProxy 
{
	DECLARE_HIT_PROXY();

	HPathfindingGridProxy (const UActorComponent* InComponent, int32 InPointIndex)
	: HPathfindingGridVisProxy (InComponent)
	, PointIndex(InPointIndex)
	{}

	int32 PointIndex;
};