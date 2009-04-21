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

#include "engine/engine.h"

//#include "../../packets.h"

#include "../../packets/creature/CreatureObjectDeltaMessage3.h"

#include "../scene/SceneObject.h"
#include "../scene/SceneObjectImplementation.h"

#include "../../objects/player/Races.h"
#include "../../objects/group/GroupObject.h"

#include "skills/Skill.h"
#include "../../managers/skills/SkillManager.h"
#include "skillmods/SkillModList.h"

#include "buffs/BuffList.h"
#include "buffs/BuffObject.h"

#include "CreatureAttribute.h"
#include "CreatureState.h"
#include "CreaturePosture.h"
#include "CreatureFlag.h"
#include "BuffAttribute.h"

#include "../guild/Guild.h"

#include "../../../chat/ChatManager.h"
#include "events/MaskScentEvent.h"
#include "skills/CamoSkill.h"

#include "dots/DamageOverTimeMap.h"

class CombatManager;
class MissionManager;

class Player;
//class Npc;

class Inventory;
class HairObject;
class TangibleObject;
class Weapon;
class Armor;
class Instrument;

class MountCreature;
class DizzyFallDownEvent;
class WoundTreatmentOverEvent;
class InjuryTreatmentOverEvent;
class StateTreatmentOverEvent;
class ConditionTreatmentOverEvent;
class BurstRunOverEvent;
class BurstRunNotifyAvailableEvent;

class MountCreature;
class BuildingObject;
class CreatureObjectServant;
class CreatureInventory;
class BankInventory;

class CreatureObjectImplementation : public CreatureObjectServant {
protected:
	String terrainName;

	String raceName; //species
	String gender;

	String hairObject; //hair object iff String
	CustomizationVariables hairCustomization;

	String creatureType;

	String meatType;
	String hideType;
	String boneType;
	int milk;
	int hideMax;
	int boneMax;
	int meatMax;
	int creatureHealth; // 1 = scrawny, 2 = skinny, 3 = medium, 4 = fat;

	String creatureFaction;

	int xp;

	int healer;

	int pack;
	int herd;
	int stalker;
	int killer;
	int aggressive;

	String behaviorScript;

	String creatureWeapon;
	String creatureWeaponName;
	String creatureWeaponTemp;
	String creatureWeaponClass;
	int creatureWeaponEquipped;
	int creatureWeaponMinDamage;
	int creatureWeaponMaxDamage;
	float creatureWeaponAttackSpeed;
	String creatureWeaponDamageType;
	String creatureWeaponArmorPiercing;

	float internalNPCDamageModifier;

	String lootGroup;

	float tame;


	uint32 positionCounter;
	uint32 actionCounter;

	VectorMap<uint32, Skill*> creatureSkills;
	Vector<String> skillsAndCertifications;
	uint32 creatureSkillsCount;

	//creature objects
	Inventory* inventory;
	CreatureInventory* lootContainer;
	BankInventory* bankContainer;
	HairObject* hairObj;

	Time lastCombatAction;

	Vector<BaseMessage*> broadcastBuffer;

	// Conversation
	// Option Responses. <screenID, "Left Box Text|Option1Text|O2|O3">
	VectorMap<String, String> convoScreens;
	// Conversation Option Links <"screenID,OptionNumber","nextScreenID">
	VectorMap<String, String> convoOptLink;

	// modifiers
	int weaponSpeedModifier;

	int centeredBonus;

	//CREO1 operands
	uint32 skillBoxesUpdateCounter;

	uint32 cashCredits;
	uint32 bankCredits;

 	//CREO3 operands
	uint8 postureState;

	uint64 stateBitmask;
	uint64 oldStateBitmask;

	MountCreature* mount;
	Time mountCooldown;

	uint64 creatureLinkID;

	uint64 timeOfDeath;

	Time knockdownRecoveryTime;
	Time dizzyRecoveryTime;
	Time stunRecoveryTime;
	Time blindRecoveryTime;
	Time intimidateRecoveryTime;
	Time rootRecoveryTime;
	Time snareRecoveryTime;
	Time berserkRecoveryTime;
	Time aimRecoveryTime;

	//Time fireRecoveryTime;
	//Time poisonRecoveryTime;
	//Time bleedingRecoveryTime;
	//Time diseasedRecoveryTime;

 	//CREO4 operands
	float speed;
	float acceleration;
	float height;
	SkillModList creatureSkillMods;
	SkillModList creatureSkillModBonus;
	BuffList creatureBuffs;

	uint32 skillModsCounter;
	String skillMod;

	uint32 skillModBonusCounter;

	//CREO6 operands

	//uint64 defenderID;

	String mood;
	String moodStr;
	uint8 moodid;

	Weapon* weaponObject;
	ManagedReference<SceneObject> targetObject;

	// HAM variables
	uint32 hamUpdateCounter;
	uint32 hamMaxUpdateCounter;
	uint32 hamBaseUpdateCounter;
	uint32 encumbUpdateCounter;
	uint32 woundsUpdateCounter;

	/**
	 * CREO1 HAM Values
	 * \param index Index is equal to definition in CreatureAttribute.
	 */
	int32 attributes[CreatureAttribute::ARRAYSIZE];
	int32 baseAttributes[CreatureAttribute::ARRAYSIZE];
	int32 maxAttributes[CreatureAttribute::ARRAYSIZE];
	int32 wounds[CreatureAttribute::ARRAYSIZE];

	int32 healthEncumbrance;
	int32 actionEncumbrance;
	int32 mindEncumbrance;

	// AKA Battle Fatigue
	uint32 shockWounds;

	// misc
	uint32 faction;
	uint8 factionRank;

	// combat
	/*int fireDotType;
	int fireDotStrength;

	int poisonDotType;
	int poisonDotStrength;

	int diseaseDotType;
	int diseaseDotStrength;

	int bleedingDotType;
	int bleedingDotStrength;

	Time nextBleedingTick;
	Time nextFireTick;
	Time nextPoisonTick;
	Time nextDiseaseTick;
*/
	Time knockdownRecovery;
	Time postureDownRecovery;
	Time postureUpRecovery;

	Time nextAttackDelay;
	Time nextAttackDelayRecovery;

	//Powerboost
	int pbHA;
	int pbMind;
	int pbTick;
	uint32 pbBonus;
	uint8 pbCounter;

	int accuracy;
	int accuracyBonus;

	int damageBonus;
	int defenseBonus;

	VectorMap<uint32, uint32> queuedStates; // TODO: make SortedVector for basic types

	BurstRunOverEvent* burstRunOverEvent;
	BurstRunNotifyAvailableEvent* burstRunNotifyAvailableEvent;
	DizzyFallDownEvent* dizzyFallDownEvent;

	VectorMap<CreatureObject*, uint32> damageMap;

	VectorMap<String, Time> cooldownMap;

	//group stuff
	uint64 groupId;
	uint64 groupInviteCount;
	uint64 groupInviterID;

	ManagedReference<GroupObject> group;

	// Entertainer stuff
	String performanceAnimation;
	uint32 performanceCounter;
	String performanceName;

	int instrumentID; // instrument + song

	bool doDancing;
	bool doPlayingMusic;
	bool doListening;
	bool doWatching;

	uint64 watchID;
	uint64 listenID;

	ManagedSortedVector<CreatureObject> listeners;
	ManagedSortedVector<CreatureObject> watchers;

	float danceBuffDuration; // track the duration
	float musicBuffDuration;

	float danceBuffStrength; // track the duration
	float musicBuffStrength;

	bool sittingOnObject;

	Guild* guild;

	uint32 lastMovementUpdateStamp;
	int ignoreMovementTests;
	Time lastServerMovementStamp;

	int level;

	//Medical Timers
	bool doWoundTreatment;
	bool doInjuryTreatment;
	bool doStateTreatment;
	bool doConditionTreatment;

	WoundTreatmentOverEvent* woundTreatmentEvent;
	InjuryTreatmentOverEvent* injuryTreatmentEvent;
	StateTreatmentOverEvent* stateTreatmentEvent;
	ConditionTreatmentOverEvent* conditionTreatmentEvent;

	bool frozen;
	String templateString;

	bool burstRunning;

	// mask scent
	uint32 camoType;
	MaskScentEvent* maskScentEvent;
	Time camoLock;
	uint32 maskScent;
	Player* camoXPTraget;

	int ferocity;
	bool baby;

	uint8 campMod;
	uint8 campAggro;
	uint8 petNumber;

	float combatRegenModifier;
	float peacedRegenModifier;

	DamageOverTimeMap* dotMap;

	uint16 berserkDamage;
	uint16 aimMod;
	uint64 aimTarget;

	bool escaping;
	Time escapeTime;
	Time escapeProtection;

public:
	static const float DEFAULT_SPEED = 5.376f;
	static const float DEFAULT_ACCELERATION = 1.549f;

	static const uint64 DEAD_TOO_LONG = 1800000; //30 minutes - How long can someone be dead and still be resuscitated in Miliseconds

public:
	CreatureObjectImplementation(uint64 oid);

	virtual ~CreatureObjectImplementation();

	// opdarand Update methods
	void doCombatAnimation(CreatureObject* defender, uint32 animcrc, uint8 hit = 0);
	void doAnimation(const String& anim);
	void doEmote(uint32 targetid, uint32 emoteid, bool showtext);
	void playEffect(const String& file, const String& aux = "");
	void showFlyText(const String& file, const String& aux, uint8 red, uint8 green, uint8 blue);
	void sendCombatSpam(CreatureObject* defender, TangibleObject* item, uint32 damage, const String& skill, bool areaSpam = true);
	void sendCombatSpamTrap(CreatureObject* defender, TangibleObject* item, uint32 damage, const String& skill, bool areaSpam = true);

	void setPosture(uint8 state, bool overrideDizzy = false, bool objectInteraction = false, float objX = 0, float objY = 0, float objZ = 0);

	void setCombatState();
	void clearCombatState(bool removeDefenders = true);

	bool setState(uint64 state);
	bool clearState(uint64 state);
	void updateStates();
	void updateDotStates(uint64 oldStates, uint64 newStates);
	void clearStates();
	void removeState(uint64 state);
	/// HAM Methods
	bool changeHAMBars(int32 health, int32 action, int32 mind, bool forcedChange = false);
	bool changeHAMWounds(int32 health, int32 action, int32 mind, bool forcedChange = false);
	void changeMaxHAMBars(int32 health, int32 action, int32 mind);

	bool changeAttributeBar(uint8 attribute, int32 value, bool forcedChange = false);
	bool changeHealthBar(int32 value, bool forcedChange = false);
	bool changeStrengthBar(int32 value, bool forcedChange = false);
	bool changeConstitutionBar(int32 value, bool forcedChange = false);
	bool changeActionBar(int32 value, bool forcedChange = false);
	bool changeQuicknessBar(int32 value, bool forcedChange = false);
	bool changeStaminaBar(int32 value, bool forcedChange = false);
	bool changeMindBar(int32 value, bool forcedChange = false);
	bool changeFocusBar(int32 value, bool forcedChange = false);
	bool changeWillpowerBar(int32 value, bool forcedChange = false);

	void changeMaxAttributeBar(uint8 attribute, int32 value, bool updateClient = true);
	void changeMaxHealthBar(int32 value, bool updateClient = true);
	void changeMaxStrengthBar(int32 value, bool updateClient = true);
	void changeMaxConstitutionBar(int32 value, bool updateClient = true);
	void changeMaxActionBar(int32 value, bool updateClient = true);
	void changeMaxQuicknessBar(int32 value, bool updateClient = true);
	void changeMaxStaminaBar(int32 value, bool updateClient = true);
	void changeMaxMindBar(int32 value, bool updateClient = true);
	void changeMaxFocusBar(int32 value, bool updateClient = true);
	void changeMaxWillpowerBar(int32 value, bool updateClient = true);

	bool changeWoundsBar(uint8 attribute, int32 value, bool forcedChange = false);
	bool changeHealthWoundsBar(int32 value, bool forcedChange = false);
	bool changeStrengthWoundsBar(int32 value, bool forcedChange = false);
	bool changeConstitutionWoundsBar(int32 value, bool forcedChange = false);
	bool changeActionWoundsBar(int32 value, bool forcedChange = false);
	bool changeQuicknessWoundsBar(int32 value, bool forcedChange = false);
	bool changeStaminaWoundsBar(int32 value, bool forcedChange = false);
	bool changeMindWoundsBar(int32 value, bool forcedChange = false);
	bool changeFocusWoundsBar(int32 value, bool forcedChange = false);
	bool changeWillpowerWoundsBar(int32 value, bool forcedChange = false);

	void setAttributeBar(uint8 attribute, int32 value);
	void setHealthBar(int32 value);
	void setStrengthBar(int32 value);
	void setConstitutionBar(int32 value);
	void setActionBar(int32 value);
	void setQuicknessBar(int32 value);
	void setStaminaBar(int32 value);
	void setMindBar(int32 value);
	void setFocusBar(int32 value);
	void setWillpowerBar(int32 value);

	void setBaseAttributeBar(uint8 attribute, int32 value, bool updateClient = true);
	void setBaseHealthBar(int32 value, bool updateClient = true);
	void setBaseStrengthBar(int32 value, bool updateClient = true);
	void setBaseConstitutionBar(int32 value, bool updateClient = true);
	void setBaseActionBar(int32 value, bool updateClient = true);
	void setBaseQuicknessBar(int32 value, bool updateClient = true);
	void setBaseStaminaBar(int32 value, bool updateClient = true);
	void setBaseMindBar(int32 value, bool updateClient = true);
	void setBaseFocusBar(int32 value, bool updateClient = true);
	void setBaseWillpowerBar(int32 value, bool updateClient = true);

	void setMaxAttributeBar(uint8 attribute, int32 value, bool updateClient = true);
	void setMaxHealthBar(int32 value, bool updateClient = true);
	void setMaxStrengthBar(int32 value, bool updateClient = true);
	void setMaxConstitutionBar(int32 value, bool updateClient = true);
	void setMaxActionBar(int32 value, bool updateClient = true);
	void setMaxQuicknessBar(int32 value, bool updateClient = true);
	void setMaxStaminaBar(int32 value, bool updateClient = true);
	void setMaxMindBar(int32 value, bool updateClient = true);
	void setMaxFocusBar(int32 value, bool updateClient = true);
	void setMaxWillpowerBar(int32 value, bool updateClient = true);

	void setWoundsBar(uint8 attribute, int32 value);
	void setHealthWoundsBar(int32 value);
	void setStrengthWoundsBar(int32 value);
	void setConstitutionWoundsBar(int32 value);
	void setActionWoundsBar(int32 value);
	void setQuicknessWoundsBar(int32 value);
	void setStaminaWoundsBar(int32 value);
	void setMindWoundsBar(int32 value);
	void setFocusWoundsBar(int32 value);
	void setWillpowerWoundsBar(int32 value);

	void changeConditionDamage(int amount);
	void setMaxCondition(int condition);

	void changeShockWounds(int bf);

	void resetHAMBars(bool doUpdateClient);

	void setMaxHAMBars(int32 health, int32 action, int32 mind);
	void setHAMBars(int32 health, int32 action, int32 mind);
	void setHAMWoundsBars(int32 health, int32 action, int32 mind);

	uint32 calculateAttributeRegenTick(uint8 attribute);

	void doMeditateHeals();
	void doMeditateWoundHeals();

	float calculateBFRatio();

	void activateBurstRun(bool bypassChecks = false);
	void deactivateBurstRun(bool bypassChecks = false);
	bool burstRunChecks();
	float calculateProneSpeedModifier();

	void updateTarget(uint64 targ);
	void updateTarget(SceneObject* targ);

	void clearTarget();

	void setDizziedState();
	void setStunnedState();
	void setBlindedState();
	void setIntimidatedState();
	void setSnaredState();
	void setRootedState();
	void setBerserkedState(uint32 duration);

	bool isTanoObjEquipped(TangibleObject* tano);

	bool setNextAttackDelay(int del);

	void setMeditateState();

	void doPowerboostTick(Player* player);
	void removePowerboost();

	void addDamage(CreatureObject* creature, uint32 damage);
	void removeFromDamageMap(CreatureObject* target);

	bool isLootOwner(CreatureObject* creature);
	CreatureObject* getLootOwner();

	virtual bool isAttackable();

	virtual void handleDeath() {
		setPosture(CreaturePosture::DEAD);
	}

	bool isAttackableBy(CreatureObject* creature);

	bool hasAttackDelay() {
		return !nextAttackDelay.isPast();
	}

	void clearAttackDelay() {
		nextAttackDelay.update();
	}

	void setRebel() {
		faction = String("rebel").hashCode();
	}

	void setImperial() {
		faction = String("imperial").hashCode();
	}

	void setNeutral() {
		faction = 0;
	}

	void setFaction(uint32 fac) {
		faction = fac;
	}

	void setLastMovementUpdateStamp(uint32 tme) {
		lastMovementUpdateStamp = tme;
	}

	void setIgnoreMovementTests(int times) {
		ignoreMovementTests = times;
	}

	void sendFactionStatusTo(Player* player, bool doTwoWay = false);

	int getCreatureSkillsSize() {
		return creatureSkills.size();
	}

	void addSkill(Skill* skill) {
		creatureSkills.put(skill->getNameCRC(), skill);
	}

	Skill* getSkill(const String& name) {
		return creatureSkills.get(name.hashCode());
	}

	Skill* getSkill(uint32 actionCRC) {
		return creatureSkills.get(actionCRC);
	}

	inline String& getSkill(int idx) {
		return creatureSkills.get(idx)->getSkillName();
	}

	inline String& getSkillOrCertification(int idx) {
		return skillsAndCertifications.get(idx);
	}

	inline int getSkillAndCertificationSize() {
		return skillsAndCertifications.size();
	}

	void removeSkill(Skill* skill) {
		creatureSkills.drop(skill->getNameCRC());

		for (int i = 0; i < skillsAndCertifications.size(); ++i) {
			if (skillsAndCertifications.get(i) == skill->getSkillName()) {
				skillsAndCertifications.remove(i);
				break;
			}
		}
	}

	bool hasSkill(uint32 skillCRC) {
		return creatureSkills.contains(skillCRC);
	}

	void addSkills(Vector<Skill*>& skills, bool updateClient);
	void removeSkills(Vector<Skill*>& skills, bool updateClient);

	inline uint32 getCreatureSkillsCount() {
		return creatureSkillsCount;
	}

	inline uint32 getNewCreatureSkillsCount(int cnt) {
		return creatureSkillsCount += cnt;
	}

	inline uint32 getDamage(CreatureObject* creature) {
		return damageMap.get(creature);
	}

	uint32 getMitigation(const String& mit);

	virtual void activateRecovery() {
	}

	void addCooldown(const String& key, int timeLimitInMilliseconds) {
		removeCooldown(key);

		Time newCooldown;
		newCooldown.addMiliTime(timeLimitInMilliseconds);
		cooldownMap.put(key, newCooldown);
	}

	void removeCooldown(const String& key) {
		if(cooldownMap.contains(key)) {
			Time cooldown = cooldownMap.get(key);
			cooldownMap.drop(key);
		}
	}

	bool containsCooldown(const String& key) {
		return cooldownMap.contains(key);
	}

	// Returns time in seconds
	// Returns 0 if no cooldown entry is found
	int getCooldownTimeRemaining(const String& key) {
		if(cooldownMap.contains(key)) {
			Time cooldownTime = cooldownMap.get(key);
			Time currentTime;

			return cooldownTime.getTime() - currentTime.getTime();
		}

		return 0;
	}

	bool hasCooldownExpired(const String& key) {
		if(cooldownMap.contains(key)) {
			Time cooldown = cooldownMap.get(key);
			if(!cooldown.isPast())
				return false;
		}

		return true;
	}

	// dots
	int addDotState(CreatureObject* attacker, uint64 dotID, uint64 dotType, uint32 str, uint8 type, uint32 duration, float potency,uint32 defense);
	void applyDots();
	bool healDot(uint64 dotType,int reduction);

	inline uint8 getLowestHAMAttribute() {
		uint8 attribute = CreatureAttribute::MIND;

		int health = getHealth();
		int action = getAction();
		int mind = getMind();

		if (health < action && health < mind)
			attribute = CreatureAttribute::HEALTH;
		else if (action < health && action < mind)
			attribute = CreatureAttribute::ACTION;

		return attribute;
	}

	inline bool isOnFullHealth() {
		return (getHealth() == getHealthMax() - getHealthWounds()) && (getAction() == getActionMax() - getActionWounds()) && (getMind() == getMindMax() - getMindWounds());
	}

	inline void setGroup(GroupObject* Group) {
		group = Group;
	}

	inline void removeGroup() {
		group = NULL;
	}

	inline bool isInAGroup() {
		return group != NULL;
	}

	inline bool isInGroupWith(CreatureObject* creature) {
		return (group != NULL && creature->getGroupID() == groupId);
	}

	inline uint64 getGroupID() {
		return groupId;
	}

	inline void setGroupID(uint64 gid) {
		groupId = gid;
	}

	inline bool isIncapacitated() {
		return postureState == CreaturePosture::INCAPACITATED;
	}

	inline bool isDead() {
		return postureState == CreaturePosture::DEAD;
	}

	inline bool isKnockedDown() {
		return postureState == CreaturePosture::KNOCKEDDOWN;
	}

	inline bool isKneeling() {
		return postureState == CreaturePosture::CROUCHED;
	}

	inline bool isProne() {
		return postureState == CreaturePosture::PRONE;
	}

	inline bool isStanding() {
		return postureState == CreaturePosture::UPRIGHT;
	}

	inline bool isSitting() {
		return postureState == CreaturePosture::SITTING;
	}

	inline bool isSkillAnimating() {
		return postureState == CreaturePosture::SKILLANIMATING;
	}

	inline bool isInCombat() {
		return stateBitmask & CreatureState::COMBAT;
	}

	inline bool isDizzied() {
		return stateBitmask & CreatureState::DIZZY;
	}

	inline bool isBerserked() {
		return stateBitmask & CreatureState::BERSERK;
	}

	inline bool isStunned() {
		return stateBitmask & CreatureState::STUNNED;
	}

	inline bool isBlinded() {
		return stateBitmask & CreatureState::BLINDED;
	}

	inline bool isIntimidated() {
		return stateBitmask & CreatureState::INTIMIDATED;
	}

	inline bool isSnared() {
		return stateBitmask & CreatureState::SNARED;
	}

	inline bool isRooted() {
		return stateBitmask & CreatureState::ROOTED;
	}

	inline bool isDiseased() {
		return stateBitmask & CreatureState::DISEASED;
	}

	inline bool isPoisoned() {
		return stateBitmask & CreatureState::POISONED;
	}

	inline bool isBleeding() {
		return stateBitmask & CreatureState::BLEEDING;
	}

	inline bool isOnFire() {
		return stateBitmask & CreatureState::ONFIRE;
	}

	inline bool isMounted() {
		return stateBitmask & CreatureState::RIDINGMOUNT;
	}

	inline bool isRidingCreature() {
		return stateBitmask & CreatureState::MOUNTEDCREATURE;
	}

	inline bool isPeaced() {
		return stateBitmask & CreatureState::PEACE;
	}

	inline bool isMeditating() {
		return stateBitmask & CreatureState::ALERT;
	}

	inline bool isBurstRunning() {
		return burstRunning;
	}

	inline bool isAiming() {
		return stateBitmask & CreatureState::AIMING;
	}

	inline bool isInCover() {
		return stateBitmask & CreatureState::COVER;
	}

	inline bool isCreature() {
		return creatureType == "ANIMAL";
	}

	inline bool isNPC() {
		return creatureType == "NPC";
	}

	//Future Creature Handler methods
	inline bool isPet() {
		return false;
	}

	// misc methods
	void updateKnockdownRecovery() {
		knockdownRecovery.update();
		knockdownRecovery.addMiliTime(30000);
	}

	bool checkKnockdownRecovery() {
		return knockdownRecovery.isPast();
	}

	void updatePostureDownRecovery() {
		postureDownRecovery.update();
		postureDownRecovery.addMiliTime(30000);
	}

	void updatePostureUpRecovery() {
		postureUpRecovery.update();
		postureUpRecovery.addMiliTime(30000);
	}

	bool checkPostureDownRecovery() {
		return postureDownRecovery.isPast();
	}

	bool checkPostureUpRecovery() {
		return postureUpRecovery.isPast();
	}

	// item methods

	void addInventoryItem(TangibleObject* item);
	void addInventoryResource(ResourceContainer* rcno);

	SceneObject* getInventoryItem(uint64 oid);

	void removeAllInventoryByMisoKey(String& mkey);
	TangibleObject* getItemByMisoKey(String& tma);

	void removeInventoryItem(SceneObject* item);
	void removeInventoryItem(uint64 oid);

	void addLootItem(TangibleObject* item);

	TangibleObject* getLootItem(uint64 oid);

	void removeLootItem(SceneObject* item);
	void removeLootItem(uint64 oid);

	// Entertainer methods
	void startDancing(const String& anim, bool changeDance = false);
	void startPlayingMusic(const String& anim, bool changeMusic = false);

	void stopDancing();
	void stopPlayingMusic();

	void startWatch(uint64 entid);
	void startListen(uint64 entid);
	void stopWatch(uint64 entid, bool doSendPackets = true, bool forced = false, bool doLock = true, bool outOfRange = false);
	void stopListen(uint64 entid, bool doSendPackets = true, bool forced = false, bool doLock = true, bool outOfRange = false);
	void activateEntertainerBuff(int performanceType);

	void doFlourish(const String& modifier = "");
	void addEntertainerFlourishBuff();
	// Rename to Tick Patron?
	void doEntertainerPatronEffects();
	void doPerformanceAction();

	bool isInBuilding();
	SceneObject* getBuilding();
	int getBuildingType();

	bool canGiveEntertainBuff();

	// Conversation Methods
	virtual void sendConversationStartTo(SceneObject* obj);
	virtual void selectConversationOption(int option, SceneObject* obj);
	virtual void sendConversationStopTo(SceneObject* obj);
	void addConvoScreen(const String& screenID, const String& leftBoxText, int numOptions, const String& Options, const String& optLinks);
	void sendConvoScreen(Player* player, const String& screenID);

	// guild methods
	void sendGuildTo();

	// mount methods
	void mountCreature(MountCreature* mnt, bool lockMount = true);
	void dismount(bool lockMount = true, bool ignoreCooldown = false);

	// buffing methods
	void addBuff(int buffCRC, float duration); // Mostly Debugging purposes
	//void applyBuff(const String& type, int value, float duration);
	void applyBuff(Buff *buff);
	void applyBuff(BuffObject *bo);
	//void removeBuff(const String& type, int value, Event* event);
	void removeBuff(const uint32 buffCRC, bool remove = true);


	void removeBuffs(bool doUpdateCreature = true);

	// cash transaction methods
	void addCashCredits(uint32 credits);
	void addBankCredits(uint32 credits);
	void updateCashCredits(uint32 credits);
	void updateBankCredits(uint32 credits);
	void subtractCashCredits(uint32 credits);
	void subtractBankCredits(uint32 credits);

	//BankStorage
	void addBankItem(TangibleObject* item);
	TangibleObject* getBankItem(uint64 oid);
	void removeBankItem(SceneObject* item);
	void removeBankItem(uint64 oid);

	inline bool verifyCashCredits(uint32 creditsToRemove) {
		return (getCashCredits() >= creditsToRemove);
	}

	inline bool verifyBankCredits(uint32 creditsToRemove) {
		return (getBankCredits() >= creditsToRemove);
	}

	// misc
	virtual uint64 getNewItemID() {
		return 0;
	}

	// client level methods
	void sendToOwner(Player* player, bool doClose = true);

	void sendTo(Player* player, bool doClose = true);

	void sendItemsTo(Player* player);

	void sendDestroyTo(Player* player);

	void broadcastMessageRange(Player* player, const String& message, float range);

	void sendSystemMessage(const String& message);
	void sendSystemMessage(UnicodeString& message);
	void sendSystemMessage(const String& file, const String& str, uint64 targetid = 0);

	void updateSpeed(float speed, float acceleration);

	void updateGroupId(uint64 id);
	void updateGroupInviterId(uint64 id);

	float getDistanceTo(SceneObject* targetCreature);

	void updateMood(const String& md);

	inline void updateServerMovementStamp() {
		lastServerMovementStamp.update();
	}

	inline uint64 getLastServerMovementStamp() {
		return lastServerMovementStamp.miliDifference();
	}

protected:
	void sendEntertainingUpdate(uint32 entval, const String& performance, uint32 perfcntr, int instrid);
	void sendEntertainmentUpdate(uint64 entid, const String& mood, bool updateEntVal = false);

public:
	// setters and getters
	void addSkillMod(const String& name, int mod, bool updateClient = false);
	void removeSkillMod(const String& name, bool updateClient = false);

	void addSkillModBonus(const String& name, int mod, bool updateClient = false);
	void removeSkillModBonus(const String& name, bool updateClient = false);

	bool hasQueuedState(uint32 skillCRC) {
		return queuedStates.contains(skillCRC);
	}

	bool removeQueuedState(uint32 skillCRC) {
		return queuedStates.drop(skillCRC);
	}

	bool addQueuedState(uint32 skillCRC) {
		return queuedStates.put(skillCRC, skillCRC);
	}

	SkillModList* getSkillModList() {
		return &creatureSkillMods;
	}

	SkillModList* getSkillModBonusList() {
		return &creatureSkillModBonus;
	}

	BuffList* getBuffsList() {
		return &creatureBuffs;
	}

	void setGroupInviterID(uint64 oid) {
		groupInviterID = oid;
	}

	int getSkillMod(const String& name) {
		// TODO: Add Buffs
		int bonus = creatureSkillModBonus.get(name);
		if (!(name == "burst_run") && !(name == "group_slope_move")) {
			if (bonus > 25)
				bonus = 25;
		}

		return creatureSkillMods.get(name) + bonus;
	}

	bool hasSkillMod(const String& name) {
		return creatureSkillMods.containsKey(name);
	}

	void removeSkillMod(String& name) {
		creatureSkillMods.remove(name);
	}

	Buff* getBuff(const uint32& buffCRC) {
		Buff *b = creatureBuffs.get(buffCRC);
		return b;
	}

	BuffObject* getBuffObject(const uint32& buffCRC) {
		BuffObject *bo = new BuffObject(creatureBuffs.get(buffCRC));
		return bo;
	}

	int getSkillModBonus(const String& name) {
		int bonus = creatureSkillModBonus.get(name);
		return bonus;
	}

	bool hasBuff(const uint32 buffCRC) {
		return creatureBuffs.contains(buffCRC);
	}

	bool hasSpice() {
		for (int i = 0; i < creatureBuffs.size(); i++)
		{
			Buff *buff = creatureBuffs.get(i);
			if (buff != NULL && buff->getBuffType() == BuffType::SPICE)
				return true;
		}
		return false;
	}

	bool hatesFaction(uint32 faction);

	bool hasSkillModBonus(const String& name) {
		return creatureSkillModBonus.containsKey(name);
	}

	void removeSkillModBonus(String& name) {
		creatureSkillModBonus.remove(name);
	}

	inline int getDamageBonus() {
		return damageBonus;
	}

	inline int getDefenseBonus() {
		return defenseBonus;
	}

	inline uint64 getGroupInviterID() {
		return groupInviterID;
	}

	inline uint64 getNewGroupInviteCounter() {
		return ++groupInviteCount;
	}

	inline uint64 getGroupInviteCounter() {
		return groupInviteCount;
	}

	inline int getConditionDamage() {
		return (int)conditionDamage;
	}

	inline int getMaxCondition() {
		return maxCondition;
	}

	inline int getCondition() {
		return (int)(maxCondition - conditionDamage);
	}

	inline int getCenteredBonus() {
		return centeredBonus;
	}

	inline uint64 getCreatureLinkID() {
		return creatureLinkID;
	}

	inline uint32 getLastMovementUpdateStamp() {
		return lastMovementUpdateStamp;
	}

	inline int getIgnoreMovementTests() {
		return ignoreMovementTests;
	}

	inline void setMount(MountCreature* mnt) {
		mount = mnt;
	}

	inline MountCreature* getMount() {
		return mount;
	}

	inline void setDamageBonus(int bonus) {
		damageBonus = bonus;
	}

	inline void setDefenseBonus(int bonus) {
		defenseBonus = bonus;
	}

	inline void setCreatureLinkID(uint64 creatureID) {
		creatureLinkID = creatureID;
	}

	inline void setCharacterName(const String& name) {
		customName = name;
	}

	inline void setCharacterName(const UnicodeString& name) {
		customName = name;
	}

	inline void setTerrainName(const String& name) {
		terrainName = name;
	}

	inline void setHairAppearance(const String& cust) {
		hairCustomization = cust;
	}


	inline void setHairAppearanceAttribute(uint8 type, uint8 value) {
		hairCustomization.setVariable(type, value);

		// TODO send packet update?
	}

	inline void setHairAppearanceAttribute(String type, uint8 value) {
		hairCustomization.setVariable(type, value);

		// TODO send packet update?
	}


	void updateCharacterAppearance();

	inline void setRaceName(const String& name) {
		raceName = name;
	}

	inline void setGender(const String& gend) {
		gender = gend;
	}

	inline void setCreatureType(const String& ctype) {
		creatureType = ctype;
	}

	inline void setHeight(float h) {
		height = h;
	}

	inline void setWeapon(Weapon* wep) {
		weaponObject = wep;
	}

	inline void setMood(uint8 mdid) {
		moodid = mdid;
		mood = Races::getMood(moodid);
		moodStr = Races::getMoodStr(mood);
	}

	inline void setMood(const String& m) {
		mood = m;
		moodStr = Races::getMoodStr(mood);
	}

	inline void setPvpStatusBitmask(uint32 mask) {
		pvpStatusBitmask = mask;
	}

	inline void setFactionRank(uint8 rank, bool updateClient = true) {
		factionRank = rank;

		if (updateClient) {
			CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3((CreatureObject*) _this);
			dcreo3->updateFactionRank();
			dcreo3->close();
			this->broadcastMessage(dcreo3);
		}
	}

	void updateHAMBars();

	void updateBaseStats();


	inline void setBaseAttribute(uint8 attribute, int32 value) {
		baseAttributes[attribute] = value;
	}

	inline void setBaseHealth(int32 value) {
		baseAttributes[CreatureAttribute::HEALTH] = value;
	}

	inline void setBaseStrength(int32 value) {
		baseAttributes[CreatureAttribute::STRENGTH] = value;
	}

	inline void setBaseConstitution(int32 value) {
		baseAttributes[CreatureAttribute::CONSTITUTION] = value;
	}

	inline void setBaseAction(int32 value) {
		baseAttributes[CreatureAttribute::ACTION] = value;
	}

	inline void setBaseQuickness(int32 value) {
		baseAttributes[CreatureAttribute::QUICKNESS] = value;
	}

	inline void setBaseStamina(int32 value) {
		baseAttributes[CreatureAttribute::STAMINA] = value;
	}

	inline void setBaseMind(int32 value) {
		baseAttributes[CreatureAttribute::MIND] = value;
	}

	inline void setBaseFocus(int32 value) {
		baseAttributes[CreatureAttribute::FOCUS] = value;
	}

	inline void setBaseWillpower(int32 value) {
		baseAttributes[CreatureAttribute::WILLPOWER] = value;
	}

	inline void setAttribute(uint8 attribute, int32 value) {
		attributes[attribute] = value;
	}

	inline void setHealth(int32 value) {
		attributes[CreatureAttribute::HEALTH] = value;
	}

	inline void setStrength(int32 value) {
		attributes[CreatureAttribute::STRENGTH] = value;
	}

	inline void setConstitution(int32 value) {
		attributes[CreatureAttribute::CONSTITUTION] = value;
	}

	inline void setAction(int32 value) {
		attributes[CreatureAttribute::ACTION] = value;
	}

	inline void setQuickness(int32 value) {
		attributes[CreatureAttribute::QUICKNESS] = value;
	}

	inline void setStamina(int32 value) {
		attributes[CreatureAttribute::STAMINA] = value;
	}

	inline void setMind(int32 value) {
		attributes[CreatureAttribute::MIND] = value;
	}

	inline void setFocus(int32 value) {
		attributes[CreatureAttribute::FOCUS] = value;
	}

	inline void setWillpower(int32 value) {
		attributes[CreatureAttribute::WILLPOWER] = value;
	}

	inline void changeAttribute(uint8 attribute, int32 value) {
		attributes[attribute] += value;
	}

	inline void changeHealth(int32 value) {
		attributes[CreatureAttribute::HEALTH] += value;
	}

	inline void changeStrength(int32 value) {
		attributes[CreatureAttribute::STRENGTH] += value;
	}

	inline void changeConstitution(int32 value) {
		attributes[CreatureAttribute::CONSTITUTION] += value;
	}

	inline void changeAction(int32 value) {
		attributes[CreatureAttribute::ACTION] += value;
	}

	inline void changeQuickness(int32 value) {
		attributes[CreatureAttribute::QUICKNESS] += value;
	}

	inline void changeStamina(int32 value) {
		attributes[CreatureAttribute::STAMINA] += value;
	}

	inline void changeMind(int32 value) {
		attributes[CreatureAttribute::MIND] += value;
	}

	inline void changeFocus(int32 value) {
		attributes[CreatureAttribute::FOCUS] += value;
	}

	inline void changeWillpower(int32 value) {
		attributes[CreatureAttribute::WILLPOWER] += value;
	}

	inline void setAttributeMax(uint8 attribute, int32 value) {
		maxAttributes[attribute] = value;
	}

	inline void setHealthMax(int32 value) {
		maxAttributes[CreatureAttribute::HEALTH] = value;
	}

	inline void setStrengthMax(int32 value) {
		maxAttributes[CreatureAttribute::STRENGTH] = value;
	}

	inline void setConstitutionMax(int32 value) {
		maxAttributes[CreatureAttribute::CONSTITUTION] = value;
	}

	inline void setActionMax(int32 value) {
		maxAttributes[CreatureAttribute::ACTION] = value;
	}

	inline void setQuicknessMax(int32 value) {
		maxAttributes[CreatureAttribute::QUICKNESS] = value;
	}

	inline void setStaminaMax(int32 value) {
		maxAttributes[CreatureAttribute::STAMINA] = value;
	}

	inline void setMindMax(int32 value) {
		maxAttributes[CreatureAttribute::MIND] = value;
	}

	inline void setFocusMax(int32 value) {
		maxAttributes[CreatureAttribute::FOCUS] = value;
	}

	inline void setWillpowerMax(int32 value) {
		maxAttributes[CreatureAttribute::WILLPOWER] = value;
	}

	inline void changeAttributeMax(uint8 attribute, int32 value) {
		maxAttributes[attribute] += value;
	}

	inline void changeHealthMax(int32 value) {
		maxAttributes[CreatureAttribute::HEALTH] += value;
	}

	inline void changeStrengthMax(int32 value) {
		maxAttributes[CreatureAttribute::STRENGTH] += value;
	}

	inline void changeConstitutionMax(int32 value) {
		maxAttributes[CreatureAttribute::CONSTITUTION] += value;
	}

	inline void changeActionMax(int32 value) {
		maxAttributes[CreatureAttribute::ACTION] += value;
	}

	inline void changeQuicknessMax(int32 value) {
		maxAttributes[CreatureAttribute::QUICKNESS] += value;
	}

	inline void changeStaminaMax(int32 value) {
		maxAttributes[CreatureAttribute::STAMINA] += value;
	}

	inline void changeMindMax(int32 value) {
		maxAttributes[CreatureAttribute::MIND] += value;
	}

	inline void changeFocusMax(int32 value) {
		maxAttributes[CreatureAttribute::FOCUS] += value;
	}

	inline void changeWillpowerMax(int32 value) {
		maxAttributes[CreatureAttribute::WILLPOWER] += value;
	}

	inline void setWounds(uint8 attribute, int32 value) {
		wounds[attribute] = value;
	}

	inline void setHealthWounds(int32 value) {
		wounds[CreatureAttribute::HEALTH] = value;
	}

	inline void setStrengthWounds(int32 value) {
		wounds[CreatureAttribute::STRENGTH] = value;
	}

	inline void setConstitutionWounds(int32 value) {
		wounds[CreatureAttribute::CONSTITUTION] = value;
	}

	inline void setActionWounds(int32 value) {
		wounds[CreatureAttribute::ACTION] = value;
	}

	inline void setQuicknessWounds(int32 value) {
		wounds[CreatureAttribute::QUICKNESS] = value;
	}

	inline void setStaminaWounds(int32 value) {
		wounds[CreatureAttribute::STAMINA] = value;
	}

	inline void setMindWounds(int32 value) {
		wounds[CreatureAttribute::MIND] = value;
	}

	inline void setFocusWounds(int32 value) {
		wounds[CreatureAttribute::FOCUS] = value;
	}

	inline void setWillpowerWounds(int32 value) {
		wounds[CreatureAttribute::WILLPOWER] = value;
	}

	inline void setShockWounds(uint32 wounds) {
		shockWounds = wounds;
	}

	inline void setWoundsUpdateCounter(uint32 count) {
		woundsUpdateCounter = count;
	}

	inline void setpbHA(int value) {
		pbHA = value;
	}

	inline void setpbMind(int value) {
		pbMind = value;
	}

	inline void setpbTick(int value) {
		pbTick = value;
	}

	inline void setpbBonus(uint32 value) {
		pbBonus = value;
	}

	inline void setSpeed(float spd) {
		speed = spd;
	}

	inline void setAcceleration(float acc) {
		acceleration = acc;
	}

	// getters
	inline int getpbHA() {
		return pbHA;
	}

	inline int getpbMind() {
		return pbMind;
	}

	inline int getpbTick() {
		return pbTick;
	}

	inline int getpbBonus() {
		return pbBonus;
	}

	inline UnicodeString& getCharacterName() {
		return customName;
	}

	inline String& getTerrainName() {
		return terrainName;
	}

	inline void getHairAppearance(String& appearance) {
		hairCustomization.toString(appearance);
		//appearance = customization;
	}


	inline String& getRaceName() {
		return raceName;
	}

	inline String& getGender() {
		return gender;
	}

	inline String& getCreatureType() {
		return creatureType;
	}

	inline uint32 getPositionCounter() {
		return positionCounter++;
	}

	inline uint32 getBankCredits() {
		return bankCredits;
	}

	inline uint32 getCashCredits() {
		return cashCredits;
	}

	inline SceneObject* getTarget() {
		return targetObject;
	}

	inline Weapon* getWeapon() {
		return weaponObject;
	}

	Instrument* getInstrument();
	int getInstrumentType();

	Armor* getArmor(int type);

	// HAM getters
	inline int32 getBaseAttribute(uint8 attribute) {
		return baseAttributes[attribute];
	}

	inline int32 getBaseHealth() {
		return baseAttributes[CreatureAttribute::HEALTH];
	}

	inline int32 getBaseStrength() {
		return baseAttributes[CreatureAttribute::STRENGTH];
	}

	inline int32 getBaseConstitution() {
		return baseAttributes[CreatureAttribute::CONSTITUTION];
	}

	inline int32 getBaseAction() {
		return baseAttributes[CreatureAttribute::ACTION];
	}

	inline int32 getBaseQuickness() {
		return baseAttributes[CreatureAttribute::QUICKNESS];
	}

	inline int32 getBaseStamina() {
		return baseAttributes[CreatureAttribute::STAMINA];
	}

	inline int32 getBaseMind() {
		return baseAttributes[CreatureAttribute::MIND];
	}

	inline int32 getBaseFocus() {
		return baseAttributes[CreatureAttribute::FOCUS];
	}

	inline int32 getBaseWillpower() {
		return baseAttributes[CreatureAttribute::WILLPOWER];
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

	inline int32 getAttributeMax(uint8 attribute) {
		return maxAttributes[attribute];
	}

	inline int32 getHealthMax() {
		return maxAttributes[CreatureAttribute::HEALTH];
	}

	inline int32 getStrengthMax() {
		return maxAttributes[CreatureAttribute::STRENGTH];
	}

	inline int32 getConstitutionMax() {
		return maxAttributes[CreatureAttribute::CONSTITUTION];
	}

	inline int32 getActionMax() {
		return maxAttributes[CreatureAttribute::ACTION];
	}

	inline int32 getQuicknessMax() {
		return maxAttributes[CreatureAttribute::QUICKNESS];
	}

	inline int32 getStaminaMax() {
		return maxAttributes[CreatureAttribute::STAMINA];
	}

	inline int32 getMindMax() {
		return maxAttributes[CreatureAttribute::MIND];
	}

	inline int32 getFocusMax() {
		return maxAttributes[CreatureAttribute::FOCUS];
	}

	inline int32 getWillpowerMax() {
		return maxAttributes[CreatureAttribute::WILLPOWER];
	}

	inline int32 getWounds(uint8 attribute) {
		return wounds[attribute];
	}

	inline uint8 getWoundsArraySize() {
		return CreatureAttribute::ARRAYSIZE;
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

	inline int32 getAttributeDamage(uint8 attribute) {
		return getAttributeMax(attribute) - getWounds(attribute) - getAttribute(attribute);
	}

	inline int32 getHealthDamage() {
		return getHealthMax() - getHealthWounds() - getHealth();
	}

	inline int32 getActionDamage() {
		return getActionMax() - getActionWounds() - getAction();
	}

	inline int32 getMindDamage() {
		return getMindMax() - getMindWounds() - getMind();
	}

	inline uint32 getShockWounds() {
		return shockWounds;
	}

	inline uint32 getHAMUpdateCounter() {
		return hamUpdateCounter;
	}

	inline uint32 getNewHAMUpdateCounter(int cnt) {
			return hamUpdateCounter += cnt;
	}

	inline uint32 getHAMMaxUpdateCounter() {
		return hamMaxUpdateCounter;
	}

	inline uint32 getNewHAMMaxUpdateCounter(int cnt) {
			return hamMaxUpdateCounter += cnt;
	}

	inline uint32 getHAMBaseUpdateCounter() {
		return hamBaseUpdateCounter;
	}

	inline uint32 getNewHAMBaseUpdateCounter(int cnt) {
			return hamBaseUpdateCounter += cnt;
	}

	inline uint32 getEncumbUpdateCounter() {
		return encumbUpdateCounter;
	}

	inline uint32 getNewEncumbUpdateCounter(int cnt) {
		return encumbUpdateCounter += cnt;
	}

	inline uint32 getWoundsUpdateCounter() {
		return woundsUpdateCounter;
	}

	inline uint32 getNewWoundsUpdateCounter(int upd) {
		return woundsUpdateCounter += upd;
	}

	inline uint8 getPosture() {
		return postureState;
	}

	inline String& getMood() {
		return mood;
	}

	inline String& getMoodStr() {
		return moodStr;
	}

	inline uint8 getMoodID() {
		return moodid;
	}

	inline uint64 getStateBitmask() {
		return stateBitmask;
	}

	inline float getHeight() {
		return height;
	}

	inline bool hasStates() {
		return stateBitmask != 0;
	}

	inline bool hasWounds(bool h = true, bool a = true, bool m = true) {
		if (h) {
			if (getHealthWounds() > 0 || getStrengthWounds() > 0 || getConstitutionWounds() > 0)
				return true;
		}
		if (1) {
			if (getActionWounds() > 0 || getQuicknessWounds() > 0 || getStaminaWounds() > 0)
				return true;
		}
		if (m) {
			if (getMindWounds() > 0 || getFocusWounds() > 0 || getWillpowerWounds() > 0)
				return true;
		}

		return false;
	}

	inline bool hasWound(uint8 attribute) {
		return (getWounds(attribute) > 0);
	}

	/**
	 * Gets the next wounded attribute in order.
	 * \param health Include health wound attributes
	 * \param action Include action wound attributes
	 * \param mind Include mind wound attributes
	 * \return Returns the next wounded attribute.
	 */
	inline uint8 getNextWoundedAttribute(bool health = true, bool action = true, bool mind = true) {
		int woundCount = 0;

		if (health) {
			for (uint8 i = CreatureAttribute::HEALTH; i < CreatureAttribute::ACTION; i++) {
				if (hasWound(i))
					return i;
			}
		}

		if (action) {
			for (uint8 i = CreatureAttribute::ACTION; i < CreatureAttribute::MIND; i++) {
				if (hasWound(i))
					return i;
			}
		}

		if (mind) {
			for (uint8 i = CreatureAttribute::MIND; i < CreatureAttribute::UNKNOWN; i++) {
				if (hasWound(i))
					return i;
			}
		}

		return CreatureAttribute::UNKNOWN;
	}

	/**
	 * Gets a wounded attribute by random.
	 * \return Returns the randomly selected wounded attribute.
	 */
	inline uint8 getRandomWoundedAttribute(bool health = true, bool action = true, bool mind = true, bool strength = true, bool constitution = true, bool quickness = true, bool stamina = true, bool focus = true, bool willpower = true) {
		Vector<uint8> woundedAttributes;

		if (health) {
			for (int i = CreatureAttribute::HEALTH; i < CreatureAttribute::ACTION; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		if (action) {
			for (int i = CreatureAttribute::ACTION; i < CreatureAttribute::MIND; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		if (mind) {
			for (int i = CreatureAttribute::MIND; i < CreatureAttribute::UNKNOWN; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		if (strength) {
			for (int i = CreatureAttribute::STRENGTH; i < CreatureAttribute::UNKNOWN; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		if (constitution) {
			for (int i = CreatureAttribute::CONSTITUTION; i < CreatureAttribute::UNKNOWN; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		if (quickness) {
			for (int i = CreatureAttribute::QUICKNESS; i < CreatureAttribute::UNKNOWN; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		if (stamina) {
			for (int i = CreatureAttribute::STAMINA; i < CreatureAttribute::UNKNOWN; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		if (focus) {
			for (int i = CreatureAttribute::FOCUS; i < CreatureAttribute::UNKNOWN; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		if (willpower) {
			for (int i = CreatureAttribute::WILLPOWER; i < CreatureAttribute::UNKNOWN; i++) {
				if (hasWound(i))
					woundedAttributes.add(i);
			}
		}

		uint8 size = woundedAttributes.size();

		if (size > 0)
			return woundedAttributes.elementAt(System::random(size - 1));
		else
			return CreatureAttribute::UNKNOWN;
	}

	inline bool isResuscitable() {
		return (isDead() && (Time().getMiliTime() - timeOfDeath) < DEAD_TOO_LONG);
	}

	inline void setTimeOfDeath(uint64 mtime) {
		timeOfDeath = mtime;
	}

	inline uint64 getTimeOfDeath() {
		return timeOfDeath;
	}

	inline bool hasHealthDamage() {
		return (getHealthDamage() > 0);
	}

	inline bool hasActionDamage() {
		return (getActionDamage() > 0);
	}

	inline bool hasMindDamage() {
		return (getMindDamage() > 0);
	}

	inline bool hasDamage() {
		return (hasHealthDamage() || hasActionDamage() || hasMindDamage());
	}

	inline bool hasShockWounds() {
		return (shockWounds > 0);
	}

	inline bool hasState(uint64 state) {
		return stateBitmask & state;
	}

	inline int getAccuracy() {
		return accuracy;
	}

	inline int getAccuracyBonus() {
		return accuracyBonus;
	}

	inline float getSpeed() {
		return speed;
	}

	inline float getAcceleration() {
		return acceleration;
	}

	inline bool isOvert() {
		return pvpStatusBitmask & CreatureFlag::OVERT;
	}

	inline bool isAgressive() {
		return pvpStatusBitmask & CreatureFlag::AGGRESSIVE;
	}

	inline bool isTEF() {
		return pvpStatusBitmask & CreatureFlag::TEF;
	}

	inline bool isPlayerFlag() {
		return pvpStatusBitmask & CreatureFlag::PLAYER;
	}

	inline bool isEnemy() {
		return pvpStatusBitmask & CreatureFlag::ENEMY;
	}

	inline uint32 getFaction() {
		return faction;
	}

	inline bool isRebel() {
		return faction == String("rebel").hashCode();
	}

	inline bool isNeutral() {
		return faction == 0;
	}

	inline bool isImperial() {
		return faction == String("imperial").hashCode();
	}

	inline uint32 getPvpStatusBitmask() {
		return pvpStatusBitmask;
	}

	inline uint8 getFactionRank() {
		return factionRank;
	}

	uint64 getTargetID();

	uint64 getWeaponID();

	inline uint32 getNewSkillModsCounter(int cnt) {
		return skillModsCounter += cnt;
	}

	inline uint32 getSkillModsCounter() {
		return skillModsCounter;
	}

	inline uint32 getNewSkillModBonusCounter(int cnt) {
		return skillModBonusCounter += cnt;
	}

	inline uint32 getSkillModBonusCounter() {
		return skillModBonusCounter;
	}

	inline uint32 getLevel() {
		return level;
	}

	inline int32 getHealthEncumbrance() {
		return healthEncumbrance;
	}

	inline int32 getActionEncumbrance() {
		return actionEncumbrance;
	}

	inline int32 getMindEncumbrance() {
		return mindEncumbrance;
	}

	inline String& getCreatureFaction() {
		return creatureFaction;
	}

	inline int getXP() {
		return xp;
	}

	inline int isHealer() {
		return healer;
	}

	inline int isPack() {
		return pack;
	}

	inline int isHerd() {
		return herd;
	}

	inline int isKiller() {
		return killer;
	}

	inline int isStalker() {
		return stalker;
	}

	inline int isAggressive() {
		return aggressive;
	}

	inline String& getBehaviorScript() {
		return behaviorScript;
	}


	//Harvesting stuff
	inline String& getMeatType() {
		return meatType;
	}

	inline String& getBoneType() {
		return boneType;
	}

	inline String& getHideType() {
		return hideType;
	}

	inline bool hasOrganics(){
		return ((hideMax + boneMax + meatMax) > 0);
	}

	inline int getMilk() {
		return milk;
	}

	inline int getHideMax() {
		return hideMax;
	}

	inline int getBoneMax() {
		return boneMax;
	}

	inline int getMeatMax() {
		return meatMax;
	}

	inline int getCreatureHealth() {
		return creatureHealth;
	}

	inline String& getLootGroup() {
		return lootGroup;
	}

	inline float getTame() {
		return tame;
	}

	//combat related

	inline float getInternalNPCDamageModifier() {
		return internalNPCDamageModifier;
	}

	inline String& getCreatureWeapon() {
		return creatureWeapon;
	}
	inline String& getCreatureWeaponName() {
		return creatureWeaponName;
	}
	inline String& getCreatureWeaponClass() {
		return creatureWeaponClass;
	}
	inline String& getCreatureWeaponTemp() {
		return creatureWeaponTemp;
	}
	inline int getCreatureWeaponEquipped() {
		return creatureWeaponEquipped;
	}
	inline int getCreatureWeaponMinDamage() {
		return creatureWeaponMinDamage;
	}
	inline int getCreatureWeaponMaxDamage() {
		return creatureWeaponMaxDamage;
	}
	inline float getCreatureWeaponAttackSpeed() {
		return creatureWeaponAttackSpeed;
	}
	inline String& getCreatureWeaponDamageType() {
		return creatureWeaponDamageType;
	}
	inline String& getCreatureWeaponArmorPiercing() {
		return creatureWeaponArmorPiercing;
	}

	//behavior
	inline String& getCreatureBehaviorScript() {
		return behaviorScript;
	}

	// modifiers
	inline int getWeaponSpeedModifier() {
		return weaponSpeedModifier;
	}

	inline Inventory* getInventory() {
		return inventory;
	}

	inline Container* getLootContainer() {
		return (Container*)lootContainer;
	}

	inline Container* getBankContainer() {
		return (Container*)bankContainer;
	}

	inline BankInventory* getBankInventory() {
		return bankContainer;
	}

	// entertainer
	inline void addListener(CreatureObject* creature) {
		listeners.put(creature);
	}

	inline void addWatcher(CreatureObject* creature) {
		watchers.put(creature);
	}

	inline void removeListener(CreatureObject* creature) {
		listeners.drop(creature);
		/*if (!listeners.drop(creature)); {
			System::out << "SortedVector ERROR: object " << creature << " not found\n";

			for (int i = 0; i < listeners.size(); ++i) {
				CreatureObject* obj = listeners.get(i);
				System::out << obj << "(0x" << obj->getObjectID() << ") ";
			}

			System::out << "\n";
		}*/
	}

	inline void removeWatcher(CreatureObject* creature) {
		watchers.drop(creature);
		/*if (!watchers.drop(creature)); {
			System::out << "SortedVector ERROR: object " << creature << " not found\n";

			for (int i = 0; i < watchers.size(); ++i) {
				CreatureObject* obj = watchers.get(i);
				System::out << obj << "(0x" << obj->getObjectID() << ") ";
			}

			System::out << "\n";
		}*/
	}

	inline String& getPerformanceAnimation() {
		return performanceAnimation;
	}

	inline uint32 getPerformanceCounter() {
		return performanceCounter;
	}

	inline int getInstrumentID() {
		return instrumentID;
	}

	inline String& getPerformanceName() {
		return performanceName;
	}

	inline uint32 getSkillBoxesUpdateCounter() {
		return skillBoxesUpdateCounter++;
	}

	inline void setAccuracy(int acc) {
		accuracy = acc;
	}

	inline void setAccuracyBonus(int accBonus) {
		accuracyBonus = accBonus;
	}

	//Harvesting stuff
	inline void setMeatType(const String& meat) {
		meatType = meat;
	}

	inline void setBoneType(const String& bone) {
		boneType = bone;
	}

	inline void setHideType(const String& hide) {
		hideType = hide;
	}

	inline void setMilk(int milkamt) {
		milk = milkamt;
	}

	inline void setHideMax(int hidemax) {
		hideMax = hidemax;
	}

	inline void setBoneMax(int bonemax) {
		boneMax = bonemax;
	}

	inline void setMeatMax(int meatmax) {
		meatMax = meatmax;
	}

	inline void setLootGroup(const String& lootgroup) {
		lootGroup = lootgroup;
	}

	inline void setTame(float tme) {
		tame = tme;
	}

	//Combat & Weapon
	inline void setInternalNPCDamageModifier(float indm) {
		internalNPCDamageModifier = indm;
	}

	inline void setCreatureWeapon(const String& wpon) {
		creatureWeapon = wpon;
	}

	inline void setCreatureWeaponName(const String& weaponname) {
		creatureWeaponName = weaponname;
	}

	inline void setCreatureWeaponTemp(const String& weapontemp) {
		creatureWeaponTemp = weapontemp;
	}

	inline void setCreatureWeaponClass(const String& weaponclass) {
		creatureWeaponClass = weaponclass;
	}

	inline void setCreatureWeaponEquipped(int weaponeq) {
		creatureWeaponEquipped = weaponeq;
	}

	inline void setCreatureWeaponMinDamage(int weaponmindam) {
		creatureWeaponMinDamage = weaponmindam;
	}

	inline void setCreatureWeaponMaxDamage(int weaponmaxdam) {
		creatureWeaponMaxDamage = weaponmaxdam;
	}

	inline void setCreatureWeaponAttackSpeed(float weaponattackspeed) {
		creatureWeaponAttackSpeed = weaponattackspeed;
	}

	inline void setCreatureWeaponDamageType(const String& weapondamtype) {
		creatureWeaponDamageType = weapondamtype;
	}

	inline void setCreatureWeaponArmorPiercing(const String& weaponarmorpiercing) {
		creatureWeaponArmorPiercing = weaponarmorpiercing;
	}

	inline void setBehaviorScript(const String& behaviorscript) {
		behaviorScript = behaviorscript;
	}

	inline void setCreatureFaction(const String& cfac) {
		creatureFaction = cfac;
	}

	inline void setXP(int xxp) {
		xp = xxp;
	}

	inline void setHealer(int heale) {
		healer = heale;
	}

	inline void setPack(int pck) {
		pack = pck;
	}

	inline void setHerd(int hrd) {
		herd = hrd;
	}

	inline void setStalker(int stlker) {
		stalker = stlker;
	}

	inline void setKiller(int kller) {
		killer = kller;
	}

	inline void setAggressive(int agg) {
		aggressive = agg;
	}

	//Entertainer
	inline void addEntertainerBuffDuration(int performanceType, float duration) {
		switch(performanceType) {
		case PerformanceType::DANCE:
			danceBuffDuration += duration;
			if (danceBuffDuration > (120.0f + (10.0f/60.0f)) ) // 2 hrs 10 seconds
				danceBuffDuration = (120.0f + (10.0f/60.0f)); // 2hrs 10 seconds
			break;
		case PerformanceType::MUSIC:
			musicBuffDuration += duration;
			if (musicBuffDuration > (120.0f + (10.0f/60.0f)) ) // 2 hrs 10 seconds
				musicBuffDuration = (120.0f + (10.0f/60.0f)); // 2hrs 10 seconds
			break;
		}
	}

	inline void addEntertainerBuffStrength(int performanceType, float strength) {
		switch(performanceType) {
		case PerformanceType::DANCE:
			danceBuffStrength += strength;
			if (danceBuffStrength > 125.0f)
				danceBuffStrength = 125.0f; // 125% cap
			break;
		case PerformanceType::MUSIC:
			musicBuffStrength += strength;
			if (musicBuffStrength > 125.0f)
				musicBuffStrength = 125.0f; // 125% cap
			break;
		}
	}
	inline void setEntertainerBuffDuration(int performanceType, float duration) {
		switch(performanceType) {
		case PerformanceType::DANCE:
			danceBuffDuration = duration;
			break;
		case PerformanceType::MUSIC:
			musicBuffDuration = duration;
			break;
		}
	}

	inline void setEntertainerBuffStrength(int performanceType, float strength) {
		switch(performanceType) {
		case PerformanceType::DANCE:
			danceBuffStrength = strength;
			break;
		case PerformanceType::MUSIC:
			musicBuffStrength = strength;
			break;
		}
	}

	inline float getEntertainerBuffDuration(int performanceType) {
		switch(performanceType) {
		case PerformanceType::DANCE:
			return danceBuffDuration;
			break;
		case PerformanceType::MUSIC:
			return musicBuffDuration;
			break;
		}
		return 0.0f;
	}

	inline float getEntertainerBuffStrength(int performanceType) {
		switch(performanceType) {
		case PerformanceType::DANCE:
			return danceBuffStrength;
			break;
		case PerformanceType::MUSIC:
			return musicBuffStrength;
			break;
		}
		return 0.0f;
	}

	inline void setPerformanceAnimation(const String& performanceanimation) {
		performanceAnimation = performanceanimation;
	}

	inline void setPerformanceCounter(uint32 performancecounter) {
		performanceCounter = performancecounter;
	}

	inline void setInstrumentID(int value) {
		instrumentID = value;
	}

	inline void setPerformanceName(const String& performancename) {
		performanceName = performancename;
	}

	inline void setDancing(bool value) {
		doDancing = value;
	}

	inline void setPlayingMusic(bool value) {
		doPlayingMusic = value;
	}

	inline bool isDancing() {
		return doDancing;
	}

	inline bool isPlayingMusic() {
		return doPlayingMusic;
	}

	inline void setWatchID(uint64 oid) {
		watchID = oid;
	}

	inline void setListenID(uint64 oid) {
		listenID = oid;
	}

	inline void setWatching(bool value) {
		doWatching = value;
	}

	inline void setListening(bool value) {
		doListening = value;
	}

	inline bool isWatching() {
		return doWatching;
	}

	inline bool isListening() {
		return doListening;
	}

	inline uint64 getWatchID() {
		return watchID;
	}

	inline uint64 getListenID() {
		return listenID;
	}

	inline bool isSittingOnObject() {
		return sittingOnObject;
	}

	inline void setSittingOnObject(bool value) {
		sittingOnObject = value;
	}

	inline void setGuild(Guild* gld) {
		guild = gld;
	}

	inline void setActionCounter(uint32 actioncntr) {
		actionCounter = actioncntr;
	}

	inline void setLevel(uint32 lvl) {
		level = lvl;
	}

	inline void setHealthEncumbrance(int32 value) {
		healthEncumbrance = value;
	}

	inline void setActionEncumbrance(int32 value) {
		actionEncumbrance = value;
	}

	inline void setMindEncumbrance(int32 value) {
		mindEncumbrance = value;
	}

	inline void changeHealthEncumbrance(int32 value) {
		healthEncumbrance += value;
	}

	inline void changeActionEncumbrance(int32 value) {
		actionEncumbrance += value;
	}

	inline void changeMindEncumbrance(int32 value) {
		mindEncumbrance += value;
	}

	inline uint32 getActionCounter() {
		return actionCounter;
	}

	inline Guild* getGuild() {
		return guild;
	}

	inline uint32 getGuildID() {
		if (guild != NULL)
			return guild->getGuildID();
		else
			return 0;
	}

	inline String& getGuildName() {
		return guild->getGuildName();
	}

	inline bool isGuilded() {
		return guild != NULL;
	}

	inline void setCashCredits(int credits) {
		cashCredits = credits;
	}

	inline void setBankCredits(int credits) {
		bankCredits = credits;
	}

	inline float getTerrainNegotiation() {
		return (float(getSkillMod("slope_move"))/float(100));
	}

	void explode(int level = 1, bool destroy = true);

	// Medic & Doctor
	bool curePoison(CreatureObject* target, float effectiveness);
	bool cureDisease(CreatureObject* target, float effectiveness);
	bool extinguishFire(CreatureObject* target, float effectiveness);
	bool healState(CreatureObject* target, uint64 state);

	void deactivateWoundTreatment();
	void activateWoundTreatment();

	void deactivateInjuryTreatment(bool isRangedStim);
	void activateInjuryTreatment();

	void deactivateStateTreatment();
	void activateStateTreatment();

	void deactivateConditionTreatment();
	void activateConditionTreatment();

	bool canTreatWounds() {
		return doWoundTreatment;
	}

	bool canTreatInjuries() {
		return doInjuryTreatment;
	}

	bool canTreatStates() {
		return doStateTreatment;
	}

	bool canTreatConditions() {
		return doConditionTreatment;
	}

	int getMedicalFacilityRating();

	inline void say(const UnicodeString& message, uint32 moodid = 0, uint32 mood2 = 0) {
		ChatManager * chatManager = this->getZone()->getChatManager();
		chatManager->broadcastMessage(_this, message, this->getTargetID(),moodid, mood2);
	}

	inline void say(const String& file, const String& str, StfParameter * param, uint32 moodid = 0, uint32 mood2 = 0) {
		ChatManager * chatManager = this->getZone()->getChatManager();
		chatManager->broadcastMessage(_this, file, str, param, this->getTargetID(),moodid, mood2);
	}

	inline bool isFrozen() {
		return frozen;
	}

	inline void setFrozen(bool flag) {
		frozen = flag;
	}

	inline String& getTemplateString() {
		return templateString;
	}

	inline void setTemplateString(const String& tmpString) {
		templateString = tmpString;
	}

	void setCamoType(unsigned int cType) {
		camoType = cType;
	}

	uint32 getCamoType() {
		if ((int)camoType < 0)
			return CamoSkill::NONE;
		else
			return camoType;
	}

	void activateCamo(unsigned int camoCRC,unsigned int time,unsigned int ms);
	void deactivateCamo(bool forced);
	void activateCamoLock();
	bool isCamoCooldownActive();
	int getCamoCooldownLeft();

	int getMaskScent() {
		return maskScent;
	}

	void setMaskScent(int value) {
		maskScent = value;
	}


	inline void clearTemplateString() {
		templateString = "";
	}

	void setFerocity(unsigned int fero) {
		ferocity = fero;
	}

	unsigned int getFerocity() {
		return ferocity;
	}

	void setBaby(bool b) {
		baby = b;
	}

	bool isBaby() {
		return baby;
	}

	Player* getCamoXPTraget() {
		return camoXPTraget;
	}

	void setCamoXPTraget(Player* xpTaget) {
		camoXPTraget = xpTaget;
	}

	void setCampModifier(int mod) {
		campMod = mod;
	}
	int getCampModifier() {
		return campMod;
	}

	bool isInCamp() {
		return campMod > 1;
	}

	void setNumberOfPets(int num) {
		petNumber = num;
	}
	int getNumberOfPets() {
		return petNumber;
	}




	//Event Handlers
	virtual void onIncapacitated(SceneObject* attacker);
	virtual void onIncapacitationRecovery();
	virtual void onConverse(Player* player);
	virtual void onDeath();
	virtual void onKilled(SceneObject* killer);
	virtual void onResuscitated(SceneObject* healer);
	virtual void onDamageHealed(SceneObject* healer, uint8 attribute, uint32 amount);
	virtual void onWoundHealed(SceneObject* healer, uint8 attribute, uint32 amount);
	virtual void onHealEnhanced(SceneObject* enhancer, uint8 attribute, uint32 amount, float duration);
	virtual void onBlinded();
	virtual void onDizzied();
	virtual void onStunned();
	virtual void onIntimidated();
	virtual void onEquip(TangibleObject* item);
	virtual void onUnequip(TangibleObject* item);
	virtual void onChangeWeapon(Weapon* weapon);
	virtual void onChangeArmor(Armor* armor);
	//virtual void onChangeClothing(Wearable* clothing);
	virtual void onReceiveDamage(SceneObject* attacker, uint8 attribute, uint32 amount);
	virtual void onRegenerateHAM();

	//Actions
	virtual bool inflictDamage(CreatureObject* victim, uint8 attribute, uint32 damage);
	virtual void incapacitateSelf();
	virtual void recoverFromIncapacitation();
	virtual void die();
	virtual void equipItem(TangibleObject* item);
	virtual void unequipItem(TangibleObject* item);


	//Setters
	inline void setCombatRegenModifier(float value) {
		combatRegenModifier = value;
	}

	inline void setPeacedRegenModifier(float value) {
		peacedRegenModifier = value;
	}

	//Getters
	inline bool canRecoverFromIncapacitation() {
		return (!isDead() && isIncapacitated() && getHealth() > 0 && getAction() > 0 && getMind() > 0);
	}

	inline float getCombatRegenModifier() {
		return combatRegenModifier;
	}

	inline float getPeacedRegenModifier() {
		return peacedRegenModifier;
	}

	inline uint8 getCampAggroMod() {
		return campAggro;
	}

	inline void setCampAggroMod(uint8 mod) {
		campAggro = mod;
	}
	void setBerserkDamage(uint16 damage) {
		berserkDamage = damage;
	}
	uint16 getBerserkDamage() {
		return berserkDamage;
	}

	inline uint16 getAimMod() {
		return aimMod;
	}

	inline void setAimMod(uint16 mod) {
		aimMod = mod;
	}

	void setAimingState();
	void setCoverState();
	void resetMovementSpeed();

	inline bool isEscaping() {
		return escaping;
	}

	inline void setEscaping(bool escape) {
		escaping = escape;
	}

	void activateEscape();
	void deactivateEscape();

	friend class CombatManager;
	friend class SkillManager;

	friend class CreatureObjectMessage1;
	//friend class CreatureObjectMessage3;
	friend class CreatureObjectMessage4;
	friend class CreatureObjectMessage6;
	friend class PlayerObjectMessage9;

	friend class CreatureObjectDeltaMessage1;
	friend class CreatureObjectDeltaMessage3;
	friend class CreatureObjectDeltaMessage4;
	friend class CreatureObjectDeltaMessage6;
	friend class PlayerObjectDeltaMessage9;

	friend class ObjectControllerMessage;
	friend class PostureMessage;

	friend class UpdatePVPStatusMessage;

};

#endif /*CREATUREOBJECTIMPLEMENTATION_H_*/
