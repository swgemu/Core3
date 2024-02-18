/*
 * LootGroupMap.h
 *
 *  Created on: Jun 24, 2011
 *      Author: xyborn
 */

#ifndef LOOTGROUPMAP_H_
#define LOOTGROUPMAP_H_

class LootItemTemplate;

#include "templates/LootGroupTemplate.h"

#include "engine/log/Logger.h"
#include "engine/util/Singleton.h"
#include "engine/lua/Lua.h"

class LootGroupMap : public Singleton<LootGroupMap>, public Object, public Logger {
public:
	static Lua* lua;

#ifdef PLATFORM_WIN
#undef NO_ERROR
#endif

	enum LUA_ERROR_CODE { NO_ERROR = 0, GENERAL_ERROR };
	static int ERROR_CODE;

	HashTable<String, Reference<LootItemTemplate*> > itemTemplates;
	HashTable<String, Reference<LootGroupTemplate*> > groupTemplates;

public:
	LootGroupMap();
	virtual ~LootGroupMap();

	int initialize();

	inline void putLootItemTemplate(const String& name, LootItemTemplate* item) {
		itemTemplates.put(name, item);
	}

	inline void putLootGroupTemplate(const String& name, LootGroupTemplate* group) {
		groupTemplates.put(name, group);
	}

	const LootGroupTemplate* getLootGroupTemplate(const String& name) const {
		return groupTemplates.get(name);
	}

	const LootItemTemplate* getLootItemTemplate(const String& name) const {
		return itemTemplates.get(name);
	}

	inline int countLootItemTemplates() const {
		return itemTemplates.size();
	}

	inline int countLootGroupTemplates() const {
		return groupTemplates.size();
	}

	bool lootGroupExists(const String& group) const {
		return groupTemplates.containsKey(group);
	}

	bool lootItemExists(const String& item) const {
		return itemTemplates.containsKey(item);
	}

private:
	static String currentFilename;

	void registerFunctions();
	void registerGlobals();

	static int includeFile(lua_State* L);

	static int addLootGroupTemplate(lua_State* L);
	static int addLootItemTemplate(lua_State* L);
};

#endif /* LOOTGROUPMAP_H_ */
