#include "server/zone/managers/frs/FrsManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/frs/RankMaintenanceTask.h"
#include "server/zone/managers/frs/VoteStatusTask.h"
#include "server/zone/managers/frs/FrsRankingData.h"
#include "server/zone/managers/frs/FrsManagerData.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/variables/FrsData.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/EnclaveVotingTerminalSuiCallback.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/managers/player/PlayerMap.h"

void FrsManagerImplementation::initialize() {
	auto zoneServer = this->zoneServer.get();

	loadLuaConfig();

	if (!frsEnabled)
		return;

	Zone* zone = zoneServer->getZone("yavin4");

	if (zone == nullptr) {
		error("Unable to initialize frs manager, yavin4 disabled.");
		frsEnabled = false;
		return;
	}

	setupEnclaves();
	loadFrsData();

	Locker locker(managerData);

	wipeArenaChallenges();

	uint64 lastTick = managerData->getLastMaintenanceTick();
	uint64 miliDiff = Time().getMiliTime() - lastTick;

	rankMaintenanceTask = new RankMaintenanceTask(_this.getReferenceUnsafeStaticCast());

	if (miliDiff >= maintenanceInterval)
		rankMaintenanceTask->execute();
	else
		rankMaintenanceTask->schedule(maintenanceInterval - miliDiff);

	lastTick = managerData->getLastVoteStatusTick();
	miliDiff = Time().getMiliTime() - lastTick;

	voteStatusTask = new VoteStatusTask(_this.getReferenceUnsafeStaticCast());

	if (miliDiff >= VOTE_STATUS_TICK)
		voteStatusTask->execute();
	else
		voteStatusTask->schedule(VOTE_STATUS_TICK - miliDiff);
}

void FrsManagerImplementation::cancelTasks() {
	if (voteStatusTask) {
		voteStatusTask->cancel();
	}

	if (rankMaintenanceTask) {
		rankMaintenanceTask->cancel();
	}
}

void FrsManagerImplementation::loadFrsData() {
	info("Loading frs manager data from frsmanager.db");

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* rankDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("frsmanager", true);

	if (rankDatabase == nullptr) {
		error("Could not load the frsmanager database.");
		return;
	}

	try {
		ObjectDatabaseIterator iterator(rankDatabase);

		uint64 objectID;

		while (iterator.getNextKey(objectID)) {
			Reference<FrsManagerData*> manData = Core::getObjectBroker()->lookUp(objectID).castTo<FrsManagerData*>();

			if (manData != nullptr) {
				managerData = manData;
			}
		}
	} catch (DatabaseException& e) {
		error("Database exception in FrsManagerImplementation::loadFrsData(): "	+ e.getMessage());
	}

	if (managerData == nullptr) {
		FrsManagerData* newManagerData = new FrsManagerData();
		ObjectManager::instance()->persistObject(newManagerData, 1, "frsmanager");

		managerData = newManagerData;
	}

	Locker locker(managerData);

	Vector<ManagedReference<FrsRank*> >* rankData = managerData->getLightRanks();

	if (rankData->size() == 0) {
		short newStatus = VOTING_CLOSED;

		for (int i = 1; i <= 11; i++) {
			ManagedReference<FrsRank*> newRank = new FrsRank(COUNCIL_LIGHT, i, newStatus);
			ObjectManager::instance()->persistObject(newRank, 1, "frsdata");
			rankData->add(newRank);
		}
	}

	rankData = managerData->getDarkRanks();

	if (rankData->size() == 0) {
		Vector<ManagedReference<FrsRank*> >* newRankData = nullptr;
		short newStatus = VOTING_CLOSED;

		for (int i = 1; i <= 11; i++) {
			ManagedReference<FrsRank*> newRank = new FrsRank(COUNCIL_DARK, i, newStatus);
			ObjectManager::instance()->persistObject(newRank, 1, "frsdata");
			rankData->add(newRank);
		}
	}
}

void FrsManagerImplementation::loadLuaConfig() {
	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/jedi/frs_manager.lua")) {
		error("Unable to load FrsManager data.");
		delete lua;
		return;
	}

	auto zoneServer = this->zoneServer.get();

	frsEnabled = lua->getGlobalInt("frsEnabled");
	petitionInterval = lua->getGlobalLong("petitionInterval");
	votingInterval = lua->getGlobalLong("votingInterval");
	acceptanceInterval = lua->getGlobalLong("acceptanceInterval");
	maintenanceInterval = lua->getGlobalLong("maintenanceInterval");
	arenaOpenInterval = lua->getGlobalLong("arenaOpenInterval");
	arenaClosedInterval = lua->getGlobalLong("arenaClosedInterval");
	arenaChallengeDuration = lua->getGlobalLong("arenaChallengeDuration");
	arenaChallengeCooldown = lua->getGlobalLong("arenaChallengeCooldown");
	requestDemotionDuration = lua->getGlobalLong("requestDemotionDuration");
	voteChallengeDuration = lua->getGlobalLong("voteChallengeDuration");
	baseMaintCost = lua->getGlobalInt("baseMaintCost");
	requestDemotionCost = lua->getGlobalInt("requestDemotionCost");
	voteChallengeCost = lua->getGlobalInt("voteChallengeCost");
	maxPetitioners = lua->getGlobalInt("maxPetitioners");
	missedVotePenalty = lua->getGlobalInt("missedVotePenalty");
	maxChallenges = lua->getGlobalInt("maxChallenges");

	uint32 enclaveID = lua->getGlobalInt("lightEnclaveID");

	lightEnclave = zoneServer->getObject(enclaveID).castTo<BuildingObject*>();

	enclaveID = lua->getGlobalInt("darkEnclaveID");

	darkEnclave = zoneServer->getObject(enclaveID).castTo<BuildingObject*>();

	LuaObject luaObject = lua->getGlobalObject("enclaveRoomRequirements");

	if (luaObject.isValidTable()) {
		for(int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject entry = luaObject.getObjectAt(i);

			uint32 cellID = entry.getIntAt(1);
			int rank = entry.getIntAt(2);

			roomRequirements.put(cellID, rank);

			entry.pop();
		}
	}

	luaObject.pop();

	luaObject = lua->getGlobalObject("lightRankingData");

	if (luaObject.isValidTable()) {
		for(int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject entry = luaObject.getObjectAt(i);

			int rank = entry.getIntAt(1);
			String skillName = entry.getStringAt(2);
			int reqExp = entry.getIntAt(3);
			int playerCap = entry.getIntAt(4);
			String robeTemp = entry.getStringAt(5);

			Reference<FrsRankingData*> data = new FrsRankingData(rank, skillName, reqExp, playerCap, robeTemp);

			lightRankingData.put(rank, data);

			entry.pop();
		}
	}

	luaObject.pop();

	luaObject = lua->getGlobalObject("darkRankingData");

	if (luaObject.isValidTable()) {
		for(int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject entry = luaObject.getObjectAt(i);

			int rank = entry.getIntAt(1);
			String skillName = entry.getStringAt(2);
			int reqExp = entry.getIntAt(3);
			int playerCap = entry.getIntAt(4);
			String robeTemp = entry.getStringAt(5);

			Reference<FrsRankingData*> data = new FrsRankingData(rank, skillName, reqExp, playerCap, robeTemp);

			darkRankingData.put(rank, data);

			entry.pop();
		}
	}

	luaObject.pop();

	luaObject = lua->getGlobalObject("frsExperienceValues");

	if (luaObject.isValidTable()) {
		for(int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject entry = luaObject.getObjectAt(i);
			uint64 keyHash = entry.getStringAt(1).hashCode();

			Vector<int> expValues;

			for (int j = 0; j <= 11; j++) {
				int value = entry.getIntAt(j + 2);
				expValues.add(value);
			}

			experienceValues.put(keyHash, expValues);

			entry.pop();
		}
	}

	luaObject.pop();

	delete lua;
	lua = nullptr;
}

void FrsManagerImplementation::setupEnclaves() {
	ManagedReference<BuildingObject*> enclaveBuilding = lightEnclave.get();

	if (enclaveBuilding != nullptr)
		setupEnclaveRooms(enclaveBuilding, "LightEnclaveRank");

	enclaveBuilding = darkEnclave.get();

	if (enclaveBuilding != nullptr)
		setupEnclaveRooms(enclaveBuilding, "DarkEnclaveRank");
}

FrsRank* FrsManagerImplementation::getFrsRank(short councilType, int rank) {
	if (rank < 0)
		return nullptr;

	ManagedReference<FrsRank*> frsRank = nullptr;

	Locker locker(managerData);

	if (councilType == COUNCIL_LIGHT) {
		Vector<ManagedReference<FrsRank*> >* rankData = managerData->getLightRanks();

		frsRank = rankData->get(rank - 1);
	} else if (councilType == COUNCIL_DARK) {
		Vector<ManagedReference<FrsRank*> >* rankData = managerData->getDarkRanks();

		frsRank = rankData->get(rank - 1);
	}

	return frsRank;
}


void FrsManagerImplementation::setupEnclaveRooms(BuildingObject* enclaveBuilding, const String& groupName) {
	for (int j = 1; j <= enclaveBuilding->getTotalCellNumber(); ++j) {
		ManagedReference<CellObject*> cell = enclaveBuilding->getCell(j);

		if (cell != nullptr) {
			cell->setContainerComponent("EnclaveContainerComponent");

			int roomReq = getRoomRequirement(cell->getObjectID());

			if (roomReq == -1)
				continue;

			ContainerPermissions* permissions = cell->getContainerPermissionsForUpdate();

			permissions->setInheritPermissionsFromParent(false);
			permissions->clearDefaultAllowPermission(ContainerPermissions::WALKIN);
			permissions->setDefaultDenyPermission(ContainerPermissions::WALKIN);

			for (int i = 11; i >= roomReq; i--) {
				permissions->setAllowPermission(groupName + String::valueOf(i), ContainerPermissions::WALKIN);
			}
		}
	}
}

void FrsManagerImplementation::verifyRoomAccess(CreatureObject* player, int playerRank) {
	if (player == nullptr)
		return;

	uint64 cellID = player->getParentID();

	if (cellID == 0)
		return;

	ManagedReference<BuildingObject*> bldg = player->getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();

	if (bldg == nullptr)
		return;

	short buildingType = 0;

	ManagedReference<BuildingObject*> lightBldg = lightEnclave.get();
	ManagedReference<BuildingObject*> darkBldg = darkEnclave.get();

	if (lightBldg != nullptr && bldg->getObjectID() == lightBldg->getObjectID())
		buildingType = COUNCIL_LIGHT;
	else if (darkBldg != nullptr && bldg->getObjectID() == darkBldg->getObjectID())
		buildingType = COUNCIL_DARK;
	else
		return;

	int roomReq = getRoomRequirement(cellID);

	if (playerRank < 0) {
		if (buildingType == COUNCIL_LIGHT)
			player->teleport(-5575, 0, 4905, 0);
		else
			player->teleport(5079, 0, 305, 0);
	} else if (playerRank < roomReq) {
		if (buildingType == COUNCIL_LIGHT)
			player->teleport(-0.1f, -19.3f, 39.9f, 8525439);
		else
			player->teleport(0.1f, -43.4f, -32.2f, 3435634);
	}
}

void FrsManagerImplementation::playerLoggedIn(CreatureObject* player) {
	if (!frsEnabled || player == nullptr)
		return;

	Locker lock(player);

	validatePlayerData(player);
	deductDebtExperience(player);
}

void FrsManagerImplementation::validatePlayerData(CreatureObject* player) {
	if (player == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int councilType = playerData->getCouncilType();
	int curPlayerRank = playerData->getRank();

	if (curPlayerRank == -1)
		return;

	int realPlayerRank = 0;

	if (curPlayerRank == 0 && !player->hasSkill("force_rank_light_novice") && !player->hasSkill("force_rank_dark_novice"))
		realPlayerRank = -1;

	uint64 playerID = player->getObjectID();

	for (int i = 1; i <= 11; i++) {
		ManagedReference<FrsRank*> rankData = getFrsRank(councilType, i);

		if (rankData == nullptr)
			continue;

		Locker clocker(rankData, player);

		if (rankData->isOnPlayerList(playerID)) {
			realPlayerRank = rankData->getRank();
			break;
		}
	}

	if ((councilType == COUNCIL_LIGHT && !player->hasSkill("force_rank_light_novice")) || (councilType == COUNCIL_DARK && !player->hasSkill("force_rank_dark_novice")))
		realPlayerRank = -1;

	if (realPlayerRank != curPlayerRank) {
		if (realPlayerRank == -1 && (councilType == COUNCIL_LIGHT || councilType == COUNCIL_DARK)) {
			removeFromFrs(player);
		} else {
			setPlayerRank(player, realPlayerRank);
		}
	}

	verifyRoomAccess(player, realPlayerRank);

	if (realPlayerRank >= 0 && (councilType == COUNCIL_LIGHT || councilType == COUNCIL_DARK)) {
		if (councilType == COUNCIL_LIGHT && player->getFaction() != Factions::FACTIONREBEL)
			player->setFaction(Factions::FACTIONREBEL);
		else if (councilType == COUNCIL_DARK && player->getFaction() != Factions::FACTIONIMPERIAL)
			player->setFaction(Factions::FACTIONIMPERIAL);

		if (player->getFactionStatus() != FactionStatus::OVERT)
			player->setFactionStatus(FactionStatus::OVERT);

		if (realPlayerRank >= 4 && !player->hasSkill("force_title_jedi_rank_04"))
			player->addSkill("force_title_jedi_rank_04", true);
		if (realPlayerRank >= 8 && !player->hasSkill("force_title_jedi_master"))
			player->addSkill("force_title_jedi_master", true);

		if (realPlayerRank == 0) {
			auto zoneServer = this->zoneServer.get();

			SkillManager* skillManager = zoneServer->getSkillManager();

			if (skillManager == nullptr)
				return;

			if (councilType == COUNCIL_LIGHT && player->getSkillMod("force_control_light") == 0) {
				player->removeSkill("force_rank_light_novice", true);
				skillManager->awardSkill("force_rank_light_novice", player, true, false, true);
			} else if (councilType == COUNCIL_DARK && player->getSkillMod("force_control_dark") == 0) {
				player->removeSkill("force_rank_dark_novice", true);
				skillManager->awardSkill("force_rank_dark_novice", player, true, false, true);
			}
		} else {
			String groupName = "";

			if (councilType == COUNCIL_LIGHT)
				groupName = "LightEnclaveRank" + String::valueOf(realPlayerRank);
			else if (councilType == COUNCIL_DARK)
				groupName = "DarkEnclaveRank" + String::valueOf(realPlayerRank);

			if (!ghost->hasPermissionGroup(groupName))
				ghost->addPermissionGroup(groupName, true);
		}
	}

	ghost->recalculateForcePower();
}

void FrsManagerImplementation::setPlayerRank(CreatureObject* player, int rank) {
	if (player == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	uint64 playerID = player->getObjectID();

	FrsData* playerData = ghost->getFrsData();

	int councilType = playerData->getCouncilType();
	String groupName = "";

	if (councilType == COUNCIL_LIGHT)
		groupName = "LightEnclaveRank";
	else if (councilType == COUNCIL_DARK)
		groupName = "DarkEnclaveRank";

	int curRank = playerData->getRank();

	if (isFrsEnabled() && curRank > 0 && (councilType == COUNCIL_LIGHT || councilType == COUNCIL_DARK)) {
		ghost->removePermissionGroup(groupName + String::valueOf(curRank), true);

		ManagedReference<FrsRank*> rankData = getFrsRank(councilType, curRank);

		if (rankData != nullptr) {
			Locker clocker(rankData, player);
			rankData->removeFromPlayerList(playerID);
		}

		if (curRank > rank) {
			String stfRank = "@force_rank:rank" + String::valueOf(rank);
			String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();

			StringIdChatParameter param("@force_rank:rank_lost"); // You have been demoted to %TO.
			param.setTO(rankString);
			player->sendSystemMessage(param);
		}

		// Player is getting demoted, remove any pending petitions
		if (curRank < 11 && curRank > rank) {
			rankData = getFrsRank(councilType, curRank + 1);

			if (rankData != nullptr) {
				Locker clocker(rankData, player);

				if (rankData->isOnPetitionerList(playerID)) {
					if (councilType == COUNCIL_DARK)
						modifySuddenDeathFlags(player, rankData, true);

					rankData->removeFromPetitionerList(playerID);
				}
			}
		}
	}

	playerData->setRank(rank);

	if (isFrsEnabled()) {
		if (rank <= 0) {
			Locker clocker(managerData, player);
			managerData->removeChallengeTime(playerID);
		}

		if (rank >= 0 && (councilType == COUNCIL_LIGHT || councilType == COUNCIL_DARK)) {
			ghost->addPermissionGroup(groupName + String::valueOf(rank), true);

			if (rank > 0) {
				ManagedReference<FrsRank*> rankData = getFrsRank(councilType, rank);

				if (rankData != nullptr) {
					Locker clocker(rankData, player);
					rankData->addToPlayerList(playerID);
				}
			}
		}

		updatePlayerSkills(player);
	}
}

void FrsManagerImplementation::removeFromFrs(CreatureObject* player) {
	if (player == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	uint64 playerID = player->getObjectID();

	FrsData* playerData = ghost->getFrsData();
	int curRank = playerData->getRank();

	int councilType = playerData->getCouncilType();
	String groupName = "";

	if (councilType == COUNCIL_LIGHT) {
		groupName = "LightEnclaveRank";
	} else if (councilType == COUNCIL_DARK) {
		groupName = "DarkEnclaveRank";
	} else {
		playerData->setRank(-1);
		return;
	}

	if (curRank >= 0) {
		ghost->removePermissionGroup(groupName + String::valueOf(curRank), true);

		if (curRank > 0) {
			ManagedReference<FrsRank*> rankData = getFrsRank(councilType, curRank);

			if (rankData != nullptr) {
				Locker clocker(rankData, player);
				rankData->removeFromPlayerList(playerID);
			}
		}

		ManagedReference<FrsRank*> rankData = getFrsRank(councilType, curRank + 1);

		if (rankData != nullptr) {
			Locker clocker(rankData, player);

			if (rankData->isOnPetitionerList(playerID)) {
				if (councilType == COUNCIL_DARK)
					modifySuddenDeathFlags(player, rankData, true);

				rankData->removeFromPetitionerList(playerID);
			}
		}
	}

	playerData->setRank(-1);
	playerData->setCouncilType(0);

	Locker clocker(managerData, player);
	managerData->removeChallengeTime(playerID);
	clocker.release();

	updatePlayerSkills(player);

	StringIdChatParameter param("@force_rank:council_left"); // You have left the %TO.

	if (councilType == COUNCIL_LIGHT) {
		param.setTO("Light Jedi Council");
	} else if (councilType == COUNCIL_DARK) {
		param.setTO("Dark Jedi Council");
	}

	player->sendSystemMessage(param);
}

void FrsManagerImplementation::handleSkillRevoked(CreatureObject* player, const String& skillName) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();
	int councilType = playerData->getCouncilType();

	if (playerRank < 0 || councilType == 0)
		return;

	if (skillName.hashCode() == STRING_HASHCODE("force_title_jedi_rank_03")) {
		VectorMap<uint32, Reference<FrsRankingData*> > rankingData;

		if (councilType == COUNCIL_LIGHT)
			rankingData = lightRankingData;
		else if (councilType == COUNCIL_DARK)
			rankingData = darkRankingData;

		auto zoneServer = this->zoneServer.get();
		SkillManager* skillManager = zoneServer->getSkillManager();

		for (int i = rankingData.size() -1; i >= 0; i--) {
			Reference<FrsRankingData*> rankData = rankingData.get(i);
			String rankSkill = rankData->getSkillName();

			if (player->hasSkill(rankSkill)) {
				skillManager->surrenderSkill(rankSkill, player, true, false);
			}
		}

		return;
	}

	int skillRank = getSkillRank(skillName, councilType);

	if (skillRank < 0) {
		return;
	} else if (skillRank > 0) {
		setPlayerRank(player, skillRank - 1);
	} else if (skillRank == 0) {
		removeFromFrs(player);
	}

	verifyRoomAccess(player, skillRank - 1);
}

int FrsManagerImplementation::getSkillRank(const String& skillName, int councilType) {
	VectorMap<uint32, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;
	else
		return -1;

	for (int i = 0; i <= 11; i++) {
		Reference<FrsRankingData*> rankData = rankingData.get(i);
		String rankSkill = rankData->getSkillName();

		if (rankSkill.hashCode() == skillName.hashCode())
			return i;
	}

	return -1;
}

void FrsManagerImplementation::updatePlayerSkills(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();
	int councilType = playerData->getCouncilType();
	VectorMap<uint32, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;
	else
		return;

	auto zoneServer = this->zoneServer.get();
	SkillManager* skillManager = zoneServer->getSkillManager();

	if (skillManager == nullptr)
		return;

	for (int i = 11; i >= 0; i--) {
		Reference<FrsRankingData*> rankData = rankingData.get(i);
		String rankSkill = rankData->getSkillName();
		int rank = rankData->getRank();

		if (playerRank >= rank) {
			if (!player->hasSkill(rankSkill))
				skillManager->awardSkill(rankSkill, player, true, true, true);

			if (rank == 4 && !player->hasSkill("force_title_jedi_rank_04"))
				player->addSkill("force_title_jedi_rank_04", true);
			if (rank == 8 && !player->hasSkill("force_title_jedi_master"))
				player->addSkill("force_title_jedi_master", true);
		} else {
			if (player->hasSkill(rankSkill))
				skillManager->surrenderSkill(rankSkill, player, true, false);
		}
	}
}

void FrsManagerImplementation::promotePlayer(CreatureObject* player) {
	if (player == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

	if (rank > 10)
		return;

	int newRank = rank + 1;

	ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();
	ManagedReference<CreatureObject*> strongRef = player->asCreatureObject();

	Core::getTaskManager()->executeTask([strongMan, strongRef, newRank] () {
		Locker locker(strongRef);
		strongMan->setPlayerRank(strongRef, newRank);
		strongMan->recoverJediItems(strongRef);
	}, "SetPlayerRankTask");

	String stfRank = "@force_rank:rank" + String::valueOf(newRank);
	String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();

	StringIdChatParameter param("@force_rank:rank_gained"); // You have achieved the Enclave rank of %TO.
	param.setTO(rankString);
	player->sendSystemMessage(param);
}

void FrsManagerImplementation::demotePlayer(CreatureObject* player) {
	if (player == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

	if (rank == 0)
		return;

	int newRank = rank - 1;
	ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();
	ManagedReference<CreatureObject*> strongRef = player->asCreatureObject();

	Core::getTaskManager()->executeTask([strongMan, strongRef, newRank] () {
		Locker locker(strongRef);
		strongMan->setPlayerRank(strongRef, newRank);
	}, "SetPlayerRankTask");
}

void FrsManagerImplementation::adjustFrsExperience(CreatureObject* player, int amount, bool sendSystemMessage) {
	if (player == nullptr || amount == 0)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	if (amount > 0) {
          
          	if (ghost->hasCappedExperience("force_rank_xp"))
                {
                	StringIdChatParameter message("base_player", "prose_hit_xp_cap"); //You have achieved your current limit for %TO experience.
                	message.setTO("exp_n", "force_rank_xp");
                	player->sendSystemMessage(message);
                	return;
                }
          
		ghost->addExperience("force_rank_xp", amount, true);

		if (sendSystemMessage) {
			StringIdChatParameter param("@force_rank:experience_granted"); // You have gained %DI Force Rank experience.
			param.setDI(amount);

			player->sendSystemMessage(param);
		}
	} else {
		FrsData* playerData = ghost->getFrsData();
		int rank = playerData->getRank();
		int councilType = playerData->getCouncilType();

		int curExperience = ghost->getExperience("force_rank_xp");

		// Ensure we dont go into the negatives
		if ((amount * -1) > curExperience)
			amount = curExperience * -1;

		ghost->addExperience("force_rank_xp", amount, true);

		if (sendSystemMessage) {
			StringIdChatParameter param("@force_rank:experience_lost"); // You have lost %DI Force Rank experience.
			param.setDI(amount * -1);
			player->sendSystemMessage(param);
		}

		curExperience += amount;

		Reference<FrsRankingData*> rankingData = nullptr;

		if (councilType == COUNCIL_LIGHT)
			rankingData = lightRankingData.get(rank);
		else if (councilType == COUNCIL_DARK)
			rankingData = darkRankingData.get(rank);

		if (rankingData == nullptr)
			return;

		int reqXp = rankingData->getRequiredExperience();

		if (reqXp > curExperience)
			demotePlayer(player);
	}
}

Vector<uint64> FrsManagerImplementation::getFullPlayerList() {
	Vector<uint64> playerList;
	Vector<uint64> memberList = getPlayerListByCouncil(COUNCIL_LIGHT);

	for (int i = 0; i < memberList.size(); ++i) {
		uint64 playerID = memberList.get(i);
		playerList.add(playerID);
	}

	memberList = getPlayerListByCouncil(COUNCIL_DARK);

	for (int i = 0; i < memberList.size(); ++i) {
		uint64 playerID = memberList.get(i);
		playerList.add(playerID);
	}

	return playerList;
}

Vector<uint64> FrsManagerImplementation::getPlayerListByCouncil(int councilType) {
	Vector<uint64> playerList;

	Vector<ManagedReference<FrsRank*> >* rankData;

	Locker locker(managerData);

	if (councilType == COUNCIL_LIGHT)
		rankData = managerData->getLightRanks();
	else if (councilType == COUNCIL_DARK)
		rankData = managerData->getDarkRanks();
	else
		return playerList;

	for (int i = 0; i < rankData->size(); i++) {
		ManagedReference<FrsRank*> frsRank = rankData->get(i);

		if (frsRank == nullptr)
			continue;

		Locker clocker(frsRank, managerData);

		SortedVector<uint64>* rankList = frsRank->getPlayerList();

		for (int j = 0; j < rankList->size(); j++) {
			uint64 playerID = rankList->get(j);
			playerList.add(playerID);
		}
	}

	return playerList;
}

void FrsManagerImplementation::deductMaintenanceXp(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

	if (rank == 0)
		return;

	int maintXp = baseMaintCost * rank;

	auto zoneServer = this->zoneServer.get();
	ChatManager* chatManager = zoneServer->getChatManager();

	StringIdChatParameter mailBody("@force_rank:xp_maintenance_body"); // You have lost %DI Force Rank experience. All members of Rank 1 or higher must pay experience each day to remain in their current positions. (Note: This loss may not take effect until your next login.)
	mailBody.setDI(maintXp);

	chatManager->sendMail("Enclave Records", "@force_rank:xp_maintenace_sub", mailBody, player->getFirstName(), nullptr);

	addExperienceDebt(player, maintXp);
}

void FrsManagerImplementation::addExperienceDebt(CreatureObject* player, int amount) {
	uint64 playerID = player->getObjectID();

	Locker clocker(managerData, player);

	int curDebt = managerData->getExperienceDebt(playerID);

	managerData->setExperienceDebt(playerID, curDebt + amount);
}

void FrsManagerImplementation::deductDebtExperience(CreatureObject* player) {
	uint64 playerID = player->getObjectID();

	Locker clocker(managerData, player);

	int curDebt = managerData->getExperienceDebt(playerID);

	if (curDebt <= 0)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* frsData = ghost->getFrsData();
	int rank = frsData->getRank();

	if (rank > 0)
		adjustFrsExperience(player, curDebt * -1);

	managerData->removeExperienceDebt(playerID);
}

bool FrsManagerImplementation::isValidFrsBattle(CreatureObject* attacker, CreatureObject* victim) {
	PlayerObject* attackerGhost = attacker->getPlayerObject();
	PlayerObject* victimGhost = victim->getPlayerObject();

	// No credit if they were killed by the attacker recently
	if (attackerGhost == nullptr || victimGhost == nullptr)
		return false;

	FrsData* attackerData = attackerGhost->getFrsData();
	int attackerRank = attackerData->getRank();
	int attackerCouncil = attackerData->getCouncilType();

	FrsData* victimData = victimGhost->getFrsData();
	int victimRank = victimData->getRank();
	int victimCouncil = victimData->getCouncilType();

	// Neither player is in the FRS
	if (victimCouncil == 0 && attackerCouncil == 0)
		return false;

	// No credit if they are in the same council
	if ((attackerCouncil == COUNCIL_LIGHT && victimCouncil == COUNCIL_LIGHT) || (attackerCouncil == COUNCIL_DARK && victimCouncil == COUNCIL_DARK))
		return false;

	return true;
}

int FrsManagerImplementation::calculatePvpExperienceChange(CreatureObject* attacker, CreatureObject* victim, float contribution, bool isVictim) {
	PlayerObject* attackerGhost = attacker->getPlayerObject();
	PlayerObject* victimGhost = victim->getPlayerObject();

	if (attackerGhost == nullptr || victimGhost == nullptr)
		return 0;

	int targetRating = 0;
	int opponentRating = 0;

	PlayerObject* playerGhost = nullptr;
	PlayerObject* opponentGhost = nullptr;

	if (isVictim) {
		targetRating = victimGhost->getPvpRating();
		opponentRating = attackerGhost->getPvpRating();

		playerGhost = victimGhost;
		opponentGhost = attackerGhost;
	} else {
		targetRating = attackerGhost->getPvpRating();
		opponentRating = victimGhost->getPvpRating();

		playerGhost = attackerGhost;
		opponentGhost = victimGhost;
	}

	int ratingDiff = abs(targetRating - opponentRating);

	if (ratingDiff > 2000)
		ratingDiff = 2000;

	float xpAdjustment = ((float)ratingDiff / 2000.f) * 0.5f;
	int xpChange = getBaseExperienceGain(playerGhost, opponentGhost, !isVictim);

	if (xpChange != 0) {
		xpChange = (int)((float)xpChange * contribution);

		// Adjust xp value depending on pvp rating
		// A lower rated victim will lose less experience, a higher rated victim will lose more experience
		// A lower rated victor will gain more experience, a higher rated victor will gain less experience
		if ((targetRating < opponentRating && isVictim) || (targetRating > opponentRating && !isVictim)) {
			xpChange -= (int)((float)xpChange * xpAdjustment);
		} else {
			xpChange += (int)((float)xpChange * xpAdjustment);
		}
	}

	return xpChange;
}

int FrsManagerImplementation::getBaseExperienceGain(PlayerObject* playerGhost, PlayerObject* opponentGhost, bool playerWon) {
	ManagedReference<CreatureObject*> opponent = opponentGhost->getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (opponent == nullptr)
		return 0;

	FrsData* playerData = playerGhost->getFrsData();
	int playerRank = playerData->getRank();
	int playerCouncil = playerData->getCouncilType();

	FrsData* opponentData = opponentGhost->getFrsData();
	int opponentRank = opponentData->getRank();

	// Make sure player is part of a council before we grab any value to award
	if (playerCouncil == 0)
		return 0;

	String key = "";

	if (opponent->hasSkill("combat_bountyhunter_master")) { // Opponent is MBH
		key = "bh_";
	} else if (opponentRank >= 0 && opponent->hasSkill("force_title_jedi_rank_03")) { // Opponent is at least a knight
		key = "rank" + String::valueOf(opponentRank) + "_";
	} else if (opponent->hasSkill("force_title_jedi_rank_02")) { // Opponent is padawan
		key = "padawan_";
	} else { // Opponent is non jedi
		key = "nonjedi_";
	}

	if (playerWon) {
		key = key + "win";
	} else {
		key = key + "lose";
	}

	uint64 keyHash = key.hashCode();

	if (!experienceValues.contains(keyHash))
		return 0;

	Vector<int> expValues = experienceValues.get(keyHash);

	int returnValue = expValues.get(playerRank);

	if (!playerWon)
		returnValue *= -1;

	return returnValue;
}

void FrsManagerImplementation::sendVoteSUI(CreatureObject* player, SceneObject* terminal, short suiType, short enclaveType) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	Locker locker(player);

	Vector<String> elementList;

	for (int i = 1; i < 12; i++) {
		String stfRank = "@force_rank:rank" + String::valueOf(i);
		String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
		elementList.add(stfRank);
	}

	auto zoneServer = this->zoneServer.get();

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, suiType, enclaveType, -1, true));
	box->setUsingObject(terminal);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setCancelButton(true, "@cancel");

	if (suiType == SUI_VOTE_STATUS) {
		box->setPromptText("@force_rank:vote_status_select"); // Select the rank whose status you wish to view.
		box->setPromptTitle("@force_rank:rank_selection"); // Rank Selection
	} else if (suiType == SUI_VOTE_RECORD) {
		box->setPromptText("@force_rank:vote_record_select"); // Select the rank for which you wish to record your vote.
		box->setPromptTitle("@force_rank:rank_selection"); // Rank Selection
		FrsData* playerData = ghost->getFrsData();
		int rank = playerData->getRank();

		for (int i = 0; i < elementList.size(); i++) {
			ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, i + 1);

			if (rankData == nullptr)
				continue;

			Locker clocker(rankData, player);

			if (rankData->getVoteStatus() != VOTING_OPEN)
				continue;

			if (getVoteWeight(rank, i) > 0 && !hasPlayerVoted(player, rankData)) {
				String voteString = elementList.get(i);
				voteString = voteString + " *";
				elementList.setElementAt(i, voteString);
			}
		}
	} else if (suiType == SUI_VOTE_ACCEPT_PROMOTE) {
		box->setPromptText("@force_rank:vote_promotion_select"); // Select the rank whose status you wish to view.
		box->setPromptTitle("@force_rank:rank_selection"); // Rank Selection
	} else if (suiType == SUI_VOTE_DEMOTE) {
		box->setPromptText("@force_rank:demote_select_rank"); // Select the rank whose member you wish to demote.
		box->setPromptTitle("@force_rank:rank_selection"); // Rank Selection
	}  else if (suiType == SUI_VOTE_PETITION) {
		box->setPromptText("@force_rank:vote_petition_select"); // Select the rank for which you wish to petition for membership.
		box->setPromptTitle("@force_rank:rank_selection"); // Rank Selection
	} else if (suiType == SUI_FORCE_PHASE_CHANGE && ghost->isPrivileged()) {
		box->setPromptText("Select the rank you want to force a phase change on.");
		box->setPromptTitle("@force_rank:rank_selection"); // Rank Selection
	}

	for (int i = 0; i < elementList.size(); i++)
		box->addMenuItem(elementList.get(i));

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleVoteStatusSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLESINGLEBUTTON);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setPromptText("Vote Status for Rank " + String::valueOf(rank));
	box->setPromptTitle("@force_rank:vote_status"); // Voting Status

	Locker clocker(rankData, player);

	short voteStatus = rankData->getVoteStatus();

	if (voteStatus == 0)
		return;

	String curPhase = "";

	if (voteStatus == PETITIONING)
		curPhase = "Petitioning";
	else if (voteStatus == VOTING_OPEN)
		curPhase = "Voting";
	else if (voteStatus == WAITING)
		curPhase = "Acceptance";
	else
		curPhase = "Inactive";

	box->addMenuItem("Current Stage: " + curPhase);

	int slotsAvailable = getAvailableRankSlots(rankData);

	if (slotsAvailable < 0)
		slotsAvailable = 0;

	box->addMenuItem("Seats Available: " + String::valueOf(slotsAvailable));

	uint64 miliDiff = rankData->getLastUpdateTickDiff();
	uint64 interval = getVotingInterval(voteStatus);
	String timeLeft = "";

	if (miliDiff <= interval)
		timeLeft = getTimeString((interval - miliDiff) / 1000);
	else
		timeLeft = "closing soon.";

	box->addMenuItem("Time Remaining: " + timeLeft);

	if (voteStatus != VOTING_CLOSED)
		box->addMenuItem("");

	auto zoneServer = this->zoneServer.get();

	if (voteStatus == PETITIONING || voteStatus == VOTING_OPEN) {

		VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();

		if (petitionerList->size() > 0) {
			box->addMenuItem("Petitioners:");

			for (int i = 0; i < petitionerList->size(); i++) {
				if (i > 20)
					break;

				VectorMapEntry<uint64, int>* entry = &petitionerList->elementAt(i);
				uint64 petitionerID = entry->getKey();
				int votes = entry->getValue();
				ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
				String playerName = playerManager->getPlayerName(petitionerID);

				if (playerName.isEmpty())
					continue;

				if (voteStatus == PETITIONING)
					box->addMenuItem("   " + playerName);
				else
					box->addMenuItem("   " + playerName + "    " + String::valueOf(votes));
			}
		}
	} else if (voteStatus == WAITING) {
		SortedVector<uint64>* winnerList = rankData->getWinnerList();

		if (winnerList->size() > 0) {
			box->addMenuItem("Awaiting Acceptance:");

			for (int i = 0; i < winnerList->size(); i++) {
				uint64 winnerID = winnerList->get(i);
				ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
				String playerName = playerManager->getPlayerName(winnerID);

				if (playerName.isEmpty())
					continue;

				box->addMenuItem("   " + playerName);
			}
		}
	}

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::sendVoteRecordSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	Locker clocker(rankData, player);

	short voteStatus = rankData->getVoteStatus();

	if (voteStatus != VOTING_OPEN) {
		player->sendSystemMessage("@force_rank:voting_not_open"); // Voting for that rank is not currently open.
		return;
	}

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();

	int voteWeight = getVoteWeight(playerRank, rank);

	if (voteWeight <= 0) {
		player->sendSystemMessage("@force_rank:cant_vote_for_rank"); // You are not allowed to cast votes for promotions to that rank.
		return;
	}

	if (rankData->isOnVotedList(player->getObjectID())) {
		player->sendSystemMessage("@force_rank:already_voted"); // You have already voted
		return;
	}

	if (rankData->getTotalPetitioners() <= 0) {
		player->sendSystemMessage("@force_rank:noone_to_vote_for"); // There is no one for which to vote.
		return;
	}

	VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();

	auto zoneServer = this->zoneServer.get();

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, SUI_VOTE_RECORD, enclaveType, rank, false));
	box->setUsingObject(terminal);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setCancelButton(true, "@cancel");

	box->setPromptText("@force_rank:vote_record_select_player"); // Select the petitioner to whom you wish to promote.
	box->setPromptTitle("@force_rank:vote_player_selection"); // Petitioner Selection

	for (int i = 0; i < petitionerList->size(); i++) {
		VectorMapEntry<uint64, int>* entry = &petitionerList->elementAt(i);
		uint64 petitionerID = entry->getKey();
		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
		String playerName = playerManager->getPlayerName(petitionerID);

		if (playerName.isEmpty())
			continue;

		box->addMenuItem(playerName, petitionerID);
	}

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::forcePhaseChange(CreatureObject* player, short enclaveType, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr || !ghost->isPrivileged())
		return;

	ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	Locker locker(rankData);

	runVotingUpdate(rankData);

	player->sendSystemMessage("Rank " + String::valueOf(rank) + "'s phase has been changed.");
}

void FrsManagerImplementation::handleVoteRecordSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank, uint64 petitionerID) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	Locker clocker(rankData, player);

	short voteStatus = rankData->getVoteStatus();

	if (voteStatus != VOTING_OPEN) {
		player->sendSystemMessage("@force_rank:vote_time_expired"); // Time has expired for the voting process.
		return;
	}

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();

	int voteWeight = getVoteWeight(playerRank, rank);

	if (voteWeight <= 0) {
		player->sendSystemMessage("@force_rank:cant_vote_for_rank"); // You are not allowed to cast votes for promotions to that rank.
		return;
	}

	uint64 playerID = player->getObjectID();

	if (rankData->isOnVotedList(playerID)) {
		player->sendSystemMessage("@force_rank:already_voted"); // You have already voted
		return;
	}

	auto zoneServer = this->zoneServer.get();

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	String playerName = playerManager->getPlayerName(petitionerID);

	if (playerName.isEmpty()) {
		player->sendSystemMessage("Unable to find that player.");
		info("FrsManagerImplementation::handleVoteRecordSui failed to find player " + String::valueOf(playerID), true);
		return;
	}

	VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();
	int curVotes = petitionerList->get(petitionerID);

	rankData->addToPetitionerList(petitionerID, curVotes + voteWeight);

	StringIdChatParameter voteCast("@force_rank:vote_cast"); // You cast your vote for %TO.
	voteCast.setTO(playerName);

	player->sendSystemMessage(voteCast);

	rankData->addToVotedList(playerID);
}

void FrsManagerImplementation::handleVotePetitionSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	Locker clocker(rankData, player);

	short voteStatus = rankData->getVoteStatus();

	if (voteStatus != PETITIONING) {
		player->sendSystemMessage("@force_rank:petition_not_open"); // Petitioning for this rank is not currently open.
		return;
	}

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();
	uint64 playerID = player->getObjectID();

	if (playerRank >= rank) {
		player->sendSystemMessage("@force_rank:petition_already_have_rank"); // You have already attained this rank.
		return;
	}

	if (rankData->isOnPetitionerList(playerID)) {
		player->sendSystemMessage("@force_rank:already_petitioning"); // You are already petitioning for this rank.
		return;
	}

	if (rankData->getTotalPetitioners() >= maxPetitioners) {
		player->sendSystemMessage("@force_rank:petitioning_no_room"); // There is already the maximum number of petitioners.
		return;
	}

	if (!isEligibleForPromotion(player, rank)) {
		player->sendSystemMessage("@force_rank:petitioning_not_eligible"); // You are not eligible to petition for this rank.
		return;
	}

	rankData->addToPetitionerList(playerID, 0);
	player->sendSystemMessage("@force_rank:petitioning_complete"); // You add your name to the list of petitioners.
}

void FrsManagerImplementation::handleAcceptPromotionSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	Locker clocker(rankData, player);

	short voteStatus = rankData->getVoteStatus();

	if (voteStatus != WAITING) {
		player->sendSystemMessage("@force_rank:acceptance_time_expired"); // Time has expired for accepting promotions.
		return;
	}

	uint64 playerID = player->getObjectID();

	if (!rankData->isOnWinnerList(playerID)) {
		player->sendSystemMessage("@force_rank:not_a_winner"); // You must win the vote before you can accept a promotion.
		return;
	}

	int availSlots = getAvailableRankSlots(rankData);

	if (availSlots <= 0) {
		SortedVector<uint64>* winnerList = rankData->getWinnerList();

		StringIdChatParameter mailBody("@force_rank:vote_last_seat_taken_body"); // The last available seat for %TO has been filled. When another becomes available, you will be notified. As long as you remain eligible for %TO, you will be able to accept the promotion without a further vote.
		String stfRank = "@force_rank:rank" + String::valueOf(rank);
		String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
		mailBody.setTO(rankString);
		sendMailToList(winnerList, "@force_rank:vote_last_seat_taken_sub", mailBody);

		player->sendSystemMessage(mailBody);
		rankData->setVoteStatus(VOTING_CLOSED);
		return;
	}

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();

	if (playerRank >= rank) {
		player->sendSystemMessage("@force_rank:promotion_already_have_rank"); // You have already achieved this rank.
		return;
	}

	if (!isEligibleForPromotion(player, rank)) {
		player->sendSystemMessage("@force_rank:not_eligible_for_promotion"); // You are not eligible to accept the promotion. If you can meet the eligibility before the acceptance period expires, you can still receive the promotion.
		return;
	}

	player->sendSystemMessage("@force_rank:promotion_accepted"); // You accept the promotion.
	promotePlayer(player);
	rankData->removeFromWinnerList(playerID);

	SortedVector<uint64>* rankList = rankData->getPlayerList();

	StringIdChatParameter mailBody("@force_rank:promotion_accepted_body"); // %TT has accepted a promotion into %TO.
	String stfRank = "@force_rank:rank" + String::valueOf(rank);
	String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
	mailBody.setTO(rankString);
	mailBody.setTT(player->getFirstName());
	sendMailToList(rankList, "@force_rank:promotion_accepted_sub", mailBody);

	if (rankData->getTotalWinners() <= 0) {
		rankData->resetVotingData();
		rankData->setVoteStatus(VOTING_CLOSED);
		return;
	}

	if ((availSlots - 1) <= 0) {
		SortedVector<uint64>* winnerList = rankData->getWinnerList();

		StringIdChatParameter mailBody("@force_rank:vote_last_seat_taken_body"); // The last available seat for %TO has been filled. When another becomes available, you will be notified. As long as you remain eligible for %TO, you will be able to accept the promotion without a further vote.
		String stfRank = "@force_rank:rank" + String::valueOf(rank);
		String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
		mailBody.setTO(rankString);
		sendMailToList(winnerList, "@force_rank:vote_last_seat_taken_sub", mailBody);

		player->sendSystemMessage(mailBody);
		rankData->setVoteStatus(VOTING_CLOSED);
	}
}

bool FrsManagerImplementation::isEligibleForPromotion(CreatureObject* player, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return false;

	FrsData* playerData = ghost->getFrsData();
	int councilType = playerData->getCouncilType();
	VectorMap<uint32, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;
	else
		return false;

	Reference<FrsRankingData*> rankData = rankingData.get(rank);
	String rankSkill = rankData->getSkillName();

	auto zoneServer = this->zoneServer.get();

	SkillManager* skillManager = zoneServer->getSkillManager();

	if (skillManager == nullptr)
		return false;

	return skillManager->fulfillsSkillPrerequisitesAndXp(rankSkill, player);
}

int FrsManagerImplementation::getVoteWeight(int playerRank, int voteRank) {
	if (playerRank < 1) // Unranked players are unable to vote
		return -1;

	if (voteRank < 1 || voteRank > 11) // Invalid vote rank
		return -1;

	if (voteRank == playerRank) // Votes count for double if the voter is in the same rank they are voting for
		return 2;

	switch (voteRank) {
	    case 1:
	    case 2:
	    case 3:
	    case 4:
	        return (playerRank < 5) ? 1 : -1; // Players of rank 1-4 can participate in votes of rank 1-4
	    case 5:
	    case 6:
	    case 7:
	        return (playerRank > 4 && playerRank < 8) ? 1 : -1; // Players of rank 5-7 can participate in votes of rank 5-7
	    case 8:
	    case 9:
	        return (playerRank == 8 || playerRank == 9) ? 1 : -1; // Players of rank 8-9 can particpate in votes of rank 8-9
	    case 10:
	    case 11:
	        return (playerRank == 10 || playerRank == 11) ? 1 : -1; // Players of rank 10-11 can particpate in votes of rank 10-11
	    default:
	        return -1;
	}
}

int FrsManagerImplementation::getRankTier(int rank) {
	switch (rank) {
		case 11: return 5;
		case 10: return 4;
		case 9:
		case 8: return 3;
		case 7:
		case 6:
		case 5: return 2;
		case 4:
		case 3:
		case 2:
		case 1: return 1;
		default: return 0;
	}
}

int FrsManagerImplementation::getChallengeVoteWeight(int playerRank, int challengedRank) {
	int playerTier = getRankTier(playerRank);
	int challengedTier = getRankTier(challengedRank);

	if (playerTier <= challengedTier)
		return 1;

	return 0;
}

bool FrsManagerImplementation::hasPlayerVoted(CreatureObject* player, FrsRank* rankData) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return true;

	return rankData->isOnVotedList(player->getObjectID());
}

int FrsManagerImplementation::getAvailableRankSlots(FrsRank* rankData) {
	short councilType = rankData->getCouncilType();
	int rank = rankData->getRank();

	VectorMap<uint32, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;

	Reference<FrsRankingData*> rankInfo = rankingData.get(rank);

	if (rankData == nullptr)
		return 0;

	return rankInfo->getPlayerCap() - rankData->getTotalPlayersInRank();
}

void FrsManagerImplementation::runChallengeVoteUpdate() {
	Locker locker(managerData);

	VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* challenges = managerData->getLightChallenges();

	if (challenges->size() == 0)
		return;

	auto zoneServer = this->zoneServer.get();

	for (int i = challenges->size() - 1; i >= 0; i--) {
		uint64 challengedID = challenges->elementAt(i).getKey();
		ManagedReference<ChallengeVoteData*> challengeData = challenges->elementAt(i).getValue();

		if (challengeData == nullptr) {
			managerData->removeLightChallenge(challengedID);
			continue;
		}

		uint64 challengeStart = challengeData->getChallengeVoteStart();
		uint64 miliDiff = Time().getMiliTime() - challengeStart;

		if (miliDiff < voteChallengeDuration)
			continue;

		if (challengeData->getStatus() == ChallengeVoteData::VOTING_CLOSED) {
			managerData->removeLightChallenge(challengedID);
			continue;
		}

		ManagedReference<CreatureObject*> challenged = zoneServer->getObject(challengedID).castTo<CreatureObject*>();

		if (challenged == nullptr) {
			managerData->removeLightChallenge(challengedID);
			continue;
		}

		PlayerObject* ghost = challenged->getPlayerObject();

		if (ghost == nullptr)
			continue;

		Locker xlock(challenged, managerData);

		FrsData* playerData = ghost->getFrsData();
		int playerRank = playerData->getRank();
		int councilType = playerData->getCouncilType();

		ManagedReference<FrsManager*> strongRef = _this.getReferenceUnsafeStaticCast();
		String challengedName = challenged->getFirstName();
		int challengedRank = challengeData->getPlayerRank();

		if (playerRank != challengedRank || councilType != COUNCIL_LIGHT) {
			Core::getTaskManager()->executeTask([strongRef, challengedRank, challengedName] () {
				StringIdChatParameter mailBody("@force_rank:challenge_vote_cancelled_body"); // The no-confidence vote on %TO has been cancelled due to a change in the member's ranking.
				mailBody.setTO(challengedName);

				strongRef->sendChallengeVoteMail(challengedRank, "@force_rank:challenge_vote_cancelled_sub", mailBody);
			}, "ChallengeVoteMailTask");

			managerData->removeLightChallenge(challengedID);
			continue;
		}

		int yesVotes = challengeData->getTotalYesVotes();
		int noVotes = challengeData->getTotalNoVotes();

		bool votePassed = yesVotes >= noVotes * 2;

		if (votePassed) {
			Core::getTaskManager()->executeTask([strongRef, challengedRank, challenged, yesVotes, noVotes] () {
				StringIdChatParameter mailBody("@force_rank:challenge_vote_success_body"); // The vote against %TT has succeeded with %TO votes for and %DI votes against.
				mailBody.setTT(challenged->getFirstName());
				mailBody.setTO(String::valueOf(yesVotes));
				mailBody.setDI(noVotes);

				strongRef->sendChallengeVoteMail(challengedRank, "@force_rank:challenge_vote_success_sub", mailBody);

				Locker locker(challenged);
				strongRef->demotePlayer(challenged);
			}, "ChallengeVoteMailTask");
		} else {
			Core::getTaskManager()->executeTask([strongRef, challengedRank, challengedName, yesVotes, noVotes] () {
				StringIdChatParameter mailBody("@force_rank:challenge_vote_fail_body"); // The vote against %TT has failed to pass with %TO votes for and %DI votes against. (Note that for a vote to succeed, two-thirds or more must be for it.)
				mailBody.setTT(challengedName);
				mailBody.setTO(String::valueOf(yesVotes));
				mailBody.setDI(noVotes);

				strongRef->sendChallengeVoteMail(challengedRank, "@force_rank:challenge_vote_fail_sub", mailBody);
			}, "ChallengeVoteMailTask");
		}

		challengeData->setStatus(ChallengeVoteData::VOTING_CLOSED);
	}
}

void FrsManagerImplementation::runVotingUpdate(FrsRank* rankData) {
	short councilType = rankData->getCouncilType();
	int rank = rankData->getRank();
	auto zoneServer = this->zoneServer.get();

	SortedVector<uint64>* rankList = rankData->getPlayerList();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int j = rankList->size() - 1; j >= 0; j--) {
		uint64 playerID = rankList->get(j);
		String playerName = playerManager->getPlayerName(playerID);

		if (playerName.isEmpty()) {
			rankData->removeFromPlayerList(playerID);
			continue;
		}

		ManagedReference<CreatureObject*> player = zoneServer->getObject(rankList->get(j)).castTo<CreatureObject*>();

		if (player == nullptr) {
			rankData->removeFromPlayerList(playerID);
			continue;
		}

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			rankData->removeFromPlayerList(playerID);
			continue;
		}

		FrsData* playerData = ghost->getFrsData();
		int playerRank = playerData->getRank();
		int playerCouncil = playerData->getCouncilType();

		if (playerCouncil != councilType) {
			rankData->removeFromPlayerList(playerID);
		} else if (playerRank != rank) {
			ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();
			ManagedReference<CreatureObject*> strongRef = player->asCreatureObject();

			Core::getTaskManager()->executeTask([strongMan, strongRef] () {
				Locker locker(strongRef);
				strongMan->validatePlayerData(strongRef);
			}, "ValidatePlayerTask");
		}
	}

	ChatManager* chatManager = zoneServer->getChatManager();

	short status = rankData->getVoteStatus();
	int availSlots = getAvailableRankSlots(rankData);

	if (status == VOTING_CLOSED) {
		if (availSlots > 0) {
			SortedVector<uint64>* winnerList = rankData->getWinnerList();

			if (winnerList->size() > 0) {
				StringIdChatParameter mailBody("@force_rank:vote_seat_available_body"); // A council seat has become available for %TO. Since you won the last voting session, you may now claim this seat by going to the voting pedestal and selecting "Accept Promotion".
				String stfRank = "@force_rank:rank" + String::valueOf(rank);
				String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
				mailBody.setTO(rankString);
				sendMailToList(winnerList, "@force_rank:vote_seat_available_sub", mailBody);

				rankData->setVoteStatus(WAITING);
			} else {
				rankData->setVoteStatus(PETITIONING);
			}

		}
	} else if (status == PETITIONING) {
		int totalPetitioners = rankData->getTotalPetitioners();

		if (totalPetitioners == 0) { // No one petitioned
			if (availSlots == 0) { // No slots available, so clear vote data and set back to voting closed
				rankData->resetVotingData();
				rankData->setVoteStatus(VOTING_CLOSED);
			}
			// Slots available, leave the status the same to run the petitioning phase again
		} else {
			if (totalPetitioners <= availSlots || totalPetitioners == 1) { // More open slots than petitioners, or only one petitioner so everyone wins
				rankData->setVoteStatus(WAITING);

				VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();
				ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

				for (int i = 0; i < petitionerList->size(); i++) {
					VectorMapEntry<uint64, int>* entry = &petitionerList->elementAt(i);
					uint64 petitionerID = entry->getKey();

					String name = playerManager->getPlayerName(petitionerID);

					if (name.isEmpty())
						continue;

					rankData->addToWinnerList(petitionerID);
					chatManager->sendMail("Enclave Records", "@force_rank:vote_win_sub", "@force_rank:vote_win_body", name);
				}
			} else { // Move to voting phase to determine who should be promoted
				rankData->setVoteStatus(VOTING_OPEN);

				StringIdChatParameter mailBody("@force_rank:vote_cycle_begun_body"); // Voting has started for promotions into %TO. It is part of your Enclave duties to cast your vote for the petitioner who you deem most worthy. Voting time remaining: %TT
				String stfRank = "@force_rank:rank" + String::valueOf(rank);
				String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
				mailBody.setTO(rankString);
				mailBody.setTT(getTimeString(votingInterval / 1000));

				sendMailToVoters(rankData, "@force_rank:vote_cycle_begun_sub", mailBody);

				if (rankData->getCouncilType() == COUNCIL_DARK)
					setupSuddenDeath(rankData, false);
			}
		}
	} else if (status == VOTING_OPEN) {
		VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();

		if (petitionerList->size() == 0) { // Empty petitioner list. This shouldn't happen, but just in case.
			rankData->resetVotingData();
			rankData->setVoteStatus(VOTING_CLOSED);
		} else {
			if (rankData->getCouncilType() == COUNCIL_DARK)
				setupSuddenDeath(rankData, true);

			if (availSlots > 0) { // Add top X (where X = available slots) winners to winner list so they can accept next phase
				Vector<uint64>* winnerList = getTopVotes(rankData, availSlots);

				for (int i = 0; i < winnerList->size(); i++) {
					rankData->addToWinnerList(winnerList->get(i));
				}

				StringIdChatParameter mailBody("@force_rank:vote_win_body"); // Your Enclave peers have decided that you are worthy of a promotion within the hierarchy. You should return to your Enclave as soon as possible and select "Accept Promotion" at the voting terminal.
				sendMailToList(winnerList, "@force_rank:vote_win_sub", mailBody);

				delete winnerList;

				rankData->setVoteStatus(WAITING);
			} else { // No available slot, top winner will be auto promoted next time a slot opens
				Vector<uint64>* winnerList = getTopVotes(rankData, 1);
				rankData->addToWinnerList(winnerList->get(0));

				StringIdChatParameter mailBody("@force_rank:vote_win_no_slot_body"); // You have won the vote by your Enclave peers in order to achieve a higher ranking. Unforuntately, there are no longer any open seats for you to fill. As a result, you will be offered a chance to accept an open seat the next time one becomes available.
				sendMailToList(winnerList, "@force_rank:vote_win_sub", mailBody);

				delete winnerList;

				rankData->setVoteStatus(VOTING_CLOSED); // Set status to closed without resetting voting data so that the winner will auto take the next available slot
			}

			checkForMissedVotes(rankData);
		}
	} else if (status == WAITING) {
		SortedVector<uint64>* winnerList = rankData->getWinnerList();

		if (winnerList->size() > 0) {
			StringIdChatParameter mailBody("@force_rank:acceptance_expired_body"); // Your deadline for accepting a promotion to %TO has passed. You will have to petition and then win another vote in order to achieve this rank.
			String stfRank = "@force_rank:rank" + String::valueOf(rank);
			String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
			mailBody.setTO(rankString);
			sendMailToList(winnerList, "@force_rank:acceptance_expired_sub", mailBody);
		}

		rankData->resetVotingData();
		rankData->setVoteStatus(VOTING_CLOSED);
	}

	rankData->updateLastTick();
}

void FrsManagerImplementation::checkForMissedVotes(FrsRank* rankData) {
	auto zoneServer = this->zoneServer.get();
	ChatManager* chatManager = zoneServer->getChatManager();
	short councilType = rankData->getCouncilType();
	int rank = rankData->getRank();

	Vector<uint64> missedVoteList;

	for (int i = 1; i <= 11; i++) {
		int voteWeight = getVoteWeight(i, rank);

		if (voteWeight <= 0)
			continue;

		int votePenalty = missedVotePenalty * pow(i, 2);

		SortedVector<uint64>* playerList = rankData->getPlayerList();

		for (int j = 0; j < playerList->size(); j++) {
			uint64 playerID = playerList->get(j);

			if (!rankData->isOnVotedList(playerID)) {
				ManagedReference<CreatureObject*> player = zoneServer->getObject(playerList->get(j)).castTo<CreatureObject*>();

				if (player != nullptr) {
					Locker clocker(player, rankData);

					missedVoteList.add(playerID);
					addExperienceDebt(player, votePenalty);

					StringIdChatParameter mailBody("@force_rank:vote_missed_body"); // You have missed a promotion vote for %TO. As a result, you have lost %DI Force Ranking experience. (Note: This loss may not take effect until your next login.)
					String stfRank = "@force_rank:rank" + String::valueOf(rank);
					String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
					mailBody.setTO(rankString);
					mailBody.setDI(votePenalty);
					chatManager->sendMail("Enclave Records", "@force_rank:vote_missed_sub", mailBody, player->getFirstName());
				}
			}
		}
	}
}

void FrsManagerImplementation::sendMailToVoters(FrsRank* rankData, const String& sub, StringIdChatParameter& body) {
	auto zoneServer = this->zoneServer.get();
	ChatManager* chatManager = zoneServer->getChatManager();
	int rank = rankData->getRank();

	for (int i = 1; i <= 11; i++) {
		int voteWeight = getVoteWeight(i, rank);

		if (voteWeight <= 0)
			continue;

		ManagedReference<FrsRank*> voterData = getFrsRank(rankData->getCouncilType(), i);

		if (voterData == nullptr)
			continue;

		Locker xlock(voterData, rankData);

		SortedVector<uint64>* voterList = voterData->getPlayerList();

		sendMailToList(voterList, sub, body);
	}
}

void FrsManagerImplementation::sendMailToList(Vector<uint64>* playerList, const String& sub, StringIdChatParameter& body) {
	auto zoneServer = this->zoneServer.get();
	ChatManager* chatManager = zoneServer->getChatManager();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int j = 0; j < playerList->size(); j++) {
		uint64 playerID = playerList->get(j);
		String name = playerManager->getPlayerName(playerID);

		if (name.isEmpty())
			continue;

		chatManager->sendMail("Enclave Records", sub, body, name);
	}
}

Vector<uint64>* FrsManagerImplementation::getTopVotes(FrsRank* rankData, int numWinners) {
	Vector<uint64>* winnerList = new Vector<uint64>();
	VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();

	for (int i = 0; i < numWinners; i++) {
		uint64 highestID = 0;
		int highestVote = 0;

		for (int j = 0; j < petitionerList->size(); j++) {
			VectorMapEntry<uint64, int> entry = petitionerList->elementAt(j);
			uint64 petitionerID = entry.getKey();
			uint32 petitionerVotes = entry.getValue();

			if (winnerList->contains(petitionerID))
				continue;

			if (highestID == 0 || petitionerVotes > highestVote || (petitionerVotes == highestVote && System::random(100) > 50)) {
				highestVote = petitionerVotes;
				highestID = petitionerID;
			}
		}

		winnerList->add(highestID);
	}

	return winnerList;
}

void FrsManagerImplementation::sendChallengeVoteSUI(CreatureObject* player, SceneObject* terminal, short suiType, short enclaveType) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();
	auto zoneServer = this->zoneServer.get();

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, suiType, enclaveType, -1, false));
	box->setUsingObject(terminal);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setCancelButton(true, "@cancel");

	if (suiType == SUI_CHAL_VOTE_STATUS or suiType == SUI_CHAL_VOTE_RECORD) {
		if (suiType == SUI_CHAL_VOTE_STATUS) {
			box->setPromptText("@force_rank:challenge_vote_status_select"); // Select a no-confidence challenge you wish to view.
			box->setPromptTitle("@force_rank:challenge_vote_status_title"); // No-Confidence Vote Status
		} else {
			box->setPromptText("@force_rank:challenge_vote_record_vote"); // Select the no-confidence challenge for which you wish to vote.
			box->setPromptTitle("@force_rank:rank_selection"); // No-Confidence Voting
		}

		Locker clocker(managerData, player);

		VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* challenges = managerData->getLightChallenges();

		if (challenges->size() == 0) {
			player->sendSystemMessage("@force_rank:no_challenge_votes"); // There are not any active no-confidence votes at this time.
			return;
		}

		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		for (int i = 0; i < challenges->size(); i++) {
			uint64 challengedID = challenges->elementAt(i).getKey();

			ManagedReference<ChallengeVoteData*> challengeData = challenges->elementAt(i).getValue();

			if (challengeData == nullptr)
				continue;

			if (suiType == SUI_CHAL_VOTE_RECORD && playerRank > challengeData->getPlayerRank())
				continue;

			String playerName = playerManager->getPlayerName(challengedID);

			if (playerName.isEmpty())
				continue;

			box->addMenuItem(playerName, challengedID);
		}
	} else if (suiType == SUI_CHAL_VOTE_ISSUE) {
		box->setPromptText("@force_rank:challenge_vote_select_name"); // Select the name of the Jedi you wish to issue a no-confidence challenge vote. The cost of calling for such a vote is 1000 Force Rank experience per rank challenged. If successful that Jedi will be demoted one rank.
		box->setPromptTitle("@force_rank:challenge_vote_select_name_title"); // No-Confidence Vote Selection

		ManagedReference<FrsRank*> rankData = getFrsRank(COUNCIL_LIGHT, playerRank + 1);

		if (rankData == nullptr)
			return;

		Locker clocker(rankData, player);

		SortedVector<uint64>* rankList = rankData->getPlayerList();
		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		for (int j = 0; j < rankList->size(); j++) {
			uint64 playerID = rankList->get(j);
			String playerName = playerManager->getPlayerName(playerID);

			if (playerName.isEmpty())
				continue;

			box->addMenuItem(playerName, playerID);
		}

	} else {
		return;
	}


	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleChallengeVoteIssueSui(CreatureObject* player, SceneObject* terminal, uint64 challengedID) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();
	auto zoneServer = this->zoneServer.get();

	ManagedReference<CreatureObject*> challenged = zoneServer->getObject(challengedID).castTo<CreatureObject*>();

	if (challenged == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	PlayerObject* challengedGhost = challenged->getPlayerObject();

	if (challengedGhost == nullptr)
		return;

	Locker xlock(challenged, player);

	FrsData* challengedData = challengedGhost->getFrsData();
	int challengedRank = challengedData->getRank();

	xlock.release();

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	String playerName = playerManager->getPlayerName(challengedID);

	if (playerName.isEmpty()) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	if (challengedRank != playerRank + 1) {
		player->sendSystemMessage("@force_rank:vote_challenge_not_correct_rank"); // You can only issue a no-confidence challenge against one rank above your own.
		return;
	}

	Locker clocker(managerData, player);

	ManagedReference<ChallengeVoteData*> challengeData = managerData->getLightChallenge(challengedID);

	if (challengeData != nullptr) {
		StringIdChatParameter param("@force_rank:vote_challenge_already_challenged"); // %TO is already in the process of a no-confidence challenge.
		param.setTO(playerName);
		player->sendSystemMessage(param);
		return;
	}

	if (managerData->getTotalLightChallenges() >= maxChallenges) {
		player->sendSystemMessage("@force_rank:vote_challenge_too_many"); // There are already a maximum number of no-confidence challenges active.
		return;
	}

	if (managerData->hasChallengedRecently(player->getObjectID(), voteChallengeDuration)) {
		uint64 miliDiff = managerData->getChallengeDuration(player->getObjectID());
		uint64 timeLeft = voteChallengeDuration - miliDiff;

		StringIdChatParameter param("@force_rank:challenge_too_soon"); // You cannot issue a no-confidence challenge against another member for another %TO
		param.setTO(getTimeString(timeLeft / 1000));
		player->sendSystemMessage(param);
		return;
	}

	int curExperience = ghost->getExperience("force_rank_xp");
	int challengeCost = voteChallengeCost * challengedRank;

	Reference<FrsRankingData*> rankingData = lightRankingData.get(playerRank);

	if (rankingData == nullptr)
		return;

	int rankXp = rankingData->getRequiredExperience();
	int availXp = curExperience - rankXp;

	if (challengeCost > availXp) {
		player->sendSystemMessage("@force_rank:vote_challenge_not_enough_xp"); // You do not have enough Force Rank experience to issue a no-confidence challenge. Note that you can not spend experience if it would cause you to lose rank.
		return;
	}

	adjustFrsExperience(player, challengeCost * -1, false);

	challengeData = new ChallengeVoteData(challengedID, ChallengeVoteData::VOTING_OPEN, challengedRank, player->getObjectID());
	ObjectManager::instance()->persistObject(challengeData, 1, "frsdata");
	challengeData->updateChallengeVoteStart();

	managerData->addLightChallenge(challengedID, challengeData);
	managerData->updateChallengeTime(player->getObjectID());

	StringIdChatParameter param("@force_rank:vote_challenge_initiated"); // You issue a no-confidence challenge against %TO.
	param.setTO(playerName);
	player->sendSystemMessage(param);

	ManagedReference<FrsManager*> strongRef = _this.getReferenceUnsafeStaticCast();
	String challengerName = player->getFirstName();

	Core::getTaskManager()->executeTask([strongRef, challengedRank, playerName, challengerName] () {
		StringIdChatParameter mailBody("@force_rank:challenge_vote_begun_body"); // %TT has initiated a no-confidence challenge vote against %TO. It is your Enclave duty to vote for or against this motion as soon as possible.
		mailBody.setTT(challengerName);
		mailBody.setTO(playerName);

		strongRef->sendChallengeVoteMail(challengedRank, "@force_rank:challenge_vote_begun_sub", mailBody);
	}, "ChallengeVoteMailTask");
}

void FrsManagerImplementation::handleChallengeVoteStatusSui(CreatureObject* player, SceneObject* terminal, uint64 challengedID) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	Locker clocker(managerData, player);

	ManagedReference<ChallengeVoteData*> challengeData = managerData->getLightChallenge(challengedID);

	if (challengeData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	auto zoneServer = this->zoneServer.get();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	String playerName = playerManager->getPlayerName(challengedID);

	if (playerName.isEmpty()) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLESINGLEBUTTON);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setPromptText("No-Confidence Challenge Status for " + playerName);
	box->setPromptTitle("@force_rank:challenge_vote_status_title"); // No-Confidence Vote Status

	uint64 startTime = challengeData->getChallengeVoteStart();
	uint64 miliDiff = Time().getMiliTime() - startTime;
	uint64 timeLeft = voteChallengeDuration - miliDiff;

	String voteStatus = "Voting Complete";

	if (challengeData->getStatus() == ChallengeVoteData::VOTING_OPEN && miliDiff < voteChallengeDuration)
		voteStatus = "Voting Open";

	box->addMenuItem("Current Stage: " + voteStatus);

	String timeLeftString = "";

	if (challengeData->getStatus() == ChallengeVoteData::VOTING_OPEN) {
		if (miliDiff < voteChallengeDuration) {
			uint64 timeLeft = voteChallengeDuration - miliDiff;
			timeLeftString = getTimeString(timeLeft / 1000);
		} else {
			timeLeftString = "closed.";
		}

		box->addMenuItem("Time Remaining: " + timeLeftString);
	}

	box->addMenuItem("Votes For: " + String::valueOf(challengeData->getTotalYesVotes()));
	box->addMenuItem("Votes Against: " + String::valueOf(challengeData->getTotalNoVotes()));

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleChallengeVoteRecordSui(CreatureObject* player, SceneObject* terminal, uint64 challengedID) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	Locker clocker(managerData, player);

	ManagedReference<ChallengeVoteData*> challengeData = managerData->getLightChallenge(challengedID);

	if (challengeData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	if (challengeData->hasVoted(player->getObjectID())) {
		player->sendSystemMessage("@force_rank:already_voted"); // You have already voted
		return;
	}

	auto zoneServer = this->zoneServer.get();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	String playerName = playerManager->getPlayerName(challengedID);

	if (playerName.isEmpty()) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, SUI_CHAL_VOTE_RECORD_CONFIRM, COUNCIL_LIGHT, -1, false));
	box->setUsingObject(terminal);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setCancelButton(true, "@cancel");

	box->setPromptText("Do you vote for or against the removal of " + playerName + "?");
	box->setPromptTitle("@force_rank:challenge_vote_record_vote_title"); // No-Confidence Voting

	box->addMenuItem("@force_rank:vote_for", challengedID);
	box->addMenuItem("@force_rank:vote_against", challengedID);

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleChallengeVoteRecordConfirmSui(CreatureObject* player, SceneObject* terminal, int index, uint64 challengedID) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	Locker clocker(managerData, player);

	ManagedReference<ChallengeVoteData*> challengeData = managerData->getLightChallenge(challengedID);

	if (challengeData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	if (challengeData->hasVoted(player->getObjectID())) {
		player->sendSystemMessage("@force_rank:already_voted"); // You have already voted
		return;
	}

	auto zoneServer = this->zoneServer.get();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	String playerName = playerManager->getPlayerName(challengedID);

	if (playerName.isEmpty()) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	uint64 startTime = challengeData->getChallengeVoteStart();
	uint64 miliDiff = Time().getMiliTime() - startTime;

	if (miliDiff >= voteChallengeDuration) {
		player->sendSystemMessage("@force_rank:vote_time_expired"); // Time has expired for the voting process.
		return;
	}

	if (index == 0) {
		challengeData->addYesVote(player->getObjectID());
	} else {
		challengeData->addNoVote(player->getObjectID());
	}

	player->sendSystemMessage("@force_rank:challenge_vote_success"); // You have successfully cast your no-confidence vote.
}

void FrsManagerImplementation::sendChallengeVoteMail(int challengedRank, const String& sub, StringIdChatParameter& body) {
	auto zoneServer = this->zoneServer.get();
	ChatManager* chatManager = zoneServer->getChatManager();

	for (int i = 1; i <= 11; i++) {
		int voteWeight = getChallengeVoteWeight(i, challengedRank);

		if (voteWeight <= 0)
			continue;

		ManagedReference<FrsRank*> voterData = getFrsRank(COUNCIL_LIGHT, i);

		if (voterData == nullptr)
			continue;

		Locker locker(voterData);

		SortedVector<uint64>* voterList = voterData->getPlayerList();

		sendMailToList(voterList, sub, body);
	}
}

void FrsManagerImplementation::sendVoteDemoteSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	Locker clocker(rankData, player);

	int demoteRank = rankData->getRank();

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();

	int demoteTier = getRankTier(demoteRank);
	int playerTier = getRankTier(playerRank);

	if (rankData->getTotalPlayersInRank() <= 0) {
		player->sendSystemMessage("@force_rank:no_players_in_rank"); // There are no members in that rank.
		return;
	}

	SortedVector<uint64>* rankList = rankData->getPlayerList();

	clocker.release();

	Locker xlock(managerData, player);

	if (playerTier != 5 && (demoteTier + 1) >= playerTier) {
		player->sendSystemMessage("@force_rank:demote_too_low_rank"); // You must be at least two Tiers higher than that of the rank you wish to demote. The Council Leader may demote anyone.
		return;
	}

	// Council leader has half the normal cooldown
	uint64 demoteDur = (playerTier == 5) ? (requestDemotionDuration / 2) : requestDemotionDuration;
	if (managerData->hasDemotedRecently(player->getObjectID(), demoteDur)) {
		uint64 miliDiff = managerData->getDemoteDuration(player->getObjectID());
		uint64 timeLeft = demoteDur - miliDiff;

		StringIdChatParameter param("@force_rank:demote_too_soon"); // 	You cannot demote a member for another %TO
		param.setTO(getTimeString(timeLeft / 1000));
		player->sendSystemMessage(param);
		return;
	}

	auto zoneServer = this->zoneServer.get();

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, SUI_VOTE_DEMOTE, enclaveType, rank, false));
	box->setUsingObject(terminal);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setCancelButton(true, "@cancel");

	box->setPromptText("@force_rank:demote_select_player"); // Select the member that you wish to demote. Once you make this selection, it may not be undone.
	box->setPromptTitle("@force_rank:demote_selection"); // Demote Selection

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int i = 0; i < rankList->size(); i++) {
		uint64 playerID = rankList->elementAt(i);
		String playerName = playerManager->getPlayerName(playerID);

		if (playerName.isEmpty())
			continue;

		box->addMenuItem(playerName, playerID);
	}

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleVoteDemoteSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank, uint64 playerID) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	auto zoneServer = this->zoneServer.get();

	ManagedReference<CreatureObject*> playerToDemote = zoneServer->getObject(playerID).castTo<CreatureObject*>();

	if (playerToDemote == nullptr) {
		info("FrsManagerImplementation::handleVoteDemoteSui failed to find player " + String::valueOf(playerID), true);
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	Locker xlock(playerToDemote, player);

	PlayerObject* demoteGhost = playerToDemote->getPlayerObject();

	if (demoteGhost == nullptr)
		return;

	FrsData* demotePlayerData = demoteGhost->getFrsData();
	int demotePlayerRank = demotePlayerData->getRank();

	if (demotePlayerRank != rank) {
		player->sendSystemMessage("@force_rank:demote_player_changed_rank"); // That member's rank has changed since you have made your selection.
		return;
	}

	xlock.release();

	ManagedReference<FrsRank*> rankData = getFrsRank(enclaveType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	Locker clocker(rankData, player);

	int demoteRank = rankData->getRank();

	FrsData* playerData = ghost->getFrsData();
	int playerRank = playerData->getRank();
	int councilType = playerData->getCouncilType();

	int demoteTier = getRankTier(demoteRank);
	int playerTier = getRankTier(playerRank);

	clocker.release();

	Locker crosslock(managerData, player);

	if (playerTier != 5 && (demoteTier + 1) >= playerTier) {
		player->sendSystemMessage("@force_rank:demote_too_low_rank"); // You must be at least two Tiers higher than that of the rank you wish to demote. The Council Leader may demote anyone.
		return;
	}

	// Council leader has half the normal cooldown
	uint64 demoteDur = (playerTier == 5) ? (requestDemotionDuration / 2) : requestDemotionDuration;
	if (managerData->hasDemotedRecently(player->getObjectID(), demoteDur)) {
		uint64 miliDiff = managerData->getDemoteDuration(player->getObjectID());
		uint64 timeLeft = demoteDur - miliDiff;

		StringIdChatParameter param("@force_rank:demote_too_soon"); // 	You cannot demote a member for another %TO
		param.setTO(getTimeString(timeLeft / 1000));
		player->sendSystemMessage(param);
		return;
	}

	int curExperience = ghost->getExperience("force_rank_xp");
	int demoteCost = requestDemotionCost * demotePlayerRank;

	Reference<FrsRankingData*> rankingData = nullptr;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData.get(playerRank);
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData.get(playerRank);

	if (rankingData == nullptr)
		return;

	int rankXp = rankingData->getRequiredExperience();
	int availXp = curExperience - rankXp;

	if (demoteCost > availXp) {
		StringIdChatParameter param("@force_rank:insufficient_experience"); // You do not have enough experience to cover the %DI cost without losing a rank.
		param.setDI(demoteCost);
		player->sendSystemMessage(param);
		return;
	}

	adjustFrsExperience(player, demoteCost * -1);
	managerData->updateDemoteTime(player->getObjectID());

	ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();
	ManagedReference<CreatureObject*> strongRef = playerToDemote->asCreatureObject();

	Core::getTaskManager()->executeTask([strongMan, strongRef] () {
		Locker locker(strongRef);
		strongMan->demotePlayer(strongRef);
	}, "DemotePlayerTask");

	StringIdChatParameter param("@force_rank:demote_player_complete"); // You demote %TO.
	param.setTO(playerToDemote->getFirstName());
	player->sendSystemMessage(param);

	Vector<uint64> memberList = getPlayerListByCouncil(councilType);

	StringIdChatParameter mailBody("@force_rank:demote_request_body_rank"); // Using Rank privilege, %TU has demoted %TT by one rank.
	mailBody.setTU(player->getFirstName());
	mailBody.setTT(playerToDemote->getFirstName());

	ChatManager* chatManager = zoneServer->getChatManager();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int j = 0; j < memberList.size(); j++) {
		uint64 listID = memberList.get(j);

		if (listID == playerID)
			continue;

		String name = playerManager->getPlayerName(listID);

		if (name.isEmpty())
			continue;

		chatManager->sendMail("Enclave Records", "@force_rank:demote_request_sub_rank", mailBody, name);
	}

	StringIdChatParameter mBody("@force_rank:demote_request_body"); // 	Using Rank privilege, %TO has demoted you one rank.
	mBody.setTO(player->getFirstName());

	String playerName = playerManager->getPlayerName(playerID);

	chatManager->sendMail("Enclave Records", "@force_rank:demote_request_sub_rank", mBody, playerName);
}


String FrsManagerImplementation::getTimeString(uint64 timestamp) {
	String abbrvs[4] = {"seconds", "minutes", "hours", "days"};

	int intervals[4] = {1, 60, 3600, 86400};
	int values[4] = {0, 0, 0, 0};

	StringBuffer str;

	for (int i = 3; i > -1; --i) {
		values[i] = floor((float)(timestamp / intervals[i]));
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0)
				str << ", ";

			str << values[i] << " " << abbrvs[i];
		}
	}

	return str.toString();
}

short FrsManagerImplementation::getEnclaveType(BuildingObject* enclave) {
	if (enclave == nullptr)
		return 0;

	if (enclave->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/light_enclave.iff"))
		return FrsManager::COUNCIL_LIGHT;
	else if (enclave->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/dark_enclave.iff"))
		return FrsManager::COUNCIL_DARK;

	return 0;
}

void FrsManagerImplementation::recoverJediItems(CreatureObject* player) {
	if (player == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int councilType = playerData->getCouncilType();
	int curPlayerRank = playerData->getRank();

	Reference<FrsRankingData*> rankingData = nullptr;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData.get(curPlayerRank);
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData.get(curPlayerRank);

	if (rankingData == nullptr)
		return;

	String robeTemplate = rankingData->getRobeTemplate();
	uint32 robeCRC = robeTemplate.hashCode();

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr)
		return;

	for (int i=0; i < inventory->getContainerObjectsSize(); i++) {
		ManagedReference<SceneObject*> invObj = inventory->getContainerObject(i);

		if (invObj == nullptr)
			continue;

		if (invObj->getServerObjectCRC() == robeCRC)
			return;
	}

	ManagedReference<SceneObject*> slot = player->getSlottedObject("cloak");

	if (slot != nullptr and slot->getServerObjectCRC() == robeCRC)
		return;

	auto zoneServer = this->zoneServer.get();
	ManagedReference<SceneObject*> robeObj = zoneServer->createObject(robeCRC, 1);

	if (robeObj == nullptr)
		return;

	if (inventory->transferObject(robeObj, -1, true)) {
		robeObj->sendTo(player, true);
		player->sendSystemMessage("@force_rank:items_recovered"); // You have been issued a new set of Jedi rank items from the terminal.
	} else {
		robeObj->destroyObjectFromDatabase(true);
	}
}

bool FrsManagerImplementation::isPlayerInEnclave(CreatureObject* player) {
	if (!frsEnabled || player->getParentID() == 0)
		return false;

	ManagedReference<BuildingObject*> bldg = player->getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();
	ManagedReference<BuildingObject*> lightBldg = lightEnclave.get();
	ManagedReference<BuildingObject*> darkBldg = darkEnclave.get();

	return bldg != nullptr && ((lightBldg != nullptr && bldg->getObjectID() == lightBldg->getObjectID()) || (darkBldg != nullptr && bldg->getObjectID() == darkBldg->getObjectID()));
}

void FrsManagerImplementation::sendRankPlayerList(CreatureObject* player, int councilType, int rank) {
	if (player == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int playerCouncil = playerData->getCouncilType();
	int curPlayerRank = playerData->getRank();

	if (curPlayerRank < 0)
		return;

	if (playerCouncil != councilType)
		return;

	ManagedReference<FrsRank*> rankData = getFrsRank(councilType, rank);

	if (rankData == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	Locker locker(rankData);

	if (rankData->getTotalPlayersInRank() <= 0) {
		player->sendSystemMessage("@force_rank:no_players_in_rank"); // There are no members in that rank.
		return;
	}

	SortedVector<uint64>* rankList = rankData->getPlayerList();

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLESINGLEBUTTON);
	box->setUsingObject(player);
	box->setOkButton(true, "@ok");

	String stfRank = "@force_rank:rank" + String::valueOf(rank);
	String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
	box->setPromptText("Members in " + rankString + ":");
	box->setPromptTitle("Council Player List");

	auto zoneServer = this->zoneServer.get();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int i = 0; i < rankList->size(); i++) {
		uint64 playerID = rankList->elementAt(i);
		String playerName = playerManager->getPlayerName(playerID);

		if (playerName.isEmpty())
			continue;

		if (ghost->isPrivileged())
			playerName += " (" + String::valueOf(playerID) + ")";

		box->addMenuItem(playerName);
	}

	int availSlots = getAvailableRankSlots(rankData);

	for (int i = 0; i < availSlots; i++) {
		box->addMenuItem("Open Seat");
	}

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

bool FrsManagerImplementation::isPlayerInDarkArena(CreatureObject* player) {
	if (player->getParentID() != ARENA_CELL)
		return false;

	float posX = player->getPositionX();
	float posY = player->getPositionY();

	if (posX < -13.f || posX > 13.f)
		return false;

	if (posY < -86.f || posY > -60.f)
		return false;

	return true;
}

void FrsManagerImplementation::handleArenaChallengeViewSui(CreatureObject* player, SceneObject* terminal, SuiBox* suiBox, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	if (index < 0)
		return;

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (listBox == nullptr)
		return;

	int rank = listBox->getMenuObjectID(index);

	Locker clocker(managerData, player);

	if (getTotalOpenArenaChallenges(rank) <= 0)
		return;

	const VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	clocker.release();

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLESINGLEBUTTON);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setPromptText("@pvp_rating:ch_terminal_pending"); // Pending challenges for selected rank:
	box->setPromptTitle("@pvp_rating:ch_terminal_view_challenges"); // View Issued Challenges

	auto zoneServer = this->zoneServer.get();

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> challengeData = arenaChallenges->get(i);

		if (challengeData->getChallengeRank() != rank)
			continue;

		if (challengeData->getChallengeAccepterID() != 0)
			continue;

		uint64 challengerID = challengeData->getChallengerID();

		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
		String playerName = playerManager->getPlayerName(challengerID);

		if (playerName.isEmpty())
			continue;

		ManagedReference<CreatureObject*> challenger = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

		if (challenger == nullptr)
			continue;

		PlayerObject* cGhost = challenger->getPlayerObject();

		if (cGhost == nullptr)
			continue;

		Locker xlck(challenger, player);

		FrsData* playerData = cGhost->getFrsData();
		int challengerRank = playerData->getRank();

		xlck.release();

		if (challengerRank + 1 != rank)
			continue;

		uint64 startTime = challengeData->getChallengeStart();
		uint64 challengeDiff = Time().getMiliTime() - startTime;

		if (challengeDiff >= arenaChallengeDuration)
			continue;

		String rowString;

		if (challengeDiff < 60000) {
			rowString = playerName + "(less than 1 minute remaining on challenge)";
		} else {
			int minsLeft = (float)(challengeDiff / 1000) / 60.f;
			rowString = playerName + "(" + String::valueOf(minsLeft) + " minutes remaining on challenge)";
		}

		box->addMenuItem(rowString, challengerID);
	}

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

int FrsManagerImplementation::getTotalOpenArenaChallenges(int rank) {
	const VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	if (arenaChallenges->size() == 0)
		return 0;

	int chalCount = 0;

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> challengeData = arenaChallenges->get(i);

		if (challengeData->getChallengeRank() != rank)
			continue;

		if (challengeData->getChallengeAccepterID() == 0)
			chalCount++;
	}

	return chalCount;
}

bool FrsManagerImplementation::playerAbleToChallenge(CreatureObject* player) {
	uint64 playerID = player->getObjectID();

	if (managerData->hasOpenArenaChallenge(playerID))
		return false;

	if (managerData->hasChallengedRecently(playerID, arenaChallengeCooldown))
		return false;

	return true;
}

bool FrsManagerImplementation::hasPlayerAcceptedArenaChallenge(CreatureObject* player) {
	uint64 playerID = player->getObjectID();
	const VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	if (arenaChallenges->size() == 0)
		return false;

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> challengeData = arenaChallenges->get(i);

		if (challengeData->getChallengeAccepterID() == playerID)
			return true;
	}

	return false;
}

void FrsManagerImplementation::updateArenaScores() {
	Locker locker(managerData);
	auto zoneServer = this->zoneServer.get();

	for (int i = 1; i <= 11; i++) {
		FrsRank* rankData = getFrsRank(COUNCIL_DARK, i);

		if (rankData == nullptr)
			continue;

		Locker clocker(rankData, managerData);

		int challenges = rankData->getArenaChallengesThisPhase();
		int challengesAccepted = rankData->getArenaChallengesAcceptedThisPhase();
		int challengeScore = rankData->getArenaChallengeScore();

		if (challenges == 0) {
			challengeScore = 0;
		} else {
			float answeredRatio = (float)challengesAccepted / (float)challenges;

			if (answeredRatio >= 0.5f) {
				challengeScore = 0;
			} else {
				challengeScore -= 1;
			}
		}

		if (challengeScore <= -8) {
			Vector<uint64> memberList = getPlayerListByCouncil(COUNCIL_DARK);

			StringIdChatParameter mailBody("@pvp_rating:ch_terminal_demote_rank_penalty"); // The members of rank %DI have failed to answer numerous challenges issued by the Dark Jedi of the enclave. As a result, the entire rank has been demoted to rank zero. Weakness cannot be tolerated in the Council.
			mailBody.setDI(i);
			sendMailToList(&memberList, "@pvp_rating:ch_terminal_demote_subject", mailBody);

			SortedVector<uint64>* playerList = rankData->getPlayerList();

			for (int j = playerList->size() - 1; j >= 0; j--) {
				uint64 playerID = playerList->get(j);
				ManagedReference<CreatureObject*> player = zoneServer->getObject(playerList->get(j)).castTo<CreatureObject*>();

				if (player != nullptr) {
					ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();

					Core::getTaskManager()->executeTask([strongMan, player] () {
						Locker locker(player);
						strongMan->setPlayerRank(player, 0);
					}, "SetPlayerRankTask");
				}
			}

			challengeScore = 0;
		}

		rankData->setArenaChallengeScore(challengeScore);
		rankData->setArenaChallengesThisPhase(0);
		rankData->setArenaChallengesAcceptedThisPhase(0);
	}
}

void FrsManagerImplementation::wipeArenaChallenges() {
	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();
	int arenaChallengeCount = arenaChallenges->size();
	auto zoneServer = this->zoneServer.get();

	for (int i = arenaChallengeCount - 1; i >= 0; i--) {
		ManagedReference<ArenaChallengeData*> challengeData = arenaChallenges->get(i);

		uint64 challengerID = challengeData->getChallengerID();
		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
		String playerName = playerManager->getPlayerName(challengerID);

		if (playerName.isEmpty()) {
			arenaChallenges->remove(i);
			continue;
		}

		uint64 challengeAccepterID = challengeData->getChallengeAccepterID();

		if (challengeAccepterID != 0) {
			managerData->removeArenaFighter(challengerID);
			managerData->removeArenaFighter(challengeAccepterID);

			ManagedReference<CreatureObject*> player = zoneServer->getObject(challengeAccepterID).castTo<CreatureObject*>();

			if (player != nullptr) {
				Locker clocker(player, managerData);
				player->removePersonalEnemyFlag(challengerID);
			}

			player = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

			if (player != nullptr) {
				Locker clocker(player, managerData);
				player->removePersonalEnemyFlag(challengeAccepterID);
			}
		}

		arenaChallenges->remove(i);
	}

	short arenaStatus = managerData->getArenaStatus();

	if (arenaStatus == ARENA_CLOSED && arenaChallengeCount > 0) {
		ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();

		Core::getTaskManager()->executeTask([strongMan] () {
			strongMan->updateArenaScores();
		}, "UpdateArenaScoresTask");
	}
}

void FrsManagerImplementation::performArenaMaintenance() {
	Locker locker(managerData);

	uint64 lastOpen = managerData->getLastArenaOpenTime();
	uint64 miliDiff = Time().getMiliTime() - lastOpen;
	short arenaStatus = managerData->getArenaStatus();
	bool justClosedArena = false;

	if (arenaStatus == ARENA_OPEN && miliDiff >= arenaOpenInterval) {
		arenaStatus = ARENA_CLOSED;
		managerData->setArenaStatus(ARENA_CLOSED);
		justClosedArena = true;
	} else if (arenaStatus == 0 || (arenaStatus == ARENA_CLOSED && miliDiff >= arenaClosedInterval + arenaOpenInterval)) {
		arenaStatus = ARENA_OPEN;
		managerData->setArenaStatus(ARENA_OPEN);
		managerData->updateLastArenaOpenTime();
	}

	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	bool challengeEnded = false;
	auto zoneServer = this->zoneServer.get();

	// Not all challenges will end at the interval, challenges started towards the end of the interval will continue until their duration is up
	for (int i = arenaChallenges->size() - 1; i >= 0; i--) {
		VectorMapEntry<uint64, ManagedReference<ArenaChallengeData*> > entry = arenaChallenges->elementAt(i);
		uint64 challengeKey = entry.getKey();
		ManagedReference<ArenaChallengeData*> challengeData = entry.getValue();

		uint64 startTime = challengeData->getChallengeStart();
		uint64 challengeDiff = Time().getMiliTime() - startTime;

		uint64 challengerID = challengeData->getChallengerID();
		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		String playerName = playerManager->getPlayerName(challengerID);
		ManagedReference<CreatureObject*> challenger = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

		uint64 challengeAccepterID = challengeData->getChallengeAccepterID();
		bool challengeCompleted = challengeData->isChallengeCompleted();
		int challengeRank = challengeData->getChallengeRank();

		FrsRank* rankData = getFrsRank(COUNCIL_DARK, challengeRank);

		if (rankData == nullptr)
			continue;

		if (challenger == nullptr || playerName.isEmpty()) {
			if (challengeAccepterID == 0) {
				Locker xlck(rankData, managerData);
				int chalCount = rankData->getArenaChallengesThisPhase();
				rankData->setArenaChallengesThisPhase(chalCount - 1);
				xlck.release();
			}

			arenaChallenges->remove(i);
			managerData->removeArenaChallenge(challengeKey);
			continue;
		}

		PlayerObject* cGhost = challenger->getPlayerObject();

		if (cGhost == nullptr) {
			if (challengeAccepterID == 0) {
				Locker xlck(rankData, managerData);
				int chalCount = rankData->getArenaChallengesThisPhase();
				rankData->setArenaChallengesThisPhase(chalCount - 1);
				xlck.release();
			}

			arenaChallenges->remove(i);
			managerData->removeArenaChallenge(challengeKey);
			continue;
		}

		Locker xlck(challenger, managerData);

		FrsData* playerData = cGhost->getFrsData();
		int challengerRank = playerData->getRank();

		xlck.release();

		if (challengerRank+1 != challengeRank) {
			if (challengeAccepterID == 0) {
				Locker xlck(rankData, managerData);
				int chalCount = rankData->getArenaChallengesThisPhase();
				rankData->setArenaChallengesThisPhase(chalCount - 1);
				xlck.release();
			}

			arenaChallenges->remove(i);
			managerData->removeArenaChallenge(challengeKey);
			continue;
		}

		if (challengeDiff >= arenaChallengeDuration) {
			if (challengeAccepterID != 0 && !challengeCompleted)
				continue;

			if (challengeAccepterID == 0) {
				Locker clocker(rankData, managerData);
				SortedVector<uint64>* playerList = rankData->getPlayerList();

				StringIdChatParameter mailBody("@pvp_rating:challenge_concluded_timeout"); // Although a challenge had been issued, no one in rank %DI saw fit to defend the honor of their rank by accepting the challenge issued by %TT. The challenge has thus expired.
				mailBody.setTT(playerName);
				mailBody.setDI(challengeRank);
				sendMailToList(playerList, "@pvp_rating:challenge_timout_subject_header", mailBody);

				ManagedReference<CreatureObject*> challenger = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

				if (challenger != nullptr)
					challenger->sendSystemMessage(mailBody);
			}

			challengeEnded = true;
			arenaChallenges->remove(i);
			managerData->removeArenaChallenge(challengeKey);
		}
	}

	// This block should only execute once there are no challenges left
	if (arenaStatus == ARENA_CLOSED && arenaChallenges->size() == 0 && (justClosedArena || challengeEnded)) {
		ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();

		Core::getTaskManager()->executeTask([strongMan] () {
			strongMan->updateArenaScores();
		}, "UpdateArenaScoresTask");
	}
}

bool FrsManagerImplementation::handleDarkCouncilIncap(CreatureObject* killer, CreatureObject* victim) {
	if (!frsEnabled || killer == nullptr || victim == nullptr)
		return false;

	uint64 killerID = killer->getObjectID();
	uint64 victimID = victim->getObjectID();

	Locker locker(managerData);

	if (!isFightingInArena(killerID) || !isFightingInArena(victimID))
		return false;

	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> tempData = arenaChallenges->get(i);
		uint64 challengerID = tempData->getChallengerID();
		uint64 accepterID = tempData->getChallengeAccepterID();

		if ((killerID == challengerID && victimID == accepterID) || (killerID == accepterID && victimID == challengerID)) {
			killer->sendSystemMessage("@pvp_rating:arena_incap_opponent"); // You have incapcitated your opponent. If you deathblow them, be sure to stay in the arena until the match has completely resolved (you will get another message) or you may lose the challenge for abandoning the fight prematurely.
			return true;
		}
	}

	return false;
}

bool FrsManagerImplementation::handleDarkCouncilDeath(CreatureObject* killer, CreatureObject* victim, bool forfeit) {
	if (!frsEnabled || killer == nullptr || victim == nullptr)
		return false;

	uint64 killerID = killer->getObjectID();
	uint64 victimID = victim->getObjectID();

	Locker locker(managerData);

	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();
	ManagedReference<ArenaChallengeData*> challengeData = nullptr;
	bool challengerWon = false;

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> tempData = arenaChallenges->get(i);
		uint64 challengerID = tempData->getChallengerID();
		uint64 accepterID = tempData->getChallengeAccepterID();

		if (killerID == challengerID && victimID == accepterID) {
			challengeData = tempData;
			challengerWon = true;
		} else if (killerID == accepterID && victimID == challengerID) {
			challengeData = tempData;
		}
	}

	if (challengeData == nullptr)
		return false;

	uint64 challengerID = challengeData->getChallengerID();
	uint64 accepterID = challengeData->getChallengeAccepterID();
	int challengeRank = challengeData->getChallengeRank();
	challengeData->setChallengeCompleted();

	managerData->removeArenaFighter(challengerID);
	managerData->removeArenaFighter(accepterID);

	int killerXp = calculatePvpExperienceChange(killer, victim, 1.0f, false);
	int victimXp = calculatePvpExperienceChange(killer, victim, 1.0f, true);

	ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();
	ManagedReference<CreatureObject*> strongKiller = killer->asCreatureObject();
	ManagedReference<CreatureObject*> strongVictim = victim->asCreatureObject();

	Core::getTaskManager()->executeTask([strongMan, strongKiller, strongVictim, killerXp, victimXp, forfeit, challengerWon] () {
		Locker locker(strongKiller);

		if (!forfeit)
			strongMan->adjustFrsExperience(strongKiller, killerXp);

		strongKiller->removePersonalEnemyFlag(strongVictim);

		Locker clocker(strongVictim, strongKiller);

		if (!forfeit)
			strongMan->adjustFrsExperience(strongVictim, victimXp);

		strongVictim->removePersonalEnemyFlag(strongKiller);

		strongVictim->sendPvpStatusTo(strongKiller);
		strongKiller->sendPvpStatusTo(strongVictim);

		if (challengerWon) {
			strongMan->demotePlayer(strongVictim);
			strongMan->promotePlayer(strongKiller);
		}
	}, "HandleDarkCouncilDeathXpTask");

	String mailString = "@pvp_rating:challenge_concluded_defender_win"; // %TU has defeated %TT during a battle for the honor of rank %DI. As a result, %TU will remain at their station in rank %DI, while %TT will live in shame for their defeat.

	if (challengerWon) {
		managerData->updateChallengeTime(accepterID);
		mailString = "@pvp_rating:challenge_concluded_challenger_won"; // %TU was defeated by %TT during a battle for the honor of rank %DI. As a result %TU has been demoted from rank %DI, while %TT has taken their place.
	}

	FrsRank* rankData = getFrsRank(COUNCIL_DARK, challengeRank);

	if (rankData == nullptr)
		return true;

	Locker clocker(rankData, managerData);

	SortedVector<uint64>* playerList = rankData->getPlayerList();

	StringIdChatParameter mailBody(mailString);

	if (challengerWon) {
		mailBody.setTU(victim->getFirstName());
		mailBody.setTT(killer->getFirstName());
	} else {
		mailBody.setTU(killer->getFirstName());
		mailBody.setTT(victim->getFirstName());
	}
	mailBody.setDI(challengeRank);
	sendMailToList(playerList, "@pvp_rating:challenge_concluded_subject_header", mailBody);

	killer->sendSystemMessage(mailBody);
	victim->sendSystemMessage(mailBody);

	return true;
}

void FrsManagerImplementation::handleLeftArena(CreatureObject* player) {
	Locker locker(managerData);

	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();
	ManagedReference<CreatureObject*> opponent = nullptr;
	uint64 playerID = player->getObjectID();
	auto zoneServer = this->zoneServer.get();

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> tempData = arenaChallenges->get(i);
		uint64 challengerID = tempData->getChallengerID();
		uint64 accepterID = tempData->getChallengeAccepterID();

		if (playerID == challengerID) {
			opponent = zoneServer->getObject(accepterID).castTo<CreatureObject*>();
			break;
		} else if (playerID == accepterID) {
			opponent = zoneServer->getObject(challengerID).castTo<CreatureObject*>();
			break;
		}
	}

	if (opponent == nullptr)
		return;

	ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();
	ManagedReference<CreatureObject*> strongPlayer = player->asCreatureObject();
	ManagedReference<CreatureObject*> strongOpponent = opponent->asCreatureObject();

	Core::getTaskManager()->executeTask([strongMan, strongPlayer, strongOpponent] () {
		strongMan->handleDarkCouncilDeath(strongOpponent, strongPlayer, true);
	}, "HandleDarkCouncilDeathTask");
}

void FrsManagerImplementation::issueArenaChallenge(CreatureObject* player, int rank) {
	FrsRank* rankData = getFrsRank(COUNCIL_DARK, rank);

	if (rankData == nullptr)
		return;

	Locker locker(rankData);

	SortedVector<uint64>* playerList = rankData->getPlayerList();
	int curChallenges = rankData->getArenaChallengesThisPhase();
	rankData->setArenaChallengesThisPhase(curChallenges + 1);

	locker.release();

	Locker lock(managerData);

	uint64 playerID = player->getObjectID();

	ArenaChallengeData* challengeData = new ArenaChallengeData(playerID, rank);
	ObjectManager::instance()->persistObject(challengeData, 1, "frsdata");
	managerData->addArenaChallenge(playerID, challengeData);

	managerData->updateChallengeTime(playerID);

	StringIdChatParameter sysMsg("@pvp_rating:challenge_issued_challenger"); // You have issued a challenge against rank %DI. Any member of that rank may accept your challenge during the next 60 minutes. Should a rank member accept your challenge and you are not present in the enclave (or you are dead), you will lose the challenge by default. If you are not in the arena hall when the challange is accepted you will be teleported there as long as you are within the walls of the enclave. Should you win the challenge, you will be granted a position in rank %DI. Should you lose the challenge, you will lose a quantity of Force RankXP.
	sysMsg.setDI(rank);

	player->sendSystemMessage(sysMsg);

	StringIdChatParameter mailBody("@pvp_rating:challenge_issued_rank"); //	%TT has issued a challenge against your rank! If you wish to defend the honor of your rank, find the challenge terminal in the Dark Jedi enclave and accept the challenge. You have 60 minutes to do so, starting now. Should you accept and lose the challenge, you will be demoted into the rank below yours, while %TT will take your position.
	mailBody.setTT(player->getFirstName());

	sendMailToList(playerList, "@pvp_rating:challenge_issued_subject_header", mailBody);

	auto zoneServer = this->zoneServer.get();

	ChatManager* chatManager = zoneServer->getChatManager();
	Locker clocker(chatManager, managerData);

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	PlayerMap* playerMap = chatManager->getPlayerMap();

	for (int j = playerList->size() - 1; j >= 0; j--) {
		uint64 memberID = playerList->get(j);
		String playerName = playerManager->getPlayerName(memberID);

		ManagedReference<CreatureObject*> rankMember = playerMap->get(playerName);

		if (rankMember != nullptr && rankMember->isOnline()) {
			rankMember->sendSystemMessage(mailBody);
		}
	}
}

void FrsManagerImplementation::acceptArenaChallenge(CreatureObject* player, uint64 challengerID) {
	Locker locker(managerData);

	if (!managerData->hasOpenArenaChallenge(challengerID))
		return;

	ManagedReference<ArenaChallengeData*> challengeData = managerData->getArenaChallenge(challengerID);

	if (challengeData->getChallengeAccepterID() != 0)
		return;

	int challengeRank = challengeData->getChallengeRank();

	FrsRank* rankData = getFrsRank(COUNCIL_DARK, challengeRank);

	if (rankData == nullptr)
		return;

	Locker clocker(rankData, managerData);

	SortedVector<uint64>* playerList = rankData->getPlayerList();
	int curChallenges = rankData->getArenaChallengesAcceptedThisPhase();
	rankData->setArenaChallengesAcceptedThisPhase(curChallenges + 1);

	clocker.release();

	auto zoneServer = this->zoneServer.get();

	ManagedReference<CreatureObject*> challenger = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

	if (challenger == nullptr)
		return;

	challengeData->setChallengeAccepterID(player->getObjectID());

	if (!challenger->isOnline() || challenger->isDead() || !isPlayerInEnclave(challenger)) {
		if (challenger->isOnline()) {
			challenger->sendSystemMessage("@pvp_rating:ch_terminal_challenger_forfeit_ch"); // Since you were not in the enclave, or you were dead, when your challenge was accepted, you have conceded the battle. Your honor has been tarnished significantly by your actions.
		}

		ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();
		ManagedReference<CreatureObject*> strongPlayer = player->asCreatureObject();
		ManagedReference<CreatureObject*> strongChallenger = challenger->asCreatureObject();

		Core::getTaskManager()->executeTask([strongMan, strongPlayer, strongChallenger] () {
			strongMan->handleDarkCouncilDeath(strongPlayer, strongChallenger, true);
		}, "HandleDarkCouncilDeathTask");

		player->sendSystemMessage("@pvp_rating:ch_terminal_challenger_forfeit"); // The challenger has forfeit this battle by not being present and alive in the enclave to complete the duel. Honor has been restored to your rank.

		ChatManager* chatManager = zoneServer->getChatManager();

		chatManager->sendMail("Enclave Records", "@pvp_rating:challenge_concluded_subject_header", "@pvp_rating:ch_terminal_challenger_forfeit_ch", challenger->getFirstName());

		return;
	}

	StringIdChatParameter mailBody("@pvp_rating:challenge_accepted"); // %TU has stepped forward to accept a challenge against rank %DI, issued by %TT. A battle to the death is commencing in the arena at the hidden enclave.
	mailBody.setTU(player->getFirstName());
	mailBody.setTT(challenger->getFirstName());
	mailBody.setDI(challengeRank);

	challenger->sendSystemMessage(mailBody);

	sendMailToList(playerList, "@pvp_rating:challenge_accepted_subject_header", mailBody);

	ChatManager* chatManager = zoneServer->getChatManager();
	Locker xlock(chatManager, managerData);

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	PlayerMap* playerMap = chatManager->getPlayerMap();

	for (int j = playerList->size() - 1; j >= 0; j--) {
		uint64 memberID = playerList->get(j);
		String playerName = playerManager->getPlayerName(memberID);

		ManagedReference<CreatureObject*> rankMember = playerMap->get(playerName);

		if (rankMember != nullptr && rankMember->isOnline()) {
			rankMember->sendSystemMessage(mailBody);
		}
	}

	xlock.release();

	if (!isPlayerInDarkArena(player))
		teleportPlayerToDarkArena(player);

	if (!isPlayerInDarkArena(challenger))
		teleportPlayerToDarkArena(challenger);

	managerData->addArenaFighter(player->getObjectID());
	managerData->addArenaFighter(challenger->getObjectID());

	ManagedReference<CreatureObject*> strongRef = player->asCreatureObject();
	ManagedReference<CreatureObject*> strongChal = challenger->asCreatureObject();

	Core::getTaskManager()->executeTask([strongRef, strongChal] () {
		Locker locker(strongRef);
		strongRef->addPersonalEnemyFlag(strongChal, 0);

		Locker clocker(strongChal, strongRef);
		strongChal->addPersonalEnemyFlag(strongRef, 0);

		strongRef->sendPvpStatusTo(strongChal);
		strongChal->sendPvpStatusTo(strongRef);
	}, "AddPersonalEnemyFlagTask");
}

void FrsManagerImplementation::teleportPlayerToDarkArena(CreatureObject* player) {
	if (!isPlayerInEnclave(player))
		return;

	float randX = -12.f + System::random(24);
	float randY = -85.f + System::random(24);

	player->teleport(randX, -47.424f, randY, ARENA_CELL);
}

void FrsManagerImplementation::sendArenaChallengeSUI(CreatureObject* player, SceneObject* terminal, short suiType, short enclaveType) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();
	auto zoneServer = this->zoneServer.get();

	Locker clocker(managerData, player);

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, suiType, enclaveType, -1, false));
	box->setUsingObject(terminal);
	box->setForceCloseDistance(16.f);
	box->setOkButton(true, "@ok");
	box->setCancelButton(true, "@cancel");

	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	if (suiType == SUI_ARENA_CHAL_SCORES) {
		box->setPromptText("@pvp_rating:ch_rank_scores"); // A challenge score of zero denotes a rank that is meeting its challenges. A negative score denotes ranks that have missed a number of challenges. Once a rank reaches -8 points, every member of that rank will be demoted to rank zero. Every time a rank fails to meet at least one challenge during a challenge period (which occurs once every 30 hours), they incur a -1 penalty. Should no challenges be issued during a challenge period, that rank's challenge score will return to zero. If challenges were issued, the rank must answer at least 50% of the challenges for the score to return to zero, else the rank will incur a -1 score penalty even though some challenges may have been answered.
		box->setPromptTitle("@pvp_rating:ch_terminal_view_scores"); // View Challenge Scores

		Vector<ManagedReference<FrsRank*> >* rankData = managerData->getDarkRanks();

		clocker.release();

		for (int i = 2; i <= 11; i++) {
			ManagedReference<FrsRank*> frsRank = getFrsRank(COUNCIL_DARK, i);

			if (frsRank != nullptr) {
				Locker xlock(frsRank, player);
				String menuString = "Score for rank " + String::valueOf(i) + ":  " + String::valueOf(frsRank->getArenaChallengeScore());
				box->addMenuItem(menuString, i);
			}
		}
	} else if (suiType == SUI_ARENA_CHAL_VIEW) {
		if (getTotalOpenArenaChallenges(-1) <= 0) {
			player->sendSystemMessage("@pvp_rating:ch_no_challenges_to_view"); // There are no active challenges against any rank.
			return;
		}

		box->setPromptText("@pvp_rating:ch_select_active_challenges"); // Select the rank you wish to view challenges for. If a rank is not listed here, that rank has no active challenges.
		box->setPromptTitle("@pvp_rating:ch_terminal_view_challenges"); // View Issued Challenges

		for (int i = 2; i <= 11; i++) {
			if (getTotalOpenArenaChallenges(i) <= 0)
				continue;

			String menuString = "Rank " + String::valueOf(i);
			box->addMenuItem(menuString, i);
		}
	} else if (suiType == SUI_ARENA_CHAL_ISSUE) {
		if (rank < 1 || rank > 10) {
			player->sendSystemMessage("@pvp_rating:ch_terminal_cant_challenge_rank_bounds"); // You may not issue challenges at your current rank level.
			return;
		}

		if (managerData->getArenaStatus() != FrsManager::ARENA_OPEN) {
			player->sendSystemMessage("@pvp_rating:ch_terminal_arena_closed"); // The arena is not currently open for challenges.
			return;
		}

		if (!isEligibleForPromotion(player, rank + 1)) {
			player->sendSystemMessage("@pvp_rating:ch_terminal_notenoughexp"); // You do not currently qualify for a promotion into the next rank.
			return;
		}

		FrsRank* rankData = getFrsRank(COUNCIL_DARK, rank + 1);

		if (rankData == nullptr)
			return;

		clocker.release();

		Locker xlock(rankData, player);


		if (getAvailableRankSlots(rankData) >= 3) {
			player->sendSystemMessage("@pvp_rating:ch_terminal_no_need_challenge"); // You do not need to challenge the rank as there are enough open seats available. Use the Voting Terminal in the enclave to petition for one of these open slots.
			return;
		}

		xlock.release();

		Locker crosslock(managerData, player);

		if (!playerAbleToChallenge(player))
			return;

		ManagedReference<SuiMessageBox*> confirmBox = new SuiMessageBox(player, SuiWindowType::ENCLAVE_VOTING);
		confirmBox->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, suiType, enclaveType, -1, false));
		confirmBox->setPromptTitle("@pvp_rating:ch_terminal_issue_challenge"); // Issue Challenge
		confirmBox->setPromptText("@pvp_rating:ch_terminal_verify_challenge"); // Are you sure you wish to issue a challenge to the next rank? The rank you are challenging has 60 minutes to answer the challenge. Should you not be in the enclave when the challenge is accepted or should you be dead, you will concede the battle which will carry with it the same consequences as losing the battle. Should you leave the arena during the battle, you will also concede. If you are not in the arena when the challenge is accepted, you will be teleported into the arena as long as you are at least within the enclave.
		confirmBox->setUsingObject(terminal);
		confirmBox->setForceCloseDistance(16.f);
		ghost->addSuiBox(confirmBox);
		player->sendMessage(confirmBox->generateMessage());
		return;
	} else if (suiType == SUI_ARENA_CHAL_ACCEPT_LIST) {
		if (rank <= 1 || managerData->isFightingInArena(player->getObjectID()))
			return;

		box->setPromptText("@pvp_rating:ch_terminal_choose_challenge"); // Choose the challenger that you wish to combat in defense of your rank's honor!
		box->setPromptTitle("@pvp_rating:ch_terminal_accept_challenge"); // Accept a Challenge

		VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

		if (arenaChallenges->size() == 0)
			return;

		int chalCount = 0;

		for (int i = 0; i < arenaChallenges->size(); i++) {
			ManagedReference<ArenaChallengeData*> challengeData = arenaChallenges->get(i);

			if (challengeData->getChallengeRank() != rank)
				continue;

			if (challengeData->getChallengeAccepterID() != 0)
				continue;

			uint64 challengerID = challengeData->getChallengerID();

			ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
			String playerName = playerManager->getPlayerName(challengerID);

			if (playerName.isEmpty())
				continue;

			clocker.release();

			ManagedReference<CreatureObject*> challenger = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

			if (challenger == nullptr)
				continue;

			PlayerObject* cGhost = challenger->getPlayerObject();

			if (cGhost == nullptr)
				continue;

			Locker xlck(challenger, player);

			FrsData* playerData = cGhost->getFrsData();
			int challengerRank = playerData->getRank();

			xlck.release();

			if (challengerRank + 1 != rank)
				continue;

			uint64 startTime = challengeData->getChallengeStart();
			uint64 challengeDiff = Time().getMiliTime() - startTime;

			if (challengeDiff >= arenaChallengeDuration)
				continue;

			String rowString = playerName + " (" + getTimeString((arenaChallengeDuration - challengeDiff) / 1000) + " remaining on challenge)";

			box->addMenuItem(rowString, challengerID);
		}
	} else if (suiType == SUI_ARENA_CHAL_ACCEPT) {
		if (rank <= 1 || managerData->isFightingInArena(player->getObjectID()))
			return;

		if (getTotalOpenArenaChallenges(rank) <= 0) {
			player->sendSystemMessage("@pvp_rating:ch_terminal_no_challenges_for_rank"); // There are no pending challenges to accept for your rank.
			return;
		}

		ManagedReference<SuiMessageBox*> confirmBox = new SuiMessageBox(player, SuiWindowType::ENCLAVE_VOTING);
		confirmBox->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, suiType, enclaveType, -1, false));
		confirmBox->setPromptTitle("@pvp_rating:ch_terminal_accept_challenge"); // Accept a Challenge
		confirmBox->setPromptText("@pvp_rating:ch_terminal_verify_accept_challenge"); // Are you certain you wish to accept the responsibility of defending the honor of your rank against the challengers? The battle will be to the death. Should you be bested in combat, your punishment will be demotion to the rank below yours, while the challenger will receive your position in the rank. If you leave the arena during the battle you will concede the battle.
		confirmBox->setUsingObject(terminal);
		confirmBox->setForceCloseDistance(16.f);
		ghost->addSuiBox(confirmBox);
		player->sendMessage(confirmBox->generateMessage());
		return;
	} else if (suiType == SUI_ARENA_CHAL_STATUS) {
		uint64 lastOpen = managerData->getLastArenaOpenTime();
		uint64 miliDiff = Time().getMiliTime() - lastOpen;

		if (managerData->getArenaStatus() == ARENA_OPEN) {
			if (miliDiff >= arenaOpenInterval) {
				player->sendSystemMessage("@pvp_rating:ch_terminal_arena_close_imminent"); // The arena is about to close for challenges.
			} else {
				uint64 timeLeft = arenaOpenInterval - miliDiff;
				StringIdChatParameter param("@pvp_rating:ch_terminal_arena_close_in"); // The arena is currently open for challenges. Challenges can be issued for another %TO.
				param.setTO(getTimeString(timeLeft / 1000));
				player->sendSystemMessage(param);
			}
		} else {
			if (miliDiff >= (arenaOpenInterval + arenaClosedInterval)) {
				player->sendSystemMessage("@pvp_rating:ch_terminal_arena_open_imminent"); // The arena is about to open for challenges.
			} else {
				uint64 timeLeft = arenaOpenInterval + arenaClosedInterval - miliDiff;
				StringIdChatParameter param("@pvp_rating:ch_terminal_arena_open_in"); // The arena is currently closed. The arena will be open for challenges again in %TO.
				param.setTO(getTimeString(timeLeft / 1000));
				player->sendSystemMessage(param);
			}
		}

		return;
	} else {
		return;
	}

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleArenaChallengeIssueSui(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

	if (rank < 1 || rank > 10) {
		player->sendSystemMessage("@pvp_rating:ch_terminal_cant_challenge_rank_bounds"); // You may not issue challenges at your current rank level.
		return;
	}

	Locker clocker(managerData, player);

	if (managerData->getArenaStatus() != FrsManager::ARENA_OPEN) {
		player->sendSystemMessage("@pvp_rating:ch_terminal_arena_closed"); // The arena is not currently open for challenges.
		return;
	}

	if (!playerAbleToChallenge(player))
		return;

	clocker.release();

	if (!isEligibleForPromotion(player, rank + 1)) {
		player->sendSystemMessage("@pvp_rating:ch_terminal_notenoughexp"); // You do not currently qualify for a promotion into the next rank.
		return;
	}

	FrsRank* rankData = getFrsRank(COUNCIL_DARK, rank + 1);

	if (rankData == nullptr)
		return;

	Locker xlock(rankData, player);

	if (getAvailableRankSlots(rankData) >= 3) {
		player->sendSystemMessage("@pvp_rating:ch_terminal_no_need_challenge"); // You do not need to challenge the rank as there are enough open seats available. Use the Voting Terminal in the enclave to petition for one of these open slots.
		return;
	}

	ManagedReference<FrsManager*> strongMan = _this.getReferenceUnsafeStaticCast();
	ManagedReference<CreatureObject*> strongRef = player->asCreatureObject();
	int chalRank = rank + 1;

	Core::getTaskManager()->executeTask([strongMan, strongRef, chalRank] () {
		strongMan->issueArenaChallenge(strongRef, chalRank);
	}, "IssueArenaChallengeTask");
}

bool FrsManagerImplementation::rankHasOpenChallenges(int rank) {
	Locker locker(managerData);

	return getTotalOpenArenaChallenges(rank);
}

bool FrsManagerImplementation::isPlayerFightingInArena(uint64 playerID) {
	Locker locker(managerData);

	return managerData->isFightingInArena(playerID);
}

bool FrsManagerImplementation::isArenaOpen() {
	Locker locker(managerData);

	return managerData->getArenaStatus() == FrsManager::ARENA_OPEN;
}

bool FrsManagerImplementation::canPlayerAcceptArenaChallenge(CreatureObject* player) {
	Locker clocker(managerData, player);

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return false;

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

	return playerRank > 1 && getTotalOpenArenaChallenges(playerRank) > 0 && !hasPlayerAcceptedArenaChallenge(player) && !managerData->hasOpenArenaChallenge(player->getObjectID());
}

bool FrsManagerImplementation::canPlayerIssueArenaChallenge(CreatureObject* player) {
	Locker clocker(managerData, player);

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return false;

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

	return playerRank > 0 && playerRank < 11 && getArenaStatus() == FrsManager::ARENA_OPEN && isEligibleForPromotion(player, playerRank + 1) && playerAbleToChallenge(player);
}

void FrsManagerImplementation::forceArenaOpen(CreatureObject* player) {
	Locker clocker(managerData, player);

	if (getArenaStatus() == FrsManager::ARENA_OPEN)
		return;

	managerData->setArenaStatus(ARENA_OPEN);
	managerData->updateLastArenaOpenTime();

	player->sendSystemMessage("The arena has been opened.");
}

void FrsManagerImplementation::setupSuddenDeath(FrsRank* rankData, bool endPhase) {
	auto zoneServer = this->zoneServer.get();
	VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int i = 0; i < petitionerList->size(); i++) {
		VectorMapEntry<uint64, int>* entry = &petitionerList->elementAt(i);
		uint64 playerID = entry->getKey();

		String name = playerManager->getPlayerName(playerID);

		if (name.isEmpty())
			continue;

		ManagedReference<CreatureObject*> player = zoneServer->getObject(playerID).castTo<CreatureObject*>();

		if (player == nullptr)
			continue;

		modifySuddenDeathFlags(player, rankData, endPhase);

		if (endPhase)
			player->sendSystemMessage("@pvp_rating:sudden_death_timeout"); // You have survied the voting period for your rank. You are no longer at war with your fellow petitioners.
		else
			player->sendSystemMessage("@pvp_rating:sudden_death_start"); // Voting has begun for the rank you have petitioned for. All petitioning Jedi in your rank are now at war with one another. Should you defeat a fellow petitioning Jedi, you will gain all of their accumilated votes as well knock them out of the race. Take heed, however, as the same could happen to you.
	}
}

void FrsManagerImplementation::modifySuddenDeathFlags(CreatureObject* player, FrsRank* rankData, bool doRemove) {
	if (player == nullptr)
		return;

	uint64 playerID = player->getObjectID();
	auto zoneServer = this->zoneServer.get();

	VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int i = 0; i < petitionerList->size(); i++) {
		VectorMapEntry<uint64, int>* entry = &petitionerList->elementAt(i);
		uint64 petitionerID = entry->getKey();

		if (playerID == petitionerID)
			continue;

		String name = playerManager->getPlayerName(petitionerID);

		if (name.isEmpty())
			continue;

		ManagedReference<CreatureObject*> petitioner = zoneServer->getObject(petitionerID).castTo<CreatureObject*>();

		if (petitioner == nullptr)
			continue;

		ManagedReference<CreatureObject*> strongRef = player->asCreatureObject();

		Core::getTaskManager()->executeTask([strongRef, petitioner, doRemove] () {
			Locker locker(strongRef);
			Locker clocker(petitioner, strongRef);

			if (doRemove) {
				strongRef->removePersonalEnemyFlag(petitioner);
			} else {
				if (!strongRef->hasPersonalEnemyFlag(petitioner))
					strongRef->addPersonalEnemyFlag(petitioner, 0);
			}

			if (doRemove) {
				strongRef->removePersonalEnemyFlag(petitioner);
			} else {
				if (!petitioner->hasPersonalEnemyFlag(strongRef))
					petitioner->addPersonalEnemyFlag(strongRef, 0);
			}

			strongRef->sendPvpStatusTo(petitioner);
			petitioner->sendPvpStatusTo(strongRef);
		}, "AddPersonalEnemyFlagTask");
	}
}

void FrsManagerImplementation::handleSuddenDeathLoss(CreatureObject* player, ThreatMap* threatMap) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	uint32 totalDamage = threatMap->getTotalDamage();

	if (totalDamage == 0)
		return;

	Locker locker(player);

	FrsData* playerData = ghost->getFrsData();
	int curRank = playerData->getRank();

	locker.release();

	uint64 playerID = player->getObjectID();

	ManagedReference<FrsRank*> rankData = getFrsRank(COUNCIL_DARK, curRank + 1);

	if (rankData == nullptr)
		return;

	Locker lock(rankData);

	if (!rankData->isOnPetitionerList(playerID))
		return;

	int totalVotes = rankData->getPetitionerVotes(playerID);

	int totalContrib = 0;
	VectorMap<uint64, int> contribList;

	for (int i = 0; i < threatMap->size(); ++i) {
		ThreatMapEntry* entry = &threatMap->elementAt(i).getValue();
		CreatureObject* attacker = threatMap->elementAt(i).getKey();

		if (entry == nullptr || attacker == nullptr || attacker == player || !attacker->isPlayerCreature())
			continue;

		if (!player->isAttackableBy(attacker, true))
			continue;

		PlayerObject* attackerGhost = attacker->getPlayerObject();

		if (attackerGhost == nullptr)
			continue;

		if (ghost->getAccountID() == attackerGhost->getAccountID())
			continue;

		if (entry->getTotalDamage() <= 0)
			continue;

		if (!rankData->isOnPetitionerList(attacker->getObjectID()))
			continue;

		if (player->getDistanceTo(attacker) > 80.f)
			continue;

		contribList.put(attacker->getObjectID(), entry->getTotalDamage());

		totalContrib += entry->getTotalDamage();
	}

	if (contribList.size() == 0)
		return;

	auto zoneServer = this->zoneServer.get();

	if (totalContrib && (totalVotes > 0)) {
		for (int i = 0; i < contribList.size(); i++) {
			uint64 contribID = contribList.elementAt(i).getKey();
			int damageContrib = contribList.elementAt(i).getValue();
			float contribPercent = (float)damageContrib / (float)totalContrib;

			ManagedReference<CreatureObject*> contributor = zoneServer->getObject(contribID).castTo<CreatureObject*>();

			if (contributor == nullptr)
				continue;

			int curVotes = rankData->getPetitionerVotes(contribID);

			int votesGained = (int)floor((float)totalVotes * contribPercent);

			if (votesGained > 0)
				rankData->addToPetitionerList(contribID, curVotes + votesGained);

			StringIdChatParameter msgBody("@pvp_rating:dark_jedi_kill_won_votes"); // You have earned %DI votes for defeating %TT in combat.
			msgBody.setDI(votesGained);
			msgBody.setTT(player->getFirstName());

			contributor->sendSystemMessage(msgBody);
		}
	}

	VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();
	StringIdChatParameter msgBody("@pvp_rating:sudden_death_death"); // %TT has fallen to a fellow rank petitioner. Any votes they may have had accumilated have been divided amongs those that took part in the slaughter of %TT. Let this be a lesson in how the Council deals with failure.
	msgBody.setTT(player->getFirstName());

	for (int i = 0; i < petitionerList->size(); i++) {
		VectorMapEntry<uint64, int>* entry = &petitionerList->elementAt(i);
		uint64 petitionerID = entry->getKey();

		if (petitionerID == playerID)
			continue;

		ManagedReference<CreatureObject*> petitioner = zoneServer->getObject(petitionerID).castTo<CreatureObject*>();

		if (petitioner == nullptr)
			continue;

		petitioner->sendSystemMessage(msgBody);
	}

	player->sendSystemMessage("@pvp_rating:dark_jedi_kill_lost_votes"); // 	For dying to another petitioning Jedi, you have lost all of your votes. You have also relinquished your rights to petition during the current voting period.
	rankData->removeFromPetitionerList(playerID);
	modifySuddenDeathFlags(player, rankData, true);
}

ZoneServer* FrsManagerImplementation::getZoneServer() {
	return zoneServer.get();
}
