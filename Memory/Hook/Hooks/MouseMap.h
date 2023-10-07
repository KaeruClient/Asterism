#pragma once
#include "../Includes/imgui/imgui.h"

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