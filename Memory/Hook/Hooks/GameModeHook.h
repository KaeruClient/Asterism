#pragma once
// Declare a void pointer(Empty object) called __o__GameMode
void* __o__GameMode;

void GameModeDetour(GameMode* gm) {
    Utils::CallFunc<void, GameMode*>(
        __o__GameMode,
        gm
    );
    Global::gm = gm;
    
    gm->buildBlock(BlockPos(0, 30, 0), 0, true);
}

class GameModeHook : public FuncHook {
public:
    bool Initialize() override
    {
        uintptr_t sigOffset = (uintptr_t)Utils::findSig("48 8D 05 ? ? ? ? 48 89 01 48 89 51 ? 48 C7 41 ? FF FF FF FF C7 41 ? FF FF FF FF ");//java bypass C6 81 88 19 00 00 00
        int offset = *reinterpret_cast<int*>(sigOffset + 3);
        uintptr_t** vtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 8);

        return Utils::HookFunction(
            vtable[9],
            (void*)&GameModeDetour,
            &__o__GameMode
        );
    }

    static GameModeHook& Instance() {
        static GameModeHook instance;
        return instance;
    }
};