#pragma once
#include "../Maths/Vector3.h"
#include "../Maths/BlockPos.h"
#include "../../Utils/Utils.h"
class Actor;
class ItemStack;
class Block;
class InputMode;
class GameMode {
private:
	virtual void Constructor();
public:
	virtual void startDestroyBlock(BlockPos const&, unsigned char, bool&);
	virtual void destroyBlock(BlockPos const&, unsigned char);
	virtual void continueDestroyBlock(BlockPos const&, unsigned char, Vector3 const&, bool&);
	virtual void stopDestroyBlock(BlockPos const&);
	virtual void startBuildBlock(BlockPos const&, unsigned char);
	virtual void buildBlock(BlockPos const&, unsigned char, bool);
	virtual void continueBuildBlock(BlockPos const&, unsigned char);
	virtual void stopBuildBlock(void);
private:
	virtual void tick(void);
	virtual int getPickRange(InputMode const&, bool);
	virtual void useItem(ItemStack&);
	virtual void useItemOn(ItemStack&, BlockPos const&, unsigned char, Vector3 const&, Block const*);
	virtual void interact(Actor&, Vector3 const&);
public:
	virtual void attack(Actor&);
private:
	virtual void releaseUsingItem(void);
	virtual void setTrialMode(bool);
	virtual bool isInTrialMode(void);
	//virtual void registerUpsellScreenCallback(std::function<void()(bool)>);
public:
	void baseUseItem(ItemStack& stack) {
		using baseUseItem = void(*)(GameMode*, ItemStack&);
		static baseUseItem baseUseItemFunc = reinterpret_cast<baseUseItem>(Utils::findSig("48 89 5C 24 10 48 89 74 24 18 55 57 41 56 48 8D 6C 24 90 48 81 EC 70 01 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 60 48 8B F2 48 8B F9 45 33 F6 4C 89 75 08 48 8D 4D 08 E8 ?? ?? ?? ?? 90 48"));
		return baseUseItemFunc(this, stack);
	}
};