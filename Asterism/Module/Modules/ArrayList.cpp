#include "ArrayList.h"

#include "../../../Utils/ImGuiUtils.h"
#include "../../../Managers/ModuleManager.h"
#include <set>

#include "../../../Utils/ColorUtils.h"
ArrayList::ArrayList() : Module(0x0, Category::RENDER, "im arraylist") {
};

ArrayList::~ArrayList() {
};

const char* ArrayList::getModuleName() {
	return "ArrayList";
}

struct ModuleContainer {
	ImFont* font = ImGui::GetIO().FontDefault;
	// Struct used to Sort IModules in a std::set
	std::shared_ptr<Module> backingModule;
	std::string moduleName;
	std::string modeName;
	bool enabled;
	int keybind;
	float moduleWidth;
	float modeWidth;
	float textWidth;
	vec2_t* pos;
	bool shouldRender = true;

	ModuleContainer(std::shared_ptr<Module> mod) {
		const char* moduleNameChr = mod->getModuleName();
		const char* modeNameChr = mod->getModeName();
		this->enabled = mod->isEnabled();
		this->backingModule = mod;
		
		moduleName = moduleNameChr;
		if (modeNameChr != "") modeName = " " + std::string(modeNameChr);
		if (!this->enabled)
			this->shouldRender = false;
		this->moduleWidth = ImGuiUtil::get_text_area(font, 30, moduleName).x;
		this->modeWidth = ImGuiUtil::get_text_area(font, 30, modeName).x;
		this->textWidth = this->moduleWidth + this->modeWidth;
	}

	bool operator<(const ModuleContainer& other) const {
		if (this->textWidth == other.textWidth)
			return moduleName < other.moduleName;
		return this->textWidth > other.textWidth;
	}
};

void ArrayList::onImRender() {
	std::set<ModuleContainer> modContainerList;
	// Fill modContainerList with Modules
	{
		auto lock = moduleMgr->lockModuleList();
		std::vector<std::shared_ptr<Module>>* moduleList = moduleMgr->getModuleList();
		for (auto it : *moduleList) {
			modContainerList.emplace(ModuleContainer(it));
		}
	}
	bool bottom = true;
	float yPos = - 5;
	ImFont* font = ImGui::GetIO().FontDefault;
	vec2_t windowSize = vec2_t(ImGuiUtil::get_window_size().x + (ImGuiUtil::isFullScreen() ? -10 : 10),  ImGuiUtil::get_window_size().y - !ImGuiUtil::isFullScreen() + yPos);
	float yOffset = 0;
	if (bottom) yOffset = windowSize.y - ImGuiUtil::get_text_area(font, 30, "A").y;
	int index = 0;
	float len = 0;
	UIColor col = UIColor(0,0,0);
	float padding = 5.f;
	for (auto it = modContainerList.begin(); it != modContainerList.end(); ++it) {

		if (!it->shouldRender) continue;

		auto& container = *it;
		auto textStr = container.moduleName;
		auto textWidth = container.textWidth;
		auto moduleWidth = container.moduleWidth;
		auto modeWidth = container.modeWidth;

		auto modeStr = container.modeName;
		auto xOffsetOri = windowSize.x - textWidth;
		float x = 0.0;
		float h = ImGuiUtil::get_text_area(font, 30, textStr).y;
		if (!bottom) {
			auto arrayColor = ColorUtil::rainbowColor(2, 1, 1, -index * 100, 255);
			ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset, windowSize.x + padding, yOffset + h, UIColor(0, 0, 0, 100));                       //background
			ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset, xOffsetOri - 4, yOffset + h, arrayColor);                               //leftrect
			if (index) ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset, windowSize.x - len - padding, yOffset + 1, arrayColor);      //underline
			ImGuiUtil::draw_text(font, 30, textStr, xOffsetOri, yOffset, arrayColor);                                         //modulename
			ImGuiUtil::draw_text(font, 30, modeStr, xOffsetOri + moduleWidth, yOffset, UIColor(160, 160, 160));              //mode
			yOffset += h;
			col = arrayColor;
		} else {
			auto arrayColor = ColorUtil::rainbowColor(2, 1, 1, index * 100, 255);
			ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset, windowSize.x + padding, yOffset + h, UIColor(0, 0, 0, 100));                       //background
			ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset, xOffsetOri - 4, yOffset + h, arrayColor);                               //leftrect
			if (index) ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset + h, windowSize.x - len - padding, yOffset - 1 + h, arrayColor);      //underline
			ImGuiUtil::draw_text(font, 30, textStr, xOffsetOri, yOffset, arrayColor);                                         //modulename
			ImGuiUtil::draw_text(font, 30, modeStr, xOffsetOri + moduleWidth, yOffset, UIColor(160, 160, 160));              //mode
			yOffset -= h;
			col = arrayColor;
		}
		++index;
		len = textWidth;
	}
	if (bottom)
		ImGuiUtil::draw_rect(windowSize.x - len - padding, yOffset + ImGuiUtil::get_text_area(font, 30, "A").y, windowSize.x + padding, yOffset + 1 + ImGuiUtil::get_text_area(font, 30, "A").y, col);
	else
		ImGuiUtil::draw_rect(windowSize.x - len - padding, yOffset, windowSize.x + padding, yOffset + 1, col);
}