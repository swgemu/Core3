/*
 * LootGroupEntry.h
 *
 *  Created on: Dec 29, 2011
 *      Author: xyborn
 */

#ifndef LOOTGROUPENTRY_H_
#define LOOTGROUPENTRY_H_

#include "engine/engine.h"

class LootGroupEntry : public Object
{
	String itemTemplate;
	int itemWeight;

public:
	LootGroupEntry() {
		itemWeight = 0;
	}

	LootGroupEntry(const String& temp, int weight) {
		itemTemplate = temp;
		itemWeight = weight;
	}

	/**
	 * Loot Group Entries are sorted by their weights, in descending order. Thus, the greatest weight will be first.
	 * @param lge The loot group entry to compare.
	 */
	int compareTo(const LootGroupEntry& lge) const {
		if (lge.itemWeight > itemWeight)
			return 1;
		else if (lge.itemWeight < itemWeight)
			return -1;
		else
			return 0;
	}

	LootGroupEntry& operator=(const LootGroupEntry& lge) {
		if (this == &lge)
			return *this;

		itemTemplate = lge.itemTemplate;
		itemWeight = lge.itemWeight;

		return *this;

	}

	inline String& getItemTemplate() {
		return itemTemplate;
	}

	inline int getWeight() {
		return itemWeight;
	}

	inline void setWeight(int weight) {
		itemWeight = weight;
	}
};


#endif /* LOOTGROUPENTRY_H_ */
