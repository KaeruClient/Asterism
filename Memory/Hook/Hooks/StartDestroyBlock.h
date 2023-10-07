#pragma once

// Declare a void pointer(Empty object) called __o__GameMode
void* __o__SDB;

void SDBDetour(GameMode* _this, vec3_ti* a2, uint8_t face, void* a4, void* a5) {
    auto pm = moduleMgr->getModule<PacketMine>();
    g_Data.setGameMode(_this);
    if (pm->isEnabled()) {
        pm->face = face;
        pm->pos = *a2;
        pm->packetmine = true;
        pm->odelay = 0;
    }
    Utils::CallFunc<void*, GameMode*, vec3_ti*, uint8_t, void*, void*>(
        __o__SDB,
        _this,
        a2,
        face,
        a4,
        a5
    );
}

class StartDestroyBlockHook : public FuncHook {
public:

    bool Initialize() override
    {
        return Utils::HookFunction(
            Global::gmvtable[1],
            (void*)&SDBDetour,
            &__o__SDB
        );
    }

    static StartDestroyBlockHook& Instance() {
        static StartDestroyBlockHook instance;
        return instance;
    }
};