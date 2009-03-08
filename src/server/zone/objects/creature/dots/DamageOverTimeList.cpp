#include "DamageOverTimeList.h"

uint64 DamageOverTimeList::activateDots(CreatureObject* victim) {
	if(!hasDot())
		return 0x0;

	uint32 key = 0;
	DamageOverTime* dot = NULL;
	resetIterator();
	uint64 states = 0x0;
	while (hasNext()) {
		key = getNextKey();
		dot = get(key);

		if (dot->nextTickPast()) {
			if (attacker != NULL) {
				try {
					if (attacker != victim)
						attacker->wlock(victim);

					dot->applyDot(attacker,victim);

					if ( attacker != victim)
						attacker->unlock();
				} catch (...) {
					if (attacker != victim)
						attacker->unlock();
				}
			}
		}

		Time nTime = dot->getNextTick();

		if (nextTick.isPast() || (!dot->isPast() && (nTime.compareTo(nextTick) > 0)))
			nextTick = nTime;

		if (!dot->isPast())
			states |= dot->getType();

	}
	if (nextTick.isPast()) {
		dot = false;
		removeAll();
		attacker = NULL;
		states = 0x0;
	}

	return states;
}

uint32 DamageOverTimeList::addDot(CreatureObject* victim, uint64 dotID, uint32 duration, uint64 dotType, uint8 pool, uint32 strength,float potency) {
	DamageOverTime* newDot = get(dotID);

	if ((newDot != NULL)  && !newDot->isPast()) {
		if (newDot->getStrength() >= strength)
			return strength;
		else {
			newDot->setStrength(strength);
			return strength;
		}
	}

	if (attacker == NULL)
		return false;

	newDot = new DamageOverTime(dotType, pool, strength ,duration,potency);

	int dotPower = newDot->initDot(attacker,victim);
	victim->setState(dotType);

	Time nTime = newDot->getNextTick();

	if(isEmpty() || nextTick.isPast())
		nextTick = nTime;
	else if (nTime.compareTo(nextTick) > 0)
		nextTick = nTime;

	put(dotID,newDot);

	dot = true;

	return dotPower;
}

float DamageOverTimeList::healState(uint64 dotType, float reduction) {
	if(!hasDot())
		return reduction;

	uint32 key = 0;
	DamageOverTime* dot = NULL;
	float tempReduction = reduction;
	resetIterator();

	while (hasNext()) {
		key = getNextKey();
		dot = get(key);

		if (tempReduction < 0.0f)
			return tempReduction;

		if (dot->getType() == dotType && !dot->isPast())
			tempReduction = dot->reduceTick(tempReduction);
	}

	return tempReduction;
}

void DamageOverTimeList::clear() {
	dot = false;
	removeAll();
	attacker = NULL;
}
