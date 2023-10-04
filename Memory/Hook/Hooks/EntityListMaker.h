#pragma once

void* __o__ActorRuntimeID;

uint64_t* ActorRuntimeIDDetour(__int64 a1, uint64_t *a2) {

    uint64_t* oFunc = Utils::CallFunc<uint64_t*, __int64, uint64_t*>(
        __o__ActorRuntimeID,
        a1, 
        a2
    );

    //g_Data.entitylist[oFunc] = ;

    return oFunc;
}

class ActorRuntimeIDHook : public FuncHook {
public:
    bool Initialize() override {
        void* renderAddr = Utils::findSig("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24");
        return Utils::HookFunction(renderAddr, (void*)&ActorRuntimeIDDetour, &__o__ActorRuntimeID);
    }

    static ActorRuntimeIDHook& Instance() {
        static ActorRuntimeIDHook instance;
        return instance;
    }
};