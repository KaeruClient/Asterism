#pragma once
#include "../../../Managers/ModuleManager.h"
void* __o__SendKey;

void keymapDetour(__int32 key, bool held) {
    Global::keymap[key] = held;
    if (held) {
        moduleMgr->onKey(key);
        auto clickgui = moduleMgr->getModule<ClickGui>();
        if (clickgui != nullptr) {
            if (clickgui->waitkey) {
                if (clickgui->waitmodule != nullptr) {
                    clickgui->waitmodule->setBind(key);
                    clickgui->waitkey = false; 
                    clickgui->waitmodule = nullptr;
                }
            }
        }
    }
    logstr(Utils::combine("Key ", key, " ", held, "\n").c_str());
    Utils::CallFunc<void*, __int32, bool>(
        __o__SendKey,
        key,
        held
    );
}

class KeymapHook : public FuncHook {
public:
    bool Initialize() override
    {
        void* keymapAddr = Utils::findSig("48 83 EC ? ? ? C1 4C 8D 05 ? ? ? ? 89 54 24 20");
        return Utils::HookFunction(
            keymapAddr,
            (void*)&keymapDetour,
            &__o__SendKey
        );
    }

    static KeymapHook& Instance() {
        static KeymapHook instance;
        return instance;
    }
};