/*
 * LootGroupCollection.h
 *
 *  Created on: Jan 16, 2012
 *      Author: xyborn
 */

#ifndef LOOTGROUPCOLLECTION_H_
#define LOOTGROUPCOLLECTION_H_

#include "engine/engine.h"
#include "LootGroupEntry.h"

class LootGroupCollection : public SortedVector<LootGroupEntry> {
public:
	LootGroupCollection() {
	}
};


#endif /* LOOTGROUPCOLLECTION_H_ */
