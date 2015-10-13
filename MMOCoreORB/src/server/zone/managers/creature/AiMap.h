/*
 * AiMap.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef AIMAP_H_
#define AIMAP_H_

#include "engine/engine.h"

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/CreatureFlag.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

// include all behaviors we want to register
#include "server/zone/objects/creature/ai/bt/node/Selector.h"
#include "server/zone/objects/creature/ai/bt/node/Sequence.h"
#include "server/zone/objects/creature/ai/bt/leaf/Checks.h"
#include "server/zone/objects/creature/ai/bt/decorator/Not.h"

#define _REGISTERNODE(name) factory.reg(#name, new BehaviorCreator<server::zone::objects::creature::ai::bt::node::name>)
#define _REGISTERLEAF(name) factory.reg(#name, new BehaviorCreator<server::zone::objects::creature::ai::bt::leaf::name>)
#define _REGISTERDECO(name) factory.reg(#name, new BehaviorCreator<server::zone::objects::creature::ai::bt::decorator::name>)

class BehaviorCreatorHelper {
public:
	virtual Behavior* create(const String&, const uint32, const String&) const = 0;
};

template <typename T>
class BehaviorCreator : public BehaviorCreatorHelper {
public:
	Behavior* create(const String& name, const uint32 id, const String& args) const {
		return new T(name, id, args);
	}
};

class BehaviorFactory {
public:
	~BehaviorFactory() {
		for (int idx = 0; idx < fnMap.size(); ++idx)
			delete fnMap.get(idx);
	}
	
	void reg(const String& key, const BehaviorCreatorHelper* fn) {
		if (!fnMap.containsKey(key))
			fnMap.put(key, fn);
	}
	
	Behavior* create(const String& key, const uint32 id, const String& args) {
		if (!fnMap.containsKey(key) || fnMap.get(key) == NULL)
			return NULL;

		return fnMap.get(key)->create(key, id, args);
	}

private:
	HashTable<String, const BehaviorCreatorHelper*> fnMap;
};

class AiMap : public Singleton<AiMap>, public Logger, public Object {
public:
	HashTable<String, Reference<Behavior*> > aiMap;
	HashTable<unsigned int, Reference<Behavior*> > getTargets;
	HashTable<unsigned int, Reference<Behavior*> > selectAttacks;
	HashTable<unsigned int, Reference<Behavior*> > combatMoves;
	HashTable<unsigned int, Reference<Behavior*> > idles;
	bool loaded;

	AtomicInteger activeMoveEvents;
	AtomicInteger scheduledMoveEvents;
	AtomicInteger moveEventsWithFollowObject;
	AtomicInteger moveEventsRetreating;

	AtomicInteger activeAwarenessEvents;
	AtomicInteger scheduledAwarenessEvents;

	AtomicInteger activeRecoveryEvents;
	AtomicInteger activeWaitEvents;

	AiMap() : Logger("AiMap") {
		aiMap.setNullValue(NULL);
		getTargets.setNullValue(NULL);
		selectAttacks.setNullValue(NULL);
		combatMoves.setNullValue(NULL);
		idles.setNullValue(NULL);

		loaded = false;
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

		lua_register(lua->getLuaState(), "includeFile", includeFile);
		lua_register(lua->getLuaState(), "addAiTemplate", addAiTemplate);
		lua->runFile("scripts/ai/templates.lua");

		putTemplate(lua, "getTarget", &getTargets);
		putTemplate(lua, "selectAttack", &selectAttacks);
		putTemplate(lua, "combatMove", &combatMoves);
		putTemplate(lua, "idle", &idles);
		loaded = true;
	}

	bool isLoaded() {
		return loaded;
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
	
	Behavior* createBehavior(const String& name, const uint32 id, const String& args) {
		return factory.create(name, id, args);
	}

	// returns the root node of a behavior tree
	Behavior* getGetTargetTemplate(unsigned int bitMask) {
		return getTemplate(bitMask, getTargets);
	}

	// returns the root node of a behavior tree
	Behavior* getSelectAttackTemplate(unsigned int bitMask) {
		return getTemplate(bitMask, selectAttacks);
	}

	// returns the root node of a behavior tree
	Behavior* getCombatMoveTemplate(unsigned int bitMask) {
		return getTemplate(bitMask, combatMoves);
	}

	// returns the root node of a behavior tree
	Behavior* getIdleTemplate(unsigned int bitMask) {
		return getTemplate(bitMask, idles);
	}

private:
	static const bool DEBUG_MODE = false;
	BehaviorFactory factory;
	
	void registerBehaviors() {
		// composite behaviors
		_REGISTERNODE(Selector);
		_REGISTERNODE(Sequence);
		// decorator behaviors
		_REGISTERDECO(Not);
		// check behaviors
		_REGISTERLEAF(CheckPosture);
		_REGISTERLEAF(CheckDestination);
		_REGISTERLEAF(CheckFollowState);
		//_REGISTERLEAF(CheckLastCommand);
		// action behaviors
	}

	void putTemplate(Lua* lua, String key, HashTable<unsigned int, Reference<Behavior*> >* table) {
		LuaObject obj = lua->getGlobalObject(key);
		if (obj.isValidTable()) {
			for (int i = 1; i <= obj.getTableSize(); i++) {
				lua_rawgeti(lua->getLuaState(), -1, i);
				LuaObject temp(lua->getLuaState());
				table->put(temp.getIntAt(1), AiMap::instance()->getTemplate(temp.getStringAt(2)));
				temp.pop();
			}
		}
	}

	Behavior* getTemplate(unsigned int bitMask, HashTable<unsigned int, Reference<Behavior*> > table) {
		HashTableIterator<unsigned int, Reference<Behavior*> > iter = table.iterator();

		unsigned int finalKey = CreatureFlag::NONE;

		while (iter.hasNext()) {
			unsigned int key = iter.getNextKey();

			if ((key & bitMask) == key && finalKey < key)
				finalKey = key;
		}

		return table.get(finalKey);
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

		LuaObject obj(L);
		if (!obj.isValidTable()) {
			AiMap::instance()->error("Lua AI template not found: " + name);
			obj.pop();
			return 0;
		}
		
		VectorMap<uint32, Behavior*> loadMap;
		VectorMap<uint32, uint32> parentMap;
		
		for (int i = 1; i <= obj.getTableSize(); ++i) {
			lua_rawgeti(L, -1, i);
			LuaObject behavior(L);

			uint32 id = behavior.getStringAt(1).hashCode();
			String className = behavior.getStringAt(2);
			uint32 parent = behavior.getStringAt(3).hashCode();
			String args = behavior.getStringAt(4);
			
			Behavior* b = AiMap::instance()->createBehavior(className, id, args);
			loadMap.put(id, b);
			parentMap.put(id, parent);

			behavior.pop();
		}
		
		for (int idx = 0; idx < loadMap.size(); ++idx) {
			VectorMapEntry<uint32, Behavior*>* entry = &loadMap.elementAt(idx);
			Reference<Behavior*> child = entry->getValue();
			if (child == NULL)
				continue;
			
			uint32 parentID = parentMap.get(child->getID());
			if (parentID == STRING_HASHCODE("none")) // this is the root
				continue;
			
			Reference<Behavior*> parent = loadMap.get(parentID);
			child->setParent(parent); // this method asserts that parent is proper
			
			if (parent->isComposite())
				static_cast<Composite*>(parent)->addChild(child);
			else if (parent->isDecorator())
				static_cast<Decorator*>(parent)->setChild(child);
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
