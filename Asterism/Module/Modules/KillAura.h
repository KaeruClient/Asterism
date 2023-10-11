#pragma once

#include "Module.h"

class KillAura : public Module {
public:
	KillAura();
	~KillAura();

	vec3_ti pos;
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override {
	};
};