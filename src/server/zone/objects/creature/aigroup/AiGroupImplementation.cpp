/*
 * AiGroupImplementation.cpp
 *
 *  Created on: Oct 31, 2010
 *      Author: dannuic
 */

#include "AiGroup.h"
#include "server/zone/objects/creature/PatrolPoint.h"
#include "server/zone/objects/creature/PatrolPointsVector.h"
#include "engine/util/Coordinate.h"
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

	// TODO: set up patrol points, will need to register observers
	// on each creature (for more than just patrol points)
	// and then add a new patrol point after one is reached
	// this function will just be for initial spawning
	// TODO: only setup patrol points for static areas once
	// maybe this function is only for static, dynamic will
	// set up patrol points based on current position of the group
}

void AiGroupImplementation::setup(StaticSpawnGroup* templ) {
	// in static groups, all members are protectors
	// designate the first in the template as the leader
	// spawn stuff here, since it's static

	CreatureManager* cm = zone->getCreatureManager();
	if (cm == NULL)
		return;

	commandLevel = templ->getCommandLevel();
	wanderRadius = templ->getWanderRadius();

	uint64 cellID = templ->getCellID();

	if (cellID != 0) {
		SceneObject* cellParent = zone->getZoneServer()->getObject(cellID);

		if (cellParent != NULL) {
			if (!cellParent->isCellObject())
				cellParent = NULL;
			else
				cellParent->addObject((SceneObject*)this, -1);
		}

		setParent(cellParent);
	}

	Vector<SpawnCoordinate> members = templ->getSpawnList();

	for (int i = 0; i < members.size(); ++i) {
		SpawnCoordinate protTempl = members.get(i);

		uint32 crc = protTempl.getTemplateName().hashCode();
		float x = protTempl.getPositionX() + getPositionX();
		float z = protTempl.getPositionZ() + getPositionZ();
		float y = protTempl.getPositionY() + getPositionY();

		ManagedReference<AiAgent*> prot = dynamic_cast<AiAgent*>(cm->spawnCreature(crc, 0, x, z, y, cellID));
		if (prot == NULL)
			continue;

		prot->setDirection(protTempl.getW(), protTempl.getX(), protTempl.getY(), protTempl.getZ());
		prot->setRespawnTimer(templ->getRespawnTime());
		prot->setHomeLocation(x, z, y, prot->getParent());

		protectors.add(prot);

		if (protectors.size() == 1)
			leader = prot;

		setPatrolPoints();
	}
}

void AiGroupImplementation::setup(DynamicSpawnGroup* templ) {
	// dynamic groups specify scouts, protectors, and babies in the template
	// don't assign the leader until the group spawns stuff
	// spawn stuff dynamically, just set up the basics here

	commandLevel = templ->getCommandLevel();
	wanderRadius = templ->getWanderRadius();

	size = templ->getSize();

	scoutTemps = templ->getScoutTemplates();
	scoutWeight = templ->getScoutWeight();

	protectorTemps = templ->getProtectorTemplates();
	protectorWeight = templ->getProtectorWeight();

	babyTemps = templ->getBabyTemplates();
	babyWeight = templ->getBabyWeight();
}
