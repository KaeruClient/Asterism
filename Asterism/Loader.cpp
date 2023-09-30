#pragma region Includes & Macros

// C++ Includes
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>

// Minhook
#include "../Memory/minhook.h"
// Utils
#include "../Utils/Global.h"
#include "../Utils/Utils.h"

// Maths
#include "../SDK/Maths/TextHolder.h"
#include "../SDK/Maths/UIColor.h"
#include "../SDK/Maths/Vector2.h"
#include "../SDK/Maths/Vector3.h"
#include "../SDK/Maths/Vector4.h"
#include "../SDK/Maths/BlockPos.h"

// Hooks
#include "../Memory/Hook/FuncHook.h"
#pragma endregion
// This function initializes the client.
void InitializeClient(HMODULE module) {
    InitializeHooks();
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) {
        // Prevent the DLL from being unloaded
        DisableThreadLibraryCalls(module);

        // Create a new thread to initialize the client on
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitializeClient, module, 0, 0);
    }
    return true;
}