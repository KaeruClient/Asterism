#include "ArrayList.h"

#include "../../../Utils/ImGuiUtils.h"
#include "../../../Managers/ModuleManager.h"
#include <set>

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
	bool enabled;
	int keybind;
	float textWidth;
	vec2_t* pos;
	bool shouldRender = true;

	ModuleContainer(std::shared_ptr<Module> mod) {
		const char* moduleNameChr = mod->getModuleName();
		this->enabled = mod->isEnabled();
		this->backingModule = mod;
		
		moduleName = moduleNameChr;

		if (!this->enabled)
			this->shouldRender = false;
		this->textWidth = ImGuiUtil::get_text_area(font, 30, moduleName).x;
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

	ImFont* font = ImGui::GetIO().FontDefault;
	vec2_t windowSize = ImGuiUtil::get_window_size();
	float yOffset = 0;
	for (auto it = modContainerList.begin(); it != modContainerList.end(); ++it) {

		if (!it->shouldRender) continue;

		auto& container = *it;
		auto textStr = container.moduleName;
		auto textWidth = container.textWidth;

		auto xOffsetOri = windowSize.x - textWidth - 10;

		ImGuiUtil::draw_text(font, 30, textStr, xOffsetOri, yOffset, UIColor(0,255,255));

		yOffset += ImGuiUtil::get_text_area(font, 30, textStr).y;
	}
}