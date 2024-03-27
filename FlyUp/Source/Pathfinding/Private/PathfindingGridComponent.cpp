#include "PathfindingGridComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UPathfindingGridComponent::UPathfindingGridComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	GridArray = CreateDefaultSubobject<UGridArray>(TEXT("MyGridArray"));
}

const FNodeGrid* UPathfindingGridComponent::FindClosestNode(FVector Location) const
{
	if (!GridArray->Contains(0, 0, 0))
	{
		return nullptr;
	}
	
	const FNodeGrid* StartGridNode = GridArray->Get(0, 0, 0);
	int NodeX = GridArray->GetXSize();
	int NodeY = GridArray->GetYSize();
	int NodeZ = GridArray->GetZSize();

	for (int i = 0; i < GridArray->GetXSize() - 1; i++)
	{
		if (Location.X < StartGridNode->WorldPosition.X + (i + 1) * GridNodeSize)
		{
			NodeX = i;
		}
	}
	for (int i = 0; i < GridArray->GetYSize() - 1; i++)
	{
		if (Location.Y < StartGridNode->WorldPosition.Y + (i + 1) * GridNodeSize)
		{
			NodeY = i;
		}
	}
	for (int i = 0; i < GridArray->GetZSize() - 1; i++)
	{
		if (Location.Z < StartGridNode->WorldPosition.Z + (i + 1) * GridNodeSize)
		{
			NodeZ = i;
		}
	}
	
	return GridArray->Get(NodeX, NodeY, NodeZ);
}

void UPathfindingGridComponent::FindNeighbours(const FNodeGrid& Origin, TArray<FNodeGrid>& Neighbours) const
{
	// FVector BoundsMin = GetBoundsMinWorldPosition();
	// FVector BoundsMax = GetBoundsMaxWorldPosition();
	//
	// int CountNodesAlongX = ((BoundsMax.X - BoundsMin.X) / GridNodeSize) + 1;
	// int CountNodesAlongY = ((BoundsMax.Y - BoundsMin.Y) / GridNodeSize) + 1;
	// int CountNodesAlongZ = ((BoundsMax.Z - BoundsMin.Z) / GridNodeSize) + 1;
	//
	// int OriginId = Nodes.IndexOfByKey(Origin);
	//
	// bool bHasUpNode = OriginId % CountNodesAlongZ != 0;
	// bool bHasDownNode = OriginId % CountNodesAlongZ != 1;
	// int DownNodeId = OriginId - 1;
	//
	// Neigbours.Empty();
	// Neigbours[0] = Nodes[0];
}

FBox UPathfindingGridComponent::GetBounds() const
{
	return FBox(Bounds.Min + GetOwner()->GetActorLocation(), Bounds.Max + GetOwner()->GetActorLocation());
}

void UPathfindingGridComponent::SetBounds(FBox NewBounds)
{
	this->Bounds.Min = NewBounds.Min - GetOwner()->GetActorLocation();
	this->Bounds.Max = NewBounds.Max - GetOwner()->GetActorLocation();
}

#include <glm/glm.hpp>

void UPathfindingGridComponent::BakeGrid()
{
	glm::vec4 v(6.0f);

	UE_LOG(LogTemp, Warning, TEXT("Bake Pressed %f"), v.a);
	return;

	FVector NodeHalfSize = FVector::OneVector * GridNodeSize * 0.5f;
	FVector BoundsMin = GetBounds().Min;
	FVector BoundsMax = GetBounds().Max;

	int XSize = ((BoundsMax.X - BoundsMin.X) / GridNodeSize) + 1;
	int YSize = ((BoundsMax.Y - BoundsMin.Y) / GridNodeSize) + 1;
	int ZSize = ((BoundsMax.Z - BoundsMin.Z) / GridNodeSize) + 1;

	GridArray->Initialize(XSize, YSize, ZSize);

	for (int X = 0; X < XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
			for (int Z = 0; Z < ZSize; Z++)
			{
				FNodeGrid Node;
				Node.WorldPosition = BoundsMin + FVector(X, Y, Z) * GridNodeSize;
				Node.Size = GridNodeSize;
				
				FVector NodeCenter = Node.WorldPosition + FVector::One() * GridNodeSize * 0.5f;
				FHitResult HitResult;
				TArray<AActor*> ActorsToIgnore;
				UKismetSystemLibrary::BoxTraceSingleByProfile(
					GetWorld(),
					NodeCenter,
					NodeCenter,
					NodeHalfSize,
					FRotator::ZeroRotator,
					FName(TEXT("PathfindingProfile")),
					true,
					ActorsToIgnore,
					EDrawDebugTrace::None,
					HitResult,
					false,
					FLinearColor::Transparent,
					FLinearColor::Transparent,
					0);
				Node.bWalkable = !HitResult.bBlockingHit;
				
				GridArray->Set(X, Y, Z, Node);
			}
		}
	}

	Modify();
}

void UPathfindingGridComponent::ResetGrid()
{
	Bounds = FBox(GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + FVector::OneVector * 1000);
	GridNodeSize = 100;
	GridArray->Empty();
	Modify();
}

void UPathfindingGridComponent::CalculatePath()
{
}
