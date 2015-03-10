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
#include "server/zone/objects/group/GroupObject.h"
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
		threatMapObserver = new ThreatMapObserver(self.get());
		threatMapObserver->deploy();
	}

	target->registerObserver(ObserverEventType::HEALINGPERFORMED, threatMapObserver);
}

void ThreatMap::removeObservers() {
	if (size() == 0)
		return;

	Reference<ThreatMapClearObserversTask*> task = new ThreatMapClearObserversTask(*this, threatMapObserver);
	Core::getTaskManager()->executeTask(task);
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
	Locker locker(&lockMutex);

	removeObservers();

	for (int i = 0; i < size(); i++) {
		VectorMapEntry<ManagedReference<CreatureObject*> , ThreatMapEntry> *entry = &elementAt(i);

		ManagedReference<CreatureObject*> key = entry->getKey();
		ThreatMapEntry *value = &entry->getValue();

		ManagedReference<TangibleObject*> selfStrong = self.get();

		// these checks will determine if we should store the damage from the dropped aggressor
		if (key == NULL || selfStrong == NULL || key->isDead() || !key->isOnline() || key->getPlanetCRC() != selfStrong->getPlanetCRC()) {
			remove(i);

			if (threatMapObserver != NULL)
				key->dropObserver(ObserverEventType::HEALINGPERFORMED, threatMapObserver);
		} else {
			value->setNonAggroDamage(value->getTotalDamage());
			value->clearAggro();
		}
	}

	currentThreat = NULL;
	threatMatrix.clear();
}

void ThreatMap::dropDamage(CreatureObject* target) {
	Locker llocker(&lockMutex);

	ManagedReference<TangibleObject*> selfStrong = self.get();
	if (target == NULL || selfStrong == NULL || target->isDead() || !target->isOnline() || target->getPlanetCRC() != selfStrong->getPlanetCRC()) {
		drop(target);

		if (threatMapObserver != NULL)
			target->dropObserver(ObserverEventType::HEALINGPERFORMED, threatMapObserver);
	} else {
		ThreatMapEntry *entry = &get(target);
		entry->setNonAggroDamage(entry->getTotalDamage());
		entry->clearAggro();
	}

	llocker.release();

	if (currentThreat == target)
		currentThreat = NULL;
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
		Reference<ClearThreatStateTask*> clearThreat = new ClearThreatStateTask(self.get(), target, state);
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

		totalDamage += entry->getTotalDamage();
	}

	return totalDamage;
}

CreatureObject* ThreatMap::getHighestDamagePlayer() {
	Locker locker(&lockMutex);

	uint32 maxDamage = 0;
	VectorMap<uint64,uint32> damageMap;
	CreatureObject* player = NULL;

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();

		uint32 totalDamage = entry->getTotalDamage();

		CreatureObject* creature = elementAt(i).getKey();

		if (creature->isPlayerCreature()) {
			if(!damageMap.contains(creature->getObjectID())){
				damageMap.put(creature->getObjectID(),totalDamage);
			} else {
				damageMap.get(creature->getObjectID()) += totalDamage;
			}

			if (damageMap.get(creature->getObjectID()) > maxDamage) {
				maxDamage = damageMap.get(creature->getObjectID());
				player = cast<CreatureObject*>(creature);
			}
		} else if (creature->isPet()) {
			CreatureObject* owner = creature->getLinkedCreature().get();

			if (owner != NULL && owner->isPlayerCreature()) {
				if(!damageMap.contains(owner->getObjectID())){
					damageMap.put(owner->getObjectID(),totalDamage);
				} else {
					damageMap.get(owner->getObjectID()) += totalDamage;
				}

				if (damageMap.get(owner->getObjectID()) > maxDamage) {
					maxDamage = damageMap.get(owner->getObjectID());
					player = cast<CreatureObject*>(owner);
				}
			}
		}
	}

	return player;
}

CreatureObject* ThreatMap::getHighestDamageGroupLeader(){

	Locker locker(&lockMutex);

	VectorMap<uint64,uint32> groupDamageMap;
	int64 highestGroupDmg = 0;

	//Logger::Logger tlog("Threat");

	ManagedReference<CreatureObject*> leaderCreature = NULL;

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();

		uint32 totalDamage = entry->getTotalDamage();

		CreatureObject* creature = elementAt(i).getKey();
		//tlog.info("Group id is " + String::valueOf(creature->getGroupID()),true);
		if(creature->isGrouped()){

			Reference<CreatureObject*> thisleader = (creature->getGroup()->getLeader()).castTo<CreatureObject*>();
			//tlog.info("leader is " + thisleader->getFirstName(),true);

			if(thisleader == NULL || !thisleader->isPlayerCreature())
				break;

			if(!groupDamageMap.contains(creature->getGroupID())){
				//tlog.info("first dmg for group " + String::valueOf(creature->getGroupID()) + " dmg: " + String::valueOf(totalDamage), true);
				groupDamageMap.put(creature->getGroupID(),totalDamage);

			} else {
				groupDamageMap.get(creature->getGroupID()) += totalDamage;
				//tlog.info("adding to group " + String::valueOf(creature->getGroupID()) + "  dmg total: " + String::valueOf(groupDamageMap.get(creature->getGroupID())) + " this player dmg: " + String::valueOf(totalDamage),true);

			}

			if(groupDamageMap.get(creature->getGroupID()) > highestGroupDmg){
				highestGroupDmg = groupDamageMap.get(creature->getGroupID());
				leaderCreature = thisleader;
			}
		} else if (creature->isPet()) {
			CreatureObject* owner = creature->getLinkedCreature().get();

			if (owner != NULL && owner->isPlayerCreature()) {
				if (owner->isGrouped()) {
					Reference<CreatureObject*> thisleader = (owner->getGroup()->getLeader()).castTo<CreatureObject*>();

					if(thisleader == NULL || !thisleader->isPlayerCreature())
						break;

					if(!groupDamageMap.contains(owner->getGroupID())){
						groupDamageMap.put(owner->getGroupID(),totalDamage);
					} else {
						groupDamageMap.get(owner->getGroupID()) += totalDamage;
					}

					if(groupDamageMap.get(owner->getGroupID()) > highestGroupDmg){
						highestGroupDmg = groupDamageMap.get(owner->getGroupID());
						leaderCreature = thisleader;
					}
				} else {
					if(!groupDamageMap.contains(owner->getObjectID())){
						groupDamageMap.put(owner->getObjectID(),totalDamage);
					} else {
						groupDamageMap.get(owner->getObjectID()) += totalDamage;
					}

					if(totalDamage > highestGroupDmg) {
						highestGroupDmg = totalDamage;
						leaderCreature = owner;
					}
				}
			}
		} else {
			//tlog.info("adding single creature damage " + String::valueOf(totalDamage),true);
			groupDamageMap.put(creature->getObjectID(),totalDamage);
			if(totalDamage > highestGroupDmg) {
				highestGroupDmg = totalDamage;
				leaderCreature = creature;
			}

		}
	}
	//tlog.info("highest group is " + leaderCreature->getFirstName() + " damage of " + String::valueOf(highestGroupDmg),true);
	return leaderCreature;
}

CreatureObject* ThreatMap::getHighestThreatCreature() {
	Locker locker(&lockMutex);

	ManagedReference<CreatureObject*> currentThreat = this->currentThreat.get();

	if(currentThreat != NULL && !currentThreat->isDead() && !currentThreat->isIncapacitated()
			&& !currentThreat->isDestroyed() && !cooldownTimerMap.isPast("doEvaluation"))
		return currentThreat;

	threatMatrix.clear();

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();
		CreatureObject* creature = elementAt(i).getKey();

		ManagedReference<CreatureObject*> selfStrong = cast<CreatureObject*>(self.get().get());

		if (!creature->isDead() && !creature->isIncapacitated() && creature->isInRange(selfStrong, 128.f) && creature->isAttackableBy(selfStrong))
			threatMatrix.add(creature, entry);
	}

	this->currentThreat = threatMatrix.getLargestThreat();

	cooldownTimerMap.updateToCurrentAndAddMili("doEvaluation", ThreatMap::EVALUATIONCOOLDOWN);
	return this->currentThreat.get().get();
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
		Reference<RemoveAggroTask*> removeAggroTask = new RemoveAggroTask(self.get(), target, value);
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
