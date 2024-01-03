#include "PathfindingGridVisualizer.h"
#include "PathfindingGridComponent.h"
#include "PathfindingGridHitProxies.h"
#include "SceneManagement.h"
#include "Animation/Rig.h"

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
		PDI->SetHitProxy(new HPathfindingGridProxy(Component, 0));
		const FLinearColor& BoundsMinColor = (SelectedPointIndex == 0) ? FLinearColor::Green : FLinearColor::Red;
		PDI->DrawPoint(TargetingComponent->GetBoundsMinWorldPosition(), BoundsMinColor, 10, SDPG_Foreground);
		
		PDI->SetHitProxy(new HPathfindingGridProxy(Component, 1));
		const FLinearColor& BoundsMaxColor = (SelectedPointIndex == 1) ? FLinearColor::Green : FLinearColor::Red;
		PDI->DrawPoint(TargetingComponent->GetBoundsMaxWorldPosition(), BoundsMaxColor, 10, SDPG_Foreground);
		
		PDI->SetHitProxy(nullptr);
		DrawWireBox(PDI, TargetingComponent->Bounds, FLinearColor::White, SDPG_Foreground);
		
		for (const FNodeGrid& Node: TargetingComponent->Nodes)
		{
			if (!Node.bWalkable)
			{
				DrawNode(PDI, Node, FColor::Red);
			}
		}

		if (TargetingComponent->StartPoint)
		{
			FNodeGrid ClosestNode = TargetingComponent->FindClosestNode(TargetingComponent->StartPoint->GetActorLocation());
			DrawNode(PDI, ClosestNode, FColor::Green);
			DrawWireSphere(PDI, TargetingComponent->StartPoint->GetActorLocation(), FColor::Red, 10, 100, 0);
		}
	}
}

void FPathfindingGridVisualizer::DrawNode(FPrimitiveDrawInterface* PDI, const FNodeGrid& Node, const FLinearColor& Color) const
{
	const FBox& NodeBounds =
		FBox(Node.WorldPosition,
			Node.WorldPosition + FVector::OneVector * Node.Size);
	DrawWireBox(PDI, NodeBounds, Color, SDPG_World);
}

bool FPathfindingGridVisualizer::VisProxyHandleClick(FEditorViewportClient* InViewportClient,
	HComponentVisProxy* VisProxy, const FViewportClick& Click)
{
	bool bEditing = false;

	if (VisProxy && VisProxy->Component.IsValid())
	{
		bEditing = true;

		if (VisProxy->IsA(HPathfindingGridProxy::StaticGetType()))
		{
			const HPathfindingGridProxy* Proxy = static_cast<HPathfindingGridProxy*>(VisProxy);
			SelectedPointIndex = Proxy->PointIndex;
			
			const UPathfindingGridComponent* GridComponent = Cast<const UPathfindingGridComponent>(VisProxy->Component.Get());
			GridComponentPropertyPath = FComponentPropertyPath(GridComponent);
		}
	}
	else
	{
		SelectedPointIndex = INDEX_NONE;
	}
	
	return bEditing;
}

bool FPathfindingGridVisualizer::GetWidgetLocation(const FEditorViewportClient* ViewportClient,
	FVector& OutLocation) const
{
	if (GetEditedGridComponent() && SelectedPointIndex != INDEX_NONE)
	{
		if (SelectedPointIndex == 0)
		{
			OutLocation = GetEditedGridComponent()->Bounds.Min;
		}
		else
		{
			OutLocation = GetEditedGridComponent()->Bounds.Max;
		}
        
		return true;
	}

	return false;
}

bool FPathfindingGridVisualizer::HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport,
	FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale)
{
	bool bHandled = false;

	UPathfindingGridComponent* GridComponent = GetEditedGridComponent();
	if (GridComponent && SelectedPointIndex != INDEX_NONE)
	{
		if (SelectedPointIndex == 0)
		{
			GridComponent->Bounds.Min = GridComponent->GetBoundsMinWorldPosition() + DeltaTranslate;
		}
		else
		{
			GridComponent->Bounds.Max = GridComponent->GetBoundsMaxWorldPosition() + DeltaTranslate;
		}

		if (DeltaTranslate != FVector::ZeroVector)
		{
			GridComponent->Modify();
		}

		bHandled = true;
	}

	return bHandled;
}

UPathfindingGridComponent* FPathfindingGridVisualizer::GetEditedGridComponent() const
{
	return Cast<UPathfindingGridComponent>(GridComponentPropertyPath.GetComponent());
}
