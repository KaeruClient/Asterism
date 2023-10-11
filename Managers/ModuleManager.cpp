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
		moduleList.emplace_back(new TestModule());
		moduleList.emplace_back(new ArrayList());
		moduleList.emplace_back(new PacketMine());
		moduleList.emplace_back(new ClickGui());
		moduleList.emplace_back(new KillAura());

		// Sort modules alphabetically
		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{ *current->getModuleName() } < std::string{ *other->getModuleName() };
			});

		initialized = true;
	}
	getModule<Watermark>()->setEnabled(true);
	getModule<ArrayList>()->setEnabled(true);
	getModule<TestModule>()->setEnabled(false);
	int count = 0;
	for (auto& list : moduleList) {
		++count;
	}
	auto notification = g_Data.addInfoBox("Setup", std::to_string(count) + " modules successfully initialized!");
	notification->duration = 10.f;
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

void ModuleManager::onKey(__int32 key) {
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (key == mod->getBind()) {
			mod->setEnabled(!mod->isEnabled());
		}
		if (mod->isEnabled())
			mod->onKey(key);
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
