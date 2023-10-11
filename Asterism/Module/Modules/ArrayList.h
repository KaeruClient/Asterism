#pragma once

#include "Module.h"
#include "../../../SDK/Maths/GlobalMath.h"
class ArrayList : public Module {
public:
	ArrayList();
	~ArrayList();
	bool bottom = true;
	virtual const char* getModuleName() override;
	virtual void onImRender() override;
};