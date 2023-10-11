#pragma once
#include "../Maths/Vectors.h"
#include "../../Utils/Utils.h"
class AABB;
class MobEffectInstance;
class CompoundTag;
class ItemStack;
class Block; // Today I want to learn how to find any sigs. That is hard for me>< <ye>
class InputMode;
class Entity;

class EntityList {
private:
	char pad_0x0000[0x70];  //0x0000
public:
	uintptr_t firstEntity;  //0x0050
	uintptr_t lastEntity;   //0x0058
	uintptr_t endAddr;      //0x0060

	inline size_t getListSize() {
		return (lastEntity - firstEntity) / sizeof(uintptr_t);
	}

	inline Entity* get(size_t idx) {
		if (idx >= getListSize())
			return 0;
		return *reinterpret_cast<Entity**>(firstEntity + (idx * sizeof(uintptr_t)));
	}

	Entity* operator[](size_t idx) {
		return get(idx);
	}
};  //Size=0x0050

class MobEntityList {
public:
private:
	char pad_0x0000[0x38];  //0x0000
public:
	uintptr_t firstEntity;  //0x0038
	uintptr_t lastEntity;   //0x0040
	uintptr_t endAddr;      //0x0048

	inline size_t getListSize() {
		return (lastEntity - firstEntity) / sizeof(uintptr_t);
	}

	inline Entity* get(size_t idx) {
		if (idx >= getListSize())
			return 0;
		return *reinterpret_cast<Entity**>(firstEntity + (idx * sizeof(uintptr_t)));
	}

	Entity* operator[](size_t idx) {
		return get(idx);
	}
};  //Size=0x0050

class Actor {
public:
	virtual __int64 getLastHurtByMob(void);                                             // 0
	virtual __int64 setLastHurtByMob(Actor*);                                         // 1
	virtual __int64 getLastHurtByActor(void);                                          // 2
	virtual __int64 setLastHurtByActor(Actor*);                                      // 3
	virtual __int64 getLastHurtMob(void);                                               // 4
	virtual __int64 setLastHurtMob(Actor*);                                           // 5
	virtual __int64 outOfWorld(void);                                                   // 6
	virtual __int64 reloadHardcoded();                                                  // 7
	virtual __int64 reloadHardcodedClient();                                            // 8
	virtual __int64 initializeComponents();                                             // 9
	virtual __int64 reloadComponents();                                                 // 10
	virtual __int64 _serverInitItemStackIds(void);                                      // 11
	virtual __int64 _doInitialMove(void);                                               // 12
	virtual bool hasComponent();                                                        // 13
	virtual void destructor();                                                          // 14
	virtual __int64 reset(void);                                                        // 15
	virtual __int64 getOnDeathExperience(void);                                         // 16
	virtual __int64 getOwnerActorType(void);                                           // 17
	virtual __int64 remove(void);                                                       // 18
	virtual __int64 setPos(vec3_t const&);                                               // 19
	virtual bool isRuntimePredictedMovementEnabled(void);                               // 20
	virtual __int64 getPredictedMovementValues(void);                                   // 21
	virtual vec3_t* getPos(void);                                                         // 22
	virtual vec3_t* getPosOld(void);                                                      // 23
	virtual vec3_t* getPosExtrapolated(float);                                            // 24
	virtual vec3_t* getAttachPos(__int64, float);                                         // 25
	virtual vec3_t* getFiringPos(void);                                                   // 26
	virtual __int64 setRot(vec2_t const&);                                               // 27
	virtual __int64 move(vec3_t const&);                                                 // 28
	virtual __int64 move(__int64, vec3_t const&);                                        // 29
	virtual __int64 getInterpolatedRidingPosition(float);                               // 30
	virtual __int64 getInterpolatedBodyRot(float);                                      // 31
	virtual __int64 getInterpolatedHeadRot(float);                                      // 32
	virtual __int64 getInterpolatedBodyYaw(float);                                      // 33
	virtual __int64 getYawSpeedInDegreesPerSecond(void);                                // 34
	virtual __int64 getInterpolatedWalkAnimSpeed(float);                                // 35
	virtual __int64 getInterpolatedRidingOffset(float);                                 // 36
	virtual __int64 checkBlockCollisions(AABB const&, __int64);                        // 37
	virtual __int64 updateActorInside(AABB const&);                                   // 38
	virtual __int64 updateActorInside(void);                                           // 39
	virtual bool isFireImmune(void);                                                    // 40
	virtual __int64 breaksFallingBlocks(void);                                          // 41
	virtual __int64 blockedByShield(__int64 const&, Actor*);                         // 42
	virtual __int64 teleportTo(vec3_t const&, bool, int, int);                           // 43
	virtual __int64 tryTeleportTo(vec3_t const&, bool, bool, int, int);                  // 44
	virtual __int64 chorusFruitTeleport(vec3_t const&);                                  // 45
	virtual __int64 lerpMotion(vec3_t const&);                                           // 46
	virtual __int64 tryCreateAddActorPacket(void);                                      // 47
	virtual __int64 normalTick(void);                                                   // 48
	virtual __int64 baseTick(void);                                                     // 49
	virtual __int64 vehicleTick(void);                                                  // 50
	virtual __int64 positionPassenger(Actor*, float);                                 // 51
	virtual __int64 getRidingHeight(void);                                              // 52
	virtual __int64 startRiding(Actor*);                                              // 53
	virtual __int64 addPassenger(Actor*);                                             // 54
	virtual __int64 flagPassengerToRemove(Actor*);                                    // 55
	virtual __int64 getExitTip(void*, int);                                      // 56
	virtual __int64 intersects(vec3_t const&, vec3_t const&);                             // 57
	virtual bool isInWall(void);                                                        // 58
	virtual bool isInvisible(void);                                                     // 59
	virtual bool canShowNameTag(void);                                                  // 60
	virtual bool canExistInPeaceful(void);                                              // 61
	virtual __int64 setNameTagVisible(bool);                                            // 62
	virtual void* getNameTag(void);                                               // 63
	virtual __int64 getNameTagAsHash(void);                                             // 64
	virtual void* getFormattedNameTag(void);                                      // 65
	virtual __int64 filterFormattedNameTag(__int64);                                    // 66
	virtual __int64 setNameTag(void*);                                           // 67
	virtual __int64 getAlwaysShowNameTag(void);                                         // 68
	virtual __int64 setScoreTag(void*);                                          // 69
	virtual __int64 getScoreTag(void);                                                  // 70
	virtual bool isInWater(void);                                                       // 71
	virtual bool hasEnteredWater(void);                                                 // 72
	virtual bool isInLava(void);                                                        // 73
	virtual bool isUnderLiquid(__int64);                                                // 74
	virtual bool isOverWater(void);                                                     // 75
	virtual __int64 setBlockMovementSlowdownMultiplier(vec3_t const&);                   // 76
	virtual __int64 resetBlockMovementSlowdownMultiplier(void);                         // 77
	virtual __int64 getCameraOffset(void);                                              // 78
	virtual __int64 getShadowHeightOffs(void);                                          // 79
	virtual __int64 getShadowRadius(void);                                              // 80
	virtual __int64 getHeadLookVector(float);                                           // 81
	virtual bool canSeeInvisible(void);                                                 // 82
	virtual bool canSee(Actor*);                                                      // 83
	virtual bool canSee(vec3_t const&);                                                  // 84
	virtual bool isSkyLit(float);                                                       // 85
	virtual __int64 getBrightness(float);                                               // 86
	virtual __int64 interactPreventDefault(void);                                       // 87
	virtual __int64 ActorTouch(Actor&);                                              // 88
	virtual __int64 onAboveBubbleColumn(bool);                                          // 89
	virtual __int64 onInsideBubbleColumn(bool);                                         // 90
	virtual bool isImmobile(void);                                                      // 91
	virtual bool isSilent(void);                                                        // 92
	virtual bool isPickable(void);                                                      // 93
	virtual bool isFishable(void);                                                      // 94
	virtual bool isSleeping(void);                                                      // 95
	virtual __int64 setSleeping(bool);                                                  // 96
	virtual bool isShootable(void);                                                     // 97
	virtual __int64 setSneaking(bool);                                                  // 98
	virtual bool isBlocking(void);                                                      // 99
	virtual bool isDamageBlocked(__int64 const&);                                      // 100
	virtual bool isAlive(void);                                                         // 101
	virtual bool isOnFire(void);                                                        // 102
	virtual bool isOnHotBlock(void);                                                    // 103
	virtual bool isCreativeModeAllowed(void);                                           // 104
	virtual bool isSurfaceMob(void);                                                    // 105
	virtual bool isTargetable(void);                                                    // 106
	virtual bool isLocalActor(void);                                                   // 107
	virtual bool isActor(void);                                                        // 108
	virtual bool isAffectedByWaterBottle(void);                                         // 109
	virtual bool canAttack(Actor*, bool);                                             // 110
	virtual __int64 setTarget(Actor*);                                                // 111
	virtual __int64 findAttackTarget(void);                                             // 112
	virtual bool isValidTarget(Actor*);                                               // 113
	virtual __int64 attack(Actor*, __int64 const&);                                  // 114
	virtual __int64 performRangedAttack(Actor*, float);                               // 115
	virtual __int64 adjustDamageAmount(int&);                                          // 116
	virtual __int64 getEquipmentCount(void);                                            // 117
	virtual __int64 setOwner(__int64);                                                  // 118
	virtual __int64 setSitting(bool);                                                   // 119
	virtual __int64 onTame(void);                                                       // 120
	virtual __int64 onFailedTame(void);                                                 // 121
	virtual __int64 getInventorySize(void);                                             // 122
	virtual __int64 getEquipSlots(void);                                                // 123
	virtual __int64 getChestSlots(void);                                                // 124
	virtual __int64 setStanding(bool);                                                  // 125
	virtual bool canPowerJump(void);                                                    // 126
	virtual __int64 setCanPowerJump(bool);                                              // 127
	virtual bool isJumping(void);                                                       // 128
	virtual bool isEnchanted(void);                                                     // 129
	virtual __int64 vehicleLanded(vec3_t const&, vec3_t const&);                          // 130
	virtual __int64 shouldRender(void);                                                 // 131
	virtual __int64 playAmbientSound(void);                                             // 132
	virtual __int64 getAmbientSound(void);                                              // 133
	virtual bool isInvulnerableTo(__int64 const&);                                     // 134
	virtual __int64 getBlockDamageCause(Block const&);                                 // 135
	virtual __int64 actuallyHurt(int, __int64 const&, bool);                           // 136
	virtual __int64 animateHurt(void);                                                  // 137
	virtual __int64 doFireHurt(int);                                                    // 138
	virtual __int64 onLightningHit(void);                                               // 139
	virtual __int64 onBounceStarted(vec3_ti const&, Block const&);                      // 140
	virtual __int64 feed(int);                                                          // 141
	virtual __int64 handleActorEvent(__int64, int);                                    // 142
	virtual __int64 getPickRadius(void);                                                // 143
	virtual __int64 getActorRendererId(void);                                           // 144
	virtual __int64 spawnAtLocation(int, int);                                          // 145
	virtual __int64 spawnAtLocation(int, int, float);                                   // 146
	virtual __int64 spawnAtLocation(Block const&, int);                                // 147
	virtual __int64 spawnAtLocation(Block const&, int, float);                         // 148
	virtual __int64 spawnAtLocation(ItemStack const&, float);                          // 149
	virtual __int64 despawn(void);                                                      // 150
	virtual __int64 killed(Actor*);                                                   // 151
	virtual __int64 awardKillScore(Actor*, int);                                      // 152
	virtual __int64 setArmor(int, ItemStack const&);                                   // 153
	virtual ItemStack* getArmor(int);                                                   // 154
	virtual __int64 getAllArmor(void);                                                  // 155
	virtual __int64 getArmorMaterialTypeInSlot(int);                                    // 156
	virtual __int64 getArmorMaterialTextureTypeInSlot(int);                             // 157
	virtual __int64 getArmorColorInSlot(int, int);                                      // 158
	virtual __int64 getEquippedSlot(int);                                               // 159
	virtual __int64 setEquippedSlot(int, ItemStack const&);                            // 160
	virtual __int64 getCarriedItem(void);                                               // 161
	virtual __int64 setCarriedItem(ItemStack const*);                                  // 162
	virtual __int64 setOffhandSlot(ItemStack const*);                                  // 163
	virtual ItemStack* getEquippedTotem(void);                                          // 164
	virtual __int64 consumeTotem(void);                                                 // 165
	virtual __int64 save(CompoundTag*);                                                // 166
	virtual __int64 saveWithoutId(CompoundTag&);                                       // 167
	virtual __int64 load(CompoundTag const&, __int64);                                 // 168
	virtual __int64 loadLinks(CompoundTag, __int64, __int64);                           // 169
	virtual int getActorTypeId(void);                                                  // 170
	virtual __int64 queryActorRenderer(void);                                          // 171
	virtual __int64 getSourceUniqueID(void);                                            // 172
	virtual __int64 thawFreezeEffect(void);                                             // 173
	virtual bool canFreeze(void);                                                       // 174
	virtual bool isWearingLeatherArmor(void);                                           // 175
	virtual __int64 getLiquidAABB(__int64);                                             // 176
	virtual __int64 handleInsidePortal(vec3_ti const&);                                  // 177
	virtual __int64 getPortalCooldown(void);                                            // 178
	virtual __int64 getPortalWaitTime(void);                                            // 179
	virtual int getDimensionId(int*);                                                  // 180
	virtual bool canChangeDimensions(void);                                             // 181
	virtual __int64 changeDimension(int, bool);                                         // 182
	virtual __int64 changeDimension(__int64 const&);                                   // 183
	virtual __int64 getControllingActor(void);                                         // 184
	virtual __int64 checkFallDamage(float, bool);                                       // 185
	virtual __int64 causeFallDamage(float);                                             // 186
	virtual __int64 handleFallDistanceOnServer(float, float, bool);                     // 187
	virtual __int64 playSynchronizedSound(__int64, vec3_t const&, Block const&, bool);  // 188
	virtual __int64 playSynchronizedSound(__int64, vec3_t const&, int, bool);            // 189
	virtual __int64 onSynchedFlagUpdate(int, long, long);                               // 190
	virtual __int64 onSynchedDataUpdate(int);                                           // 191
	virtual bool canAddPassenger(Actor*);                                             // 192
	virtual bool canPickupItem(ItemStack const&);                                      // 193
	virtual bool canBePulledIntoVehicle(void);                                          // 194
	virtual __int64 inCaravan(void);                                                    // 195
	virtual bool isLeashableType(void);                                                 // 196
	virtual __int64 tickLeash(void);                                                    // 197
	virtual __int64 sendMotionPacketIfNeeded(void);                                     // 198
	virtual bool canSynchronizeNewActor(void);                                         // 199
	virtual __int64 stopRiding(bool, bool, bool);                                       // 200
	virtual __int64 startSwimming(void);                                                // 201
	virtual __int64 stopSwimming(void);                                                 // 202
	virtual __int64 buildDebugInfo(std::string&);                                      // 203
	virtual __int64 getCommandPermissionLevel(void);                                    // 204
	virtual bool isClientSide(void);                                                    // 205
	virtual  int* getMutableAttribute();
	virtual  void* getAttribute();    // 207
	virtual __int64 getDeathTime(void);                                           // 208
	virtual __int64 heal(int);                                                    // 209
	virtual bool isInvertedHealAndHarm(void);                                     // 210
	virtual bool canBeAffected(int);                                              // 211
	virtual bool canBeAffected();                        // 212
	virtual bool canBeAffectedByArrow();                 // 213
	virtual __int64 onEffectAdded();                           // 214
	virtual __int64 onEffectUpdated();                         // 215
	virtual __int64 onEffectRemoved();                         // 216
	virtual __int64 getAnimationComponent(void);                                  // 217
	virtual __int64 openContainerComponent(Actor&);                             // 218
	virtual __int64 swing(void);                                                  // 219
};
class GameMode {
private:
	virtual void Constructor();
public:
	virtual void startDestroyBlock(vec3_ti const&, unsigned char, bool&);
	virtual void destroyBlock(vec3_ti const&, unsigned char);
	virtual void continueDestroyBlock(vec3_ti const&, unsigned char, vec3_t const&, bool&);
	virtual void stopDestroyBlock(vec3_ti const&);
	virtual void startBuildBlock(vec3_ti const&, unsigned char);
	virtual void buildBlock(vec3_ti const&, unsigned char, bool);
	virtual void continueBuildBlock(vec3_ti const&, unsigned char);
	virtual void stopBuildBlock(void);
private:
	virtual void tick(void);
	virtual int getPickRange(InputMode const&, bool);
	virtual void useItem(ItemStack&);
	virtual void useItemOn(ItemStack&, vec3_ti const&, unsigned char, vec3_t const&, Block const*);
	virtual void interact(Actor&, vec3_t const&);
public:
	virtual void attack(Actor&);
private:
	virtual void releaseUsingItem(void);
	virtual void setTrialMode(bool);
	virtual bool isInTrialMode(void);
	virtual void registerUpsellScreenCallback();
public:
	Actor* player;
	void baseUseItem(ItemStack& stack) {
		using baseUseItem = void(*)(GameMode*, ItemStack&);
		static baseUseItem baseUseItemFunc = reinterpret_cast<baseUseItem>(Utils::findSig("48 89 5C 24 10 48 89 74 24 18 55 57 41 56 48 8D 6C 24 90 48 81 EC 70 01 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 60 48 8B F2 48 8B F9 45 33 F6 4C 89 75 08 48 8D 4D 08 E8 ?? ?? ?? ?? 90 48"));
		return baseUseItemFunc(this, stack);
	}
};