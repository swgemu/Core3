#include "server/zone/managers/frs/FrsManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/frs/RankMaintenanceTask.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/variables/FrsData.h"
#include "server/zone/objects/building/BuildingObject.h"

void FrsManagerImplementation::initialize() {
	loadLuaConfig();
	setupEnclaves();

/*	uint64 miliDiff = lastMaintenanceTime.miliDifference();

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
	}*/
}

void FrsManagerImplementation::loadLuaConfig() {
	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/jedi/frs_manager.lua")) {
		error("Unable to load FrsManager data.");
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

void FrsManagerImplementation::setPlayerRank(PlayerObject* ghost, int rank) {
	if (ghost == NULL)
		return;

	FrsData* frsData = ghost->getFrsData();

	int councilType = frsData->getCouncilType();
	String groupName = "";

	if (councilType == FrsData::COUNCIL_LIGHT)
		groupName = "LightEnclaveRank";
	else if (councilType == FrsData::COUNCIL_DARK)
		groupName = "DarkEnclaveRank";

	if (groupName == "")
		return;

	int curRank = frsData->getRank();

	if (curRank > 0)
		ghost->removePermissionGroup(groupName + String::valueOf(curRank), true);

	frsData->setRank(rank);

	ghost->addPermissionGroup(groupName + String::valueOf(rank), true);
}

void FrsManagerImplementation::processRankMaintenance() {
	rankMaintenanceTask->reschedule(maintenanceInterval);
}
