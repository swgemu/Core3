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

namespace server {
namespace zone {
namespace managers {
namespace creature {

class CreatureTemplateManager : private HashTable<uint32, Reference<CreatureTemplate*> >, private HashTableIterator<uint32, Reference<CreatureTemplate*> >, private Lua, public Singleton<CreatureTemplateManager> {
protected:
	VectorMap<uint32, Vector<String> > weaponMap;
	VectorMap<uint32, SpawnGroup> groupMap;

	int hash(const uint32& key) {
		return Integer::hashCode(key);
	}

public:
	CreatureTemplateManager() : HashTable<uint32,Reference<CreatureTemplate*> >(3000), HashTableIterator<uint32, Reference<CreatureTemplate*> >(this), Lua(), Singleton<CreatureTemplateManager>() {
		setLogging(false);
		setGlobalLogging(true);
		setLoggingName("CreatureTemplateManager");

		Lua::init();
		setNullValue(NULL);

		lua_register(getLuaState(), "includeFile", includeFile);
		lua_register(getLuaState(), "addTemplate", addTemplate);
		lua_register(getLuaState(), "addWeapon", addWeapon);
		lua_register(getLuaState(), "addGroup", addGroup);

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
		/*resetIterator();

		while (hasNext()) {
			CreatureTemplate* npcTemp = next();

			delete npcTemp;
		}*/
	}

	void loadTemplates() {
		info("loading mobile templates...", true);

		try {
			runFile("scripts/mobile/creatures.lua");
		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		} catch (...) {
			error("unreported exception caught while loading templates");
		}

		info("done loading mobile templates", true);
	}

	CreatureTemplate* getTemplate(uint32 crc) {
		return get(crc);
	}

	CreatureTemplate* getTemplate(String ascii) {
		return get(ascii.hashCode());
	}

	Vector<String> getWeapons(uint32 crc) {
		return weaponMap.get(crc);
	}

	Vector<String> getWeapons(String ascii) {
		return weaponMap.get(ascii.hashCode());
	}

	SpawnGroup getGroup(uint32 crc) {
		return groupMap.get(crc);
	}

	SpawnGroup getGroup(String ascii) {
		return groupMap.get(ascii.hashCode());
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

		CreatureTemplateManager::instance()->put(crc, newTemp);

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

	static int addGroup(lua_State* L) {
		String ascii = lua_tostring(L, -2);
		uint32 crc = (uint32) ascii.hashCode();

		LuaObject obj(L);
		CreatureTemplateManager::instance()->groupMap.put(crc, SpawnGroup(ascii, obj));

		return 0;
	}
};

}
}
}
}

#endif /* CREATURETEMPLATEMANAGER_H_ */
