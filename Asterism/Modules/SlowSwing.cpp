#include "SlowSwing.h"

SlowSwing::SlowSwing() : Module(0x0, Category::VISUAL, "Slow Swing!") {
}

SlowSwing::~SlowSwing() {

}

const char* SlowSwing::getModuleName() {
	return "SlowSwing";
}

void SlowSwing::onTick(GameMode* gm) {

}