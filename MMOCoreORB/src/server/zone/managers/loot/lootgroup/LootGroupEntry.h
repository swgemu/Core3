/*
 * LootGroupEntry.h
 *
 *  Created on: Dec 29, 2011
 *      Author: xyborn
 */

#ifndef LOOTGROUPENTRY_H_
#define LOOTGROUPENTRY_H_

class LootGroupEntry : public Object {
	String templateName;
	int lootChance;

public:
	LootGroupEntry() {
		lootChance = 0;
	}

	LootGroupEntry(const String& name, int chance) {
		templateName = name;
		lootChance = chance;
	}

	LootGroupEntry(const LootGroupEntry& entry) : Object(), templateName(entry.templateName), lootChance(entry.lootChance) {
	}

	void readObject(LuaObject* lua) {
		templateName = lua->getStringField("group");
		lootChance = lua->getIntField("chance");
	}

	/**
	 * Loot Group Entries are sorted by their weights, in descending order. Thus, the greatest weight will be first.
	 * @param lge The loot group entry to compare.
	 */
	int compareTo(const LootGroupEntry& lge) const {
		if (lootChance < lge.lootChance)
			return 1;
		else if (lootChance > lge.lootChance)
			return -1;
		else
			return 0;
	}

	LootGroupEntry& operator=(const LootGroupEntry& lge) {
		if (this == &lge)
			return *this;

		templateName = lge.templateName;
		lootChance = lge.lootChance;

		return *this;

	}

	inline const String& getLootGroupName() const {
		return templateName;
	}

	inline int getLootChance() const {
		return lootChance;
	}
};


#endif /* LOOTGROUPENTRY_H_ */
