#pragma once

void* __o__progress;
float progressDetour(void* inv, void* block) {
    if (GameData::keymap['R']) 
    return INFINITY;
    return Utils::CallFunc<float, void*, void*>(
        __o__progress,
        inv,
        block
    );
}
class DestroyProgressHook : public FuncHook {
public:
    bool Initialize() override
    {
        void* fluxAddr = Utils::findSig("48 89 5C 24 ? 57 48 83 EC 40 48 8B FA 0F 29 74 24 ? 48 8B 91");//java bypass C6 81 88 19 00 00 00
        return Utils::HookFunction(fluxAddr, (void*)&progressDetour, &__o__progress);
    }
    static DestroyProgressHook& Instance() {
        static DestroyProgressHook instance;
        return instance;
    }
};