#pragma once

#include "Module.h"
#include <vector>
#include <memory>

class ModuleManager {
private:
	
	std::vector<std::unique_ptr<Module>> moduleList;
public:
	void initModule();
	std::vector<std::unique_ptr<Module>> getModuleList() {
		return moduleList;
	}
};

extern ModuleManager* moduleMgr;