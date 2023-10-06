#pragma once
#include <map>

class GameData {
private:
	//SDKのサポート
	GameMode* _gm = nullptr;
public:
	static std::map<uint64_t, Actor*> entitylist;

	void setGameMode(GameMode* gm) {
		_gm = gm;
	}
	GameMode* getGameMode() {
		return _gm;
	}
};
static GameData g_Data;