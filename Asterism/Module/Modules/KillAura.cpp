#include "KillAura.h"

KillAura::KillAura() : Module('P', Category::COMBAT, "For testing module") {
};

KillAura::~KillAura() {
};

const char* KillAura::getModuleName() {
	return "KillAura";
}

void KillAura::onTick(GameMode* gm) {
}