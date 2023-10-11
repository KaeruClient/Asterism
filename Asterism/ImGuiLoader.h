#pragma once


#define WIN32_LEAN_AND_MEAN
// C++ Includes
#include <d3d11.h>
#include <d3d12.h>

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
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dwrite.lib")

//Amimation Stuff
#include "../Includes//Animations/snowflake.hpp"
#include "../Includes/animations/dotMatrix.h"
#include "../Includes/Animations/fade.hpp"
#include "../Managers/ModuleManager.h"

static ImVec2 getScreenResolution() {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	return ImVec2(desktop.right, desktop.bottom);
}
// Snow Shit
#define SNOW_LIMIT 300 // max ammount of Snow/Bubbles allowed on screen at once
std::vector<Snowflake::Snowflake> snow;
std::vector<Particle> dots;
auto GetDllMod(void) -> HMODULE {
	MEMORY_BASIC_INFORMATION info;
	size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)GetDllMod, &info, sizeof(info));
	assert(len == sizeof(info));
	return len ? (HMODULE)info.AllocationBase : NULL;
}

void drawNotifications() {
	//Notification
	ImGuiIO& io = ImGui::GetIO();
	auto arraylist = moduleMgr->getModule<ArrayList>();
	vec2_t windowSize = ImGuiUtil::get_window_size();
	auto& notifications = g_Data.getInfoBoxList();
	auto font = io.FontDefault;
	float yPos = 15;
	float x = 15;
	int counter = 0;
	if (arraylist == nullptr) return;
	for (auto& notification : notifications) {
		counter++;
		if (notification == nullptr || counter >= 23) return;
		if (!notification->check) {
			notification->maxDuration = notification->duration;
			notification->check = true;
		}
		notification->fadeVal += (notification->fadeTarget - notification->fadeVal) * 0.08f;
		if (notification->fadeTarget == 0 && notification->fadeVal < 0.1f)
			notification->isOpen = false;
		if (notification->fadeTarget == 1 && notification->duration <= 0 && notification->duration > -1)
			notification->fadeTarget = 0;
		else if (notification->duration > 0)
			notification->duration -= 1.f / 60;
		float percent = notification->duration / notification->maxDuration;
		std::string text = notification->message;
		float textHight = ImGuiUtil::get_text_area(font, 25, text).y;
		float textWight = ImGuiUtil::get_text_area(font, 25, text).x;
		float bar = x + (textWight + 4) * percent;
		notification->animate.y = smoothLerp(yPos, notification->animate.y, 0.2);
		ImGuiUtil::draw_rect(x * notification->fadeVal, (notification->animate.y - 2) * notification->fadeVal, (x + textWight + 4) * notification->fadeVal, (notification->animate.y + textHight + 2) * notification->fadeVal, UIColor(0, 0, 0, 150 * notification->fadeVal));
		ImGuiUtil::draw_rect(x * notification->fadeVal, (notification->animate.y + textHight + 1) * notification->fadeVal, bar * notification->fadeVal, (notification->animate.y + textHight + 2) * notification->fadeVal, UIColor(255, 255, 255, 255 * notification->fadeVal));
		ImGuiUtil::draw_text(font, 25 * notification->fadeVal, text, (x + 2) * notification->fadeVal, notification->animate.y * notification->fadeVal, UIColor(255, 255, 255, 255 * notification->fadeVal));
		yPos += textHight + 15;
	}
}
ImFont* font;
//Index shit
int countnum = -1;

typedef HRESULT(__thiscall* PresentD3D12)(IDXGISwapChain3*, UINT, UINT);
PresentD3D12 oPresentD3D12;
ID3D11Device* d3d11Device = nullptr;
ID3D12Device* d3d12Device = nullptr;
enum ID3D_Device_Type {
	INVALID_DEVICE_TYPE,
	D3D11,
	D3D12
};
struct FrameContext {
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12Resource* main_render_target_resource = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE main_render_target_descriptor;
};
uint64_t buffersCounts = -1;
FrameContext* frameContext = nullptr;
ID3D12DescriptorHeap* d3d12DescriptorHeapImGuiRender = nullptr;
ID3D12DescriptorHeap* d3d12DescriptorHeapBackBuffers = nullptr;
ID3D12GraphicsCommandList* d3d12CommandList = nullptr;
ID3D12CommandAllocator* allocator = nullptr;
D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
ID3D12CommandQueue* d3d12CommandQueue = nullptr;
bool initContext = false;/*
void drawInfoBox()
{
	//auto interfaceMod = moduleMgr->getModule<Interface>();
	auto arraylist = moduleMgr->getModule<ArrayList>();
	vec2_t windowSize = ImGuiUtil::get_window_size();
	auto& notifications = boxmgr.getInfoBoxList();
	int index = 0;
	index++; int curIndex = -index * 25;
	//auto interfaceColor = ColorUtil::interfaceColor(curIndex);
	float yPos = windowSize.y - 15;
	constexpr float margin = 6;
	for (auto& notification : notifications) {
		auto rainbow = ColorUtil::rainbowColor(32, 1.f, 1.f, -notification->colorIndex * 30, 150);
		if (notification->check) {
			notification->fadeVal += (notification->fadeTarget - notification->fadeVal) * 0.08f;
			if (notification->fadeTarget == 0 && notification->fadeVal < 0.001f)
				notification->isOpen = false;
			if (notification->fadeTarget == 1 && notification->duration <= 0 && notification->duration > -1)
				notification->fadeTarget = 0;
			else if (notification->duration > 0)
				notification->duration -= 1.f / 60;

			int lines = 1;

			std::string substring = notification->message;

			while (lines < 5) {
				auto brea = substring.find("\n");
				if (brea == std::string::npos || brea + 1 >= substring.size())
					break;
				substring = substring.substr(brea + 1);
				lines++;
			}
			if (notification->message.size() == 0)
				lines = 0;

			constexpr float notificationMessage = 1;
			constexpr float unused = 0.7f;
			constexpr float borderPadding = 10;
			std::string message = notification->message;
			std::string title = notification->title;
			std::string textStr = message;
			vec2_t getNotiTextSize = ImGuiUtil::get_text_area(font, 30.f, message);
			float nameLength = getNotiTextSize.x;
			float fullTextLength = nameLength;
			static const float textHeight = (notificationMessage + unused * 1) * (getNotiTextSize.y * 1.2);

			notification->animate.y += (yPos - notification->animate.y) * 0.1f;
			if (notification->fadeTarget == 1)
				notification->animate.x += ((windowSize.x - margin - fullTextLength - 2 - borderPadding * 2) - notification->animate.x) * 0.1f;
			else
				notification->animate.x += (windowSize.x - notification->animate.x) * 0.1f;

			vec4_t rect = vec4_t(
				notification->animate.x,
				notification->animate.y - margin - textHeight - 4,
				(notification->animate.x + margin + fullTextLength + 2 + borderPadding * 2) + margin - borderPadding - 2,
				notification->animate.y - margin);

			float duration = (rect.z - rect.x) * (notification->duration / notification->maxDuration);
			if (duration < 1) duration = 1;
			vec2_t textPos = vec2_t(rect.x + 9, rect.y + 1);
			vec2_t titlePos = vec2_t(rect.x + 9, rect.y + 1);

			//DrawUtils::drawText(vec2_t(textPos.x, textPos.y), &textStr, MC_Color(255, 255, 255), 0.8, 1, true);
			vec4_t rect_glow = rect;
			float rect_round = 10.f;
			float rect_alpha = 7.5f;
			for (int i = 0; i < 25; i++)
			{
				rect_glow.x -= 1.f;
				rect_glow.y -= 1.f;
				rect_glow.z += 1.f;
				rect_glow.w += 1.f;
				rect_round += 1.f;
				rect_alpha -= 0.3f;
				ImGuiUtil::draw_rounded(rect_glow.x, rect_glow.y, rect_glow.z, rect_glow.w, rect_round, UIColor(0, 0, 0, rect_alpha));
			}


				rect_glow = rect;
				rect_round = 10.f;
				rect_alpha = 7.5f;
				rect_glow.z -= duration;
				UIColor rainbowGlowColor = ColorUtil::rainbowColor(32, 1.f, 1.f, -notification->colorIndex * 30, 150);
				for (int i = 0; i < 20; i++)
				{
					rect_glow.x -= 1.f;
					rect_glow.y -= 1.f;
					rect_glow.w += 1.f;
					rect_round += 1.f;
					rect_alpha -= 0.3f;
					ImGuiUtil::draw_rounded(rect_glow.x, rect_glow.y, rect_glow.z, rect_glow.w, rect_round, rainbowGlowColor);
				}
				ImGuiUtil::draw_rounded(rect.x, rect.y, rect.z, rect.w, 10, UIColor(0, 0, 0, 150));
				ImGuiUtil::draw_rounded(rect.x, rect.y, rect.z - duration, rect.w, 10, rainbow);
				ImGuiUtil::draw_text(font, 30.f, textStr, textPos.x, textPos.y + 15.f, UIColor (255, 255, 255));

		}
		else {
			notification->maxDuration = notification->duration;
			notification->check = true;
			notification->animate.y = yPos;
			notification->animate.x = windowSize.x;
		}
		if (notification->animate.x < windowSize.x + margin - 12 || notification->fadeTarget == 1) {
			yPos -= margin + 75;
		}
	}
}*/
HRESULT hookPresentD3D12(IDXGISwapChain3* ppSwapChain, UINT syncInterval, UINT flags) {
	auto deviceType = ID3D_Device_Type::INVALID_DEVICE_TYPE;
	auto window = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");
	if (window == NULL) {
		goto out;
	};
	if (SUCCEEDED(ppSwapChain->GetDevice(IID_PPV_ARGS(&d3d11Device)))) {
		deviceType = ID3D_Device_Type::D3D11;
	}
	else if (SUCCEEDED(ppSwapChain->GetDevice(IID_PPV_ARGS(&d3d12Device)))) {
		deviceType = ID3D_Device_Type::D3D12;
	};
	if (deviceType == ID3D_Device_Type::INVALID_DEVICE_TYPE) {
		goto out;
	};
	if (deviceType == ID3D_Device_Type::D3D11) {
		if (!initContext)
			ImGui::CreateContext();
		ID3D11DeviceContext* ppContext = nullptr;
		d3d11Device->GetImmediateContext(&ppContext);
		ID3D11Texture2D* pBackBuffer;
		ppSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		ID3D11RenderTargetView* mainRenderTargetView;
		d3d11Device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
		pBackBuffer->Release();
		POINT mouse;
		RECT rc = { 0 };
		md::FadeInOut fade;
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(d3d11Device, ppContext);
		if (!initContext) {
			// fade effect with windows transparency
			fade.init();

			// Snowflakes
			Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 15.f /*minimum size*/, 25.f /*maximum size*/, getScreenResolution().x, getScreenResolution().y, 0 /*imgui window x position*/, 0 /*imgui window y position*/, Snowflake::vec3(0.f, -0.005f) /*gravity*/, IM_COL32(255, 255, 255, 100) /*color*/);

			// Dots
			dots = createDotMatrix({ getScreenResolution().x,getScreenResolution().y }, { 40,40 }, getScreenResolution().x * getScreenResolution().y / 5);

			// Fonts

			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			io.FontDefault = io.Fonts->AddFontFromMemoryCompressedBase85TTF(ProductSans_compressed_data_base85,
				30.f);

			initContext = true;
		}
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

#pragma region SnowFlakes
		RECT rect;
		GetWindowRect(window, &rect);
		ImVec2 size69 = ImVec2(rect.right - rect.left, rect.bottom - rect.top);
		if (ImGui::doSnow || ImGui::doDotMatrix) {
			ImGui::SetNextWindowPos(ImVec2(size69.x - size69.x, size69.y - size69.y), ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(size69.x, size69.y));
			ImGui::SetNextWindowBgAlpha(0.f);//Set to 0.25 for a nice background

			ImGui::Begin("HELLO!!!", 0, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
			{
				GetWindowRect(window, &rc);
				GetCursorPos(&mouse);
				// render this before anything else so it is the background
				if (ImGui::doSnow)
					Snowflake::Update(snow, Snowflake::vec3(mouse.x, mouse.y), Snowflake::vec3(rc.left, rc.top));  // you can change a few things inside the update function
				if (ImGui::doDotMatrix) {
					updateDotMatrix({ getScreenResolution().x,getScreenResolution().y }, dots);
					drawDotMatrix(dots, 50, 0.05, false);
				}
			}
			ImGui::End();
		}
#pragma endregion
		if (moduleMgr->isInitialized() && moduleMgr->getModule<ClickGui>()->isEnabled()) {
			ImGuiUtil::draw_rect(0, 0, size69.x, size69.y, UIColor(0, 0, 0, 170));
			updateDotMatrix({ getScreenResolution().x,getScreenResolution().y }, dots);
			drawDotMatrix(dots, 50, 0.05, false);
		}
		else {
			moduleMgr->onImRender();
			drawNotifications();
		}
		{
			ImGuiStyle* style = &ImGui::GetStyle();
			style->WindowPadding = ImVec2(15, 15);
			style->WindowRounding = 10.f;
			style->FramePadding = ImVec2(5, 5);
			style->FrameRounding = 6.f;
			style->ItemSpacing = ImVec2(12, 8);
			style->ItemInnerSpacing = ImVec2(8, 6);
			style->IndentSpacing = 25.0f;
			style->ScrollbarSize = 15.0f;
			style->ScrollbarRounding = 9.0f;
			style->GrabMinSize = 5.0f;
			style->GrabRounding = 3.0f;
			style->WindowTitleAlign = ImVec2(0.5, 0.5);

			style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
			style->Colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
			style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
			style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_CheckMark] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
			style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
			style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
			style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
			ImGuiWindowFlags TargetFlags;
			TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
		}

		ImGui::Render();
		ppContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		mainRenderTargetView->Release();
		d3d11Device->Release();
	}
	else if (deviceType == ID3D_Device_Type::D3D12) {
		if (!initContext)
			ImGui::CreateContext();
		DXGI_SWAP_CHAIN_DESC sdesc;
		ppSwapChain->GetDesc(&sdesc);
		sdesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sdesc.OutputWindow = window;
		sdesc.Windowed = ((GetWindowLongPtr(window, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
		buffersCounts = sdesc.BufferCount;
		frameContext = new FrameContext[buffersCounts];
		D3D12_DESCRIPTOR_HEAP_DESC descriptorImGuiRender = {};
		descriptorImGuiRender.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descriptorImGuiRender.NumDescriptors = buffersCounts;
		descriptorImGuiRender.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		if (d3d12DescriptorHeapImGuiRender == nullptr)
			if (FAILED(d3d12Device->CreateDescriptorHeap(&descriptorImGuiRender, IID_PPV_ARGS(&d3d12DescriptorHeapImGuiRender))))
				goto out;
		if (d3d12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator)) != S_OK)
			return false;
		for (size_t i = 0; i < buffersCounts; i++) {
			frameContext[i].commandAllocator = allocator;
		};
		if (d3d12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, NULL, IID_PPV_ARGS(&d3d12CommandList)) != S_OK ||
			d3d12CommandList->Close() != S_OK)
			return false;
		D3D12_DESCRIPTOR_HEAP_DESC descriptorBackBuffers;
		descriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		descriptorBackBuffers.NumDescriptors = buffersCounts;
		descriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descriptorBackBuffers.NodeMask = 1;
		if (d3d12Device->CreateDescriptorHeap(&descriptorBackBuffers, IID_PPV_ARGS(&d3d12DescriptorHeapBackBuffers)) != S_OK)
			return false;
		const auto rtvDescriptorSize = d3d12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		rtvHandle = d3d12DescriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();
		for (size_t i = 0; i < buffersCounts; i++) {
			ID3D12Resource* pBackBuffer = nullptr;
			frameContext[i].main_render_target_descriptor = rtvHandle;
			ppSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
			d3d12Device->CreateRenderTargetView(pBackBuffer, nullptr, rtvHandle);
			frameContext[i].main_render_target_resource = pBackBuffer;
			rtvHandle.ptr += rtvDescriptorSize;
			pBackBuffer->Release();
		};
		POINT mouse;
		RECT rc = { 0 };
		md::FadeInOut fade;
		if (!initContext) {
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX12_Init(d3d12Device, buffersCounts,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				d3d12DescriptorHeapImGuiRender,
				d3d12DescriptorHeapImGuiRender->GetCPUDescriptorHandleForHeapStart(),
				d3d12DescriptorHeapImGuiRender->GetGPUDescriptorHandleForHeapStart());

			// fade effect with windows transparency
			fade.init();

			// Snowflakes
			Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 5.f /*minimum size*/, 25.f /*maximum size*/, 0 /*imgui window x position*/, 0 /*imgui window y position*/, getScreenResolution().x, getScreenResolution().y, Snowflake::vec3(0.f, 0.005f) /*gravity*/, IM_COL32(255, 255, 255, 100) /*color*/);

			// Dots
			dots = createDotMatrix({ getScreenResolution().x,getScreenResolution().y }, { 40,40 }, getScreenResolution().x * getScreenResolution().y / 9000);

			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			io.FontDefault = io.Fonts->AddFontFromMemoryCompressedBase85TTF(ProductSans_compressed_data_base85,
				30.f);
			initContext = true;
		};
		if (d3d12CommandQueue == nullptr)
			goto out;
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

#pragma region SnowFlakesAndDotMatrix
		RECT rect;
		GetWindowRect(window, &rect);
		ImVec2 size69 = ImVec2(rect.right - rect.left, rect.bottom - rect.top);
		if (ImGui::doSnow || ImGui::doDotMatrix) {
			ImGui::SetNextWindowPos(ImVec2(size69.x - size69.x, size69.y - size69.y), ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(size69.x, size69.y));
			ImGui::SetNextWindowBgAlpha(0.f);//Set to 0.25 for a nice background

			ImGui::Begin("HELLO!!!", 0, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
			{
				GetWindowRect(window, &rc);
				GetCursorPos(&mouse);
				// render this before anything else so it is the background
				if (ImGui::doSnow)
					Snowflake::Update(snow, Snowflake::vec3(mouse.x, mouse.y), Snowflake::vec3(rc.left, rc.top));  // you can change a few things inside the update function

				if (ImGui::doDotMatrix) {
					updateDotMatrix({ getScreenResolution().x,getScreenResolution().y }, dots);
					drawDotMatrix(dots, 50, 0.05, false);
				}
			}
			ImGui::End();
		}
#pragma endregion
		if (moduleMgr->isInitialized() && moduleMgr->getModule<ClickGui>()->isEnabled()) {
			auto col1 = ColorUtil::rainbowColor(2, 1, 1, 0, 50);
			auto col2 = ColorUtil::rainbowColor(2, 1, 1, 1000, 50);
			auto col3 = ColorUtil::rainbowColor(2, 1, 1, 0, 00);
			auto col4 = ColorUtil::rainbowColor(2, 1, 1, 1000, 00);
			ImGuiUtil::draw_rect(0, 0, size69.x, size69.y, UIColor(0, 0, 0, 100));
			ImGuiUtil::draw_gradient_rect(0, size69.y / 2, size69.x, size69.y, col4, col3, col1, col2);
			//updateDotMatrix({ getScreenResolution().x,getScreenResolution().y }, dots);
			//drawDotMatrix(dots, 50, 0.05, false);

			moduleMgr->getModule<ClickGui>()->onImRender();
		}
		else {
			moduleMgr->onImRender();
			drawNotifications();
		}
		//}
	//}

		FrameContext& currentFrameContext = frameContext[ppSwapChain->GetCurrentBackBufferIndex()];
		currentFrameContext.commandAllocator->Reset();
		D3D12_RESOURCE_BARRIER barrier;
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = currentFrameContext.main_render_target_resource;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		d3d12CommandList->Reset(currentFrameContext.commandAllocator, nullptr);
		d3d12CommandList->ResourceBarrier(1, &barrier);
		d3d12CommandList->OMSetRenderTargets(1, &currentFrameContext.main_render_target_descriptor, FALSE, nullptr);
		d3d12CommandList->SetDescriptorHeaps(1, &d3d12DescriptorHeapImGuiRender);
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), d3d12CommandList);
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		d3d12CommandList->ResourceBarrier(1, &barrier);
		d3d12CommandList->Close();
		d3d12CommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&d3d12CommandList));
		d3d12DescriptorHeapBackBuffers->Release();
		d3d12CommandList->Release();
		allocator->Release();
		currentFrameContext.main_render_target_resource->Release();
		currentFrameContext.commandAllocator->Release();
		d3d12Device->Release();
		delete frameContext;
	};
	goto out;
out:
	return oPresentD3D12(ppSwapChain, syncInterval, flags);
};

//CommandList
typedef void(__thiscall* ExecuteCommandListsD3D12)(ID3D12CommandQueue*, UINT, ID3D12CommandList*);
ExecuteCommandListsD3D12 oExecuteCommandListsD3D12;
void hookExecuteCommandListsD3D12(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists) {
	if (!d3d12CommandQueue)
		d3d12CommandQueue = queue;
	oExecuteCommandListsD3D12(queue, NumCommandLists, ppCommandLists);
};

//Instanced
typedef void(__stdcall* D3D12DrawInstanced)(ID3D12GraphicsCommandList* dCommandList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation);
D3D12DrawInstanced o_D12DrawInstanced = NULL;
void __stdcall hkDrawInstancedD12(ID3D12GraphicsCommandList* dCommandList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation) {
	return o_D12DrawInstanced(dCommandList, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

//Indexed
typedef void(__stdcall* D3D12DrawIndexedInstanced)(ID3D12GraphicsCommandList* dCommandList, UINT IndexCount, UINT InstanceCount, UINT StartIndex, INT BaseVertex);
D3D12DrawIndexedInstanced o_D12DrawIndexedInstanced = NULL;
void __stdcall hkDrawIndexedInstancedD12(ID3D12GraphicsCommandList* dCommandList, UINT IndexCount, UINT InstanceCount, UINT StartIndex, INT BaseVertex) {
	//Tests

	//for (int i = -3; i <= 3; i++) {
	//	INT offset = BaseVertex + i * 10;
	//	o_D12DrawIndexedInstanced(dCommandList, IndexCount, InstanceCount, StartIndex, offset); /multiply rendering
	//}

	//IndexCount = 3; // Only draw the first three triangles of the mesh

	//static float time = 0.0f;
	//BaseVertex += static_cast<int>(sin(time) * 10.0f); // Offset the vertices based on a sine wave
	//time += 0.01f;

	//IndexCount += rand() % 10; // Add a random offset to IndexCount
	//StartIndex += rand() % 10; // Add a random offset to StartIndex
	//BaseVertex += rand() % 10; // Add a random offset to BaseVertex

	//static float time = 0.0f;
	//time += 0.1f; // Increase time to make the wave move faster
	//float wave = sin(time) * 10.0f; // Calculate the wave value based on the current time
	//BaseVertex += (INT)wave; // Add the wave value to the BaseVertex parameter

	//Wireframe
	//dCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

	//static float time = 0.0f;
	//time += 0.001f; // Increase time to make the wave move faster
	//float wave = sin(time) * 10.0f; // Calculate the wave value based on the current time
	//if (IndexCount == 72 || IndexCount == 180) {
	//	BaseVertex += static_cast<int>(wave); // Add the wave value to the BaseVertex parameter
	//}

	return o_D12DrawIndexedInstanced(dCommandList, IndexCount, InstanceCount, StartIndex, BaseVertex);
}

//Hooks
class ImguiHooks {
public:
	static void InitImgui() {
		if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
			auto notification = g_Data.addInfoBox("Setup", "Created hook for SwapChain::Present (DX12)!");
			notification->duration = 7.f;
		}

		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
			auto notification = g_Data.addInfoBox("Setup", "Created hook for SwapChain::Present (DX11)!");
			notification->duration = 7.f;
		}

		kiero::bind(54, (void**)&oExecuteCommandListsD3D12, hookExecuteCommandListsD3D12);
		kiero::bind(140, (void**)&oPresentD3D12, hookPresentD3D12);
		kiero::bind(84, (void**)&o_D12DrawInstanced, hkDrawInstancedD12);
		kiero::bind(85, (void**)&o_D12DrawIndexedInstanced, hkDrawIndexedInstancedD12);
	}
};