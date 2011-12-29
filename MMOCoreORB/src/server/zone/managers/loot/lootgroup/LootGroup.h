/*
 * LootGroup.h
 *
 *  Created on: Jun 24, 2011
 *      Author: kyle
 */

#ifndef LOOTGROUP_H_
#define LOOTGROUP_H_

#include "engine/engine.h"
#include "LootGroupEntry.h"

class LootGroup : public SortedVector<LootGroupEntry>, Logger {
public:
	static const int EXPECTED_SUM = 10000000; // 10,000,000
public:
	LootGroup();
	virtual ~LootGroup();

	void parseLua(lua_State* L);

	void normalizeWeights();
};

#endif /* LOOTGROUP_H_ */
