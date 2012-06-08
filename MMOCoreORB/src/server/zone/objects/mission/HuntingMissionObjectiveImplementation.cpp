/*
 * HuntingMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "HuntingMissionObjective.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "MissionObject.h"
#include "MissionObserver.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"

void HuntingMissionObjectiveImplementation::activate() {
	MissionObjectiveImplementation::activate();

	if (hasObservers())
		return;

	targetsKilled = 15 * getMissionObject().get()->getDifficultyLevel();

	ManagedReference<CreatureObject*> player = getPlayerOwner();

	ManagedReference<MissionObserver*> observer = new MissionObserver(_this.get());
	addObserver(observer, true);

	Locker locker(player);
	player->registerObserver(ObserverEventType::KILLEDCREATURE, observer);
}

void HuntingMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	for (int i = 0; i < getObserverCount(); i++) {
		ManagedReference<MissionObserver*> observer = getObserver(i);

		ManagedReference<CreatureObject*> player = getPlayerOwner();

		if (player != NULL) {
			Locker locker(player);

			player->dropObserver(ObserverEventType::KILLEDCREATURE, observer);

			dropObserver(observer, true);
		}
	}
}

void HuntingMissionObjectiveImplementation::complete() {

	MissionObjectiveImplementation::complete();
}

int HuntingMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<MissionObject* > mission = this->mission.get();

	if (eventType == ObserverEventType::KILLEDCREATURE) {
		if (cast<CreatureObject*>(observable) != getPlayerOwner().get())
			return 0;

		CreatureObject* creature = cast<CreatureObject*>(arg1);
		AiAgent* agent = cast<AiAgent*>(creature);

		if (agent == NULL)
			return 0;

		CreatureTemplate* creatureTemplate = agent->getCreatureTemplate();

		if (creatureTemplate == NULL)
			return 0;

		String temp1 = mission->getTemplateString1();
		String temp2 = mission->getTemplateString2();

		if (creatureTemplate->getTemplateName() == temp1 || creatureTemplate->getTemplateName() == temp2) {
			targetsKilled--;

			if (targetsKilled <= 0) {
				complete();
				return 1;
			}

			StringIdChatParameter message("mission/mission_generic", "hunting_kills_remaining");
			message.setDI(targetsKilled);
			message.setTO(mission->getTargetName());

			getPlayerOwner().get()->sendSystemMessage(message);
		}
	}

	return 0;
}

Vector3 HuntingMissionObjectiveImplementation::getEndPosition() {
	ManagedReference<MissionObject* > mission = this->mission.get();

	Vector3 missionEndPoint;

	missionEndPoint.setX(mission->getStartPositionX());
	missionEndPoint.setY(mission->getStartPositionY());
	TerrainManager* terrain = getPlayerOwner().get()->getZone()->getPlanetManager()->getTerrainManager();
	missionEndPoint.setZ(terrain->getHeight(missionEndPoint.getX(), missionEndPoint.getY()));

	return missionEndPoint;
}
