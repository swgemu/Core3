/*
 * VeteranRewardList.h
 *
 *  Created on: 5/22/2014
 *      Author: Klivian
 */

#ifndef VETERANREWARDLIST_H_
#define VETERANREWARDLIST_H_

#include "engine/engine.h"
#include "VeteranReward.h"

class VeteranRewardList : public Vector<VeteranReward> {

public:

	VeteranRewardList() : Vector<VeteranReward>() {
	}

};

#endif /* VETERANREWARDLIST_H_ */
