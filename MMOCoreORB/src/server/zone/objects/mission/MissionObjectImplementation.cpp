/*
 * MissionObjectImplementation.cpp
 *
 *  Created on: Sep 3, 2009
 *      Author: theanswer
 */

#include "server/zone/objects/creature/CreatureObject.h"

#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/MissionObjective.h"
#include "server/zone/packets/mission/MissionObjectMessage6.h"
#include "server/zone/packets/mission/MissionObjectMessage3.h"
#include "server/zone/packets/mission/MissionObjectDeltaMessage3.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/group/GroupObject.h"

void MissionObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("MissionObject");

	if(waypointToMission == nullptr)
		waypointToMission = createWaypoint();
}

void MissionObjectImplementation::sendBaselinesTo(SceneObject* player) {
	BaseMessage* tano3 = new MissionObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(tano3);

	BaseMessage* tano6 = new MissionObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(tano6);
}

void MissionObjectImplementation::setRefreshCounter(int ctr, bool notifyClient) {
	refreshCounter = ctr;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateRefreshCount(ctr);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setTypeCRC(uint32 crc, bool notifyClient) {
	/*if (typeCRC == crc)
		return;*/

	typeCRC = crc;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateTypeCRC(crc);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setMissionDescription(const String& file, const String& id, bool notifyClient) {
	missionDescription.setStringId(file, id);

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateDescriptionStf(&missionDescription);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setMissionTitle(const String& file, const String& id, bool notifyClient) {
	missionTitle.setStringId(file, id);

	Locker clocker(waypointToMission, _this.getReferenceUnsafeStaticCast());

	waypointToMission->setCustomObjectName(missionTitle.getFullPath(), false);

	clocker.release();

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateTitleStf(&missionTitle);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setMissionTargetName(const String& target, bool notifyClient) {
	targetName = target;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateTargetName(target);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setMissionDifficulty(int diffLevel, bool notifyClient) {
	setMissionDifficulty(diffLevel, diffLevel, 2, notifyClient);
}

void MissionObjectImplementation::setMissionDifficulty(int diffLevel, int display, int diff, bool notifyClient) {
	difficultyLevel = diffLevel;
	difficultyDisplay = display;
	difficulty = diff;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateDifficultyLevel(difficultyDisplay);
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

	ManagedReference<CreatureObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (player != nullptr) {
		if (player->isGrouped()) {
			Reference<GroupObject*> group = player->getGroup();

			rewardCreditsDivisor = group->getNumberOfPlayerMembers();
		} else {
			rewardCreditsDivisor = 1;
		}

		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateRewardCredits(creds);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("description", missionDescription.getFullPath());
}

SharedObjectTemplate* MissionObjectImplementation::getTargetTemplate() {
	return targetTemplate;
}

void MissionObjectImplementation::setTargetTemplate(SharedObjectTemplate* templateObject, bool notifyClient) {
	if (targetTemplate == templateObject)
		return;

	targetTemplate = templateObject;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateTemplateCRC(targetTemplate->getClientObjectCRC());
		delta->close();

		player->sendMessage(delta);
	}
}

WaypointObject* MissionObjectImplementation::createWaypoint() {
	waypointToMission = ( getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>();

	Locker locker(waypointToMission);

	//obj->setPlanetCRC(planet.hashCode());
	//obj->setPosition(positionX, 0, positionY);
	waypointToMission->setActive(false);
	waypointToMission->setColor(3);

	return waypointToMission;
}

void MissionObjectImplementation::updateMissionLocation() {
	if (getMissionObjective() == nullptr) {
		return;
	}

	ManagedReference<CreatureObject*> playerCreature = getMissionObjective()->getPlayerOwner();
	
	ManagedReference<WaypointObject* > waypointToMission = this->waypointToMission;

	if (playerCreature != nullptr && waypointToMission != nullptr) {
		MissionObjectDeltaMessage3* dmiso3 = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		dmiso3->updateWaypoint(waypointToMission);
		dmiso3->close();

		playerCreature->sendMessage(dmiso3);

		if (playerCreature->isGrouped() && playerCreature->getGroup() != nullptr) {
			Reference<GroupObject*> group = playerCreature->getGroup();

			Core::getTaskManager()->executeTask([group, playerCreature] () {
				Locker locker(group);

				group->scheduleUpdateNearestMissionForGroup(playerCreature->getPlanetCRC());
			}, "updateMissionLocationLambda");
		}
	}
}

void MissionObjectImplementation::updateToDatabaseAllObjects(bool startTask) {
	IntangibleObjectImplementation::updateToDatabaseAllObjects(startTask);

	if (missionObjective != nullptr) {
		missionObjective->updateToDatabase();
	}
}

void MissionObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	if (destroyContainedObjects) {
		if (waypointToMission != nullptr) {
			Locker clocker(waypointToMission, _this.getReferenceUnsafeStaticCast());
			waypointToMission->destroyObjectFromDatabase(true);
		}

		if (missionObjective != nullptr) {
			Locker clocker(missionObjective, _this.getReferenceUnsafeStaticCast());
			missionObjective->destroyObjectFromDatabase();
		}
	}

}

void MissionObjectImplementation::setStartPosition(float posX, float posY, const String& planet, bool notifyClient) {
	startPositionX = posX;
	startPositionY = posY;
	startPlanet = planet;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateStartPosition(posX, 0.f, posY, planet.hashCode());
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setStartPosition(float posX, float posZ, float posY, const String& planet, bool notifyClient) {
	startPositionX = posX;
	startPositionZ = posZ;
	startPositionY = posY;
	startPlanet = planet;

	if (!notifyClient) {
		return;
	}

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateStartPosition(posX, posZ, posY, planet.hashCode());
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setStartPosition(float posX, float posY, bool notifyClient) {
	setStartPosition(posX, posY, startPlanet, notifyClient);
}

uint32 MissionObjectImplementation::getStartPlanetCRC() {
	return startPlanet.hashCode();
}

void MissionObjectImplementation::setEndPosition(float posX, float posY, const String& planet, bool notifyClient) {
	endPositionX = posX;
	endPositionY = posY;
	endPlanet = planet;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateDestination(posX, 0.f, posY, endPlanet.hashCode());
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setEndPosition(float posX, float posZ, float posY, const String& planet, bool notifyClient) {
	endPositionX = posX;
	endPositionZ = posZ;
	endPositionY = posY;
	endPlanet = planet;

	if (!notifyClient) {
		return;
	}

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateDestination(posX, posZ, posY, endPlanet.hashCode());
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setCreatorName(const String& name, bool notifyClient) {
	creatorName = name;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> player = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (player != nullptr) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
		delta->updateCreator();
		delta->close();

		player->sendMessage(delta);
	}
}

String MissionObjectImplementation::getTypeAsString() const {
	// clang-format off
	switch (typeCRC) {
		case MissionTypes::BOUNTY:          return "bounty";
		case MissionTypes::CRAFTING:        return "crafting";
		case MissionTypes::DANCER:          return "dancer";
		case MissionTypes::DELIVER:         return "deliver";
		case MissionTypes::DESTROY:         return "destroy";
		case MissionTypes::ESCORT2ME:       return "escort2me";
		case MissionTypes::ESCORT:          return "escort";
		case MissionTypes::ESCORTTOCREATOR: return "escorttocreator";
		case MissionTypes::HUNTING:         return "hunting";
		case MissionTypes::MUSICIAN:        return "musician";
		case MissionTypes::RECON:           return "recon";
		case MissionTypes::SURVEY:          return "survey";
	}
	// clang-format on

	StringBuffer asString;
	asString << "MissionTypeCRC(" << hex << typeCRC << ")";
	return asString.toString();
}

uint32 MissionObjectImplementation::getQuestCRC() const {
	uint32 questCRC = 0;

	if (questName.isEmpty()) {
		return questCRC;
	}

	String questString = "spacequest/" + questType + "/" + questName;

	questCRC = questString.hashCode();

	return questCRC;
}
