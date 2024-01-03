// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingPath.h"

PathfindingPath::PathfindingPath(): StartNode(*new FNodeGrid()), EndNode(*new FNodeGrid())
{
}

PathfindingPath::~PathfindingPath()
{
	UE_LOG(LogTemp, Warning, TEXT("destructor PathfindingPath"))
	delete &StartNode;
	delete &EndNode;
}
