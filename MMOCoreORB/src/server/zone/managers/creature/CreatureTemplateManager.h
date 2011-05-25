/*
 * CreatureTemplateMap.h
 *
 *  Created on: Oct 8, 2010
 *      Author: dannuic
 */

#ifndef CREATURETEMPLATEMANAGER_H_
#define CREATURETEMPLATEMANAGER_H_

#include "engine/engine.h"
#include "CreatureTemplate.h"
#include "SpawnGroup.h"
#include "StaticSpawnGroup.h"
#include "DynamicSpawnGroup.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class CreatureTemplateManager : public Singleton<CreatureTemplateManager>, public Object, public Logger {
protected:
	VectorMap<uint32, Vector<String> > weaponMap;
	VectorMap<uint32, DynamicSpawnGroup*> dynamicGroupMap;
	VectorMap<uint32, StaticSpawnGroup*> staticGroupMap;
	Lua* lua;
	HashTable<uint32, Reference<CreatureTemplate*> > hashTable;

public:
	CreatureTemplateManager() : Logger("CreatureTemplateManager") {
		/*setLogging(false);
		setGlobalLogging(true);*/
		//setLoggingName("CreatureTemplateManager");

		lua = new Lua();
		lua->init();
		hashTable.setNullValue(NULL);

		lua_register(lua->getLuaState(), "includeFile", includeFile);
		lua_register(lua->getLuaState(), "addTemplate", addTemplate);
		lua_register(lua->getLuaState(), "addWeapon", addWeapon);
		lua_register(lua->getLuaState(), "addDynamicGroup", addDynamicGroup);
		lua_register(lua->getLuaState(), "addStaticGroup", addStaticGroup);

		lua->setGlobalInt("NONE", CreatureFlag::NONE);
		lua->setGlobalInt("ATTACKABLE", CreatureFlag::ATTACKABLE);
		lua->setGlobalInt("AGGRESSIVE", CreatureFlag::AGGRESSIVE);
		lua->setGlobalInt("OVERT", CreatureFlag::OVERT);
		lua->setGlobalInt("TEF", CreatureFlag::TEF);
		lua->setGlobalInt("PLAYER", CreatureFlag::PLAYER);
		lua->setGlobalInt("ENEMY", CreatureFlag::ENEMY);
		lua->setGlobalInt("CHANGEFACTIONSTATUS", CreatureFlag::CHANGEFACTIONSTATUS);
		lua->setGlobalInt("BLINK_GREEN", CreatureFlag::BLINK_GREEN);

		lua->setGlobalInt("PACK", CreatureFlag::PACK);
		lua->setGlobalInt("HERD", CreatureFlag::HERD);
		lua->setGlobalInt("KILLER", CreatureFlag::KILLER);
		lua->setGlobalInt("STALKER", CreatureFlag::STALKER);
		lua->setGlobalInt("BABY", CreatureFlag::BABY);
		lua->setGlobalInt("LAIR", CreatureFlag::LAIR);

		lua->setGlobalInt("CARNIVORE", CreatureFlag::CARNIVORE);
		lua->setGlobalInt("HERBIVORE", CreatureFlag::HERBIVORE);
	}

	virtual ~CreatureTemplateManager() {
	}

	void loadTemplates() {
		info("loading mobile templates...", true);

		try {
			lua->runFile("scripts/mobile/creatures.lua");
		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		}

		info("done loading mobile templates", true);
	}

	int size() {
		return hashTable.size();
	}

	HashTable<uint32, Reference<CreatureTemplate*> >* getHashTable() {
		return &hashTable;
	}

	CreatureTemplate* getTemplate(uint32 crc) {
		return hashTable.get(crc);
	}

	CreatureTemplate* getTemplate(String ascii) {
		return hashTable.get(ascii.hashCode());
	}

	Vector<String> getWeapons(uint32 crc) {
		return weaponMap.get(crc);
	}

	Vector<String> getWeapons(String ascii) {
		return weaponMap.get(ascii.hashCode());
	}

	DynamicSpawnGroup* getDynamicGroup(uint32 crc) {
		return dynamicGroupMap.get(crc);
	}

	DynamicSpawnGroup* getDynamicGroup(String ascii) {
		return dynamicGroupMap.get(ascii.hashCode());
	}

	StaticSpawnGroup* getStaticGroup(uint32 crc) {
		return staticGroupMap.get(crc);
	}

	StaticSpawnGroup* getStaticGroup(String ascii) {
		return staticGroupMap.get(ascii.hashCode());
	}

	static int includeFile(lua_State* L) {
		String filename = Lua::getStringParameter(L);

		Lua::runFile("scripts/mobile/" + filename, L);

		return 0;
	}

	static int addTemplate(lua_State* L) {
		String ascii =  lua_tostring(L, -2);
		uint32 crc = (uint32) ascii.hashCode();

		LuaObject obj(L);
		CreatureTemplate* newTemp = new CreatureTemplate();
		newTemp->setTemplateName(ascii);
		newTemp->readObject(&obj);

		CreatureTemplateManager::instance()->hashTable.put(crc, newTemp);

		return 0;
	}

	static int addWeapon(lua_State* L) {
		String ascii = lua_tostring(L, -2);
		uint32 crc = (uint32) ascii.hashCode();

		LuaObject obj(L);
		if (obj.isValidTable()) {
			Vector<String> weps;
			for (int i = 1; i <= obj.getTableSize(); ++i)
				weps.add(obj.getStringAt(i));

			CreatureTemplateManager::instance()->weaponMap.put(crc, weps);
		}

		return 0;
	}

	static int addDynamicGroup(lua_State* L) {
		String ascii = lua_tostring(L, -2);
		uint32 crc = (uint32) ascii.hashCode();

		LuaObject obj(L);
		CreatureTemplateManager::instance()->dynamicGroupMap.put(crc, new DynamicSpawnGroup(ascii, obj));

		return 0;
	}

	static int addStaticGroup(lua_State* L) {
		String ascii = lua_tostring(L, -2);
		uint32 crc = (uint32) ascii.hashCode();

		LuaObject obj(L);
		CreatureTemplateManager::instance()->staticGroupMap.put(crc, new StaticSpawnGroup(ascii, obj));

		return 0;
	}
};

}
}
}
}

#endif /* CREATURETEMPLATEMANAGER_H_ */
