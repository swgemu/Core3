/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "VisibilityManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/visibility/tasks/VisibilityDecayTask.h"
#include "server/zone/Zone.h"

const String VisibilityManager::factionStringRebel = "rebel";
const String VisibilityManager::factionStringImperial = "imperial";
const unsigned int VisibilityManager::factionRebel = factionStringRebel.hashCode();
const unsigned int VisibilityManager::factionImperial = factionStringImperial.hashCode();

void VisibilityManager::addPlayerToBountyList(CreatureObject* creature, int reward) {
	MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
	missionManager->addPlayerToBountyList(creature->getObjectID(), reward);
	info("Adding player " + String::valueOf(creature->getObjectID()) + " to bounty hunter list.", true);
}

void VisibilityManager::removePlayerFromBountyList(CreatureObject* creature) {
	MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
	missionManager->removePlayerFromBountyList(creature->getObjectID());
	info("Dropping player " + String::valueOf(creature->getObjectID()) + " from bounty hunter list.", true);
}

int VisibilityManager::calculateReward(float visibility) {
	return visibility * 1000 + System::random(5000);
}

float VisibilityManager::calculateVisibilityIncrease(CreatureObject* creature) {
	ManagedReference<Zone*> zone = creature->getZone();

	float visibilityIncrease = 0;

	if (zone != NULL) {
		SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;
		zone->getInRangeObjects(creature->getWorldPositionX(), creature->getWorldPositionY(), 32, &closeObjects, true);

		for (int i = 0; i < closeObjects.size(); ++i) {
			SceneObject* obj = cast<SceneObject*>(closeObjects.get(i).get());
			if (obj->isCreatureObject()) {
				ManagedReference<CreatureObject*> c = cast<CreatureObject*>(obj);
				if (c->isNonPlayerCreatureObject()) {
					if (creature->getFaction() == 0 || (c->getFaction() != factionImperial && c->getFaction() != factionRebel)) {
						visibilityIncrease += 0.5;
					} else {
						if (creature->getFaction() == c->getFaction()) {
							visibilityIncrease += 0.25;
						} else {
							visibilityIncrease += 1;
						}
					}
				}
			}
		}
	}

	info("Increasing visibility for player " + String::valueOf(creature->getObjectID()) + " with " + String::valueOf(visibilityIncrease), true);
	return visibilityIncrease;
}

void VisibilityManager::decreaseVisibility(CreatureObject* creature) {
	ManagedReference<PlayerObject*> ghost = cast<PlayerObject*>(creature->getSlottedObject("ghost"));

	if (ghost != NULL) {
		float visibilityDecrease = ghost->getLastVisibilityUpdateTimestamp().miliDifference() / 1000.f / 3600.f;
		if (ghost->getVisibility() <= visibilityDecrease) {
			clearVisibility(creature);
		} else {
			Locker locker(ghost);
			ghost->setVisibility(ghost->getVisibility() - visibilityDecrease);
			locker.release();

			if (ghost->getVisibility() < TERMINALVISIBILITYLIMIT) {
				removePlayerFromBountyList(creature);
			}
		}
	}
}

VisibilityManager::VisibilityManager() {
	Reference<Task*> decayTask = new VisibilityDecayTask();
	decayTask->schedule(3600 * 1000);
}

void VisibilityManager::login(CreatureObject* creature) {
	ManagedReference<PlayerObject*> ghost = cast<PlayerObject*>(creature->getSlottedObject("ghost"));

	if (ghost != NULL) {
		decreaseVisibility(creature);

		Locker locker(&visibilityListLock);

		if ((ghost->getVisibility() > 0) && (!visibilityList.contains(creature->getObjectID()))) {
			info("Adding player " + String::valueOf(creature->getObjectID()) + " to visibility list.", true);
			visibilityList.put(creature->getObjectID(), creature);
		}

		locker.release();

		if (ghost->getVisibility() >= TERMINALVISIBILITYLIMIT) {
			addPlayerToBountyList(creature, calculateReward(ghost->getVisibility()));
		}
	}
}

void VisibilityManager::logout(CreatureObject* creature) {
	Locker locker(&visibilityListLock);

	if (visibilityList.contains(creature->getObjectID())) {
		info("Dropping player " + String::valueOf(creature->getObjectID()) + " from visibility list.", true);
		visibilityList.drop(creature->getObjectID());

		removePlayerFromBountyList(creature);
	}
}

void VisibilityManager::increaseVisibility(CreatureObject* creature) {
	ManagedReference<PlayerObject*> ghost = cast<PlayerObject*>(creature->getSlottedObject("ghost"));

	if (ghost != NULL) {
		Locker locker(ghost);
		decreaseVisibility(creature);
		ghost->setVisibility(ghost->getVisibility() + calculateVisibilityIncrease(creature));
		locker.release();

		login(creature);
	}
}

void VisibilityManager::clearVisibility(CreatureObject* creature) {
	ManagedReference<PlayerObject*> ghost = cast<PlayerObject*>(creature->getSlottedObject("ghost"));

	if (ghost != NULL) {
		info("Clearing visibility for player " + String::valueOf(creature->getObjectID()), true);

		Locker locker(ghost);
		ghost->setVisibility(0);
		locker.release();

		logout(creature);
	}
}

void VisibilityManager::performVisiblityDecay() {
	Locker locker(&visibilityListLock);

	for (int i = 0; i < visibilityList.size(); i++) {
		ManagedReference<CreatureObject*> creature = visibilityList.get(i);
		decreaseVisibility(creature);
	}
}
