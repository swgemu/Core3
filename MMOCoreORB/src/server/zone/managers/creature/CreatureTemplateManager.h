/*
 * CreatureTemplateMap.h
 *
 *  Created on: Oct 8, 2010
 *      Author: dannuic
 */

#ifndef CREATURETEMPLATEMANAGER_H_
#define CREATURETEMPLATEMANAGER_H_

#include "engine/engine.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/templates/mobile/ConversationTemplate.h"
#include "server/zone/templates/mobile/LairTemplate.h"
#include "server/zone/templates/mobile/PatrolPathTemplate.h"
#include "server/zone/templates/mobile/MobileOutfitGroup.h"
#include "SpawnGroup.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class CreatureTemplateManager : public Singleton<CreatureTemplateManager>, public Object, public Logger {
protected:
	VectorMap<uint32, Vector<String> > weaponMap;
	Reference<Lua*> lua;
	HashTable<uint32, Reference<CreatureTemplate*> > hashTable;

	HashTable<uint32, Reference<ConversationTemplate*> > conversations;

	HashTable<uint32, Reference<LairTemplate*> > lairTemplates;
	HashTable<uint32, Reference<SpawnGroup*> > spawnGroupMap;
	HashTable<uint32, Reference<SpawnGroup*> > destroyMissionGroupMap;
	HashTable<String, Reference<PatrolPathTemplate*> > patrolPaths;
	HashTable<String, Reference<MobileOutfitGroup*> > outfits;
	static AtomicInteger loadedMobileTemplates;

public:
	static int DEBUG_MODE;
	enum LUA_ERROR_CODE { NO_ERROR = 0, GENERAL_ERROR, DUPLICATE_MOBILE, INCORRECT_ARGUMENTS };
	static int ERROR_CODE;

public:
	CreatureTemplateManager();
	virtual ~CreatureTemplateManager();

	int loadTemplates();
	static int includeFile(lua_State* L);
	static int addTemplate(lua_State* L);
	static int addWeapon(lua_State* L);
	static int addSpawnGroup(lua_State* L);
	static int addDestroyMissionGroup(lua_State* L);
	static int addConversationTemplate(lua_State* L);
	static int addLairTemplate(lua_State* L);
	static int addPatrolPathTemplate(lua_State* L);
	static int addOutfitGroup(lua_State* L);

	static int checkArgumentCount(lua_State* L, int args);

	int size() {
		return hashTable.size();
	}

	HashTableIterator<uint32, Reference<CreatureTemplate*> > iterator() {
		return hashTable.iterator();
	}

	HashTableIterator<uint32, Reference<LairTemplate*> > lairTemplateIterator() {
		return lairTemplates.iterator();
	}

	HashTableIterator<uint32, Reference<SpawnGroup*> > spawnGroupIterator() {
		return spawnGroupMap.iterator();
	}

	HashTableIterator<uint32, Reference<SpawnGroup*> > destroyMissionGroupIterator() {
		return destroyMissionGroupMap.iterator();
	}

	CreatureTemplate* getTemplate(uint32 crc) {
		return hashTable.get(crc);
	}

	PatrolPathTemplate* getPatrolPathTemplate(const String& name) {
		return patrolPaths.get(name);
	}

	CreatureTemplate* getTemplate(const String& ascii) {
		return hashTable.get(ascii.hashCode());
	}

	MobileOutfitGroup* getMobileOutfitGroup(const String& name) {
		return outfits.get(name);
	}

	ConversationTemplate* getConversationTemplate(const String& name) {
		return conversations.get(name.hashCode()).get();
	}

	ConversationTemplate* getConversationTemplate(uint32 crc) {
		return conversations.get(crc).get();
	}

	Vector<String> getWeapons(uint32 crc) {
		return weaponMap.get(crc);
	}

	Vector<String> getWeapons(String ascii) {
		return weaponMap.get(ascii.hashCode());
	}

	SpawnGroup* getSpawnGroup(uint32 crc) {
		return spawnGroupMap.get(crc);
	}

	LairTemplate* getLairTemplate(uint32 crc) {
		return lairTemplates.get(crc);
	}

	SpawnGroup* getDestroyMissionGroup(uint32 crc) {
		return destroyMissionGroupMap.get(crc);
	}

};

}
}
}
}

using namespace server::zone::managers::creature;

#endif /* CREATURETEMPLATEMANAGER_H_ */
