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
	for (uint32 j = 1; j < enclaveBuilding->getTotalCellNumber(); ++j) {
		ManagedReference<CellObject*> cell = enclaveBuilding->getCell(j);

		if (cell != NULL) {
			cell->setContainerComponent("EnclaveContainerComponent");

			ContainerPermissions* permissions = cell->getContainerPermissions();

			permissions->setInheritPermissionsFromParent(false);
			permissions->clearDefaultAllowPermission(ContainerPermissions::WALKIN);
			permissions->setDefaultDenyPermission(ContainerPermissions::WALKIN);

			int roomReq = getRoomRequirement(cell->getObjectID());

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
