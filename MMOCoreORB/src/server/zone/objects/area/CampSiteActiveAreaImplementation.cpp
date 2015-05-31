/*
 * CampSiteActiveAreaImplementation.cpp
 *
 *  Created on: Jan 1, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/area/CampSiteActiveArea.h"
#include "server/zone/objects/area/CampSiteObserver.h"
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
	Locker locker(&taskMutex);

	if(despawnTask == NULL) {
		despawnTask = new CampDespawnTask(_this.getReferenceUnsafeStaticCast());
	} else {
		if(despawnTask->isScheduled())
			despawnTask->cancel();
	}


	if(abandonTask == NULL) {
		abandonTask = new CampAbandonTask(_this.getReferenceUnsafeStaticCast());
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

	if (camp == NULL || terminal == NULL)
		return;

	CreatureObject* player = cast<CreatureObject*> (object);

	if (player == NULL)
		return;

	if (camp != NULL)
		camp->addTemplateSkillMods(player);

	if (campObserver == NULL) {
		campObserver = new CampSiteObserver(_this.getReferenceUnsafeStaticCast());
		campObserver->deploy();
	}

	if(object == campOwner && !abandoned) {

		Locker locker(&taskMutex);

		if(abandonTask != NULL && abandonTask->isScheduled())
			abandonTask->cancel();

		object->registerObserver(ObserverEventType::STARTCOMBAT, campObserver);

	}

	StringIdChatParameter stringID("camp", "prose_camp_enter");
	stringID.setTO(terminal->getDisplayedName());
	player->sendSystemMessage(stringID);

	player->sendSystemMessage("@camp:sys_camp_heal"); // While in the camp, medics and entertainers can heal your wounds.


	if (object->isPlayerCreature() && !visitors.contains(object->getObjectID()))
		visitors.add(object->getObjectID());


	if (object->isPlayerCreature())
		object->registerObserver(ObserverEventType::HEALINGPERFORMED, campObserver);
}

void CampSiteActiveAreaImplementation::notifyExit(SceneObject* object) {
	object->dropObserver(ObserverEventType::HEALINGPERFORMED, campObserver);

	if (!object->isPlayerCreature())
		return;

	if (camp == NULL || terminal == NULL)
		return;

	CreatureObject* player = cast<CreatureObject*> (object);

	if (player == NULL)
		return;

	if (camp != NULL)
		camp->removeTemplateSkillMods(player);

	StringIdChatParameter stringID("camp", "prose_camp_exit");
	stringID.setTO(terminal->getDisplayedName());
	player->sendSystemMessage(stringID);

	if(abandoned || object != campOwner)
		return;

	Locker locker(&taskMutex);

	if(!abandoned && abandonTask != NULL && !abandonTask->isScheduled()) {
		try {
			abandonTask->schedule(CampSiteActiveArea::ABANDONTIME);
		} catch (Exception& e) {

		}
	}
}

int CampSiteActiveAreaImplementation::notifyHealEvent(int64 quantity) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	// Increase XP Pool for heals
	currentXp += (campStructureData->getExperience() / 180);
	return 1;
}

int CampSiteActiveAreaImplementation::notifyCombatEvent() {
	Locker locker(&taskMutex);

	if(abandonTask != NULL) {
		if(abandonTask->isScheduled())
			abandonTask->cancel();

	} else {
		abandonTask = new CampAbandonTask(_this.getReferenceUnsafeStaticCast());
	}

	abandonTask->execute();

	return 1;
}

void CampSiteActiveAreaImplementation::abandonCamp() {
	abandoned = true;

	currentXp = 0;

	Locker locker(&taskMutex);

	if(despawnTask != NULL && despawnTask->isScheduled()) {
		despawnTask->cancel();
		int newTime = (CampSiteActiveArea::DESPAWNTIME / 6);
		int maxTime = CampSiteActiveArea::DESPAWNTIME - ((System::getTime() - timeCreated) * 1000);

		despawnTask->schedule(newTime < maxTime ? newTime : maxTime);
	}

	if(terminal != NULL) {
		Locker clocker(terminal, _this.getReferenceUnsafeStaticCast());
		terminal->setCustomObjectName("Abandoned Camp", true);
	}

	if(campOwner != NULL) {
		campOwner->dropObserver(ObserverEventType::STARTCOMBAT, campObserver);
		campOwner->sendSystemMessage("@camp:sys_abandoned_camp"); // Your camp has been abandoned.
	}
}

bool CampSiteActiveAreaImplementation::despawnCamp() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if(!abandoned && campOwner != NULL && campOwner->getZoneServer() != NULL) {
		/// Get Player Manager
		PlayerManager* playerManager = campOwner->getZoneServer()->getPlayerManager();
		if (playerManager == NULL) {
			error("playerManager is null");
			return false;
		}

		float durationUsed = ((float)(System::getTime() - timeCreated)) / (campStructureData->getDuration() / 4);
		if (durationUsed > 1)
			durationUsed = 1;

		int amount = 0;
		int campXp = campStructureData->getExperience();
		amount = (int)(campXp * durationUsed);

		amount += (int)((visitors.size() -1) * (campXp / 30) * durationUsed);
		amount += (int)(currentXp * durationUsed);

		playerManager->awardExperience(campOwner, "camp", amount, true);
	}

	Locker tlocker(&taskMutex);

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

	tlocker.release();

	if(campOwner != NULL)
		campOwner->dropObserver(ObserverEventType::STARTCOMBAT, campObserver);

	if (camp != NULL) {
		if(camp->getZone() == NULL)
			return false;

		StructureManager::instance()->destroyStructure(camp);
	}

	destroyObjectFromWorld(true);
	destroyObjectFromDatabase(true);


	return true;
}

void CampSiteActiveAreaImplementation::assumeOwnership(CreatureObject* player) {
	if (camp == NULL || player == NULL)
		return;

	if (player->getSkillMod("camp") < campStructureData->getSkillRequired()) {
		player->sendSystemMessage("@camp:error_too_big"); // You cannot assume ownership of this camp. You lack the skill to maintain a camp of this size.
		return;
	}

	PlayerObject* playerGhost = player->getPlayerObject();

	if (playerGhost == NULL)
		return;

	for (int i = 0; i < playerGhost->getTotalOwnedStructureCount(); ++i) {
		uint64 oid = playerGhost->getOwnedStructure(i);

		ManagedReference<StructureObject*> structure = playerGhost->getZoneServer()->getObject(oid).castTo<StructureObject*>();

		if (structure->isCampStructure()) {
			player->sendSystemMessage("@camp:sys_already_camping"); // But you already have a camp established elsewhere!
			return;
		}
	}

	Locker clocker(campOwner, _this.getReferenceUnsafeStaticCast());

	PlayerObject* ownerGhost = campOwner->getPlayerObject();

	if (ownerGhost != NULL) {
		ownerGhost->removeOwnedStructure(camp);
	}

	clocker.release();

	setOwner(player);

	abandoned = false;
	currentXp = 0;
	visitors.removeAll();

	Reference<SortedVector<ManagedReference<QuadTreeEntry*> >*> closeObjects = new SortedVector<ManagedReference<QuadTreeEntry*> >();
	zone->getInRangeObjects(camp->getWorldPositionX(), camp->getWorldPositionY(), campStructureData->getRadius(), closeObjects, true);

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* scno = cast<SceneObject*>(closeObjects->get(i).get());
		if (scno->isPlayerCreature())
			visitors.add(scno->getObjectID());
	}

	Locker clocker2(player, _this.getReferenceUnsafeStaticCast());

	playerGhost->addOwnedStructure(camp);

	campOwner->registerObserver(ObserverEventType::STARTCOMBAT, campObserver);

	Locker locker(&taskMutex);

	if(abandonTask != NULL && abandonTask->isScheduled())
		abandonTask->cancel();

	if(despawnTask != NULL && despawnTask->isScheduled())
		despawnTask->cancel();

	timeCreated = System::getTime();
	despawnTask->schedule(CampSiteActiveArea::DESPAWNTIME);

	if(terminal != NULL) {
		String campName = campOwner->getFirstName();
		if(!campOwner->getLastName().isEmpty())
			campName += " " + campOwner->getLastName();
		campName += "'s Camp";
		terminal->setCustomObjectName(campName, true);
	}

	player->sendSystemMessage("@camp:assuming_ownership"); //You assume ownership of the camp.
}

void CampSiteActiveAreaImplementation::setOwner(CreatureObject* player) {
	campOwner = player;

	Locker clocker(camp, _this.getReferenceUnsafeStaticCast());
	camp->setOwner(player->getObjectID());
}
