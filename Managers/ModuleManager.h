#pragma once
#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include <algorithm> 
#include "../Includes/imgui/imgui.h"
#include "../Asterism/Module/Modules/Module.h"

#include "../Asterism/Module/Modules/Watermark.h"
#include "../Asterism/Module/Modules/ArrayList.h"
#include "../Asterism/Module/Modules/PacketMine.h"
#include "../Asterism/Module/Modules/TestModule.h"
#include "../Memory/GameData.h"
//hi ikaaa ikaclient on TRASH
class ModuleManager {
private:
	std::vector<std::shared_ptr<Module>> moduleList;
	bool initialized = false;
	std::shared_mutex moduleListMutex;
public:
	ModuleManager(GameData*);
	~ModuleManager();
	void initModules();
	void onTick(GameMode* gameMode);
	void onRender(MinecraftUIRenderContext* renderCtx);
	void onImRender();
	void onKey(__int32);
	std::shared_lock<std::shared_mutex> lockModuleList() { return std::shared_lock<std::shared_mutex>(moduleListMutex); }
	std::unique_lock<std::shared_mutex> lockModuleListExclusive() { return std::unique_lock<std::shared_mutex>(moduleListMutex); }

	std::shared_mutex* getModuleListLock() { return &moduleListMutex; }

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<Module>>* getModuleList();


	std::shared_ptr<Module> getModuleByName(const char* str) {
		for (auto mod : moduleList) {
			if (mod->getModuleName() == str)
				return mod;
		}
	}

	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		auto lock = lockModuleList(); 
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())) {
				return pRet;
			}
		}
		return nullptr;
	};
}; //‚ ‚È‚½‚Í‚Ç‚¤‚µ‚½
extern ModuleManager* moduleMgr;