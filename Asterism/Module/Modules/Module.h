#pragma once
#include "../../../Includes/imgui/imgui.h"
#include "../../../SDK/Structs/GameMode.h"
#include "../../../SDK/Structs/MinecraftUIRenderContext.h"
#include "../../../Memory/GameData.h"
enum class Category {
	COMBAT = 0,
	PLAYER = 1,
	WORLD = 2,
	RENDER = 3,
	MISC = 4
};

class Module {
private:
	bool enabled = false;
	const char* tooltip;
	Category category;
	int key = 0x0;
	vec2_t pos;
public:

	Module(int key, Category category, const char* tooltip);
	virtual ~Module() {};
	inline Category getCategory() { return category; }
	inline vec2_t* getPos() {
		return &pos;
	};
	virtual bool isEnabled() {
		return this->enabled;
	};
	virtual int getBind() {
		return this->key;
	};
	virtual void onEnable() {
	};
	virtual void onDisable() {
	};
	virtual void setEnabled(bool ean);

	virtual const char* getModuleName() = 0;
	virtual const char* getModeName();
	virtual void onTick(GameMode* gm) {};
	virtual void onRender(MinecraftUIRenderContext* ctx) {};
	virtual void onImRender() {};
	virtual void onKey(__int32 key);
};