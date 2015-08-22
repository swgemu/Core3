/*
 * DamageOverTimeList.h
 *
 *  Created on: 04/06/2010
 *      Author: victor
 */

#ifndef DAMAGEOVERTIMELIST_H_
#define DAMAGEOVERTIMELIST_H_

#include "engine/engine.h"
#include "DamageOverTime.h"

class DamageOverTimeList : private VectorMap<uint64, Vector<DamageOverTime> > {
protected:
	Time nextTick;
	bool dot;
	Mutex guard;
public:
	DamageOverTimeList() {
		setNoDuplicateInsertPlan();
		dot = false;
	}

	DamageOverTimeList(const DamageOverTimeList& list) : VectorMap<uint64, Vector<DamageOverTime> >(list), guard() {
		setNoDuplicateInsertPlan();

		nextTick = list.nextTick;
		dot = list.dot;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return VectorMap<uint64, Vector<DamageOverTime> >::toBinaryStream(stream);
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return VectorMap<uint64, Vector<DamageOverTime> >::parseFromBinaryStream(stream);
	}

	uint64 activateDots(CreatureObject* victim);
	uint32 addDot(CreatureObject* victim, CreatureObject* attacker, uint64 parentObjectID, uint32 duration, uint64 dotType, uint8 pool, uint32 strength, float potency, uint32 defense, int secondaryStrength = 0);
	uint8 getRandomPool(uint64 dotType);
	bool healState(CreatureObject* victim, uint64 dotType, float reduction);
	void clear(CreatureObject* creature);
	bool hasDot(uint64 dotType);

	void sendStartMessage(CreatureObject* victim, uint64 type);
	void sendStopMessage(CreatureObject* victim, uint64 type);
	void sendIncreaseMessage(CreatureObject* victim, uint64 type);
	void sendDecreaseMessage(CreatureObject* victim, uint64 type);

	int getStrength(uint8 pool, uint64 dotType);

	uint64 generateKey(uint64 dotType, uint8 pool, uint64 parentObjectID)
	{
		//System::out << "oid: " << objectID << " pool: " << pool << " dotType: " << dotType << endl;
		uint64 key = parentObjectID;
		key ^= Long::hashCode((uint64)pool);
		key ^= Long::hashCode((uint64)dotType);
		//System::out << "key " << key << endl;
		return key;
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

	inline bool isNextTickPast() {
		return nextTick.isPast();
	}

};


#endif /* DAMAGEOVERTIMELIST_H_ */
