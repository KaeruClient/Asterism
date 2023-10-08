#include "TestModule.h"

TestModule::TestModule() : Module('X', Category::MISC, "For testing module") {
};

TestModule::~TestModule() {
};

const char* TestModule::getModuleName() {
	return "AutoCrystal";
}

const char* TestModule::getModeName() {
	return "Java";
}
