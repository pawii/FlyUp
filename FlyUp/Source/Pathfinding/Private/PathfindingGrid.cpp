// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingGrid.h"

APathfindingGrid::APathfindingGrid()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APathfindingGrid::BeginPlay()
{
	Super::BeginPlay();
}

void APathfindingGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APathfindingGrid::BuildGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("Build Grid called"));
}

