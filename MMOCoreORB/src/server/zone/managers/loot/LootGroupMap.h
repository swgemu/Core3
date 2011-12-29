/*
 * LootGroupMap.h
 *
 *  Created on: Jun 24, 2011
 *      Author: kyle
 */

#ifndef LOOTGROUPMAP_H_
#define LOOTGROUPMAP_H_

#include "engine/engine.h"
#include "lootgroup/LootGroup.h"
#include "lootitems/LootItems.h"

class LootGroupMap : public HashTable<String, Reference<LootGroup*> >, public Singleton<LootGroupMap>, public Object {
public:
	static Lua* lua;
	LootItems lootItemMap;

public:
	LootGroupMap();
	virtual ~LootGroupMap();

	void initialize();

	LootItemTemplate* getLootItem(const String& name) {
		return lootItemMap.get(name);
	}

private:
	//LUA
	void registerFunctions();
	void registerGlobals();
	static int includeFile(lua_State* L);
	static int addLootGroupTemplate(lua_State* L);
	static int addLootItemTemplate(lua_State* L);
};

#endif /* LOOTGROUPMAP_H_ */
