#pragma once

#include "Module.h"
#include "../../../SDK/Maths/GlobalMath.h"
class PacketMine : public Module {
public:
	PacketMine();
	~PacketMine();
	bool packetmine = false;
	vec3_ti pos;
	uint8_t face;
	int odelay = 0;
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override {
		pos = vec3_ti(0, 0, 0);
		face = 0;
		odelay = 0;
		packetmine = false;
	};
};