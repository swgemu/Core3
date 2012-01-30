/*
 * LootGroupMap.h
 *
 *  Created on: Jun 24, 2011
 *      Author: xyborn
 */

#ifndef LOOTGROUPMAP_H_
#define LOOTGROUPMAP_H_

#include "engine/engine.h"

class LootItemTemplate;
//class LootGroupTemplate;
#include "server/zone/templates/LootGroupTemplate.h"

class LootGroupMap : public Singleton<LootGroupMap>, public Object {
public:
	static Lua* lua;

	HashTable<String, Reference<LootItemTemplate*> > itemTemplates;
	HashTable<String, Reference<LootGroupTemplate*> > groupTemplates;

public:
	LootGroupMap();
	virtual ~LootGroupMap();

	void initialize();

	inline void putLootItemTemplate(const String& name, LootItemTemplate* item) {
		itemTemplates.put(name, item);
	}

	inline void putLootGroupTemplate(const String& name, LootGroupTemplate* group) {
		groupTemplates.put(name, group);
	}

	LootGroupTemplate* getLootGroupTemplate(const String& name) {
		return groupTemplates.get(name);
	}

	LootItemTemplate* getLootItemTemplate(const String& name) {
		return itemTemplates.get(name);
	}

	inline int countLootItemTemplates() {
		return itemTemplates.size();
	}

	inline int countLootGroupTemplates() {
		return groupTemplates.size();
	}

private:
	void registerFunctions();
	void registerGlobals();

	static int includeFile(lua_State* L);

	static int addLootGroupTemplate(lua_State* L);
	static int addLootItemTemplate(lua_State* L);
};

#endif /* LOOTGROUPMAP_H_ */
