/*
 * MissionManagerImplementation.cpp
 *
 *  Created on: 21/06/2010
 *      Author: victor
 */

#include "MissionManager.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/SurveyMissionObjective.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/Zone.h"

void MissionManagerImplementation::handleMissionListRequest(MissionTerminal* missionTerminal, PlayerCreature* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");

	while (missionBag->getContainerObjectsSize() < 6) {
		SceneObject* mission = server->createObject(0x18e19914, 1); // empty mission
		missionBag->addObject(mission, -1, false);
		mission->sendTo(player, true);
		missionBag->updateToDatabaseWithoutChildren();
	}

	if (missionTerminal->isGeneralTerminal()) {
		populateGeneralMissionList(missionTerminal, player, counter);
	} else if (missionTerminal->isArtisanTerminal()) {
		populateArtisanMissionList(missionTerminal, player, counter);
	}
}

void MissionManagerImplementation::handleMissionAccept(MissionTerminal* missionTerminal, MissionObject* mission, PlayerCreature* player) {
	SceneObject* missionBag = mission->getParent();

	if (missionBag == NULL)
		return;

	SceneObject* bagParent = missionBag->getParent();

	if (bagParent != player)
		return;

	SceneObject* playerMissionBag = player->getSlottedObject("mission_bag");

	if (playerMissionBag != missionBag)
		return;

	SceneObject* datapad = player->getSlottedObject("datapad");

	int missionCount = 0;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		SceneObject* obj = datapad->getContainerObject(i);

		if (obj->isMissionObject())
			++missionCount;
	}

	if (missionCount >= 2) {
		ParameterizedStringId stringId("mission/mission_generic", "too_many_missions");
		player->sendSystemMessage(stringId);
		return;
	}

	if (mission->isSurveyMission()) {
		if (hasSurveyMission(player, mission->getTargetName())) {
			ParameterizedStringId stringId("mission/mission_generic", "npc_job_request_already_have");
			player->sendSystemMessage(stringId);

			return;
		}
	}

	missionBag->removeObject(mission);

	datapad->addObject(mission, -1, true);

	createMissionObjectives(mission, missionTerminal, player);

	player->updateToDatabaseAllObjects(false);
}

bool MissionManagerImplementation::hasSurveyMission(PlayerCreature* player, const String& spawn) {
	SceneObject* datapad = player->getSlottedObject("datapad");

	int missionCount = 0;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		SceneObject* obj = datapad->getContainerObject(i);

		if (obj->isMissionObject()) {
			MissionObject* mission = (MissionObject*) obj;

			if (mission->getTargetName() == spawn)
				return true;
		}
	}

	return false;
}

void MissionManagerImplementation::createSurveyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	ManagedReference<SurveyMissionObjective*> objective = new  SurveyMissionObjective(mission);
	objective->setEfficiency(mission->getDifficultyLevel());

	String spawnName = mission->getTargetName();
	ResourceManager* manager = server->getResourceManager();
	ManagedReference<ResourceSpawn*> spawn = manager->getResourceSpawn(spawnName);

	if (spawn == NULL) {
		error("spawn not found for " + spawnName);
		return;
	}

	objective->setSpawn(spawn);
	objective->setMissionGiver(missionTerminal);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	uint32 missionType = mission->getTypeCRC();

	switch (missionType) {
	case 0x19C9FAC1: // survey
		createSurveyMissionObjectives(mission, missionTerminal, player);
		break;
	default:
		break;
	}
}

void MissionManagerImplementation::removeMission(MissionObject* mission, PlayerCreature* player) {
	ManagedReference<MissionObject*> ref = mission;

	SceneObject* missionParent = mission->getParent();
	SceneObject* datapad = player->getSlottedObject("datapad");

	if (missionParent != datapad)
		return;

	datapad->removeObject(mission, true);
	mission->sendDestroyTo(player);

	mission->destroyObjectFromDatabase(true);
	player->updateToDatabaseAllObjects(false);
}

void MissionManagerImplementation::handleMissionAbort(MissionObject* mission, PlayerCreature* player) {
	mission->abort();

	removeMission(mission, player);
}

void MissionManagerImplementation::populateGeneralMissionList(MissionTerminal* missionTerminal, PlayerCreature* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");

	for (int i = 0; i < missionBag->getContainerObjectsSize(); ++i) {
		MissionObject* mission = (MissionObject*) missionBag->getContainerObject(i);
		mission->setTypeCRC(0x74EF9BE3, true);
		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::populateArtisanMissionList(MissionTerminal* missionTerminal, PlayerCreature* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");

	for (int i = 0; i < missionBag->getContainerObjectsSize(); ++i) {
		MissionObject* mission = (MissionObject*) missionBag->getContainerObject(i);
		randomizeSurveyMission(player, mission);
		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::randomizeSurveyMission(PlayerCreature* player, MissionObject* mission) {
	int maxLevel = 50;
	int minLevel = 10;

	if (player->hasSkillBox("outdoors_scount_harvest_04")) {
		minLevel = 10, maxLevel = 50;
	} else if (player->hasSkillBox("outdoors_scount_harvest_03")) {
		minLevel = 10, maxLevel = 40;
	} else if (player->hasSkillBox("outdoors_scount_harvest_02")) {
		minLevel = 10, maxLevel = 30;
	} else if (player->hasSkillBox("outdoors_scount_harvest_01")) {
		minLevel = 40, maxLevel = 50;
	} else {
		minLevel = 40, maxLevel = 50;
	}

	int randLevel = minLevel + System::random(maxLevel - minLevel);

	if (randLevel == 0)
		randLevel = 1;

	if (randLevel > maxLevel)
		randLevel = maxLevel;

	ResourceManager* manager = server->getResourceManager();

	int zoneID = player->getZone()->getZoneID();

	Vector<ManagedReference<ResourceSpawn*> > resources;

	int toolType = SurveyTool::MINERAL;

	if (System::random(1) == 0)
		toolType = SurveyTool::CHEMICAL;

	manager->getResourceListByType(resources, toolType, zoneID);

	ManagedReference<ResourceSpawn*> spawn = resources.get(System::random(resources.size() - 1));
	uint32 containerCRC = spawn->getContainerCRC();
	SharedObjectTemplate* templateObject = TemplateManager::instance()->getTemplate(containerCRC);

	if (templateObject != NULL) {
		containerCRC = templateObject->getClientObjectCRC();
	}

	int texts = System::random(50);

	if (texts == 0)
		texts = 1;

	//mission->setMissionTarget(spawn);
	//mission->setStartPosition(0, 0, player->getPlanetCRC());
	mission->setMissionTargetName(spawn->getName());
	mission->setTargetTemplateCRC(containerCRC);
	mission->setRewardCredits(500 + System::random(500));
	mission->setMissionDifficulty(randLevel);
	mission->setMissionTitle("mission/mission_npc_survey_neutral_easy", "m" + String::valueOf(texts) + "t");
	mission->setMissionDescription("mission/mission_npc_survey_neutral_easy", "m" + String::valueOf(texts) + "o");
	mission->setTypeCRC(0x19C9FAC1);
}
