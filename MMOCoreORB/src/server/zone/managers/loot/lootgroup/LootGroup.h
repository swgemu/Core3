/*
 * LootGroup.h
 *
 *  Created on: Jun 24, 2011
 *      Author: kyle
 */

#ifndef LOOTGROUP_H_
#define LOOTGROUP_H_

#include "../lootitems/LootItems.h"

class LootGroup : public Vector<String> {
public:
	LootGroup();
	virtual ~LootGroup();
};

#endif /* LOOTGROUP_H_ */
