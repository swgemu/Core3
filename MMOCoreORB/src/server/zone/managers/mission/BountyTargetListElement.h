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
	String targetName;
	int reward;
	bool canHaveNewMissions;
	Vector<String> activeBountyHunters;

	BountyTargetListElement(String targetName, int reward) {
		this->targetName = targetName;
		this->reward = reward;
		canHaveNewMissions = true;
		activeBountyHunters.removeAll();
	}

	~BountyTargetListElement() {
	}

	String getTargetName() {
		return targetName;
	}

	int getReward() {
		return reward;
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

	int addBountyHunter(String bountyHunterName) {
		activeBountyHunters.add(bountyHunterName);
	}

	void removeBountyHunter(String bountyHunterName) {
		activeBountyHunters.removeElement(bountyHunterName);
	}
};

#endif /* BOUNTYTARGETLISTELEMENT_H_ */
