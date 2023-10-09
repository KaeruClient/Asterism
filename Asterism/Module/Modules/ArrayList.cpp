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
		this->pos = mod->getPos();
		moduleName = moduleNameChr;
		if (modeNameChr != "") modeName = " " + std::string(modeNameChr);
		if (!this->enabled && (this->pos->x == 0 && this->pos->y == 0))
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
	float yPos = - 0;
	ImFont* font = ImGui::GetIO().FontDefault;
	vec2_t windowSize = vec2_t(ImGuiUtil::get_window_size().x + (ImGuiUtil::isFullScreen() ? 0 : 10),  ImGuiUtil::get_window_size().y - !ImGuiUtil::isFullScreen() + yPos);
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
		auto xOffset = windowSize.x - container.pos->x;
		if (container.enabled) {
			container.pos->y = smoothLerp(1, container.pos->y, 0.3);
			if (container.pos->y >= 0.95)
				container.pos->x = smoothLerp(windowSize.x - xOffsetOri, container.pos->x, 0.3);
		}
		else { 
			container.pos->x = smoothLerp(-1, container.pos->x, 0.3);
			if (xOffset >= windowSize.x) {
				container.pos->x = 0.f;
				container.pos->y = smoothLerp(0, container.pos->y, 0.3);
				if (container.pos->y <= 0.1) container.pos->y = 0;
			}
		}
		float h = ImGuiUtil::get_text_area(font, 30, textStr).y;
		if (!bottom) {
			auto arrayColor = ColorUtil::rainbowColor(2, 1, 1, -index * 100, 255);
			ImGuiUtil::draw_rect(xOffset - padding, yOffset, windowSize.x + padding, yOffset + h, UIColor(0, 0, 0, 100));                       //background
			ImGuiUtil::draw_rect(xOffset - padding, yOffset, xOffset - 4, yOffset + h, arrayColor);                               //leftrect
			if (index) ImGuiUtil::draw_rect(xOffset - padding, yOffset, windowSize.x - (len + padding), yOffset + 1, arrayColor);      //underline
			ImGuiUtil::draw_text(font, 30, textStr, xOffset, yOffset, arrayColor);                                         //modulename
			ImGuiUtil::draw_text(font, 30, modeStr, xOffset + moduleWidth, yOffset, UIColor(160, 160, 160));              //mode
			yOffset += h * container.pos->y;
			col = arrayColor;
		} else {
			auto arrayColor = ColorUtil::rainbowColor(2, 1, 1, index * 100, 255);
			ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset + h, windowSize.x + padding, yOffset + (h - h * container.pos->y), UIColor(0, 0, 0, 100));                       //background
			ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset + h, xOffsetOri - 4, yOffset + (h - h * container.pos->y), arrayColor);                               //leftrect
			if (index) ImGuiUtil::draw_rect(xOffsetOri - padding, yOffset + h, windowSize.x - (len + padding), yOffset - 1 + h, arrayColor);      //underline
			ImGuiUtil::draw_text(font, 30, textStr, xOffset, yOffset, arrayColor);                                         //modulename
			ImGuiUtil::draw_text(font, 30, modeStr, xOffset + moduleWidth, yOffset, UIColor(160, 160, 160));              //mode
			yOffset -= h * container.pos->y;
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