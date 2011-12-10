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
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "MissionObject.h"
#include "MissionObserver.h"

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
	CreatureObject* player = cast<CreatureObject*>( getPlayerOwner());

	if (player == NULL)
		return;

	Locker locker(player);

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

int HuntingMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::KILLEDCREATURE) {
		if (cast<CreatureObject*>(observable) != getPlayerOwner())
			return 0;

		CreatureObject* creature = cast<CreatureObject*>(arg1);
		String temp1 = mission->getTemplateString1();
		String temp2 = mission->getTemplateString2();

		if (creature->getServerObjectCRC() == temp1.hashCode() || creature->getServerObjectCRC() == temp2.hashCode()) {
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
