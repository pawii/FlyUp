#include "PathfindingEditorModule.h"
#include "PathfindingGridVisualizer.h"
#include "PathfindingGridComponent.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FPathfindingEditorModule, PathfindingEditor);

DEFINE_LOG_CATEGORY(PathfindingEditor)

#define LOCTEXT_NAMESPACE "PathfindingEditor"

void FPathfindingEditorModule::StartupModule()
{
	if (GUnrealEd != NULL)
	{
		TSharedPtr<FPathfindingGridVisualizer> Visualizer = MakeShareable(new FPathfindingGridVisualizer);
    
		if (Visualizer.IsValid())
		{
			GUnrealEd->RegisterComponentVisualizer(UPathfindingGridComponent::StaticClass()->GetFName(), Visualizer);
			Visualizer->OnRegister();
		}
	}
}

void FPathfindingEditorModule::ShutdownModule()
{
	if (GUnrealEd != NULL)
	{
		GUnrealEd->UnregisterComponentVisualizer(UPathfindingGridComponent::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE