// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeGrid.h"

/**
 * 
 */
class PATHFINDING_API PathfindingPath
{
public:
	PathfindingPath();
	~PathfindingPath();

	FNodeGrid& StartNode;
	FNodeGrid& EndNode;
};
