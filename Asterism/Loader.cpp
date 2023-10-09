#include "Loader.h"
#include "../Managers/ModuleManager.h"
// この関数はクライアントの初期設定をするものです
void InitializeClient(HMODULE module) {
    moduleMgr->initModules();
    InitializeHooks();
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) {
        // Prevent the DLL from being unloaded
        DisableThreadLibraryCalls(module);
        // Create a new thread to initialize the client on
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitializeClient, module, 0, 0);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ImguiHooks::InitImgui, module, 0, 0);
    }
    return true;
}