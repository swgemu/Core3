/*
 * CampSiteActiveAreaImplementation.cpp
 *
 *  Created on: Jan 1, 2012
 *      Author: Kyle
 */

#include "CampSiteActiveArea.h"
#include "CampSiteObserver.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/area/events/CampAbandonTask.h"
#include "server/zone/objects/area/events/CampDespawnTask.h"

void CampSiteActiveAreaImplementation::initializeTransientMembers() {
	startTasks();
}

void CampSiteActiveAreaImplementation::init(CampStructureTemplate* campData) {
	campStructureData = campData;
	setRadius(campStructureData->getRadius());
	startTasks();
}

void CampSiteActiveAreaImplementation::startTasks() {
	if(despawnTask == NULL) {
		despawnTask = new CampDespawnTask(_this);
	} else {
		if(despawnTask->isScheduled())
			despawnTask->cancel();
	}


	if(abandonTask == NULL) {
		abandonTask = new CampAbandonTask(_this);
	} else {
		if(abandonTask->isScheduled())
			abandonTask->cancel();
	}

	despawnTask->schedule(CampSiteActiveArea::DESPAWNTIME);
	abandonTask->schedule(CampSiteActiveArea::ABANDONTIME);

}

void CampSiteActiveAreaImplementation::notifyEnter(SceneObject* object) {
	if (!object->isPlayerCreature())
		return;

	CreatureObject* player = cast<CreatureObject*> (object);

	if (player == NULL)
		return;

	camp->addTemplateSkillMods(player);

	if (campObserver == NULL) {
		campObserver = new CampSiteObserver(_this);
		campObserver->deploy();
	}

	if(object == campOwner && !abandoned) {

		if(abandonTask->isScheduled())
			abandonTask->cancel();

		object->registerObserver(ObserverEventType::STARTCOMBAT, campObserver);

	} else {

		StringIdChatParameter stringID("camp", "prose_camp_enter");
		stringID.setTO(terminal->getDisplayedName());
		player->sendSystemMessage(stringID);

		player->sendSystemMessage("@camp:sys_camp_heal");

	}

	if (object->isPlayerCreature() && !visitors.contains(object->getObjectID()))
		visitors.add(object->getObjectID());


	if (object->isPlayerCreature())
		object->registerObserver(ObserverEventType::HEALINGPERFORMED, campObserver);
}

void CampSiteActiveAreaImplementation::notifyExit(SceneObject* object) {
	object->dropObserver(ObserverEventType::HEALINGPERFORMED, campObserver);

	if (!object->isPlayerCreature())
		return;

	CreatureObject* player = cast<CreatureObject*> (object);

	if (player == NULL)
		return;

	camp->removeTemplateSkillMods(player);

	if(abandoned || object != campOwner) {
		StringIdChatParameter stringID("camp", "prose_camp_exit");
		stringID.setTO(terminal->getDisplayedName());
		player->sendSystemMessage(stringID);
		return;
	}


	if(!abandoned && abandonTask != NULL) {
		abandonTask->schedule(CampSiteActiveArea::ABANDONTIME);
	}
}

int CampSiteActiveAreaImplementation::notifyHealEvent(int64 quantity) {
	// Increase XP Pool for heals
	currentXp += 5;
	return 1;
}

int CampSiteActiveAreaImplementation::notifyCombatEvent() {
	abandonCamp();

	if(abandonTask != NULL)
		if(abandonTask->isScheduled())
			abandonTask->cancel();

	if(campOwner != NULL)
		campOwner->sendSystemMessage("@camp:sys_abandoned_camp");

	return 1;
}

void CampSiteActiveAreaImplementation::abandonCamp() {
	abandoned = true;

	currentXp = 0;

	if(despawnTask != NULL && despawnTask->isScheduled()) {
		despawnTask->cancel();
		int newTime = (CampSiteActiveArea::DESPAWNTIME / 6);
		int maxTime = CampSiteActiveArea::DESPAWNTIME - ((System::getTime() - timeCreated) * 1000);

		despawnTask->schedule(newTime < maxTime ? newTime : maxTime);
	}

	if(terminal != NULL)
		terminal->setCustomObjectName("Abandoned Camp", true);

	if(campOwner != NULL) {
		campOwner->dropObserver(ObserverEventType::STARTCOMBAT, campObserver);
		campOwner->sendSystemMessage("@camp:sys_abandoned_camp");
	}
}

bool CampSiteActiveAreaImplementation::despawnCamp() {

	if(!abandoned && campOwner != NULL && campOwner->getZoneServer() != NULL) {
		/// Get Player Manager
		PlayerManager* playerManager = campOwner->getZoneServer()->getPlayerManager();
		if (playerManager == NULL) {
			error("playerManager is null");
			return false;
		}

		float durationUsed = ((float)(System::getTime() - timeCreated)) / (campStructureData->getDuration());

		int amount = 0;
		amount += (int)(campStructureData->getExperience() * durationUsed);
		amount += ((visitors.size() -1) * 15);
		amount += currentXp;

		int awarded = (amount > campStructureData->getExperience() ? campStructureData->getExperience() : amount);

		playerManager->awardExperience(campOwner, "camp", awarded, true);
	}

	if(despawnTask != NULL ) {
		if(despawnTask->isScheduled())
			despawnTask->cancel();
		despawnTask = NULL;
	}


	if(abandonTask != NULL) {
		if(abandonTask->isScheduled())
			abandonTask->cancel();
		abandonTask = NULL;
	}

	if(campOwner != NULL)
		campOwner->dropObserver(ObserverEventType::STARTCOMBAT, campObserver);

	if(camp->getZone() == NULL)
		return false;

	ManagedReference<StructureManager*> structureManager = camp->getZone()->getStructureManager();
	if (structureManager == NULL) {
		error("Unable to get StructureManager when placing camp");
		return false;
	}

	destroyObjectFromWorld(true);
	destroyObjectFromDatabase(true);
	structureManager->destroyStructure(camp);

	return true;
}

void CampSiteActiveAreaImplementation::assumeOwnership(CreatureObject* player) {

	/// Get Ghost
	PlayerObject* ghost = campOwner->getPlayerObject();

	if (ghost != NULL) {
		ghost->removeOwnedStructure(camp);
	}

	setOwner(player);

	abandoned = false;
	currentXp = 0;

	/// Get Ghost
	ghost = campOwner->getPlayerObject();

	if (ghost != NULL) {
		ghost->addOwnedStructure(camp);
	}

	player->registerObserver(ObserverEventType::STARTCOMBAT, campObserver);

	if(abandonTask != NULL && abandonTask->isScheduled())
		abandonTask->cancel();

	if(terminal != NULL) {
		String campName = player->getFirstName();
		if(!player->getLastName().isEmpty())
			campName += " " + player->getLastName();
		campName += "'s Camp";
		terminal->setCustomObjectName(campName, true);
	}
}
