/*
 * HuntingTargetMap.h
 *
 *  Created on: Aug 27, 2010
 *      Author: dannuic
 */

#ifndef HUNTINGTARGETMAP_H_
#define HUNTINGTARGETMAP_H_

#include "engine/engine.h"
#include "HuntingTargetEntry.h"

class HuntingTargetMap :private ReadWriteLock, public Object {
	VectorMap<int, SortedVector<HuntingTargetEntry> > targets;

public:
	HuntingTargetMap() {
		targets.setNoDuplicateInsertPlan();
	}

	void addTarget(const String& temp1, const String& temp2, int lev) {
		if (lev <= 0)
			return;

		int idx = targets.find(lev);

		if (idx == -1) {
			SortedVector<HuntingTargetEntry> newVec;
			newVec.setNoDuplicateInsertPlan();

			HuntingTargetEntry entry(temp1, temp2);
			newVec.put(entry);

			targets.put(lev, newVec);
		} else {
			SortedVector<HuntingTargetEntry>& vec = targets.elementAt(idx).getValue();

			HuntingTargetEntry entry(temp1, temp2);
			vec.put(entry);
		}
	}

	HuntingTargetEntry* getRandomTarget(int lev) {
		HuntingTargetEntry* result = NULL;

		//rlock();

		int idx = targets.find(lev);

		if (idx != -1) {
			SortedVector<HuntingTargetEntry>& vector = targets.elementAt(idx).getValue();

			if (vector.size() >= 0)
				result = &vector.get(System::random(vector.size() - 1));
		}

		//runlock();

		return result;
	}
};

#endif /* HUNTINGTARGETMAP_H_ */
