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
#include "server/zone/objects/mission/DestroyMissionObjective.h"
#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "server/zone/objects/mission/EntertainerMissionObjective.h"
#include "server/zone/objects/mission/HuntingMissionObjective.h"
#include "server/zone/objects/mission/ReconMissionObjective.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/planet/MissionTargetMap.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/templates/tangible/LairObjectTemplate.h"
#include "server/zone/managers/planet/HuntingTargetEntry.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/Zone.h"
#include "server/db/ServerDatabase.h"

void MissionManagerImplementation::loadLairObjectsToSpawn() {
	info("loading lair objects to spawn...", true);

	String query = "SELECT * FROM mission_manager_spawn_lairs";

	ResultSet* res = ServerDatabase::instance()->executeQuery(query);

	while (res->next()) {
		String templateObject = res->getString(1);
		String planets = res->getString(2);

		StringTokenizer tokenizer(planets);
		tokenizer.setDelimeter((","));

		while (tokenizer.hasMoreTokens()) {
			int planetID = tokenizer.getIntToken();

			lairObjectTemplatesToSpawn.addTemplate(planetID, templateObject.hashCode());
		}
	}

	delete res;

	/*StringBuffer msg;
	msg << "loaded " << lairObjectTemplatesToSpawn.size() << " lairs to spawn";
	info(msg.toString(), true);*/
}

void MissionManagerImplementation::handleMissionListRequest(MissionTerminal* missionTerminal, PlayerCreature* player, int counter) {
	// newbie and statue terminals don't exist, but their templates do
	if (missionTerminal->isStatueTerminal() || missionTerminal->isNewbieTerminal()) {
		player->sendSystemMessage("skill_teacher", "skill_terminal_disabled");
		return;
	}

	SceneObject* missionBag = player->getSlottedObject("mission_bag");

	while (missionBag->getContainerObjectsSize() < 6) {
		SceneObject* mission = server->createObject(0x18e19914, 1); // empty mission
		missionBag->addObject(mission, -1, false);
		mission->sendTo(player, true);
		//missionBag->updateToDatabaseWithoutChildren();
	}

	populateMissionList(missionTerminal, player, counter);
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

void MissionManagerImplementation::createDestroyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	ManagedReference<DestroyMissionObjective*> objective = new DestroyMissionObjective(mission);
	objective->setLairTemplateToSpawn(mission->getTargetTemplate());

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createDeliverMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	ManagedReference<DeliverMissionObjective*> objective = new DeliverMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createSurveyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	ManagedReference<SurveyMissionObjective*> objective = new SurveyMissionObjective(mission);
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

void MissionManagerImplementation::createEntertainerMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	ManagedReference<EntertainerMissionObjective*> objective = new EntertainerMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createHuntingMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	ManagedReference<HuntingMissionObjective*> objective = new HuntingMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createReconMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	ManagedReference<ReconMissionObjective*> objective = new ReconMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, PlayerCreature* player) {
	uint32 missionType = mission->getTypeCRC();

	switch (missionType) {
	case MissionObject::SURVEY: // survey
		createSurveyMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionObject::DESTROY:
		createDestroyMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionObject::DELIVER:
		createDeliverMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionObject::HUNTING:
		createHuntingMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionObject::RECON:
		createReconMissionObjectives(mission, missionTerminal, player);
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

void MissionManagerImplementation::populateMissionList(MissionTerminal* missionTerminal, PlayerCreature* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");

	for (int i = 0; i < missionBag->getContainerObjectsSize(); ++i) {
		MissionObject* mission = (MissionObject*) missionBag->getContainerObject(i);
		//randomizeDestroyMission(player, mission);

		// TODO: make mission distribution function more like live
		if (missionTerminal->isGeneralTerminal()) {
			if (System::random(1) == 0)
				randomizeDestroyMission(player, mission);
			else
				randomizeDeliverMission(player, mission);
		} else if (missionTerminal->isArtisanTerminal()) {
			if (System::random(1) == 0)
				randomizeSurveyMission(player, mission);
			else
				randomizeCraftingMission(player, mission);
		} else if (missionTerminal->isEntertainerTerminal()) {
			// TODO: implement entertainer missions after entertainer is implemented
			//randomizeEntertainerMission(player, mission);
			mission->setTypeCRC(0);
		} else if (missionTerminal->isImperialTerminal()) {
			if (System::random(1) == 0)
				randomizeImperialDestroyMission(player, mission);
			else
				randomizeImperialDeliverMission(player, mission);
		} else if (missionTerminal->isRebelTerminal()) {
			if (System::random(1) == 0)
				randomizeRebelDestroyMission(player, mission);
			else
				randomizeRebelDeliverMission(player, mission);
		} else if (missionTerminal->isScoutTerminal()) {
			if (System::random(1) == 0)
				randomizeReconMission(player, mission);
			else
				randomizeHuntingMission(player, mission);
		} else if (missionTerminal->isBountyTerminal())
			randomizeBountyMission(player, mission);

		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::randomizeDestroyMission(PlayerCreature* player, MissionObject* mission) {

	//String mission = "mission/mission_destroy_neutral_easy_creature_naboo";
	int zoneID = player->getZone()->getZoneID();

	uint32 templateCRC = lairObjectTemplatesToSpawn.getRandomTemplate(zoneID);

	if (templateCRC == 0) {
		mission->setTypeCRC(0);
		return;
	}

	SharedObjectTemplate* templateObject = TemplateManager::instance()->getTemplate(templateCRC);

	if (templateObject == NULL || !templateObject->isLairObjectTemplate()) {
		mission->setTypeCRC(0);
		error("incorrect template object in randomizeDestroyMission " + String::valueOf(templateCRC));
		return;
	}

	LairObjectTemplate* lairObjectTemplate = (LairObjectTemplate*) templateObject;

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(34) + 1;

	mission->setMissionNumber(randTexts);

	Vector3 startPos = player->getCoordinate(System::random(1000) + 1000, (float)System::random(360));
	//mission->setMissionTarget(lairObjectTemplate->getObjectName());
	mission->setStartPlanetCRC(player->getZone()->getPlanetName().hashCode());
	mission->setStartPosition(startPos.getX(), startPos.getY(), player->getPlanetCRC());
	mission->setCreatorName(nm->makeCreatureName());

	mission->setMissionTargetName(lairObjectTemplate->getObjectName());
	mission->setTargetTemplate(lairObjectTemplate);

	// TODO: this all needs to change to be less static and use player levels
	mission->setRewardCredits(500 + System::random(500));
	mission->setMissionDifficulty(5);
	mission->setMissionTitle("mission/mission_destroy_neutral_easy_creature", "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_destroy_neutral_easy_creature", "m" + String::valueOf(randTexts) + "d");

	mission->setTypeCRC(MissionObject::DESTROY);
}

void MissionManagerImplementation::randomizeSurveyMission(PlayerCreature* player, MissionObject* mission) {
	int maxLevel = 50;
	int minLevel = 10;

	if (player->hasSkillBox("crafting_artisan_survey_04")) {
		minLevel = 10, maxLevel = 50;
	} else if (player->hasSkillBox("crafting_artisan_survey_03")) {
		minLevel = 10, maxLevel = 40;
	} else if (player->hasSkillBox("crafting_artisan_survey_02")) {
		minLevel = 10, maxLevel = 30;
	} else if (player->hasSkillBox("crafting_artisan_survey_01")) {
		minLevel = 10, maxLevel = 20;
	} else {
		minLevel = 10, maxLevel = 10;
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

	NameManager* nm = processor->getNameManager();

	int texts = System::random(50);

	if (texts == 0)
		texts = 1;

	// TODO: make less static
	//mission->setMissionTarget(spawn);
	//mission->setStartPosition(0, 0, player->getPlanetCRC());
	mission->setMissionTargetName(spawn->getName());
	mission->setTargetTemplate(templateObject);
	mission->setRewardCredits(500 + System::random(500));
	mission->setMissionDifficulty(randLevel);
	mission->setStartPlanetCRC(player->getZone()->getPlanetName().hashCode());
	mission->setStartPosition(player->getPositionX(), player->getPositionY(), player->getPlanetCRC());
	mission->setMissionTitle("mission/mission_npc_survey_neutral_easy", "m" + String::valueOf(texts) + "t");
	mission->setMissionDescription("mission/mission_npc_survey_neutral_easy", "m" + String::valueOf(texts) + "o");
	mission->setCreatorName(nm->makeCreatureName());

	mission->setTypeCRC(MissionObject::SURVEY);
}

void MissionManagerImplementation::randomizeBountyMission(PlayerCreature* player, MissionObject* mission) {
	// TODO: add bounty targets (don't just overload destroy)
	randomizeDestroyMission(player, mission);

	mission->setTypeCRC(MissionObject::BOUNTY);
}

void MissionManagerImplementation::randomizeDeliverMission(PlayerCreature* player, MissionObject* mission) {
	PlanetManager* pmng = player->getZone()->getPlanetManager();
	MissionTargetMap* missionNpcs = pmng->getMissionNpcs();
	// need at least 2 NPCs to have a delivery mission
	if (missionNpcs->size() <= 1) {
		mission->setTypeCRC(0);
		return;
	}

	SceneObject* target = missionNpcs->getRandomTarget(player, 1);
	SceneObject* targetDest = missionNpcs->getRandomTarget(player, 1);

	if (target == NULL || targetDest == NULL || target == targetDest) {
		mission->setTypeCRC(0);
		return;
	}

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(29) + 1;

	mission->setMissionNumber(randTexts);
	mission->setMissionTarget(target);
	mission->setMissionTargetDest(targetDest);
	mission->setCreatorName(nm->makeCreatureName());

	mission->setStartPlanetCRC(player->getZone()->getPlanetName().hashCode());
	mission->setStartPosition(target->getPositionX(), target->getPositionY(), target->getPlanetCRC());
	mission->setEndPosition(targetDest->getPositionX(), targetDest->getPositionY(), targetDest->getPlanetCRC());

	// TODO: will need to do table lookup to get the other types of deliver missions (most are datadisk)
	mission->setMissionTargetName("Datadisc");
	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(String("object/tangible/mission/mission_datadisk.iff").hashCode()));

	// TODO: this all needs to change to be less static and use distance
	mission->setRewardCredits(100 + System::random(100));
	mission->setMissionDifficulty(5);
	mission->setMissionTitle("mission/mission_deliver_neutral_easy", "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_deliver_neutral_easy", "m" + String::valueOf(randTexts) + "d");

	mission->setTypeCRC(MissionObject::DELIVER);
}

void MissionManagerImplementation::randomizeCraftingMission(PlayerCreature* player, MissionObject* mission) {
	// TODO: add crafting logic (don't just overload destroy)
	/*
	 * get random low level trash schematic
	 * give player components and schematic
	 * get random NPC like deliver mission
	 * add waypoint
	 * onConversation() --
	 *   check for completed item, success if there
	 */
	randomizeDestroyMission(player, mission);

	mission->setTypeCRC(MissionObject::CRAFTING);
}

void MissionManagerImplementation::randomizeEntertainerMission(PlayerCreature* player, MissionObject* mission) {
	PlanetManager* pmng = player->getZone()->getPlanetManager();
	MissionTargetMap* performanceLocations = pmng->getPerformanceLocations();
	if (performanceLocations->size() <= 0) {
		mission->setTypeCRC(0);
		return;
	}

	// TODO: filter by distance (get closer locations for lower difficulties)
	SceneObject* target = performanceLocations->getRandomTarget(player, 1);
	if (target == NULL || !target->isStructureObject()) {
		mission->setTypeCRC(0);
		return;
	}

	NameManager* nm = processor->getNameManager();

	bool dancing = false;
	if (System::random(1) == 0)
		dancing = true;

	String missionType = "musician";
	if (dancing)
		missionType = "dancer";

	int randTexts = System::random(49) + 1;

	mission->setMissionNumber(randTexts);
	mission->setMissionTarget(target);
	mission->setCreatorName(nm->makeCreatureName());

	mission->setStartPlanetCRC(player->getZone()->getPlanetName().hashCode());
	mission->setStartPosition(target->getPositionX(), target->getPositionY(), target->getPlanetCRC());

	// TODO: this all needs to change to be less static and use distance
	mission->setMissionTargetName("Theater");
	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(String("object/building/general/mun_all_guild_theater_s01.iff").hashCode()));

	mission->setRewardCredits(100 + System::random(100));
	mission->setMissionDifficulty(5);
	mission->setMissionTitle("mission/mission_npc_" + missionType + "_neutral_easy", "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_npc_" + missionType + "_neutral_easy", "m" + String::valueOf(randTexts) + "o");

	if (!dancing)
		mission->setTypeCRC(MissionObject::MUSICIAN);
	else
		mission->setTypeCRC(MissionObject::DANCER);
}

void MissionManagerImplementation::randomizeHuntingMission(PlayerCreature* player, MissionObject* mission) {
	PlanetManager* pmng = player->getZone()->getPlanetManager();

	// TODO: randomize difficulty (weighted by what?) once more missions are in the db
	HuntingTargetEntry* entry = pmng->getHuntingTargetTemplate(1);
	if (entry == NULL) {
		mission->setTypeCRC(0);
		return;
	}

	mission->setTemplateStrings(entry->getPrimary(), entry->getSecondary());
	String targetTemp = entry->getPrimary();

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(7) + 1;

	mission->setMissionNumber(randTexts);
	mission->setCreatorName(nm->makeCreatureName());

	mission->setStartPlanetCRC(player->getZone()->getPlanetName().hashCode());
	mission->setStartPosition(player->getPositionX(), player->getPositionY(), player->getPlanetCRC());

	// TODO: this all needs to change to be less static and use distance
	mission->setMissionTargetName(TemplateManager::instance()->getTemplate(targetTemp.hashCode())->getObjectName());
	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(targetTemp.hashCode()));

	mission->setRewardCredits(100 + System::random(100));
	mission->setMissionDifficulty(1);
	mission->setMissionTitle("mission/mission_npc_hunting_neutral_easy", "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_npc_hunting_neutral_easy", "m" + String::valueOf(randTexts) + "o");

	mission->setTypeCRC(MissionObject::HUNTING);
}

void MissionManagerImplementation::randomizeReconMission(PlayerCreature* player, MissionObject* mission) {
	PlanetManager* pmng = player->getZone()->getPlanetManager();

	MissionTargetMap* reconlocs = pmng->getReconLocs();
	if (reconlocs->size() <= 0) {
		mission->setTypeCRC(0);
		return;
	}

	SceneObject* target = reconlocs->getRandomTarget(player, 3);
	if (target == NULL) {
		mission->setTypeCRC(0);
		return;
	}

	mission->setMissionTarget(target);

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(24) + 1;

	mission->setMissionNumber(randTexts);
	mission->setCreatorName(nm->makeCreatureName());

	mission->setStartPlanetCRC(target->getZone()->getPlanetName().hashCode());
	mission->setStartPosition(target->getPositionX(), target->getPositionY(), target->getPlanetCRC());

	mission->setMissionTargetName(TemplateManager::instance()->getTemplate(target->getServerObjectCRC())->getObjectName());
	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(target->getServerObjectCRC()));

	mission->setRewardCredits(100 + System::random(100));
	mission->setMissionDifficulty(1);
	mission->setMissionTitle("mission/mission_npc_recon_neutral_easy", "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_npc_recon_neutral_easy", "m" + String::valueOf(randTexts) + "o");

	mission->setTypeCRC(MissionObject::RECON);
}

void MissionManagerImplementation::randomizeImperialDestroyMission(PlayerCreature* player, MissionObject* mission) {
	// TODO: add faction-specific targets
	randomizeDestroyMission(player, mission);
}

void MissionManagerImplementation::randomizeImperialDeliverMission(PlayerCreature* player, MissionObject* mission) {
	// TODO: add faction-specific targets
	randomizeDeliverMission(player, mission);
}

void MissionManagerImplementation::randomizeRebelDestroyMission(PlayerCreature* player, MissionObject* mission) {
	// TODO: add faction-specific targets
	randomizeDestroyMission(player, mission);
}

void MissionManagerImplementation::randomizeRebelDeliverMission(PlayerCreature* player, MissionObject* mission) {
	// TODO: add faction-specific targets
	randomizeDeliverMission(player, mission);
}
