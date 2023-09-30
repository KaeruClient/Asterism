#pragma once

void* __o__javabypass;

void JavaBypass(void* p) {
    if (!Global::keymap['R']) {
        Utils::CallFunc<void*, void*>(
            __o__javabypass,
            p
        );
    }
}
class JavaBypassHook : public FuncHook {
public:
    bool Initialize() override
    {
        void* javabypassAddr = Utils::findSig("C6 81 88 19 00 00 00");
        return Utils::HookFunction(javabypassAddr, (void*)&JavaBypass, &__o__javabypass);
    }
    static JavaBypassHook& Instance() {
        static JavaBypassHook instance;
        return instance;
    }
};