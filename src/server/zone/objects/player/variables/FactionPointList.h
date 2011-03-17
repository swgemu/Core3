/*
 * FactionPointList.h
 *
 *  Created on: Mar 16, 2011
 *      Author: crush
 */

#ifndef FACTIONPOINTLIST_H_
#define FACTIONPOINTLIST_H_

#include "engine/engine.h"

class FactionPointList : public VectorMap<String, int> {
public:
	FactionPointList() : VectorMap<String, int>() {
		setNoDuplicateInsertPlan();
		setNullValue(0);
	}
};

#endif /* FACTIONPOINTLIST_H_ */
