#include "KillAura.h"

KillAura::KillAura() : Module('P', Category::COMBAT, "For testing module") {
	registerBoolSetting("Kill", &k, false);
	registerFloatSetting("Float", &a, 1.f, 1.f, 2.f);
	mode.addEntry(EnumEntry("Ka1", 0))
		.addEntry(EnumEntry("Ka2", 1))
		.addEntry(EnumEntry("Ka3", 2))
		.addEntry(EnumEntry("Ka4", 3))
		.addEntry(EnumEntry("Ka5", 4))
		.addEntry(EnumEntry("Ka6", 5));
	registerEnumSetting("Mode", &mode, 0);
};

KillAura::~KillAura() {
};

const char* KillAura::getModuleName() {
	if (!k) {
		return "KillAura";
	}
	else {
		return "TestAura";
	}
}

void KillAura::onTick(GameMode* gm) {
}