#pragma once

#include "Module.h"

class TestModule : public Module {
public:
	TestModule();
	~TestModule();

	virtual const char* getModuleName() override;
	virtual const char* getModeName() override;
};