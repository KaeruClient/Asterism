#pragma once
// Declare a void pointer(Empty object) called __o__GameMode
void* __o__GameMode;

float GameModeDetour(GameMode* gm, void* a1, void* a2, void* a3) {
    if (gm != nullptr) g_Data.setGameMode(gm);
    float oFunc = Utils::CallFunc<float, GameMode*, void*, void*, void*>(
        __o__GameMode,
        gm,
        a1,
        a2,
        a3
    );
    //log("woah");
    return oFunc;
}

class GameModeHook : public FuncHook {
public:

    bool Initialize() override
    {
        uintptr_t sigOffset = (uintptr_t)Utils::findSig("48 8D 05 ? ? ? ? 48 89 01 48 89 51 ? 48 C7 41 ? FF FF FF FF C7 41 ? FF FF FF FF");
        int offset = *reinterpret_cast<int*>(sigOffset + 3);
        uintptr_t** vtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*–½—ß‚Ì’·‚³*/ 7);
        Global::gmvtable = vtable;
        return Utils::HookFunction(
            vtable[10],
            (void*)&GameModeDetour,
            &__o__GameMode
        );
    }

    static GameModeHook& Instance() {
        static GameModeHook instance;
        return instance;
    }
};