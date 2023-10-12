#pragma once
#include "GameMode.h"
#include <vector>
class Attribute;
class MobEffect;
class ActorFlags;
class ActorLocation;
class ActorCategory;
class ActorType;
class IActorMovementProxy;
class BlockLegacy;
class DirectMovementProxy {
	virtual void destructor(); //2
	virtual void isRiding(void); //5
	virtual void hasPassenger(void); //6
	virtual void isClientSide(void); //7
	virtual void isInWater(void); //8
	virtual void isOverScaffolding(void); //9
	virtual void isHeadInWater(void); //10
	virtual void isSwimmer(void); //11
	virtual void isControlledByLocalInstance(void); //12
	virtual void hasTeleported(void); //13
	virtual void isWearingLeatherBoots(void); //14
	virtual void hasFamily(void* const&); //15
	virtual void isWorldBuilder(void); //16
	virtual void isSleeping(void); //17
	virtual void setStuckInCollider(bool); //18
	virtual void setWasPenetratingLastFrame(bool); //19
	virtual void setSubAABBs(std::vector<AABB, std::allocator<AABB>> const&); //20
	virtual void isStackable(void); //21
	virtual void setCollidableMobNear(bool); //22
	virtual void isFlying(void); //23
	virtual void wasOnGround(void); //24
	virtual void setWasOnGround(bool); //25
	virtual void setHorizontalCollision(bool); //26
	virtual void getVerticalCollision(void); //27
	virtual void setVerticalCollision(bool); //28
	virtual void getCollision(void); //29
	virtual void setCollision(bool); //30
	virtual void getMaxAutoStep(void); //31
	virtual void getHeightOffset(void); //32
	virtual void getCurrentSwimAmount(void); //33
	virtual void getAttribute(Attribute const&); //34
	virtual void hasEffect(MobEffect const&); //35
	virtual void getEffect(MobEffect const&); //36
	virtual void getEntityData(void); //37
	virtual void setStatusFlag(ActorFlags, bool); //38
	virtual void getStatusFlag(ActorFlags); //39
	virtual void hasCategory(ActorCategory); //40
	virtual void isType(ActorType); //41
	virtual void getEntityTypeId(void); //42
	virtual void getPosition(void); //43
	virtual void getPosPrev(void); //44
	virtual void setPosDirect(vec3_t const&); //45
	virtual void setPosition(vec3_t const&); //46
	virtual void getPosDelta(void); //47
	virtual void getPosDeltaNonConst(void); //48
	virtual void setAABB(AABB const&); //49
	virtual void getAABB(void); //50
	virtual void getAABBDim(void); //51
	virtual void getAttachPos(ActorLocation, float); //52
	virtual void getRotation(void); //53
	virtual void setRotation(vec2_t const&); //54
	virtual void getPrevRotation(void); //55
	virtual void getFallDistance(void); //56
	virtual void setFallDistance(float); //57
	virtual void isSneaking(void); //58
	virtual void setSneaking(bool); //59
	virtual void getDimensionBlockSource(void); //60
	virtual void getRegionFromDimension(void); //61
	virtual void hasDimension(void); //62
	virtual void getVehicle(void); //63
	virtual void isWASDControlled(void); //64
	virtual void getControllingSeat(void); //65
	virtual void getPassengerIndex(IActorMovementProxy const&); //66
	virtual void tryAsBoat(void); //67
	virtual void tryAsMob(void); //68
	virtual void tryAsMob_0(void); //69
	virtual void tryAsPlayer(void); //70
	virtual void tryAsPlayer_0(void); //71
	virtual void getOrCreateUniqueID(void); //72
	virtual void getRuntimeID(void); //73
	virtual void shouldTriggerOnStandOn(BlockLegacy const&, vec3_ti const&); //74
	virtual void move(vec3_t const&); //75
	virtual void checkFallDamage(float, bool); //76
	virtual void onBounceStarted(vec3_ti const&, Block const&); //77
	virtual void updatePrevPosRot(void); //78
	virtual void _teleportTo(vec3_t const&, bool, int, int); //79
	virtual void _getRawActor(void); //80
	virtual void _getRawActor_0(void); //81
	virtual void _getEntityData(void); //82
	virtual void _setPreviousPosRot(void); //83
	virtual void _setHasTeleported(bool); //84
	virtual void _advanceLiveFrame(); //85
	virtual void getEntity(void); //86
	virtual void getEntity_0(void); //87
	virtual void isJumping(void); //88
	virtual void setJumping(bool); //89
	virtual void getJumpStartPos(void); //90
	virtual void getJumpPower(void); //91
	virtual void getJumpTicks(void); //92
	virtual void setJumpTicks(int); //93
	virtual void onPlayerJump(int); //94
	virtual void setSpeed(float); //95
	virtual void isSprinting(void); //96
	virtual void setSprinting(bool); //97
	virtual void discardFriction(void); //98
	virtual void ascendBlockByJumping(void); //99
	virtual void descendBlockByCrouching(void); //100
	virtual void getLocalMoveVelocity(void); //101
	virtual void setLocalMoveVelocity(vec3_t const&); //102
	virtual void getMobRotation(void); //103
	virtual void setMobRotation(float); //104
	virtual void getNoActionTime(void); //105
	virtual void setNoActionTime(int); //106
	virtual void getYHeadRot(void); //107
	virtual void setYHeadRot(float); //108
	virtual void emitJumpPreventedEvent(vec3_ti const&); //109
	virtual void setFlySpeed(float); //110
	virtual void getFrictionModifier(void); //111
	virtual void setFrictionModifier(float); //112
	virtual void _getMob(void); //113
	virtual void _setYHeadRotOld(float); //114
	virtual void getControllingPlayer(void); //115
	virtual void setPaddleState(void*, bool); //116

};