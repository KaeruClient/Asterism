#pragma once
#include <vector>
#include "../SDK/Structs/GameMode.h"
#include <map>
#include "../Memory/GameData.h"
// You might use this if you want to group all of your global variables,
// functions, etc. under a common name to make them easier to find and organize
namespace Global {
	static std::map<__int32, bool> keymap;
	static bool rightclick;
	static uintptr_t** gmvtable;
};