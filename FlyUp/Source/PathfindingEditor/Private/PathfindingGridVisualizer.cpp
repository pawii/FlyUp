#include "PathfindingGridVisualizer.h"
#include "PathfindingGridComponent.h"
#include "PathfindingGridHitProxies.h"
#include "SceneManagement.h"

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
		PDI->DrawPoint(TargetingComponent->Bounds.Min, BoundsMinColor, 10, SDPG_Foreground);
		
		PDI->SetHitProxy(new HPathfindingGridProxy(Component, 1));
		const FLinearColor& BoundsMaxColor = (SelectedPointIndex == 1) ? FLinearColor::Green : FLinearColor::Red;
		PDI->DrawPoint(TargetingComponent->Bounds.Max, BoundsMaxColor, 10, SDPG_Foreground);
		
		PDI->SetHitProxy(nullptr);
		DrawWireBox(PDI, TargetingComponent->Bounds, FLinearColor::White, SDPG_Foreground);
		
		for (const FNodeGrid Node: TargetingComponent->Nodes)
		{
			const FLinearColor& NodeColor = Node.bWalkable ? FColor::Green : FColor::Red;
			const FBox& NodeBounds =
				FBox(TargetingComponent->Bounds.Min + Node.LocalPosition,
					TargetingComponent->Bounds.Min + Node.LocalPosition + FVector:: OneVector * TargetingComponent->GridNodeSize);
			DrawWireBox(PDI, NodeBounds, NodeColor, SDPG_Foreground);
		}
	}
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

	if (GetEditedGridComponent() && SelectedPointIndex != INDEX_NONE)
	{
		if (SelectedPointIndex == 0)
		{
			GetEditedGridComponent()->Bounds.Min += DeltaTranslate;
		}
		else
		{
			GetEditedGridComponent()->Bounds.Max += DeltaTranslate;
		}

		bHandled = true;
	}

	return bHandled;
}

UPathfindingGridComponent* FPathfindingGridVisualizer::GetEditedGridComponent() const
{
	return Cast<UPathfindingGridComponent>(GridComponentPropertyPath.GetComponent());
}
