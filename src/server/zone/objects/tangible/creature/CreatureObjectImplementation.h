/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef CREATUREOBJECTIMPLEMENTATION_H_
#define CREATUREOBJECTIMPLEMENTATION_H_

#include "CreatureObject.h"
#include "modifiers/ModifierEffect.h"
#include "modifiers/ModifierList.h"
#include "../SkillModList.h"
#include "../instrument/InstrumentObject.h"
#include "../weapon/WeaponObject.h"
#include "../../universe/group/GroupObject.h"
#include "../../universe/guild/GuildObject.h"
#include "FactionRank.h"
#include "Species.h"
#include "Moods.h"
#include "CreatureAttribute.h"
#include "CreaturePosture.h"
#include "CreatureState.h"
#include "CreatureFlag.h"

class PlayerObject;
class CreatureObjectImplementation : public CreatureObjectServant {
protected:
	ManagedReference<TangibleObject> hairObject;
	ManagedReference<InstrumentObject> instrumentObject;
	ManagedReference<SceneObject> targetObject;
	ManagedReference<WeaponObject> weaponObject;
	ManagedReference<GroupObject> groupObject;
	ManagedReference<GuildObject> guildObject;
	ManagedReference<CreatureObject> linkedCreature; //TODO: Is this only used for Mount?

	SkillModList skillMods;
	ModifierList modifiers;

	String templatePath;
	String performanceAnimation;
	String moodName;

	float height;
	float speed;
	float turnRadius;
	float terrainNegotiation;
	float acceleration;
	float deceleration;

	uint64 statesBitmask;
	uint64 listeningToID;
	uint64 groupInviterID;
	uint64 updateCounterGroupInvite;

	uint32 level;

	uint32 creditsBank;
	uint32 creditsCash;

	FactionRank* factionRank;
	Species* species; //Should this actually go in player?

	uint32 timestampLastMovement;
	uint32 updateCounterPosition;

	uint32 updateCounterAction;
	uint32 updateCounterHAM;
	uint32 updateCounterHAMMax;
	uint32 updateCounterHAMBase;
	uint32 updateCounterWounds;
	uint32 updateCounterEncumbrance;
	uint32 updateCounterPerformance;
	uint32 updateCounterEquipment;

	int32 attributesBase[9];
	int32 attributes[9];
	int32 attributesMax[9];
	int32 wounds[9];
	uint32 shockWounds;

	int32 encumbranceHealth;
	int32 encumbranceAction;
	int32 encumbranceMind;

	uint8 moodID;
	uint8 posture;

	bool stationary;

public:
	static const float DEFAULT_SPEED = 5.376f;
	static const float DEFAULT_ACCEL = 1.549f;

	//TODO: These need to be checked out.
	static const int NPC = 0x402;
	static const int DROID = 0x403;

public:
	CreatureObjectImplementation(uint64 objectid, int type = CREATURE);
	~CreatureObjectImplementation();

	//Saving and loading

	//Sending of packets
	virtual void sendTo(PlayerObject* player, bool close = true);
	virtual void sendToOwner(PlayerObject* player, bool close = true);

	//Modifiers
	virtual void addModifierEffect(ModifierEffect* modeffect, bool activate = true);
	virtual void removeModifierEffect(ModifierEffect* modeffect);
	virtual ModifierEffect* getModifierEffect(const String& modeffectname);
	virtual bool hasModifierEffect(const String& modeffectname);
	virtual float getModifier(const String& modname);
	virtual bool hasModifier(const String& modname);

	//General Commands
	virtual void groupInvite(PlayerObject* player);
	virtual void groupJoin(PlayerObject* player);
	virtual void groupLeave(PlayerObject* player);
	virtual void groupKick(PlayerObject* player);
	virtual void groupDisband(PlayerObject* player);
	virtual void groupDecline(PlayerObject* player);
	virtual void follow(TangibleObject* target);
	virtual void stopFollowing(TangibleObject* target);
	virtual void imageDesign(CreatureObject* target);
	virtual void diagnose(CreatureObject* target);
	virtual void tendDamage(CreatureObject* target);
	virtual void tendWound(CreatureObject* target);
	virtual void healWound(CreatureObject* target, uint8 woundtype);
	virtual void healDamage(CreatureObject* target);
	virtual void healState(CreatureObject* target, uint8 statetype);
	virtual void healEnhance(CreatureObject* target, uint8 enhancetype);
	virtual void healFirstAid(CreatureObject* target);
	virtual void healCurePoison(CreatureObject* target);
	virtual void healCureDisease(CreatureObject* target);
	virtual void healApplyPoison(CreatureObject* target);
	virtual void healApplyDisease(CreatureObject* target);
	virtual void performanceListen(CreatureObject* target);
	virtual void performanceWatch(CreatureObject* target);
	virtual void performanceStopListening(CreatureObject* target);
	virtual void performanceStopWatching(CreatureObject* target);

	virtual void updateTargetObject(uint64 targetid, bool updateclients = true);
	virtual void updateTargetObject(SceneObject* target, bool updateclients = true);

	//Setters
	inline void setMovementCounter(uint32 counter) {
		updateCounterMovement = counter;
	}

	inline void setLastMovementStamp(uint32 timestamp) {
		timestampLastMovement = timestamp;
	}

	inline void setLinkedCreature(CreatureObject* creature) {
		linkedCreature = creature;
	}

	inline void setHairObject(TangibleObject* hair) {
		hairObject = hair;
	}

	inline void setMoodID(uint8 moodid) {
		moodID = moodid;
		moodName = Moods::getName(moodid);
	}

	inline void setHeight(float value) {
		height = value;
	}

	inline void setBankCredits(uint32 credits) {
		creditsBank = credits;
	}

	inline void setCashCredits(uint32 credits) {
		creditsCash = credits;
	}

	inline void setFactionRank(FactionRank* rank) {
		factionRank = rank;
	}

	inline void setSpecies(Species* spec) {
		species = spec;
	}

	inline void setGroupObject(GroupObject* groupobject) {
		groupObject = groupobject;
	}

	inline void setGuildObject(GuildObject* guildobject) {
		guildObject = guildobject;
	}

	//Getters
	inline GroupObject* getGroupObject() {
		return groupObject.get();
	}

	inline GuildObject* getGuildObject() {
		return guildObject.get();
	}

	inline uint32 getLastMovementStamp() {
		return timestampLastMovement;
	}

	inline CreatureObject* getLinkedCreature() {
		return linkedCreature;
	}

	inline TangibleObject* getHairObject() {
		return hairObject.get();
	}

	inline uint8 getMoodID() {
		return moodID;
	}

	inline String& getTemplatePath() {
		return templatePath;
	}

	inline String& getMoodName() {
		return moodName;
	}

	inline String& getPerformanceAnimation() {
		return performanceAnimation;
	}

	inline uint64 getWeaponID() {
		if (weaponObject != NULL)
			return weaponObject->getObjectID();

		return 0;
	}

	inline uint64 getGroupID() {
		if (groupObject != NULL)
			return groupObject->getObjectID();

		return 0;
	}

	inline uint64 getGroupInviterID() {
		return groupInviterID;
	}

	inline uint32 getGuildID() {
		if (guildObject != NULL)
			return guildObject->getObjectID();

		return 0;
	}

	inline uint64 getTargetID() {
		if (targetObject != NULL)
			return targetObject->getObjectID();

		return 0;
	}

	inline uint32 getInstrumentID() {
		if (instrumentObject != NULL)
			return instrumentObject->getInstrumentID();

		return 0;
	}

	inline float getHeight() {
		return height;
	}

	inline uint64 getStatesBitmask() {
		return statesBitmask;
	}

	inline uint8 getPosture() {
		return posture;
	}

	inline uint32 getBankCredits() {
		return creditsBank;
	}

	inline uint32 getCashCredits() {
		return creditsCash;
	}

	inline FactionRank* getFactionRank() {
		return factionRank;
	}

	inline Species* getSpecies() {
		return species;
	}

	inline uint64 getListeningToID() {
		return listeningToID;
	}

	inline float getSpeed() {
		return speed;
	}

	inline float getTerrainNegotiation() {
		return terrainNegotiation;
	}

	inline float getTurnRadius() {
		return turnRadius;
	}

	inline float getAcceleration() {
		return acceleration;
	}

	inline float getDeceleration() {
		return deceleration;
	}

	inline uint32 getLevel() {
		return level;
	}

	inline uint32 getUpdateCounterAction() {
		return updateCounterAction;
	}

	inline uint64 getUpdateCounterGroupInvite() {
		return updateCounterGroupInvite;
	}

	inline uint32 getUpdateCounterHAM() {
		return updateCounterHAM;
	}

	inline uint32 getUpdateCounterHAMMax() {
		return updateCounterHAMMax;
	}

	inline uint32 getUpdateCounterHAMBase() {
		return updateCounterHAMBase;
	}

	inline uint32 getUpdateCounterWounds() {
		return updateCounterWounds;
	}

	inline uint32 getUpdateCounterEncumbrance() {
		return updateCounterEncumbrance;
	}

	inline uint32 getUpdateCounterPerformance() {
		return updateCounterPerformance;
	}

	inline uint32 getUpdateCounterEquipment() {
		return updateCounterEquipment;
	}

	inline int32 getAttribute(uint8 attribute) {
		return attributes[attribute];
	}

	inline int32 getHealth() {
		return attributes[CreatureAttribute::HEALTH];
	}

	inline int32 getStrength() {
		return attributes[CreatureAttribute::STRENGTH];
	}

	inline int32 getConstitution() {
		return attributes[CreatureAttribute::CONSTITUTION];
	}

	inline int32 getAction() {
		return attributes[CreatureAttribute::ACTION];
	}

	inline int32 getQuickness() {
		return attributes[CreatureAttribute::QUICKNESS];
	}

	inline int32 getStamina() {
		return attributes[CreatureAttribute::STAMINA];
	}

	inline int32 getMind() {
		return attributes[CreatureAttribute::MIND];
	}

	inline int32 getFocus() {
		return attributes[CreatureAttribute::FOCUS];
	}

	inline int32 getWillpower() {
		return attributes[CreatureAttribute::WILLPOWER];
	}

	inline int32 getAttributeBase(uint8 attribute) {
		return attributesBase[attribute];
	}

	inline int32 getHealthBase() {
		return attributesBase[CreatureAttribute::HEALTH];
	}

	inline int32 getStrengthBase() {
		return attributesBase[CreatureAttribute::STRENGTH];
	}

	inline int32 getConstitutionBase() {
		return attributesBase[CreatureAttribute::CONSTITUTION];
	}

	inline int32 getActionBase() {
		return attributesBase[CreatureAttribute::ACTION];
	}

	inline int32 getQuicknessBase() {
		return attributesBase[CreatureAttribute::QUICKNESS];
	}

	inline int32 getStaminaBase() {
		return attributesBase[CreatureAttribute::STAMINA];
	}

	inline int32 getMindBase() {
		return attributesBase[CreatureAttribute::MIND];
	}

	inline int32 getFocusBase() {
		return attributesBase[CreatureAttribute::FOCUS];
	}

	inline int32 getWillpowerBase() {
		return attributesBase[CreatureAttribute::WILLPOWER];
	}

	inline int32 getAttributeMax(uint8 attribute) {
		return attributesMax[attribute];
	}

	inline int32 getHealthMax() {
		return attributesMax[CreatureAttribute::HEALTH];
	}

	inline int32 getStrengthMax() {
		return attributesMax[CreatureAttribute::STRENGTH];
	}

	inline int32 getConstitutionMax() {
		return attributesMax[CreatureAttribute::CONSTITUTION];
	}

	inline int32 getActionMax() {
		return attributesMax[CreatureAttribute::ACTION];
	}

	inline int32 getQuicknessMax() {
		return attributesMax[CreatureAttribute::QUICKNESS];
	}

	inline int32 getStaminaMax() {
		return attributesMax[CreatureAttribute::STAMINA];
	}

	inline int32 getMindMax() {
		return attributesMax[CreatureAttribute::MIND];
	}

	inline int32 getFocusMax() {
		return attributesMax[CreatureAttribute::FOCUS];
	}

	inline int32 getWillpowerMax() {
		return attributesMax[CreatureAttribute::WILLPOWER];
	}

	inline int32 getAttributeWounds(uint8 attribute) {
		return wounds[attribute];
	}

	inline int32 getHealthWounds() {
		return wounds[CreatureAttribute::HEALTH];
	}

	inline int32 getStrengthWounds() {
		return wounds[CreatureAttribute::STRENGTH];
	}

	inline int32 getConstitutionWounds() {
		return wounds[CreatureAttribute::CONSTITUTION];
	}

	inline int32 getActionWounds() {
		return wounds[CreatureAttribute::ACTION];
	}

	inline int32 getQuicknessWounds() {
		return wounds[CreatureAttribute::QUICKNESS];
	}

	inline int32 getStaminaWounds() {
		return wounds[CreatureAttribute::STAMINA];
	}

	inline int32 getMindWounds() {
		return wounds[CreatureAttribute::MIND];
	}

	inline int32 getFocusWounds() {
		return wounds[CreatureAttribute::FOCUS];
	}

	inline int32 getWillpowerWounds() {
		return wounds[CreatureAttribute::WILLPOWER];
	}

	inline int32 getHealthEncumbrance() {
		return encumbranceHealth;
	}

	inline int32 getActionEncumbrance() {
		return encumbranceAction;
	}

	inline int32 getMindEncumbrance() {
		return encumbranceMind;
	}

	inline uint32 getShockWounds() {
		return shockWounds;
	}

	//State Getters
	inline bool isInCombat() {
		return (statesBitmask & CreatureState::COMBAT);
	}

	inline bool isPeaced() {
		return (statesBitmask & CreatureState::PEACE);
	}

	inline bool isAiming() {
		return (statesBitmask & CreatureState::AIMING);
	}

	inline bool isMeditating() {
		return (statesBitmask & CreatureState::ALERT);
	}

	inline bool isBerserk() {
		return (statesBitmask & CreatureState::BERSERK);
	}

	inline bool isFeigningDeath() {
		return (statesBitmask & CreatureState::FEIGNDEATH);
	}

	inline bool isTumbling() {
		return (statesBitmask & CreatureState::TUMBLING);
	}

	inline bool isRallied() {
		return (statesBitmask & CreatureState::RALLIED);
	}

	inline bool isStunned() {
		return (statesBitmask & CreatureState::STUNNED);
	}

	inline bool isBlinded() {
		return (statesBitmask & CreatureState::BLINDED);
	}

	inline bool isDizzy() {
		return (statesBitmask & CreatureState::DIZZY);
	}

	inline bool isIntimidated() {
		return (statesBitmask & CreatureState::INTIMIDATED);
	}

	inline bool isSnared() {
		return (statesBitmask & CreatureState::SNARED);
	}

	inline bool isRooted() {
		return (statesBitmask & CreatureState::ROOTED);
	}

	inline bool isSwimming() {
		return (statesBitmask & CreatureState::SWIMMING);
	}

	inline bool isSittingOnChair() {
		return (statesBitmask & CreatureState::SITTINGONCHAIR);
	}

	inline bool isCrafting() {
		return (statesBitmask & CreatureState::CRAFTING);
	}

	inline bool isGlowingJedi() {
		return (statesBitmask & CreatureState::GLOWINGJEDI);
	}

	inline bool isMaskedScent() {
		return (statesBitmask & CreatureState::MASKSCENT);
	}

	inline bool isPoisoned() {
		return (statesBitmask & CreatureState::POISONED);
	}

	inline bool isBleeding() {
		return (statesBitmask & CreatureState::BLEEDING);
	}

	inline bool isDiseased() {
		return (statesBitmask & CreatureState::DISEASED);
	}

	inline bool isOnFire() {
		return (statesBitmask & CreatureState::ONFIRE);
	}

	inline bool isRidingMount() {
		return (statesBitmask & CreatureState::RIDINGMOUNT);
	}

	inline bool isOnMountedCreature() {
		return (statesBitmask & CreatureState::MOUNTEDCREATURE);
	}

	inline bool isGrouped() {
		return (groupObject != NULL);
	}

	//inline bool isInGroupWith(CreatureObject* creature);

	inline bool isGuilded() {
		return (guildObject != NULL);
	}

	//inline bool isInGuildWith(CreatureObject* creature);

	inline bool isStationary() {
		return stationary;
	}
};

#endif /*CREATUREOBJECTIMPLEMENTATION_H_*/
