/*
 * SpaceAiMap.h
 */

#ifndef SPACEAIMAP_H_
#define SPACEAIMAP_H_

#include "server/ServerCore.h"
#include "system/util/VectorMap.h"

// Space AI
#include "server/zone/objects/ship/ai/bt/Behavior.h"
#include "server/zone/objects/ship/ai/bt/BehaviorTreeSlot.h"

#include "templates/params/creature/CreatureFlag.h"

// include all behaviors we want to register
#include "server/zone/objects/ship/ai/bt/TreeSocket.h"
#include "server/zone/objects/ship/ai/bt/node/Selector.h"
#include "server/zone/objects/ship/ai/bt/node/Sequence.h"
#include "server/zone/objects/ship/ai/bt/leaf/Checks.h"
#include "server/zone/objects/ship/ai/bt/leaf/FollowActions.h"
#include "server/zone/objects/ship/ai/bt/leaf/SimpleActions.h"
#include "server/zone/objects/ship/ai/bt/decorator/AlwaysFail.h"
#include "server/zone/objects/ship/ai/bt/decorator/AlwaysSucceed.h"
#include "server/zone/objects/ship/ai/bt/decorator/If.h"
#include "server/zone/objects/ship/ai/bt/decorator/Not.h"
#include "server/zone/objects/ship/ai/bt/decorator/UntilFailure.h"
#include "server/zone/objects/ship/ai/bt/decorator/UntilSuccess.h"
#include "server/zone/objects/ship/ai/bt/decorator/LookForTarget.h"
#include "server/zone/objects/ship/ai/bt/decorator/LookForPlayer.h"

#define _REGISTERSPACEBASE(name) factory.reg(#name, new SpaceBehaviorCreator<name>)
#define _REGISTERSPACENODE(name) factory.reg(#name, new SpaceBehaviorCreator<node::name>)
#define _REGISTERSPACELEAF(name) factory.reg(#name, new SpaceBehaviorCreator<leaf::name>)
#define _REGISTERSPACEDECO(name) factory.reg(#name, new SpaceBehaviorCreator<decorator::name>)

class SpaceBehaviorCreatorHelper {
public:
	virtual ~SpaceBehaviorCreatorHelper() {
	}
	virtual Behavior* create(const String&, const uint32, const LuaObject&) const = 0;
};

template <typename T>
class SpaceBehaviorCreator : public SpaceBehaviorCreatorHelper {
public:
	Behavior* create(const String& name, const uint32 id, const LuaObject& args) const {
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

	Behavior* create(const String& key, const uint32 id, const LuaObject& args) {
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
	HashTable<String, Reference<Behavior*>> spaceAiMap;
	// <ai bitmask, <treeID, root behavior> >
	VectorMap<uint32, VectorMap<BehaviorTreeSlot, Reference<Behavior*>>> bitmaskMap;
	VectorMap<uint64, VectorMap<BehaviorTreeSlot, Reference<Behavior*>>> customMap;

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
			info("Loading templates...", true);

		Lua* lua = new Lua();
		lua->init();
		lua->setLoggingName("SpaceAiMapLuaInstance");
		lua->setGlobalLogging(true);
		lua->setLogging(true);

		// SpaceAI
		lua->setGlobalInt("NONE", BehaviorTreeSlot::NONE);
		lua->setGlobalInt("AWARE", BehaviorTreeSlot::AWARE);
		lua->setGlobalInt("IDLE", BehaviorTreeSlot::IDLE);
		lua->setGlobalInt("ATTACK", BehaviorTreeSlot::ATTACK);

		lua_register(lua->getLuaState(), "includeFile", includeFile);
		lua_register(lua->getLuaState(), "addAiTemplate", addAiTemplate);
		lua->runFile("scripts/space_ai/templates.lua");

		putBitmask(lua, "bitmaskLookup");
		loadCustomMap(lua);

		delete lua;
	}

	int getTemplateSize() {
		return spaceAiMap.size();
	}

	// put the root node of a btree into this map
	void putTemplate(const String& name, Reference<Behavior*> ait) {
		spaceAiMap.put(name, ait);
	}

	// returns the root node of a behavior tree
	Behavior* getTemplate(const String& name) {
		if (name == "none")
			return NULL;

		return spaceAiMap.get(name);
	}

	// returns the root node of a behavior tree associated with the tree type (treeID)
	Behavior* getTemplate(uint32 bitMask, BehaviorTreeSlot treeID, uint64 customMapName = 0) {
		if (customMapName > 0) {
			auto treeMap = customMap.get(customMapName);
			if (treeMap.contains(treeID))
				return treeMap.get(treeID);
		}

		for (int mask = CreatureFlag::LASTAIMASK; (mask = mask >> 1) >= 0;) {
			if ((bitMask & mask) == mask && bitmaskMap.contains(mask)) {
				auto treeMap = bitmaskMap.get((uint32)(mask));
				if (treeMap.contains(treeID))
					return treeMap.get(treeID);
			}

			if (mask == 0)
				break;
		}

		SpaceAiMap::instance()->error("Failed to find Behavior for mask: " + String::valueOf(bitMask) + " and treeID: " + String::valueOf(treeID));
		return NULL;
	}

	Behavior* createBehavior(const String& name, const uint32 id, const LuaObject& args) {
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

			for (int i = 0; i < server->getZoneCount(); ++i) {
				Zone* zone = server->getZone(i);

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
		_REGISTERSPACEBASE(TreeSocket);
		// composite behaviors
		_REGISTERSPACENODE(Selector);
		_REGISTERSPACENODE(ParallelSelector);
		_REGISTERSPACENODE(RandomSelector);
		_REGISTERSPACENODE(Sequence);
		_REGISTERSPACENODE(ParallelSequence);
		_REGISTERSPACENODE(RandomSequence);
		// decorator behaviors
		_REGISTERSPACEDECO(AlwaysFail);
		_REGISTERSPACEDECO(AlwaysSucceed);
		_REGISTERSPACEDECO(If);
		_REGISTERSPACEDECO(Not);
		_REGISTERSPACEDECO(UntilFailure);
		_REGISTERSPACEDECO(UntilSuccess);
		_REGISTERSPACEDECO(LookForTarget);
		_REGISTERSPACEDECO(LookForPlayer);
		//_REGISTERDECO(LookForAllies);
		// check behaviors

		// action behaviors
		_REGISTERSPACELEAF(Dummy);
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

			VectorMap<BehaviorTreeSlot, Reference<Behavior*>> flagMap;
			flagMap.setNullValue(NULL);
			for (int j = 1; j <= table.getTableSize(); ++j) {
				LuaObject tableEntry = table.getObjectAt(j);
				if (!tableEntry.isValidTable()) {
					SpaceAiMap::instance()->error("Invalid entry in table: " + String::valueOf(flag));
					continue;
				}

				BehaviorTreeSlot treeNum = static_cast<BehaviorTreeSlot>(tableEntry.getIntAt(1));
				String tempName = tableEntry.getStringAt(2);
				tableEntry.pop();

				flagMap.put(treeNum, SpaceAiMap::instance()->getTemplate(tempName));
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

			VectorMap<BehaviorTreeSlot, Reference<Behavior*>> flagMap;
			flagMap.setNullValue(NULL);
			for (int j = 1; j <= table.getTableSize(); ++j) {
				LuaObject tableEntry = table.getObjectAt(j);
				if (!tableEntry.isValidTable()) {
					SpaceAiMap::instance()->error("Invalid custom map entry in table: " + stringKey);
					continue;
				}

				BehaviorTreeSlot treeNum = static_cast<BehaviorTreeSlot>(tableEntry.getIntAt(1));
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

	static int addAiTemplate(lua_State* L) {
		String name = lua_tostring(L, -2);

		if (DEBUG_MODE)
			SpaceAiMap::instance()->info("Including template: " + name, true);

		LuaObject obj(L);
		if (!obj.isValidTable()) {
			SpaceAiMap::instance()->error("Lua AI template not found: " + name);
			obj.pop();
			return 0;
		}

		Vector<Reference<Behavior*>> loadVec;
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

				// if (DEBUG_MODE)
				//	SpaceAiMap::instance()->info("Read Behavior: " + className, true);

				Behavior* b = SpaceAiMap::instance()->createBehavior(className, id, args);
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

		SpaceAiMap::instance()->putTemplate(name, root);

		if (DEBUG_MODE)
			SpaceAiMap::instance()->info("Loaded AI template " + name, true);

		obj.pop();
		return 0;
	}
};

#endif /* SPACEAIMAP_H_ */
