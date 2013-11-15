/*
 * PlayerQuestData.h
 *
 *  Created on: 15/11/2013
 *      Author: victor
 */

#ifndef PLAYERQUESTDATA_H_
#define PLAYERQUESTDATA_H_

#include "engine/engine.h"

class PlayerQuestData : public Object {
	uint64 ownerId;
	uint16 activeStepBitmask;
	uint16 completedStepBitmask;
	byte completedFlag;
	int questCounter;
public:
	PlayerQuestData() : Object() {
		ownerId = 0;
		activeStepBitmask = 0;
		completedStepBitmask = 0;
		completedFlag = 0;
		questCounter = 0;
	}

	PlayerQuestData(const PlayerQuestData& data) : Object() {
		initialize(data);
	}

	PlayerQuestData& operator=(const PlayerQuestData& data) {
		if (this == &data)
			return *this;

		initialize(data);

		return *this;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		stream->writeLong(ownerId);
		stream->writeShort(activeStepBitmask);
		stream->writeShort(completedStepBitmask);
		stream->writeByte(completedFlag);
		stream->writeInt(questCounter);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		ownerId = stream->readLong();
		activeStepBitmask = stream->readShort();
		completedStepBitmask = stream->readShort();
		completedFlag = stream->readByte();
		questCounter = stream->readInt();

		return true;
	}

	void initialize(const PlayerQuestData& data) {
		ownerId = data.ownerId;
		activeStepBitmask = data.activeStepBitmask;
		completedStepBitmask = data.completedStepBitmask;
		completedFlag = data.completedFlag;
		questCounter = data.questCounter;
	}

	uint16 getActiveStepBitmask() const {
		return activeStepBitmask;
	}

	void setActiveStepBitmask(uint16 activeStepBitmask) {
		this->activeStepBitmask = activeStepBitmask;
	}

	byte getCompletedFlag() const {
		return completedFlag;
	}

	void setCompletedFlag(byte completedFlag) {
		this->completedFlag = completedFlag;
	}

	uint16 getCompletedStepBitmask() const {
		return completedStepBitmask;
	}

	void setCompletedStepBitmask(uint16 completedStepBitmask) {
		this->completedStepBitmask = completedStepBitmask;
	}

	uint64 getOwnerId() const {
		return ownerId;
	}

	void setOwnerId(uint64 ownerId) {
		this->ownerId = ownerId;
	}

	int getQuestCounter() const {
		return questCounter;
	}

	void setQuestCounter(int questCounter) {
		this->questCounter = questCounter;
	}
};


#endif /* PLAYERQUESTDATA_H_ */
