/*
 * DamageOverTimeList.cpp
 *
 *  Created on: 04/06/2010
 *      Author: victor
 */

#include "DamageOverTimeList.h"
#include "../CreatureObject.h"

uint64 DamageOverTimeList::activateDots(CreatureObject* victim) {
	if (!hasDot())
		return 0;

	uint64 states = 0;

	for (int i = 0; i < size(); ++i) {
		uint64 type = elementAt(i).getKey();
		DamageOverTime* dot = &elementAt(i).getValue();

		if (dot->nextTickPast()) {
			dot->applyDot(victim);
		}

		Time nTime = dot->getNextTick();

		if (nextTick.isPast() || (!dot->isPast() && (nTime.compareTo(nextTick) > 0)))
			nextTick = nTime;

		if (!dot->isPast()) {
			states |= dot->getType();
		} else {
			victim->clearState(dot->getType());
		}
	}

	if (nextTick.isPast()) {
		dot = false;
		removeAll();

		states = 0;
	}

	return states;
}

uint32 DamageOverTimeList::addDot(CreatureObject* victim, uint32 duration, uint64 dotType, uint8 pool, uint32 strength, float potency, uint32 defense) {
	if (contains(dotType)) {
		DamageOverTime* newDot = &get(dotType);

		if (!newDot->isPast()) {
			if (newDot->getStrength() >= strength)
				return strength;
			else {
				sendIncreaseMessage(victim, dotType);
				newDot->setStrength(strength);
				return strength;
			}
		}
	}

	float dotReductionMod = 1.0f;

	if (defense > 0)
		dotReductionMod -= (float) defense / 125.0f;

	//System::out << "dot reduction (" << defense << ")= " << dotReductionMod << "\n";

	int redStrength = (int)(strength * dotReductionMod);
	float redPotency = potency * dotReductionMod;

	//System::out << "Strength : " << strength << " => " << redStrength << "\n";
	//System::out << "Potency: " << potency << " => " << redPotency << "\n";

	// hitChance may need modification when poison resist packs are added, include 5% hit and 5% miss
	if (!(redPotency > System::random(125) || redPotency > System::random(125))) {
		//info("potency % miss", true);
		return 0;
	}

	//System::out << "Adding dot strength " << redStrength << endl;

	DamageOverTime newDot(dotType, pool, redStrength, duration, redPotency);

	int dotPower = newDot.initDot(victim);
	victim->setState(dotType);

	Time nTime = newDot.getNextTick();

	if (isEmpty() || nextTick.isPast())
		nextTick = nTime;
	else if (nTime.compareTo(nextTick) > 0)
		nextTick = nTime;

	put(dotType, newDot);

	sendStartMessage(victim, dotType);

	dot = true;

	return dotPower;
}

bool DamageOverTimeList::healState(CreatureObject* victim, uint64 dotType, float reduction) {
	if (!hasDot())
		return reduction;

	float tempReduction = reduction;

	for (int i = 0; i < size(); ++i) {
		uint64 type = elementAt(i).getKey();
		DamageOverTime* dot = &elementAt(i).getValue();

		if (tempReduction < 0.0f)
			return tempReduction;

		if (dot->getType() == dotType && !dot->isPast())
			tempReduction = dot->reduceTick(tempReduction);
	}

	if (tempReduction >= 0.0f) {
		victim->clearState(dotType);
		//sendStopMessage(victim,dotType);
		return true;
	}

	sendDecreaseMessage(victim, dotType);

	return false;
}

void DamageOverTimeList::clear() {
	dot = false;
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

