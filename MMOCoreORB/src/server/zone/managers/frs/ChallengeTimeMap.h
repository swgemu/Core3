//
// Created by Greg Slomin on 5/2/18.
//

#ifndef CORE3_CHALLENGETIMEMAP_H
#define CORE3_CHALLENGETIMEMAP_H
#include "engine/engine.h"
#include "system/lang/Time.h"

class ChallengeTimeMap : public VectorMap<uint64, Time> {
public:
	ChallengeTimeMap() : VectorMap<uint64, Time>() {
		setNoDuplicateInsertPlan();
	}
};
#endif //CORE3_CHALLENGETIMEMAP_H
