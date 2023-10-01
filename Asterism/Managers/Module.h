#pragma once/*
#include "../../includes/imgui/imgui.h"
#include "../../includes/imgui/imgui_impl_dx11.h"
#include "../../includes/imgui/imgui_impl_dx12.h"
#include "../../includes/imgui/imgui_impl_win32.h"*/
#include "../../SDK/Structs/GameMode.h"
#include "../../SDK/Structs/MinecraftUIRenderContext.h"

enum class Category {
	COMBAT = 0,
	VISUAL = 1,
	MOVEMENT = 2,
	PLAYER = 3,
	MISC = 4,
	WORLD = 5
};

class Module {
private:
	bool enabled = false;
	int keybind = 0x0;
	bool extended = false;
	const char* tooltip;
	Category cat;
protected:
	Module(int key, Category c, const char* tooltip) {
		this->keybind = key;
		this->cat = c;
		this->tooltip = tooltip;
	};
public:
	virtual ~Module();

	const Category getCategory() {
		return cat;
	}

	virtual bool isEnabled() {
		return enabled;
	};
	virtual void onEnable();
	virtual void onDisable();

	void setEnabled(bool enabled) {
		if (this->enabled != enabled) {
			this->enabled = enabled;
			if (enabled)
				this->onEnable();
			else
				this->onDisable();
		}
	}
};