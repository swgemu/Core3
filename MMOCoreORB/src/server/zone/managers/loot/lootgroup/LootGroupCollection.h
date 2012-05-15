/*
 * LootGroupCollection.h
 *
 *  Created on: Jan 16, 2012
 *      Author: xyborn
 */

#ifndef LOOTGROUPCOLLECTION_H_
#define LOOTGROUPCOLLECTION_H_

#include "engine/engine.h"
#include "LootGroupCollectionEntry.h"

class LootGroupCollection {
	Vector<LootGroupCollectionEntry> entries;

public:
	LootGroupCollection() {
	}

	void readObject(LuaObject* obj) {
		if (!obj->isValidTable())
			return;

		lua_State* L = obj->getLuaState();

		for (int i = 1; i <= obj->getTableSize(); ++i) {
			lua_rawgeti(L, -1, i);

			LuaObject luacollection(L);

			LootGroupCollectionEntry entry;
			entry.readObject(&luacollection);

			entries.add(entry);

			luacollection.pop();
		}
	}

	inline int count() {
		return entries.size();
	}

	LootGroupCollectionEntry* get(int i) {
		if (i < 0 || i >= entries.size())
			return NULL;

		return &entries.get(i);
	}
};


#endif /* LOOTGROUPCOLLECTION_H_ */
