#include "PathfindingGridComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UPathfindingGridComponent::UPathfindingGridComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPathfindingGridComponent::BakeGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("Bake Pressed"));

	Nodes.Empty();
	FVector NodeHalfSize = FVector::OneVector * GridNodeSize * 0.5f;

	for (float x = Bounds.Min.X; x < Bounds.Max.X; x+= GridNodeSize)
	{
		for (float y = Bounds.Min.Y; y < Bounds.Max.Y; y += GridNodeSize)
		{
			for (float z = Bounds.Min.Z; z < Bounds.Max.Z; z += GridNodeSize)
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
	Bounds = FBox(FVector::ZeroVector, FVector::OneVector * 1000);
	GridNodeSize = 100;
	Nodes.Empty();
	Modify();
}

