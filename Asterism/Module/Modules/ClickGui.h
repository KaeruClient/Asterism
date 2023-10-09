#pragma once
//insert : 0x2D

#include "Module.h"
#include "../../../SDK/Maths/GlobalMath.h"
class ClickGui : public Module {
public:
	ClickGui();
	~ClickGui();
	 const char* catToName(Category cat) {
		 const char* categoryName{};

		// Get Category Name
		{
			switch (cat) {
			case Category::COMBAT:
				categoryName = "Combat";
				break;
			case Category::RENDER:
				categoryName = "Visual";
				break;
			case Category::PLAYER:
				categoryName = "Player";
				break;
			case Category::WORLD:
				categoryName = "World";
				break;
			case Category::MISC:
				categoryName = "Misc";
				break;
			}
		}
		return categoryName;
	}
	virtual const char* getModuleName() override;
	virtual void onImRender() override;
	void getModuleListByCategory(Category category, std::vector<std::shared_ptr<Module>>* modList);
};