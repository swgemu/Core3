/*
 * LootGroup.cpp
 *
 *  Created on: Jun 24, 2011
 *      Author: kyle
 */

#include "LootGroup.h"

LootGroup::LootGroup() : Logger("LootGroup") {
	// TODO Auto-generated constructor stub

}

LootGroup::~LootGroup() {
	// TODO Auto-generated destructor stub
}

void LootGroup::parseLua(lua_State* L) {
	LuaObject obj(L);

	int minLevel = obj.getIntField("minimumLevel");
	int maxLevel = obj.getIntField("maximumLevel");

	LuaObject luaItems = obj.getObjectField("lootItems");

	for (int i = 1; i <= luaItems.getTableSize(); ++i) {
		lua_rawgeti(L, -1, i);
		LuaObject luaObject(L);

		String itemTemplate = luaObject.getStringField("itemTemplate");
		int weight = luaObject.getIntField("weight");

		luaObject.pop();

		LootGroupEntry entry(itemTemplate, weight);

		put(entry);
	}

	luaItems.pop();

	normalizeWeights();
}

void LootGroup::normalizeWeights() {
	int sum = 0;

	for (int i = 0; i < size(); ++i)
		sum += (&get(i))->getWeight();

	if (sum != EXPECTED_SUM)
		warning("Loot group's sum weight is not equal to the expected amount.");
}
