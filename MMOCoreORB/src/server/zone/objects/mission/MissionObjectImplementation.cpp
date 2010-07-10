/*
 * MissionObjectImplementation.cpp
 *
 *  Created on: Sep 3, 2009
 *      Author: theanswer
 */

#include "MissionObject.h"
#include "MissionObjective.h"
#include "server/zone/packets/mission/MissionObjectMessage6.h"
#include "server/zone/packets/mission/MissionObjectMessage3.h"
#include "server/zone/packets/mission/MissionObjectDeltaMessage3.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"

void MissionObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("MissionObject");
}

void MissionObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending miso baselines");

	BaseMessage* tano3 = new MissionObjectMessage3(_this);
	player->sendMessage(tano3);

	BaseMessage* tano6 = new MissionObjectMessage6(_this);
	player->sendMessage(tano6);
}

void MissionObjectImplementation::setRefreshCounter(int ctr, bool notifyClient) {
	refreshCounter = ctr;

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateRefreshCount(ctr);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setTypeCRC(uint32 crc, bool notifyClient) {
	if (typeCRC == crc)
		return;

	typeCRC = crc;

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateTypeCRC(crc);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setMissionDescription(const String& file, const String& id, bool notifyClient) {
	missionDescription.setStringId(file, id);

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateDescriptionStf(&missionDescription);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setMissionTitle(const String& file, const String& id, bool notifyClient) {
	missionTitle.setStringId(file, id);

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateTitleStf(&missionTitle);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setMissionTargetName(const String& target, bool notifyClient) {
	targetName = target;

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateTargetName(target);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setMissionDifficulty(int difficulty, bool notifyClient) {
	if (difficultyLevel == difficulty)
		return;

	difficultyLevel = difficulty;

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateDifficultyLevel(difficultyLevel);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setRewardCredits(int creds, bool notifyClient) {
	if (rewardCredits == creds)
		return;

	rewardCredits = creds;

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateRewardCredits(creds);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setTargetTemplateCRC(uint32 crc, bool notifyClient) {
	if (targetTemplateCRC == crc)
		return;

	targetTemplateCRC = crc;

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateTemplateCRC(targetTemplateCRC);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::createWaypoint() {
	waypointToMission = (WaypointObject*) getZoneServer()->createObject(0xc456e788, 1);
	//obj->setPlanetCRC(planet.hashCode());
	//obj->setPosition(positionX, 0, positionY);
	waypointToMission->setActive(false);
}

void MissionObjectImplementation::updateToDatabaseAllObjects(bool startTask) {
	IntangibleObjectImplementation::updateToDatabaseAllObjects(startTask);

	if (missionObjective != NULL) {
		missionObjective->updateToDatabase();
	}
}

void MissionObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	if (destroyContainedObjects) {
		if (waypointToMission != NULL)
			waypointToMission->destroyObjectFromDatabase(true);

		if (missionObjective != NULL)
			missionObjective->destroyObjectFromDatabase();
	}

}

void MissionObjectImplementation::setStartPosition(float posX, float posY, uint32 planetCRC, bool notifyClient) {
	startPositionX = posX;
	startPositionY = posY;
	startPlanetCRC = planetCRC;

	if (!notifyClient)
		return;

	SceneObject* player = getParentRecursively(SceneObject::PLAYERCREATURE);

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateStartPosition(posX, posY, planetCRC);
		delta->close();

		player->sendMessage(delta);
	}
}
