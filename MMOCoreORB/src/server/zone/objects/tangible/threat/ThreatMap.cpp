/*
 * DamageMap.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "ThreatMap.h"
#include "server/zone/objects/tangible/tasks/ClearThreatStateTask.h"
#include "server/zone/objects/tangible/tasks/RemoveAggroTask.h"
#include "ThreatMapClearObserversTask.h"

void ThreatMapEntry::addDamage(WeaponObject* weapon, uint32 damage) {
	addDamage(weapon->getXpType(), damage);
}

void ThreatMapEntry::addDamage(String xp, uint32 damage) {
	int idx = find(xp);

	if (idx == -1) {
		put(xp, damage);

	} else {
		uint32* dmg = &elementAt(idx).getValue();

		*dmg = *dmg + damage;
	}
}

void ThreatMapEntry::setThreatState(uint64 state) {
	if(!threatBitmask & state)
		threatBitmask |= state;

}

bool ThreatMapEntry::hasState(uint64 state) {
	if(threatBitmask & state)
		return true;

	return false;
}

void ThreatMapEntry::clearThreatState(uint64 state) {
	if(threatBitmask & state)
		threatBitmask &= ~state;
}

void ThreatMap::registerObserver(CreatureObject* target) {

	if(threatMapObserver == NULL) {
		threatMapObserver = new ThreatMapObserver(self);
		threatMapObserver->deploy();
	}

	target->registerObserver(ObserverEventType::HEALINGPERFORMED, threatMapObserver);
}

void ThreatMap::removeObservers() {
	if (size() == 0)
		return;

	Reference<ThreatMapClearObserversTask*> task = new ThreatMapClearObserversTask(*this, threatMapObserver);
	Core::getTaskManager()->executeTask(task);

	//moved this to a task so it executes async in a different thread to avoid deadlocks
	/*Locker locker(self);

	for (int i = 0; i < size(); ++i) {
		CreatureObject* creature = elementAt(i).getKey();

		if (creature != NULL && threatMapObserver != NULL) {
			Locker clocker(creature, self);

			creature->dropObserver(ObserverEventType::HEALINGPERFORMED, threatMapObserver);
		}
	}*/
}

void ThreatMap::addDamage(CreatureObject* target, uint32 damage, String xp) {
	Locker locker(&lockMutex);

	int idx = find(target);
	String xpToAward = "";

	if (xp == "") {
		WeaponObject* weapon = target->getWeapon();
		xpToAward = weapon->getXpType();
	} else
		xpToAward = xp;

	if (idx == -1) {
		ThreatMapEntry entry;
		entry.addDamage(xpToAward, damage);
		entry.addAggro(1);

		put(target, entry);
		registerObserver(target);

	} else {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->addDamage(xpToAward, damage);
		entry->addAggro(1);
	}
}

void ThreatMap::removeAll() {
	Locker llocker(&lockMutex);

	removeObservers();
	VectorMap<ManagedReference<CreatureObject*> , ThreatMapEntry>::removeAll();
	currentThreat = NULL;
	threatMatrix.clear();
}

void ThreatMap::dropDamage(CreatureObject* target) {
	Locker llocker(&lockMutex);

	drop(target);

	llocker.release();

	if (currentThreat == target)
		currentThreat = NULL;

	if (threatMapObserver != NULL) {
		target->dropObserver(ObserverEventType::HEALINGPERFORMED, threatMapObserver);
	}
}

bool ThreatMap::setThreatState(CreatureObject* target, uint64 state, uint64 duration, uint64 cooldown) {
	Locker locker(&lockMutex);

	if((hasState(state) && isUniqueState(state))
			|| !cooldownTimerMap.isPast(String::valueOf(state)))
		return false;

	int idx = find(target);

	if (idx == -1) {
		ThreatMapEntry entry;
		entry.setThreatState(state);
		put(target, entry);
		registerObserver(target);

	} else {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->setThreatState(state);
	}

	if(duration > 0) {
		ClearThreatStateTask* clearThreat = new ClearThreatStateTask(self, target, state);
		clearThreat->schedule(duration);
	}

	if(cooldown > 0) {
		cooldownTimerMap.updateToCurrentAndAddMili(String::valueOf(state), duration + cooldown);
	}

	if(isUniqueState(state)) {
		cooldownTimerMap.updateToCurrentTime("doEvaluation");
	}

#ifdef DEBUG
	System::out << "Setting threat state on "  << target->getObjectID() << ": " << state << endl;
#endif

	return true;
}

bool ThreatMap::hasState(uint64 state) {
	Locker locker(&lockMutex);

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();
		if(entry->hasState(state))
			return true;
	}

	return false;
}

bool ThreatMap::isUniqueState(uint64 state) {
	return state & ThreatStates::UNIQUESTATE;
}

void ThreatMap::clearThreatState(CreatureObject* target, uint64 state) {
	Locker locker(&lockMutex);

	int idx = find(target);

	if (idx != -1) {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->clearThreatState(state);

#ifdef DEBUG
		System::out << "Clearing threat state on "  << target->getObjectID() << ": " << state << endl;
#endif
	}
}

uint32 ThreatMap::getTotalDamage() {
	Locker locker(&lockMutex);

	uint32 totalDamage = 0;

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();

		for (int j = 0; j < entry->size(); ++j) {
			uint32 damage = entry->elementAt(j).getValue();

			totalDamage += damage;
		}
	}

	return totalDamage;
}

CreatureObject* ThreatMap::getHighestDamagePlayer() {
	Locker locker(&lockMutex);

	uint32 maxDamage = 0;
	CreatureObject* player = NULL;

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();

		uint32 totalDamage = 0;

		for (int j = 0; j < entry->size(); ++j) {
			uint32 damage = entry->elementAt(j).getValue();

			totalDamage += damage;
		}

		CreatureObject* creature = elementAt(i).getKey();

		if (totalDamage > maxDamage && creature->isPlayerCreature()) {
			maxDamage = totalDamage;
			player = cast<CreatureObject*>(creature);
		}
	}

	return player;
}

CreatureObject* ThreatMap::getHighestThreatCreature() {
	Locker locker(&lockMutex);

	if(currentThreat != NULL
			&& !currentThreat->isDead()
			&& !currentThreat->isIncapacitated()
			&& !cooldownTimerMap.isPast("doEvaluation"))
		return currentThreat;

	threatMatrix.clear();

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();
		CreatureObject* creature = elementAt(i).getKey();

		threatMatrix.add(creature, entry);
	}

	currentThreat = threatMatrix.getLargestThreat();

	cooldownTimerMap.updateToCurrentAndAddMili("doEvaluation", ThreatMap::EVALUATIONCOOLDOWN);
	return currentThreat;
}

void ThreatMap::addAggro(CreatureObject* target, int value, uint64 duration) {
	Locker locker(&lockMutex);

	int idx = find(target);

	if (idx == -1) {
		ThreatMapEntry entry;
		entry.addAggro(value);
		put(target, entry);
		registerObserver(target);

	} else {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->addAggro(value);
	}

	if(duration > 0) {
		RemoveAggroTask* removeAggroTask = new RemoveAggroTask(self, target, value);
		removeAggroTask->schedule(duration);
	}
}

void ThreatMap::removeAggro(CreatureObject* target, int value) {
	Locker locker(&lockMutex);

	int idx = find(target);

	if (idx != -1) {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->removeAggro(value);
	}
}

void ThreatMap::clearAggro(CreatureObject* target) {
	Locker locker(&lockMutex);

	int idx = find(target);

	if (idx != -1) {
		ThreatMapEntry entry;
		entry.clearAggro();
	}
}

void ThreatMap::addHeal(CreatureObject* target, int value) {
	Locker locker(&lockMutex);

	int idx = find(target);

	if (idx == -1) {
		ThreatMapEntry entry;
		entry.addHeal(value);
		entry.addAggro(2);
		put(target, entry);
		registerObserver(target);

	} else {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->addHeal(value);
		entry->addAggro(2);
	}
}
