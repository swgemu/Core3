#include "server/zone/managers/frs/FrsManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/frs/RankMaintenanceTask.h"
#include "server/zone/managers/frs/VoteStatusTask.h"
#include "server/zone/managers/frs/FrsRankingData.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/variables/FrsData.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/EnclaveVotingTerminalSuiCallback.h"

void FrsManagerImplementation::initialize() {
	loadLuaConfig();

	if (!frsEnabled)
		return;

	setupEnclaves();

	uint64 miliDiff = lastMaintenanceTime.miliDifference();

	if (rankMaintenanceTask == NULL) {
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

	short newStatus = VOTING_CLOSED;

	if (lightRanks.size() == 0) {
		for (int i = 1; i <= 11; i++) {
			FrsRank* newRank = new FrsRank(COUNCIL_LIGHT, i, newStatus);
			lightRanks.add(newRank);
		}
	}

	if (darkRanks.size() == 0) {
		for (int i = 1; i <= 11; i++) {
			FrsRank* newRank = new FrsRank(COUNCIL_DARK, i, newStatus);
			darkRanks.add(newRank);
		}
	}

	miliDiff = lastVoteStatusTick.miliDifference();

	if (voteStatusTask == NULL) {
		voteStatusTask = new VoteStatusTask(_this.getReferenceUnsafeStaticCast());

		if (miliDiff > VOTE_STATUS_TICK)
			voteStatusTask->execute();
		else
			voteStatusTask->schedule(VOTE_STATUS_TICK - miliDiff);
	} else {
		if (miliDiff > VOTE_STATUS_TICK)
			voteStatusTask->execute();
		else
			voteStatusTask->reschedule(VOTE_STATUS_TICK - miliDiff);
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

	uint64 playerID = player->getObjectID();

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

	if (curRank > 0) {
		ghost->removePermissionGroup(groupName + String::valueOf(curRank), true);

		FrsRank* rankData = getFrsRank(councilType, curRank);

		if (rankData != NULL) {
			rankData->removeFromPlayerList(playerID);
		}
	}

	frsData->setRank(rank);

	ghost->addPermissionGroup(groupName + String::valueOf(rank), true);

	FrsRank* rankData = getFrsRank(councilType, rank);

	if (rankData != NULL) {
		rankData->addToPlayerList(playerID);
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

void FrsManagerImplementation::sendVoteSUI(CreatureObject* player, SceneObject* terminal, short suiType, short enclaveType) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	Vector<String> elementList;

	for (int i = 1; i < 12; i++) {
		String stfRank = "@force_rank:rank" + i;
		String rankString = StringIdManager::instance()->getStringId(stfRank.hashCode()).toString();
		elementList.add(stfRank);
	}

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new EnclaveVotingTerminalSuiCallback(player->getZoneServer(), suiType, enclaveType, -1, true));
	box->setUsingObject(terminal);
	box->setOkButton(true, "@ok");
	box->setCancelButton(true, "@cancel");

	if (suiType == SUI_VOTE_STATUS) {
		box->setPromptText("@force_rank:vote_status_select"); // Select the rank whose status you wish to view.
		box->setPromptTitle("@force_rank:rank_selection"); // Rank Selection
	} else if (suiType == SUI_VOTE_RECORD) {
		box->setPromptText("@force_rank:vote_record_select"); // Select the rank for which you wish to record your vote.
		box->setPromptTitle("@force_rank:rank_selection"); // Rank Selection
		FrsData* frsData = ghost->getFrsData();
		int rank = frsData->getRank();

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
	}

	for (int i = 0; i < elementList.size(); i++)
		box->addMenuItem(elementList.get(i));

	box->setUsingObject(terminal);
	player->getPlayerObject()->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void FrsManagerImplementation::handleVoteStatusSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	int rank = index + 1;

	FrsRank* rankData = getFrsRank(enclaveType, rank);

	if (rankData == NULL) {
		player->sendSystemMessage("@force_rank:invalid_rank_selected"); // That is an invalid rank.
		return;
	}

	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::ENCLAVE_VOTING, SuiListBox::HANDLESINGLEBUTTON);
	box->setOkButton(true, "@ok");
	box->setPromptText("Vote Stats for Rank " + String::valueOf(rank));
	box->setPromptTitle("@force_rank:vote_status"); // Voting Status

	short voteStatus = rankData->getVoteStatus();

	if (voteStatus != 0)
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
		timeLeft = getTimeString(timeRemaining);
	else
		timeLeft = "closed.";

	box->addMenuItem("Time Remaining: " + timeLeft);
	box->addMenuItem("");

	if (voteStatus == PETITIONING || voteStatus == VOTING_OPEN) {

		VectorMap<uint64, int>* petitionerList = rankData->getPetitionerList();

		if (petitionerList->size() > 0) {
			box->addMenuItem("Petitioners: (first 20 shown)");

			for (int i = 0; i < petitionerList->size(); i++) {
				if (i > 20)
					break;

				VectorMapEntry<uint64, int> entry = petitionerList->elementAt(i);
				uint64 petitionerID = entry.getKey();
				int votes = entry.getValue();
				ManagedReference<CreatureObject*> player = zoneServer->getObject(petitionerID).castTo<CreatureObject*>();

				if (player == NULL) {
					rankData->removeFromPetitionerList(petitionerID);
					continue;
				}

				String playerName = player->getFirstName();

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
				ManagedReference<CreatureObject*> player = zoneServer->getObject(winnerID).castTo<CreatureObject*>();

				if (player == NULL) {
					rankData->removeFromPetitionerList(winnerID);
					continue;
				}

				String playerName = player->getFirstName();
				box->addMenuItem("   " + playerName);
			}
		}
	}
}

void FrsManagerImplementation::sendVoteRecordSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int index) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	int rank = index + 1;

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

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

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
	box->setCallback(new EnclaveVotingTerminalSuiCallback(player->getZoneServer(), SUI_VOTE_RECORD, enclaveType, rank, false));
	box->setUsingObject(terminal);
	box->setOkButton(true, "@ok");
	box->setCancelButton(true, "@cancel");

	box->setPromptText("@force_rank:vote_record_select_player"); // Select the petitioner to whom you wish to promote.
	box->setPromptTitle("@force_rank:vote_player_selection"); // Petitioner Selection

	for (int i = 0; i < petitionerList->size(); i++) {
		VectorMapEntry<uint64, int> entry = petitionerList->elementAt(i);
		uint64 petitionerID = entry.getKey();
		ManagedReference<CreatureObject*> player = zoneServer->getObject(petitionerID).castTo<CreatureObject*>();

		if (player == NULL) {
			rankData->removeFromPetitionerList(petitionerID);
			continue;
		}

		String playerName = player->getFirstName();
		box->addMenuItem(playerName);
	}
}

void FrsManagerImplementation::handleVoteRecordSui(CreatureObject* player, SceneObject* terminal, short enclaveType, int rank, int index) {
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
		player->sendSystemMessage("@force_rank:vote_time_expired"); // Time has expired for the voting process.
		return;
	}

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

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

	VectorMapEntry<uint64, int> petitionerData = petitionerList->elementAt(index);

	uint64 petitionerID = petitionerData.getKey();
	ManagedReference<CreatureObject*> petitioner = zoneServer->getObject(petitionerID).castTo<CreatureObject*>();

	if (petitioner == NULL) {
		rankData->removeFromPetitionerList(petitionerID);
		return;
	}

	int curVotes = petitionerData.getValue();

	String playerName = petitioner->getFirstName();
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

	if (voteStatus != WAITING) {
		player->sendSystemMessage("@force_rank:petition_time_expired"); // 	Time has expired for petitioning.
		return;
	}

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();
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
		mailBody.setTO("@force_rank:rank" + rank);
		sendMailToList(winnerList, "@force_rank:vote_last_seat_taken_sub", mailBody);

		player->sendSystemMessage(mailBody);
		rankData->setVoteStatus(VOTING_CLOSED);
		return;
	}

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

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
	mailBody.setTO("@force_rank:rank" + rank);
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
		mailBody.setTO("@force_rank:rank" + rank);
		sendMailToList(winnerList, "@force_rank:vote_last_seat_taken_sub", mailBody);

		player->sendSystemMessage(mailBody);
		rankData->setVoteStatus(VOTING_CLOSED);
	}
}

bool FrsManagerImplementation::isEligibleForPromotion(CreatureObject* player, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return false;

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();
	int councilType = frsData->getCouncilType();
	VectorMap<uint, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;
	else
		return false;

	Reference<FrsRankingData*> rankData = rankingData.get(playerRank - 1);
	String rankSkill = rankData->getSkillName();

	SkillManager* skillManager = zoneServer->getSkillManager();

	if (skillManager == NULL)
		return false;

	return skillManager->fulfillsSkillPrerequisitesAndXp(rankSkill, player);
}

int FrsManagerImplementation::getVoteWeight(int playerRank, int voteRank) {
	// Unranked players are unable to vote
	if (playerRank < 1)
		return -1;

	if (voteRank < 1 || voteRank > 11)
		return -1;
	else if (voteRank == playerRank) // Votes count for double if the voter is in the same rank they are voting for
		return 2;
	else if (voteRank > 0 && voteRank < 5 && playerRank > 0 && playerRank < 5) // Players of rank 1-4 can participate in votes of rank 1-4
		return 1;
	else if (voteRank > 4 && voteRank < 8 && playerRank > 4 && playerRank < 8) // Players of rank 5-7 can participate in votes of rank 5-7
		return 1;
	else if ((voteRank == 8 || voteRank == 9) && (playerRank == 8 || playerRank == 9)) // Players of rank 8-9 can particpate in votes of rank 8-9
		return 1;
	else if ((voteRank == 10 && playerRank == 11) || (voteRank == 10 && playerRank == 11)) // Rank 10 can vote for 11, 11 can vote for 10
		return 1;
	else
		return -1;
}

bool FrsManagerImplementation::hasPlayerVoted(CreatureObject* player, int rank) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return true;

	FrsData* frsData = ghost->getFrsData();
	int councilType = frsData->getCouncilType();

	FrsRank* rankInfo = NULL;

	if (councilType == COUNCIL_LIGHT)
		rankInfo = lightRanks.get(rank - 1);
	else if (councilType == COUNCIL_DARK)
		rankInfo = darkRanks.get(rank - 1);

	if (rankInfo == NULL)
		return false;

	return rankInfo->isOnVotedList(player->getObjectID());
}

int FrsManagerImplementation::getAvailableRankSlots(FrsRank* rankInfo) {
	short councilType = rankInfo->getCouncilType();
	int rank = rankInfo->getRank();

	VectorMap<uint, Reference<FrsRankingData*> > rankingData;

	if (councilType == COUNCIL_LIGHT)
		rankingData = lightRankingData;
	else if (councilType == COUNCIL_DARK)
		rankingData = darkRankingData;

	Reference<FrsRankingData*> rankData = rankingData.get(rank - 1);

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
				mailBody.setTO("@force_rank:rank" + rank);
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

				for (int i = 0; i < petitionerList->size(); i++) {
					VectorMapEntry<uint64, int> entry = petitionerList->elementAt(i);
					uint64 petitionerID = entry.getKey();
					ManagedReference<CreatureObject*> player = zoneServer->getObject(petitionerID).castTo<CreatureObject*>();

					if (player == NULL) {
						rankInfo->removeFromPetitionerList(petitionerID);
						continue;
					}

					rankInfo->addToWinnerList(petitionerID);
					chatManager->sendMail("Enclave Records", "@force_rank:vote_win_sub", "@force_rank:vote_win_body", player->getFirstName());
				}
			} else { // Move to voting phase to determine who should be promoted
				rankInfo->setVoteStatus(VOTING_OPEN);

				StringIdChatParameter mailBody("@force_rank:vote_cycle_begun_body"); // Voting has started for promotions into %TO. It is part of your Enclave duties to cast your vote for the petitioner who you deem most worthy. Voting time remaining: %TT
				mailBody.setTO("@force_rank:rank" + rank);
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
			StringIdChatParameter mailBody("@force_rank:vote_win_no_slot_body"); // Your deadline for accepting a promotion to %TO has passed. You will have to petition and then win another vote in order to achieve this rank.
			mailBody.setTO("@force_rank:rank" + rank);
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

		FrsRank* voteRankInfo = NULL;

		if (councilType == COUNCIL_LIGHT)
			voteRankInfo = lightRanks.get(i - 1);
		else if (councilType == COUNCIL_DARK)
			voteRankInfo = darkRanks.get(i - 1);

		if (voteRankInfo == NULL)
			continue;

		int votePenalty = missedVotePenalty * pow(i, 2);

		SortedVector<uint64>* playerList = voteRankInfo->getPlayerList();

		for (int j = 0; j < playerList->size(); j++) {
			uint64 playerID = playerList->get(j);

			if (!rankInfo->isOnVotedList(playerID)) {
				ManagedReference<CreatureObject*> player = zoneServer->getObject(playerList->get(j)).castTo<CreatureObject*>();

				if (player != NULL) {
					missedVoteList.add(playerID);
					addExperienceDebt(player, votePenalty);

					StringIdChatParameter mailBody("@force_rank:vote_missed_body"); // You have missed a promotion vote for %TO. As a result, you have lost %DI Force Ranking experience. (Note: This loss may not take effect until your next login.)
					mailBody.setTO("@force_rank:rank" + rank);
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

		FrsRank* rankInfo = NULL;

		if (councilType == COUNCIL_LIGHT)
			rankInfo = lightRanks.get(rank - 1);
		else if (councilType == COUNCIL_DARK)
			rankInfo = darkRanks.get(rank - 1);

		if (rankInfo == NULL)
			continue;

		SortedVector<uint64>* voterList = rankInfo->getPlayerList();

		sendMailToList(voterList, sub, body);
	}
}

void FrsManagerImplementation::sendMailToList(Vector<uint64>* playerList, const String& sub, StringIdChatParameter& body) {
	ChatManager* chatManager = zoneServer->getChatManager();

	for (int j = 0; j < playerList->size(); j++) {
		ManagedReference<CreatureObject*> player = zoneServer->getObject(playerList->get(j)).castTo<CreatureObject*>();

		if (player != NULL) {
			chatManager->sendMail("Enclave Records", sub, body, player->getFirstName());
		}
	}
}

Vector<uint64>* FrsManagerImplementation::getTopVotes(FrsRank* rankInfo, int numWinners) {
	Vector<uint64>* winnerList = NULL;
	VectorMap<uint32, uint64> reverseList;
	VectorMap<uint64, int>* petitionerList = rankInfo->getPetitionerList();

	for (int i = 0; i < petitionerList->size(); i++) {
		VectorMapEntry<uint64, int> entry = petitionerList->elementAt(i);
		uint64 petitionerID = entry.getKey();
		uint32 petitionerVotes = entry.getValue();
		reverseList.put(petitionerVotes, petitionerID);
	}

	for (int i = 0; i < numWinners; i++) {
		VectorMapEntry<uint32, uint64> entry = reverseList.elementAt(i);
		uint64 petitionerID = entry.getValue();
		winnerList->add(petitionerID);
	}

	return winnerList;
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

			str << ((i == 0) ? "and " : "") << values[i] << " " << abbrvs[i];
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
