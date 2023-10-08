#include "PacketMine.h"

PacketMine::PacketMine() : Module('R', Category::WORLD, "For testing module") {
};

PacketMine::~PacketMine() {
};

const char* PacketMine::getModuleName() {
	return "PacketMine";
}
void PacketMine::onTick(GameMode* gm) {
}