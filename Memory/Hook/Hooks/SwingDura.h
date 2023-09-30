#pragma once

void* __o__sd;

__int64 sdDetour() {
    return 20;
}

class SwingDuraHook : public FuncHook {
public:
    bool Initialize() override {
        void* renderAddr = Utils::findSig("48 89 5C 24 ? 57 48 83 EC 20 48 8B 15");
        return Utils::HookFunction(renderAddr, (void*)&sdDetour, &__o__sd);
    }

    static SwingDuraHook& Instance() {
        static SwingDuraHook instance;
        return instance;
    }
};