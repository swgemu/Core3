/*
 * DamageOverTime.h
 *
 *  Created on: 04/06/2010
 *      Author: victor
 */

#ifndef DAMAGEOVERTIME_H_
#define DAMAGEOVERTIME_H_

#include "engine/engine.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
    class CreatureObject;
   }
  }
 }
}

using namespace server::zone::objects::creature;

class DamageOverTime : public Serializable {
protected:
	uint64 type;
	uint8 attribute;
	uint32 strength;
	uint32 duration;
	float potency;

	Time expires;
	Time nextTick;
public:
	DamageOverTime();
	DamageOverTime(uint64 tp, uint8 attrib, uint32 str, uint32 dur, float potency);

	DamageOverTime(const DamageOverTime& dot);
	DamageOverTime& operator=(const DamageOverTime& dot);

	void addSerializableVariables();

	/*bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);*/

	//~DamageOverTime();

	void activate();
	uint32 applyDot(CreatureObject* victim);
	uint32 initDot(CreatureObject* victim);
	float reduceTick(float reduction);

	// damage methods
	inline uint32 doBleedingTick(CreatureObject* victim);
	inline uint32 doFireTick(CreatureObject* victim);
	inline uint32 doPoisonTick(CreatureObject* victim);
	inline uint32 doDiseaseTick(CreatureObject* victim);

	// Setters
	inline void setType(uint64 value) {
		type = value;
	}

	inline void setAttribute(uint8 value) {
		attribute = value;
	}

	inline void setStrength(uint32 value) {
		strength = value;
	}

	inline void setDuration(uint32 seconds) {
		duration = seconds;
	}

	inline void setPotency(float percent) {
		potency = percent;
	}

	inline void setExpires(Time time) {
		expires = time;
	}

	//Getters
	inline uint64 getType() {
		return type;
	}

	inline uint8 getAttribute() {
		return attribute;
	}

	inline uint32 getStrength() {
		return strength;
	}

	inline uint32 getDuration() {
		return duration;
	}

	inline float getPotency() {
		return potency;
	}

	inline bool isActivated() {
		return !expires.isPast();
	}

	inline bool isPast() {
		return expires.isPast();
	}

	inline bool isFuture() {
		return expires.isFuture();
	}

	inline bool isPresent() {
		return expires.isPresent();
	}

	inline bool nextTickPast() {
		return nextTick.isPast();
	}

	inline Time getNextTick() {
		return nextTick;
	}
};


#endif /* DAMAGEOVERTIME_H_ */
