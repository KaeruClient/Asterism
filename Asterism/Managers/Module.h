#pragma once
#include "../../includes/imgui/imgui.h"
#include "../../includes/imgui/imgui_impl_dx11.h"
#include "../../includes/imgui/imgui_impl_dx12.h"
#include "../../includes/imgui/imgui_impl_win32.h"

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
public:
	Module(int key, Category c, const char* tooltip);

};