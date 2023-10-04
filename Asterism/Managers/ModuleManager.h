#pragma once

#include "Module.h"
#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>
//hi ikaaa ikaclient on TRASH
class ModuleManager {
private:
	std::vector<std::shared_ptr<Module>> moduleList;
	bool initialized = false;
	std::shared_mutex moduleListMutex;
public:
	std::shared_mutex* getModuleListLock() { return &moduleListMutex; }

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<Module>>* getModuleList();
};

extern ModuleManager* moduleMgr;