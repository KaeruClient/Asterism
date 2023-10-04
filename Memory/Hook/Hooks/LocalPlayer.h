#pragma once

// Declare a void pointer(Empty object) called __o__BaseUseItem
void* __o__select;
ItemStack* getSelectedItem(Actor* _this) {
    ItemStack* oFunc = Utils::CallFunc<ItemStack*, Actor*>(
        __o__select,
        _this
    );
    if (Global::rightclick)
    g_Data.getGameMode()->baseUseItem(*oFunc);
    return oFunc;
}

class BaseUseItemHook : public FuncHook {
public:

    bool Initialize() override
    {
        auto selecteditem = Utils::findSig("48 8B 91 C0 07 00 00 80 BA B8 00 00 00 00 75 18 48 8B 8A C0 00 00 00 8B 52 10 48 8B 01 48 8B 40 28");
        return Utils::HookFunction(
            selecteditem,
            (void*)&getSelectedItem,
            &__o__select
        );
    }

    static BaseUseItemHook& Instance() {
        static BaseUseItemHook instance;
        return instance;
    }
};