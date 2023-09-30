#pragma once
#include "../../../SDK/Structs/GameMode.h"
// Declare a void pointer(Empty object) called __o__GameMode
void* __o__GameMode;

void* GameModeDetour() {
}

class GameModeHook : public FuncHook {
public:
    bool Initialize() override
    {
        void* GameModeAddr = Utils::findSig("44 0F B6 11 48 8D 0D");

        return Utils::HookFunction(
            GameModeAddr,
            (void*)&GameModeDetour,
            &__o__GameMode
        );
    }

    static GameModeHook& Instance() {
        static GameModeHook instance;
        return instance;
    }
};