#pragma once

#include "Module.h"
#include <vector>

class ModuleManager {
private:
	
	std::vector<Module> moduleList;
public:
	std::vector<Module> getModuleList() {
		return moduleList;
	}
};

extern ModuleManager* moduleMgr;