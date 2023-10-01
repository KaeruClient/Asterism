#include "ModuleManager.h"
#include "Module.h"

//modules
#include "../Modules/SlowSwing.h"
//

void ModuleManager::initModule() {
	moduleList.emplace_back(std::make_unique<SlowSwing>);
}