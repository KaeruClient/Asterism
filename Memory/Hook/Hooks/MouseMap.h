#pragma once


#define WIN32_LEAN_AND_MEAN
// C++ Includes
#include <d3d11.h>
#include <d3d10.h>
#include <d3d12.h>
#include <d3d.h>

#include <winerror.h>
#include <windef.h>
#include <WinUser.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <Psapi.h>

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <basetsd.h>

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <cmath>

#include "../Includes/imgui/imgui.h"
#include "../Includes/imgui/imgui_impl_win32.h"
#include "../Includes/imgui/imgui_impl_dx12.h"
#include "../Includes/imgui/imgui_impl_dx11.h"
#include <initguid.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3d12.h>
#include <d2d1_1.h>
#include <dxgi1_4.h>
#include <dwrite_1.h>
#include "../Includes/kiero/kiero.h"
#include <d3d11.h>
#include <d3d10.h>
#include <d3d12.h>
#include <d3d.h>

#include <winerror.h>
#include <windef.h>
#include <WinUser.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <Psapi.h>

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <basetsd.h>


void* __o__mouse;

void MouseDetour(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
    if (ImGui::GetCurrentContext() != nullptr) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(mouseX, mouseY);

        switch (mouseButton) {
        case 1:
            io.MouseDown[0] = isDown;
            break;
        case 2:
            io.MouseDown[1] = isDown;
            break;
        case 3:
            io.MouseDown[2] = isDown;
            break;
        case 4:
            io.MouseWheel = isDown < 0 ? -0.5f : 0.5f; //For scrolling
            break;
        default:
            break;
        }
    }
    Utils::CallFunc<void, __int64, char, char, __int16, __int16, __int16, __int16, char>(
        __o__mouse,
        a1,
        mouseButton,
        isDown,
        mouseX,
        mouseY,
        relativeMovementX,
        relativeMovementY,
        a8
    );
    if (mouseButton == 2) 
        Global::rightclick = isDown;
}

class MouseMapHook : public FuncHook {
public:
    bool Initialize() override {
        void* renderAddr = Utils::findSig("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24");
        return Utils::HookFunction(renderAddr, (void*)&MouseDetour, &__o__mouse);
    }

    static MouseMapHook& Instance() {
        static MouseMapHook instance;
        return instance;
    }
};