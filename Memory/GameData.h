#pragma once
#include <vector>
#include "../SDK/Structs/GameMode.h"
#include "../SDK/Structs/ClientInstance.h"
// You might use this if you want to group all of your global variables,
// functions, etc. under a common name to make them easier to find and organize
namespace GameData {
	static std::map<__int32, bool> keymap;
	static GameMode* gm;
};
