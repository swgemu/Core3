/*
 * CampSiteActiveAreaImplementation.cpp
 *
 *  Created on: Jan 1, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/staticobject/StaticObject.h"
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
	ActiveAreaImplementation::initializeTransientMembers();

	startTasks();

	Core::getTaskManager()->executeTask([weakCampSiteArea = WeakReference<CampSiteActiveArea*>(_this.getReferenceUnsafeStaticCast())]() {
		auto strongCampSiteArea = weakCampSiteArea.get();

		if (strongCampSiteArea != nullptr) {
			Locker lock(strongCampSiteArea);
			strongCampSiteArea->setAbandoned(strongCampSiteArea->isAbandoned());
		}
	}, "InitCampSiteActiveArea");
}

void CampSiteActiveAreaImplementation::init(CampStructureTemplate* campData) {
	campStructureData = campData;
	setRadius(campStructureData->getRadius());
	startTasks();
}

void CampSiteActiveAreaImplementation::startTasks() {
	Locker locker(&taskMutex);

	if(despawnTask == nullptr) {
		despawnTask = new CampDespawnTask(_this.getReferenceUnsafeStaticCast());
	} else {
		if(despawnTask->isScheduled())
			despawnTask->cancel();
	}


	if(abandonTask == nullptr) {
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

	if (camp == nullptr || terminal == nullptr)
		return;

	CreatureObject* player = cast<CreatureObject*> (object);

	if (player == nullptr)
		return;

	camp->addTemplateSkillMods(player);

	if (campObserver == nullptr) {
		campObserver = new CampSiteObserver(_this.getReferenceUnsafeStaticCast());
		campObserver->deploy();
	}

	if(object == campOwner && !abandoned) {

		Locker locker(&taskMutex);

		if(abandonTask != nullptr && abandonTask->isScheduled())
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
		object->registerObserver(ObserverEventType::HEALINGRECEIVED, campObserver);
}

void CampSiteActiveAreaImplementation::notifyExit(SceneObject* object) {
	object->dropObserver(ObserverEventType::HEALINGRECEIVED, campObserver);

	if (!object->isPlayerCreature())
		return;

	if (camp == nullptr || terminal == nullptr)
		return;

	CreatureObject* player = cast<CreatureObject*> (object);

	if (player == nullptr)
		return;

	camp->removeTemplateSkillMods(player);

	StringIdChatParameter stringID("camp", "prose_camp_exit");
	stringID.setTO(terminal->getDisplayedName());
	player->sendSystemMessage(stringID);

	if(abandoned || object != campOwner)
		return;

	Locker locker(&taskMutex);

	if(!abandoned && abandonTask != nullptr && !abandonTask->isScheduled()) {
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
	return 0;
}

int CampSiteActiveAreaImplementation::notifyCombatEvent() {
	Locker locker(&taskMutex);

	if(abandonTask != nullptr) {
		if(abandonTask->isScheduled())
			abandonTask->cancel();

	} else {
		abandonTask = new CampAbandonTask(_this.getReferenceUnsafeStaticCast());
	}

	abandonTask->execute();

	return 1;
}

void CampSiteActiveAreaImplementation::setAbandoned(bool isAbandoned) {
	abandoned = isAbandoned;

	if (campFire != nullptr) {
		Locker clocker(campFire, _this.getReferenceUnsafeStaticCast());
		campFire->destroyObjectFromWorld(true);
	}

	ZoneServer* zServ = getZoneServer();
	Zone* thisZone = getZone();

	if (zServ == nullptr || thisZone == nullptr)
		return;

	String fireTemplate = "object/static/structure/general/campfire_fresh.iff";

	if (isAbandoned)
		fireTemplate = "object/static/structure/general/campfire_smoldering.iff";

	ManagedReference<StaticObject*> fire = (zServ->createObject(fireTemplate.hashCode(), 0)).castTo< StaticObject*>();

	if (fire == nullptr)
		return;

	float posX = getPositionX();
	float posY = getPositionY();
	float posZ = thisZone->getHeight(posX, posY);

	Locker locker(fire);

	fire->initializePosition(posX, posZ, posY);

	thisZone->transferObject(fire, -1, true);

	campFire = fire;
}

void CampSiteActiveAreaImplementation::abandonCamp() {
	setAbandoned(true);

	currentXp = 0;

	Locker locker(&taskMutex);

	if(despawnTask != nullptr && despawnTask->isScheduled()) {
		despawnTask->cancel();
		int newTime = (CampSiteActiveArea::DESPAWNTIME / 6);
		int maxTime = CampSiteActiveArea::DESPAWNTIME - ((System::getTime() - timeCreated) * 1000);

		despawnTask->schedule(newTime < maxTime ? newTime : maxTime);
	}

	if(terminal != nullptr) {
		Locker clocker(terminal, _this.getReferenceUnsafeStaticCast());
		terminal->setCustomObjectName("Abandoned Camp", true);
	}

	if(campOwner != nullptr) {
		campOwner->dropObserver(ObserverEventType::STARTCOMBAT, campObserver);
		campOwner->sendSystemMessage("@camp:sys_abandoned_camp"); // Your camp has been abandoned.
	}
}

bool CampSiteActiveAreaImplementation::despawnCamp() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if(!abandoned && campOwner != nullptr && campOwner->getZoneServer() != nullptr) {
		/// Get Player Manager
		PlayerManager* playerManager = campOwner->getZoneServer()->getPlayerManager();
		if (playerManager == nullptr) {
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

	if(despawnTask != nullptr ) {
		if(despawnTask->isScheduled())
			despawnTask->cancel();
		despawnTask = nullptr;
	}


	if(abandonTask != nullptr) {
		if(abandonTask->isScheduled())
			abandonTask->cancel();
		abandonTask = nullptr;
	}

	tlocker.release();

	if(campOwner != nullptr)
		campOwner->dropObserver(ObserverEventType::STARTCOMBAT, campObserver);

	if (camp != nullptr) {
		if(camp->getZone() == nullptr)
			return false;

		StructureManager::instance()->destroyStructure(camp);
	}

	if (campFire != nullptr) {
		Locker clocker(campFire, _this.getReferenceUnsafeStaticCast());
		campFire->destroyObjectFromWorld(true);
	}

	destroyObjectFromWorld(true);
	destroyObjectFromDatabase(true);


	return true;
}

void CampSiteActiveAreaImplementation::assumeOwnership(CreatureObject* player) {
	if (camp == nullptr || player == nullptr)
		return;

	if (player->getSkillMod("camp") < campStructureData->getSkillRequired()) {
		player->sendSystemMessage("@camp:error_too_big"); // You cannot assume ownership of this camp. You lack the skill to maintain a camp of this size.
		return;
	}

	PlayerObject* playerGhost = player->getPlayerObject();

	if (playerGhost == nullptr)
		return;

	for (int i = 0; i < playerGhost->getTotalOwnedStructureCount(); ++i) {
		uint64 oid = playerGhost->getOwnedStructure(i);

		ManagedReference<StructureObject*> structure = playerGhost->getZoneServer()->getObject(oid).castTo<StructureObject*>();

		if (structure != nullptr && structure->isCampStructure()) {
			player->sendSystemMessage("@camp:sys_already_camping"); // But you already have a camp established elsewhere!
			return;
		}
	}

	Locker clocker(campOwner, _this.getReferenceUnsafeStaticCast());

	auto zone = this->zone;

	if (zone == nullptr) {
		return;
	}

	PlayerObject* ownerGhost = campOwner->getPlayerObject();

	if (ownerGhost != nullptr) {
		ownerGhost->removeOwnedStructure(camp);
	}

	clocker.release();

	setOwner(player);

	setAbandoned(false);
	currentXp = 0;
	visitors.removeAll();

	Reference<SortedVector<ManagedReference<QuadTreeEntry*> >*> closeObjects = new SortedVector<ManagedReference<QuadTreeEntry*> >();
	zone->getInRangeObjects(camp->getWorldPositionX(), camp->getWorldPositionY(), campStructureData->getRadius(), closeObjects, true);

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* scno = static_cast<SceneObject*>(closeObjects->get(i).get());
		if (scno->isPlayerCreature())
			visitors.add(scno->getObjectID());
	}

	Locker clocker2(player, _this.getReferenceUnsafeStaticCast());

	playerGhost->addOwnedStructure(camp);

	campOwner->registerObserver(ObserverEventType::STARTCOMBAT, campObserver);

	Locker locker(&taskMutex);

	if(abandonTask != nullptr && abandonTask->isScheduled())
		abandonTask->cancel();

	if(despawnTask != nullptr && despawnTask->isScheduled())
		despawnTask->cancel();

	timeCreated = System::getTime();
	despawnTask->schedule(CampSiteActiveArea::DESPAWNTIME);

	if(terminal != nullptr) {
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
