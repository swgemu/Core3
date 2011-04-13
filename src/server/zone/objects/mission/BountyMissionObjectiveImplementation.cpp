/*
 * BountyMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "BountyMissionObjective.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/creature/informant/InformantCreature.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "MissionObject.h"
#include "MissionObserver.h"

void BountyMissionObjectiveImplementation::setNpcTemplateToSpawn(SharedObjectTemplate* sp) {
	npcTemplateToSpawn = sp;
}

void BountyMissionObjectiveImplementation::activate() {
	if (observers.size() != 0)
		return;

	// register observer with self
	ManagedReference<MissionObserver*> observer = new MissionObserver(_this);
	ObjectManager::instance()->persistObject(observer, 1, "missionobservers");

	PlayerCreature* player = getPlayerOwner();
	player->registerObserver(ObserverEventType::CONVERSE, observer);

	observers.put(observer);
}

void BountyMissionObjectiveImplementation::abort() {
	// remove observers
	if (observers.size() != 0) {
		ManagedReference<MissionObserver*> observer = observers.get(0);

		PlayerCreature* player = getPlayerOwner();

		if (npcTarget != NULL) {
			ManagedReference<SceneObject*> npcHolder = npcTarget.get();
			Locker locker(npcTarget);

			npcTarget->dropObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
			npcTarget->destroyObjectFromDatabase();
			npcTarget->removeFromZone();

			npcTarget = NULL;

			observers.drop(observer);
		}

		if (player != NULL && observers.size() != 0) {
			observer = observers.get(0);
			Locker locker(player);

			player->dropObserver(ObserverEventType::CONVERSE, observer);
			observer->destroyObjectFromDatabase();

			observers.drop(observer);
		}
	}
}

void BountyMissionObjectiveImplementation::complete() {
	PlayerCreature* player = (PlayerCreature*) getPlayerOwner();

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

void BountyMissionObjectiveImplementation::spawnTarget(const String& terrainName) {
	if (npcTarget != NULL && npcTarget->isInQuadTree())
		return;

	ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
	Zone* zone = zoneServer->getZone(terrainName);
	CreatureManager* cmng = zone->getCreatureManager();

	ManagedReference<CreatureObject*> npcCreature = NULL;

	if (npcTarget == NULL) {
		npcTarget = (AiAgent*) zoneServer->createObject(npcTemplateToSpawn->getServerObjectCRC(), 0);
	}

	if (npcTarget == NULL || (npcTarget != NULL && !npcTarget->isInQuadTree())) {
		int x = System::random(15000) - 7500;
		int y = System::random(15000) - 7500;
		npcTarget->initializePosition(x, zone->getHeight(x, y), y);
		npcTarget->insertToZone(zone);

		ManagedReference<MissionObserver*> observer = new MissionObserver(_this);
		ObjectManager::instance()->persistObject(observer, 1, "missionobservers");

		npcTarget->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);

		observers.put(observer);
	}
}

int BountyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::CONVERSE) {
		PlayerCreature* player = (PlayerCreature*)observable;
		InformantCreature* informant = (InformantCreature*)arg1;
		int level = informant->getLevel();

		player->sendMessage(new StartNpcConversation(player, informant->getObjectID(), ""));

		if (level < mission->getDifficultyLevel() - 1) {
			StringIdChatParameter params("mission/mission_bounty_informant", "informant_find_harder");
			player->sendMessage(new NpcConversationMessage(player, params));
			player->sendMessage(new StopNpcConversation(player, informant->getObjectID()));
			return 0;
		}

		if (level > mission->getDifficultyLevel() - 1) {
			StringIdChatParameter params("mission/mission_bounty_informant", "informant_find_easier");
			player->sendMessage(new NpcConversationMessage(player, params));
			player->sendMessage(new StopNpcConversation(player, informant->getObjectID()));
			return 0;
		}

		// switch mission level to determine how the waypoint is given
		// level 0: give straight waypoint (target on planet)
		if (level == 0) {
			spawnTarget(player->getZone()->getTerrainName());

			WaypointObject* waypoint = mission->getWaypointToMission();

			if (waypoint == NULL)
				waypoint = mission->createWaypoint();

			mission->setEndPosition(npcTarget->getPositionX(), npcTarget->getPositionY(), npcTarget->getPlanetCRC(), true);
			waypoint->setPlanetCRC(npcTarget->getPlanetCRC());
			waypoint->setPosition(npcTarget->getPositionX(), 0, npcTarget->getPositionY());
			waypoint->setActive(true);

			mission->updateMissionLocation();

			player->sendSystemMessage("mission/mission_bounty_informant", "target_location_received");

			StringIdChatParameter params("mission/mission_bounty_informant", "target_easy_" + String::valueOf(System::random(4) + 1));
			player->sendMessage(new NpcConversationMessage(player, params));
			player->sendMessage(new StopNpcConversation(player, informant->getObjectID()));
		}
		// higher level, give biosignature
	} else if (eventType == ObserverEventType::OBJECTDESTRUCTION) {
		complete();
	}

	return 1;
}
