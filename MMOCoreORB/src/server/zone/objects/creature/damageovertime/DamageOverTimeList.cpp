/*
 * DamageOverTimeList.cpp
 *
 *  Created on: 04/06/2010
 *      Author: victor
 */

#include "DamageOverTimeList.h"
#include "server/zone/objects/creature/CreatureObject.h"

uint64 DamageOverTimeList::activateDots(CreatureObject* victim) {
	uint64 states = 0;
	uint64 statesBefore = 0;

	Locker guardLocker(&guard);

	for (int i = 0; i < size(); ++i) {
		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = 0; j < vector->size(); ++j) {
			DamageOverTime* dot = &vector->elementAt(j);
			statesBefore |= dot->getType();

			if (dot->nextTickPast()) {
				//guard.unlock();

				try {
					dot->applyDot(victim);
				} catch (...) {
					//guard.wlock();

					throw;
				}

				//guard.wlock();
			}

			Time nTime = dot->getNextTick();

			if (nextTick.isPast() || (!dot->isPast() && (nTime.compareTo(nextTick) > 0)))
				nextTick = nTime;

			if (!dot->isPast()) {
				states |= dot->getType();
			} else {
				if (i < size()) {
					vector->remove(j);
					--j;
				}
			}
		}
	}

	int statesRemoved = states ^ statesBefore;

	if( statesRemoved & CreatureState::BLEEDING )
		victim->clearState(CreatureState::BLEEDING);

	if( statesRemoved & CreatureState::POISONED )
		victim->clearState(CreatureState::POISONED);

	if( statesRemoved & CreatureState::DISEASED )
		victim->clearState(CreatureState::DISEASED);

	if( statesRemoved & CreatureState::ONFIRE )
		victim->clearState(CreatureState::ONFIRE);


	if (nextTick.isPast()) {
		dot = false;
		removeAll();

		states = 0;
	}

	return states;
}

int DamageOverTimeList::getStrength(uint8 pool, uint64 dotType) {
	Locker locker(&guard);

	Vector<DamageOverTime>* vector;
	int strength = 0;

	for(int i = 0; i < size(); i++)
	{
		vector = &elementAt(i).getValue();
		for(int j = 0; j < vector->size(); j++)
		{
			DamageOverTime* currentDot = &vector->elementAt(j);
			if(currentDot->getType() == dotType && (currentDot->getAttribute() == pool))
			{
				if (!currentDot->isPast()) {
					strength+=currentDot->getStrength();
				}
			}
		}
	}
	return strength;
}

uint32 DamageOverTimeList::addDot(CreatureObject* victim, CreatureObject* attacker, uint64 objectID, uint32 duration, uint64 dotType, uint8 pool, uint32 strength, float potency, uint32 defense, int secondaryStrength) {
	Locker locker(&guard);

	if (strength == 0 || duration == 0)
		return 0;

	// determine chance to hit, if no hit, just return 0. potency of less than 0 can't be resisted
	if (potency > 0 && System::random(100) >= MAX(5.f, MIN(potency * (80.f / (100.f + defense)), 95.f)))
		return 0;

	int oldStrength = getStrength(pool, dotType);

	int durationMod = 0;

	switch (dotType) {
	case CreatureState::POISONED:
		durationMod = victim->getSkillMod("dissipation_poison");
		break;
	case CreatureState::DISEASED:
		durationMod = victim->getSkillMod("dissipation_disease");
		break;
	case CreatureState::ONFIRE:
		durationMod = victim->getSkillMod("dissipation_fire");
		break;
	case CreatureState::BLEEDING:
		durationMod = victim->getSkillMod("dissipation_bleeding");
		break;
	default:
		break;
	}

	if (durationMod > 0) {
		if (durationMod > 90) durationMod = 90;
		duration = MAX(1, (int)(duration * (1.f - (durationMod / 100.f))));
	}

	//only 1 disease per bar allowed
	if(dotType == CreatureState::DISEASED)
		objectID = Long::hashCode(CreatureState::DISEASED);

	DamageOverTime newDot(attacker, dotType, pool, strength, duration, secondaryStrength);
	int dotPower = newDot.initDot(victim);

	Time nTime = newDot.getNextTick();

	if (isEmpty() || nextTick.isPast() || nTime.compareTo(nextTick) > 0)
		nextTick = nTime;

	uint64 key = generateKey(dotType, pool, objectID);

	if (contains(key)) {
		Vector<DamageOverTime>* vector = &get(key);

		for (int i = 0; i < vector->size(); ++i) {
			DamageOverTime dot = vector->get(i);

			if (newDot.getSecondaryStrength() >= dot.getSecondaryStrength()) {
				dot.setStrength(newDot.getStrength());
				dot.setSecondaryStrength(newDot.getSecondaryStrength());
				dot.setDuration(newDot.getDuration());
				dot.setExpires(newDot.getExpires());
			}
		}
	} else {
		Vector<DamageOverTime> newVector;
		newVector.add(newDot);
		put(key, newVector);
	}

	if(oldStrength == 0)
		sendStartMessage(victim, dotType);
	else
		sendIncreaseMessage(victim, dotType);

	dot = true;

	locker.release();
	victim->setState(dotType);

	return dotPower;
}

bool DamageOverTimeList::healState(CreatureObject* victim, uint64 dotType, float reduction) {
	Locker locker(&guard);

	if (!hasDot())
		return reduction;

	bool expired = true;

	float reductionLeft = reduction;

	for (int i = 0; i < size(); ++i) {
		uint64 type = elementAt(i).getKey();

		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = 0; j < vector->size(); ++j) {
			DamageOverTime* dot = &vector->elementAt(j);

			if (dot->getType() == dotType && !dot->isPast()) {
				if (reductionLeft >= dot->getStrength()) {
					reductionLeft -= dot->getStrength();
					dot->reduceTick(dot->getStrength());
					expired = expired && true;
				} else {
					dot->reduceTick(reductionLeft);
					reductionLeft = 0;
					expired = false;
					break;
				}
			}
		}

		if (reductionLeft == 0)
			break;
	}

	if (expired) {
		locker.release();
		victim->clearState(dotType);
		return true;
	}

	sendDecreaseMessage(victim, dotType);

	return false;
}

bool DamageOverTimeList::hasDot(uint64 dotType) {
	Locker locker(&guard);

	bool hasDot = false;

	for (int i = 0; i < size(); ++i) {
		uint64 type = elementAt(i).getKey();

		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = 0; j < vector->size(); ++j) {
			DamageOverTime* dot = &vector->elementAt(j);

			if (dot->getType() == dotType)
				hasDot = true;
		}
	}

	return hasDot;
}

void DamageOverTimeList::clear(CreatureObject* creature) {
	Locker locker(&guard);

	dot = false;

	for (int i = 0; i < size(); ++i) {
		uint64 type = elementAt(i).getKey();

		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = 0; j < vector->size(); ++j) {
			DamageOverTime* dot = &vector->elementAt(j);

			creature->clearState(dot->getType());
		}
	}

	removeAll();
}


void DamageOverTimeList::sendStartMessage(CreatureObject* victim, uint64 type) {
	if (!victim->isPlayerCreature())
		return;

	switch(type) {
	case CreatureState::BLEEDING:
		victim->sendSystemMessage("@dot_message:start_bleeding");
		break;
	case CreatureState::POISONED:
		victim->sendSystemMessage("@dot_message:start_poisoned");
		break;
	case CreatureState::DISEASED:
		victim->sendSystemMessage("@dot_message:start_diseased");
		break;
	case CreatureState::ONFIRE:
		victim->sendSystemMessage("@dot_message:start_fire");
		break;
	}
}

void DamageOverTimeList::sendStopMessage(CreatureObject* victim, uint64 type) {
	if (!victim->isPlayerCreature())
		return;

	switch(type) {
	case CreatureState::BLEEDING:
		victim->sendSystemMessage("@dot_message:stop_bleeding");
		break;
	case CreatureState::POISONED:
		victim->sendSystemMessage("@dot_message:stop_poisoned");
		break;
	case CreatureState::DISEASED:
		victim->sendSystemMessage("@dot_message:stop_diseased");
		break;
	case CreatureState::ONFIRE:
		victim->sendSystemMessage("@dot_message:stop_fire");
		break;
	}
}

void DamageOverTimeList::sendIncreaseMessage(CreatureObject* victim, uint64 type) {
	if (!victim->isPlayerCreature())
		return;

	switch(type) {
	case CreatureState::BLEEDING:
		victim->sendSystemMessage("@dot_message:increase_bleeding");
		break;
	case CreatureState::POISONED:
		victim->sendSystemMessage("@dot_message:increase_poisoned");
		break;
	case CreatureState::DISEASED:
		victim->sendSystemMessage("@dot_message:increase_diseased");
		break;
	case CreatureState::ONFIRE:
		victim->sendSystemMessage("@dot_message:increase_fire");
		break;
	}
}

void DamageOverTimeList::sendDecreaseMessage(CreatureObject* victim, uint64 type) {
	if (!victim->isPlayerCreature())
		return;

	switch(type) {
	case CreatureState::BLEEDING:
		victim->sendSystemMessage("@dot_message:decrease_bleeding");
		break;
	case CreatureState::POISONED:
		victim->sendSystemMessage("@dot_message:decrease_poisoned");
		break;
	case CreatureState::DISEASED:
		victim->sendSystemMessage("@dot_message:decrease_diseased");
		break;
	case CreatureState::ONFIRE:
		victim->sendSystemMessage("@dot_message:decrease_fire");
		break;
	}
}

