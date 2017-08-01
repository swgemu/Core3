#include "server/zone/managers/frs/FrsManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/frs/RankMaintenanceTask.h"
#include "server/zone/managers/frs/FrsRankingData.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/variables/FrsData.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"

void FrsManagerImplementation::initialize() {
	loadLuaConfig();

	if (!frsEnabled)
		return;

	setupEnclaves();

	uint64 miliDiff = lastMaintenanceTime.miliDifference();

	if(rankMaintenanceTask == NULL) {
		rankMaintenanceTask = new RankMaintenanceTask(_this.getReferenceUnsafeStaticCast());

		if (miliDiff > maintenanceInterval)
			rankMaintenanceTask->execute();
		else
			rankMaintenanceTask->schedule(maintenanceInterval - miliDiff);
	} else {
		if (miliDiff > maintenanceInterval)
			rankMaintenanceTask->execute();
		else
			rankMaintenanceTask->reschedule(maintenanceInterval - miliDiff);
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
	petitionInterval = lua->getGlobalInt("petitionInterval");
	votingInterval = lua->getGlobalInt("votingInterval");
	acceptanceInterval = lua->getGlobalInt("acceptanceInterval");
	maintenanceInterval = lua->getGlobalInt("maintenanceInterval");
	requestDemotionDuration = lua->getGlobalInt("requestDemotionDuration");
	voteChallengeDuration = lua->getGlobalInt("voteChallengeDuration");
	baseMaintCost = lua->getGlobalInt("baseMaintCost");
	requestDemotionCost = lua->getGlobalInt("requestDemotionCost");
	voteChallengeCost = lua->getGlobalInt("voteChallengeCost");
	maxPetitioners = lua->getGlobalInt("maxPetitioners");
	missedVotePenalty = lua->getGlobalInt("missedVotePenalty");

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

void FrsManagerImplementation::setPlayerRank(CreatureObject* player, int rank) {
	if (player == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	FrsData* frsData = ghost->getFrsData();

	int councilType = frsData->getCouncilType();
	String groupName = "";

	if (councilType == COUNCIL_LIGHT)
		groupName = "LightEnclaveRank";
	else if (councilType == COUNCIL_DARK)
		groupName = "DarkEnclaveRank";
	else
		return;

	int curRank = frsData->getRank();

	if (curRank > 0)
		ghost->removePermissionGroup(groupName + String::valueOf(curRank), true);

	frsData->setRank(rank);

	ghost->addPermissionGroup(groupName + String::valueOf(rank), true);

	uint32 playerID = ghost->getObjectID();

	if (councilType == COUNCIL_LIGHT) {
		if (lightRankedMembers.contains(playerID))
			lightRankedMembers.drop(playerID);

		if (rank > 0)
			lightRankedMembers.put(playerID, rank);
	} else if (councilType == COUNCIL_DARK) {
		if (darkRankedMembers.contains(playerID))
			darkRankedMembers.drop(playerID);

		if (rank > 0)
			darkRankedMembers.put(playerID, rank);
	}

	updatePlayerSkills(player);
}

void FrsManagerImplementation::updatePlayerSkills(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();
	int councilType = frsData->getCouncilType();
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

	FrsData* frsData = ghost->getFrsData();
	int rank = frsData->getRank();

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

	FrsData* frsData = ghost->getFrsData();
	int rank = frsData->getRank();

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
		FrsData* frsData = ghost->getFrsData();
		int rank = frsData->getRank();
		int councilType = frsData->getCouncilType();

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

	for (int i = 0; i < lightRankedMembers.size(); ++i) {
		uint64 playerID = lightRankedMembers.elementAt(i).getKey();

		playerList.add(playerID);
	}

	for (int i = 0; i < darkRankedMembers.size(); ++i) {
		uint64 playerID = darkRankedMembers.elementAt(i).getKey();

		playerList.add(playerID);
	}

	return playerList;
}

void FrsManagerImplementation::deductMaintenanceXp(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	FrsData* frsData = ghost->getFrsData();
	int rank = frsData->getRank();

	if (rank == 0)
		return;

	int maintXp = rank * 100;

	ChatManager* chatManager = zoneServer->getChatManager();

	StringIdChatParameter mailBody("@force_rank:xp_maintenance_body"); // You have lost %DI Force Rank experience. All members of Rank 1 or higher must pay experience each day to remain in their current positions. (Note: This loss may not take effect until your next login.)
	mailBody.setTO(maintXp);

	chatManager->sendMail("Enclave Records", "@force_rank:xp_maintenace_sub", mailBody, player->getFirstName(), NULL);

	addExperienceDebt(player, maintXp);
}

void FrsManagerImplementation::addExperienceDebt(CreatureObject* player, int amount) {
	uint64 playerID = player->getObjectID();

	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (experienceDebt.contains(playerID)) {
		int curAmount = experienceDebt.get(playerID);
		amount += curAmount;
	}

	experienceDebt.put(playerID, amount);
}

void FrsManagerImplementation::deductDebtExperience(CreatureObject* player) {
	uint64 playerID = player->getObjectID();

	Locker clocker(_this.getReferenceUnsafeStaticCast(), player);

	if (!experienceDebt.contains(playerID))
		return;

	int debtAmt = experienceDebt.get(playerID);

	if (debtAmt <= 0)
		return;

	adjustFrsExperience(player, debtAmt * -1);

	experienceDebt.drop(playerID);
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
