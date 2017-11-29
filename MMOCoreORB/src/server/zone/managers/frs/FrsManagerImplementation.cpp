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
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"

void FrsManagerImplementation::initialize() {
	loadLuaConfig();

	if (!frsEnabled)
		return;

	setupEnclaves();
	loadFrsData();

	Time* lastTick = managerData->getLastMaintenanceTick();
	uint64 miliDiff = lastTick->miliDifference();

	rankMaintenanceTask = new RankMaintenanceTask(_this.getReferenceUnsafeStaticCast());

	if (miliDiff >= maintenanceInterval)
		rankMaintenanceTask->execute();
	else
		rankMaintenanceTask->schedule(maintenanceInterval - miliDiff);

	lastTick = managerData->getLastVoteStatusTick();
	miliDiff = lastTick->miliDifference();

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

	if (rankDatabase == NULL) {
		error("Could not load the frsmanager database.");
		return;
	}

	try {
		ObjectDatabaseIterator iterator(rankDatabase);

		uint64 objectID;

		while (iterator.getNextKey(objectID)) {
			Reference<FrsManagerData*> manData = Core::getObjectBroker()->lookUp(objectID).castTo<FrsManagerData*>();

			if (manData != NULL) {
				managerData = manData;
			}
		}
	} catch (DatabaseException& e) {
		error("Database exception in FrsManagerImplementation::loadFrsData(): "	+ e.getMessage());
	}

	if (managerData == NULL) {
		FrsManagerData* newManagerData = new FrsManagerData();
		ObjectManager::instance()->persistObject(newManagerData, 1, "frsmanager");

		managerData = newManagerData;
	}

	Vector<ManagedReference<FrsRank*> >* rankData = managerData->getLightRanks();

	if (rankData->size() == 0) {
		short newStatus = VOTING_CLOSED;

		for (int i = 1; i <= 11; i++) {
			FrsRank* newRank = new FrsRank(COUNCIL_LIGHT, i, newStatus);
			ObjectManager::instance()->persistObject(newRank, 1, "frsdata");
			rankData->add(newRank);
		}
	}

	rankData = managerData->getDarkRanks();

	if (rankData->size() == 0) {
		Vector<ManagedReference<FrsRank*> >* newRankData = NULL;
		short newStatus = VOTING_CLOSED;

		for (int i = 1; i <= 11; i++) {
			FrsRank* newRank = new FrsRank(COUNCIL_DARK, i, newStatus);
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

			Reference<FrsRankingData*> data = new FrsRankingData(rank, skillName, reqExp, playerCap);

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

			Reference<FrsRankingData*> data = new FrsRankingData(rank, skillName, reqExp, playerCap);

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
	lua = NULL;
}

void FrsManagerImplementation::setupEnclaves() {
	ManagedReference<BuildingObject*> enclaveBuilding = lightEnclave.get();

	if (enclaveBuilding != NULL)
		setupEnclaveRooms(enclaveBuilding, "LightEnclaveRank");

	enclaveBuilding = darkEnclave.get();

	if (enclaveBuilding != NULL)
		setupEnclaveRooms(enclaveBuilding, "DarkEnclaveRank");
}

FrsRank* FrsManagerImplementation::getFrsRank(short councilType, int rank) {
	if (rank < 0)
		return NULL;

	if (councilType == COUNCIL_LIGHT) {
		Vector<ManagedReference<FrsRank*> >* rankData = managerData->getLightRanks();

		for (int i = 0; i < rankData->size(); i++) {
			ManagedReference<FrsRank*> frsRank = rankData->get(i);

			if (frsRank->getRank() == rank)
				return frsRank;
		}
	} else if (councilType == COUNCIL_DARK) {
		Vector<ManagedReference<FrsRank*> >* rankData = managerData->getDarkRanks();

		for (int i = 0; i < rankData->size(); i++) {
			ManagedReference<FrsRank*> frsRank = rankData->get(i);

			if (frsRank->getRank() == rank)
				return frsRank;
		}
	}

	return NULL;
}


void FrsManagerImplementation::setupEnclaveRooms(BuildingObject* enclaveBuilding, const String& groupName) {
	for (int j = 1; j <= enclaveBuilding->getTotalCellNumber(); ++j) {
		ManagedReference<CellObject*> cell = enclaveBuilding->getCell(j);

		if (cell != NULL) {
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
	if (player == NULL)
		return;

	Locker lock(player);

	deductDebtExperience(player);
	validatePlayerData(player);
}

void FrsManagerImplementation::validatePlayerData(CreatureObject* player) {
	if (player == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	Locker lock(player);

	FrsData* playerData = ghost->getFrsData();
	int councilType = playerData->getCouncilType();
	int curPlayerRank = playerData->getRank();

	if (curPlayerRank == -1)
		return;

	int realPlayerRank = -1;
	uint64 playerID = player->getObjectID();

	for (int i = 1; i <= 11; i++) {
		FrsRank* rankData = getFrsRank(councilType, i);

		if (rankData == NULL)
			continue;

		if (rankData->isOnPlayerList(playerID)) {
			realPlayerRank = rankData->getRank();
			break;
		}
	}

	if (realPlayerRank != curPlayerRank) {
		setPlayerRank(player, realPlayerRank);

		if (realPlayerRank == -1)
			playerData->setCouncilType(0);
	}

	if (realPlayerRank >= 0) {
		if (councilType == COUNCIL_LIGHT && player->getFaction() != Factions::FACTIONREBEL)
			player->setFaction(Factions::FACTIONREBEL);
		else if (councilType == COUNCIL_DARK && player->getFaction() != Factions::FACTIONIMPERIAL)
		player->setFaction(Factions::FACTIONIMPERIAL);

		if (player->getFactionStatus() != FactionStatus::OVERT)
			player->setFactionStatus(FactionStatus::OVERT);
	}
}

void FrsManagerImplementation::setPlayerRank(CreatureObject* player, int rank) {
	if (player == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
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

		FrsRank* rankData = getFrsRank(councilType, curRank);

		if (rankData != NULL) {
			rankData->removeFromPlayerList(playerID);
		}
	}

	playerData->setRank(rank);

	if (rank <= 0)
		managerData->removeChallengeTime(playerID);

	if (rank >= 0)
		ghost->addPermissionGroup(groupName + String::valueOf(rank), true);

	if (rank > 0) {
		FrsRank* rankData = getFrsRank(councilType, rank);

		if (rankData != NULL) {
			rankData->addToPlayerList(playerID);
		}
	}

	updatePlayerSkills(player);
}

void FrsManagerImplementation::updatePlayerSkills(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
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
		} else {
			if (player->hasSkill(rankSkill))
				player->removeSkill(rankSkill, true);
		}
	}
}

void FrsManagerImplementation::promotePlayer(CreatureObject* player) {
	if (player == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	Locker lock(player);

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

	if (rank > 10)
		return;

	int newRank = rank + 1;
	setPlayerRank(player, newRank);

	String stfRank = "@force_rank:rank" + String::valueOf(newRank);
	String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();

	StringIdChatParameter param("@force_rank:rank_gained"); // You have achieved the Enclave rank of %TO.
	param.setTO(rankString);
	player->sendSystemMessage(param);
}

void FrsManagerImplementation::demotePlayer(CreatureObject* player) {
	if (player == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	Locker lock(player);

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

	if (rank == 0)
		return;

	int newRank = rank - 1;
	setPlayerRank(player, newRank);

	String stfRank = "@force_rank:rank" + String::valueOf(newRank);
	String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();

	StringIdChatParameter param("@force_rank:rank_lost"); // You have been demoted to %TO.
	param.setTO(rankString);
	player->sendSystemMessage(param);
}

void FrsManagerImplementation::adjustFrsExperience(CreatureObject* player, int amount) {
	if (player == NULL || amount == 0)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (amount > 0) {
		ghost->addExperience("force_rank_xp", amount, true);

		StringIdChatParameter param("@force_rank:experience_granted"); // You have gained %DI Force Rank experience.
		param.setDI(amount);

		player->sendSystemMessage(param);
	} else {
		FrsData* playerData = ghost->getFrsData();
		int rank = playerData->getRank();
		int councilType = playerData->getCouncilType();

		int curExperience = ghost->getExperience("force_rank_xp");

		// Ensure we dont go into the negatives
		if ((amount * -1) > curExperience)
			amount = curExperience * -1;

		ghost->addExperience("force_rank_xp", amount, true);

		StringIdChatParameter param("@force_rank:experience_lost"); // You have lost %DI Force Rank experience.
		param.setDI(amount * -1);
		player->sendSystemMessage(param);

		curExperience += amount;

		Reference<FrsRankingData*> rankingData = NULL;

		if (councilType == COUNCIL_LIGHT)
			rankingData = lightRankingData.get(rank);
		else if (councilType == COUNCIL_DARK)
			rankingData = darkRankingData.get(rank);

		if (rankingData == NULL)
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

	if (councilType == COUNCIL_LIGHT)
		rankData = managerData->getLightRanks();
	else if (councilType == COUNCIL_DARK)
		rankData = managerData->getDarkRanks();
	else
		return playerList;

	for (int i = 0; i < rankData->size(); i++) {
		ManagedReference<FrsRank*> frsRank = rankData->get(i);

		if (frsRank == NULL)
			continue;

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

	if (ghost == NULL)
		return;

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

	if (rank == 0)
		return;

	int maintXp = rank * 100;

	ChatManager* chatManager = zoneServer->getChatManager();

	StringIdChatParameter mailBody("@force_rank:xp_maintenance_body"); // You have lost %DI Force Rank experience. All members of Rank 1 or higher must pay experience each day to remain in their current positions. (Note: This loss may not take effect until your next login.)
	mailBody.setDI(maintXp);

	chatManager->sendMail("Enclave Records", "@force_rank:xp_maintenace_sub", mailBody, player->getFirstName(), NULL);

	addExperienceDebt(player, maintXp);
}

void FrsManagerImplementation::addExperienceDebt(CreatureObject* player, int amount) {
	uint64 playerID = player->getObjectID();

	int curDebt = managerData->getExperienceDebt(playerID);

	managerData->setExperienceDebt(playerID, curDebt + amount);
}

void FrsManagerImplementation::deductDebtExperience(CreatureObject* player) {
	uint64 playerID = player->getObjectID();

	Locker clocker(_this.getReferenceUnsafeStaticCast(), player);

	int curDebt = managerData->getExperienceDebt(playerID);

	if (curDebt <= 0)
		return;

	adjustFrsExperience(player, curDebt * -1);

	managerData->removeExperienceDebt(playerID);
}

bool FrsManagerImplementation::isValidFrsBattle(CreatureObject* attacker, CreatureObject* victim) {
	PlayerObject* attackerGhost = attacker->getPlayerObject();
	PlayerObject* victimGhost = victim->getPlayerObject();

	// No credit if they were killed by the attacker recently
	if (attackerGhost == NULL || victimGhost == NULL)
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

	if (attackerGhost == NULL || victimGhost == NULL)
		return 0;

	int targetRating = 0;
	int opponentRating = 0;

	PlayerObject* playerGhost = NULL;
	PlayerObject* opponentGhost = NULL;

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

	if (opponent == NULL)
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

	if (ghost == NULL)
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
			FrsRank* rankData = getFrsRank(enclaveType, i + 1);

			if (rankData == NULL || rankData->getVoteStatus() != VOTING_OPEN)
				continue;

			if (getVoteWeight(rank, i) > 0 && !hasPlayerVoted(player, rank)) {
				String voteString = elementList.get(i);
				voteString = voteString + " *";
				elementList.setElementAt(i, voteString);
			}
		}
	} else if (suiType == SUI_VOTE_ACCEPT_PROMOTE) {
		box->setPromptText("@force_rank:vote_promotion_select"); // Select the rank whose status you wish to view.
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

	if (ghost == NULL)
		return;

	FrsRank* rankData = getFrsRank(enclaveType, rank);

	if (rankData == NULL) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLESINGLEBUTTON);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setPromptText("Vote Status for Rank " + String::valueOf(rank));
	box->setPromptTitle("@force_rank:vote_status"); // Voting Status

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
	uint64 timeRemaining = interval - miliDiff;
	String timeLeft = "";

	if (timeRemaining > 0)
		timeLeft = getTimeString(timeRemaining / 1000);
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
					playerName = "UNKNOWN PLAYER";

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
					playerName = "UNKNOWN PLAYER";

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

	if (ghost == NULL)
		return;

	FrsRank* rankData = getFrsRank(enclaveType, rank);

	if (rankData == NULL) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

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
			playerName = "UNKNOWN PLAYER";

		box->addMenuItem(playerName);
	}

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::forcePhaseChange(CreatureObject* player, short enclaveType, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL || !ghost->isPrivileged())
		return;

	FrsRank* rankData = getFrsRank(enclaveType, rank);

	if (rankData == NULL) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	runVotingUpdate(rankData);
	player->sendSystemMessage("Rank " + String::valueOf(rank) + "'s phase has been changed.");
}

void FrsManagerImplementation::handleVoteRecordSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	Locker locker(_this.getReferenceUnsafeStaticCast());

	FrsRank* rankData = getFrsRank(enclaveType, rank);

	if (rankData == NULL) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

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

	VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();

	if (petitionerList->size() <= index)
		return;

	VectorMapEntry<uint64, int>* petitionerData = &petitionerList->elementAt(index);

	uint64 petitionerID = petitionerData->getKey();
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	String playerName = playerManager->getPlayerName(petitionerID);

	if (playerName.isEmpty()) {
		player->sendSystemMessage("Unable to find that player.");
		return;
	}

	int curVotes = petitionerData->getValue();

	rankData->addToPetitionerList(petitionerID, curVotes + 1);

	StringIdChatParameter voteCast("@force_rank:vote_cast"); // You cast your vote for %TO.
	voteCast.setTO(playerName);

	player->sendSystemMessage(voteCast);

	rankData->addToVotedList(playerID);
}

void FrsManagerImplementation::handleVotePetitionSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	FrsRank* rankData = getFrsRank(enclaveType, rank);

	if (rankData == NULL) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

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

	if (ghost == NULL)
		return;

	FrsRank* rankData = getFrsRank(enclaveType, rank);

	if (rankData == NULL) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

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

	if (ghost == NULL)
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

	if (skillManager == NULL)
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

bool FrsManagerImplementation::hasPlayerVoted(CreatureObject* player, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return true;

	FrsData* playerData = ghost->getFrsData();
	int councilType = playerData->getCouncilType();

	FrsRank* rankData = getFrsRank(councilType, rank);

	if (rankData == NULL)
		return false;

	return rankData->isOnVotedList(player->getObjectID());
}

int FrsManagerImplementation::getAvailableRankSlots(FrsRank* rankInfo) {
	short councilType = rankInfo->getCouncilType();
	int rank = rankInfo->getRank();

	VectorMap<uint, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;

	Reference<FrsRankingData*> rankData = rankingData.get(rank);

	if (rankData == NULL)
		return 0;

	return rankData->getPlayerCap() - rankInfo->getTotalPlayersInRank();
}

void FrsManagerImplementation::runVotingUpdate(FrsRank* rankInfo) {
	short councilType = rankInfo->getCouncilType();;
	int rank = rankInfo->getRank();

	ChatManager* chatManager = zoneServer->getChatManager();

	short status = rankInfo->getVoteStatus();
	int availSlots = getAvailableRankSlots(rankInfo);

	if (status == VOTING_CLOSED) {
		if (availSlots > 0) {
			SortedVector<uint64>* winnerList = rankInfo->getWinnerList();

			if (winnerList->size() > 0) {
				StringIdChatParameter mailBody("@force_rank:vote_seat_available_body"); // A council seat has become available for %TO. Since you won the last voting session, you may now claim this seat by going to the voting pedestal and selecting "Accept Promotion".
				String stfRank = "@force_rank:rank" + String::valueOf(rank);
				String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
				mailBody.setTO(rankString);
				sendMailToList(winnerList, "@force_rank:vote_seat_available_sub", mailBody);

				rankInfo->setVoteStatus(WAITING);
			} else {
				rankInfo->setVoteStatus(PETITIONING);
			}

		}
	} else if (status == PETITIONING) {
		int totalPetitioners = rankInfo->getTotalPetitioners();

		if (totalPetitioners == 0) { // No one petitioned
			if (availSlots == 0) { // No slots available, so clear vote data and set back to voting closed
				rankInfo->resetVotingData();
				rankInfo->setVoteStatus(VOTING_CLOSED);
			}
			// Slots available, leave the status the same to run the petitioning phase again
		} else {
			if (totalPetitioners <= availSlots || totalPetitioners == 1) { // More open slots than petitioners, or only one petitioner so everyone wins
				rankInfo->setVoteStatus(WAITING);

				VectorMap<uint64, int>* petitionerList = rankInfo->getPetitionerList();
				ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

				for (int i = 0; i < petitionerList->size(); i++) {
					VectorMapEntry<uint64, int>* entry = &petitionerList->elementAt(i);
					uint64 petitionerID = entry->getKey();

					String name = playerManager->getPlayerName(petitionerID);

					if (name.isEmpty())
						continue;

					rankInfo->addToWinnerList(petitionerID);
					chatManager->sendMail("Enclave Records", "@force_rank:vote_win_sub", "@force_rank:vote_win_body", name);
				}
			} else { // Move to voting phase to determine who should be promoted
				rankInfo->setVoteStatus(VOTING_OPEN);

				StringIdChatParameter mailBody("@force_rank:vote_cycle_begun_body"); // Voting has started for promotions into %TO. It is part of your Enclave duties to cast your vote for the petitioner who you deem most worthy. Voting time remaining: %TT
				String stfRank = "@force_rank:rank" + String::valueOf(rank);
				String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
				mailBody.setTO(rankString);
				mailBody.setTT(getTimeString(votingInterval / 1000));

				sendMailToVoters(councilType, rank, "@force_rank:vote_cycle_begun_sub", mailBody);
			}
		}
	} else if (status == VOTING_OPEN) {
		VectorMap<uint64, int>* petitionerList = rankInfo->getPetitionerList();

		if (petitionerList->size() == 0) { // Empty petitioner list. This shouldn't happen, but just in case.
			rankInfo->resetVotingData();
			rankInfo->setVoteStatus(VOTING_CLOSED);
		} else {
			if (availSlots > 0) { // Add top X (where X = available slots) winners to winner list so they can accept next phase
				Vector<uint64>* winnerList = getTopVotes(rankInfo, availSlots);

				for (int i = 0; i < winnerList->size(); i++) {
					rankInfo->addToWinnerList(winnerList->get(i));
				}

				StringIdChatParameter mailBody("@force_rank:vote_win_body"); // Your Enclave peers have decided that you are worthy of a promotion within the hierarchy. You should return to your Enclave as soon as possible and select "Accept Promotion" at the voting terminal.
				sendMailToList(winnerList, "@force_rank:vote_win_sub", mailBody);

				rankInfo->setVoteStatus(WAITING);
			} else { // No available slot, top winner will be auto promoted next time a slot opens
				Vector<uint64>* winnerList = getTopVotes(rankInfo, 1);
				rankInfo->addToWinnerList(winnerList->get(0));

				StringIdChatParameter mailBody("@force_rank:vote_win_no_slot_body"); // You have won the vote by your Enclave peers in order to achieve a higher ranking. Unforuntately, there are no longer any open seats for you to fill. As a result, you will be offered a chance to accept an open seat the next time one becomes available.
				sendMailToList(winnerList, "@force_rank:vote_win_sub", mailBody);

				rankInfo->setVoteStatus(VOTING_CLOSED); // Set status to closed without resetting voting data so that the winner will auto take the next available slot
			}

			checkForMissedVotes(rankInfo);
		}
	} else if (status == WAITING) {
		SortedVector<uint64>* winnerList = rankInfo->getWinnerList();

		if (winnerList->size() > 0) {
			StringIdChatParameter mailBody("@force_rank:acceptance_expired_body"); // Your deadline for accepting a promotion to %TO has passed. You will have to petition and then win another vote in order to achieve this rank.
			String stfRank = "@force_rank:rank" + String::valueOf(rank);
			String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
			mailBody.setTO(rankString);
			sendMailToList(winnerList, "@force_rank:acceptance_expired_sub", mailBody);
		}

		rankInfo->resetVotingData();
		rankInfo->setVoteStatus(VOTING_CLOSED);
	}

	rankInfo->updateLastTick();
}

void FrsManagerImplementation::checkForMissedVotes(FrsRank* rankInfo) {
	ChatManager* chatManager = zoneServer->getChatManager();
	short councilType = rankInfo->getCouncilType();
	int rank = rankInfo->getRank();

	Vector<uint64> missedVoteList;

	for (int i = 1; i <= 11; i++) {
		int voteWeight = getVoteWeight(i, rank);

		if (voteWeight <= 0)
			continue;

		FrsRank* rankData = getFrsRank(councilType, i);

		if (rankData == NULL)
			continue;

		int votePenalty = missedVotePenalty * pow(i, 2);

		SortedVector<uint64>* playerList = rankData->getPlayerList();

		for (int j = 0; j < playerList->size(); j++) {
			uint64 playerID = playerList->get(j);

			if (!rankInfo->isOnVotedList(playerID)) {
				ManagedReference<CreatureObject*> player = zoneServer->getObject(playerList->get(j)).castTo<CreatureObject*>();

				if (player != NULL) {
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

void FrsManagerImplementation::sendMailToVoters(short councilType, int rank, const String& sub, StringIdChatParameter& body) {
	ChatManager* chatManager = zoneServer->getChatManager();

	for (int i = 1; i <= 11; i++) {
		int voteWeight = getVoteWeight(i, rank);

		if (voteWeight <= 0)
			continue;

		FrsRank* rankData = getFrsRank(councilType, i);

		if (rankData == NULL)
			continue;

		SortedVector<uint64>* voterList = rankData->getPlayerList();

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

Vector<uint64>* FrsManagerImplementation::getTopVotes(FrsRank* rankInfo, int numWinners) {
	Vector<uint64>* winnerList = new Vector<uint64>();
	VectorMap<uint32, uint64> reverseList;
	VectorMap<uint64, int>* petitionerList = rankInfo->getPetitionerList();

	for (int i = 0; i < petitionerList->size(); i++) {
		VectorMapEntry<uint64, int>* entry = &petitionerList->elementAt(i);
		uint64 petitionerID = entry->getKey();
		uint32 petitionerVotes = entry->getValue();
		reverseList.put(petitionerVotes, petitionerID);
	}

	for (int i = 0; i < numWinners; i++) {
		VectorMapEntry<uint32, uint64>* entry = &reverseList.elementAt(i);
		uint64 petitionerID = entry->getValue();
		winnerList->add(petitionerID);
	}

	return winnerList;
}

void FrsManagerImplementation::sendChallengeVoteSUI(CreatureObject* player, SceneObject* terminal, short suiType, short enclaveType) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	Locker locker(player);

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, suiType, enclaveType, -1, false));
	box->setUsingObject(terminal);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setCancelButton(true, "@cancel");

	VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* lightChallenges = managerData->getLightChallenges();

	if (suiType == SUI_CHAL_VOTE_STATUS) {
		if (lightChallenges->size() == 0) {
			player->sendSystemMessage("@force_rank:no_challenge_votes"); // There are not any active no-confidence votes at this time.
			return;
		} else {
			box->setPromptText("@force_rank:challenge_vote_status_select"); // Select a no-confidence challenge you wish to view.
			box->setPromptTitle("@force_rank:challenge_vote_status_title"); // No-Confidence Vote Status

			ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

			for (int i = 0; i < lightChallenges->size(); i++) {
				uint64 playerID = lightChallenges->elementAt(i).getKey();
				String playerName = playerManager->getPlayerName(playerID);

				if (playerName.isEmpty())
					continue;

				box->addMenuItem(playerName, playerID);
			}
		}
	} else if (suiType == SUI_CHAL_VOTE_RECORD) {
		FrsData* playerData = ghost->getFrsData();
		int rank = playerData->getRank();

		if (rank < 1) {
			player->sendSystemMessage("@force_rank:insufficient_rank_vote"); // You have insufficient rank in order to vote.
			return;
		}

		VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* lightChallenges = managerData->getLightChallenges();

		if (lightChallenges->size() == 0) {
			player->sendSystemMessage("@force_rank:no_challenge_votes"); // There are not any active no-confidence votes at this time.
			return;
		}

		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		for (int i = 0; i < lightChallenges->size(); i++) {
			VectorMapEntry<uint64, ManagedReference<ChallengeVoteData*> >* challengeDataEntry = &lightChallenges->elementAt(i);

			uint64 playerID = challengeDataEntry->getKey();
			String playerName = playerManager->getPlayerName(playerID);

			if (playerName.isEmpty())
				continue;

			ChallengeVoteData* voteData = challengeDataEntry->getValue();
			int challengedRank = voteData->getPlayerRank();

			if (challengedRank < 1 || challengedRank > 11)
				continue;

			if (rank > challengedRank)
				continue;

			Time* startTime = voteData->getChallengeVoteStart();
			uint64 miliDiff = startTime->miliDifference();

			if (miliDiff > voteChallengeDuration)
				continue;

			box->addMenuItem(playerName, playerID);
		}

		box->setPromptText("@force_rank:challenge_vote_record_vote"); // Select the no-confidence challenge for which you wish to vote.
		box->setPromptTitle("@force_rank:challenge_vote_record_vote_title"); // No-Confidence Voting
	} else if (suiType == SUI_CHAL_VOTE_ISSUE) {
		FrsData* playerData = ghost->getFrsData();
		int rank = playerData->getRank();

		if (rank < 1) {
			player->sendSystemMessage("@force_rank:no_challenge_vote_low_rank"); // You must be at least Rank 1 in order to issue a no-confidence challenge vote.
			return;
		} else if (rank == 11) {
			player->sendSystemMessage("@force_rank:no_challenge_vote_leader"); // As the Council Leader, you cannot issue a no-confidence challenge vote.
			return;
		}

		VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* lightChallenges = managerData->getLightChallenges();

		if (lightChallenges->size() >= maxChallenges) {
			player->sendSystemMessage("@force_rank:vote_challenge_too_many"); // There are already a maximum number of no-confidence challenges active.
			return;
		}

		box->setPromptText("@force_rank:challenge_vote_select_name"); // Select the name of the Jedi you wish to issue a no-confidence challenge vote. The cost of calling for such a vote is 1000 Force Rank experience per rank challenged. If successful that Jedi will be demoted one rank.
		box->setPromptTitle("@force_rank:challenge_vote_select_name_title"); // No-Confidence Vote Selection

		FrsRank* rankData = getFrsRank(COUNCIL_LIGHT, rank + 1);
		SortedVector<uint64>* playerList = rankData->getPlayerList();

		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		for (int i = 0; i < playerList->size(); i++) {
			uint64 challengeID = playerList->elementAt(i);
			String playerName = playerManager->getPlayerName(challengeID);

			if (playerName.isEmpty())
				continue;

			box->addMenuItem(playerName, challengeID);
		}
	}

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleChallengeVoteIssueSui(CreatureObject* player, SceneObject* terminal, SuiBox* suiBox, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (index < 0)
		return;

	VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* lightChallenges = managerData->getLightChallenges();

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (listBox == NULL)
		return;

	uint64 challengedID = listBox->getMenuObjectID(index);

	if (challengedID == 0) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	if (lightChallenges->size() >= maxChallenges) {
		player->sendSystemMessage("@force_rank:vote_challenge_too_many"); // There are already a maximum number of no-confidence challenges active.
		return;
	}

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

	if (rank < 1) {
		player->sendSystemMessage("@force_rank:insufficient_rank_vote"); // You have insufficient rank in order to vote.
		return;
	}

	FrsRank* rankData = getFrsRank(COUNCIL_LIGHT, rank + 1);
	SortedVector<uint64>* playerList = rankData->getPlayerList();

	if (!playerList->contains(challengedID)) {
		player->sendSystemMessage("@force_rank:vote_challenge_not_correct_rank"); // You can only issue a no-confidence challenge against one rank above your own.
		return;
	}

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	String playerName = playerManager->getPlayerName(challengedID);

	if (lightChallenges->contains(challengedID)) {
		StringIdChatParameter param("@force_rank:vote_challenge_already_challenged"); // %TO is already in the process of a no-confidence challenge.
		param.setTO(playerName);
		player->sendSystemMessage(param);
		return;
	}

	uint64 playerID = player->getObjectID();

	if (managerData->hasChallengedRecently(playerID, voteChallengeDuration)) {
		Time* lastChallenge = managerData->getChallengeTime(playerID);
		uint64 miliDiff = lastChallenge->miliDifference();

		StringIdChatParameter param("@force_rank:challenge_too_soon"); // You cannot issue a no-confidence challenge against another member for another %TO
		param.setTO(getTimeString(miliDiff / 1000));
		player->sendSystemMessage(param);
	}

	Reference<FrsRankingData*> rankingData = lightRankingData.get(rank);
	int rankXpReq = rankingData->getRequiredExperience();

	int curXp = ghost->getExperience("force_rank_xp");

	if (curXp - voteChallengeCost < rankXpReq) {
		player->sendSystemMessage("@force_rank:vote_challenge_not_enough_xp"); // You do not have enough Force Rank experience to issue a no-confidence challenge. Note that you can not spend experience if it would cause you to lose rank.
		return;
	}

	ChallengeVoteData* voteData = new ChallengeVoteData(challengedID, 1, rank + 1);
	ObjectManager::instance()->persistObject(voteData, 1, "frsdata");
	managerData->addLightChallenge(challengedID, voteData);

	adjustFrsExperience(player, voteChallengeCost * -1);

	StringIdChatParameter param("@force_rank:vote_challenge_initiated"); // You issue a no-confidence challenge against %TO.
	param.setTO(playerName);
	player->sendSystemMessage(param);

	StringIdChatParameter mailBody("@force_rank:challenge_vote_begun_body"); // %TT has initiated a no-confidence challenge vote against %TO. It is your Enclave duty to vote for or against this motion as soon as possible.
	mailBody.setTO(playerName);
	mailBody.setTT(player->getFirstName());

	for (int i = 1; i <= rank; i++) {
		FrsRank* tempData = getFrsRank(COUNCIL_LIGHT, i);
		SortedVector<uint64>* playerList = rankData->getPlayerList();
		sendMailToList(playerList, "@force_rank:challenge_vote_begun_sub", mailBody);
	}
}

void FrsManagerImplementation::handleChallengeVoteStatusSui(CreatureObject* player, SceneObject* terminal, SuiBox* suiBox, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (index < 0)
		return;

	VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* lightChallenges = managerData->getLightChallenges();

	if (index >= lightChallenges->size()) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // 	That is an invalid selection.
		return;
	}

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (listBox == NULL)
		return;

	uint64 challengedID = listBox->getMenuObjectID(index);

	if (challengedID == 0 || !lightChallenges->contains(challengedID)) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // 	That is an invalid selection.
		return;
	}

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	String playerName = playerManager->getPlayerName(challengedID);

	if (playerName.isEmpty()) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // 	That is an invalid selection.
		return;
	}

	ManagedReference<ChallengeVoteData*> voteData = lightChallenges->get(challengedID);

	int voteStatus = voteData->getStatus();

	String voteStatusString = "Voting Complete";

	if (voteStatus == 1)
		voteStatusString = "Voting Open";

	Time* startTime = voteData->getChallengeVoteStart();
	uint64 miliDiff = startTime->miliDifference();
	String timeLeftString = "closed.";

	if (voteChallengeDuration > miliDiff)
		timeLeftString = getTimeString((voteChallengeDuration - miliDiff) / 1000);

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLESINGLEBUTTON);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setPromptText("No-Confidence Challenge Status for " + playerName);
	box->setPromptTitle("@force_rank:challenge_vote_status_title"); // No-Confidence Vote Status
	box->addMenuItem("Current Stage: " + voteStatusString);
	box->addMenuItem("Time Remaining: " + timeLeftString);
	box->addMenuItem("Votes For: " + String::valueOf(voteData->getTotalYesVotes()));
	box->addMenuItem("Votes Against: " + String::valueOf(voteData->getTotalNoVotes()));

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleChallengeVoteRecordSui(CreatureObject* player, SceneObject* terminal, SuiBox* suiBox, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (index < 0)
		return;

	VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* lightChallenges = managerData->getLightChallenges();

	if (index >= lightChallenges->size()) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // 	That is an invalid selection.
		return;
	}

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (listBox == NULL)
		return;

	uint64 challengedID = listBox->getMenuObjectID(index);

	if (challengedID == 0 || !lightChallenges->contains(challengedID)) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // 	That is an invalid selection.
		return;
	}

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
	String playerName = playerManager->getPlayerName(challengedID);

	if (playerName.isEmpty()) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // 	That is an invalid selection.
		return;
	}

	uint64 voterID = player->getObjectID();
	ManagedReference<ChallengeVoteData*> voteData = lightChallenges->get(challengedID);

	if (voteData->hasVoted(voterID)) {
		player->sendSystemMessage("@force_rank:already_voted"); // 	You have already voted.
		return;
	}

	Time* startTime = voteData->getChallengeVoteStart();
	uint64 miliDiff = startTime->miliDifference();

	if (miliDiff > voteChallengeDuration) {
		player->sendSystemMessage("@force_rank:vote_time_expired"); // Time has expired for the voting process.
		return;
	}

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(zoneServer, SUI_CHAL_VOTE_RECORD_CONFIRM, COUNCIL_LIGHT, -1, false));
	box->setUsingObject(terminal);
	box->setForceCloseDistance(16.f);
	box->setOkButton(true, "@ok");
	box->setCancelButton(true, "@cancel");
	box->setPromptText("Do you vote for or against the removal of " + playerName + "?");
	box->setPromptTitle("@force_rank:challenge_vote_record_vote_title"); // No-Confidence Voting
	box->addMenuItem("@force_rank:vote_for", challengedID); // For
	box->addMenuItem("@force_rank:vote_against", challengedID); // Against

	box->setUsingObject(terminal);
	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleChallengeVoteRecordConfirmSui(CreatureObject* player, SceneObject* terminal, SuiBox* suiBox, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (index < 0)
		return;

	if (index > 1) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // 	That is an invalid selection.
		return;
	}

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (listBox == NULL)
		return;

	uint64 challengedID = listBox->getMenuObjectID(index);

	VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* lightChallenges = managerData->getLightChallenges();

	if (!lightChallenges->contains(challengedID)) {
		player->sendSystemMessage("@force_rank:invalid_selection"); // That is an invalid selection.
		return;
	}

	ManagedReference<ChallengeVoteData*> voteData = lightChallenges->get(challengedID);

	Time* startTime = voteData->getChallengeVoteStart();
	uint64 miliDiff = startTime->miliDifference();

	if (miliDiff > voteChallengeDuration) {
		player->sendSystemMessage("@force_rank:vote_time_expired"); // Time has expired for the voting process.
		return;
	}

	uint64 voterID = player->getObjectID();

	if (voteData->hasVoted(voterID)) {
		player->sendSystemMessage("@force_rank:already_voted"); // You have already voted.
		return;
	}

	if (index == 0)
		voteData->addYesVote(voterID);
	else
		voteData->addNoVote(voterID);

	player->sendSystemMessage("@force_rank:challenge_vote_success"); // You have successfully cast your no-confidence vote.
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
	if (enclave == NULL)
		return 0;

	if (enclave->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/light_enclave.iff"))
		return FrsManager::COUNCIL_LIGHT;
	else if (enclave->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/dark_enclave.iff"))
		return FrsManager::COUNCIL_DARK;

	return 0;
}

void FrsManagerImplementation::checkLightChallenges() {
	VectorMap<uint64, ManagedReference<ChallengeVoteData*> >* lightChallenges = managerData->getLightChallenges();

	if (lightChallenges->size() <= 0)
		return;

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	for (int i = 0; i < lightChallenges->size(); i++) {
		VectorMapEntry<uint64, ManagedReference<ChallengeVoteData*> >* challengeDataEntry = &lightChallenges->elementAt(i);

		uint64 playerID = challengeDataEntry->getKey();
		ChallengeVoteData* voteData = challengeDataEntry->getValue();
		int challengedRank = voteData->getPlayerRank();

		String playerName = playerManager->getPlayerName(playerID);

		if (playerName.isEmpty()) {
			managerData->removeLightChallenge(playerID);
			continue;
		}

		FrsRank* rankData = getFrsRank(COUNCIL_LIGHT, challengedRank);
		SortedVector<uint64>* playerList = rankData->getPlayerList();
		int voteStatus = voteData->getStatus();

		if (voteStatus == ChallengeVoteData::VOTING_OPEN) {
			if (!playerList->contains(playerID)) {
				StringIdChatParameter mailBody("@force_rank:challenge_vote_cancelled_body"); // The no-confidence vote on %TO has been cancelled due to a change in the member's ranking.
				mailBody.setTO(playerName);

				for (int i = 1; i <= challengedRank; i++) {
					FrsRank* tempData = getFrsRank(COUNCIL_LIGHT, i);
					SortedVector<uint64>* playerList = rankData->getPlayerList();
					sendMailToList(playerList, "@force_rank:challenge_vote_begun_sub", mailBody);
				}

				managerData->removeLightChallenge(playerID);
				continue;
			}

			uint64 timeSinceStart = voteData->getChallengeVoteStart()->miliDifference();

			if (timeSinceStart >= voteChallengeDuration) {
				int yesVotes = voteData->getTotalYesVotes();
				int noVotes = voteData->getTotalNoVotes();
				bool success = yesVotes >= (noVotes * 2);

				ManagedReference<CreatureObject*> challengedPlayer = zoneServer->getObject(playerID).castTo<CreatureObject*>();

				if (challengedPlayer == NULL) {
					managerData->removeLightChallenge(playerID);
					continue;
				}

				if (success) {
					StringIdChatParameter mailBody("@force_rank:challenge_vote_success_body"); // The vote against %TT has succeeded with %TO votes for and %DI votes against.
					mailBody.setTT(playerName);
					mailBody.setTO(String::valueOf(yesVotes));
					mailBody.setDI(noVotes);

					demotePlayer(challengedPlayer);

					for (int i = 1; i <= challengedRank; i++) {
						FrsRank* tempData = getFrsRank(COUNCIL_LIGHT, i);
						SortedVector<uint64>* playerList = rankData->getPlayerList();
						sendMailToList(playerList, "@force_rank:challenge_vote_success_sub", mailBody);
					}
				} else {
					StringIdChatParameter mailBody("@force_rank:challenge_vote_fail_body"); // The vote against %TT has failed to pass with %TO votes for and %DI votes against. (Note that for a vote to succeed, two-thirds or more must be for it.)
					mailBody.setTT(playerName);
					mailBody.setTO(String::valueOf(yesVotes));
					mailBody.setDI(noVotes);

					for (int i = 1; i <= challengedRank; i++) {
						FrsRank* tempData = getFrsRank(COUNCIL_LIGHT, i);
						SortedVector<uint64>* playerList = rankData->getPlayerList();
						sendMailToList(playerList, "@force_rank:challenge_vote_fail_sub", mailBody);
					}
				}

				voteData->setStatus(ChallengeVoteData::VOTING_CLOSED);
			}
		} else {
			uint64 timeSinceStart = voteData->getChallengeVoteStart()->miliDifference();

			// 1 hour buffer to show votes after voting is over
			if (timeSinceStart + (3600 * 1000) >= voteChallengeDuration) {
				managerData->removeLightChallenge(playerID);
				continue;
			}
		}
	}
}

void FrsManagerImplementation::performArenaMaintenance() {
	Time* lastOpen = managerData->getLastArenaOpenTime();
	uint64 miliDiff = lastOpen->miliDifference();
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

	if (arenaChallenges->size() == 0)
		return;

	bool challengeEnded = false;

	// Not all challenges will end at the interval, challenges started towards the end of the interval will continue until their duration is up
	for (int i = arenaChallenges->size() - 1; i >= 0; i--) {
		ManagedReference<ArenaChallengeData*> challengeData = arenaChallenges->get(i);

		Time* startTime = challengeData->getChallengeStart();
		uint64 challengeDiff = startTime->miliDifference();

		if (challengeDiff >= arenaChallengeDuration) {
			challengeEnded = true;

			uint64 challengeAccepterID = challengeData->getChallengeAccepterID();
			uint64 challengerID = challengeData->getChallengerID();

			if (challengeAccepterID != 0) {
				managerData->removeArenaFighter(challengerID);
				managerData->removeArenaFighter(challengeAccepterID);

				ManagedReference<CreatureObject*> player = zoneServer->getObject(challengeAccepterID).castTo<CreatureObject*>();

				if (player != NULL)
					player->removePersonalEnemyFlag(challengerID);

					player = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

					if (player != NULL)
						player->removePersonalEnemyFlag(challengeAccepterID);
			} else {
				FrsRank* rankData = getFrsRank(COUNCIL_DARK, challengeData->getChallengeRank());

				if (rankData == NULL)
					return;

				int challengeRank = challengeData->getChallengeRank();

				SortedVector<uint64>* playerList = rankData->getPlayerList();

				ManagedReference<CreatureObject*> challenger = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

				if (challenger != NULL) {
					StringIdChatParameter mailBody("@pvp_rating:challenge_concluded_timeout"); // Although a challenge had been issued, no one in rank %DI saw fit to defend the honor of their rank by accepting the challenge issued by %TT. The challenge has thus expired.
					mailBody.setTT(challenger->getFirstName());
					mailBody.setDI(challengeRank);
					sendMailToList(playerList, "@pvp_rating:challenge_timout_subject_header", mailBody);

					challenger->sendSystemMessage(mailBody);
				}
			}

			arenaChallenges->remove(i);
		}
	}

	// This block should only execute once there are no challenges left
	if (arenaStatus == ARENA_CLOSED && arenaChallenges->size() == 0 && (justClosedArena || challengeEnded)) {
		updateArenaScores();
	}
}

void FrsManagerImplementation::updateArenaScores() {
	for (int i = 2; i <= 11; i++) {
		FrsRank* rankData = getFrsRank(COUNCIL_DARK, i);

		if (rankData == NULL)
			continue;

		int challenges = rankData->getArenaChallengesThisPhase();
		int challengesAccepted = rankData->getArenaChallengesAcceptedThisPhase();
		int challengeScore = rankData->getArenaChallengeScore();
		float answeredRatio = (float)challengesAccepted / (float)challenges;

		if (answeredRatio >= 0.5f || challenges == 0) {
			rankData->setArenaChallengeScore(0);
		} else {
			challengeScore -= 1;
		}

		if (challengeScore <= -8) {
			Vector<uint64> memberList = getPlayerListByCouncil(COUNCIL_DARK);

			StringIdChatParameter mailBody("@force_rank:ch_terminal_demote_rank_penalty"); // 	The members of rank %DI have failed to answer numerous challenges issued by the Dark Jedi of the enclave. As a result, the entire rank has been demoted to rank zero. Weakness cannot be tolerated in the Council.
			mailBody.setDI(i);
			sendMailToList(&memberList, "@force_rank:ch_terminal_demote_subject", mailBody);

			SortedVector<uint64>* playerList = rankData->getPlayerList();

			for (int j = playerList->size() - 1; j >= 0; j--) {
				uint64 playerID = playerList->get(j);
				ManagedReference<CreatureObject*> player = zoneServer->getObject(playerList->get(j)).castTo<CreatureObject*>();

				if (player != NULL) {
					Locker lock(player);
					setPlayerRank(player, 0);
				}
			}

			challengeScore = 0;
		}

		rankData->setArenaChallengeScore(challengeScore);
		rankData->setArenaChallengesThisPhase(0);
		rankData->setArenaChallengesAcceptedThisPhase(0);
	}
}

void FrsManagerImplementation::issueArenaChallenge(CreatureObject* player, int rank) {
	FrsRank* rankData = getFrsRank(COUNCIL_DARK, rank);

	if (rankData == NULL)
		return;

	uint64 playerID = player->getObjectID();

	ArenaChallengeData* challengeData = new ArenaChallengeData(playerID, rank);
	ObjectManager::instance()->persistObject(challengeData, 1, "frsdata");
	managerData->addArenaChallenge(playerID, challengeData);

	managerData->updateChallengeTime(playerID);

	StringIdChatParameter sysMsg("@pvp_rating:challenge_issued_challenger"); // You have issued a challenge against rank %DI. Any member of that rank may accept your challenge during the next 60 minutes. Should a rank member accept your challenge and you are not present in the enclave (or you are dead), you will lose the challenge by default. If you are not in the arena hall when the challange is accepted you will be teleported there as long as you are within the walls of the enclave. Should you win the challenge, you will be granted a position in rank %DI. Should you lose the challenge, you will lose a quantity of Force RankXP.
	sysMsg.setDI(rank);

	player->sendSystemMessage(sysMsg);

	SortedVector<uint64>* playerList = rankData->getPlayerList();

	StringIdChatParameter mailBody("@pvp_rating:challenge_issued_rank"); //	%TT has issued a challenge against your rank! If you wish to defend the honor of your rank, find the challenge terminal in the Dark Jedi enclave and accept the challenge. You have 60 minutes to do so, starting now. Should you accept and lose the challenge, you will be demoted into the rank below yours, while %TT will take your position.
	mailBody.setTT(player->getFirstName());

	sendMailToList(playerList, "@pvp_rating:challenge_issued_subject_header", mailBody);

	ChatManager* chatManager = zoneServer->getChatManager();
	Locker clocker(chatManager, _this.getReferenceUnsafeStaticCast());

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	PlayerMap* playerMap = chatManager->getPlayerMap();

	for (int j = playerList->size() - 1; j >= 0; j--) {
		uint64 memberID = playerList->get(j);
		String playerName = playerManager->getPlayerName(memberID);

		ManagedReference<CreatureObject*> rankMember = playerMap->get(playerName);

		if (rankMember != NULL && rankMember->isOnline()) {
			rankMember->sendSystemMessage(mailBody);
		}
	}
}

void FrsManagerImplementation::acceptArenaChallenge(CreatureObject* player, uint64 challengerID) {
	if (!managerData->hasOpenArenaChallenge(challengerID))
		return;

	ManagedReference<ArenaChallengeData*> challengeData = managerData->getArenaChallenge(challengerID);

	if (challengeData->getChallengeAccepterID() != 0)
		return;

	int challengeRank = challengeData->getChallengeRank();

	FrsRank* rankData = getFrsRank(COUNCIL_DARK, challengeRank);

	if (rankData == NULL)
		return;

	ManagedReference<CreatureObject*> challenger = zoneServer->getObject(challengerID).castTo<CreatureObject*>();

	if (challenger == NULL)
		return;

	challengeData->setChallengeAccepterID(player->getObjectID());

	if (!challenger->isOnline() || challenger->isDead() || !isPlayerInEnclave(challenger)) {
		if (challenger->isOnline()) {
			challenger->sendSystemMessage("@pvp_rating:ch_terminal_challenger_forfeit_ch"); // Since you were not in the enclave, or you were dead, when your challenge was accepted, you have conceded the battle. Your honor has been tarnished significantly by your actions.
		}

		handleDarkCouncilDeath(player, challenger, true);

		player->sendSystemMessage("@pvp_rating:ch_terminal_challenger_forfeit"); // The challenger has forfeit this battle by not being present and alive in the enclave to complete the duel. Honor has been restored to your rank.

		ChatManager* chatManager = zoneServer->getChatManager();

		chatManager->sendMail("Enclave Records", "@pvp_rating:challenge_concluded_subject_header", "@pvp_rating:ch_terminal_challenger_forfeit_ch", challenger->getFirstName());

		return;
	}

	SortedVector<uint64>* playerList = rankData->getPlayerList();

	StringIdChatParameter mailBody("@pvp_rating:challenge_accepted"); // %TU has stepped forward to accept a challenge against rank %DI, issued by %TT. A battle to the death is commencing in the arena at the hidden enclave.
	mailBody.setTU(player->getFirstName());
	mailBody.setTT(challenger->getFirstName());
	mailBody.setDI(challengeRank);

	challenger->sendSystemMessage(mailBody);

	sendMailToList(playerList, "@pvp_rating:challenge_accepted_subject_header", mailBody);

	ChatManager* chatManager = zoneServer->getChatManager();
	Locker clocker(chatManager, _this.getReferenceUnsafeStaticCast());

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	PlayerMap* playerMap = chatManager->getPlayerMap();

	for (int j = playerList->size() - 1; j >= 0; j--) {
		uint64 memberID = playerList->get(j);
		String playerName = playerManager->getPlayerName(memberID);

		ManagedReference<CreatureObject*> rankMember = playerMap->get(playerName);

		if (rankMember != NULL && rankMember->isOnline()) {
			rankMember->sendSystemMessage(mailBody);
		}
	}

	clocker.release();

	if (!isPlayerInDarkArena(player))
		teleportPlayerToDarkArena(player);

	if (!isPlayerInDarkArena(challenger))
		teleportPlayerToDarkArena(challenger);

	managerData->addArenaFighter(player->getObjectID());
	managerData->addArenaFighter(challenger->getObjectID());

	Locker xlock(player, _this.getReferenceUnsafeStaticCast());
	player->addPersonalEnemyFlag(challenger, 0);
	xlock.release();

	Locker crosslock(challenger, _this.getReferenceUnsafeStaticCast());
	challenger->addPersonalEnemyFlag(player, 0);
}

bool FrsManagerImplementation::isPlayerInEnclave(CreatureObject* player) {
	if (player->getParentID() == 0)
		return false;

	ManagedReference<BuildingObject*> bldg = player->getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();

	if (bldg == NULL || (bldg->getObjectID() != lightEnclave.get()->getObjectID() && bldg->getObjectID() != darkEnclave.get()->getObjectID()))
		return false;

	return true;
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

void FrsManagerImplementation::teleportPlayerToDarkArena(CreatureObject* player) {
	if (!isPlayerInEnclave(player))
		return;

	float randX = -13.f + System::random(26);
	float randY = -86.f + System::random(26);

	player->teleport(randX, -47.424, randY, ARENA_CELL);

	UpdateTransformWithParentMessage* message = new UpdateTransformWithParentMessage(player);
	player->broadcastMessage(message, false);
}

int FrsManagerImplementation::getTotalOpenArenaChallenges(int rank) {
	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	if (arenaChallenges->size() == 0)
		return 0;

	int chalCount = 0;

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> challengeData = arenaChallenges->get(i);

		if (rank > 1 && challengeData->getChallengeRank() != rank)
			continue;

		if (challengeData->getChallengeAccepterID() == 0)
			chalCount++;
	}

	return chalCount;
}

bool FrsManagerImplementation::canPlayerIssueArenaChallenge(CreatureObject* player) {
	uint64 playerID = player->getObjectID();

	if (managerData->hasOpenArenaChallenge(playerID))
		return false;

	if (managerData->hasChallengedRecently(playerID, arenaChallengeCooldown))
		return false;

	return true;
}

bool FrsManagerImplementation::hasPlayerAcceptedArenaChallenge(CreatureObject* player) {
	uint64 playerID = player->getObjectID();
	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	if (arenaChallenges->size() == 0)
		return false;

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> challengeData = arenaChallenges->get(i);

		if (challengeData->getChallengeAccepterID() == playerID)
			return true;
	}

	return false;
}

void FrsManagerImplementation::sendArenaChallengeSUI(CreatureObject* player, SceneObject* terminal, short suiType, short enclaveType) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	Locker locker(player);

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

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

		for (int i = 2; i <= 11; i++) {
			ManagedReference<FrsRank*> frsRank = getFrsRank(COUNCIL_DARK, i);
			String menuString = "Score for rank " + String::valueOf(i) + ":  " + String::valueOf(frsRank->getArenaChallengeScore());
			box->addMenuItem(menuString, i);
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

		if (getAvailableRankSlots(rankData) >= 1) {
			player->sendSystemMessage("@pvp_rating:ch_terminal_no_need_challenge"); // You do not need to challenge the rank as there are enough open seats available. Use the Voting Terminal in the enclave to petition for one of these open slots.
			return;
		}

		if (!canPlayerIssueArenaChallenge(player))
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

			Time* startTime = challengeData->getChallengeStart();
			uint64 challengeDiff = startTime->miliDifference();

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
		Time* lastOpen = managerData->getLastArenaOpenTime();
		uint64 miliDiff = lastOpen->miliDifference();

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

void FrsManagerImplementation::handleArenaChallengeViewSui(CreatureObject* player, SceneObject* terminal, SuiBox* suiBox, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (index < 0)
		return;

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (listBox == NULL)
		return;

	int rank = listBox->getMenuObjectID(index);

	if (getTotalOpenArenaChallenges(rank) <= 0)
		return;

	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLESINGLEBUTTON);
	box->setOkButton(true, "@ok");
	box->setForceCloseDistance(16.f);
	box->setPromptText("@pvp_rating:ch_terminal_pending"); // Pending challenges for selected rank:
	box->setPromptTitle("@pvp_rating:ch_terminal_view_challenges"); // View Issued Challenges

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

		Time* startTime = challengeData->getChallengeStart();
		uint64 challengeDiff = startTime->miliDifference();

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

void FrsManagerImplementation::handleArenaChallengeIssueSui(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	FrsData* playerData = ghost->getFrsData();
	int rank = playerData->getRank();

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

	if (rankData == NULL)
		return;

	if (getAvailableRankSlots(rankData) >= 1) {
		player->sendSystemMessage("@pvp_rating:ch_terminal_no_need_challenge"); // You do not need to challenge the rank as there are enough open seats available. Use the Voting Terminal in the enclave to petition for one of these open slots.
		return;
	}

	if (!canPlayerIssueArenaChallenge(player))
		return;

	issueArenaChallenge(player, rank + 1);
}

void FrsManagerImplementation::handleArenaChallengeAcceptListSui(CreatureObject* player, SceneObject* terminal, SuiBox* suiBox, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (index < 0)
		return;

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (listBox == NULL)
		return;

	uint64 challengerID = listBox->getMenuObjectID(index);

	acceptArenaChallenge(player, challengerID);
}

void FrsManagerImplementation::handleDarkCouncilDeath(CreatureObject* killer, CreatureObject* victim, bool forfeit) {
	if (killer == NULL || victim == NULL)
		return;

	uint64 killerID = killer->getObjectID();
	uint64 victimID = victim->getObjectID();

	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();
	ManagedReference<ArenaChallengeData*> challengeData = NULL;
	bool isVictimChallenger = false;

	for (int i = 0; i < arenaChallenges->size(); i++) {
		ManagedReference<ArenaChallengeData*> tempData = arenaChallenges->get(i);
		uint64 challengerID = tempData->getChallengerID();
		uint64 accepterID = tempData->getChallengeAccepterID();

		if (killerID == challengerID && victimID == accepterID) {
			challengeData = tempData;
		} else if (killerID == accepterID && victimID == challengerID) {
			challengeData = tempData;
			isVictimChallenger = true;
		}
	}

	if (challengeData == NULL)
		return;

	uint64 challengerID = challengeData->getChallengerID();
	uint64 accepterID = challengeData->getChallengeAccepterID();
	int challengeRank = challengeData->getChallengeRank();

	managerData->removeArenaFighter(challengerID);
	managerData->removeArenaFighter(accepterID);

	Core::getTaskManager()->executeTask([=] () {
		Locker locker(_this.getReferenceUnsafeStaticCast());

		int killerXp = calculatePvpExperienceChange(killer, victim, 1.0f, false);
		int victimXp = calculatePvpExperienceChange(killer, victim, 1.0f, true);

		Locker clocker(killer, _this.getReferenceUnsafeStaticCast());

		if (!forfeit)
			adjustFrsExperience(killer, killerXp);

		killer->removePersonalEnemyFlag(victim);

		clocker.release();
		Locker crosslock(victim, _this.getReferenceUnsafeStaticCast());

		if (!forfeit)
			adjustFrsExperience(victim, victimXp);

		victim->removePersonalEnemyFlag(killer);

		killer->sendPvpStatusTo(victim);

	}, "DarkArenaFinishLambda");

	String mailString = "@pvp_rating:challenge_concluded_defender_win"; // %TU has defeated %TT during a battle for the honor of rank %DI. As a result, %TU will remain at their station in rank %DI, while %TT will live in shame for their defeat.

	if (!isVictimChallenger) {
		managerData->updateChallengeTime(accepterID);
		demotePlayer(victim);
		promotePlayer(killer);

		mailString = "@pvp_rating:challenge_concluded_challenger_won"; // %TU was defeated by %TT during a battle for the honor of rank %DI. As a result %TU has been demoted from rank %DI, while %TT has taken their place.
	}

	FrsRank* rankData = getFrsRank(COUNCIL_DARK, challengeRank);

	if (rankData == NULL)
		return;

	SortedVector<uint64>* playerList = rankData->getPlayerList();

	StringIdChatParameter mailBody(mailString);
	mailBody.setTU(killer->getFirstName());
	mailBody.setTT(victim->getFirstName());
	mailBody.setDI(challengeRank);
	sendMailToList(playerList, "@pvp_rating:challenge_concluded_subject_header", mailBody);

	killer->sendSystemMessage(mailBody);
	victim->sendSystemMessage(mailBody);
}

bool FrsManagerImplementation::handleDarkCouncilIncap(CreatureObject* killer, CreatureObject* victim) {
	if (killer == NULL || victim == NULL)
		return false;

	uint64 killerID = killer->getObjectID();
	uint64 victimID = victim->getObjectID();

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

void FrsManagerImplementation::handleLeftArena(CreatureObject* player) {
	VectorMap<uint64, ManagedReference<ArenaChallengeData*> >* arenaChallenges = managerData->getArenaChallenges();
	ManagedReference<CreatureObject*> opponent = NULL;
	uint64 playerID = player->getObjectID();
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

	if (opponent == NULL)
		return;

	handleDarkCouncilDeath(opponent, player, true);
}

