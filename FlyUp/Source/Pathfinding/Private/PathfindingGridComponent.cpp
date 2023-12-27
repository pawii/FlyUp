#include "PathfindingGridComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UPathfindingGridComponent::UPathfindingGridComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

FVector UPathfindingGridComponent::GetBoundsMinWorldPosition() const
{
	return Bounds.Min + GetOwner()->GetActorLocation();
}

FVector UPathfindingGridComponent::GetBoundsMaxWorldPosition() const
{
	return Bounds.Max + GetOwner()->GetActorLocation();
}

void UPathfindingGridComponent::BakeGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("Bake Pressed"));

	Nodes.Empty();
	FVector NodeHalfSize = FVector::OneVector * GridNodeSize * 0.5f;
	FVector BoundsMin = GetBoundsMinWorldPosition();
	FVector BoundsMax = GetBoundsMaxWorldPosition();

	for (float x = BoundsMin.X; x < BoundsMax.X; x+= GridNodeSize)
	{
		for (float y = BoundsMin.Y; y < BoundsMax.Y; y += GridNodeSize)
		{
			for (float z = BoundsMin.Z; z < BoundsMax.Z; z += GridNodeSize)
			{
				TArray<AActor*> ActorsToIgnore;
				FNodeGrid Node;
				Node.WorldPosition = FVector(x, y, z);
				Node.Size = GridNodeSize;
				
				FVector NodeCenter = Node.WorldPosition + FVector::One() * GridNodeSize * 0.5f;
				FHitResult HitResult;
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
				
				Nodes.Add(Node);
			}
		}
	}

	Modify();
}

void UPathfindingGridComponent::ResetGrid()
{
	Bounds = FBox(GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + FVector::OneVector * 1000);
	GridNodeSize = 100;
	Nodes.Empty();
	Modify();
}

void UPathfindingGridComponent::CalculatePath()
{
	
}