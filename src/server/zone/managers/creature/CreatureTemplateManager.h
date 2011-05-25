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

class CreatureTemplateManager : public Lua, public Singleton<CreatureTemplateManager>  {
protected:
	HashTable<uint32, Reference<CreatureTemplate*> > templates;

	VectorMap<uint32, Vector<String> > weaponMap;
	VectorMap<uint32, DynamicSpawnGroup*> dynamicGroupMap;
	VectorMap<uint32, StaticSpawnGroup*> staticGroupMap;

public:
	CreatureTemplateManager() : Lua(), Singleton<CreatureTemplateManager>(), templates(3000) {
		setLogging(false);
		setGlobalLogging(true);
		setLoggingName("CreatureTemplateManager");

		Lua::init();

		lua_register(getLuaState(), "includeFile", includeFile);
		lua_register(getLuaState(), "addTemplate", addTemplate);
		lua_register(getLuaState(), "addWeapon", addWeapon);
		lua_register(getLuaState(), "addDynamicGroup", addDynamicGroup);
		lua_register(getLuaState(), "addStaticGroup", addStaticGroup);

		setGlobalInt("NONE", CreatureFlag::NONE);
		setGlobalInt("ATTACKABLE", CreatureFlag::ATTACKABLE);
		setGlobalInt("AGGRESSIVE", CreatureFlag::AGGRESSIVE);
		setGlobalInt("OVERT", CreatureFlag::OVERT);
		setGlobalInt("TEF", CreatureFlag::TEF);
		setGlobalInt("PLAYER", CreatureFlag::PLAYER);
		setGlobalInt("ENEMY", CreatureFlag::ENEMY);
		setGlobalInt("CHANGEFACTIONSTATUS", CreatureFlag::CHANGEFACTIONSTATUS);
		setGlobalInt("BLINK_GREEN", CreatureFlag::BLINK_GREEN);

		setGlobalInt("PACK", CreatureFlag::PACK);
		setGlobalInt("HERD", CreatureFlag::HERD);
		setGlobalInt("KILLER", CreatureFlag::KILLER);
		setGlobalInt("STALKER", CreatureFlag::STALKER);
		setGlobalInt("BABY", CreatureFlag::BABY);
		setGlobalInt("LAIR", CreatureFlag::LAIR);

		setGlobalInt("CARNIVORE", CreatureFlag::CARNIVORE);
		setGlobalInt("HERBIVORE", CreatureFlag::HERBIVORE);
	}

	virtual ~CreatureTemplateManager() {
	}

	void loadTemplates() {
		info("loading mobile templates...", true);

		try {
			runFile("scripts/mobile/creatures.lua");
		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		}

		info("done loading mobile templates", true);
	}

	void addTemplate(uint32 crc, CreatureTemplate* templ) {
		templates.put(crc, templ);
	}

	CreatureTemplate* getTemplate(uint32 crc) {
		return templates.get(crc);
	}

	CreatureTemplate* getTemplate(String ascii) {
		return templates.get(ascii.hashCode());
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

		CreatureTemplateManager::instance()->addTemplate(crc, newTemp);

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

	HashTableIterator<uint32, Reference<CreatureTemplate*> > iterator() {
		return templates.iterator();
	}

	int size() {
		return templates.size();
	}
};

}
}
}
}

#endif /* CREATURETEMPLATEMANAGER_H_ */
