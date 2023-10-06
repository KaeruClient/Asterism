#include "ModuleManager.h"
#include "../SDK/Structs/GameMode.h"
#include "../SDK/Structs/MinecraftUIRenderContext.h"
#include "../Includes/imgui/imgui.h"


ModuleManager::ModuleManager(GameData* game) {
	game = game;
}

ModuleManager::~ModuleManager() {
	initialized = false;
	auto lock = lockModuleListExclusive();
	moduleList.clear();
}

void ModuleManager::initModules() {
	{
		auto lock = lockModuleListExclusive();

		moduleList.emplace_back(new Watermark());

		moduleList.emplace_back(new ArrayList());

		getModuleByName("Watermark")->setEnabled(true);
		getModuleByName("ArrayList")->setEnabled(true);
		// Sort modules alphabetically
		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{ *current->getModuleName() } < std::string{ *other->getModuleName() };
			});

		initialized = true;
	}

}

void ModuleManager::onTick(GameMode* gameMode) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onTick(gameMode);
	}
}

std::vector<std::shared_ptr<Module>>* ModuleManager::getModuleList() {
	return &moduleList;
}

void ModuleManager::onImRender() {
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onImRender();
	}
}

void ModuleManager::onRender(MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onRender(renderCtx);
	}
}

ModuleManager* moduleMgr = new ModuleManager(&g_Data);
