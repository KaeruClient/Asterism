#pragma once

void* __o__sd;

__int64 sdDetour(Actor* _this) {
    auto oFunc = Utils::CallFunc<__int64, Actor*>(
        __o__sd,
        _this
    );
    return 70;
    return oFunc;
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