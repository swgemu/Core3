/*
 * DamageOverTimeList.cpp
 *
 *  Created on: 04/06/2010
 *      Author: victor
 */

#include "DamageOverTimeList.h"
#include "../CreatureObject.h"

uint64 DamageOverTimeList::activateDots(CreatureObject* victim) {
	uint64 states = 0;
	uint64 statesBefore = 0;

	for (int i = 0; i < size(); ++i) {
		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = 0; j < vector->size(); ++j) {
			DamageOverTime* dot = &vector->elementAt(j);
			statesBefore |= dot->getType();

			if (dot->nextTickPast()) {
				dot->applyDot(victim);
			}

			Time nTime = dot->getNextTick();

			if (nextTick.isPast() || (!dot->isPast() && (nTime.compareTo(nextTick) > 0)))
				nextTick = nTime;

			if (!dot->isPast()) {
				states |= dot->getType();
			} else {
				vector->remove(j);
				--j;
			}
		}
	}

	int statesRemoved = states ^ statesBefore;

	if( statesRemoved & CreatureState::BLEEDING )
	{
		victim->clearState(CreatureState::BLEEDING);
	}
	if( statesRemoved & CreatureState::POISONED )
	{
		victim->clearState(CreatureState::POISONED);
	}
	if( statesRemoved & CreatureState::DISEASED )
	{
		victim->clearState(CreatureState::DISEASED);
	}
	if( statesRemoved & CreatureState::ONFIRE )
	{
		victim->clearState(CreatureState::ONFIRE);
	}

	if (nextTick.isPast()) {
		dot = false;
		removeAll();

		states = 0;
	}

	return states;
}

int DamageOverTimeList::getStrength(uint8 pool, uint64 dotType) {
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

uint32 DamageOverTimeList::addDot(CreatureObject* victim, uint64 objectID, uint32 duration, uint64 dotType, uint8 pool, uint32 strength, float potency, uint32 defense) {
	if (strength == 0) return 0;
	int oldStrength = getStrength(pool, dotType);
	float dotReductionMod = 1.0f;
	int redStrength;
	float redPotency;

	if (!(dotType == CreatureState::DISEASED || dotType == CreatureState::POISONED)) { // Calculate hit for non poison & disease dots
		if (defense > 0)
			dotReductionMod -= (float) defense / 125.0f;

		redStrength = (int)(strength * dotReductionMod);
		redPotency = potency * dotReductionMod;
		if (!(redPotency > System::random(125) || redPotency > System::random(125)))
			return 0;

	} else {

		int missChance = System::random(100); // find out 5% miss and 5% hit

		if (missChance <= 5) // 5% miss chance
			return 0;

		else if (missChance >5 && missChance <=95){ // Over 95 is 5% hit

			int dotChance = 50;   // If potency and resist are equal, then 50% chance to land

			if (potency >= defense)
				dotChance += (int)((potency - defense)*.5); // For every point of difference, increase chance by .5%
			else
				dotChance -= (int)((defense - potency)*.5); // For every point of difference, decrease chance by .5%

			if (dotChance < System::random(100))
				return 0;

		}
		redStrength = strength;
		redPotency = potency;
	}

	//only 1 disease per bar allowed
	if(dotType == CreatureState::DISEASED)
	{
		objectID = Long::hashCode(CreatureState::DISEASED);

	}
	DamageOverTime newDot(dotType, pool, redStrength, duration, redPotency);
	int dotPower = newDot.initDot(victim);
	victim->setState(dotType);

	Time nTime = newDot.getNextTick();

	if (isEmpty() || nextTick.isPast())
		nextTick = nTime;
	else if (nTime.compareTo(nextTick) > 0)
		nextTick = nTime;

	uint64 key = generateKey(dotType, pool, objectID);

	if (contains(key)) {
		Vector<DamageOverTime>* vector = &get(key);
		vector->removeAll();
		vector->add(newDot);
		//System::out << "Replacing Dot" << endl;
	} else {
		Vector<DamageOverTime> newVector;
		newVector.add(newDot);
		put(key, newVector);
		//System::out << "New Dot" << endl;
	}
	if(oldStrength == 0)
	{
		sendStartMessage(victim, dotType);
	}
	else
	{
		sendIncreaseMessage(victim, dotType);
	}

	dot = true;

	return dotPower;
}

bool DamageOverTimeList::healState(CreatureObject* victim, uint64 dotType, float reduction) {
	if (!hasDot())
		return reduction;

	//float tempReduction = reduction;

	/*if (tempReduction < 0.0f)
		return tempReduction;*/

	bool expired = true;

	for (int i = 0; i < size(); ++i) {
		uint64 type = elementAt(i).getKey();

		Vector<DamageOverTime>* vector = &elementAt(i).getValue();

		for (int j = 0; j < vector->size(); ++j) {
			DamageOverTime* dot = &vector->elementAt(j);

			if (dot->getType() == dotType && !dot->isPast()) {
				float tempReduction = dot->reduceTick(reduction);

				if (tempReduction >= 0.0f)
					expired = expired && true;
				else
					expired = false;
			}
		}
	}

	if (/*tempReduction >= 0.0f*/expired) {
		victim->clearState(dotType);
		//sendStopMessage(victim,dotType);
		return true;
	}

	sendDecreaseMessage(victim, dotType);

	return false;
}

void DamageOverTimeList::clear(CreatureObject* creature) {
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

