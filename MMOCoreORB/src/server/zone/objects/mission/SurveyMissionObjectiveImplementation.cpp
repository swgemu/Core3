/*
 * SurveyMissionObjectiveImplementation.cpp
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#include "SurveyMissionObjective.h"
#include "MissionObserver.h"
#include "MissionObject.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/ZoneServer.h"

void SurveyMissionObjectiveImplementation::activate() {
	if (observers.size() != 0) {
		return;
	}

	if(mission != NULL) {
		CreatureObject* player = cast<CreatureObject*>( mission->getParentRecursively(SceneObjectType::PLAYERCREATURE));
		if (player != NULL) {
			ManagedReference<MissionObserver*> observer = new MissionObserver(_this);
			ObjectManager::instance()->persistObject(observer, 1, "missionobservers");

			player->registerObserver(ObserverEventType::SURVEY, observer);

			observers.put(observer);
		}
	}
}

void SurveyMissionObjectiveImplementation::abort() {
	if (observers.size() == 0)
		return;

	ManagedReference<MissionObserver*> observer = observers.get(0);

	if (mission != NULL) {

		CreatureObject* player = cast<CreatureObject*>( mission->getParentRecursively(SceneObjectType::PLAYERCREATURE));

		player->dropObserver(ObserverEventType::SURVEY, observer);
	}

	observer->destroyObjectFromDatabase();

	observers.drop(observer);
}

void SurveyMissionObjectiveImplementation::complete() {

	MissionObjectiveImplementation::complete();
}

int SurveyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::SURVEY) {
		CreatureObject* player = cast<CreatureObject*>( mission->getParentRecursively(SceneObjectType::PLAYERCREATURE));
		ResourceSpawn* sampledSpawn = cast<ResourceSpawn*>( arg1);

		int sampledDensity = (int)arg2;
		if (sampledSpawn->getFamilyName() == spawnFamily && (sampledDensity >= efficiency)) {

			if (!player->isInRange(missionGiver, 1024)) {
				complete();

				return 1;
			} else {
				StringIdChatParameter stringId("mission/mission_generic", "survey_too_close");
				stringId.setDI(1024);
				stringId.setDF(player->getDistanceTo(missionGiver));
				player->sendSystemMessage(stringId);

				return 0;
			}
		} else
			return 0;
	}

	observer->destroyObjectFromDatabase();
	observers.drop(observer);

	updateToDatabase();

	return 1;
}
