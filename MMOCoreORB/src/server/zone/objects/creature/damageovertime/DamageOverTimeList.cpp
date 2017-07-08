/*
 * DamageOverTimeList.cpp
 *
 *  Created on: 04/06/2010
 *      Author: victor
 */

#include "DamageOverTimeList.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/commands/effect/CommandEffect.h"
#include "templates/params/creature/CreatureAttribute.h"

uint64 DamageOverTimeList::activateDots(CreatureObject* victim) {
	uint64 states = 0;
	uint64 statesBefore = 0;

	Locker guardLocker(&guard);

	for (int i = size() - 1; i >= 0 ; --i) {
		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = vector->size() - 1; j >= 0 ; --j) {
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
				if (vector->size() == 1) {
					vector->remove(j);
					remove(i);
				} else {
					vector->remove(j);
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
			if(currentDot->getType() == dotType && (currentDot->getAttribute() == pool || pool == 0xFF))
			{
				if (!currentDot->isPast()) {
					strength+=currentDot->getStrength();
				}
			}
		}
	}
	return strength;
}

uint32 DamageOverTimeList::addDot(CreatureObject* victim,
								  CreatureObject* attacker,
								  uint64 objectID,
								  uint32 duration,
								  uint64 dotType,
								  uint8 pool,
								  uint32 strength,
								  float potency,
								  uint32 defense,
								  int secondaryStrength) {
	Locker locker(&guard);

	if (strength == 0 || duration == 0)
		return 0;

	// determine chance to hit, if no hit, just return 0. potency of less than 0 can't be resisted
	if (potency > 0 && System::random(100) >= Math::max(5.f, Math::min(potency * (80.f / (100.f + defense)), 95.f)))
		return 0;

	if (pool == CreatureAttribute::UNKNOWN) {
		pool = getRandomPool(dotType);
	}

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
		duration = Math::max(1, (int)(duration * (1.f - (durationMod / 100.f))));
	}

	//only 1 disease per bar allowed
	if(dotType == CreatureState::DISEASED) {
		objectID = Long::hashCode(CreatureState::DISEASED);
	} else if (dotType == CommandEffect::FORCECHOKE) {
		objectID = 0;
	}

	DamageOverTime newDot(attacker, dotType, pool, strength, duration, secondaryStrength);
	int dotPower = newDot.initDot(victim, attacker);

	uint64 key = generateKey(dotType, pool, objectID);

	if (contains(key)) {
		Vector<DamageOverTime>* vector = &get(key);
		Vector<DamageOverTime> newVec;

		// This seems to only ever put one value in the DOT vector. This needs to remain a vector to
		// maintain the integrity of the db.
		for (int i = 0; i < vector->size(); ++i) {
			DamageOverTime dot = vector->get(i);

			// Curing the dot can cause the dot to expire but not get
			// removed from the list, so if the dot is expired make sure
			// to not reset it
			if (dot.isPast()) {
				newVec.add(newDot);
			} else if (newDot.getStrength() >= dot.getStrength()) {
				// but we only want to reuse the tick if the old dot has not
				// expired yet but is being replaced due to strength
				newDot.setNextTick(dot.getNextTick());
				newVec.add(newDot);
			} else // the new dot has less strength and the old dot hasn't expired
				newVec.add(dot);

			drop(key);
			put(key, newVec);
		}
	} else {
		Vector<DamageOverTime> newVector;
		newVector.add(newDot);
		put(key, newVector);
	}

	Time nTime = newDot.getNextTick();

	if (isEmpty() || nTime.compareTo(nextTick) > 0)
		nextTick = nTime;

	if(oldStrength == 0)
		sendStartMessage(victim, dotType);
	else
		sendIncreaseMessage(victim, dotType);

	dot = true;

	locker.release();

	if (dotType != CommandEffect::FORCECHOKE)
		victim->setState(dotType);

	return dotPower;
}

uint8 DamageOverTimeList::getRandomPool(uint64 dotType) {
	uint8 pool = 0;

	switch (dotType) {
	case CreatureState::POISONED:
	case CreatureState::ONFIRE:
	case CreatureState::BLEEDING:
		pool = System::random(2) * 3;
		break;
	case CreatureState::DISEASED:
		pool = System::random(8);
		break;
	default:
		break;
	}

	return pool;
}

bool DamageOverTimeList::healState(CreatureObject* victim, uint64 dotType, float reduction, bool sendMsg) {
	Locker locker(&guard);

	if (!hasDot())
		return reduction;

	Vector<DamageOverTime*> timeVec;

	for (int i = 0; i < size(); i++) {
		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = 0; j < vector->size(); j++) {
			DamageOverTime* dot = &vector->elementAt(j);

			if (dot->getType() == dotType && !dot->isPast())
				timeVec.add(dot);
		}
	}

	bool expired = true;

	float reductionLeft = reduction;

	for (int i = 0; i < timeVec.size(); i++) {
		DamageOverTime* dot = timeVec.elementAt(i);

		if (!dot->isPast()) {
			reductionLeft = dot->reduceTick(reductionLeft);
			// reduceTick() *should* be guaranteed to return a non-negative value,
			// but since this is a float, we want to make sure
			if (reductionLeft <= 0.f)
			{
				// we ran out of juice in our cure, so don't expire the dotType,
				// ie, maintain the state with a reduced damage per tick
				expired = false;
				break;
			}
		}
	}

	if (expired) {
		locker.release();
		victim->clearState(dotType);
		return true;
	}

	if (sendMsg)
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

void DamageOverTimeList::multiplyAllDOTDurations(float multiplier) {
	Locker locker(&guard);

	if(!hasDot())
		return;

	for (int i = 0; i < size(); i++) {
		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = 0; j < vector->size(); j++) {
			DamageOverTime* dot = &vector->elementAt(j);

			if (!dot->isPast()) {
				dot->multiplyDuration(multiplier);
			}
		}
	}
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
	case CommandEffect::FORCECHOKE:
		victim->sendSystemMessage("@combat_effects:choke_single");
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

