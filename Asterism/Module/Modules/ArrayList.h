#pragma once

#include "Module.h"

class ArrayList : public Module {
public:
	ArrayList();
	~ArrayList();

	virtual const char* getModuleName() override;
	virtual void onImRender() override;
};