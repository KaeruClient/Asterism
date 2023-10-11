#pragma once
#include "../../../SDK/Structs/GameMode.h"

// Declare a void pointer(Empty object) called __o__Tick
void* __o__Tick;

void TickDetour(GameMode* gm) {
    Utils::CallFunc<void, GameMode*>(
        __o__Tick,
        gm
    );
}

class TickHook : public FuncHook {
public:

    bool Initialize() override
    {
        return Utils::HookFunction(
            Global::gmvtable[9],
            (void*)&TickDetour,
            &__o__Tick
        );
    }

    static TickHook& Instance() {
        static TickHook instance;
        return instance;
    }
};