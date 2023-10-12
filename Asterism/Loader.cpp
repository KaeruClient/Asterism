#include "Loader.h"
#include "../Managers/ModuleManager.h"

bool eject = false;
auto GetDllMod(void) -> HMODULE {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)GetDllMod, &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? (HMODULE)info.AllocationBase : NULL;
}
DWORD WINAPI EjectClient(LPVOID a) {
    while (!eject) Sleep(100);
    Sleep(1000);
    FreeLibraryAndExitThread(GetDllMod(), 1);
    return 1;
}
// この関数はクライアントの初期設定をするものです

void InitializeClient(HMODULE module) {
    moduleMgr->initModules();
    InitializeHooks();
    while (!eject) {
        if (Global::keymap['L'] && Global::keymap[17]) {
            delete moduleMgr;
            FuncHook::Restore();
            eject = true;
        }
    }
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) {
        // Prevent the DLL from being unloaded
        DisableThreadLibraryCalls(module);
        // Create a new thread to initialize the client on
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitializeClient, module, 0, 0);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ImguiHooks::InitImgui, module, 0, 0);
        CreateThread(0, 0, &EjectClient, 0, 0, 0);
    }
    return true;
}