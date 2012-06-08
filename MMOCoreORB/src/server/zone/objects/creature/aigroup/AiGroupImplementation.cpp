/*
 * AiGroupImplementation.cpp
 *
 *  Created on: Oct 31, 2010
 *      Author: dannuic
 */

#include "AiGroup.h"
#include "AiGroupObserver.h"
#include "server/zone/objects/creature/PatrolPoint.h"
#include "server/zone/objects/creature/PatrolPointsVector.h"
#include "engine/util/u3d/Coordinate.h"
#include "server/zone/objects/creature/CreatureFlag.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/creature/SpawnGroup.h"
#include "server/zone/managers/creature/StaticSpawnGroup.h"
#include "server/zone/managers/creature/DynamicSpawnGroup.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/scene/SceneObject.h"

void AiGroupImplementation::setPatrolPoints() {
	if (wanderRadius == 0)
		return;

	for (int i = 0; i < scouts.size(); ++i)
		setPatrolPoint(scouts.get(i));

	for (int i = 0; i < protectors.size(); ++i)
		setPatrolPoint(protectors.get(i));

	for (int i = 0; i < babies.size(); ++i)
		setPatrolPoint(babies.get(i));
}

void AiGroupImplementation::setPatrolPoint(AiAgent* member) {
	if (member == NULL)
		return;

	if (member == leader && !isStatic) {
		setPosition(member->getPositionX(), member->getPositionZ(), member->getPositionY());
		// TODO: check to make sure not wandering into static areas and out of original area
	}

	Coordinate coord(getPositionX(), 0, getPositionY());

	float radius = wanderRadius;
	if (scouts.contains(member))
		radius *= 3;

	coord.randomizePosition(radius);

	member->setNextPosition(coord.getPositionX(), getZone()->getHeight(coord.getPositionX(), coord.getPositionY()), coord.getPositionY(), getParent().get());
	member->activateWaitEvent();
}

void AiGroupImplementation::setup(StaticSpawnGroup* templ) {
	// in static groups, all members are protectors
	// designate the first in the template as the leader
	isStatic = true;

	CreatureManager* cm = getZone()->getCreatureManager();
	if (cm == NULL)
		return;

	commandLevel = templ->getCommandLevel();
	wanderRadius = templ->getWanderRadius();

	uint64 cellID = templ->getCellID();

	if (cellID != 0) {
		SceneObject* cellParent = getZone()->getZoneServer()->getObject(cellID);

		if (cellParent != NULL) {
			if (!cellParent->isCellObject())
				cellParent = NULL;
			else
				cellParent->transferObject(_this.get(), -1);
		}

		//setParent(cellParent);
	}

	Vector<SpawnCoordinate>* members = templ->getSpawnList();

	for (int i = 0; i < members->size(); ++i) {
		SpawnCoordinate* protTempl = &members->get(i);

		uint32 crc = protTempl->getTemplateName().hashCode();
		Coordinate* coordinate = protTempl->getCoordinate();
		float x = coordinate->getPositionX();
		float z = coordinate->getPositionZ();
		float y = coordinate->getPositionY();

		if (cellID == 0) {
			x += getPositionX();
			y += getPositionY();
			z += getPositionZ();
		}

		ManagedReference<AiAgent*> prot = dynamic_cast<AiAgent*>(cm->spawnCreature(crc, 0, x, z, y, cellID));
		if (prot == NULL)
			continue;

		Quaternion* dir = protTempl->getDirection();

		prot->setDirection(dir->getW(), dir->getX(), dir->getY(), dir->getZ());
		prot->setRespawnTimer(templ->getRespawnTime());
		prot->setHomeLocation(x, z, y, prot->getParent().get());

		protectors.add(prot);

		if (protectors.size() == 1)
			leader = prot;

		AiGroupObserver* moveObserver = new AiGroupObserver(_this.get());
		ObjectManager::instance()->persistObject(moveObserver, 1, "aiobservers");
		prot->registerObserver(ObserverEventType::DESTINATIONREACHED, moveObserver);
		observers.put(moveObserver);
	}

	setPatrolPoints();
}

void AiGroupImplementation::setup(DynamicSpawnGroup* templ) {
	// dynamic groups specify scouts, protectors, and babies in the template
	// don't assign the leader until the group spawns stuff
	isStatic = false;

	commandLevel = templ->getCommandLevel();
	wanderRadius = templ->getWanderRadius();

	size = templ->getSize();

	scoutTemps = templ->getScoutTemplates();
	scoutWeight = templ->getScoutWeight();

	protectorTemps = templ->getProtectorTemplates();
	protectorWeight = templ->getProtectorWeight();

	babyTemps = templ->getBabyTemplates();
	babyWeight = templ->getBabyWeight();

	setPatrolPoints();
}

int AiGroupImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	AiAgent* member = cast<AiAgent*>(observable);

	switch (eventType) {
	case ObserverEventType::DESTINATIONREACHED:
		setPatrolPoint(member);
		break;
	default:
		break;
	}

	return 0;
}
