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


		/*if(dot->isPast())
			remove(key);
		else*/
		if (dot->nextTickPast() && !dot->isPast())
			states |= dot->getType();

	}
	if (nextTick.isPast()) {
		dot = false;
		removeAll();
		attacker = NULL;
	}

	return states;
}

bool DamageOverTimeList::addDot(CreatureObject* victim, uint64 dotID, uint32 duration, uint64 dotType, uint8 pool, uint32 strength,float potency) {
	DamageOverTime* newDot = get(dotID);

	if ((newDot != NULL)  && !newDot->isPast()) {
		if (newDot->getStrength() >= strength)
			return false;
		else {
			newDot->setStrength(strength);
			return true;
		}
	}

	if (attacker == NULL)
		return false;

	newDot = new DamageOverTime(dotType, pool, strength ,duration,potency);

	newDot->applyDot(attacker,victim);
	victim->setState(dotType);

	Time nTime = newDot->getNextTick();

	if(isEmpty() || nextTick.isPast())
		nextTick = nTime;
	else if (nTime.compareTo(nextTick) > 0)
		nextTick = nTime;

	put(dotID,newDot);

	dot = true;

	return true;
}

int DamageOverTimeList::healState(uint64 dotType, int reduction) {
	if(!hasDot())
		return reduction;

	uint32 key = 0;
	DamageOverTime* dot = NULL;
	int red_iter = reduction;
	resetIterator();

	while (hasNext()) {
		key = getNextKey();
		dot = get(key);

		if (red_iter < 0)
			return red_iter;

		if (dot->getType() == dotType && !dot->isPast())
			red_iter = dot->reduceTick(red_iter);
	}

	return red_iter;
}
