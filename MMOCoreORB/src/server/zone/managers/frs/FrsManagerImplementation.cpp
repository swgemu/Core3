/*
 * FrsManagerImplementation.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: Dreadlow
 */

#include "server/zone/managers/frs/FrsManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "engine/engine.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/forcerank/ForceRankObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/player/events/FRSMaintenanceTask.h"
#include "server/zone/managers/frs/RankMaintenanceEvent.h"
#include "server/zone/managers/skill/SkillManager.h"

void FrsManagerImplementation::initialize() {
	lua = new Lua();
	lua->init();

	info("Loading configuration file.");

	if (loadConfigFile()) {
		loadConfigData();
		loadRankMembers();

		Reference<RankMaintenanceEvent*> startMaintenanceEvent = new RankMaintenanceEvent(server, maintenanceInterval);
		startMaintenanceEvent->run();
	} else
		info("Failed to load configuration values.");
}

void FrsManagerImplementation::loadRankMembers() {
	Locker _lock(_this.get());

	ObjectDatabase* enclaveDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("enclave", true);

	if (enclaveDatabase == NULL) {
		error("Could not load the enclave database.");
		return;
	}

	try {
		info("Loading rank members from database.", true);
		ObjectDatabaseIterator iterator(enclaveDatabase);

		uint64 objectID = 0;

		while (iterator.getNextKey(objectID)) {
			Reference<ForceRankObject*> rankMember = Core::getObjectBroker()->lookUp(objectID).castTo<ForceRankObject*>();

			if (rankMember == NULL)
				continue;

			ManagedReference<SceneObject*> object = server->getObject(rankMember->getCreatureID());

			if (object == NULL) {
				ObjectManager::instance()->destroyObjectFromDatabase(rankMember->_getObjectID());
				continue;
			}

			if (rankMember->getEnclave() == 4)
				lightMemberList.put(rankMember->getCreatureID(), rankMember->getRank());
			else if (rankMember->getEnclave() == 8)
				darkMemberList.put(rankMember->getCreatureID(), rankMember->getRank());

		}

		info(String::valueOf(lightMemberList.size() + darkMemberList.size()) + " rank members loaded.", true);
	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Exception found in FrsManagerImplementation::loadRankMembers(): " << e.getMessage();
		error(err);
		return;
	}
}

bool FrsManagerImplementation::loadConfigFile() {
	return lua->runFile("scripts/managers/frs_manager.lua");
}

void FrsManagerImplementation::loadConfigData() {
	maintenanceInterval = lua->getGlobalInt("maintenanceInterval");

	LuaObject maxPerRankObject = lua->getGlobalObject("max_members_per_rank");

	if (maxPerRankObject.isValidTable()) {
		for (int i = 1; i <= maxPerRankObject.getTableSize(); ++i) {
			LuaObject rankObject = maxPerRankObject.getObjectAt(i);

			if(rankObject.isValidTable()){
				uint8 rank = rankObject.getIntAt(1);
				uint8 rankMax = rankObject.getIntAt(2);
				frsMaximums.put(rank, rankMax);
				info("Rank " + String::valueOf(rank) + " limited to " + String::valueOf(rankMax) + " member(s).");
			}

			rankObject.pop();
		}
	}

	maxPerRankObject.pop();
}

void FrsManagerImplementation::updateEnclaveMember(CreatureObject* creo, int rank, bool remove) {
	uint64 objectID = creo->getObjectID();

	ManagedReference<ForceRankObject*> enclaveObject = creo->getForceRankObject();

	if (enclaveObject == NULL)
		return;

	if (lightMemberList.contains(objectID))
		lightMemberList.drop(objectID);
	else if (darkMemberList.contains(objectID))
		darkMemberList.drop(objectID);

	if (remove) {
		ObjectManager::instance()->destroyObjectFromDatabase(enclaveObject->_getObjectID());
		creo->setForceRankObject(NULL);

		return;
	}

	if (enclaveObject->getEnclave() == 4)
		lightMemberList.put(objectID, rank);
	else if (enclaveObject->getEnclave() == 8)
		darkMemberList.put(objectID, rank);

	enclaveObject->setRank(rank);
	enclaveObject->_setUpdated(true);
}

int FrsManagerImplementation::checkSeatAvailability(int enclave, int rank) {
	int availableSeats = frsMaximums.elementAt(rank-1).getValue();

	if (enclave == 4) {
		for (int i=0; i < lightMemberList.size(); i++) {
			if (lightMemberList.elementAt(i).getValue() == rank)
				availableSeats = availableSeats - 1;
		}
	} else {
		for (int i=0; i < darkMemberList.size(); i++) {
			if (darkMemberList.elementAt(i).getValue() == rank)
				availableSeats = availableSeats - 1;
		}
	}

	if (availableSeats < 0)
		availableSeats = 0;

	return availableSeats;
}

void FrsManagerImplementation::processRankMaintenance() {
	info("Running rank maintenance...", true);

	for (int i=0; i < lightMemberList.size(); i++) {
		uint64 objectID = lightMemberList.elementAt(i).getKey();
		CreatureObject* creature = server->getObject(objectID).castTo<CreatureObject*>();

		if (creature == NULL)
			continue;

		Reference<FRSMaintenanceTask*> frsMaintenanceTask = new FRSMaintenanceTask(creature);
		frsMaintenanceTask->run();
	}

	for (int i=0; i < darkMemberList.size(); i++) {
		uint64 objectID = darkMemberList.elementAt(i).getKey();
		CreatureObject* creature = server->getObject(objectID).castTo<CreatureObject*>();

		if (creature == NULL)
			continue;

		Reference<FRSMaintenanceTask*> frsMaintenanceTask = new FRSMaintenanceTask(creature);
		frsMaintenanceTask->run();
	}
}

void FrsManagerImplementation::getVotingPetitioners(int enclave, int rank) {
	lua_State* L = lua->getLuaState();

	lua_newtable(L);
	Vector<String> petitionerNames;

	if (enclave == 4) {
		for (int i = 0; i < lightPetitioningList.size(); i++) {
			if (lightPetitioningList.elementAt(i).getValue() == rank) {
				petitionerNames.add(server->getObject(lightPetitioningList.elementAt(i).getKey())->getDisplayedName());
			}
		}
	} else if (enclave == 8) {
		for (int i = 0; i < darkPetitioningList.size(); i++) {
			if (darkPetitioningList.elementAt(i).getValue() == rank) {
				petitionerNames.add(server->getObject(darkPetitioningList.elementAt(i).getKey())->getDisplayedName());
			}
		}
	}

	for (int i = 0; i < petitionerNames.size(); i++) {
		lua_pushstring(L, petitionerNames.get(i).toCharArray());
	}

	for (int i = petitionerNames.size(); i > 0; i--) {
		lua_rawseti(L, -i - 1, i);
	}
}
