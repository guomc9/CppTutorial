#pragma once

#include "Engine.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UnrealEd.h"

#include "CppTutorial/MoveComponentVisualizer.h"


DECLARE_LOG_CATEGORY_EXTERN(CppTutorialEditor, All, All)

class FCppTutorialEditorModule: public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};