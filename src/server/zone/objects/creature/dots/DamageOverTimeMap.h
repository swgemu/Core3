/*
 * DamageOverTimeMap.h
 *
 *  Created on: Jan 23, 2009
 *      Author: swgdev
 */

#ifndef DAMAGEOVERTIMEMAP_H_
#define DAMAGEOVERTIMEMAP_H_

#include "engine/engine.h"

#include "../CreatureObject.h"
#include "DamageOverTimeList.h"

class DamageOverTimeMap : public HashTable<uint64, DamageOverTimeList*>, public HashTableIterator<uint64, DamageOverTimeList*>{
	int hash(const uint64& key) {
		return Long::hashCode(key);
	}

protected:
	Time nextTick;
	bool dot;
	uint64 dotStates;
public:
	//uint32 is the skillCRC of the skill used to apply the DOT
	DamageOverTimeMap() : HashTable<uint64, DamageOverTimeList*>() , HashTableIterator<uint64, DamageOverTimeList*>(this) {
		setNullValue(NULL);

		setNextTick(NULL);
		dot = false;
		dotStates = 0x0;
	}

	inline void setNextTick(Time time) {
		nextTick = time;
	}

	inline void setNextTick(uint32 delay) {
		nextTick.addMiliTime(delay * 1000);
	}

	inline Time getNextTick() {
		return nextTick;
	}

	bool hasDot() {
		return (!isEmpty() && dot);
	}

	inline bool isPast() {
		return nextTick.isPast();
	}


	void addDot(CreatureObject* attacker, CreatureObject* victim, uint64 dotID, uint32 duration, uint64 dotType, uint8 pool, uint32 strength, float potency, uint32 defense);
	void activateDots(CreatureObject* victim);
	bool healState(CreatureObject* victim, uint64 dotType, int reduction);


	void sendStartMessage(CreatureObject* victim, uint64 type);
	void sendStopMessage(CreatureObject* victim, uint64 type);
	void sendIncreaseMessage(CreatureObject* victim, uint64 type);
	void sendDecreaseMessage(CreatureObject* victim, uint64 type);

};

#endif /* DAMAGEOVERTIMEMAP_H_ */
