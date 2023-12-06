// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"

/**
 * 
 */
class FPathfindingGridVisualizer : public FComponentVisualizer
{
public:
	FPathfindingGridVisualizer();
	virtual ~FPathfindingGridVisualizer() override;
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
};
