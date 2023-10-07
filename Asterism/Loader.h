#pragma once
#pragma region Includes & Macros

#define WIN32_LEAN_AND_MEAN
// C++ Includes
#include <d3d11.h>
#include <d3d10.h>
#include <d3d12.h>
#include <d3d.h>

#include <winerror.h>
#include <windef.h>
#include <WinUser.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <Psapi.h>

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <basetsd.h>

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <cmath>
// Minhook
#include "../Memory/minhook.h"
// Utils
#include "../Memory/Global.h"
#include "../Utils/Utils.h"

// Maths
#include "../SDK/Maths/TextHolder.h"
#include "../SDK/Maths/UIColor.h"
#include "../SDK/Maths/Vectors.h"

// Hooks
#include "../Memory/Hook/FuncHook.h"

// memory

#include "../Memory/GameData.h"
 
// Client 
#include "ImGuiLoader.h"
#include "../Utils/ImGuiUtils.h"


//ImGuis
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
#include <d3d11.h>
#include <d3d10.h>
#include <d3d12.h>
#include <d3d.h>

#include <winerror.h>
#include <windef.h>
#include <WinUser.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <Psapi.h>

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <basetsd.h>
#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include <algorithm>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dwrite.lib")
#pragma endregion