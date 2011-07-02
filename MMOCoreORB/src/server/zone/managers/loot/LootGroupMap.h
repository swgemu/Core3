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

class LootGroupMap : public VectorMap<String, LootGroup*> {
public:
	static Lua* lua;

public:
	LootGroupMap();
	virtual ~LootGroupMap();

	void initialize();

private:
	//LUA
	void registerFunctions();
	void registerGlobals();
	static int includeFile(lua_State* L);
	static int addLootGroupTemplate(lua_State* L);
};

#endif /* LOOTGROUPMAP_H_ */
