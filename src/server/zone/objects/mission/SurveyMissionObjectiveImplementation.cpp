/*
 * SurveyMissionObjectiveImplementation.cpp
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#include "SurveyMissionObjective.h"
#include "MissionObserver.h"
#include "MissionObject.h"
#include "engine/util/ObserverEventType.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/ZoneServer.h"

void SurveyMissionObjectiveImplementation::activate() {
	if (observers.size() != 0) {
		return;
	}

	PlayerCreature* player = (PlayerCreature*) mission->getParentRecursively(SceneObject::PLAYERCREATURE);

	ManagedReference<MissionObserver*> observer = new MissionObserver(_this);
	ObjectManager::instance()->persistObject(observer, 1, "missionobservers");

	player->registerObserver(ObserverEventType::SAMPLE, observer);

	observers.put(observer);
}

void SurveyMissionObjectiveImplementation::abort() {
	if (observers.size() == 0)
		return;

	ManagedReference<MissionObserver*> observer = observers.get(0);

	if (mission != NULL) {

		PlayerCreature* player = (PlayerCreature*) mission->getParentRecursively(SceneObject::PLAYERCREATURE);

		player->dropObserver(ObserverEventType::SAMPLE, observer);
	}

	observer->destroyObjectFromDatabase();

	observers.drop(observer);
}

void SurveyMissionObjectiveImplementation::complete() {
	PlayerCreature* player = (PlayerCreature*) mission->getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player == NULL)
		return;

	PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
	player->sendMessage(pmm);

	int missionReward = mission->getRewardCredits();

	StringIdChatParameter stringId("mission/mission_generic", "success_w_amount");
	stringId.setDI(missionReward);
	player->sendSystemMessage(stringId);

	player->addBankCredits(missionReward, true);

	ZoneServer* zoneServer = player->getZoneServer();
	MissionManager* missionManager = zoneServer->getMissionManager();

	missionManager->removeMission(mission, player);
}

int SurveyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::SAMPLE) {
		PlayerCreature* player = (PlayerCreature*) mission->getParentRecursively(SceneObject::PLAYERCREATURE);
		ResourceSpawn* sampledSpawn = (ResourceSpawn*) arg1;

		int sampledDensity = (int)arg2;

		if (sampledSpawn == spawn && (sampledDensity >= efficiency)) {

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
