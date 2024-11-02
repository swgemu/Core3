/*
 * SpaceAiMap.h
 */

#ifndef SPACEAIMAP_H_
#define SPACEAIMAP_H_

#include "server/ServerCore.h"
#include "system/util/VectorMap.h"

// Space AI
#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"
#include "server/zone/objects/ship/ai/btspace/BehaviorTreeSlotSpace.h"

#include "templates/params/ship/ShipFlag.h"

// include all behaviors we want to register
#include "server/zone/objects/ship/ai/btspace/TreeSocketSpace.h"
#include "server/zone/objects/ship/ai/btspace/nodespace/SelectorSpace.h"
#include "server/zone/objects/ship/ai/btspace/nodespace/SequenceSpace.h"
#include "server/zone/objects/ship/ai/btspace/leafspace/ChecksSpace.h"
#include "server/zone/objects/ship/ai/btspace/leafspace/FollowActionsSpace.h"
#include "server/zone/objects/ship/ai/btspace/leafspace/SimpleActionsSpace.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/AlwaysFailSpace.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/AlwaysSucceedSpace.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/IfSpace.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/NotSpace.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/UntilFailureSpace.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/UntilSuccessSpace.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/LookForTargetSpace.h"

#define _REGISTERSPACEBASE(name) factory.reg(#name, new SpaceBehaviorCreator<name>)
#define _REGISTERSPACENODE(name) factory.reg(#name, new SpaceBehaviorCreator<nodespace::name>)
#define _REGISTERSPACELEAF(name) factory.reg(#name, new SpaceBehaviorCreator<leafspace::name>)
#define _REGISTERSPACEDECO(name) factory.reg(#name, new SpaceBehaviorCreator<decoratorspace::name>)

class SpaceBehaviorCreatorHelper {
public:
	virtual ~SpaceBehaviorCreatorHelper() {
	}
	virtual BehaviorSpace* create(const String&, const uint32, const LuaObject&) const = 0;
};

template <typename T>
class SpaceBehaviorCreator : public SpaceBehaviorCreatorHelper {
public:
	BehaviorSpace* create(const String& name, const uint32 id, const LuaObject& args) const {
		return new T(name, id, args);
	}
};

class SpaceBehaviorFactory {
public:
	~SpaceBehaviorFactory() {
		HashTableIterator<String, const SpaceBehaviorCreatorHelper*> it = fnMap.iterator();
		while (it.hasNext())
			delete it.next();
	}

	void reg(const String& key, const SpaceBehaviorCreatorHelper* fn) {
		if (!fnMap.containsKey(key))
			fnMap.put(key, fn);
	}

	BehaviorSpace* create(const String& key, const uint32 id, const LuaObject& args) {
		if (!fnMap.containsKey(key) || fnMap.get(key) == nullptr)
			return NULL;

		return fnMap.get(key)->create(key, id, args);
	}

private:
	HashTable<String, const SpaceBehaviorCreatorHelper*> fnMap;
};

class SpaceAiMap : public Singleton<SpaceAiMap>, public Logger, public Object {
public:
	// <template name, root behavior>
	HashTable<String, Reference<BehaviorSpace*>> spaceAiMap;
	// <ai bitmask, <treeID, root behavior> >
	VectorMap<uint32, VectorMap<BehaviorTreeSlotSpace, Reference<BehaviorSpace*>>> bitmaskMap;
	VectorMap<uint64, VectorMap<BehaviorTreeSlotSpace, Reference<BehaviorSpace*>>> customMap;

	AtomicInteger countExceptions;
	AtomicInteger activeBehaviorEvents;
	AtomicInteger scheduledBehaviorEvents;
	AtomicInteger behaviorsWithFollowObject;
	AtomicInteger behaviorsRetreating;
	AtomicInteger activeRecoveryEvents;

	Mutex guard;

	SpaceAiMap() : Logger("SpaceAiMap") {
		spaceAiMap.setNullValue(NULL);

		initialize();
	}

	~SpaceAiMap() {
	}

	void initialize() {
		if (DEBUG_MODE)
			info("Initializing...", true);

		registerBehaviors();
	}

	void loadTemplates() {
		if (DEBUG_MODE)
			info("Loading space templates...", true);

		Lua* lua = new Lua();
		lua->init();
		lua->setLoggingName("SpaceAiMapLuaInstance");
		lua->setGlobalLogging(true);
		lua->setLogging(false);

		// SpaceAI
		lua->setGlobalInt("NONESPACE",			BehaviorTreeSlotSpace::NONESPACE);
		lua->setGlobalInt("AGGROSPACE",			BehaviorTreeSlotSpace::AGGROSPACE);
		lua->setGlobalInt("ATTACKSPACE",		BehaviorTreeSlotSpace::ATTACKSPACE);
		lua->setGlobalInt("AWARESPACE",			BehaviorTreeSlotSpace::AWARESPACE);
		lua->setGlobalInt("EVADESPACE",			BehaviorTreeSlotSpace::EVADESPACE);
		lua->setGlobalInt("IDLESPACE",			BehaviorTreeSlotSpace::IDLESPACE);
		lua->setGlobalInt("LOOKATSPACE",		BehaviorTreeSlotSpace::LOOKATSPACE);
		lua->setGlobalInt("MOVESPACE",			BehaviorTreeSlotSpace::MOVESPACE);
		lua->setGlobalInt("TARGETSPACE",		BehaviorTreeSlotSpace::TARGETSPACE);

		// Ship Bitmasks in ShipFlag.h
		lua->setGlobalInt("ESCORT",				ShipFlag::ESCORT);
		lua->setGlobalInt("FOLLOW",				ShipFlag::FOLLOW);
		lua->setGlobalInt("TURRETSHIP",			ShipFlag::TURRETSHIP);
		lua->setGlobalInt("GUARD_PATROL",		ShipFlag::GUARD_PATROL);
		lua->setGlobalInt("RANDOM_PATROL",		ShipFlag::RANDOM_PATROL);
		lua->setGlobalInt("FIXED_PATROL",		ShipFlag::FIXED_PATROL);
		lua->setGlobalInt("SQUADRON_PATROL",	ShipFlag::SQUADRON_PATROL);
		lua->setGlobalInt("SQUADRON_FOLLOW",	ShipFlag::SQUADRON_FOLLOW);
		lua->setGlobalInt("TEST",				ShipFlag::TEST);

		lua->setGlobalInt("OBLIVIOUS",			ShipAiAgent::OBLIVIOUS);
		lua->setGlobalInt("WATCHING",			ShipAiAgent::WATCHING);
		lua->setGlobalInt("FOLLOWING",			ShipAiAgent::FOLLOWING);
		lua->setGlobalInt("PATROLLING",			ShipAiAgent::PATROLLING);
		lua->setGlobalInt("ATTACKING",			ShipAiAgent::ATTACKING);
		lua->setGlobalInt("FLEEING",			ShipAiAgent::FLEEING);
		lua->setGlobalInt("LEASHING",			ShipAiAgent::LEASHING);
		lua->setGlobalInt("EVADING",			ShipAiAgent::EVADING);
		lua->setGlobalInt("PATHING_HOME",		ShipAiAgent::PATHING_HOME);
		lua->setGlobalInt("FOLLOW_FORMATION",	ShipAiAgent::FOLLOW_FORMATION);

		lua_register(lua->getLuaState(), "includeFile", includeFile);
		lua_register(lua->getLuaState(), "addAiTemplate", addSpaceAiTemplate);

		lua->runFile("scripts/ai_space/space_templates.lua");

		putBitmask(lua, "bitmaskLookup");
		loadCustomMap(lua);

		delete lua;
	}

	int getTemplateSize() {
		return spaceAiMap.size();
	}

	// put the root node of a btree into this map
	void putTemplate(const String& name, Reference<BehaviorSpace*> ait) {
		spaceAiMap.put(name, ait);
	}

	// returns the root node of a behavior tree
	BehaviorSpace* getTemplate(const String& name) {
		if (name == "none")
			return NULL;

		return spaceAiMap.get(name);
	}

	// returns the root node of a behavior tree associated with the tree type (treeID)
	BehaviorSpace* getTemplate(uint32 bitMask, BehaviorTreeSlotSpace treeID, uint64 customMapName = 0) {
		if (customMapName > 0) {
			auto treeMap = customMap.get(customMapName);
			if (treeMap.contains(treeID))
				return treeMap.get(treeID);
		}

		for (int mask = ShipFlag::LASTAIMASK; (mask = mask >> 1) >= 0;) {
			if ((bitMask & mask) == mask && bitmaskMap.contains(mask)) {
				auto treeMap = bitmaskMap.get((uint32)(mask));

				if (treeMap.contains(treeID)) {
					return treeMap.get(treeID);
				}
			}

			if (mask == 0)
				break;
		}

		error() << "Failed to find Space Behavior for mask: " << bitMask << " and treeID: " << treeID;

		return nullptr;
	}

	BehaviorSpace* createBehavior(const String& name, const uint32 id, const LuaObject& args) {
		return factory.create(name, id, args);
	}

	const JSONSerializationType getStatsAsJSON() const {
		JSONSerializationType json;

		json["activeBehaviorEvents"] = activeBehaviorEvents.get();
		json["activeRecoveryEvents"] = activeRecoveryEvents.get();
		json["countExceptions"] = countExceptions.get();
		json["behaviorsRetreating"] = behaviorsRetreating.get();
		json["behaviorsWithFollowObject"] = behaviorsWithFollowObject.get();
		json["scheduledMoveEvents"] = scheduledBehaviorEvents.get();

		auto server = ServerCore::getZoneServer();

		if (server != nullptr) {
			int totalSpawned = 0;

			for (int i = 0; i < server->getSpaceZoneCount(); ++i) {
				Zone* zone = server->getSpaceZone(i);

				if (zone == nullptr)
					continue;

				int num = zone->getSpawnedAiAgents();

				if (num <= 0)
					continue;

				String ucFirstZoneName = zone->getZoneName();
				ucFirstZoneName[0] = toupper(ucFirstZoneName[0]);
				json["countAiAgents" + ucFirstZoneName] = num;

				totalSpawned += num;
			}

			json["countAiAgentsTotal"] = totalSpawned;
		}

		return json;
	}

private:
	static const bool DEBUG_MODE = false;
	SpaceBehaviorFactory factory;

	void registerBehaviors() {
		// special behaviors
		_REGISTERSPACEBASE(TreeSocketSpace);
		// composite behaviors
		_REGISTERSPACENODE(SelectorSpace);
		_REGISTERSPACENODE(ParallelSelectorSpace);
		_REGISTERSPACENODE(RandomSelectorSpace);
		_REGISTERSPACENODE(SequenceSpace);
		_REGISTERSPACENODE(ParallelSequenceSpace);
		_REGISTERSPACENODE(RandomSequenceSpace);
		// decorator behaviors
		_REGISTERSPACEDECO(AlwaysFailSpace);
		_REGISTERSPACEDECO(AlwaysSucceedSpace);
		_REGISTERSPACEDECO(IfSpace);
		_REGISTERSPACEDECO(NotSpace);
		_REGISTERSPACEDECO(UntilFailureSpace);
		_REGISTERSPACEDECO(UntilSuccessSpace);
		_REGISTERSPACEDECO(LookForTargetSpace);

		// check behaviors
		_REGISTERSPACELEAF(CheckDestination);
		_REGISTERSPACELEAF(CheckHasPatrol);
		_REGISTERSPACELEAF(CheckMovementState);
		_REGISTERSPACELEAF(CheckProspectInRange);
		_REGISTERSPACELEAF(CheckAggroDelayPast);
		_REGISTERSPACELEAF(CheckHasFollow);
		_REGISTERSPACELEAF(CheckProspectAggression);
		_REGISTERSPACELEAF(CheckRefireRate);
		_REGISTERSPACELEAF(CheckStopEvading);
		_REGISTERSPACELEAF(CheckTargetIsValid);
		_REGISTERSPACELEAF(CheckEnginesDisabled);
		_REGISTERSPACELEAF(CheckEvadeChance);
		_REGISTERSPACELEAF(CheckRetreat);
		_REGISTERSPACELEAF(CheckProspectLOS);
		_REGISTERSPACELEAF(CheckWeapons);

		// action behaviors
		_REGISTERSPACELEAF(DummySpace);
		_REGISTERSPACELEAF(FindNextPosition);
		_REGISTERSPACELEAF(Wait);
		_REGISTERSPACELEAF(GeneratePatrol);
		_REGISTERSPACELEAF(ExitCombat);
		_REGISTERSPACELEAF(WriteBlackboard);
		_REGISTERSPACELEAF(EraseBlackboard);
		_REGISTERSPACELEAF(CalculateAggroMod);
		_REGISTERSPACELEAF(SetMovementState);
		_REGISTERSPACELEAF(Evade);
		_REGISTERSPACELEAF(SetAlert);
		_REGISTERSPACELEAF(SetDefenderFromProspect);
		_REGISTERSPACELEAF(GetProspectFromThreatMap);
		_REGISTERSPACELEAF(EngageSingleTarget);
		_REGISTERSPACELEAF(EngageTurrets);
		_REGISTERSPACELEAF(SetDisabledEngineSpeed);
		_REGISTERSPACELEAF(Leash);
		_REGISTERSPACELEAF(GetProspectFromDefenders);
	}

	void putBitmask(Lua* lua, String key) {
		LuaObject obj = lua->getGlobalObject(key);

		if (!obj.isValidTable()) {
			SpaceAiMap::instance()->error("Failed to load bitmask map: " + key);
			return;
		}

		for (int i = 1; i <= obj.getTableSize(); ++i) {
			LuaObject entry = obj.getObjectAt(i);

			if (!entry.isValidTable()) {
				SpaceAiMap::instance()->error("Failed to load bitmask map at : " + String::valueOf(i));
				continue;
			}

			uint32 flag = entry.getIntAt(1);
			LuaObject table = entry.getObjectAt(2);

			if (!table.isValidTable()) {
				SpaceAiMap::instance()->error("Failed to load bitmask map for flag: " + String::valueOf(flag));
				continue;
			}

			VectorMap<BehaviorTreeSlotSpace, Reference<BehaviorSpace*>> flagMap;
			flagMap.setNullValue(NULL);

			for (int j = 1; j <= table.getTableSize(); ++j) {
				LuaObject tableEntry = table.getObjectAt(j);

				if (!tableEntry.isValidTable()) {
					SpaceAiMap::instance()->error("Invalid entry in table: " + String::valueOf(flag));
					continue;
				}

				uint32 tableInt = tableEntry.getIntAt(1);

				BehaviorTreeSlotSpace treeNum = static_cast<BehaviorTreeSlotSpace>(tableInt);
				String tempName = tableEntry.getStringAt(2);

				tableEntry.pop();

				flagMap.put(treeNum, SpaceAiMap::instance()->getTemplate(tempName));
			}

			if (DEBUG_MODE) {
				info(true) << "Loaded bitmask: " << flag;
			}

			table.pop();
			entry.pop();

			bitmaskMap.put(flag, flagMap);
		}

		obj.pop();
	}

	void loadCustomMap(Lua* lua) {
		LuaObject obj = lua->getGlobalObject("customMap");
		if (!obj.isValidTable()) {
			SpaceAiMap::instance()->error("Failed to load custom map.");
			return;
		}

		for (int i = 1; i <= obj.getTableSize(); ++i) {
			LuaObject entry = obj.getObjectAt(i);
			if (!entry.isValidTable()) {
				SpaceAiMap::instance()->error("Failed to load custom map at : " + String::valueOf(i));
				continue;
			}

			String stringKey = entry.getStringAt(1);
			LuaObject table = entry.getObjectAt(2);
			if (!table.isValidTable()) {
				SpaceAiMap::instance()->error("Failed to load custom map for key: " + stringKey);
				continue;
			}

			VectorMap<BehaviorTreeSlotSpace, Reference<BehaviorSpace*>> flagMap;
			flagMap.setNullValue(NULL);
			for (int j = 1; j <= table.getTableSize(); ++j) {
				LuaObject tableEntry = table.getObjectAt(j);
				if (!tableEntry.isValidTable()) {
					SpaceAiMap::instance()->error("Invalid custom map entry in table: " + stringKey);
					continue;
				}

				BehaviorTreeSlotSpace treeNum = static_cast<BehaviorTreeSlotSpace>(tableEntry.getIntAt(1));
				String tempName = tableEntry.getStringAt(2);
				tableEntry.pop();

				flagMap.put(treeNum, SpaceAiMap::instance()->getTemplate(tempName));
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
			SpaceAiMap::instance()->info("Including file: " + filename, true);

		Lua::runFile("scripts/ai_space/" + filename, L);

		return 0;
	}

	static int addSpaceAiTemplate(lua_State* L) {
		String name = lua_tostring(L, -2);

		if (DEBUG_MODE)
			SpaceAiMap::instance()->info("Including template: " + name, true);

		LuaObject obj(L);
		if (!obj.isValidTable()) {
			SpaceAiMap::instance()->error("Lua AI template not found: " + name);
			obj.pop();
			return 0;
		}

		Vector<Reference<BehaviorSpace*>> loadVec;
		VectorMap<uint32, BehaviorSpace*> loadMap;
		VectorMap<uint32, uint32> parentMap;

		for (int i = 1; i <= obj.getTableSize(); ++i) {
			lua_rawgeti(L, -1, i);
			LuaObject behavior(L);

			if (behavior.isValidTable()) {
				uint32 id = behavior.getStringField("id").hashCode();
				String className = behavior.getStringField("name");
				uint32 parent = behavior.getStringField("pid").hashCode();
				LuaObject args = behavior.getObjectField("args");

				// if (DEBUG_MODE)
				//	SpaceAiMap::instance()->info("Read Behavior: " + className, true);

				BehaviorSpace* b = SpaceAiMap::instance()->createBehavior(className, id, args);
				args.pop();

				loadVec.add(b);
				loadMap.put(id, b);
				parentMap.put(id, parent);

				// if (DEBUG_MODE)
				//	SpaceAiMap::instance()->info("Instantiated Behavior: " + b->print(), true);
			}

			behavior.pop();
		}

		for (int idx = 0; idx < loadVec.size(); ++idx) {
			Reference<BehaviorSpace*> child = loadVec.get(idx);
			if (child == nullptr)
				continue;

			uint32 parentID = parentMap.get(child->getID());
			if (parentID == STRING_HASHCODE("none")) // this is the root
				continue;

			Reference<BehaviorSpace*> parent = loadMap.get(parentID);
			child->setParent(parent); // this method asserts that parent is proper

			if (parent->isCompositeSpace())
				static_cast<nodespace::CompositeSpace*>(parent.get())->addChild(child);
			else if (parent->isDecoratorSpace())
				static_cast<decoratorspace::DecoratorSpace*>(parent.get())->setChild(child);
		}

		// root will be the final result of any behavior in the tree
		Reference<BehaviorSpace*> root = loadMap.get(0);

		while (root->getParent())
			root = root->getParent();

		SpaceAiMap::instance()->putTemplate(name, root);

		if (DEBUG_MODE)
			SpaceAiMap::instance()->info("Loaded Ship AI template " + name, true);

		obj.pop();
		return 0;
	}
};

#endif /* SPACEAIMAP_H_ */
