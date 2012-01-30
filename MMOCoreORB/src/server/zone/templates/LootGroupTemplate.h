/*
 * LootGroupTemplate.h
 *
 *  Created on: Jan 30, 2012
 *      Author: xyborn
 */

#ifndef LOOTGROUPTEMPLATE_H_
#define LOOTGROUPTEMPLATE_H_

#include "engine/engine.h"

class LootGroupTemplate : public Object {
	String templateName;

	VectorMap<String, int> itemMap;

public:
	LootGroupTemplate(const String& name) {
		templateName = name;

		itemMap.setNoDuplicateInsertPlan();
		itemMap.setNullValue(0);
	}

	LootGroupTemplate(const LootGroupTemplate& lgt) : Object() {
		templateName = lgt.templateName;

		itemMap = lgt.itemMap;
	}

	LootGroupTemplate& operator=(const LootGroupTemplate& lgt) {
		if (this == &lgt)
			return *this;

		templateName = lgt.templateName;
		itemMap = lgt.itemMap;

		return *this;
	}

	String getLootItemTemplateForRoll(int roll) {
		int totalChance = 0;

		for (int i = 0; i < itemMap.size(); ++i) {
			VectorMapEntry<String, int>* entry = &itemMap.elementAt(i);

			totalChance += entry->getValue();

			if (totalChance >= roll)
				return entry->getKey();
		}

		//Should never get here unless the scripts didn't add up to 10000000.
		return "";
	}

	void readObject(LuaObject* lua) {
		LuaObject lootItems = lua->getObjectField("lootItems");

		if (!lootItems.isValidTable())
			return;

		lua_State* L = lua->getLuaState();

		for (int i = 1; i <= lootItems.getTableSize(); ++i) {
			lua_rawgeti(L, -1, i);
			LuaObject lootItem(L);

			String itemTemplate = lootItem.getStringField("itemTemplate");
			int chance = lootItem.getIntField("weight");

			itemMap.put(itemTemplate, chance);

			lootItem.pop();
		}

		lootItems.pop();
	}
};


#endif /* LOOTGROUPTEMPLATE_H_ */
