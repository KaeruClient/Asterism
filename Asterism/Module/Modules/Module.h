#pragma once
#include "../../../Includes/imgui/imgui.h"
#include "../../../SDK/Structs/GameMode.h"
#include "../../../SDK/Structs/MinecraftUIRenderContext.h"
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
	Module(int key, Category category, const char* tooltip);
	virtual ~Module() {};

	virtual bool isEnabled() {
		return this->enabled;
	}
	virtual void setEnabled(bool ean) {
		this->enabled = ean;
	};

	virtual const char* getModuleName() = 0;
	virtual const char* getModeName() {
		return "";
	};
	virtual void onTick(GameMode* gm) {};
	virtual void onRender(MinecraftUIRenderContext* ctx) {};
	virtual void onImRender() {};
};