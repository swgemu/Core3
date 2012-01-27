/*
 * MissionManagerImplementation.cpp
 *
 *  Created on: 21/06/2010
 *      Author: victor
 */

#include "MissionManager.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/SurveyMissionObjective.h"
#include "server/zone/objects/mission/DestroyMissionObjective.h"
#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "server/zone/objects/mission/CraftingMissionObjective.h"
#include "server/zone/objects/mission/EntertainerMissionObjective.h"
#include "server/zone/objects/mission/HuntingMissionObjective.h"
#include "server/zone/objects/mission/ReconMissionObjective.h"
#include "server/zone/objects/mission/BountyMissionObjective.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/area/LairSpawnArea.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/planet/MissionTargetMap.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/templates/mobile/LairTemplate.h"
#include "server/zone/managers/planet/HuntingTargetEntry.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/area/MissionReconActiveArea.h"
#include "server/zone/Zone.h"
#include "server/db/ServerDatabase.h"

void MissionManagerImplementation::loadNpcObjectsToSpawn() {
	String query = "SELECT * FROM mission_manager_spawn_bounty";

	Reference<ResultSet*> res = NULL;

	try {
		res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			String templateName = res->getString(1);

			npcObjectTemplatesToSpawn.add(templateName.hashCode());
		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}

	info("loaded " + String::valueOf(npcObjectTemplatesToSpawn.size()) + " npc objects to spawn.", true);
}

void MissionManagerImplementation::loadCraftingMissionItems() {
	try {
		Lua* lua = new Lua();
		lua->init();

		lua->runFile("scripts/managers/mission_manager.lua");

		LuaObject items = lua->getGlobalObject("crafting_mission_items");

		for (int i = 1; i <= items.getTableSize(); i++) {
			craftingMissionItems.add(items.getStringAt(i));
		}

		items.pop();

		String value = lua->getGlobalString("enable_factional_crafting_missions");

		if (value.toLowerCase() == "true") {
			enableFactionalCraftingMissions = true;
		}

		value = lua->getGlobalString("enable_factional_recon_missions");

		if (value.toLowerCase() == "true") {
			enableFactionalReconMissions = true;
		}

		value = lua->getGlobalString("enable_factional_entertainer_missions");

		if (value.toLowerCase() == "true") {
			enableFactionalEntertainerMissions = true;
		}

		delete lua;
	}
	catch (Exception& e) {
		error(e.getMessage());
	}
}

void MissionManagerImplementation::handleMissionListRequest(MissionTerminal* missionTerminal, CreatureObject* player, int counter) {
	// newbie and statue terminals don't exist, but their templates do
	if (missionTerminal->isStatueTerminal() || missionTerminal->isNewbieTerminal()) {
		player->sendSystemMessage("skill_teacher", "skill_terminal_disabled");
		return;
	}

	ManagedReference<SceneObject*> missionBag = player->getSlottedObject("mission_bag");

	if (missionBag == NULL)
		return;

	int maximumNumberOfItemsInMissionBag = 12;


	if (enableFactionalCraftingMissions) {
		maximumNumberOfItemsInMissionBag += 6;
	}

	if (enableFactionalReconMissions) {
		maximumNumberOfItemsInMissionBag += 6;
	}

	if (enableFactionalEntertainerMissions) {
		maximumNumberOfItemsInMissionBag += 12; //Both musician and dancer.
	}

	while (missionBag->getContainerObjectsSize() < maximumNumberOfItemsInMissionBag) {
		SceneObject* mission = server->createObject(0x18e19914, 1); // empty mission
		missionBag->transferObject(mission, -1, false);
		mission->sendTo(player, true);
		//missionBag->updateToDatabaseWithoutChildren();
	}

	populateMissionList(missionTerminal, player, counter);
}

void MissionManagerImplementation::handleMissionAccept(MissionTerminal* missionTerminal, MissionObject* mission, CreatureObject* player) {
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
	bool hasBountyMission = false;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		SceneObject* obj = datapad->getContainerObject(i);

		if (obj->isMissionObject()) {
			++missionCount;
			MissionObject* datapadMission = cast<MissionObject*>(obj);
			if (datapadMission->getTypeCRC() == MissionObject::BOUNTY) {
				hasBountyMission = true;
			}
		}
	}

	//Limit to two missions (only one of them can be a bounty mission)
	if (missionCount >= 2 || (hasBountyMission && mission->getTypeCRC() == MissionObject::BOUNTY)) {
		StringIdChatParameter stringId("mission/mission_generic", "too_many_missions");
		player->sendSystemMessage(stringId);
		return;
	}

	datapad->transferObject(mission, -1, true);

	createMissionObjectives(mission, missionTerminal, player);

	player->updateToDatabaseAllObjects(false);
}

void MissionManagerImplementation::createDestroyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<DestroyMissionObjective*> objective = new DestroyMissionObjective(mission);
	objective->setLairTemplateToSpawn(mission->getTargetOptionalTemplate());
	objective->setDifficulty(mission->getDifficultyLevel(), mission->getDifficultyLevel());

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createDeliverMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<DeliverMissionObjective*> objective = new DeliverMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createCraftingMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	//Check if player already got an crafting mission and what item it uses.
	SceneObject* datapad = player->getSlottedObject("datapad");

	if (datapad == NULL) {
		return;
	}

	if (mission->getFaction() != MissionObject::FACTIONNEUTRAL && !enableFactionalCraftingMissions) {
		//Faction mission, but faction missions are disabled.
		return;
	}

	int datapadSize = datapad->getContainerObjectsSize();
	String missionItem = "";

	for (int i = 0; i < datapadSize; ++i) {
		if (datapad->getContainerObject(i)->isMissionObject()) {
			MissionObject* datapadMission = cast<MissionObject*>(datapad->getContainerObject(i));

			if (datapadMission != NULL && datapadMission->getTypeCRC() == MissionObject::CRAFTING && datapadMission != mission) {
				//Crafting mission found, store the item.
				missionItem = datapadMission->getTemplateString1();
			}
		}
	}

	//Pick a random item for the new mission.
	int itemNumber = System::random(craftingMissionItems.size() - 1);

	//Get next item in line if the player already got a mission with the random generated item.
	if (craftingMissionItems.get(itemNumber) == missionItem) {
		itemNumber = (itemNumber + 1) % craftingMissionItems.size();
	}

	mission->setTemplateStrings(craftingMissionItems.get(itemNumber), craftingMissionItems.get(itemNumber).replaceFirst("draft_schematic/item/", "tangible/mission/"));

	ManagedReference<CraftingMissionObjective*> objective = new CraftingMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createSurveyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<SurveyMissionObjective*> objective = new SurveyMissionObjective(mission);
	objective->setEfficiency(mission->getDifficultyLevel());

	String spawnName = mission->getTargetName();

	objective->setSpawnFamily(spawnName);
	objective->setMissionGiver(missionTerminal);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createEntertainerMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<EntertainerMissionObjective*> objective = new EntertainerMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createHuntingMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<HuntingMissionObjective*> objective = new HuntingMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createReconMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<ReconMissionObjective*> objective = new ReconMissionObjective(mission);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createBountyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	uint32 templateCRC = npcObjectTemplatesToSpawn.get(System::random(npcObjectTemplatesToSpawn.size() - 1));
	SharedObjectTemplate* templateObject = TemplateManager::instance()->getTemplate(templateCRC);

	if (templateObject == NULL) {
		removeMission(mission, player);
		error("incorrect template object in createBountyMission " + String::valueOf(templateCRC));
		return;
	}

	ManagedReference<BountyMissionObjective*> objective = new BountyMissionObjective(mission);

	objective->setNpcTemplateToSpawn(templateObject);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	uint32 missionType = mission->getTypeCRC();

	switch (missionType) {
	case MissionObject::SURVEY:
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
	case MissionObject::BOUNTY:
		createBountyMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionObject::CRAFTING:
		createCraftingMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionObject::DANCER:
	case MissionObject::MUSICIAN:
		createEntertainerMissionObjectives(mission, missionTerminal, player);
		break;
	default:
		break;
	}
}

void MissionManagerImplementation::removeMission(MissionObject* mission, CreatureObject* player) {
	ManagedReference<MissionObject*> ref = mission;

	SceneObject* missionParent = mission->getParent();
	SceneObject* datapad = player->getSlottedObject("datapad");

	if (missionParent != datapad)
		return;

	mission->destroyObjectFromWorld(true);
	mission->sendDestroyTo(player);

	mission->destroyObjectFromDatabase(true);
	player->updateToDatabaseAllObjects(false);
}

void MissionManagerImplementation::handleMissionAbort(MissionObject* mission, CreatureObject* player) {
	mission->abort();

	removeMission(mission, player);
}

void MissionManagerImplementation::populateMissionList(MissionTerminal* missionTerminal, CreatureObject* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");
	int bagSize = missionBag->getContainerObjectsSize();

	//info("bagSize = " + String::valueOf(bagSize), true);

	int numberOfCraftingMissions = 0;
	int numberOfReconMissions = 0;
	int numberOfDancerMissions = 0;
	int numberOfMusicianMissions = 0;

	int maximumNumberOfMissionTypesInOneTerminal = 2;
	if (enableFactionalCraftingMissions) {
		maximumNumberOfMissionTypesInOneTerminal++;
	}
	if (enableFactionalReconMissions) {
		maximumNumberOfMissionTypesInOneTerminal++;
	}
	if (enableFactionalEntertainerMissions) {
		maximumNumberOfMissionTypesInOneTerminal +=2;
	}

	for (int i = 0; i < bagSize; ++i) {
		MissionObject* mission = cast<MissionObject*>( missionBag->getContainerObject(i));

		//Clear mission type before calling mission generators.
		mission->setTypeCRC(0);

		if (missionTerminal->isGeneralTerminal()) {
			if (i < bagSize / maximumNumberOfMissionTypesInOneTerminal) {
				randomizeDestroyMission(player, mission);
			} else if (i < (bagSize * 2 / maximumNumberOfMissionTypesInOneTerminal)) {
				randomizeDeliverMission(player, mission);
			} else {
				mission->setTypeCRC(0);
			}
		} else if (missionTerminal->isArtisanTerminal()) {
			if (i < bagSize / maximumNumberOfMissionTypesInOneTerminal) {
				randomizeSurveyMission(player, mission);
			} else  if (i < (bagSize * 2 / maximumNumberOfMissionTypesInOneTerminal)) {
				randomizeCraftingMission(player, mission);
			} else {
				mission->setTypeCRC(0);
			}
		} else if (missionTerminal->isEntertainerTerminal()) {
			if (i < (bagSize / maximumNumberOfMissionTypesInOneTerminal)) {
				randomizeGenericEntertainerMission(player, mission, MissionObject::FACTIONNEUTRAL, MissionObject::DANCER);
			} else if (i < (bagSize * 2 / maximumNumberOfMissionTypesInOneTerminal)) {
				randomizeGenericEntertainerMission(player, mission, MissionObject::FACTIONNEUTRAL, MissionObject::MUSICIAN);
			} else {
				mission->setTypeCRC(0);
			}
		} else if (missionTerminal->isImperialTerminal()) {
			if (i < bagSize / maximumNumberOfMissionTypesInOneTerminal) {
				randomizeImperialDestroyMission(player, mission);
			} else if (i < (bagSize * 2 / maximumNumberOfMissionTypesInOneTerminal)) {
				randomizeImperialDeliverMission(player, mission);
			} else {
				if (enableFactionalCraftingMissions && numberOfCraftingMissions < 6) {
					randomizeImperialCraftingMission(player, mission);
					numberOfCraftingMissions++;
				} else if (enableFactionalReconMissions && numberOfReconMissions < 6) {
					randomizeImperialReconMission(player, mission);
					numberOfReconMissions++;
				} else if (enableFactionalEntertainerMissions && numberOfDancerMissions < 6) {
					randomizeGenericEntertainerMission(player, mission, MissionObject::FACTIONIMPERIAL, MissionObject::DANCER);
					numberOfDancerMissions++;
				} else if (enableFactionalEntertainerMissions && numberOfMusicianMissions < 6) {
					randomizeGenericEntertainerMission(player, mission, MissionObject::FACTIONIMPERIAL, MissionObject::MUSICIAN);
					numberOfMusicianMissions++;
				} else {
					mission->setTypeCRC(0, true);
				}
			}
		} else if (missionTerminal->isRebelTerminal()) {
			if (i < bagSize / maximumNumberOfMissionTypesInOneTerminal) {
				randomizeRebelDestroyMission(player, mission);
			} else if (i < (bagSize * 2 / maximumNumberOfMissionTypesInOneTerminal)) {
				randomizeRebelDeliverMission(player, mission);
			} else {
				if (enableFactionalCraftingMissions && numberOfCraftingMissions < 6) {
					randomizeRebelCraftingMission(player, mission);
					numberOfCraftingMissions++;
				} else if (enableFactionalReconMissions && numberOfReconMissions < 6) {
					randomizeRebelReconMission(player, mission);
					numberOfReconMissions++;
				} else if (enableFactionalEntertainerMissions && numberOfDancerMissions < 6) {
					randomizeGenericEntertainerMission(player, mission, MissionObject::FACTIONREBEL, MissionObject::DANCER);
					numberOfDancerMissions++;
				} else if (enableFactionalEntertainerMissions && numberOfMusicianMissions < 6) {
					randomizeGenericEntertainerMission(player, mission, MissionObject::FACTIONREBEL, MissionObject::MUSICIAN);
					numberOfMusicianMissions++;
				} else {
					mission->setTypeCRC(0, true);
				}
			}
		} else if (missionTerminal->isScoutTerminal()) {
			if (i < bagSize / maximumNumberOfMissionTypesInOneTerminal) {
				randomizeReconMission(player, mission);
			} else if (i < (bagSize * 2 / maximumNumberOfMissionTypesInOneTerminal)) {
				randomizeHuntingMission(player, mission);
			} else {
				mission->setTypeCRC(0);
			} /*
			if (i < bagSize / maximumNumberOfMissionTypesInOneTerminal)
				randomizeHuntingMission(player, mission);
			else
				mission->setTypeCRC(0);*/

		} else if (missionTerminal->isBountyTerminal()) {
			if (i < bagSize / maximumNumberOfMissionTypesInOneTerminal) {
				randomizeBountyMission(player, mission);
			} else {
				mission->setTypeCRC(0);
			}
		}

		if (missionTerminal->isSlicer(player)) {
			mission->setRewardCredits(mission->getRewardCredits() * 2);
		}

	//	randomizeHuntingMission(player, mission);
		mission->setRefreshCounter(counter, true);
	}

	// Remove the Slicer from the List. They have received their one time mission reward increase.
	if (missionTerminal->isSlicer(player))
		missionTerminal->removeSlicer(player);

}

void MissionManagerImplementation::randomizeDestroyMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericDestroyMission(player, mission, MissionObject::FACTIONNEUTRAL);
}

void MissionManagerImplementation::randomizeGenericDestroyMission(CreatureObject* player, MissionObject* mission, const int faction) {
	LairSpawn* randomLairSpawn = getRandomLairSpawn(player);

	if (randomLairSpawn == NULL) {
		mission->setTypeCRC(0);
		return;
	}

	String lairTemplate = randomLairSpawn->getLairTemplateName();
	LairTemplate* lairTemplateObject = CreatureTemplateManager::instance()->getLairTemplate(lairTemplate.hashCode());

	if (lairTemplateObject == NULL) {
		mission->setTypeCRC(0);
		return;
	}

	int difficulty = server->getPlayerManager()->calculatePlayerLevel(player);
	String building = lairTemplateObject->getBuilding(difficulty);

	if (building.isEmpty()) {
		mission->setTypeCRC(0);
		return;
	}

	SharedObjectTemplate* templateObject = TemplateManager::instance()->getTemplate(building.hashCode());

	if (templateObject == NULL || !templateObject->isSharedTangibleObjectTemplate()) {
		error("incorrect template object in randomizeDestroyMission " + building);
		mission->setTypeCRC(0);
		return;
	}

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(34) + 1;

	mission->setMissionNumber(randTexts);

	Vector3 startPos = player->getWorldCoordinate(System::random(1000) + 1000, (float)System::random(360));
	//mission->setMissionTarget(lairObjectTemplate->getObjectName());
	mission->setStartPlanet(player->getZone()->getZoneName());
	mission->setStartPosition(startPos.getX(), startPos.getY(), player->getZone()->getZoneName());
	mission->setCreatorName(nm->makeCreatureName());

	mission->setMissionTargetName(templateObject->getObjectName());
	mission->setTargetTemplate(templateObject);
	mission->setTargetOptionalTemplate(lairTemplate);

	mission->setRewardCredits(System::random(difficulty * 100) + (difficulty * 200));
	mission->setMissionDifficulty(difficulty);

	mission->setFaction(faction);

	String messageDifficulty;

	if (difficulty <= 10)
		messageDifficulty = "_easy";
	else if (difficulty <= 17)
		messageDifficulty = "_medium";
	else
		messageDifficulty = "_hard";

	mission->setMissionTitle("mission/mission_destroy_neutral" + messageDifficulty + "_creature", "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_destroy_neutral" +  messageDifficulty + "_creature", "m" + String::valueOf(randTexts) + "d");

	mission->setTypeCRC(MissionObject::DESTROY);

}

void MissionManagerImplementation::randomizeSurveyMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericSurveyMission(player, mission, MissionObject::FACTIONNEUTRAL);
}

void MissionManagerImplementation::randomizeGenericSurveyMission(CreatureObject* player, MissionObject* mission, const int faction) {
	int maxLevel = 50;
	int minLevel = 50;
	long long surveySkill = player->getSkillMod("surveying");
	if (surveySkill > 30) {
		maxLevel += 10;
	}
	if (surveySkill > 50) {
		maxLevel += 10;
	}
	if (surveySkill > 70) {
		maxLevel += 10;
	}
	if (surveySkill > 90) {
		maxLevel += 10;
	}
	if (surveySkill > 100) {
		//Max mission level is 95.
		maxLevel += 5;
	}

	//Mission level used as needed concentration in increments of 5. I.e. 50, 55, 60 etc. up to 95.
	int randLevel = minLevel + 5 * System::random((maxLevel - minLevel) / 5);

	if (randLevel > maxLevel)
		randLevel = maxLevel;

	ResourceManager* manager = server->getResourceManager();

	String zoneName = player->getZone()->getZoneName();

	Vector<ManagedReference<ResourceSpawn*> > resources;

	int toolType = SurveyTool::MINERAL;

	//75 % mineral, 25 % chemical.
	if (System::random(3) == 0) {
		toolType = SurveyTool::CHEMICAL;
	}

	manager->getResourceListByType(resources, toolType, zoneName);

	ManagedReference<ResourceSpawn*> spawn = resources.get(System::random(resources.size() - 1));
	uint32 containerCRC = spawn->getContainerCRC();
	SharedObjectTemplate* templateObject = TemplateManager::instance()->getTemplate(containerCRC);

	NameManager* nm = processor->getNameManager();

	int texts = System::random(50);

	if (texts == 0)
		texts = 1;

	mission->setMissionTargetName(spawn->getFamilyName());
	mission->setTargetTemplate(templateObject);

	//Reward depending on mission level.
	mission->setRewardCredits(400 + (randLevel - minLevel) * 20 + System::random(100));

	mission->setFaction(faction);

	mission->setMissionDifficulty(randLevel);
	mission->setStartPosition(player->getPositionX(), player->getPositionY(), player->getZone()->getZoneName());
	mission->setMissionTitle("mission/mission_npc_survey_neutral_easy", "m" + String::valueOf(texts) + "t");
	mission->setMissionDescription("mission/mission_npc_survey_neutral_easy", "m" + String::valueOf(texts) + "o");
	mission->setCreatorName(nm->makeCreatureName());

	mission->setTypeCRC(MissionObject::SURVEY);
}

void MissionManagerImplementation::randomizeBountyMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericBountyMission(player, mission, MissionObject::FACTIONNEUTRAL);
}

void MissionManagerImplementation::randomizeGenericBountyMission(CreatureObject* player, MissionObject* mission, const int faction) {
	if (!player->hasSkill("combat_bountyhunter_novice")) {
		player->sendSystemMessage("@mission/mission_generic:not_bounty_hunter_terminal");
		mission->setTypeCRC(0);
		return;
	}

	int difficulty = 1;
	if (player->hasSkill("combat_bountyhunter_investigation_03")) {
		difficulty = 3;
	} else if (player->hasSkill("combat_bountyhunter_investigation_01")) {
		difficulty = 2;
	}

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(24) + 1;

	mission->setMissionNumber(randTexts);

	mission->setStartPlanet(player->getZone()->getZoneName());
	mission->setStartPosition(player->getPositionX(), player->getPositionY(), player->getZone()->getZoneName());
	mission->setCreatorName(nm->makeCreatureName());

	mission->setMissionTargetName("???");
	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(String("object/tangible/mission/mission_bounty_target.iff").hashCode()));

	mission->setFaction(faction);

	Vector3 endPos = getRandomBountyTargetPosition(player);
	String planet = player->getZone()->getZoneName();
	mission->setEndPosition(endPos.getX(), endPos.getY(), planet, true);

	mission->setRewardCredits(500 + System::random(500));
	mission->setMissionDifficulty(difficulty);
	mission->setMissionTitle("mission/mission_bounty_neutral_easy", "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_bounty_neutral_easy", "m" + String::valueOf(randTexts) + "d");

	mission->setTypeCRC(MissionObject::BOUNTY);
}

void MissionManagerImplementation::randomizeDeliverMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericDeliverMission(player, mission, MissionObject::FACTIONNEUTRAL);
}

void MissionManagerImplementation::randomizeGenericDeliverMission(CreatureObject* player, MissionObject* mission, const int faction) {
	//Randomize in city or between city missions.
	bool inTownMission = true;
	if (System::random(1) == 1) {
		inTownMission = false;
	}

	if (!randomGenericDeliverMission(player, mission, inTownMission, faction)) {
		//In town or out of town mission failed try the other sort of mission instead.
		inTownMission = !inTownMission;
		randomGenericDeliverMission(player, mission, inTownMission, faction);
	}
}

String MissionManagerImplementation::getDeliveryMissionFileName(const int faction) {
	switch (faction) {
	case MissionObject::FACTIONIMPERIAL:
		return "mission/mission_deliver_imperial_easy";
	case MissionObject::FACTIONREBEL:
		return "mission/mission_deliver_rebel_easy";
	default:
		return "mission/mission_deliver_neutral_easy";
	}
}

int MissionManagerImplementation::getDeliverMissionNumberOfMissions(const int faction) {
	switch (faction) {
	case MissionObject::FACTIONIMPERIAL:
		return 24;
	case MissionObject::FACTIONREBEL:
		return 24;
	default:
		return 29;
	}
}

int MissionManagerImplementation::getDeliverMissionSpawnType(const int faction) {
	switch (faction) {
	case MissionObject::FACTIONIMPERIAL:
		return NpcSpawnPoint::IMPERIALSPAWN;
	case MissionObject::FACTIONREBEL:
		return NpcSpawnPoint::REBELSPAWN;
	default:
		return NpcSpawnPoint::NEUTRALSPAWN;
	}
}

bool MissionManagerImplementation::randomGenericDeliverMission(CreatureObject* player, MissionObject* mission, bool inTownMission, const int faction) {
	//Get the current planet and position of the player.
	String planetName = player->getZone()->getZoneName();

	Vector3 playerPosition = player->getWorldPosition();
	Vector3* startPosition = &playerPosition;

	//Lock spawn point map for the search.
	Locker missionSpawnLocker(&missionNpcSpawnMap);

	//Find a spawn point in current city.
	float minDistance = 0.0f;
	float maxDistance = 300.0f;
	Reference<NpcSpawnPoint*> startNpc = missionNpcSpawnMap.getRandomNpcSpawnPoint(planetName.hashCode(), startPosition, getDeliverMissionSpawnType(faction), minDistance, maxDistance, false);

	if (startNpc == NULL) {
		//Couldn't find a suitable spawn point.
		return false;
	}

	//Find a spawn point for the delivery target.
	Vector3* endPosition = startPosition;
	if (!inTownMission) {
		//Find city center of another city and use as position to search for spawn points from.
		endPosition = missionNpcSpawnMap.getRandomCityCoordinates(planetName.hashCode(), startPosition);

	}
	//Search in all parts of the city for the end spawn.
	minDistance = 5.0f;
	maxDistance = 1500.0f;
	Reference<NpcSpawnPoint*> endNpc = missionNpcSpawnMap.getRandomNpcSpawnPoint(planetName.hashCode(), endPosition, getDeliverMissionSpawnType(faction), minDistance, maxDistance, false);

	if (endNpc == NULL) {
		//Couldn't find a suitable spawn point.
		return false;
	}

	//Randomize mission description strings/delivery object.
	int randomTexts = System::random(getDeliverMissionNumberOfMissions(faction)) + 1;

	//Setup mission object.
	mission->setMissionNumber(randomTexts);
	mission->setMissionTarget(startNpc);
	mission->setMissionTargetDest(endNpc);

	NameManager* nm = processor->getNameManager();
	mission->setCreatorName(nm->makeCreatureName());
	mission->setMissionTargetName(TemplateManager::instance()->getTemplate(String("object/tangible/mission/mission_datadisk.iff").hashCode())->getObjectName());

	String planet = player->getZone()->getZoneName();
	mission->setStartPlanet(planet);
	mission->setStartPosition(startNpc->getPosition()->getX(), startNpc->getPosition()->getY(), planet, true);
	mission->setEndPosition(endNpc->getPosition()->getX(), endNpc->getPosition()->getY(), planet);

	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(String("object/tangible/mission/mission_datadisk.iff").hashCode()));

	int baseCredits = 50;
	int deliverDistanceCredits = startNpc->getPosition()->distanceTo(*(endNpc->getPosition())) / 10;

	mission->setRewardCredits(baseCredits + deliverDistanceCredits);

	switch (faction) {
	case MissionObject::FACTIONIMPERIAL:
		mission->setRewardFactionPointsImperial(5);
		mission->setRewardFactionPointsRebel(0);
		break;
	case MissionObject::FACTIONREBEL:
		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(5);
		break;
	default:
		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(0);
		break;
	}

	mission->setMissionDifficulty(5);
	mission->setMissionTitle(getDeliveryMissionFileName(faction), "m" + String::valueOf(randomTexts) + "t");
	mission->setMissionDescription(getDeliveryMissionFileName(faction), "m" + String::valueOf(randomTexts) + "d");

	mission->setTypeCRC(MissionObject::DELIVER);
	mission->setFaction(faction);

	return true;
}

NpcSpawnPoint* MissionManagerImplementation::getRandomFreeNpcSpawnPoint(unsigned const int planetCRC, const float x, const float y, const int spawnType) {
	float min = 0.0f;
	float max = 50.0f;

	Locker missionSpawnLocker(&missionNpcSpawnMap);

	//Try to find a free NPC spawn point in a circle with a radius of max.
	while (max <= 1600.0f) {
		Reference<NpcSpawnPoint* > npc = missionNpcSpawnMap.getRandomNpcSpawnPoint(planetCRC, new Vector3(x, y, 0), spawnType, min, max, true);
		if (npc != NULL) {
			return npc;
		} else {
			//No NPC spawn point found, double the search area radius.
			max *= 2;
		}
	}

	//Couldn't find any free NPC spawn point.
	return NULL;
}

void MissionManagerImplementation::returnSpawnPoint(NpcSpawnPoint* spawnPoint) {
	if (spawnPoint != NULL) {
		//Lock spawn map before changing the spawn point parameters.
		Locker missionSpawnLocker(&missionNpcSpawnMap);
		spawnPoint->setInUse(false);
	}
}

void MissionManagerImplementation::randomizeCraftingMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericCraftingMission(player, mission, MissionObject::FACTIONNEUTRAL);
}

void MissionManagerImplementation::randomizeGenericCraftingMission(CreatureObject* player, MissionObject* mission, const int faction) {
	//Create a random neutral delivery mission that can be modified.
	randomizeGenericDeliverMission(player, mission, faction);

	//Modify the delivery mission to be a crafting mission.
	int maximumMissionNumber;
	String fileName = "";

	switch (faction) {
	case MissionObject::FACTIONIMPERIAL:
		maximumMissionNumber = 34;
		fileName = "mission/mission_npc_crafting_imperial_easy";
		break;
	case MissionObject::FACTIONREBEL:
		maximumMissionNumber = 34;
		fileName = "mission/mission_npc_crafting_rebel_easy";
		break;
	default:
		maximumMissionNumber = 49;
		fileName = "mission/mission_npc_crafting_neutral_easy";
		break;
	}

	int missionNumber = System::random(maximumMissionNumber) + 1;
	mission->setMissionTitle(fileName, "m" + String::valueOf(missionNumber) + "t");
	mission->setMissionDescription(fileName, "m" + String::valueOf(missionNumber) + "d");

	mission->setTypeCRC(MissionObject::CRAFTING);
}

void MissionManagerImplementation::randomizeGenericEntertainerMission(CreatureObject* player, MissionObject* mission, const int faction, const int missionType) {
	//Generate difficulty for mission. How far away missions can be.
	int difficulty = 1;

	if (missionType == MissionObject::DANCER && player->hasSkill("social_dancer_novice")) {
		difficulty = 2;
	} else if (missionType == MissionObject::MUSICIAN && player->hasSkill("social_musician_novice")) {
		difficulty = 2;
	}

	int randomRange = System::random(difficulty - 1) + 1;

	PlanetManager* pmng = player->getZone()->getPlanetManager();
	MissionTargetMap* performanceLocations = pmng->getPerformanceLocations();
	if (performanceLocations->size() <= 0) {
		mission->setTypeCRC(0);
		return;
	}

	// TODO: filter by distance (get closer locations for lower difficulties)
	SceneObject* target = performanceLocations->getRandomTarget(player, randomRange);
	if (target == NULL || !target->isStructureObject()) {
		mission->setTypeCRC(0);
		return;
	}

	NameManager* nm = processor->getNameManager();

	String missionString = "musician";
	if (missionType == MissionObject::DANCER) {
		missionString = "dancer";
	}

	int numberOfMissions = 49;
	if (faction != MissionObject::FACTIONNEUTRAL) {
		numberOfMissions = 34;
	}
	int randTexts = System::random(numberOfMissions) + 1;

	mission->setMissionNumber(randTexts);
	mission->setCreatorName(nm->makeCreatureName());

	mission->setStartPlanet(player->getZone()->getZoneName());
	mission->setStartPosition(target->getPositionX(), target->getPositionY(), player->getZone()->getZoneName());

	if (missionType == MissionObject::DANCER) {
		mission->setMissionTargetName("@ui_mission:dancer_tab");
	} else {
		mission->setMissionTargetName("@ui_mission:musician_tab");
	}

	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(String("object/building/general/mun_all_guild_theater_s01.iff").hashCode()));

	int distanceReward = player->getWorldPosition().distanceTo(target->getPosition()) / 10;

	mission->setRewardCredits(100 + distanceReward + System::random(100));

	mission->setFaction(faction);

	switch (faction) {
	case MissionObject::FACTIONIMPERIAL:
		mission->setRewardFactionPointsImperial(5);
		mission->setRewardFactionPointsRebel(0);
		mission->setMissionTitle("mission/mission_npc_" + missionString + "_imperial_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_" + missionString + "_imperial_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	case MissionObject::FACTIONREBEL:
		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(5);
		mission->setMissionTitle("mission/mission_npc_" + missionString + "_rebel_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_" + missionString + "_rebel_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	default:
		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(0);
		mission->setMissionTitle("mission/mission_npc_" + missionString + "_neutral_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_" + missionString + "_neutral_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	}

	mission->setMissionDifficulty(5 * randomRange);

	mission->setTypeCRC(missionType);
}

void MissionManagerImplementation::randomizeHuntingMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericHuntingMission(player, mission, MissionObject::FACTIONNEUTRAL);
}

void MissionManagerImplementation::randomizeGenericHuntingMission(CreatureObject* player, MissionObject* mission, const int faction) {
	LairSpawn* randomLairSpawn = getRandomLairSpawn(player);

	if (randomLairSpawn == NULL) {
		mission->setTypeCRC(0);
		return;
	}

	LairTemplate* lairTemplate = CreatureTemplateManager::instance()->getLairTemplate(randomLairSpawn->getLairTemplateName().hashCode());

	if (lairTemplate == NULL) {
		mission->setTypeCRC(0);
		return;
	}

	VectorMap<String, uint32>* mobiles = lairTemplate->getMobiles();

	if (mobiles->size() == 0) {
		mission->setTypeCRC(0);
		return;
	}

	String mobileName = mobiles->elementAt(0).getKey();

	CreatureTemplate* creatureTemplate = CreatureTemplateManager::instance()->getTemplate(mobileName);

	if (creatureTemplate == NULL) {
		mission->setTypeCRC(0);
		return;
	}

	Vector<String>& templatesNames = creatureTemplate->getTemplates();

	if (templatesNames.size() == 0) {
		mission->setTypeCRC(0);
		return;
	}

	String serverTemplate = templatesNames.get(0);

	SharedObjectTemplate* sharedTemplate = TemplateManager::instance()->getTemplate(serverTemplate.hashCode());

	if (sharedTemplate == NULL) {
		mission->setTypeCRC(0);
		return;
	}

	mission->setTemplateStrings(mobileName, mobileName);

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(7) + 1;

	String creatorName = nm->makeCreatureName();

	//info("creator name " + creatorName, true);

	mission->setMissionNumber(randTexts);
	mission->setCreatorName(creatorName);

	mission->setStartPlanet(player->getZone()->getZoneName());
	mission->setStartPosition(player->getPositionX(), player->getPositionY(), player->getZone()->getZoneName());

	mission->setMissionTargetName(creatureTemplate->getObjectName());
	mission->setTargetTemplate(sharedTemplate);

	//50% easy missions, 33% medium missions, 17% hard missions.
	int difficulty = System::random(5) + 1;
	String diffString;
	if (difficulty <= 3) {
		difficulty = 1;
		diffString = "easy";
	} else if (difficulty <= 5) {
		difficulty = 2;
		diffString = "medium";
	} else {
		difficulty = 3;
		diffString = "hard";
	}

	int baseReward = 100 + difficulty * (200 + randomLairSpawn->getMinDifficulty());
	mission->setRewardCredits(baseReward + System::random(100));
	mission->setMissionDifficulty(difficulty);
	mission->setMissionTitle("mission/mission_npc_hunting_neutral_" + diffString, "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_npc_hunting_neutral_" + diffString, "m" + String::valueOf(randTexts) + "o");

	mission->setTypeCRC(MissionObject::HUNTING);
	mission->setFaction(faction);
}

void MissionManagerImplementation::randomizeGenericReconMission(CreatureObject* player, MissionObject* mission, const int faction) {
	bool foundPosition = false;
	Vector3 position;

	while (!foundPosition) {
		position = player->getWorldCoordinate(System::random(3000) + 1000, (float)System::random(360));

		if (position.getX() > player->getZone()->getMaxX() - 500) {
			position.setX(player->getZone()->getMaxX());
		} else if (position.getX() < player->getZone()->getMinX() + 500) {
			position.setX(player->getZone()->getMinX());
		}
		if (position.getY() > player->getZone()->getMaxY() - 500) {
			position.setY(player->getZone()->getMaxY());
		} else if (position.getY() < player->getZone()->getMinY() + 500) {
			position.setY(player->getZone()->getMinY());
		}

		//Check if it is a position where you can build and away from any travel points.
		if (player->getZone()->getPlanetManager()->isBuildingPermittedAt(position.getX(), position.getY(), NULL)) {
			ManagedReference<PlanetTravelPoint*> travelPoint = player->getZone()->getPlanetManager()->getNearestPlanetTravelPoint(position);

			if (travelPoint->getArrivalPosition().distanceTo(position) > 1000.0f) {
				foundPosition = true;
			}
		}
	}

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(24) + 1;

	mission->setMissionNumber(randTexts);
	mission->setCreatorName(nm->makeCreatureName());

	mission->setMissionTargetName(TemplateManager::instance()->getTemplate(String("object/tangible/mission/mission_recon_target.iff").hashCode())->getObjectName());
	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(String("object/tangible/mission/mission_recon_target.iff").hashCode()));

	mission->setStartPlanet(player->getZone()->getZoneName());
	mission->setStartPosition(position.getX(), position.getY(), player->getZone()->getZoneName());

	int reward = position.distanceTo(player->getWorldPosition()) / 5;

	mission->setRewardCredits(50 + reward);

	switch (faction) {
	case MissionObject::FACTIONIMPERIAL:
		mission->setRewardFactionPointsImperial(10);
		mission->setRewardFactionPointsRebel(0);
		mission->setMissionTitle("mission/mission_npc_recon_imperial_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_recon_imperial_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	case MissionObject::FACTIONREBEL:
		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(10);
		mission->setMissionTitle("mission/mission_npc_recon_rebel_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_recon_rebel_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	default:
		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(0);
		mission->setMissionTitle("mission/mission_npc_recon_neutral_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_recon_neutral_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	}

	mission->setMissionDifficulty(1);

	mission->setFaction(faction);

	mission->setTypeCRC(MissionObject::RECON);
}

void MissionManagerImplementation::randomizeReconMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericReconMission(player, mission, MissionObject::FACTIONNEUTRAL);
}

void MissionManagerImplementation::randomizeImperialDestroyMission(CreatureObject* player, MissionObject* mission) {
	// TODO: add faction-specific targets
	randomizeGenericDestroyMission(player, mission, MissionObject::FACTIONIMPERIAL);
}

void MissionManagerImplementation::randomizeImperialDeliverMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericDeliverMission(player, mission, MissionObject::FACTIONIMPERIAL);
}

void MissionManagerImplementation::randomizeImperialCraftingMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericCraftingMission(player, mission, MissionObject::FACTIONIMPERIAL);
}

void MissionManagerImplementation::randomizeImperialReconMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericReconMission(player, mission, MissionObject::FACTIONIMPERIAL);
}

void MissionManagerImplementation::randomizeRebelDestroyMission(CreatureObject* player, MissionObject* mission) {
	// TODO: add faction-specific targets
	randomizeGenericDestroyMission(player, mission, MissionObject::FACTIONREBEL);
}

void MissionManagerImplementation::randomizeRebelDeliverMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericDeliverMission(player, mission, MissionObject::FACTIONREBEL);
}

void MissionManagerImplementation::randomizeRebelCraftingMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericCraftingMission(player, mission, MissionObject::FACTIONREBEL);
}

void MissionManagerImplementation::randomizeRebelReconMission(CreatureObject* player, MissionObject* mission) {
	randomizeGenericReconMission(player, mission, MissionObject::FACTIONREBEL);
}

void MissionManagerImplementation::createSpawnPoint(CreatureObject* player, const String& spawnTypes) {
	if (player == NULL) {
		return;
	}

	if (player->getParentID() != 0) {
		player->sendSystemMessage("Mission NPC spawns cannot be placed inside buildings.");
		return;
	}

	Reference<NpcSpawnPoint* > npc = new NpcSpawnPoint(player, spawnTypes);
	if (npc != NULL && npc->getSpawnType() != 0) {
		//Lock mission spawn points.
		Locker missionSpawnLocker(&missionNpcSpawnMap);

		String message;
		NpcSpawnPoint* returnedNpc = missionNpcSpawnMap.findSpawnAt(player->getPlanetCRC(), npc->getPosition());
		if (returnedNpc != NULL) {
			message = "NPC spawn point to close to existing spawn point at coordinates " + returnedNpc->getPosition()->toString() + " of spawn type " + String::valueOf(returnedNpc->getSpawnType());
		} else {
			returnedNpc = missionNpcSpawnMap.addSpawnPoint(player->getPlanetCRC(), npc);
			if (returnedNpc == NULL) {
				message = "Could not create spawn point here since the planet does not exist.";
			} else if (*returnedNpc->getPosition() == *npc->getPosition()) {
				message = "NPC spawn point created at coordinates " + npc->getPosition()->toString() + " of spawn type " + String::valueOf(npc->getSpawnType());
				missionNpcSpawnMap.saveSpawnPoints();
			} else {
				message = "NPC spawn point to close to existing spawn point at coordinates " + returnedNpc->getPosition()->toString() + " of spawn type " + String::valueOf(returnedNpc->getSpawnType());
			}
		}
		player->sendSystemMessage(message);
	} else {
		player->sendSystemMessage("Incorrect parameters. /createMissionElement [spawn type(s)] - (spawn types supported: neutral, imperial, rebel, bhtarget, nospawn)");
	}
}

LairSpawn* MissionManagerImplementation::getRandomLairSpawn(CreatureObject* player) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return NULL;

	CreatureManager* creatureManager = zone->getCreatureManager();

	Vector<ManagedReference<SpawnArea* > >* worldAreas = creatureManager->getWorldSpawnAreas();
	ManagedReference<SpawnArea*> spawnArea;

	if (worldAreas->size() == 0) {
		return NULL;
	}

	int rand = System::random(worldAreas->size() - 1);

	spawnArea = worldAreas->get(rand);

	if (spawnArea == NULL || !spawnArea->isLairSpawnArea()) {
		return NULL;
	}

	LairSpawnArea* lairSpawnArea = cast<LairSpawnArea*>(spawnArea.get());
	LairSpawnGroup* lairSpawnGroup = lairSpawnArea->getSpawnGroup();

	if (lairSpawnGroup == NULL) {
		return NULL;
	}

	Vector<Reference<LairSpawn*> >* availableLairList = lairSpawnGroup->getLairList();

	if (availableLairList == NULL || availableLairList->size() == 0) {
		return NULL;
	}

	bool foundLair = false;
	int counter = availableLairList->size();
	int playerLevel = server->getPlayerManager()->calculatePlayerLevel(player);
	LairSpawn* lairSpawn = NULL;

	//Try to pick random lair within playerLeve +-5;
	while (counter > 0 && !foundLair) {
		LairSpawn* randomLairSpawn = availableLairList->get(System::random(availableLairList->size() - 1));
		if (randomLairSpawn != NULL) {
			if (randomLairSpawn->getMinDifficulty() <= (playerLevel + 5) ||
					randomLairSpawn->getMaxDifficulty() >= (playerLevel - 5)) {
				lairSpawn = randomLairSpawn;
				foundLair = true;
			}
		}

		--counter;
	}

	if (!foundLair) {
		//No random lair found, iterate through all lairs and find the first within playerLeve +-5;
		for (int i = 0; i < availableLairList->size(); i++) {
			LairSpawn* randomLairSpawn = availableLairList->get(i);
			if (randomLairSpawn->getMinDifficulty() <= (playerLevel + 5) ||
					randomLairSpawn->getMaxDifficulty() >= (playerLevel - 5)) {
				lairSpawn = randomLairSpawn;
				break;
			}
		}
	}

	return lairSpawn;
}

Vector3 MissionManagerImplementation::getRandomBountyTargetPosition(CreatureObject* player) {
	Vector3 position;
	bool found = false;
	float radiusX = player->getZone()->getMaxX() - player->getZone()->getMinX();
	float radiusY = player->getZone()->getMaxY() - player->getZone()->getMinY();
	float radius = radiusX > radiusY ? radiusX : radiusY;

	while (!found) {
		position = player->getWorldCoordinate(System::random(radius), System::random(360));

		if (position.getX() > player->getZone()->getMinX() && position.getX() < player->getZone()->getMaxX() &&
				position.getY() > player->getZone()->getMinY() && position.getY() < player->getZone()->getMaxY()) {
			found = player->getZone()->getPlanetManager()->isBuildingPermittedAt(position.getX(), position.getY(), NULL);
		}
	}

	return position;
}

MissionObject* MissionManagerImplementation::getBountyHunterMission(CreatureObject* player) {
	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad != NULL) {
		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			if (datapad->getContainerObject(i)->isMissionObject()) {
				ManagedReference<MissionObject*> mission = cast<MissionObject*>(datapad->getContainerObject(i));

				if (mission != NULL && mission->getTypeCRC() == MissionObject::BOUNTY) {
					return mission;
				}
			}
		}
	}

	return NULL;
}
