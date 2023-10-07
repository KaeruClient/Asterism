#include "TestModule.h"

TestModule::TestModule() : Module(0x0, Category::MISC, "For testing module") {
};

TestModule::~TestModule() {
};

const char* TestModule::getModuleName() {
	return "TestModule";
}

const char* TestModule::getModeName() {
	return "Test";
}
