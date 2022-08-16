/*
 * PlayerBitmasks.h
 *
 * Created on: 08/19/22
 * Author: H
 */

#ifndef PLAYERBITMASKS_H_
#define PLAYERBITMASKS_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

class PlayerBitmasks : public Serializable, public ReadWriteLock {
	uint32 playerBitmask[4];
public:
	enum {
		LFG				= 0,
		NEWBIEHELPER	= 1,
		ROLEPLAYER		= 2,
		AFK				= 7,
		LD				= 8,
		FACTIONRANK		= 9,
		ANONYMOUS		= 127
	};

	PlayerBitmasks() {
		for (int i = 0; i < 4; ++i)
			playerBitmask[i] = 0;

		addSerializableVariables();
	}

	PlayerBitmasks(const PlayerBitmasks& bitmasks) : Object(), Serializable(), ReadWriteLock() {
		for (int i = 0; i < 4; ++i) {
			playerBitmask[i] = bitmasks.playerBitmask[i];
		}

		addSerializableVariables();
	}

	PlayerBitmasks& operator=(const PlayerBitmasks& bitmasks) {
		for (int i = 0; i < 4; ++i) {
			playerBitmask[i] = bitmasks.playerBitmask[i];
		}

		return *this;
	}

	inline void addSerializableVariables() {
		addSerializableVariable("playerBitmask1", &playerBitmask[0]);
		addSerializableVariable("playerBitmask2", &playerBitmask[1]);
		addSerializableVariable("playerBitmask3", &playerBitmask[2]);
		addSerializableVariable("playerBitmask4", &playerBitmask[3]);
	}

public:
	friend void to_json(nlohmann::json& j, const PlayerBitmasks& b) {
		auto array = nlohmann::json::array();

		for (int i = 0; i < 4; ++i) {
			array.push_back(b.playerBitmask[i]);
		}

		j["playerBitmasks"] = array;
	}

	void setPlayerBitmask(const uint32 bitmask) {
		Locker locker(this);

		int bitmaskNumber = bitmask >> 4;
		uint32 bit = bitmask % 128;
		uint32 value = 1 << bit;

		if (bitmask == PlayerBitmasks::ANONYMOUS)
			bitmaskNumber = 3;

		// Logger::console.info("setPlayerBitmask - Bitmask = " + String::valueOf(bitmask) + " bitmaskNumber = " + String::valueOf(bitmaskNumber) + " bit = " + String::valueOf(bit) + " value = " + String::valueOf(value), true);

		if (bitmaskNumber > 3 || bitmaskNumber < 0) {
			Logger::console.error("PlayerBitmask::setPlayerBitmask error " + String::valueOf(bitmask));

			return;
		}

		if (!(playerBitmask[bitmaskNumber] & value)) {
			playerBitmask[bitmaskNumber] |= value;
		}
	}

	void removePlayerBitmask(const uint32 bitmask) {
		Locker locker(this);

		int bitmaskNumber = bitmask >> 4;
		uint32 bit = bitmask % 128;
		uint32 value = 1 << bit;

		if (bitmask == PlayerBitmasks::ANONYMOUS)
			bitmaskNumber = 3;

		// Logger::console.info("removePlayerBitmask - Bitmask = " + String::valueOf(bitmask) + " bitmaskNumber = " + String::valueOf(bitmaskNumber) + " bit = " + String::valueOf(bit) + " value = " + String::valueOf(value), true);

		if (bitmaskNumber > 3 || bitmaskNumber < 0) {
			Logger::console.error("PlayerBitmask::removePlayerBitmask error " + String::valueOf(bitmask));

			return;
		}

		if (playerBitmask[bitmaskNumber] & value) {
			playerBitmask[bitmaskNumber] -= value;
		}
	}

	bool hasPlayerBitmask(const uint32 bitmask) const {
		int bitmaskNumber = bitmask >> 4;

		if (bitmask == PlayerBitmasks::ANONYMOUS)
			bitmaskNumber = 3;

		if (bitmaskNumber > 3 || bitmaskNumber < 0) {
			Logger::console.error("PlayerBitmask::hasPlayerBitmask improper bit " + String::valueOf(bitmask));

			return false;
		}

		uint32 bit = bitmask % 32;
		uint32 value = 1 << bit;

		ReadLocker locker(this);

		bool res = playerBitmask[bitmaskNumber] & value;

		return res;
	}

	uint32 getBitmask(int index) const {
		uint32 res = 0;

		if (index > 3 || index < 0) {
			Logger::console.error("PlayerBitmasks::getBitmask index out of bounds" + String::valueOf(index));

			return res;
		}

		ReadLocker locker(this);

		res = playerBitmask[index];

		return res;
	}
};

#endif /* PLAYERBITMASKS_H_ */