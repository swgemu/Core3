/*
 * DeliverMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "DeliverMissionObjective.h"
#include "server/zone/objects/area/MissionSpawnActiveArea.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "MissionObject.h"
#include "MissionObserver.h"

void DeliverMissionObjectiveImplementation::activate() {
	if (observers.size() != 0)  {
		return;
	}

	SceneObject* targetObject = mission->getMissionTarget();
	SceneObject* targetObjectDest = mission->getMissionTargetDest();
	if (targetObject == NULL || !targetObject->isCreatureObject() || targetObjectDest == NULL || !targetObjectDest->isCreatureObject())
		return;

	CreatureObject* targetCreature = (CreatureObject*)targetObject;
	CreatureObject* targetCreatureDest = (CreatureObject*)targetObjectDest;
	if (!targetCreature->isAiAgent() || !targetCreatureDest->isAiAgent())
		return;

	target = (AiAgent*)targetCreature;
	targetDest = (AiAgent*)targetCreatureDest;
	objectiveStatus = 0;

	ManagedReference<MissionObserver*> observer1 =  new MissionObserver(_this);
	ObjectManager::instance()->persistObject(observer1, 1, "missionobservers");

	Locker locker1(target);
	target->registerObserver(ObserverEventType::CONVERSE, observer1);
	observers.put(observer1);
	locker1.release();

	ManagedReference<MissionObserver*> observer2 =  new MissionObserver(_this);
	ObjectManager::instance()->persistObject(observer2, 1, "missionobservers");

	Locker locker2(targetDest);
	targetDest->registerObserver(ObserverEventType::CONVERSE, observer2);
	observers.put(observer2);

	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL)
		waypoint = mission->createWaypoint();

	waypoint->setPlanetCRC(mission->getStartPlanetCRC());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
}

void DeliverMissionObjectiveImplementation::abort() {
	for (int i = 0; i < observers.size(); i++) {
		ManagedReference<MissionObserver*> observer = observers.get(i);

		AiAgent* observed = targetDest;
		if (i == 0)
			observed = target;

		if (observed != NULL) {
			Locker locker(observed);

			observed->dropObserver(ObserverEventType::CONVERSE, observer);
			observer->destroyObjectFromDatabase();
			locker.release();
		}
	}

	observers.removeAll();
}

void DeliverMissionObjectiveImplementation::complete() {
	CreatureObject* player = (CreatureObject*) getPlayerOwner();

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

int DeliverMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::CONVERSE) {
		CreatureObject* player = (CreatureObject*)arg1;
		if (!player->isPlayerCreature())
			return 0;

		AiAgent* converser = (AiAgent*)observable;
		SceneObject* targetNpc = target;
		if (objectiveStatus == 1)
			targetNpc = targetDest;

		if (targetNpc != converser)
			converser->sendDefaultConversationTo(player);
		else {
			CreatureObject* playerCreature = (CreatureObject*) player;

			player->sendMessage(new StartNpcConversation(playerCreature, converser->getObjectID(), ""));
			StringBuffer response, itemEntry;
			response << "m" << mission->getMissionNumber();
			itemEntry = response;

		   	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		   	StringId itemName;

			switch (objectiveStatus) {
			case 0:
				itemEntry << "l";
				response << "p";
				item = NULL;
			   	// just create a datadisk for now... not many missions that use something else and can add in a table lookup later
			   	item = (TangibleObject*) player->getZoneServer()->createObject(String("object/tangible/mission/mission_datadisk.iff").hashCode(), 2);
			   	if (item == NULL)
			   			return 0;

			   	itemName.setStringId("mission/mission_deliver_neutral_easy", itemEntry.toString());
			   	item->setObjectName(itemName);
			   	item->sendTo(player, true);

				// give player the item to deliver
			   	inventory->addObject(item, -1, true);

			   	updateMissionTarget(player);

				objectiveStatus = 1;
				break;
			case 1:
				response << "r";
				// check for item, then remove item
				if (item == NULL || !inventory->hasObjectInContainer(item->getObjectID()))
					return 0;

				inventory->removeObject(item, true);

				complete();
				break;
			default:
				break;
			}

			// TODO: make this less static, there can be more than one difficulty (start this back in MissionManager)
			StringIdChatParameter params("missing/mission_deliver_neutral_easy", response.toString());
			player->sendMessage(new NpcConversationMessage(playerCreature, params));
			player->sendMessage(new StopNpcConversation(player, converser->getObjectID()));
		}
	}

	return 1;
}

bool DeliverMissionObjectiveImplementation::updateMissionTarget(CreatureObject* player) {
	// now update the waypoint to the new target
	WaypointObject* waypoint = mission->getWaypointToMission();
	if (waypoint == NULL)
		waypoint = mission->createWaypoint();
	waypoint->setPlanetCRC(mission->getEndPlanetCRC());
	waypoint->setPosition(targetDest->getPositionX(), 0, targetDest->getPositionY());
	waypoint->setActive(true);
	mission->updateMissionLocation();

	return true;
}
