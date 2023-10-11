#include "ClickGui.h"
#include "../../../Utils/ImGuiUtils.h"
#include "../../../Includes/animations/snowflake.hpp"
#include "../../../Includes/animations/dotMatrix.h"
#include "../../../Managers/ModuleManager.h"
ClickGui::ClickGui() : Module(0x2D, Category::RENDER, "clickgui") {
};

ClickGui::~ClickGui() {
};

const char* ClickGui::getModuleName() {
	return "ClickGui";
}
void ClickGui::getModuleListByCategory(Category category, std::vector<std::shared_ptr<Module>>* modList) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<Module>>* moduleList = moduleMgr->getModuleList();

	for (auto& it : *moduleList) {
		if (it->getCategory() == category)
			modList->push_back(it);
	}
}
void ClickGui::onImRender() {
	ImGuiStyle* style = &ImGui::GetStyle();
	
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 0.f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 0.f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 0.0f;
	style->WindowTitleAlign = ImVec2(0.5, 0.5);

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 0.70f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	//style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.5f, 0.5f, 0.50f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.5f, 0.5f, 0.70f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.5f, 0.5f, 0.70f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, .30f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, .30f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, .30f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, .30f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, .30f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, .30f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, .30f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f); 
	ImGuiIO& io = ImGui::GetIO();
	vec2_t windowSize = ImGuiUtil::get_window_size();
	auto& notifications = g_Data.getInfoBoxList();
	auto font = io.FontDefault;
	font->Scale = 0.65f;
	ImGuiWindowFlags TargetFlags;
	TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	std::vector<Category> cats = { Category::COMBAT, Category::MISC, Category::PLAYER, Category::RENDER, Category::WORLD };
	
	for (auto& category : cats) {
		//len = fmax(len, ImGuiUtil::get_text_area(font, 30, catToName(category)).x);
		if (ImGui::Begin((catToName(category)), 0, TargetFlags)) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategory(category, &moduleList);
			// Get max width of all text
			{
				for (auto& it : moduleList) {
					std::string label = it->getModuleName();
					//len = fmax(len, ImGuiUtil::get_text_area(font, 30, label).x);
				}
			}
			ImGui::SetWindowSize(ImVec2(200, 430.f));
			for (auto& mods : moduleList) {
				
				if (ImGui::CollapsingHeader((mods->getModuleName()))) {
					std::string key = (std::string)"Key : " + Utils::getKeyName(mods->getBind());
					if (mods->getBind() == 0x0) key = (std::string)"Key : None";
					if (waitkey && mods == waitmodule) key = (std::string)"Key : ...";
					if (ImGui::Button(key.c_str())) {
						waitkey = true;
						waitmodule = mods;
					}
					if (ImGui::Button(mods->isEnabled() ? "Disable" : "Enable")) {
						mods->setEnabled(!mods->isEnabled());
					}
				}
				else {
					if (mods == waitmodule) {
						waitmodule = nullptr;
						waitkey = false;
					}
				}
			}
			/*
			if (ImGui::CollapsingHeader("Visuals")) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
				}
				ImGui::Toggle("Toggle Snow", &ImGui::doSnow);
				ImGui::Toggle("Toggle DotMatrix", &ImGui::doDotMatrix);
				ImGui::ButtonScrollable("Button Scrollable", ImVec2(100.f, 0.f));
				ImGui::ButtonScrollableEx("Button Scrollable (Right-click only!)", ImVec2(100.f, 0.f), ImGuiButtonFlags_MouseButtonRight);
				ImGui::Spacing();
			}
			if (ImGui::CollapsingHeader(("Aura"))) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
				}
				ImGui::Spacing();
			}
			if (ImGui::CollapsingHeader(("Client"))) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
				}
				ImGui::Spacing();
			}
			if (ImGui::CollapsingHeader(("Exploits"))) {
				ImGui::Spacing();
				if (ImGui::Button("Unlock Achevements")) {
				}
				ImGui::Spacing();
			}*/
		}

		ImGui::End();
	}
}