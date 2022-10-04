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

// #define DEBUG_PLAYERBITMASKS

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
		uint32 bit = bitmask % 32;
		uint32 value = 1 << bit;

#ifdef DEBUG_PLAYERBITMASKS
		Logger::console.info("setPlayerBitmask - Bitmask = " + String::valueOf(bitmask) + " bit = " + String::valueOf(bit) + " value = " + String::valueOf(value), true);
#endif
		Locker locker(this);

		// Anonymous flag is stored in int 3
		if (bitmask == PlayerBitmasks::ANONYMOUS) {
			if (!(playerBitmask[3] & value))
				playerBitmask[3] |= value;
		} else if (!(playerBitmask[0] & value)) {
			playerBitmask[0] |= value;
		}
	}

	void removePlayerBitmask(const uint32 bitmask) {
		uint32 bit = bitmask % 32;
		uint32 value = 1 << bit;

#ifdef DEBUG_PLAYERBITMASKS
		Logger::console.info("removePlayerBitmask - Bitmask = " + String::valueOf(bitmask) + " bit = " + String::valueOf(bit) + " value = " + String::valueOf(value), true);
#endif
		Locker locker(this);

		// Anonymous flag is stored in int 3
		if (bitmask == PlayerBitmasks::ANONYMOUS) {
			if ((playerBitmask[3] & value))
				playerBitmask[3] &= ~value;
		} else if ((playerBitmask[0] & value)) {
			playerBitmask[0] &= ~value;
		}
	}

	bool hasPlayerBitmask(const uint32 bitmask) const {
		int bitmaskNumber = 0;
		uint32 bit = bitmask % 32;
		uint32 value = 1 << bit;

#ifdef DEBUG_PLAYERBITMASKS
		Logger::console.info("hasPlayerBitmask - Bitmask = " + String::valueOf(bitmask) + " bitmaskNumber = " + String::valueOf(bitmaskNumber) + " bit = " + String::valueOf(bit) + " value = " + String::valueOf(value), true);
#endif
		ReadLocker locker(this);

		if (bitmask == PlayerBitmasks::ANONYMOUS)
			bitmaskNumber = 3;

		bool result = playerBitmask[bitmaskNumber] & value;

		return result;
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