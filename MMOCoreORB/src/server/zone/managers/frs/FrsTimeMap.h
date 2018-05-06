//
// Created by Greg Slomin on 5/2/18.
//

#ifndef CORE3_FRSTIMEMAP_H
#define CORE3_FRSTIMEMAP_H
#include "engine/engine.h"
#include "system/lang/Time.h"

class FrsTimeMap : public VectorMap<uint64, Time> {
public:
	FrsTimeMap() : VectorMap<uint64, Time>() {
		setNoDuplicateInsertPlan();
	}
};
#endif //CORE3_FRSTIMEMAP_H
