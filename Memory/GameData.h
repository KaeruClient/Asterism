#pragma once
#include <d3d11.h>
#include <d3d10.h>
#include <d3d12.h>
#include <d3d.h>

#include <winerror.h>
#include <windef.h>
#include <WinUser.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <Psapi.h>

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <basetsd.h>

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <cmath>
#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include <algorithm> 
#include "../SDK/Structs/GameMode.h"
struct InfoBoxData {
	bool isOpen = true;
	float fadeTarget = 1;
	float fadeVal = 0;
	float duration = 0;
	bool check = false;
	vec2_t animate;
	float maxDuration = 0;
	float colorIndex = 0;
	int colorR = 0;
	int colorG = 0;
	int colorB = 0;
	std::string title;
	std::string message;

	InfoBoxData(std::string title, std::string message) : title(title), message(message) {};

	void fade() {
		fadeVal = fadeTarget - ((fadeTarget - fadeVal) + 0.65f);
		if (fadeTarget == 0 && fadeVal < 0.001f)
			isOpen = false;
	}
};
class GameData {
private:
	//SDKのサポート
	GameMode* _gm = nullptr;
	std::vector<std::shared_ptr<InfoBoxData>> infoBoxQueue;
public:

	inline std::shared_ptr<InfoBoxData> getFreshInfoBox() {
		while (!this->infoBoxQueue.empty()) {
			auto box = this->infoBoxQueue.front();
			if (!box->isOpen) {
				this->infoBoxQueue.erase(this->infoBoxQueue.begin());
				continue;
			}
			return box;
		}
		return std::shared_ptr<InfoBoxData>();
	}

	inline std::vector<std::shared_ptr<InfoBoxData>>& getInfoBoxList() {
		while (!this->infoBoxQueue.empty()) {
			auto box = this->infoBoxQueue.front();
			if (!box->isOpen) {
				this->infoBoxQueue.erase(this->infoBoxQueue.begin());
				continue;
			}
			break;
		}
		return this->infoBoxQueue;
	}

	inline std::shared_ptr<InfoBoxData> addInfoBox(std::string title, std::string message) { // success, warning, error
		auto box = std::make_shared<InfoBoxData>(title, message);
		this->infoBoxQueue.push_back(box);
		return box;
	}
	static std::map<uint64_t, Actor*> entitylist;
	void setGameMode(GameMode* gm) {
		_gm = gm;
	}
	GameMode* getGameMode() {
		return _gm;
	}
};
extern GameData g_Data;