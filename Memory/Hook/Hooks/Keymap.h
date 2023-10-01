#pragma once

void* __o__SendKey;

HMODULE getDll() {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)getDll, &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? (HMODULE)info.AllocationBase : NULL;
};
void EjectClient(HMODULE DllModule) { // âJÇ∑Ç≤Ç¢,,âJç~Ç¡ÇƒÇ»Ç¢ÅI (PROî≈ÇÃÇ›)
    FuncHook::Restore(); 
    FreeLibraryAndExitThread(DllModule, 0);
}

void keymapDetour(__int32 key, bool held) {
    GameData::keymap[key] = held;
    if (GameData::keymap['L'] && GameData::keymap[17])
        EjectClient(getDll());
    log(Utils::combine("Key ", key, " ", held, "\n").c_str());
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