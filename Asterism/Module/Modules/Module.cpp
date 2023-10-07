#include "Module.h"
Module::Module(int key, Category c, const char* tooltip) {
	this->key = key;
	this->category = c;
	this->tooltip = tooltip;
}

const char* Module::getModuleName() {
	return "Module";
}
const char* Module::getModeName() {
	return "";
}
void Module::onKey(__int32 key) {
}