#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"
#include "PathfindingGridComponent.h"

class FPathfindingGridVisualizer : public FComponentVisualizer
{
public:
	FPathfindingGridVisualizer();
	virtual ~FPathfindingGridVisualizer() override;
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
	virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;
	virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;
	virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;
	
private:
	int SelectedPointIndex;
	FComponentPropertyPath GridComponentPropertyPath;

	UPathfindingGridComponent* GetEditedGridComponent() const;
	void DrawNode(FPrimitiveDrawInterface* PDI, const FNodeGrid& Node, const FLinearColor& Color) const;
};
