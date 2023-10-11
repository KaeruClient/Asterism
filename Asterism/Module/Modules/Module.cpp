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
void Module::setEnabled(bool ean) {
	if (this->enabled == ean) return;
	auto state = ean ? " Enabled" : " Disabled";
	std::string noftitle = "Notification:";
	auto notification = g_Data.addInfoBox(noftitle, std::string(std::string(state) + " " + this->getModuleName()));
	notification->duration = 3.f;
	if (ean) onEnable();
	else onDisable();
	this->enabled = ean;
};