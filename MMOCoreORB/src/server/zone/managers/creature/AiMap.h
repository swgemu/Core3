/*
 * AiMap.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef AIMAP_H_
#define AIMAP_H_

#include "system/util/VectorMap.h"

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/BehaviorTreeSlot.h"
#include "templates/params/creature/CreatureFlag.h"
#include "templates/params/creature/CreaturePosture.h"
#include "templates/params/creature/CreatureState.h"
#include "server/zone/managers/creature/PetManager.h"

// include all behaviors we want to register
#include "server/zone/objects/creature/ai/bt/TreeSocket.h"
#include "server/zone/objects/creature/ai/bt/node/Selector.h"
#include "server/zone/objects/creature/ai/bt/node/Sequence.h"
#include "server/zone/objects/creature/ai/bt/leaf/Checks.h"
#include "server/zone/objects/creature/ai/bt/leaf/FollowActions.h"
#include "server/zone/objects/creature/ai/bt/leaf/SimpleActions.h"
#include "server/zone/objects/creature/ai/bt/decorator/AlwaysFail.h"
#include "server/zone/objects/creature/ai/bt/decorator/AlwaysSucceed.h"
#include "server/zone/objects/creature/ai/bt/decorator/If.h"
#include "server/zone/objects/creature/ai/bt/decorator/Not.h"
#include "server/zone/objects/creature/ai/bt/decorator/UntilFailure.h"
#include "server/zone/objects/creature/ai/bt/decorator/UntilSuccess.h"
#include "server/zone/objects/creature/ai/bt/decorator/LookForTarget.h"
#include "server/zone/objects/creature/ai/bt/decorator/LookForPlayer.h"
#include "server/zone/objects/creature/ai/bt/decorator/LookForAllies.h"

#define _REGISTERBASE(name) factory.reg(#name, new BehaviorCreator<name>)
#define _REGISTERNODE(name) factory.reg(#name, new BehaviorCreator<node::name>)
#define _REGISTERLEAF(name) factory.reg(#name, new BehaviorCreator<leaf::name>)
#define _REGISTERDECO(name) factory.reg(#name, new BehaviorCreator<decorator::name>)

class BehaviorCreatorHelper {
public:
	virtual ~BehaviorCreatorHelper() {}
	virtual Behavior* create(const String&, const uint32, const LuaObject&) const = 0;
};

template <typename T>
class BehaviorCreator : public BehaviorCreatorHelper {
public:
	Behavior* create(const String& name, const uint32 id, const LuaObject& args) const {
		return new T(name, id, args);
	}
};

class BehaviorFactory {
public:
	~BehaviorFactory() {
		HashTableIterator<String, const BehaviorCreatorHelper*> it = fnMap.iterator();
		while (it.hasNext())
			delete it.next();
	}

	void reg(const String& key, const BehaviorCreatorHelper* fn) {
		if (!fnMap.containsKey(key))
			fnMap.put(key, fn);
	}

	Behavior* create(const String& key, const uint32 id, const LuaObject& args) {
		if (!fnMap.containsKey(key) || fnMap.get(key) == nullptr)
			return NULL;

		return fnMap.get(key)->create(key, id, args);
	}

private:
	HashTable<String, const BehaviorCreatorHelper*> fnMap;
};

class AiMap : public Singleton<AiMap>, public Logger, public Object {
public:
	// <template name, root behavior>
	HashTable<String, Reference<Behavior*> > aiMap;
	// <ai bitmask, <treeID, root behavior> >
	VectorMap<uint32, VectorMap<BehaviorTreeSlot, Reference<Behavior*> > > bitmaskMap;
	VectorMap<uint64, VectorMap<BehaviorTreeSlot, Reference<Behavior*> > > customMap;

	AtomicInteger countExceptions;
	AtomicInteger activeMoveEvents;
	AtomicInteger scheduledMoveEvents;
	AtomicInteger moveEventsWithFollowObject;
	AtomicInteger moveEventsRetreating;

	AtomicInteger activeRecoveryEvents;

	Mutex guard;

	AiMap() : Logger("AiMap") {
		aiMap.setNullValue(NULL);

		initialize();
	}

	~AiMap() {}

	void initialize() {
		if (DEBUG_MODE)
			info("Initializing...", true);

		registerBehaviors();
	}

	void loadTemplates() {
		if (DEBUG_MODE)
			info("Loading templates...", true);

		Lua* lua = new Lua();
		lua->init();
		lua->setLoggingName("AiMapLuaInstance");
		lua->setGlobalLogging(true);
		lua->setLogging(true);

		lua->setGlobalInt("NONE",						BehaviorTreeSlot::NONE					);
		lua->setGlobalInt("AWARE",						BehaviorTreeSlot::AWARE					);
		lua->setGlobalInt("IDLE",						BehaviorTreeSlot::IDLE					);
		lua->setGlobalInt("ATTACK",						BehaviorTreeSlot::ATTACK				);
		lua->setGlobalInt("EQUIP",						BehaviorTreeSlot::EQUIP					);
		lua->setGlobalInt("TARGET",						BehaviorTreeSlot::TARGET				);
		lua->setGlobalInt("MOVE",						BehaviorTreeSlot::MOVE					);
		lua->setGlobalInt("LOOKAT",						BehaviorTreeSlot::LOOKAT				);
		lua->setGlobalInt("AGGRO",						BehaviorTreeSlot::AGGRO					);
		lua->setGlobalInt("SCARE",						BehaviorTreeSlot::SCARE					);
		lua->setGlobalInt("KILL",						BehaviorTreeSlot::KILL					);
		lua->setGlobalInt("STALK",						BehaviorTreeSlot::STALK					);
		lua->setGlobalInt("CRACKDOWNSCAN",				BehaviorTreeSlot::CRACKDOWNSCAN			);
		lua->setGlobalInt("HEAL",						BehaviorTreeSlot::HEAL					);
		lua->setGlobalInt("CHATREACTION",				BehaviorTreeSlot::CHATREACTION			);
		lua->setGlobalInt("NOTIFYHELP",					BehaviorTreeSlot::NOTIFYHELP			);
		lua->setGlobalInt("HARVEST",					BehaviorTreeSlot::HARVEST				);

		lua->setGlobalInt("WALK",						DataVal::WALK							);
		lua->setGlobalInt("RUN",						DataVal::RUN							);
		lua->setGlobalInt("DEFAULT",					DataVal::DEFAULT						);
		lua->setGlobalInt("WEAPON",						DataVal::WEAPON							);
		lua->setGlobalInt("RANDOM",						DataVal::RANDOM							);
		lua->setGlobalInt("PLAYERTYPE",					DataVal::PLAYER							);
		lua->setGlobalInt("CREATURETYPE",				DataVal::CREATURE						);
		lua->setGlobalInt("NPCTYPE",					DataVal::NPC							);
		lua->setGlobalInt("TANGIBLETYPE",				DataVal::TANGIBLE						);
		lua->setGlobalInt("AGENTTYPE",					DataVal::AGENT							);
		lua->setGlobalInt("PRIMARYWEAPON",				DataVal::PRIMARYWEAPON					);
		lua->setGlobalInt("SECONDARYWEAPON",			DataVal::SECONDARYWEAPON				);
		lua->setGlobalInt("MONSTERTYPE",				DataVal::MONSTER						);
		lua->setGlobalInt("DROIDTYPE",					DataVal::DROID							);
		lua->setGlobalInt("ANDROIDTYPE",				DataVal::ANDROID						);
		lua->setGlobalInt("HUMANOIDTYPE",				DataVal::HUMANOID						);

		lua->setGlobalInt("OBLIVIOUS",					AiAgent::OBLIVIOUS						);
		lua->setGlobalInt("WATCHING",					AiAgent::WATCHING						);
		lua->setGlobalInt("STALKING",					AiAgent::STALKING						);
		lua->setGlobalInt("FOLLOWING",					AiAgent::FOLLOWING						);
		lua->setGlobalInt("PATROLLING",					AiAgent::PATROLLING						);
		lua->setGlobalInt("FLEEING",					AiAgent::FLEEING						);
		lua->setGlobalInt("LEASHING",					AiAgent::LEASHING						);
		lua->setGlobalInt("EVADING",					AiAgent::EVADING						);
		lua->setGlobalInt("PATHING_HOME",				AiAgent::PATHING_HOME					);
		lua->setGlobalInt("FOLLOW_FORMATION",			AiAgent::FOLLOW_FORMATION				);
		lua->setGlobalInt("MOVING_TO_HEAL",				AiAgent::MOVING_TO_HEAL					);

		lua->setGlobalInt("UPRIGHT",					CreaturePosture::UPRIGHT				);
		lua->setGlobalInt("CROUCHED",					CreaturePosture::CROUCHED				);
		lua->setGlobalInt("PRONE",						CreaturePosture::PRONE					);
		lua->setGlobalInt("SNEAKING",					CreaturePosture::SNEAKING				);
		lua->setGlobalInt("BLOCKING",					CreaturePosture::BLOCKING				);
		lua->setGlobalInt("CLIMBING",					CreaturePosture::CLIMBING				);
		lua->setGlobalInt("FLYING",						CreaturePosture::FLYING					);
		lua->setGlobalInt("LYINGDOWN",					CreaturePosture::LYINGDOWN				);
		lua->setGlobalInt("SITTING",					CreaturePosture::SITTING				);
		lua->setGlobalInt("SKILLANIMATING",				CreaturePosture::SKILLANIMATING			);
		lua->setGlobalInt("DRIVINGVEHICLE",				CreaturePosture::DRIVINGVEHICLE			);
		lua->setGlobalInt("RIDINGCREATURE",				CreaturePosture::RIDINGCREATURE			);
		lua->setGlobalInt("KNOCKEDDOWN",				CreaturePosture::KNOCKEDDOWN			);
		lua->setGlobalInt("INCAPACITATED",				CreaturePosture::INCAPACITATED			);
		lua->setGlobalInt("DEAD",						CreaturePosture::DEAD					);

		lua->setGlobalInt("STATIONARY",					CreatureLocomotion::STATIONARY			);
		lua->setGlobalInt("SLOW",						CreatureLocomotion::SLOW				);
		lua->setGlobalInt("FAST",						CreatureLocomotion::FAST				);

		lua->setGlobalInt("COVER",						CreatureState::COVER					);
		lua->setGlobalInt("COMBAT",						CreatureState::COMBAT					);
		lua->setGlobalInt("PEACE",						CreatureState::PEACE					);
		lua->setGlobalInt("AIMING",						CreatureState::AIMING					);
		lua->setGlobalInt("ALERT",						CreatureState::ALERT					);
		lua->setGlobalInt("BERSERK",					CreatureState::BERSERK					);
		lua->setGlobalInt("FEIGNDEATH",					CreatureState::FEIGNDEATH				);
		lua->setGlobalInt("COMBATATTITUDEEVASIVE",		CreatureState::COMBATATTITUDEEVASIVE	);
		lua->setGlobalInt("COMBATATTITUDENORMAL",		CreatureState::COMBATATTITUDENORMAL		);
		lua->setGlobalInt("COMBATATTITUDEAGGRESSIVE",	CreatureState::COMBATATTITUDEAGGRESSIVE	);
		lua->setGlobalInt("TUMBLING",					CreatureState::TUMBLING					);
		lua->setGlobalInt("RALLIED",					CreatureState::RALLIED					);
		lua->setGlobalInt("STUNNED",					CreatureState::STUNNED					);
		lua->setGlobalInt("BLINDED",					CreatureState::BLINDED					);
		lua->setGlobalInt("DIZZY",						CreatureState::DIZZY					);
		lua->setGlobalInt("INTIMIDATED",				CreatureState::INTIMIDATED				);
		lua->setGlobalInt("IMMOBILIZED",				CreatureState::IMMOBILIZED				);
		lua->setGlobalInt("FROZEN",						CreatureState::FROZEN					);
		lua->setGlobalInt("SWIMMING",					CreatureState::SWIMMING					);
		lua->setGlobalInt("SITTINGONCHAIR",				CreatureState::SITTINGONCHAIR			);
		lua->setGlobalInt("CRAFTING",					CreatureState::CRAFTING					);
		lua->setGlobalInt("GLOWINGJEDI",				CreatureState::GLOWINGJEDI				);
		lua->setGlobalInt("MASKSCENT",					CreatureState::MASKSCENT				);
		lua->setGlobalInt("POISONED",					CreatureState::POISONED					);
		lua->setGlobalInt("BLEEDING",					CreatureState::BLEEDING					);
		lua->setGlobalInt("DISEASED",					CreatureState::DISEASED					);
		lua->setGlobalInt("ONFIRE",						CreatureState::ONFIRE					);
		lua->setGlobalInt("RIDINGMOUNT",				CreatureState::RIDINGMOUNT				);
		lua->setGlobalInt("MOUNTEDCREATURE",			CreatureState::MOUNTEDCREATURE			);
		lua->setGlobalInt("PILOTINGSHIP",				CreatureState::PILOTINGSHIP				);
		lua->setGlobalInt("SHIPOPERATIONS",				CreatureState::SHIPOPERATIONS			);
		lua->setGlobalInt("SHIPGUNNER",					CreatureState::SHIPGUNNER				);

		lua->setGlobalInt("ATTACKABLE",					CreatureFlag::ATTACKABLE				);
		lua->setGlobalInt("AGGRESSIVE",					CreatureFlag::AGGRESSIVE				);
		lua->setGlobalInt("OVERT",						CreatureFlag::OVERT						);
		lua->setGlobalInt("TEF",						CreatureFlag::TEF						);
		lua->setGlobalInt("PLAYER",						CreatureFlag::PLAYER					);
		lua->setGlobalInt("ENEMY",						CreatureFlag::ENEMY						);
		lua->setGlobalInt("WILLBEDECLARED",				CreatureFlag::WILLBEDECLARED			);
		lua->setGlobalInt("WASDECLARED",				CreatureFlag::WASDECLARED				);

		lua->setGlobalInt("NPC",						CreatureFlag::NPC						);
		lua->setGlobalInt("PACK",						CreatureFlag::PACK						);
		lua->setGlobalInt("HERD",						CreatureFlag::HERD						);
		lua->setGlobalInt("KILLER",						CreatureFlag::KILLER					);
		lua->setGlobalInt("STALKER",					CreatureFlag::STALKER					);
		lua->setGlobalInt("BABY",						CreatureFlag::BABY						);
		lua->setGlobalInt("LAIR",						CreatureFlag::LAIR						);
		lua->setGlobalInt("HEALER",						CreatureFlag::HEALER					);
		lua->setGlobalInt("SCOUT",						CreatureFlag::SCOUT						);
		lua->setGlobalInt("PET",						CreatureFlag::PET						);
		lua->setGlobalInt("DROID_PET",					CreatureFlag::DROID_PET					);
		lua->setGlobalInt("FACTION_PET",				CreatureFlag::FACTION_PET				);
		lua->setGlobalInt("ESCORT",						CreatureFlag::ESCORT					);
		lua->setGlobalInt("FOLLOW",						CreatureFlag::FOLLOW					);
		lua->setGlobalInt("STATIC",						CreatureFlag::STATIC					);
		lua->setGlobalInt("STATIONARY",					CreatureFlag::STATIONARY				);
		lua->setGlobalInt("NOAIAGGRO",					CreatureFlag::NOAIAGGRO					);
		lua->setGlobalInt("TEST",						CreatureFlag::TEST						);

		lua->setGlobalInt("CARNIVORE",					CreatureFlag::CARNIVORE					);
		lua->setGlobalInt("HERBIVORE",					CreatureFlag::HERBIVORE					);

		lua->setGlobalInt("PET_FOLLOW",					PetManager::FOLLOW						);
		lua->setGlobalInt("PET_STORE",					PetManager::STORE						);
		lua->setGlobalInt("PET_ATTACK",					PetManager::ATTACK						);
		lua->setGlobalInt("PET_GUARD",					PetManager::GUARD						);
		lua->setGlobalInt("PET_FRIEND",					PetManager::FRIEND						);
		lua->setGlobalInt("PET_FOLLOWOTHER",			PetManager::FOLLOWOTHER					);
		lua->setGlobalInt("PET_TRICK1",					PetManager::TRICK1						);
		lua->setGlobalInt("PET_TRICK2",					PetManager::TRICK2						);
		lua->setGlobalInt("PET_PATROL",					PetManager::PATROL						);
		lua->setGlobalInt("PET_FORMATION1",				PetManager::FORMATION1					);
		lua->setGlobalInt("PET_FORMATION2",				PetManager::FORMATION2					);
		lua->setGlobalInt("PET_SPECIAL_ATTACK1",		PetManager::SPECIAL_ATTACK1				);
		lua->setGlobalInt("PET_SPECIAL_ATTACK2",		PetManager::SPECIAL_ATTACK2				);
		lua->setGlobalInt("PET_RANGED_ATTACK",			PetManager::RANGED_ATTACK				);
		lua->setGlobalInt("PET_GROUP",					PetManager::GROUP						);
		lua->setGlobalInt("PET_STAY",					PetManager::STAY						);
		lua->setGlobalInt("PET_RECHARGEOTHER",			PetManager::RECHARGEOTHER				);
		lua->setGlobalInt("PET_TRANSFER",				PetManager::TRANSFER					);
		lua->setGlobalInt("PET_THROW",					PetManager::THROWTRAP					);

		lua_register(lua->getLuaState(), "includeFile", includeFile);
		lua_register(lua->getLuaState(), "addAiTemplate", addAiTemplate);
		lua->runFile("scripts/ai/templates.lua");

		putBitmask(lua, "bitmaskLookup");
		loadCustomMap(lua);

		delete lua;
	}

	int getTemplateSize() {
		return aiMap.size();
	}

	// put the root node of a btree into this map
	void putTemplate(const String& name, Reference<Behavior*> ait) {
		aiMap.put(name, ait);
	}

	// returns the root node of a behavior tree
	Behavior* getTemplate(const String& name) {
		if (name == "none")
			return NULL;

		return aiMap.get(name);
	}

	// returns the root node of a behavior tree associated with the tree type (treeID)
	Behavior* getTemplate(uint32 bitMask, BehaviorTreeSlot treeID, uint64 customMapName = 0) {
		if (customMapName > 0) {
			auto treeMap = customMap.get(customMapName);
			if (treeMap.contains(treeID)) return treeMap.get(treeID);
		}

		for (int mask = CreatureFlag::LASTAIMASK; (mask = mask >> 1) >= 0;) {
			if ((bitMask & mask) == mask && bitmaskMap.contains(mask)) {
				auto treeMap = bitmaskMap.get((uint32)(mask));
				if (treeMap.contains(treeID)) return treeMap.get(treeID);
			}

			if (mask == 0) break;
		}

		AiMap::instance()->error("Failed to find Behavior for mask: " + String::valueOf(bitMask) + " and treeID: " + String::valueOf(treeID));
		return NULL;
	}

	Behavior* createBehavior(const String& name, const uint32 id, const LuaObject& args) {
		return factory.create(name, id, args);
	}

private:
	static const bool DEBUG_MODE = true;
	BehaviorFactory factory;

	void registerBehaviors() {
		// special behaviors
		_REGISTERBASE(TreeSocket);
		// composite behaviors
		_REGISTERNODE(Selector);
		_REGISTERNODE(ParallelSelector);
		_REGISTERNODE(RandomSelector);
		_REGISTERNODE(Sequence);
		_REGISTERNODE(ParallelSequence);
		_REGISTERNODE(RandomSequence);
		// decorator behaviors
		_REGISTERDECO(AlwaysFail);
		_REGISTERDECO(AlwaysSucceed);
		_REGISTERDECO(If);
		_REGISTERDECO(Not);
		_REGISTERDECO(UntilFailure);
		_REGISTERDECO(UntilSuccess);
		_REGISTERDECO(LookForTarget);
		_REGISTERDECO(LookForPlayer);
		_REGISTERDECO(LookForAllies);
		// check behaviors
		_REGISTERLEAF(CheckPosture);
		_REGISTERLEAF(CheckDestination);
		_REGISTERLEAF(CheckMovementState);
		_REGISTERLEAF(CheckHasFollow);
		_REGISTERLEAF(CheckFollowHasState);
		_REGISTERLEAF(CheckAggroDelayPast);
		_REGISTERLEAF(CheckProspectInRange);
		_REGISTERLEAF(CheckFollowAggression);
		_REGISTERLEAF(CheckProspectAggression);
		_REGISTERLEAF(CheckIsCamouflaged);
		_REGISTERLEAF(CheckFollowPosture);
		_REGISTERLEAF(CheckFollowInWeaponRange);
		_REGISTERLEAF(CheckFollowClosestIdealRange);
		_REGISTERLEAF(CheckRandomLevel);
		_REGISTERLEAF(CheckAttackInRange);
		_REGISTERLEAF(CheckAttackIsValid);
		_REGISTERLEAF(CheckTargetIsValid);
		_REGISTERLEAF(CheckRetreat);
		_REGISTERLEAF(CheckSpeed);
		_REGISTERLEAF(CheckProspectSpeed);
		_REGISTERLEAF(CheckProspectLOS);
		_REGISTERLEAF(CheckOutdoors);
		_REGISTERLEAF(CheckProspectLevel);
		_REGISTERLEAF(CheckProspectBackAggression);
		_REGISTERLEAF(CheckProspectFacing);
		_REGISTERLEAF(CheckPetCommand);
		_REGISTERLEAF(CheckProspectIsCommand);
		_REGISTERLEAF(CheckIsInCombat);
		_REGISTERLEAF(CheckHasPatrol);
		_REGISTERLEAF(CheckProspectIsType);
		_REGISTERLEAF(CheckIsType);
		_REGISTERLEAF(CheckProspectJediTrial);
		_REGISTERLEAF(CheckProspectIsIncapacitated);
		_REGISTERLEAF(CheckIsKiller);
		_REGISTERLEAF(CheckIsHealer);
		_REGISTERLEAF(CheckHealChance);
		_REGISTERLEAF(CheckIsStalker);
		_REGISTERLEAF(CheckFlee);
		_REGISTERLEAF(CheckOwnerInRange);
		_REGISTERLEAF(CheckTargetInOwnerRange);
		_REGISTERLEAF(CheckUseRanged);
		_REGISTERLEAF(CheckWeaponIsRanged);
		_REGISTERLEAF(CheckIsDroid);
		_REGISTERLEAF(CheckCrackdownScanner);
		_REGISTERLEAF(CheckCrackdownFollowTarget);
		_REGISTERLEAF(CheckIsStationary);
		_REGISTERLEAF(CheckIsHome);
		_REGISTERLEAF(CheckHomeIsCell);
		_REGISTERLEAF(CheckChatDelay);
		_REGISTERLEAF(CheckCallForHelp);
		_REGISTERLEAF(CheckIsHarvester);
		_REGISTERLEAF(CheckHasHarvestTargets);
		// action behaviors
		_REGISTERLEAF(Dummy);
		_REGISTERLEAF(GeneratePatrol);
		_REGISTERLEAF(ExitCombat);
		_REGISTERLEAF(EquipStagedWeapon);
		_REGISTERLEAF(WriteBlackboard);
		_REGISTERLEAF(EraseBlackboard);
		_REGISTERLEAF(SelectAttack);
		_REGISTERLEAF(EnqueueAttack);
		_REGISTERLEAF(GetProspectFromThreatMap);
		_REGISTERLEAF(GetProspectFromDefenders);
		_REGISTERLEAF(GetProspectFromTarget);
		_REGISTERLEAF(GetProspectFromCommand);
		_REGISTERLEAF(RestoreFollow);
		_REGISTERLEAF(DropProspectFromDefenders);
		_REGISTERLEAF(SetDefenderFromProspect);
		_REGISTERLEAF(UpdateRangeToFollow);
		_REGISTERLEAF(SetMovementState);
		_REGISTERLEAF(CalculateAggroMod);
		_REGISTERLEAF(RunAway);
		_REGISTERLEAF(Evade);
		_REGISTERLEAF(FindNextPosition);
		_REGISTERLEAF(Leash);
		_REGISTERLEAF(Wait);
		_REGISTERLEAF(SetAlert);
		_REGISTERLEAF(KillProspect);
		_REGISTERLEAF(StalkProspect);
		_REGISTERLEAF(Flee);
		_REGISTERLEAF(SetAttackPosture);
		_REGISTERLEAF(PetReturn);
		_REGISTERLEAF(ContrabandScan);
		_REGISTERLEAF(FollowSquadLeader);
		_REGISTERLEAF(GetHealTarget);
		_REGISTERLEAF(HealTarget);
		_REGISTERLEAF(RestorePetPatrols);
		_REGISTERLEAF(SendChatGreeting);
		_REGISTERLEAF(CallForHelp);
		_REGISTERLEAF(DroidHarvest);
	}

	void putBitmask(Lua* lua, String key) {
		LuaObject obj = lua->getGlobalObject(key);
		if (!obj.isValidTable()) {
			AiMap::instance()->error("Failed to load bitmask map: " + key);
			return;
		}

		for (int i = 1; i <= obj.getTableSize(); ++i) {
			LuaObject entry = obj.getObjectAt(i);
			if (!entry.isValidTable()) {
				AiMap::instance()->error("Failed to load bitmask map at : " + String::valueOf(i));
				continue;
			}

			uint32 flag = entry.getIntAt(1);
			LuaObject table = entry.getObjectAt(2);
			if (!table.isValidTable()) {
				AiMap::instance()->error("Failed to load bitmask map for flag: " + String::valueOf(flag));
				continue;
			}

			VectorMap<BehaviorTreeSlot, Reference<Behavior*> > flagMap;
			flagMap.setNullValue(NULL);
			for (int j = 1; j <= table.getTableSize(); ++j){
				LuaObject tableEntry = table.getObjectAt(j);
				if (!tableEntry.isValidTable()) {
					AiMap::instance()->error("Invalid entry in table: " + String::valueOf(flag));
					continue;
				}

				BehaviorTreeSlot treeNum = static_cast<BehaviorTreeSlot>(tableEntry.getIntAt(1));
				String tempName = tableEntry.getStringAt(2);
				tableEntry.pop();

				flagMap.put(treeNum, AiMap::instance()->getTemplate(tempName));
			}

			if (DEBUG_MODE)
				info("Loaded bitmask: " + String::valueOf(flag), true);

			table.pop();
			entry.pop();

			bitmaskMap.put(flag, flagMap);
		}
		obj.pop();
	}

	void loadCustomMap(Lua* lua) {
		LuaObject obj = lua->getGlobalObject("customMap");
		if (!obj.isValidTable()) {
			AiMap::instance()->error("Failed to load custom map.");
			return;
		}

		for (int i = 1; i <= obj.getTableSize(); ++i) {
			LuaObject entry = obj.getObjectAt(i);
			if (!entry.isValidTable()) {
				AiMap::instance()->error("Failed to load custom map at : " + String::valueOf(i));
				continue;
			}

			String stringKey = entry.getStringAt(1);
			LuaObject table = entry.getObjectAt(2);
			if (!table.isValidTable()) {
				AiMap::instance()->error("Failed to load custom map for key: " + stringKey);
				continue;
			}

			VectorMap<BehaviorTreeSlot, Reference<Behavior*> > flagMap;
			flagMap.setNullValue(NULL);
			for (int j = 1; j <= table.getTableSize(); ++j){
				LuaObject tableEntry = table.getObjectAt(j);
				if (!tableEntry.isValidTable()) {
					AiMap::instance()->error("Invalid custom map entry in table: " + stringKey);
					continue;
				}

				BehaviorTreeSlot treeNum = static_cast<BehaviorTreeSlot>(tableEntry.getIntAt(1));
				String tempName = tableEntry.getStringAt(2);
				tableEntry.pop();

				flagMap.put(treeNum, AiMap::instance()->getTemplate(tempName));
			}

			if (DEBUG_MODE)
				info("Loaded custom map: " + stringKey, true);

			table.pop();
			entry.pop();

			customMap.put(stringKey.hashCode(), flagMap);
		}

		obj.pop();
	}

	static int includeFile(lua_State* L) {
		String filename = Lua::getStringParameter(L);

		if (DEBUG_MODE)
			AiMap::instance()->info("Including file: " + filename, true);

		Lua::runFile("scripts/ai/" + filename, L);

		return 0;
	}

	static int addAiTemplate(lua_State* L) {
		String name = lua_tostring(L, -2);

		if (DEBUG_MODE)
			AiMap::instance()->info("Including template: " + name, true);

		LuaObject obj(L);
		if (!obj.isValidTable()) {
			AiMap::instance()->error("Lua AI template not found: " + name);
			obj.pop();
			return 0;
		}

		Vector<Reference<Behavior*> > loadVec;
		VectorMap<uint32, Behavior*> loadMap;
		VectorMap<uint32, uint32> parentMap;

		for (int i = 1; i <= obj.getTableSize(); ++i) {
			lua_rawgeti(L, -1, i);
			LuaObject behavior(L);

			if (behavior.isValidTable()) {
				uint32 id = behavior.getStringField("id").hashCode();
				String className = behavior.getStringField("name");
				uint32 parent = behavior.getStringField("pid").hashCode();
				LuaObject args = behavior.getObjectField("args");

				//if (DEBUG_MODE)
				//	AiMap::instance()->info("Read Behavior: " + className, true);

				Behavior* b = AiMap::instance()->createBehavior(className, id, args);
				args.pop();

				loadVec.add(b);
				loadMap.put(id, b);
				parentMap.put(id, parent);

				//if (DEBUG_MODE)
				//	AiMap::instance()->info("Instantiated Behavior: " + b->print(), true);
			}

			behavior.pop();
		}

		for (int idx = 0; idx < loadVec.size(); ++idx) {
			Reference<Behavior*> child = loadVec.get(idx);
			if (child == nullptr)
				continue;

			uint32 parentID = parentMap.get(child->getID());
			if (parentID == STRING_HASHCODE("none")) // this is the root
				continue;

			Reference<Behavior*> parent = loadMap.get(parentID);
			child->setParent(parent); // this method asserts that parent is proper

			if (parent->isComposite())
				static_cast<node::Composite*>(parent.get())->addChild(child);
			else if (parent->isDecorator())
				static_cast<decorator::Decorator*>(parent.get())->setChild(child);
		}

		// root will be the final result of any behavior in the tree
		Reference<Behavior*> root = loadMap.get(0);
		while (root->getParent())
			root = root->getParent();

		AiMap::instance()->putTemplate(name, root);

		if (DEBUG_MODE)
			AiMap::instance()->info("Loaded AI template " + name, true);

		obj.pop();
		return 0;
	}
};

#endif /* AIMAP_H_ */
