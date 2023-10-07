#pragma once

#include <Windows.h>
#include <string>

#include "../Memory/GameData.h"
#include "../Includes/imgui/imgui.h"
#include "../Includes/imgui/imgui_internal.h"

#include "../Assets/ProductSans.h"
class ImGuiUtil {
public:
	static vec2_t get_cursor_pos() {
		RECT desktop;
		static HWND window = (HWND)FindWindowA(nullptr, "Minecraft");
		GetWindowRect(window, &desktop);

		POINT p;
		GetCursorPos(&p);

		// not in fullscreen
		if (desktop.top != 0 || desktop.left != 0)
			p.y -= 45;

		return vec2_t(p.x - desktop.left, p.y - desktop.top);
	}

	static vec2_t get_window_size() {
		RECT desktop;
		static HWND window = (HWND)FindWindowA(nullptr, "Minecraft");
		GetWindowRect(window, &desktop);
		int w = desktop.right - desktop.left;
		int h = desktop.bottom - desktop.top;
		// not in fullscreen
		if (desktop.top != 0 || desktop.left != 0) {
			w -= 30;
			h -= 45;
		}
		return vec2_t(w, h);
	}

	static bool isFullScreen() {
		RECT desktop;
		static HWND window = (HWND)FindWindowA(nullptr, "Minecraft");
		GetWindowRect(window, &desktop);
		if (desktop.top != 0 || desktop.left != 0)
			return false;
		return true;
	}
	static void draw_image(ImTextureID textureId, float x1, float y1, float x2, float y2) {
		get_draw_list()->AddImageQuad(textureId, ImVec2(x1, y1), ImVec2(x2, y1), ImVec2(x1, y2), ImVec2(x2, y2));
	}
	static void start_clipping(float x1, float y1, float x2, float y2) {
		get_draw_list()->PushClipRect(ImVec2(x1, y1), ImVec2(x2, y2), true);
	}

	static void stop_clipping() {
		get_draw_list()->PopClipRect();
	}

	static void draw_rect(float x1, float y1, float x2, float y2, UIColor const& color) {
		get_draw_list()->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), to_imu32(color));
	}
	static void draw_outline(float x1, float y1, float x2, float y2, float thickness, UIColor const& color) {
		get_draw_list()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), to_imu32(color), 0, 0, thickness = thickness);
	}

	static void draw_gradient_rect(float x1, float y1, float x2, float y2, UIColor const& left_top, UIColor const& right_top, UIColor const& left_bottom, UIColor const& right_bottom) {
		get_draw_list()->AddRectFilledMultiColor(ImVec2(x1, y1), ImVec2(x2, y2), to_imu32(left_top), to_imu32(right_top), to_imu32(right_bottom), to_imu32(left_bottom));
	}

	static void draw_rounded(float x1, float y1, float x2, float y2, float rounding, UIColor const& color) {
		get_draw_list()->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), to_imu32(color), rounding);
	}

	static void draw_rounded_outline(float x1, float y1, float x2, float y2, float rounding, float thickness, UIColor const& color) {
		get_draw_list()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), to_imu32(color), rounding, 0, thickness = thickness);
	}

	static void draw_gradient_rounded(float x1, float y1, float x2, float y2, float rounding, UIColor const& color1, UIColor const& color2) {
		int vert_start_idx = get_draw_list()->VtxBuffer.Size;
		get_draw_list()->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), to_imu32(color1), rounding);
		int vert_end_idx = get_draw_list()->VtxBuffer.Size;

		ImGui::ShadeVertsLinearColorGradientKeepAlpha(get_draw_list(), vert_start_idx, vert_end_idx, ImVec2(x1, y1), ImVec2(x2, y2), to_imu32(color1), to_imu32(color2));
	}

	static void draw_circle(float x, float y, float scale, UIColor const& color) {
		get_draw_list()->AddCircleFilled(ImVec2(x, y), scale, to_imu32(color));
	}

	static void draw_circle_outline(float x, float y, float scale, float thickness, UIColor const& color) {
		get_draw_list()->AddCircle(ImVec2(x, y), scale, to_imu32(color), thickness = thickness);
	}

	static void draw_text(ImFont* font, float size, std::string const& text, float x, float y, UIColor const& color) {
		get_draw_list()->AddText(font, size, ImVec2(x, y), to_imu32(color), text.c_str());
	}

	static vec2_t get_text_area(ImFont* font, float size, std::string const& text) {
		ImVec2 r = font->CalcTextSizeA(size, 1000, 0.0f, text.c_str());
		return vec2_t(r.x, r.y);
	}
private:
	static ImU32 to_imu32(UIColor const& color) {
		int r = (int)(color.r * 255);
		int g = (int)(color.g * 255);
		int b = (int)(color.b * 255);
		int a = (int)(color.a * 255);
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		if (a > 255)
			a = 255;

		return IM_COL32(r, g, b, a);
	}

	static ImDrawList* get_draw_list() {
		return ImGui::GetBackgroundDrawList();
	}
};