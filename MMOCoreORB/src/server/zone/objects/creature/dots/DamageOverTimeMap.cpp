
#include "DamageOverTimeMap.h"

void DamageOverTimeMap::addDot(CreatureObject* attacker, CreatureObject* victim, uint64 dotID, uint32 duration, uint64 dotType, uint8 pool, uint32 strength, float potency, uint32 defense) {
	uint64 attackerID = attacker->getObjectID();
	DamageOverTimeList* dotList = get(attackerID);

	if(dotList == NULL)
		dotList = new DamageOverTimeList(attacker);

	bool hasState = victim->hasState(dotType);

	float dotReductionMod = 1.0f;

	if (defense > 0)
		dotReductionMod -= (float) defense / 125.0f;

	int redStrength = (int)(strength * dotReductionMod);
	float redPotency = potency * dotReductionMod;

	bool dotAdded =  dotList->addDot(victim, dotID, duration, dotType, pool, redStrength,redPotency);

	if (dotAdded) {
		Time nTime = dotList->getNextTick();

		if(isEmpty() || nextTick.isPast())
			nextTick = nTime;
		else if (nTime.compareTo(nextTick) > 0)
			nextTick = nTime;

		put(attackerID,dotList);


		dot = true;

		if (hasState)
			sendIncreaseMessage(victim,dotType);
		else if (dotAdded)
			sendStartMessage(victim,dotType);
	}

	victim->updateStates();
}

void DamageOverTimeMap::activateDots(CreatureObject* victim) {
	if(!hasDot())
		return;

	uint64 attacker = 0;
	DamageOverTimeList* dotList = NULL;
	resetIterator();
	uint64 newStates = 0x0;
	while (hasNext()) {
		attacker = getNextKey();
		dotList = get(attacker);

		if(!dotList->hasDot()) {
			remove(attacker);
			continue;
		}

		if (dotList->isNextTickPast())
			newStates |= dotList->activateDots(victim);

		if (nextTick.isPast() || (dotList->getNextTick().compareTo(nextTick) > 0)) {
			Time nextDot = dotList->getNextTick();
			nextTick = nextDot;
		}
	}

	if (nextTick.isPast()) {
		dot = false;
		removeAll();
	}

	if (newStates != dotStates) {
		victim->updateDotStates(dotStates,newStates);
		dotStates = newStates;
	}

	victim->updateStates();
}

bool DamageOverTimeMap::healState(CreatureObject* victim, uint64 dotType, int reduction) {
	if(!hasDot())
		return false;

	uint64 attacker = 0;
	DamageOverTimeList* dotList = NULL;
	resetIterator();

	while (hasNext()) {
		attacker = getNextKey();
		dotList = get(attacker);

		if (reduction < 0)
			break;

		reduction = dotList->healState(dotType,reduction);

	}

	if (reduction >= 0) {
		victim->clearState(dotType);
		//sendStopMessage(victim,dotType);
		victim->updateStates();
		return true;
	}

	sendDecreaseMessage(victim,dotType);
	return false;
}

void DamageOverTimeMap::sendStartMessage(CreatureObject* victim, uint64 type) {
		if (!victim->isPlayer())
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

void DamageOverTimeMap::sendStopMessage(CreatureObject* victim, uint64 type) {
	if (!victim->isPlayer())
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

void DamageOverTimeMap::sendIncreaseMessage(CreatureObject* victim, uint64 type) {
	if (!victim->isPlayer())
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

void DamageOverTimeMap::sendDecreaseMessage(CreatureObject* victim, uint64 type) {
	if (!victim->isPlayer())
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
