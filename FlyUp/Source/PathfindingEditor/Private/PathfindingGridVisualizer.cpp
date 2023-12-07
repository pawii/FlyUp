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
		//PDI->DrawPoint(TargetingComponent->Bounds.Min, FLinearColor::Red, 1, SDPG_World);
		const FLinearColor& Point0Color = (SelectedPointIndex == 0) ? FLinearColor::Green : FLinearColor::Red;
		PDI->DrawPoint(TargetingComponent->Point0, Point0Color, 10, SDPG_World);
		
		PDI->SetHitProxy(new HPathfindingGridProxy(Component, 1));
		//PDI->DrawPoint(TargetingComponent->Bounds.Max, FLinearColor::Red, 1, SDPG_World);
		const FLinearColor& Point1Color = (SelectedPointIndex == 1) ? FLinearColor::Green : FLinearColor::Red;
		PDI->DrawPoint(TargetingComponent->Point1, Point1Color, 10, SDPG_World);
		PDI->SetHitProxy(nullptr);
		
		DrawWireBox(PDI, TargetingComponent->Bounds, FLinearColor::Red, SDPG_World);
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
	if (GetEditedPathfindingGridComponent() && SelectedPointIndex != INDEX_NONE)
	{
		if (SelectedPointIndex == 0)
		{
			OutLocation = GetEditedPathfindingGridComponent()->Point0;
		}
		else
		{
			OutLocation = GetEditedPathfindingGridComponent()->Point1;
		}
        
		return true;
	}

	return false;
}

bool FPathfindingGridVisualizer::HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport,
	FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale)
{
	bool bHandled = false;

	if (GetEditedPathfindingGridComponent() && SelectedPointIndex != INDEX_NONE)
	{
		if (SelectedPointIndex == 0)
		{
			GetEditedPathfindingGridComponent()->Point0 += DeltaTranslate;
		}
		else
		{
			GetEditedPathfindingGridComponent()->Point1 += DeltaTranslate;
		}

		bHandled = true;
	}

	return bHandled;
}

UPathfindingGridComponent* FPathfindingGridVisualizer::GetEditedPathfindingGridComponent() const
{
	return static_cast<UPathfindingGridComponent*>(GetEditedComponent());
}
