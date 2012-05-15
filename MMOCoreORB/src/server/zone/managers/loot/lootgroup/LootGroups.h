/*
 * LootGroups.h
 *
 *  Created on: Jan 30, 2012
 *      Author: xyborn
 */

#ifndef LOOTGROUPS_H_
#define LOOTGROUPS_H_

#include "engine/engine.h"
#include "LootGroupEntry.h"

class LootGroups {
	SortedVector<LootGroupEntry> entries;

public:
	LootGroups() {
	}

	void readObject(LuaObject* obj) {
		if (!obj->isValidTable())
			return;

		lua_State* L = obj->getLuaState();

		for (int i = 1; i <= obj->getTableSize(); ++i) {
			lua_rawgeti(L, -1, i);

			LuaObject luagroup(L);

			LootGroupEntry entry;
			entry.readObject(&luagroup);

			put(entry);

			luagroup.pop();
		}
	}

	void put(const LootGroupEntry& entry) {
		entries.put(entry);
	}

	int count() {
		return entries.size();
	}

	LootGroupEntry* get(int idx) {
		return &entries.get(idx);
	}
};


#endif /* LOOTGROUPS_H_ */
