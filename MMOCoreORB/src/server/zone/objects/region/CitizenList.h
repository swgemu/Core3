/*
 * CitizenList.h
 *
 *  Created on: Feb 19, 2012
 *      Author: xyborn
 */

#ifndef CITIZENLIST_H_
#define CITIZENLIST_H_

#include "engine/engine.h"

class CitizenList : public SortedVector<uint64> {
public:
	CitizenList() : SortedVector<uint64>() {
		setNoDuplicateInsertPlan();
	}
};


#endif /* CITIZENLIST_H_ */
