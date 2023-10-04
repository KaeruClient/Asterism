#pragma once
#include "../../SDK/Structs/GameMode.h"
#include "../../SDK/Structs/MinecraftUIRenderContext.h"
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
public:
	Module(int key, Category category, const char* tooltip) {
		this->key = key;
		this->category = category;
		this->tooltip = tooltip;
	};
	~Module();

	bool isEnabled() {
		return enabled;
	}

	virtual const char* getModuleName() = 0;
	virtual const char* getModeName() {
		return "";
	};
	virtual void onTick(GameMode* gm);
	virtual void onRender(MinecraftUIRenderContext* ctx);
	virtual void onImGuiRender(ImFont* font);
};