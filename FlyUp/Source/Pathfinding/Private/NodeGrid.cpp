#include "NodeGrid.h"

FNodeGrid::FNodeGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("constructor FNodeGrid"))
}

FNodeGrid::~FNodeGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("destructor FNodeGrid"))
}

int FNodeGrid::CalculateFCost() const
{
	return GCost + HCost;
}
