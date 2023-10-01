#pragma once
#pragma region Includes & Macros

#define WIN32_LEAN_AND_MEAN
// C++ Includes
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>

// Minhook
#include "../Memory/minhook.h"
// Utils
#include "../Memory/GameData.h"
#include "../Utils/Utils.h"

// Maths
#include "../SDK/Maths/TextHolder.h"
#include "../SDK/Maths/UIColor.h"
#include "../SDK/Maths/Vectors.h"
#include "../SDK/Maths/BlockPos.h"

// Hooks
#include "../Memory/Hook/FuncHook.h"

// ImGuiLoader
#include "ImGuiLoader.h"
#include "../Includes/imgui/imgui.h"
#include "../Includes/imgui/imgui_impl_win32.h"
#include "../Includes/imgui/imgui_impl_dx12.h"
#include "../Includes/imgui/imgui_impl_dx11.h"
#include <initguid.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3d12.h>
#include <d2d1_1.h>
#include <dxgi1_4.h>
#include <dwrite_1.h>
#include "../Includes/kiero/kiero.h"
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dwrite.lib")

#pragma endregion