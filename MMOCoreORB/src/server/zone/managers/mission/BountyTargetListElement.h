/*
 * BountyTargetListElement.h
 *
 *  Created on: Feb 22, 2012
 *      Author: loshult
 */

#ifndef BOUNTYTARGETLISTELEMENT_H_
#define BOUNTYTARGETLISTELEMENT_H_

#include "system/util/Vector.h"

/**
 * Class containing a player bounty.
 */
class BountyTargetListElement : public Object {
	/**
	 * Object id of the bounty target.
	 */
	uint64 targetObjectId;

	/**
	 * Bounty reward.
	 */
	int reward;

	/**
	 * List of object id's for the bounty hunters that have the mission.
	 */
	Vector<uint64> activeBountyHunters;

public:
	/**
	 * Constructor.
	 * @param targetObjectId object id of the bounty target.
	 * @param reward bounty reward.
	 */
	BountyTargetListElement(uint64 targetObjectId, int reward) {
		this->targetObjectId = targetObjectId;
		this->reward = reward;
		activeBountyHunters.removeAll();
	}

	/**
	 * Destructor.
	 */
	~BountyTargetListElement() {
	}

	/**
	 * Get the object id of the bounty target.
	 * @return object id of the bounty target.
	 */
	uint64 getTargetId() {
		return targetObjectId;
	}

	/**
	 * Get the reward for the bounty target.
	 * @return reward for the bounty target.
	 */
	int getReward() {
		return reward;
	}

	/**
	 * Set the reward for the bounty target.
	 * @param reward the reward.
	 */
	void setReward(int reward) {
		this->reward = reward;
	}

	/**
	 * Get the current number of active bounty hunters on this bounty.
	 * @return the current number of active bounty hunters on this bounty.
	 */
	int numberOfActiveMissions() {
		return activeBountyHunters.size();
	}

	/**
	 * Add a bounty hunter to the list of active bounty hunters on the bounty.
	 * @param bountyHunterId the object id of the bounty hunter.
	 */
	void addBountyHunter(uint64 bountyHunterId) {
		if(!activeBountyHunters.contains(bountyHunterId))
			activeBountyHunters.add(bountyHunterId);
	}

	/**
	 * Remove a bounty hunter from the list of active bounty hunters on the bounty.
	 * @param bountyHunterId the object id of the bounty hunter.
	 */
	void removeBountyHunter(uint64 bountyHunterId) {
		activeBountyHunters.removeElement(bountyHunterId);
	}

	/**
	 * Get the list of active bounty hunters.
	 * @return list of active bounty hunters.
	 */
	Vector<uint64>* getActiveBountyHunters() {
		return &activeBountyHunters;
	}

	/**
	 * Load the object from a stream.
	 * @param stream stream to load from.
	 * @return true if successful.
	 */
	bool parseFromBinaryStream(ObjectInputStream* stream) {
		targetObjectId = stream->readLong();
		reward = stream->readInt();
		return activeBountyHunters.parseFromBinaryStream(stream);
	}

	/**
	 * Write the object to a stream.
	 * @param stream stream to write to.
	 * @return true if successful.
	 */
	bool toBinaryStream(ObjectOutputStream* stream) {
		stream->writeLong(targetObjectId);
		stream->writeInt(reward);
		return activeBountyHunters.toBinaryStream(stream);
	}
};

#endif /* BOUNTYTARGETLISTELEMENT_H_ */
