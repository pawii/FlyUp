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
		FBox Bounds = TargetingComponent->GetBounds();
		
		PDI->SetHitProxy(new HPathfindingGridProxy(Component, 0));
		const FLinearColor& BoundsMinColor = (SelectedPointIndex == 0) ? FLinearColor::Green : FLinearColor::Red;
		PDI->DrawPoint(Bounds.Min, BoundsMinColor, 10, SDPG_Foreground);
		
		PDI->SetHitProxy(new HPathfindingGridProxy(Component, 1));
		const FLinearColor& BoundsMaxColor = (SelectedPointIndex == 1) ? FLinearColor::Green : FLinearColor::Red;
		PDI->DrawPoint(Bounds.Max, BoundsMaxColor, 10, SDPG_Foreground);
		
		PDI->SetHitProxy(nullptr);
		DrawWireBox(PDI, Bounds, FLinearColor::White, SDPG_Foreground);

		if (!TargetingComponent->GridArray)
		{
			return;
		}
		
		// TODO: replace on foreach loop
		for (int X = 0; X < TargetingComponent->GridArray->GetXSize(); X++)
		{
			for (int Y = 0; Y < TargetingComponent->GridArray->GetYSize(); Y++)
			{
				for (int Z = 0; Z < TargetingComponent->GridArray->GetZSize(); Z++)
				{
					const FNodeGrid* Node = TargetingComponent->GridArray->Get(X, Y, Z);
					if (!Node->bWalkable)
					{
						DrawNode(PDI, *Node, FColor::Red);
					}
				}
			}
		}

		if (TargetingComponent->StartPoint)
		{
			const FNodeGrid* StartNode = TargetingComponent->FindClosestNode(TargetingComponent->StartPoint->GetActorLocation());
			if (StartNode)
			{
				DrawNode(PDI, *StartNode, FColor::Green);
				DrawWireSphere(PDI, TargetingComponent->StartPoint->GetActorLocation(), FColor::Red, 10, 100, 0);
			}
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
			OutLocation = GetEditedGridComponent()->GetBounds().Min;
		}
		else
		{
			OutLocation = GetEditedGridComponent()->GetBounds().Max;
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
		FBox Bounds = GridComponent->GetBounds();
		if (SelectedPointIndex == 0)
		{
			Bounds.Min += DeltaTranslate;
			GridComponent->SetBounds(Bounds);
		}
		else
		{
			Bounds.Max += DeltaTranslate;
			GridComponent->SetBounds(Bounds);
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
