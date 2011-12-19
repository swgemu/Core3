/*
 * LootItems.h
 *
 *  Created on: Jun 24, 2011
 *      Author: kyle
 */

#ifndef LOOTITEMS_H_
#define LOOTITEMS_H_

#include "server/zone/templates/LootItemTemplate.h"

class LootItems : public HashTable<String, Reference<LootItemTemplate*> > {
public:
	LootItems();
	virtual ~LootItems();
};

#endif /* LOOTITEMS_H_ */
