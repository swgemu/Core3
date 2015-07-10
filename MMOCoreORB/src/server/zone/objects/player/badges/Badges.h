/*
 * Badges.h
 *
 *  Created on: 02/02/2010
 *      Author: victor
 */

#ifndef BADGES_H_
#define BADGES_H_

#include "engine/engine.h"
#include "server/ServerCore.h"
#include "server/zone/managers/player/BadgeList.h"
#include "Badge.h"

class Badges : public Serializable, public ReadWriteLock {
	uint32 badgeBitmask[5];
	uint8 badgeTypeCounts[6];
	uint8 badgeTotal;
public:
	Badges() {
		for (int i = 0; i < 5; ++i)
			badgeBitmask[i] = 0;

		for (int i = 0; i < 6; ++i)
			badgeTypeCounts[i] = 0;

		badgeTotal = 0;

		addSerializableVariables();
	}

	Badges(const Badges& badges) : Object(), Serializable(), ReadWriteLock() {
		for (int i = 0; i < 5; ++i) {
			badgeBitmask[i] = badges.badgeBitmask[i];
		}

		for (int i = 0; i < 6; ++i)
			badgeTypeCounts[i] = badges.badgeTypeCounts[i];

		badgeTotal = badges.badgeTotal;

		addSerializableVariables();
	}

	Badges& operator=(const Badges& badges) {
		for (int i = 0; i < 5; ++i) {
			badgeBitmask[i] = badges.badgeBitmask[i];
		}

		for (int i = 0; i < 6; ++i)
			badgeTypeCounts[i] = badges.badgeTypeCounts[i];

		badgeTotal = badges.badgeTotal;

		return *this;
	}

	inline void addSerializableVariables() {
		addSerializableVariable("badgeBitmask1", &badgeBitmask[0]);
		addSerializableVariable("badgeBitmask2", &badgeBitmask[1]);
		addSerializableVariable("badgeBitmask3", &badgeBitmask[2]);
		addSerializableVariable("badgeBitmask4", &badgeBitmask[3]);
		addSerializableVariable("badgeBitmask5", &badgeBitmask[4]);

		addSerializableVariable("badgeTypeCount1", &badgeTypeCounts[0]);
		addSerializableVariable("badgeTypeCount2", &badgeTypeCounts[1]);
		addSerializableVariable("badgeTypeCount3", &badgeTypeCounts[2]);
		addSerializableVariable("badgeTypeCount4", &badgeTypeCounts[3]);
		addSerializableVariable("badgeTypeCount5", &badgeTypeCounts[4]);
		addSerializableVariable("badgeTypeCount6", &badgeTypeCounts[5]);

		addSerializableVariable("badgeTotal", &badgeTotal);
	}

public:
	void setBadge(const uint badgeid) {
		const Badge* badge = BadgeList::instance()->get(badgeid);
		setBadge(badge);
	}
	void setBadge(const Badge* badge) {
		if (badge == NULL) return;

		Locker locker(this);

		const int badgeIndex = badge->getIndex();

		int bitmaskNumber = badgeIndex >> 5;

		uint32 bit = badgeIndex % 32;
		uint32 value = 1 << bit;

		if (bitmaskNumber > 4 || bitmaskNumber < 0) {
			Logger::console.error("Badge::setBadge wrong badge index " + String::valueOf(badgeIndex));

			return;
		}

		if (!(badgeBitmask[bitmaskNumber] & value)) {
			badgeBitmask[bitmaskNumber] |= value;
			const int badgeType = badge->getTypeInt(); 
			badgeTypeCounts[badgeType]++;
			badgeTotal++;
		}
	}

	void unsetBadge(Badge* badge) {
		if (badge == NULL) return;
		Locker locker(this);

		const int badgeIndex = badge->getIndex();
		int bitmaskNumber = badgeIndex >> 5;

		uint32 bit = badgeIndex % 32;
		uint32 value = 1 << bit;

		if (bitmaskNumber > 4 || bitmaskNumber < 0) {
			Logger::console.error("Badge::unsetBadge wrong badge index " + String::valueOf(badgeIndex));

			return;
		}

		if (badgeBitmask[bitmaskNumber] & value) {
			badgeBitmask[bitmaskNumber] -= value;
			const int badgeType = badge->getTypeInt();
			badgeTypeCounts[badgeType]--;
			badgeTotal--;
		}

	}



	bool hasBadge(int badgeindex) {
		int bitmaskNumber = badgeindex >> 5;

		if (bitmaskNumber > 4 || bitmaskNumber < 0) {
			Logger::console.error("Badge::hasBadge wrong badge index " + String::valueOf(badgeindex));

			return false;
		}

		uint32 bit = badgeindex % 32;
		uint32 value = 1 << bit;

		rlock();

		bool res = badgeBitmask[bitmaskNumber] & value;

		runlock();

		return res;
	}

	void setBitmask(int index, uint32 bitmask) {
		if (index > 4 || index < 0) {
			Logger::console.error("Badge::setBitmask wrong badge index " + String::valueOf(index));

			return;
		}

		Locker locker(this);

		badgeBitmask[index] = bitmask;
	}

	uint32 getBitmask(int index) {
		uint32 res = 0;

		if (index > 4 || index < 0) {
			Logger::console.error("Badge::getBitmask wrong badge index " + String::valueOf(index));

			return res;
		}

		rlock();

		res = badgeBitmask[index];

		runlock();

		return res;
	}

	void setTypeCount(uint8 index, uint8 value) {
		if (index > 5)
			return;

		Locker locker(this);

		badgeTypeCounts[index] = value;
	}

	uint8 getTypeCount(uint8 type) {
		rlock();

		uint8 res = badgeTypeCounts[type];

		runlock();

		return res;
	}

	uint8 getNumBadges() {
		rlock();

		uint8 res = badgeTotal;

		runlock();

		return res;
	}

	void setNumBadges(uint8 value) {
		Locker locker(this);

		badgeTotal = value;
	}
};

#endif /* BADGES_H_ */
