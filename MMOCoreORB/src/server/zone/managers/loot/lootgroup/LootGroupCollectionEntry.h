/*
 * LootGroupCollectionEntry.h
 *
 *  Created on: Jan 30, 2012
 *      Author: xyborn
 */

#ifndef LOOTGROUPCOLLECTIONENTRY_H_
#define LOOTGROUPCOLLECTIONENTRY_H_

#include "engine/engine.h"
#include "LootGroups.h"

class LootGroupCollectionEntry : public Object {
	LootGroups lootGroups;

	int lootChance;

public:
	LootGroupCollectionEntry() {
		lootChance = 0;
	}

	LootGroupCollectionEntry(const LootGroupCollectionEntry& lgce) : Object() {
		lootGroups = lgce.lootGroups;
		lootChance = lgce.lootChance;
	}

	LootGroupCollectionEntry& operator=(const LootGroupCollectionEntry& lgce) {
		if (this == &lgce)
			return *this;

		lootGroups = lgce.lootGroups;
		lootChance = lgce.lootChance;

		return *this;
	}

	void readObject(LuaObject* lua) {
		lootChance = lua->getIntField("lootChance");

		LuaObject luagroups = lua->getObjectField("groups");
		lootGroups.readObject(&luagroups);

		luagroups.pop();
	}

	inline int getLootChance() {
		return lootChance;
	}

	LootGroups* getLootGroups() {
		return &lootGroups;
	}
};


#endif /* LOOTGROUPCOLLECTIONENTRY_H_ */
