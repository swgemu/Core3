/*
 * BountyTargetListElement.h
 *
 *  Created on: Feb 22, 2012
 *      Author: loshult
 */

#ifndef BOUNTYTARGETLISTELEMENT_H_
#define BOUNTYTARGETLISTELEMENT_H_

#include "system/util/Vector.h"

class BountyTargetListElement {
	unsigned long long int targetObjectId;
	int reward;
	bool canHaveNewMissions;
	Vector<unsigned long long int> activeBountyHunters;

public:
	BountyTargetListElement(unsigned long long int targetObjectId, int reward) {
		this->targetObjectId = targetObjectId;
		this->reward = reward;
		canHaveNewMissions = true;
		activeBountyHunters.removeAll();
	}

	~BountyTargetListElement() {
	}

	unsigned long long int getTargetName() {
		return targetObjectId;
	}

	int getReward() {
		return reward;
	}

	void setReward(int reward) {
		this->reward = reward;
	}

	bool getCanHaveNewMissions() {
		return canHaveNewMissions;
	}

	void setCanHaveNewMissions(bool value) {
		canHaveNewMissions = value;
	}

	int numberOfActiveMissions() {
		return activeBountyHunters.size();
	}

	void addBountyHunter(unsigned long long int bountyHunterId) {
		activeBountyHunters.add(bountyHunterId);
	}

	void removeBountyHunter(unsigned long long int bountyHunterId) {
		activeBountyHunters.removeElement(bountyHunterId);
	}
};

#endif /* BOUNTYTARGETLISTELEMENT_H_ */
