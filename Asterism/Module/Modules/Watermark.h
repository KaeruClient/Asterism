#pragma once
#include "Module.h"

class Watermark : public Module {
public: 
	Watermark();
	~Watermark();

	virtual const char* getModuleName() override;
	virtual void onImRender() override;
};