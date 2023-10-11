#pragma once
// This is an abstract base class for function hooks to inherit
class FuncHook {
public:
    // This function initializes the hook
    virtual bool Initialize() = 0;
    static void Restore() {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_RemoveHook(MH_ALL_HOOKS);
        MH_Uninitialize();
    };
};
#include "../GameData.h"
#include "../../Managers/ModuleManager.h"
#include "Hooks/Keymap.h"
#include "Hooks/RenderContext.h"
#include "Hooks/SwingDura.h"
#include "Hooks/FluxAnim.h"
#include "Hooks/GameModeHook.h"
#include "Hooks/Background.h"
#include "Hooks/getDestroyProgress.h"
#include "Hooks/JavaBypass.h"
#include "Hooks/MouseMap.h"
#include "Hooks/StartDestroyBlock.h"
#include "Hooks/onTick.h"
// This function initializes all registered function hooks
void InitializeHooks() {
    // This is an array of pointers to function hook objects
    static FuncHook* hooks[] = {
        &KeymapHook::Instance(),
        &MouseMapHook::Instance(),
        &GameModeHook::Instance(),
        &RenderContextHook::Instance(),
        &SwingDuraHook::Instance(),
        &FluxSwingHook::Instance(),
        //&DrawBackGroundHook::Instance(),
  //      &DestroyProgressHook::Instance(),
        &JavaBypassHook::Instance(),
        &StartDestroyBlockHook::Instance(),
        &TickHook::Instance()
    };
    int count = 0;
    // Iterate through all the hook objects
    for (std::size_t i = 0; i < std::size(hooks); ++i) {
        // Initialize the hook
        if (!hooks[i]->Initialize()) {
            // Handle initialization failure (Which for now we'll ignore)
        }
        ++count;
    }
    auto notification = g_Data.addInfoBox("Setup", std::to_string(count) + " hooks successfully hooked!");
    notification->duration = 10.f;
}