#pragma once
void* __o__drawBG;
void drawBackGroundDetour() {
}
class DrawBackGroundHook : public FuncHook {
public:
    bool Initialize() override
    {
        void* bgAddr = Utils::findSig("48 8b c4 48 89 58 ? 48 89 70 ? 55 57 41 55 41 56 41 57 48 8d 6c 24 ? 48 81 ec ? ? ? ? 0f 29 70 ? 0f 29 78 ? 44 0f 29 40 ? 48 8b 05");
        return Utils::HookFunction(bgAddr, (void*)&drawBackGroundDetour, &__o__drawBG);
    }
    static DrawBackGroundHook& Instance() {
        static DrawBackGroundHook instance;
        return instance;
    }
};