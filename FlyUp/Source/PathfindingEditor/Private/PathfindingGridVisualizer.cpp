// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingGridVisualizer.h"
#include "PathfindingGridComponent.h"

FPathfindingGridVisualizer::FPathfindingGridVisualizer()
{
}

FPathfindingGridVisualizer::~FPathfindingGridVisualizer()
{
}

void FPathfindingGridVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
	if (const UPathfindingGridComponent* TargetingComponent = Cast<UPathfindingGridComponent>(Component))
	{
		PDI->DrawLine(FVector(0, 0, 0), FVector(1000, 1000, 1000), FLinearColor(1, 1, 1), SDPG_Foreground);
	}
}
