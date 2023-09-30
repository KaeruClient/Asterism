#pragma once
void* __o__flux;
bool fluxDetour() {
    return true;
}
class FluxSwingHook : public FuncHook {
public:
    bool Initialize() override
    {
        void* fluxAddr = Utils::findSig("8B 81 98 0B 00 00 C3");
        return Utils::HookFunction(fluxAddr, (void*)&fluxDetour, &__o__flux);
    }
    static FluxSwingHook& Instance() {
        static FluxSwingHook instance;
        return instance;
    }
};