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
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "MissionObject.h"
#include "MissionObserver.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"

void HuntingMissionObjectiveImplementation::activate() {
	if (observers.size() != 0)
		return;

	targetsKilled = 15 * getMissionObject()->getDifficultyLevel();

	CreatureObject* player = getPlayerOwner();

	ManagedReference<MissionObserver*> observer = new MissionObserver(_this);
	ObjectManager::instance()->persistObject(observer, 1, "missionobservers");

	Locker locker(player);
	player->registerObserver(ObserverEventType::KILLEDCREATURE, observer);
	observers.put(observer);
}

void HuntingMissionObjectiveImplementation::abort() {
	if (observers.size() != 0) {
		for (int i = 0; i < observers.size(); i++) {
			ManagedReference<MissionObserver*> observer = observers.get(i);

			CreatureObject* player = getPlayerOwner();

			if (player != NULL) {
				Locker locker(player);

				player->dropObserver(ObserverEventType::KILLEDCREATURE, observer);
				observer->destroyObjectFromDatabase();

				observers.drop(observer);
			}
		}
	}
}

void HuntingMissionObjectiveImplementation::complete() {

	MissionObjectiveImplementation::complete();
}

int HuntingMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::KILLEDCREATURE) {
		if (cast<CreatureObject*>(observable) != getPlayerOwner())
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

			getPlayerOwner()->sendSystemMessage(message);
		}
	}

	return 0;
}
