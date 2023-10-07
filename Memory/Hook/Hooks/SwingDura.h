#pragma once

void* __o__sd;

__int64 sdDetour(Actor* _this) {//_thisがentitylistなんだよなぁww
    auto oFunc = Utils::CallFunc<__int64, Actor*>(//死刑死刑死刑死刑！！！死刑！！！！！！！！！！！！！！！！
        __o__sd,
        _this
    );
    //g_Data.getGameMode()->attack(*g_Data.getEntityList()[0]);
    return 20;
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