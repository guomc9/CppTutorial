#include "CppTutorialEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FCppTutorialEditorModule, CppTutorialEditor);

void FCppTutorialEditorModule::StartupModule()
{
    // Check if editor is valid
    if (GUnrealEd)
    {
        // Registerin the move visualizer
        TSharedPtr<FMoveComponentVisualizer> MoveVisualizer = MakeShareable(new FMoveComponentVisualizer);
        if (MoveVisualizer.IsValid())
        {
            GUnrealEd->RegisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName(), MoveVisualizer);
            MoveVisualizer->OnRegister();
        }
    }
}

void FCppTutorialEditorModule::ShutdownModule()
{
    // Check if editor is valid
    if (GUnrealEd)
    {
        GUnrealEd->UnregisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName());
    }
}