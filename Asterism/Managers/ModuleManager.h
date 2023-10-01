#pragma once

#include "Module.h"
#include "../../Utils/Utils.h"
#include <vector>
#include <memory>

class ModuleManager;

class ModuleManager {
private:

	std::vector<std::shared_ptr<Module>> moduleList;
public:
	void initModule();
	std::vector<std::shared_ptr<Module>> getModuleList() {
		return moduleList;
	}
	//ModuleManager(GameData* gameData);
	//virtual void onTick(GameMode* gm);
};

extern ModuleManager* moduleMgr;