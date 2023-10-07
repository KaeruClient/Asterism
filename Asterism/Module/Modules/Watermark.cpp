#include "Watermark.h"
#include "../../../Utils/ImGuiUtils.h"

Watermark::Watermark() : Module(0x0, Category::RENDER, "im watermark") {
};

Watermark::~Watermark() {
};

const char* Watermark::getModuleName() {
	return "Watermark";
}

void Watermark::onImRender() {
	ImFont* font = ImGui::GetIO().FontDefault;
	UIColor color = UIColor{ 0, 150, 150, 255 };
	UIColor color2 = UIColor{ 0, 0, 0, 255 };
	UIColor color3 = UIColor{ 255, 255, 255, 255 };
	//ImGuiUtil::draw_gradient_rounded(10, 10, 200, 70, 20.f, color, color2);

	std::string name = "Asterism";
	vec2_t area = ImGuiUtil::get_text_area(font, 50, name);
	ImGuiUtil::draw_gradient_rounded(10, 10, area.x + 20, area.y + 10, 15, color, color2);
	ImGuiUtil::draw_text(font, 50, name, 15, 10, color3);

}