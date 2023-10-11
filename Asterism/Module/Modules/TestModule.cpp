#include "TestModule.h"
bool a = true;
TestModule::TestModule() : Module('X', Category::MISC, "For testing module") {
};

TestModule::~TestModule() {
};

const char* TestModule::getModuleName() {
	return "TestModule";
}

const char* TestModule::getModeName() {
	return "Mode";
}
