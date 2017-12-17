/*
 * MissionManagerImplementation.cpp
 *
 *  Created on: 21/06/2010
 *      Author: victor
 */

#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/SurveyMissionObjective.h"
#include "server/zone/objects/mission/DestroyMissionObjective.h"
#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "server/zone/objects/mission/CraftingMissionObjective.h"
#include "server/zone/objects/mission/EntertainerMissionObjective.h"
#include "server/zone/objects/mission/HuntingMissionObjective.h"
#include "server/zone/objects/mission/ReconMissionObjective.h"
#include "server/zone/objects/mission/BountyMissionObjective.h"
#include "server/zone/objects/area/SpawnArea.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/planet/MissionTargetMap.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "templates/mobile/LairTemplate.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/managers/visibility/VisibilityManager.h"

void MissionManagerImplementation::loadLuaSettings() {
	try {
		Lua* lua = new Lua();
		lua->init();

		lua->runFile("scripts/managers/mission/mission_manager.lua");

		LuaObject items = lua->getGlobalObject("crafting_mission_items");

		for (int i = 1; i <= items.getTableSize(); i++) {
			craftingMissionItems.add(items.getStringAt(i));
		}

		items.pop();

		LuaObject zones = lua->getGlobalObject("bh_target_zones");

		for (int i = 1; i <= zones.getTableSize(); i++) {
			bhTargetZones.add(zones.getStringAt(i));
		}

		zones.pop();

		LuaObject targetsAtMissionLevel = lua->getGlobalObject("bh_targets_at_mission_level");

		for (unsigned int i = 1; i <= 3; i++) {
			Vector<String> targets;
			LuaObject level = targetsAtMissionLevel.getObjectField("level" + String::valueOf(i));

			for (int j = 1; j <= level.getTableSize(); j++) {
				targets.add(level.getStringAt(j));
			}
			level.pop();

			bhTargetsAtMissionLevel.put(i, targets);
		}

		targetsAtMissionLevel.pop();

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

		value = lua->getGlobalString("enable_same_account_bounty_missions");

		if (value.toLowerCase() == "true") {
			enableSameAccountBountyMissions = true;
		}

		delete lua;
	}
	catch (Exception& e) {
		error(e.getMessage());
	}
}

void MissionManagerImplementation::loadPlayerBounties() {
	info("Loading player bounties from playerbounties.db");

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* playerBountyDatabase = dbManager->loadObjectDatabase("playerbounties", true);

	if (playerBountyDatabase == NULL) {
		error("Could not load the player bounties database.");
		return;
	}

	int i = 0;

	try {
		ObjectDatabaseIterator iterator(playerBountyDatabase);

		uint64 objectID = 0;

		while (iterator.getNextKey(objectID)) {
			Reference<PlayerBounty*> bounty = Core::getObjectBroker()->lookUp(objectID).castTo<PlayerBounty*>();

			if (bounty != NULL) {
				++i;

				bounty->setOnline(false);

				playerBountyList.put(bounty->getTargetPlayerID(), bounty);

				if (ConfigManager::instance()->isProgressMonitorActivated())
					printf("\r\tLoading player bounties [%d] / [?]\t", i);
			} else {
				error("Failed to deserialize player bounty with objectID: " + String::valueOf(objectID));
			}
		}
	} catch (DatabaseException& e) {
		error("Database exception in MissionManager::loadPlayerBounties(): " + e.getMessage());
	}

	bool log = i > 0;
	info("Loaded " + String::valueOf(i) + " player bounties.", log);
}

void MissionManagerImplementation::handleMissionListRequest(MissionTerminal* missionTerminal, CreatureObject* player, int counter) {
	// newbie and statue terminals don't exist, but their templates do
	if (missionTerminal->isStatueTerminal() || missionTerminal->isNewbieTerminal()) {
		player->sendSystemMessage("@skill_teacher:skill_terminal_disabled");
		return;
	}

	if (!player->isInRange(missionTerminal, 6)) {
		StringIdChatParameter stringId("ui", "radial_out_of_range_prose"); // %TT is too far away to '%TO'.
		stringId.setTT(missionTerminal->getObjectID());
		stringId.setTO("ui_radial", "terminal_mission_list"); // List Missions
		player->sendSystemMessage(stringId);
		return;
	}

	if (missionTerminal->isBountyTerminal()) {
		if (!player->hasSkill("combat_bountyhunter_novice")) {
			player->sendSystemMessage("@mission/mission_generic:not_bounty_hunter_terminal");
			return;
		}
	}

	ManagedReference<CityRegion*> terminalCity = missionTerminal->getCityRegion().get();

	if (terminalCity != NULL) {
		if (terminalCity.get()->isBanned(player->getObjectID())) {
			player->sendSystemMessage("@city/city:banned_services"); // You are banned from using this city's services.
			return;
		}
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
		ManagedReference<SceneObject*> mission = server->createObject(0x18e19914, 1); // empty mission
		missionBag->transferObject(mission, -1, false);
		mission->sendTo(player, true);
		//missionBag->updateToDatabaseWithoutChildren();
	}

	populateMissionList(missionTerminal, player, counter);
}

void MissionManagerImplementation::handleMissionAccept(MissionTerminal* missionTerminal, MissionObject* mission, CreatureObject* player) {
	ManagedReference<SceneObject*> missionBag = mission->getParent().get();

	if (missionBag == NULL)
		return;

	ManagedReference<SceneObject*> bagParent = missionBag->getParent().get();

	if (bagParent != player)
		return;

	SceneObject* playerMissionBag = player->getSlottedObject("mission_bag");

	if (playerMissionBag != missionBag)
		return;

	SceneObject* datapad = player->getSlottedObject("datapad");

	if (mission->getParent().get() == datapad)
		return;

	int missionCount = 0;
	bool hasBountyMission = false;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		SceneObject* obj = datapad->getContainerObject(i);

		if (obj->isMissionObject()) {
			++missionCount;
			MissionObject* datapadMission = cast<MissionObject*>(obj);
			if (datapadMission->getTypeCRC() == MissionTypes::BOUNTY) {
				hasBountyMission = true;
			}
		}
	}

	//Limit to two missions (only one of them can be a bounty mission)
	if (missionCount >= 2 || (hasBountyMission && mission->getTypeCRC() == MissionTypes::BOUNTY)) {
		StringIdChatParameter stringId("mission/mission_generic", "too_many_missions");
		player->sendSystemMessage(stringId);
		return;
	}

	if (mission->getTypeCRC() == MissionTypes::BOUNTY) {
		Locker listLocker(&playerBountyListMutex);

		uint64 targetID = mission->getTargetObjectId();
		if (targetID != 0) {
			PlayerBounty* bounty = playerBountyList.get(targetID);

			if (bounty == NULL || !isBountyValidForPlayer(player, bounty)) {
				player->sendSystemMessage("Mission has expired.");
				return;
			} else {
				addBountyHunterToPlayerBounty(targetID, player->getObjectID());
			}
		}
	}

	datapad->transferObject(mission, -1, true);

	createMissionObjectives(mission, missionTerminal, player);

	player->updateToDatabaseAllObjects(false);
}

void MissionManagerImplementation::createDestroyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<DestroyMissionObjective*> objective = new DestroyMissionObjective(mission);

	Locker locker(objective);

	objective->setLairTemplateToSpawn(mission->getTargetOptionalTemplate());
	objective->setDifficultyLevel(mission->getDifficultyLevel());
	objective->setDifficulty(mission->getDifficulty());

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createDeliverMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<DeliverMissionObjective*> objective = new DeliverMissionObjective(mission);

	Locker locker(objective);

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

	if (mission->getFaction() != Factions::FACTIONNEUTRAL && !enableFactionalCraftingMissions) {
		//Faction mission, but faction missions are disabled.
		return;
	}

	int datapadSize = datapad->getContainerObjectsSize();
	String missionItem = "";

	for (int i = 0; i < datapadSize; ++i) {
		if (datapad->getContainerObject(i)->isMissionObject()) {
			Reference<MissionObject*> datapadMission = datapad->getContainerObject(i).castTo<MissionObject*>();

			if (datapadMission != NULL && datapadMission->getTypeCRC() == MissionTypes::CRAFTING && datapadMission != mission) {
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

	String itemTemplate = craftingMissionItems.get(itemNumber).replaceFirst("draft_schematic/item/", "tangible/mission/");
	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(STRING_HASHCODE("object/tangible/mission/quest_item/attunement_grid.iff")));
	mission->setTemplateStrings(craftingMissionItems.get(itemNumber), itemTemplate);

	ManagedReference<CraftingMissionObjective*> objective = new CraftingMissionObjective(mission);

	Locker locker(objective);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createSurveyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<SurveyMissionObjective*> objective = new SurveyMissionObjective(mission);

	Locker locker(objective);

	objective->setEfficiency(mission->getDifficultyLevel());

	String spawnName = mission->getTargetName();

	objective->setSpawnFamily(spawnName);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createEntertainerMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<EntertainerMissionObjective*> objective = new EntertainerMissionObjective(mission);

	Locker locker(objective);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createHuntingMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<HuntingMissionObjective*> objective = new HuntingMissionObjective(mission);

	Locker locker(objective);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createReconMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<ReconMissionObjective*> objective = new ReconMissionObjective(mission);

	Locker locker(objective);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createBountyMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	ManagedReference<BountyMissionObjective*> objective = new BountyMissionObjective(mission);

	Locker locker(objective);

	ObjectManager::instance()->persistObject(objective, 1, "missionobjectives");

	mission->setMissionObjective(objective);
	objective->activate();
}

void MissionManagerImplementation::createMissionObjectives(MissionObject* mission, MissionTerminal* missionTerminal, CreatureObject* player) {
	uint32 missionType = mission->getTypeCRC();

	switch (missionType) {
	case MissionTypes::SURVEY:
		createSurveyMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionTypes::DESTROY:
		createDestroyMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionTypes::DELIVER:
		createDeliverMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionTypes::HUNTING:
		createHuntingMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionTypes::RECON:
		createReconMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionTypes::BOUNTY:
		createBountyMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionTypes::CRAFTING:
		createCraftingMissionObjectives(mission, missionTerminal, player);
		break;
	case MissionTypes::DANCER:
	case MissionTypes::MUSICIAN:
		createEntertainerMissionObjectives(mission, missionTerminal, player);
		break;
	default:
		break;
	}
}

void MissionManagerImplementation::removeMission(MissionObject* mission, CreatureObject* player) {
	ManagedReference<MissionObject*> ref = mission;

	ManagedReference<SceneObject*> missionParent = mission->getParent().get();
	SceneObject* datapad = player->getSlottedObject("datapad");

	if (missionParent != datapad)
		return;

	uint64 targetId = 0;

	if (mission->getTypeCRC() == MissionTypes::BOUNTY) {
		targetId = mission->getTargetObjectId();
		removeBountyHunterFromPlayerBounty(targetId, player->getObjectID());
	}

	Locker mlocker(mission);

	mission->destroyObjectFromWorld(true);
	mission->sendDestroyTo(player);

	mission->destroyObjectFromDatabase(true);
	player->updateToDatabaseAllObjects(false);

	mlocker.release();

	if (targetId != 0) {
		ManagedReference<CreatureObject*> target = server->getObject(targetId).castTo<CreatureObject*>();

		if (target != NULL)
			target->sendPvpStatusTo(player);
	}

	if (player->isGrouped() && player->getGroup() != NULL) {
		Reference<GroupObject*> group = player->getGroup();

		Locker locker(group);

		group->scheduleUpdateNearestMissionForGroup(player->getPlanetCRC());
	}
}

void MissionManagerImplementation::handleMissionAbort(MissionObject* mission, CreatureObject* player) {
	if (player->isIncapacitated()) {
		player->sendSystemMessage("You cannot abort a mission while incapacitated.");
		return;
	}

	if (player->isInCombat()) {
		player->sendSystemMessage("You cannot abort a mission while in combat.");
		return;
	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (mission->getTypeCRC() == MissionTypes::BOUNTY && ghost != NULL && ghost->hasBhTef()) {
		player->sendSystemMessage("You cannot abort a bounty hunter mission this soon after being in combat with the mission target.");
		return;
	}

	mission->abort();

	removeMission(mission, player);
}

void MissionManagerImplementation::populateMissionList(MissionTerminal* missionTerminal, CreatureObject* player, int counter) {
	bool slicer = missionTerminal->isSlicer(player);

	if (missionTerminal->isGeneralTerminal()) {
		randomizeGeneralTerminalMissions(player, counter, slicer);
	} else if (missionTerminal->isArtisanTerminal()) {
		randomizeArtisanTerminalMissions(player, counter, slicer);
	} else if (missionTerminal->isEntertainerTerminal()) {
		randomizeEntertainerTerminalMissions(player, counter, slicer);
	} else if (missionTerminal->isScoutTerminal()) {
		randomizeScoutTerminalMissions(player, counter, slicer);
	} else if (missionTerminal->isBountyTerminal()) {
		randomizeBountyTerminalMissions(player, counter);
	} else if (missionTerminal->isImperialTerminal()) {
		randomizeFactionTerminalMissions(player, counter, slicer, Factions::FACTIONIMPERIAL);
	} else if (missionTerminal->isRebelTerminal()) {
		randomizeFactionTerminalMissions(player, counter, slicer, Factions::FACTIONREBEL);
	}

	// Remove the Slicer from the List. They have received their one time mission reward increase.
	if (slicer)
		missionTerminal->removeSlicer(player);

}

void MissionManagerImplementation::randomizeGeneralTerminalMissions(CreatureObject* player, int counter, bool slicer) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");
	int bagSize = missionBag->getContainerObjectsSize();

	for (int i = 0; i < bagSize; ++i) {
		Reference<MissionObject*> mission = missionBag->getContainerObject(i).castTo<MissionObject*>( );

		Locker locker(mission);

		//Clear mission type before calling mission generators.
		mission->setTypeCRC(0);

		if (i < 6) {
			randomizeGenericDestroyMission(player, mission, Factions::FACTIONNEUTRAL);
		} else if (i < 12) {
			randomizeGenericDeliverMission(player, mission, Factions::FACTIONNEUTRAL);
		}

		if (slicer) {
			mission->setRewardCredits(mission->getRewardCredits() * 1.5);
		}

		float cityBonus = 1.f + player->getSkillMod("private_spec_missions") / 100.f;
		mission->setRewardCredits(mission->getRewardCredits() * cityBonus);

		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::randomizeArtisanTerminalMissions(CreatureObject* player, int counter, bool slicer) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");
	int bagSize = missionBag->getContainerObjectsSize();

	for (int i = 0; i < bagSize; ++i) {
		Reference<MissionObject*> mission = missionBag->getContainerObject(i).castTo<MissionObject*>( );

		Locker locker(mission);

		//Clear mission type before calling mission generators.
		mission->setTypeCRC(0);

		if (i < 6) {
			randomizeGenericSurveyMission(player, mission, Factions::FACTIONNEUTRAL);
		} else if (i < 12) {
			randomizeGenericCraftingMission(player, mission, Factions::FACTIONNEUTRAL);
		}

		if (slicer) {
			mission->setRewardCredits(mission->getRewardCredits() * 1.5);
		}

		float cityBonus = 1.f + player->getSkillMod("private_spec_missions") / 100.f;
		mission->setRewardCredits(mission->getRewardCredits() * cityBonus);

		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::randomizeEntertainerTerminalMissions(CreatureObject* player, int counter, bool slicer) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");
	int bagSize = missionBag->getContainerObjectsSize();

	for (int i = 0; i < bagSize; ++i) {
		Reference<MissionObject*> mission = missionBag->getContainerObject(i).castTo<MissionObject*>( );

		Locker locker(mission);

		//Clear mission type before calling mission generators.
		mission->setTypeCRC(0);

		if (i < 6) {
			randomizeGenericEntertainerMission(player, mission, Factions::FACTIONNEUTRAL, MissionTypes::DANCER);
		} else if (i < 12) {
			randomizeGenericEntertainerMission(player, mission, Factions::FACTIONNEUTRAL, MissionTypes::MUSICIAN);
		}

		if (slicer) {
			mission->setRewardCredits(mission->getRewardCredits() * 1.5);
		}

		float cityBonus = 1.f + player->getSkillMod("private_spec_missions") / 100.f;
		mission->setRewardCredits(mission->getRewardCredits() * cityBonus);

		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::randomizeScoutTerminalMissions(CreatureObject* player, int counter, bool slicer) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");
	int bagSize = missionBag->getContainerObjectsSize();

	for (int i = 0; i < bagSize; ++i) {
		Reference<MissionObject*> mission = missionBag->getContainerObject(i).castTo<MissionObject*>( );

		Locker locker(mission);

		//Clear mission type before calling mission generators.
		mission->setTypeCRC(0);

		if (i < 6) {
			randomizeGenericReconMission(player, mission, Factions::FACTIONNEUTRAL);
		} else if (i < 12) {
			randomizeGenericHuntingMission(player, mission, Factions::FACTIONNEUTRAL);
		}

		if (slicer) {
			mission->setRewardCredits(mission->getRewardCredits() * 1.5);
		}

		float cityBonus = 1.f + player->getSkillMod("private_spec_missions") / 100.f;
		mission->setRewardCredits(mission->getRewardCredits() * cityBonus);

		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::randomizeBountyTerminalMissions(CreatureObject* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");
	int bagSize = missionBag->getContainerObjectsSize();

	Vector<ManagedReference<PlayerBounty*>> potentialTargets = getPotentialPlayerBountyTargets(player);

	for (int i = 0; i < bagSize; ++i) {
		Reference<MissionObject*> mission = missionBag->getContainerObject(i).castTo<MissionObject*>( );

		Locker locker(mission);

		//Clear mission type before calling mission generators.
		mission->setTypeCRC(0);

		if (i < 10) {
			randomizeGenericBountyMission(player, mission, Factions::FACTIONNEUTRAL, &potentialTargets);
		}

		float cityBonus = 1.f + player->getSkillMod("private_spec_missions") / 100.f;
		mission->setRewardCredits(mission->getRewardCredits() * cityBonus);

		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::randomizeFactionTerminalMissions(CreatureObject* player, int counter, bool slicer, const uint32 faction) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");
	int bagSize = missionBag->getContainerObjectsSize();

	int numberOfCraftingMissions = 0;
	int numberOfReconMissions = 0;
	int numberOfDancerMissions = 0;
	int numberOfMusicianMissions = 0;

	for (int i = 0; i < bagSize; ++i) {
		Reference<MissionObject*> mission = missionBag->getContainerObject(i).castTo<MissionObject*>( );

		Locker locker(mission);

		//Clear mission type before calling mission generators.
		mission->setTypeCRC(0);

		if (i < 6) {
			randomizeGenericDestroyMission(player, mission, faction);
		} else if (i < 12) {
			randomizeGenericDeliverMission(player, mission, faction);
		} else {
			if (enableFactionalCraftingMissions && numberOfCraftingMissions < 6) {
				randomizeGenericCraftingMission(player, mission, faction);
				numberOfCraftingMissions++;
			} else if (enableFactionalReconMissions && numberOfReconMissions < 6) {
				randomizeGenericReconMission(player, mission, faction);
				numberOfReconMissions++;
			} else if (enableFactionalEntertainerMissions && numberOfDancerMissions < 6) {
				randomizeGenericEntertainerMission(player, mission, faction, MissionTypes::DANCER);
				numberOfDancerMissions++;
			} else if (enableFactionalEntertainerMissions && numberOfMusicianMissions < 6) {
				randomizeGenericEntertainerMission(player, mission, faction, MissionTypes::MUSICIAN);
				numberOfMusicianMissions++;
			}
		}

		if (slicer) {
			mission->setRewardCredits(mission->getRewardCredits() * 1.5);
		}

		float cityBonus = 1.f + player->getSkillMod("private_spec_missions") / 100.f;
		mission->setRewardCredits(mission->getRewardCredits() * cityBonus);

		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::randomizeGenericDestroyMission(CreatureObject* player, MissionObject* mission, const uint32 faction) {
	Zone* zone = player->getZone();

	if (zone == NULL) {
		return;
	}

	LairSpawn* randomLairSpawn = getRandomLairSpawn(player, faction, MissionTypes::DESTROY);

	if (randomLairSpawn == NULL) {
		return;
	}

	String lairTemplate = randomLairSpawn->getLairTemplateName();
	LairTemplate* lairTemplateObject = CreatureTemplateManager::instance()->getLairTemplate(lairTemplate.hashCode());

	if (lairTemplateObject == NULL) {
		return;
	}

	int playerLevel = server->getPlayerManager()->calculatePlayerLevel(player);
	int maxDiff = randomLairSpawn->getMaxDifficulty();
	int minDiff = randomLairSpawn->getMinDifficulty();
	int difficultyLevel = System::random(maxDiff - minDiff) + minDiff;
	int difficulty = (difficultyLevel - minDiff) / ((maxDiff > (minDiff + 5) ? maxDiff - minDiff : 5) / 5);

	if (difficulty == 5)
		difficulty = 4;

	int diffDisplay = difficultyLevel + 7;
	if (player->isGrouped())
		diffDisplay += player->getGroup()->getGroupLevel();
	else
		diffDisplay += playerLevel;

	String building = lairTemplateObject->getMissionBuilding(difficulty);

	if (building.isEmpty()) {
		return;
	}

	SharedObjectTemplate* templateObject = TemplateManager::instance()->getTemplate(building.hashCode());

	if (templateObject == NULL || !templateObject->isSharedTangibleObjectTemplate()) {
		error("incorrect template object in randomizeDestroyMission " + building);
		return;
	}

	NameManager* nm = processor->getNameManager();

	TerrainManager* terrain = zone->getPlanetManager()->getTerrainManager();

	Vector3 startPos;

	bool foundPosition = false;
	int maximumNumberOfTries = 20;
	while (!foundPosition && maximumNumberOfTries-- > 0) {
		foundPosition = true;

		startPos = player->getWorldCoordinate(System::random(1000) + 1000, (float)System::random(360), false);

		if (zone->isWithinBoundaries(startPos)) {
			float height = zone->getHeight(startPos.getX(), startPos.getY());
			float waterHeight = height * 2;
			bool result = terrain->getWaterHeight(startPos.getX(), startPos.getY(), waterHeight);

			if (!result || waterHeight <= height) {
				//Check that the position is outside cities.
				SortedVector<ManagedReference<ActiveArea* > > activeAreas;
				zone->getInRangeActiveAreas(startPos.getX(), startPos.getY(), &activeAreas, true);
				for (int i = 0; i < activeAreas.size(); ++i) {
					if (activeAreas.get(i)->isMunicipalZone()) {
						foundPosition = false;
					}
				}
			} else {
				foundPosition = false;
			}
		} else {
			foundPosition = false;
		}
	}

	if (!foundPosition) {
		return;
	}

	int randTexts = System::random(34) + 1;

	mission->setMissionNumber(randTexts);

	mission->setStartPosition(startPos.getX(), startPos.getY(), zone->getZoneName());
	mission->setCreatorName(nm->makeCreatureName());

	mission->setMissionTargetName("@lair_n:" + lairTemplateObject->getName());
	mission->setTargetTemplate(templateObject);
	mission->setTargetOptionalTemplate(lairTemplate);
	mission->setRewardCredits(System::random(diffDisplay * 15) + (difficultyLevel * 375));
	mission->setMissionDifficulty(difficultyLevel, diffDisplay, difficulty);
	mission->setSize(randomLairSpawn->getSize());
	mission->setFaction(faction);

	int factionPointsReward = randomLairSpawn->getMinDifficulty();
	if (factionPointsReward > 32)
	{
		factionPointsReward = 32;
	}

	String messageDifficulty;
	String missionType;

	if (difficulty < 2)
		messageDifficulty = "_easy";
	else if (difficulty == 2)
		messageDifficulty = "_medium";
	else
		messageDifficulty = "_hard";

	if (lairTemplateObject->getMobType() == LairTemplate::NPC)
		missionType = "_npc";
	else
		missionType = "_creature";

	mission->setMissionTitle("mission/mission_destroy_neutral" + messageDifficulty + missionType, "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_destroy_neutral" +  messageDifficulty + missionType, "m" + String::valueOf(randTexts) + "d");

	switch (faction) {
	case Factions::FACTIONIMPERIAL:
		mission->setRewardFactionPointsImperial(factionPointsReward * 2);
		mission->setRewardFactionPointsRebel(-factionPointsReward);
		generateRandomFactionalDestroyMissionDescription(player, mission, "imperial");
		break;
	case Factions::FACTIONREBEL:
		mission->setRewardFactionPointsImperial(-factionPointsReward);
		mission->setRewardFactionPointsRebel(factionPointsReward * 2);
		generateRandomFactionalDestroyMissionDescription(player, mission, "rebel");
		break;
	default:
		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(0);
		break;
	}

	mission->setTypeCRC(MissionTypes::DESTROY);
}

void MissionManagerImplementation::randomizeGenericSurveyMission(CreatureObject* player, MissionObject* mission, const uint32 faction) {
	int maxLevel = 50;
	int minLevel = 50;
	Zone* playerZone = player->getZone();

	if (playerZone == NULL)
		return;

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

	String zoneName = playerZone->getZoneName();

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

	mission->setMissionTargetName(spawn->getSurveyMissionSpawnFamilyName());
	mission->setTargetTemplate(templateObject);

	//Reward depending on mission level.
	mission->setRewardCredits(400 + (randLevel - minLevel) * 20 + System::random(100));

	mission->setFaction(faction);

	mission->setMissionDifficulty(randLevel);
	mission->setStartPosition(player->getPositionX(), player->getPositionY(), playerZone->getZoneName());
	mission->setMissionTitle("mission/mission_npc_survey_neutral_easy", "m" + String::valueOf(texts) + "t");
	mission->setMissionDescription("mission/mission_npc_survey_neutral_easy", "m" + String::valueOf(texts) + "o");
	mission->setCreatorName(nm->makeCreatureName());

	mission->setTypeCRC(MissionTypes::SURVEY);
}

void MissionManagerImplementation::randomizeGenericBountyMission(CreatureObject* player, MissionObject* mission, const uint32 faction, Vector<ManagedReference<PlayerBounty*>>* potentialTargets) {
	if (!player->hasSkill("combat_bountyhunter_novice")) {
		player->sendSystemMessage("@mission/mission_generic:not_bounty_hunter_terminal");
		return;
	}

	Zone* playerZone = player->getZone();

	if (playerZone == NULL) {
		return;
	}

	int level = 1;
	int randomTexts = 25;
	if (player->hasSkill("combat_bountyhunter_investigation_03")) {
		level = 3;
	} else if (player->hasSkill("combat_bountyhunter_investigation_01")) {
		level = 2;
		randomTexts = 50;
	}

	NameManager* nm = processor->getNameManager();

	bool playerTarget = false;
	int size = potentialTargets->size();

	if (level == 3 && size > 0) {
		int compareValue = size > 25 ? 25 : size < 5 ? 5 : size;
		if (System::random(100) < compareValue) {
			playerTarget = true;
			randomTexts = 6;
		}
	}

	mission->setStartPosition(player->getPositionX(), player->getPositionY(), playerZone->getZoneName());

	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(STRING_HASHCODE("object/tangible/mission/mission_bounty_target.iff")));

	mission->setMissionLevel(level);
	mission->setFaction(faction);

	if (playerTarget) {
		int index = System::random(size - 1);

		PlayerBounty* target = potentialTargets->get(index);

		potentialTargets->removeElementAt(index);

		if (target != NULL) {
			mission->setTargetObjectId(target->getTargetPlayerID());
			mission->setEndPosition(0, 0, "", true);
			mission->setTargetOptionalTemplate("");

			ManagedReference<CreatureObject*> creature = server->getObject(target->getTargetPlayerID()).castTo<CreatureObject*>();
			String name = "";

			if (creature != NULL) {
				name = creature->getFirstName() + " " + creature->getLastName();
				name = name.trim();
			}

			mission->setMissionTargetName(name);
			mission->setMissionDifficulty(75);
			mission->setRewardCredits(target->getReward());

			// Set the Title, Creator, and Description of the mission.

			int randTexts = 0;

			String stfFile = "mission/mission_bounty_jedi";

			UnicodeString numberOfEntries = StringIdManager::instance()->getStringId(String::hashCode("@" + stfFile  + ":" + "number_of_entries"));

			if (!numberOfEntries.isEmpty()) {
				randTexts = System::random(Integer::valueOf(numberOfEntries.toString()) - 1) + 1;
			} else {
				randTexts = (target->getTargetPlayerID() % randomTexts) + 1;
			}

			mission->setMissionNumber(randTexts);

			UnicodeString possibleCreatorName = StringIdManager::instance()->getStringId(String::hashCode("@" + stfFile + "m" + String::valueOf(randTexts) + "o"));
			String creatorName = "";


			if (!possibleCreatorName.isEmpty()) {
				creatorName = possibleCreatorName.toString();
			} else {
				creatorName = nm->makeCreatureName();
			}

			mission->setCreatorName(creatorName);
			mission->setMissionTitle(stfFile, "m" + String::valueOf(randTexts) + "t");
			mission->setMissionDescription(stfFile, "m" + String::valueOf(randTexts) + "d");
		}
	} else {
		mission->setMissionTargetName(nm->makeCreatureName());

		String planet = playerZone->getZoneName();
		if (level == 3 && bhTargetZones.size() > 0) {
			planet = getRandomBountyPlanet();
		}

		Vector3 endPos = getRandomBountyTargetPosition(player, planet);
		mission->setEndPosition(endPos.getX(), endPos.getY(), planet, true);

		String targetTemplate = bhTargetsAtMissionLevel.get((unsigned int)level).get(System::random(bhTargetsAtMissionLevel.get((unsigned int)level).size() - 1));
		mission->setTargetOptionalTemplate(targetTemplate);

		CreatureTemplate* creoTemplate = CreatureTemplateManager::instance()->getTemplate(mission->getTargetOptionalTemplate());

		int reward = 1000;
		int creoLevel = 1;

		if (creoTemplate != NULL) {
			creoLevel = creoTemplate->getLevel();
		}

		if (level == 1) {
			reward = creoLevel * (200 + System::random(200));
		} else if (level == 2) {
			reward = creoLevel * (250 + System::random(250));
		} else if (level == 3) {
			reward = creoLevel * (300 + System::random(300));
		}

		mission->setRewardCredits(reward);

		String diffString = "easy";

		if (level == 3) {
			diffString = "hard";
		} else if (level == 2) {
			diffString = "medium";
		}

		mission->setTargetObjectId(0);

		// Set the Title, Creator, and Description of the mission.

		int randTexts = 0;

		String stfFile = "mission/mission_bounty_neutral_";

		UnicodeString numberOfEntries = StringIdManager::instance()->getStringId(String::hashCode("@" + stfFile + diffString + ":" + "number_of_entries"));

		if (!numberOfEntries.isEmpty()) {
			randTexts =  System::random(Integer::valueOf(numberOfEntries.toString()) - 1) + 1;
		} else {
			randTexts = System::random(randomTexts - 1) + 1;
		}

		mission->setMissionNumber(randTexts);
		mission->setMissionDifficulty(3 * creoLevel + 7);

		UnicodeString possibleCreatorName = StringIdManager::instance()->getStringId(String::hashCode("@" + stfFile + diffString + ":" + "m" + String::valueOf(randTexts) + "o"));
		String creatorName = "";


		if (!possibleCreatorName.isEmpty()) {
			creatorName = possibleCreatorName.toString();
		} else {
			creatorName = nm->makeCreatureName();
		}

		mission->setCreatorName(creatorName);
		mission->setMissionTitle(stfFile + diffString, "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription(stfFile + diffString, "m" + String::valueOf(randTexts) + "d");
	}

	mission->setTypeCRC(MissionTypes::BOUNTY);
}

void MissionManagerImplementation::randomizeGenericDeliverMission(CreatureObject* player, MissionObject* mission, const uint32 faction) {
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

String MissionManagerImplementation::getDeliveryMissionFileName(const uint32 faction) {
	switch (faction) {
	case Factions::FACTIONIMPERIAL:
		return "mission/mission_deliver_imperial_easy";
	case Factions::FACTIONREBEL:
		return "mission/mission_deliver_rebel_easy";
	default:
		return "mission/mission_deliver_neutral_easy";
	}
}

int MissionManagerImplementation::getDeliverMissionNumberOfMissions(const uint32 faction) {
	switch (faction) {
	case Factions::FACTIONIMPERIAL:
		return 24;
	case Factions::FACTIONREBEL:
		return 24;
	default:
		return 29;
	}
}

int MissionManagerImplementation::getDeliverMissionSpawnType(const uint32 faction) {
	switch (faction) {
	case Factions::FACTIONIMPERIAL:
		return NpcSpawnPoint::IMPERIALSPAWN;
	case Factions::FACTIONREBEL:
		return NpcSpawnPoint::REBELSPAWN;
	default:
		return NpcSpawnPoint::NEUTRALSPAWN;
	}
}

bool MissionManagerImplementation::randomGenericDeliverMission(CreatureObject* player, MissionObject* mission, bool inTownMission, const uint32 faction) {
	//Get the current planet and position of the player.
	ManagedReference<Zone*> zone = player->getZone();

	if (zone == NULL)
		return false;

	String planetName = zone->getZoneName();

	Vector3 playerPosition = player->getWorldPosition();
	playerPosition.setZ(0);
	Vector3* startPosition = &playerPosition;

	//Lock spawn point map for the search.
	Locker missionSpawnLocker(&missionNpcSpawnMap);

	//Find a spawn point in current city.
	float minDistance = 10.0f;
	float maxDistance = 300.0f;
	Reference<NpcSpawnPoint*> startNpc = missionNpcSpawnMap.getRandomNpcSpawnPoint(planetName.hashCode(), startPosition, getDeliverMissionSpawnType(faction), minDistance, maxDistance);

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
	minDistance = 15.0f;
	maxDistance = 1500.0f;

	Reference<NpcSpawnPoint*> endNpc;
	int retries = 10;
	while ((endNpc == NULL || endNpc == startNpc) && (retries > 0)) {
		endNpc = missionNpcSpawnMap.getRandomNpcSpawnPoint(planetName.hashCode(), endPosition, getDeliverMissionSpawnType(faction), minDistance, maxDistance);
		retries--;
	}

	if (endNpc == NULL || endNpc == startNpc) {
		//Couldn't find a suitable spawn point.
		return false;
	}

	//Randomize mission description strings/delivery object.
	int randomTexts = System::random(getDeliverMissionNumberOfMissions(faction)) + 1;

	//Setup mission object.
	mission->setMissionNumber(randomTexts);

	NameManager* nm = processor->getNameManager();
	mission->setCreatorName(nm->makeCreatureName());
	mission->setMissionTargetName(TemplateManager::instance()->getTemplate(STRING_HASHCODE("object/tangible/mission/mission_datadisk.iff"))->getObjectName());

	String planet = zone->getZoneName();
	mission->setStartPosition(startNpc->getPosition()->getX(), startNpc->getPosition()->getY(), planet, true);
	mission->setEndPosition(endNpc->getPosition()->getX(), endNpc->getPosition()->getY(), planet);

	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(STRING_HASHCODE("object/tangible/mission/mission_datadisk.iff")));

	int baseCredits = 40;
	int deliverDistanceCredits = (playerPosition.distanceTo(*(startNpc->getPosition())) + startNpc->getPosition()->distanceTo(*(endNpc->getPosition()))) / 10;

	mission->setRewardCredits(baseCredits + deliverDistanceCredits);

	switch (faction) {
	case Factions::FACTIONIMPERIAL:
		mission->setRewardFactionPointsImperial(5);
		mission->setRewardFactionPointsRebel(0);
		break;
	case Factions::FACTIONREBEL:
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

	mission->setTypeCRC(MissionTypes::DELIVER);
	mission->setFaction(faction);

	return true;
}

NpcSpawnPoint* MissionManagerImplementation::getFreeNpcSpawnPoint(unsigned const int planetCRC, const float x, const float y, const int spawnType) {
	Locker missionSpawnLocker(&missionNpcSpawnMap);

	Vector3 pos(x, y, 0);

	//First try for an exact match
	Reference<NpcSpawnPoint* > npc = missionNpcSpawnMap.findSpawnAt(planetCRC, &pos);

	if (npc != NULL && npc->getInUse() == 0) {
		return npc;
	}

	//Next try to find a free NPC spawn point in a circle with a radius of max.
	float min = 0.0f;
	float max = 50.0f;

	while (max <= 1600.0f) {
		npc = missionNpcSpawnMap.getRandomNpcSpawnPoint(planetCRC, &pos, spawnType, min, max);
		if (npc != NULL && npc->getInUse() == 0) {
			return npc;
		} else {
			//No free NPC spawn point found, double the search area radius.
			max *= 2;
		}
	}

	//Couldn't find any free NPC spawn point.
	return NULL;
}

void MissionManagerImplementation::randomizeGenericCraftingMission(CreatureObject* player, MissionObject* mission, const uint32 faction) {
	//Create a random neutral delivery mission that can be modified.
	randomizeGenericDeliverMission(player, mission, faction);

	if (mission->getTypeCRC() != MissionTypes::DELIVER) {
		//Failed to create mission.
		return;
	}

	//Modify the delivery mission to be a crafting mission.
	int maximumMissionNumber;
	String fileName = "";

	switch (faction) {
	case Factions::FACTIONIMPERIAL:
		maximumMissionNumber = 34;
		fileName = "mission/mission_npc_crafting_imperial_easy";
		break;
	case Factions::FACTIONREBEL:
		maximumMissionNumber = 34;
		fileName = "mission/mission_npc_crafting_rebel_easy";
		break;
	default:
		maximumMissionNumber = 49;
		fileName = "mission/mission_npc_crafting_neutral_easy";
		break;
	}

	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(STRING_HASHCODE("object/tangible/mission/quest_item/attunement_grid.iff")));

	int missionNumber = System::random(maximumMissionNumber) + 1;
	mission->setMissionTitle(fileName, "m" + String::valueOf(missionNumber) + "t");
	mission->setMissionDescription(fileName, "m" + String::valueOf(missionNumber) + "d");

	mission->setTypeCRC(MissionTypes::CRAFTING);
}

void MissionManagerImplementation::randomizeGenericEntertainerMission(CreatureObject* player, MissionObject* mission, const uint32 faction, const uint32 missionType) {
	//Generate difficulty for mission. How far away missions can be.
	int difficulty = 2;

	int randomRange = System::random(difficulty - 1) + 1;

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	PlanetManager* pmng = zone->getPlanetManager();
	MissionTargetMap* performanceLocations = pmng->getPerformanceLocations();
	if (performanceLocations->size() <= 0) {
		return;
	}

	SceneObject* target = performanceLocations->getRandomTarget(player, randomRange);
	if (target == NULL || !target->isStructureObject()) {
		return;
	}

	NameManager* nm = processor->getNameManager();

	String missionString = "musician";
	if (missionType == MissionTypes::DANCER) {
		missionString = "dancer";
	}

	int numberOfMissions = 49;
	if (faction != Factions::FACTIONNEUTRAL) {
		numberOfMissions = 34;
	}
	int randTexts = System::random(numberOfMissions) + 1;

	mission->setMissionNumber(randTexts);
	mission->setCreatorName(nm->makeCreatureName());

	mission->setStartPosition(target->getPositionX(), target->getPositionY(), zone->getZoneName());

	if (missionType == MissionTypes::DANCER) {
		mission->setMissionTargetName("@ui_mission:dancer_tab");
	} else {
		mission->setMissionTargetName("@ui_mission:musician_tab");
	}

	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(STRING_HASHCODE("object/building/general/mun_all_guild_theater_s01.iff")));

	int distanceReward = player->getWorldPosition().distanceTo(target->getPosition()) / 10;

	mission->setRewardCredits(100 + distanceReward + System::random(100));

	mission->setFaction(faction);

	switch (faction) {
	case Factions::FACTIONIMPERIAL:
		mission->setRewardFactionPointsImperial(5);
		mission->setRewardFactionPointsRebel(0);
		mission->setMissionTitle("mission/mission_npc_" + missionString + "_imperial_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_" + missionString + "_imperial_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	case Factions::FACTIONREBEL:
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

void MissionManagerImplementation::randomizeGenericHuntingMission(CreatureObject* player, MissionObject* mission, const uint32 faction) {
	LairSpawn* randomLairSpawn = getRandomLairSpawn(player, Factions::FACTIONNEUTRAL, MissionTypes::HUNTING);

	if (randomLairSpawn == NULL) {
		return;
	}

	Zone* playerZone = player->getZone();

	if (playerZone == NULL) {
		return;
	}

	LairTemplate* lairTemplate = CreatureTemplateManager::instance()->getLairTemplate(randomLairSpawn->getLairTemplateName().hashCode());

	if (lairTemplate == NULL) {
		return;
	}

	VectorMap<String, int>* mobiles = lairTemplate->getMobiles();

	if (mobiles->size() == 0) {
		return;
	}

	String mobileName = mobiles->elementAt(0).getKey();

	CreatureTemplate* creatureTemplate = CreatureTemplateManager::instance()->getTemplate(mobileName);

	if (creatureTemplate == NULL) {
		return;
	}

	Vector<String>& templatesNames = creatureTemplate->getTemplates();

	if (templatesNames.size() == 0) {
		return;
	}

	const String& serverTemplate = templatesNames.get(0);

	SharedObjectTemplate* sharedTemplate = TemplateManager::instance()->getTemplate(serverTemplate.hashCode());

	if (sharedTemplate == NULL) {
		return;
	}

	mission->setTemplateStrings(mobileName, mobileName);

	NameManager* nm = processor->getNameManager();

	int randTexts = System::random(7) + 1;

	String creatorName = nm->makeCreatureName();

	//info("creator name " + creatorName, true);

	mission->setMissionNumber(randTexts);
	mission->setCreatorName(creatorName);

	mission->setStartPosition(player->getPositionX(), player->getPositionY(), playerZone->getZoneName());

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

	int baseReward = 500 + (difficulty * 100 * randomLairSpawn->getMinDifficulty());
	mission->setRewardCredits(baseReward + System::random(100));
	mission->setMissionDifficulty(difficulty);
	mission->setMissionTitle("mission/mission_npc_hunting_neutral_" + diffString, "m" + String::valueOf(randTexts) + "t");
	mission->setMissionDescription("mission/mission_npc_hunting_neutral_" + diffString, "m" + String::valueOf(randTexts) + "o");

	mission->setTypeCRC(MissionTypes::HUNTING);
	mission->setFaction(faction);
}

void MissionManagerImplementation::randomizeGenericReconMission(CreatureObject* player, MissionObject* mission, const uint32 faction) {
	bool foundPosition = false;
	Vector3 position;

	Zone* playerZone = player->getZone();

	if (playerZone == NULL) {
		return;
	}

	int maximumNumberOfTries = 20;
	while (!foundPosition && maximumNumberOfTries-- > 0) {
		position = player->getWorldCoordinate(System::random(3000) + 1000, (float)System::random(360), false);

		//Check if it is a position where you can build and away from any travel points.
		if (playerZone->getPlanetManager()->isBuildingPermittedAt(position.getX(), position.getY(), NULL)) {
			Reference<PlanetTravelPoint*> travelPoint = playerZone->getPlanetManager()->getNearestPlanetTravelPoint(position);

			if (travelPoint != NULL && travelPoint->getArrivalPosition().distanceTo(position) > 1000.0f) {
				foundPosition = true;
			}
		}
	}

	if (!foundPosition) {
		return;
	}

	NameManager* nm = processor->getNameManager();


	mission->setCreatorName(nm->makeCreatureName());

	mission->setMissionTargetName(TemplateManager::instance()->getTemplate(STRING_HASHCODE("object/tangible/mission/mission_recon_target.iff"))->getObjectName());
	mission->setTargetTemplate(TemplateManager::instance()->getTemplate(STRING_HASHCODE("object/tangible/mission/mission_recon_target.iff")));

	mission->setStartPosition(position.getX(), position.getY(), playerZone->getZoneName());

	int reward = position.distanceTo(player->getWorldPosition()) / 5;

	mission->setRewardCredits(50 + reward);

	switch (faction) {
	case Factions::FACTIONIMPERIAL:
	{
		int randTexts = System::random(48)+1; // There are actually 50 imperial recon missions including bugged m19
		if (randTexts >= 19)
			  randTexts++;

		mission->setMissionNumber(randTexts);
          
		mission->setRewardFactionPointsImperial(10);
		mission->setRewardFactionPointsRebel(0);
		mission->setMissionTitle("mission/mission_npc_recon_imperial_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_recon_imperial_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	}
	case Factions::FACTIONREBEL:
	{
		int randTexts = System::random(49) + 1;
		mission->setMissionNumber(randTexts);

		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(10);
		mission->setMissionTitle("mission/mission_npc_recon_rebel_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_recon_rebel_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	}
	default:
	{
		int randTexts = System::random(24) + 1;
		mission->setMissionNumber(randTexts);

		mission->setRewardFactionPointsImperial(0);
		mission->setRewardFactionPointsRebel(0);
		mission->setMissionTitle("mission/mission_npc_recon_neutral_easy", "m" + String::valueOf(randTexts) + "t");
		mission->setMissionDescription("mission/mission_npc_recon_neutral_easy", "m" + String::valueOf(randTexts) + "o");
		break;
	}
	}

	mission->setMissionDifficulty(1);

	mission->setFaction(faction);

	mission->setTypeCRC(MissionTypes::RECON);
}

void MissionManagerImplementation::generateRandomFactionalDestroyMissionDescription(CreatureObject* player, MissionObject* mission, const String& faction) {
	String difficultyString = faction;
	int randomMax;

	if (player->getFaction() == Factions::FACTIONIMPERIAL || player->getFaction() == Factions::FACTIONREBEL) {
		if (player->getFactionStatus() == FactionStatus::OVERT || player->getFactionStatus() == FactionStatus::COVERT) {
			difficultyString += "_military";
			randomMax = 49;
		} else {
			difficultyString += "_non_military";
			randomMax = 12;
		}
	} else {
		difficultyString += "_non_military";
		randomMax = 12;
	}

	int difficulty = mission->getDifficultyLevel();

	if (difficulty < 20) {
		difficultyString += "_easy";
	} else if (difficulty < 40) {
		difficultyString += "_medium";
		randomMax = 49;
	} else {
		difficultyString += "_hard";
		randomMax = (randomMax < 50) ? 25 : 50;
	}

	int randomNumber = System::random(randomMax) + 1;

	mission->setMissionTitle("mission/mission_destroy_" + difficultyString, "m" + String::valueOf(randomNumber) + "t");
	mission->setMissionDescription("mission/mission_destroy_" +  difficultyString, "m" + String::valueOf(randomNumber) + "d");
}

void MissionManagerImplementation::createSpawnPoint(CreatureObject* player, const String& spawnTypes) {
	if (player == NULL) {
		return;
	}

	if (player->getParentID() != 0 || spawnTypes == "") {
		//player->sendSystemMessage("Mission NPC spawns cannot be placed inside buildings.");
		String text = "Player position = " + player->getPosition().toString() + ", direction = " + String::valueOf(player->getDirection()->getRadians()) + ", cell id = " + String::valueOf(player->getParentID());
		player->sendSystemMessage(text);
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

LairSpawn* MissionManagerImplementation::getRandomLairSpawn(CreatureObject* player, const uint32 faction, unsigned int type) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return NULL;

	Vector<Reference<LairSpawn*> >* availableLairList = NULL;
	int minLevelCeiling = 20;

	if (type == MissionTypes::DESTROY) {
		String missionGroup;

		if (faction == Factions::FACTIONNEUTRAL) {
			missionGroup = zone->getZoneName() + "_destroy_missions";
		} else {
			bool neutralMission = true;

			if (player->getFaction() != 0 && player->getFaction() == faction) {
				if (player->getFactionStatus() == FactionStatus::OVERT || player->getFactionStatus() == FactionStatus::COVERT) {
					neutralMission = false;
				}
			}

			if (neutralMission) {
				missionGroup = "factional_neutral_destroy_missions";
			} else if (faction == Factions::FACTIONIMPERIAL) {
				missionGroup = "factional_imperial_destroy_missions";
			} else {
				missionGroup = "factional_rebel_destroy_missions";
			}
		}

		SpawnGroup* destroyMissionGroup = CreatureTemplateManager::instance()->getDestroyMissionGroup(missionGroup.hashCode());

		if (destroyMissionGroup == NULL) {
			return NULL;
		}

		availableLairList = destroyMissionGroup->getSpawnList();
		minLevelCeiling = destroyMissionGroup->getMinLevelCeiling();

	} else if (type == MissionTypes::HUNTING) {
		CreatureManager* creatureManager = zone->getCreatureManager();
		Vector<ManagedReference<SpawnArea* > >* worldAreas = creatureManager->getWorldSpawnAreas();

		ManagedReference<SpawnArea*> spawnArea = NULL;

		if (worldAreas == NULL || worldAreas->size() == 0) {
			return NULL;
		}

		int rand = System::random(worldAreas->size() - 1);

		spawnArea = worldAreas->get(rand);

		if (spawnArea == NULL) {
			return NULL;
		}

		availableLairList = spawnArea->getSpawnList();
	}

	if (availableLairList == NULL || availableLairList->size() == 0) {
		return NULL;
	}

	bool foundLair = false;
	int counter = availableLairList->size();
	int playerLevel = server->getPlayerManager()->calculatePlayerLevel(player);
	if (player->isGrouped())
		playerLevel = player->getGroup()->getGroupLevel();

	LairSpawn* lairSpawn = NULL;

	//Cap the minLevel to prevent a group from being too high to get missions on a planet
	int minLevel = Math::min(playerLevel - 5, minLevelCeiling);

	//Try to pick random lair within playerLevel +-5;
	while (counter > 0 && !foundLair) {
		LairSpawn* randomLairSpawn = availableLairList->get(System::random(availableLairList->size() - 1));
		if (randomLairSpawn != NULL) {
			if (randomLairSpawn->getMinDifficulty() <= (playerLevel + 5) && randomLairSpawn->getMaxDifficulty() >= minLevel) {
				if (type == MissionTypes::DESTROY) {
					lairSpawn = randomLairSpawn;
					foundLair = true;
				} else {
					LairTemplate* lairTemp = CreatureTemplateManager::instance()->getLairTemplate(randomLairSpawn->getLairTemplateName().hashCode());

					if (lairTemp->getMobType() == LairTemplate::CREATURE) {
						lairSpawn = randomLairSpawn;
						foundLair = true;
					}
				}
			}
		}

		--counter;
	}

	if (!foundLair) {
		//No random lair found, iterate through all lairs and find the first within playerLevel +-5;
		for (int i = 0; i < availableLairList->size(); i++) {
			LairSpawn* randomLairSpawn = availableLairList->get(i);
			if (randomLairSpawn->getMinDifficulty() <= (playerLevel + 5) && randomLairSpawn->getMaxDifficulty() >= minLevel) {
				if (type == MissionTypes::DESTROY) {
					lairSpawn = randomLairSpawn;
					foundLair = true;
					break;
				} else {
					LairTemplate* lairTemp = CreatureTemplateManager::instance()->getLairTemplate(randomLairSpawn->getLairTemplateName().hashCode());

					if (lairTemp->getMobType() == LairTemplate::CREATURE) {
						lairSpawn = randomLairSpawn;
						foundLair = true;
						break;
					}
				}
			}
		}
	}

	if (!foundLair) {
		//There are no lairs within playerLevel +-5, pick the first lair below playerLevel +5
		for (int i = 0; i < availableLairList->size(); i++) {
			LairSpawn* randomLairSpawn = availableLairList->get(i);
			if (randomLairSpawn->getMinDifficulty() <= (playerLevel + 5)) {
				if (type == MissionTypes::DESTROY) {
					lairSpawn = randomLairSpawn;
					break;
				} else {
					LairTemplate* lairTemp = CreatureTemplateManager::instance()->getLairTemplate(randomLairSpawn->getLairTemplateName().hashCode());

					if (lairTemp->getMobType() == LairTemplate::CREATURE) {
						lairSpawn = randomLairSpawn;
						break;
					}
				}
			}
		}
	}

	return lairSpawn;
}

Vector3 MissionManagerImplementation::getRandomBountyTargetPosition(CreatureObject* player, const String& planet) {
	Vector3 position;

	// Use the zone the target is on.

	Zone* targetZone = server->getZone(planet);

	if (targetZone == NULL) {
		return position;
	}

	bool found = false;
	float minX = targetZone->getMinX(), maxX = targetZone->getMaxX();
	float minY = targetZone->getMinY(), maxY = targetZone->getMaxY();
	float diameterX = maxX - minX;
	float diameterY = maxY - minY;
	int retries = 20;

	while (!found && retries > 0) {
		position.setX(System::random(diameterX) + minX);
		position.setY(System::random(diameterY) + minY);

		found = targetZone->getPlanetManager()->isBuildingPermittedAt(position.getX(), position.getY(), NULL);

		retries--;
	}

	if (retries == 0) {
		position.set(0, 0, 0);
	}

	return position;
}

Reference<MissionObject*> MissionManagerImplementation::getBountyHunterMission(CreatureObject* player) {
	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad != NULL) {
		VectorMap<uint64, ManagedReference<SceneObject*> > objects;
		datapad->getContainerObjects(objects);

		for (int i = 0; i < objects.size(); i++) {
			if (objects.get(i)->isMissionObject()) {
				Reference<MissionObject*> mission = objects.get(i).castTo<MissionObject*>();

				if (mission != NULL && mission->getTypeCRC() == MissionTypes::BOUNTY) {
					return mission;
				}
			}
		}
	}

	return NULL;
}

void MissionManagerImplementation::addPlayerToBountyList(uint64 targetId, int reward) {
	Locker listLocker(&playerBountyListMutex);

	if (!playerBountyList.contains(targetId)) {
		PlayerBounty* bounty = new PlayerBounty(targetId, reward);
		ObjectManager::instance()->persistObject(bounty, 1, "playerbounties");
		playerBountyList.put(targetId, bounty);

		info("Adding player " + String::valueOf(targetId) + " to bounty hunter list.", true);
	}
}

void MissionManagerImplementation::removePlayerFromBountyList(uint64 targetId) {
	Locker listLocker(&playerBountyListMutex);

	if (playerBountyList.contains(targetId)) {

		PlayerBounty* target = playerBountyList.get(targetId);

		playerBountyList.remove(playerBountyList.find(targetId));

		SortedVector<uint64>* bountyHunters = target->getBountyHunters();

		for (int i = 0; i < bountyHunters->size(); i++) {
			failPlayerBountyMission(bountyHunters->get(i));
		}

		ObjectManager::instance()->destroyObjectFromDatabase(target->_getObjectID());
		info("Removing player " + String::valueOf(targetId) + " from bounty hunter list.", true);
	}
}

void MissionManagerImplementation::updatePlayerBountyReward(uint64 targetId, int reward) {
	Locker listLocker(&playerBountyListMutex);

	if (playerBountyList.contains(targetId)) {
		playerBountyList.get(targetId)->setReward(reward);
	}
}

void MissionManagerImplementation::updatePlayerBountyOnlineStatus(uint64 targetId, bool status) {
	Locker listLocker(&playerBountyListMutex);

	if (playerBountyList.contains(targetId)) {
		playerBountyList.get(targetId)->setOnline(status);

		if (status)
			info("Player jedi is now online: " + String::valueOf(targetId), true);
		else
			info("Player jedi is now offline: " + String::valueOf(targetId), true);
	}
}

void MissionManagerImplementation::addBountyHunterToPlayerBounty(uint64 targetId, uint64 bountyHunterId) {
	Locker listLocker(&playerBountyListMutex);

	playerBountyList.get(targetId)->addBountyHunter(bountyHunterId);
}

void MissionManagerImplementation::removeBountyHunterFromPlayerBounty(uint64 targetId, uint64 bountyHunterId) {
	Locker listLocker(&playerBountyListMutex);

	if (playerBountyList.contains(targetId)) {
		playerBountyList.get(targetId)->removeBountyHunter(bountyHunterId);
	}
}

Vector<ManagedReference<PlayerBounty*>> MissionManagerImplementation::getPotentialPlayerBountyTargets(CreatureObject* player) {
	Locker listLocker(&playerBountyListMutex);

	Vector<ManagedReference<PlayerBounty*>> potentialTargets;

	for (int i = 0; i < playerBountyList.size(); i++) {
		PlayerBounty* playerBounty = playerBountyList.get(i);

		if (isBountyValidForPlayer(player, playerBounty))
			potentialTargets.add(playerBounty);
	}

	return potentialTargets;
}

bool MissionManagerImplementation::isBountyValidForPlayer(CreatureObject* player, PlayerBounty* bounty) {
	if (!bounty->isOnline())
		return false;

	if (bounty->numberOfActiveMissions() >= 5)
		return false;

	uint64 targetId = bounty->getTargetPlayerID();
	uint64 playerId = player->getObjectID();

	if (targetId == playerId)
		return false;

	ManagedReference<CreatureObject*> creature = server->getObject(targetId).castTo<CreatureObject*>();

	if (creature == NULL)
		return false;

	auto targetGhost = creature->getPlayerObject();
	float terminalVisibilityThreshold = VisibilityManager::instance()->getTerminalVisThreshold();

	if (targetGhost == NULL || targetGhost->getVisibility() < terminalVisibilityThreshold)
		return false;

	auto playerGhost = player->getPlayerObject();

	if (playerGhost == NULL)
		return false;

	uint64 accountId = playerGhost->getAccountID();

	if (!enableSameAccountBountyMissions && targetGhost->getAccountID() == accountId)
		return false;

	auto hunters = bounty->getBountyHunters();

	for (int j = 0; j < hunters->size(); j++) {
		ManagedReference<CreatureObject*> hunter = server->getObject(hunters->get(j)).castTo<CreatureObject*>();

		if (hunter != NULL) {
			auto hunterGhost = hunter->getPlayerObject();

			if (hunterGhost != NULL && hunterGhost->getAccountID() == accountId)
				return false;
		}
	}

	return true;
}

void MissionManagerImplementation::completePlayerBounty(uint64 targetId, uint64 bountyHunter) {
	Locker listLocker(&playerBountyListMutex);

	if (playerBountyList.contains(targetId)) {
		PlayerBounty* target = playerBountyList.get(targetId);

		Vector<uint64> activeBountyHunters;

		for (int i = 0; i < target->getBountyHunters()->size(); i++)
			activeBountyHunters.add(target->getBountyHunters()->get(i));

		auto bhSize = activeBountyHunters.size();

		for (int i = 0; i < bhSize; i++) {
			if (activeBountyHunters.get(i) != bountyHunter) {
				//Fail mission.
				failPlayerBountyMission(activeBountyHunters.get(i));
			} else {
				ManagedReference<CreatureObject*> creo = server->getObject(activeBountyHunters.get(i)).castTo<CreatureObject*>();
				auto ghost = creo->getPlayerObject();
				if (ghost != NULL)
					ghost->schedulePvpTefRemovalTask(false, true);
			}
		}
	}
}

void MissionManagerImplementation::failPlayerBountyMission(uint64 bountyHunter) {
	ManagedReference<CreatureObject*> creature = server->getObject(bountyHunter).castTo<CreatureObject*>();

	if (creature != NULL) {
		Locker creatureLock(creature);

		Reference<MissionObject*> mission = getBountyHunterMission(creature);

		if (mission != NULL) {
			ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

			if (objective != NULL) {
				ManagedReference<CreatureObject*> player = objective->getPlayerOwner();

				if (player != NULL) {
					player->sendSystemMessage("@mission/mission_generic:failed");

					auto ghost = player->getPlayerObject();
					if (ghost != NULL)
						ghost->schedulePvpTefRemovalTask(false, true);
				}

				objective->fail();
			}
		}
	}
}

Vector<uint64>* MissionManagerImplementation::getHuntersHuntingTarget(uint64 targetId) {
	Locker listLocker(&playerBountyListMutex);

	PlayerBounty* list = playerBountyList.get(targetId);

	if (list != NULL)
		return list->getBountyHunters();

	return NULL;
}

void MissionManagerImplementation::allocateMissionNpcs(NpcSpawnPoint* target, NpcSpawnPoint* destination, TerrainManager* terrainManager, CreatureManager* creatureManager) {
	//Lock mission spawn points.
	Locker missionSpawnLocker(&missionNpcSpawnMap);

	target->allocateNpc(terrainManager, creatureManager);
	destination->allocateNpc(terrainManager, creatureManager);
}

void MissionManagerImplementation::freeMissionNpc(AiAgent* npc) {
	//Lock mission spawn points.
	Locker missionSpawnLocker(&missionNpcSpawnMap);
	Vector3 pos = npc->getPosition();
	pos.setZ(0);
	NpcSpawnPoint* point = missionNpcSpawnMap.findSpawnAt(npc->getPlanetCRC(), &pos);

	if (point != NULL)
		point->freeNpc(_this.getReferenceUnsafeStaticCast());
}

void MissionManagerImplementation::despawnMissionNpc(NpcSpawnPoint* npc) {
	//Lock mission spawn points.
	if (npc == NULL)
		return;

	Locker missionSpawnLocker(&missionNpcSpawnMap);
	npc->despawnNpc();
}

void MissionManagerImplementation::deactivateMissions(CreatureObject* player) {
	if (player == NULL) {
		return;
	}

	SceneObject* datapad = player->getSlottedObject("datapad");

	if (datapad == NULL) {
		return;
	}

	int datapadSize = datapad->getContainerObjectsSize();

	for (int i = datapadSize - 1; i >= 0; --i) {
		if (datapad->getContainerObject(i)->isMissionObject()) {
			Reference<MissionObject*> mission = datapad->getContainerObject(i).castTo<MissionObject*>();

			if (mission != NULL) {
				//Check if it is target or destination NPC
				MissionObjective* objective = mission->getMissionObjective();
				if (objective != NULL) {
					Locker locker(objective);
					objective->deactivate();
				}
			}
		}
	}
}

String MissionManagerImplementation::getRandomBountyPlanet() {
	int randomNumber = System::random(bhTargetZones.size() - 1);
	return bhTargetZones.get(randomNumber);
}

bool MissionManagerImplementation::sendPlayerBountyDebug(CreatureObject* creature, CreatureObject* target) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return false;

	ManagedReference<PlayerObject*> targetGhost = target->getPlayerObject();

	if (targetGhost == NULL)
		return false;

	Locker listLocker(&playerBountyListMutex);

	PlayerBounty* playerBounty = playerBountyList.get(target->getObjectID());

	ManagedReference<SuiListBox*> box = new SuiListBox(creature, 0);
	box->setPromptTitle("Jedi Visibility");
	String promptText = "Player: " + target->getFirstName() + "\n" + "Visibility: " + String::valueOf(targetGhost->getVisibility()) + "\n";

	if (playerBounty == NULL) {
		promptText += "-- No player bounty data --\n";
	} else {
		promptText += "-- Bounty Data --\n";
		promptText += "Reward: " + String::valueOf(playerBounty->getReward()) + "\n";
		String onlineStatus = playerBounty->isOnline() ? "True" : "False";
		promptText += "Online Status: " + onlineStatus + "\n";
		int activeCount = playerBounty->numberOfActiveMissions();
		promptText += "Active Bounty Count: " + String::valueOf(activeCount) + "\n";
		if (activeCount > 0) {
			promptText += "\nPlayers holding active bounties:";
			ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();

			SortedVector<uint64>* bountyHunters = playerBounty->getBountyHunters();

			for (int i = 0; i < bountyHunters->size(); i++) {
				String name = playerManager->getPlayerName(bountyHunters->get(i));

				if (name.isEmpty())
					box->addMenuItem("Unknown player");
				else
					box->addMenuItem(name);
			}
		}
	}

	box->setPromptText(promptText);
	box->setUsingObject(target);
	box->setForceCloseDisabled();
	ghost->addSuiBox(box);
	creature->sendMessage(box->generateMessage());

	return true;
}
