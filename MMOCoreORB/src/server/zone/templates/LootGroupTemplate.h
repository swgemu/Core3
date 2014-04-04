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

	VectorMap<String, int> entryMap;

public:
	LootGroupTemplate(const String& name) {
		templateName = name;

		entryMap.setNoDuplicateInsertPlan();
		entryMap.setNullValue(0);
	}

	LootGroupTemplate(const LootGroupTemplate& lgt) : Object() {
		templateName = lgt.templateName;

		entryMap.setNoDuplicateInsertPlan();
		entryMap.setNullValue(0);

		entryMap = lgt.entryMap;
	}

	LootGroupTemplate& operator=(const LootGroupTemplate& lgt) {
		if (this == &lgt)
			return *this;

		templateName = lgt.templateName;
		entryMap = lgt.entryMap;

		return *this;
	}

	String getLootGroupEntryForRoll(int roll) {
		int totalChance = 0;

		for (int i = 0; i < entryMap.size(); ++i) {
			VectorMapEntry<String, int>* entry = &entryMap.elementAt(i);

			totalChance += entry->getValue();

			if (totalChance >= roll)
				return entry->getKey();
		}

		//Should never get here unless the scripts didn't add up to 10000000.
		return "";
	}

	int size(){
		return entryMap.size();
	}

	String getLootGroupEntryAt( int i ){

		if( i < 0 )
			return "";

		if( i >= entryMap.size() )
			return "";

		VectorMapEntry<String, int>* entry = &entryMap.elementAt(i);
		return entry->getKey();

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
			String groupTemplate = lootItem.getStringField("groupTemplate");
			int chance = lootItem.getIntField("weight");

			if (itemTemplate.isEmpty())
				entryMap.put(groupTemplate, chance);
			else
				entryMap.put(itemTemplate, chance);

			lootItem.pop();
		}

		lootItems.pop();
	}

	String& getTemplateName() {
		return templateName;
	}
};


#endif /* LOOTGROUPTEMPLATE_H_ */
