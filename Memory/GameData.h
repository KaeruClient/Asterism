#pragma once

class GameData {
private:
	//SDK�̃T�|�[�g
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
GameData g_Data;