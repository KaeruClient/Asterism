#pragma once

void* __o__progress;
float progressDetour(Actor* ent) {
    return true;
    return Utils::CallFunc<bool, Actor*>(
        __o__progress,
        ent
    );
}
class DestroyProgressHook : public FuncHook {
public:
    bool Initialize() override
    {
        void* fluxAddr = Utils::findSig("E8 ? ? ? ? 0F B6 E8 84 C0 0F 84 ? ? ? ? 49 8B 0E");//java bypass C6 81 88 19 00 00 00
        return Utils::HookFunction(fluxAddr, (void*)&progressDetour, &__o__progress);
    }
    static DestroyProgressHook& Instance() {
        static DestroyProgressHook instance;
        return instance;
    }
};