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
	loadLuaConfig();

	if (!frsEnabled)
		return;

	setupEnclaves();
	loadFrsData();

	Locker locker(managerData);

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

	frsEnabled = lua->getGlobalInt("frsEnabled");
	petitionInterval = lua->getGlobalLong("petitionInterval");
	votingInterval = lua->getGlobalLong("votingInterval");
	acceptanceInterval = lua->getGlobalLong("acceptanceInterval");
	maintenanceInterval = lua->getGlobalLong("maintenanceInterval");
	arenaOpenInterval = lua->getGlobalLong("arenaOpenInterval");
	arenaClosedInterval = lua->getGlobalLong("arenaClosedInterval");
	arenaChallengeDuration = lua->getGlobalLong("arenaChallengeDuration");
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

			ContainerPermissions* permissions = cell->getContainerPermissions();

			permissions->setInheritPermissionsFromParent(false);
			permissions->clearDefaultAllowPermission(ContainerPermissions::WALKIN);
			permissions->setDefaultDenyPermission(ContainerPermissions::WALKIN);

			for (int i = 11; i >= roomReq; i--) {
				permissions->setAllowPermission(groupName + String::valueOf(i), ContainerPermissions::WALKIN);
			}
		}
	}
}

void FrsManagerImplementation::playerLoggedIn(CreatureObject* player) {
	if (player == nullptr)
		return;

	Locker lock(player);

	deductDebtExperience(player);
	validatePlayerData(player);
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
		if (realPlayerRank == -1) {
			removeFromFrs(player);
		} else {
			setPlayerRank(player, realPlayerRank);
		}
	}

	if (realPlayerRank >= 0) {
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
	}
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
	else
		return;

	int curRank = playerData->getRank();

	if (curRank > 0) {
		ghost->removePermissionGroup(groupName + String::valueOf(curRank), true);

		ManagedReference<FrsRank*> rankData = getFrsRank(councilType, curRank);

		if (rankData != nullptr) {
			Locker clocker(rankData, player);
			rankData->removeFromPlayerList(playerID);
		}

		// Player is getting demoted, remove any pending petitions
		if (curRank > rank) {
			rankData = getFrsRank(councilType, curRank + 1);

			if (rankData != nullptr) {
				Locker clocker(rankData, player);
				rankData->removeFromPetitionerList(playerID);
			}
		}
	}

	playerData->setRank(rank);

	if (rank <= 0) {
		Locker clocker(managerData, player);
		managerData->removeChallengeTime(playerID);
	}

	if (rank >= 0)
		ghost->addPermissionGroup(groupName + String::valueOf(rank), true);

	if (rank > 0) {
		ManagedReference<FrsRank*> rankData = getFrsRank(councilType, rank);

		if (rankData != nullptr) {
			Locker clocker(rankData, player);
			rankData->addToPlayerList(playerID);
		}
	}

	updatePlayerSkills(player);
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

	if (curRank > 0) {
		ghost->removePermissionGroup(groupName + String::valueOf(curRank), true);

		ManagedReference<FrsRank*> rankData = getFrsRank(councilType, curRank);

		if (rankData != nullptr) {
			Locker clocker(rankData, player);
			rankData->removeFromPlayerList(playerID);
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
		VectorMap<uint, Reference<FrsRankingData*> > rankingData;

		if (councilType == COUNCIL_LIGHT)
			rankingData = lightRankingData;
		else if (councilType == COUNCIL_DARK)
			rankingData = darkRankingData;

		SkillManager* skillManager = zoneServer->getSkillManager();

		for (int i = rankingData.size() -1; i >= 0; i--) {
			Reference<FrsRankingData*> rankData = rankingData.get(i);
			String rankSkill = rankData->getSkillName();

			if (player->hasSkill(rankSkill)) {
				skillManager->surrenderSkill(rankSkill, player, true);
			}
		}

		return;
	}

	int skillRank = getSkillRank(skillName, councilType);

	if (skillRank < 0) {
		return;
	} else if (skillRank > 0) {
		demotePlayer(player);
	} else if (skillRank == 0) {
		removeFromFrs(player);
	}
}

int FrsManagerImplementation::getSkillRank(const String& skillName, int councilType) {
	VectorMap<uint, Reference<FrsRankingData*> > rankingData;

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
	VectorMap<uint, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;
	else
		return;

	for (int i = 0; i <= 11; i++) {
		Reference<FrsRankingData*> rankData = rankingData.get(i);
		String rankSkill = rankData->getSkillName();
		int rank = rankData->getRank();

		if (playerRank >= rank) {
			if (!player->hasSkill(rankSkill))
				player->addSkill(rankSkill, true);

			if (rank == 4 && !player->hasSkill("force_title_jedi_rank_04"))
				player->addSkill("force_title_jedi_rank_04", true);
			if (rank == 8 && !player->hasSkill("force_title_jedi_master"))
				player->addSkill("force_title_jedi_master", true);
		} else {
			if (player->hasSkill(rankSkill))
				player->removeSkill(rankSkill, true);
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

	String stfRank = "@force_rank:rank" + String::valueOf(newRank);
	String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();

	StringIdChatParameter param("@force_rank:rank_lost"); // You have been demoted to %TO.
	param.setTO(rankString);
	player->sendSystemMessage(param);
}

void FrsManagerImplementation::adjustFrsExperience(CreatureObject* player, int amount, bool sendSystemMessage) {
	if (player == nullptr || amount == 0)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	if (amount > 0) {
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
		timeLeft = "closed.";

	box->addMenuItem("Time Remaining: " + timeLeft);

	if (voteStatus != VOTING_CLOSED)
		box->addMenuItem("");

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
	VectorMap<uint, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;
	else
		return false;

	Reference<FrsRankingData*> rankData = rankingData.get(rank);
	String rankSkill = rankData->getSkillName();

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
	        return (playerRank == 9 || playerRank == 10) ? 1 : -1; // Players of rank 8-9 can particpate in votes of rank 8-9
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

	VectorMap<uint, Reference<FrsRankingData*> > rankingData;

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
			demotePlayer(challenged);

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

		bool votePassed = yesVotes > noVotes * 2;

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
			}
		}
	} else if (status == VOTING_OPEN) {
		VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();

		if (petitionerList->size() == 0) { // Empty petitioner list. This shouldn't happen, but just in case.
			rankData->resetVotingData();
			rankData->setVoteStatus(VOTING_CLOSED);
		} else {
			if (availSlots > 0) { // Add top X (where X = available slots) winners to winner list so they can accept next phase
				Vector<uint64>* winnerList = getTopVotes(rankData, availSlots);

				for (int i = 0; i < winnerList->size(); i++) {
					rankData->addToWinnerList(winnerList->get(i));
				}

				StringIdChatParameter mailBody("@force_rank:vote_win_body"); // Your Enclave peers have decided that you are worthy of a promotion within the hierarchy. You should return to your Enclave as soon as possible and select "Accept Promotion" at the voting terminal.
				sendMailToList(winnerList, "@force_rank:vote_win_sub", mailBody);

				rankData->setVoteStatus(WAITING);
			} else { // No available slot, top winner will be auto promoted next time a slot opens
				Vector<uint64>* winnerList = getTopVotes(rankData, 1);
				rankData->addToWinnerList(winnerList->get(0));

				StringIdChatParameter mailBody("@force_rank:vote_win_no_slot_body"); // You have won the vote by your Enclave peers in order to achieve a higher ranking. Unforuntately, there are no longer any open seats for you to fill. As a result, you will be offered a chance to accept an open seat the next time one becomes available.
				sendMailToList(winnerList, "@force_rank:vote_win_sub", mailBody);

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
		int highestIndex = 0;

		for (int j = 0; j < petitionerList->size(); j++) {
			VectorMapEntry<uint64, int> entry = petitionerList->elementAt(j);
			uint64 petitionerID = entry.getKey();
			uint32 petitionerVotes = entry.getValue();

			if (winnerList->contains(petitionerID))
				continue;

			if (petitionerVotes > highestVote || (petitionerVotes == highestVote && System::random(100) > 50)) {
				highestVote = petitionerVotes;
				highestID = petitionerID;
				highestIndex = j;
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

	ManagedReference<CreatureObject*> challenged = zoneServer->getObject(challengedID).castTo<CreatureObject*>();

	if (challenged == nullptr) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	PlayerObject* challengedGhost = challenged->getPlayerObject();

	if (ghost == nullptr)
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

	challengeData = new ChallengeVoteData(challengedID, ChallengeVoteData::VOTING_OPEN, challengedRank);
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

	if (managerData->hasDemotedRecently(player->getObjectID(), requestDemotionDuration)) {
		uint64 miliDiff = managerData->getDemoteDuration(player->getObjectID());
		uint64 timeLeft = requestDemotionDuration - miliDiff;

		StringIdChatParameter param("@force_rank:demote_too_soon"); // 	You cannot demote a member for another %TO
		param.setTO(getTimeString(timeLeft / 1000));
		player->sendSystemMessage(param);
		return;
	}

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

	if (managerData->hasDemotedRecently(player->getObjectID(), requestDemotionDuration)) {
		uint64 miliDiff = managerData->getDemoteDuration(player->getObjectID());
		uint64 timeLeft = requestDemotionDuration - miliDiff;

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
	managerData->updateChallengeTime(player->getObjectID());

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
	if (player->getParentID() == 0)
		return false;

	ManagedReference<BuildingObject*> bldg = player->getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();

	return bldg != nullptr && (bldg->getObjectID() == lightEnclave.get()->getObjectID() || bldg->getObjectID() == darkEnclave.get()->getObjectID());
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

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int i = 0; i < rankList->size(); i++) {
		uint64 playerID = rankList->elementAt(i);
		String playerName = playerManager->getPlayerName(playerID);

		if (playerName.isEmpty())
			continue;

		box->addMenuItem(playerName);
	}

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}
