#pragma once
#include "../Managers/Module.h"
#include "../Managers/ModuleManager.h"

class SlowSwing : public Module {
private:
	int swingtick = 25;

public:

	SlowSwing();
	~SlowSwing();

	const char* getModuleName();
};
