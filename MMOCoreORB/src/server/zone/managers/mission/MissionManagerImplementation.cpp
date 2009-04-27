/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "../../objects.h"

#include "../../objects/terrain/PlanetNames.h"

#include "../../objects/player/Player.h"

#include "../../packets.h"
#include "../../objects.h"

#include "../../../ServerCore.h"

#include "../../ZoneServer.h"
#include "../../ZoneServerImplementation.h"

#include "MissionManagerImplementation.h"

MissionManagerImplementation* MissionManagerImplementation::instance = NULL;

MissionManagerImplementation::MissionManagerImplementation(ZoneServer* zs, ZoneProcessServerImplementation* ps) : MissionManagerServant(), Mutex("MissionManager"), Lua() {

	zoneServer = zs;
	processServer = ps;

	misoMap = new MissionMap();

	setLoggingName("MissionManager");

	setLogging(false); //set to false after debugging
	setGlobalLogging(true);

	init();
}

MissionManagerImplementation::~MissionManagerImplementation() {
	removeMissions();

	delete misoMap;
	misoMap = NULL;
}

void MissionManagerImplementation::init() {
	// Scripting
	Lua::init();
	registerFunctions();
	registerGlobals();
	instance = this;
	loadMissionScripts();
}

void MissionManagerImplementation::unloadManager() {
}

/**
 * Deploy a mission to the server and add to the Manager's pool of available missions
 */
MissionObject* MissionManagerImplementation::poolMission(MissionObject* miso, bool doLock) {
	try {
		lock(doLock);

		miso->deploy();

		if (misoMap->get(miso->getDBKey()) != NULL) {
			String err = "Mission Key Collision with " + miso->getDBKey();
			error(err);

			unlock(doLock);
			return NULL;
		} else {
			misoMap->add(miso);

			unlock(doLock);
			return miso;
		}

	} catch (...) {
		error("unreported Exception caught on poolMission()");

		unlock(doLock);
		return NULL;
	}
}

/**
 * Copies mission vars from the default mission in the pool
 * Creates a new mission object for a player, spawns personalized objectives
 * Used whenever a player is online an owns a mission. Released when a player logs out
 */
void MissionManagerImplementation::instanceMission(Player* player, MissionObject* misoCopy, const String& objectives, bool isNew) {
	if(misoCopy == NULL) {
		System::out << "instanceMission: misoCopy is null" << endl;
		return;
	}

	//object id can be the same, no need to waste id space. Also set owner object
	MissionObject* miso = new MissionObject(misoCopy->getObjectID(), player);
	miso->deploy();

	miso->lock();

	//Clone vars:
	// Server Vars
	miso->setDBKey(misoCopy->getDBKey());

	// Title/Name
	miso->setTitleKey(misoCopy->getTitleKey());
	miso->setTitleStf(misoCopy->getTitleStf());
	miso->setTitle(misoCopy->getTitle());

	// General: (type, terminal)
	miso->applyTerminalMask(misoCopy->getTerminalMask());
	miso->setTypeStr(misoCopy->getTypeStr());
	miso->setTypeCrc(misoCopy->getTypeCrc());
	miso->setCreatorName(misoCopy->getCreatorName());
	miso->setDifficultyLevel(misoCopy->getDifficultyLevel());

	// Location: Start (npc assigner)
	miso->setTargetX(misoCopy->getTargetX());
	miso->setTargetY(misoCopy->getTargetY());
	miso->setTargetPlanetCrc(misoCopy->getTargetPlanetCrc());

	// Location: Destination (target)
	miso->setDestX(misoCopy->getDestX());
	miso->setDestY(misoCopy->getDestY());
	miso->setDestPlanetCrc(misoCopy->getDestPlanetCrc());

	// Rewards
	miso->setRewardCredits(misoCopy->getRewardCredits());
	/*String rewardXp = mission.getStringField("rewardXP");
	String rewardBadgeIds = mission.getStringField("rewardBadgeIds");
	String rewardFactions = mission.getStringField("rewardFactions");
	String rewardObjects = mission.getStringField("rewardObjects");*/

	// Description
	miso->setDescKey(misoCopy->getDescKey());
	miso->setDescriptionStf(misoCopy->getDescriptionStf());
	miso->setDescription(misoCopy->getDescription());

	// Objective & target
	miso->setTargetName(misoCopy->getTargetName());
	miso->setDepictedObjCrc(misoCopy->getDepictedObjCrc());
	miso->setObjectiveDefaults(misoCopy->getObjectiveDefaults());
	miso->setInstantComplete(misoCopy->isInstantComplete());

	// Spawn objectives:
	miso->spawnObjectives(misoCopy->getObjectiveDefaults(), false);

	// Add the mission to the player:
	player->addMission(miso->getDBKey(), miso);

	// Setup Mission assets if the mission is being given for the first time
	if(isNew)
		miso->assetSetup();

	miso->unlock();
}

/**
 * Send the appropriate data for a given terminal in the galaxy
 */
void MissionManagerImplementation::sendTerminalData(Player* player, int termBitmask, bool doLock) {
	try {
		lock(doLock);

		//TODO: Ditch the misoBSB, just lookup player's current planet & ifIsInGroup and use terminal type

		//List baselines if player needs completely new refresh:
		if(player->getMisoRFC() == 0x01) {
			for (int i = 0; i < misoMap->size(); i++) {
				MissionObject* miso = misoMap->get(i);
				if (miso == NULL)
					continue;

				//Check if player is already on mission:
				if (player->isOnCurMisoKey(miso->getDBKey()))
					continue;

				sendMissionBase(player, miso);
				sendMissionDelta(player, miso);
			}
		} else {
			for (int i = 0; i < misoMap->size(); i++) {
				MissionObject* miso = misoMap->get(i);
				if (miso == NULL)
					continue;

				//Check if player is already on mission:
				if (player->isOnCurMisoKey(miso->getDBKey()))
					continue;

				sendMissionDelta(player, miso);
			}
		}

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on sendTerminalData()");

		unlock(doLock);
	}
}

/**
 * Send all mission packets and link them to a player
 */
void MissionManagerImplementation::sendMission(Player* player, const String& tKey, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(tKey);

		if (miso == NULL) {
			error("miso object[" + tKey + "] is NULL for player: " + player->getFirstName() + ", exiting function: sendMission()");
			unlock(doLock);
			return;
		}

		sendMissionBase(player, miso);
		sendMissionDelta(player, miso);
		miso->doLinkToPlayer(player);

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on sendMission()");

		unlock(doLock);
	}
}

/**
 * Mission Events
 * Triggered by ingame actions. Accept, complete, abort, evaluate
 */

/**
 * Mission Accept (from terminal or npc)
 */
void MissionManagerImplementation::doMissionAccept(Player* player, uint64& oid, bool doLock) {
	try {
		lock(doLock);

		// Check if the player has more than the max amount of missions allowed
		if(player->getMissionCount() > MAX_MISSIONS_PER_PLAYER)
			player->sendSystemMessage("You cannot have more than " + MAX_MISSIONS_PER_PLAYER + " missions at a time");

		MissionObject* miso = misoMap->get(oid);
		if (miso == NULL) {
			error("miso object is NULL, exiting function: doMissionAccept()");
			unlock(doLock);
			return;
		}

		// Check if player is already on mission:
		if (player->isOnCurMisoKey(miso->getDBKey())) {
			unlock(doLock);
			return;
		}

		// Give the mission to the player:
		miso->doLinkToPlayer(player);
		instanceMission(player, miso, miso->getObjectiveDefaults(), true);
		player->sendSystemMessage("You have accepted the mission and it has been added to your datapad.");

		// Play acceptance music:
		PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_accepted.snd");
		player->sendMessage(pmm);

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAccept()");

		unlock(doLock);
	}
}

/**
 * Mission Complete events
 */
void MissionManagerImplementation::doMissionComplete(Player* player, const String& tKey, bool doLock) {
	try {
		lock(doLock);

		// Remove any mission save from the DB:
		deleteMissionSave(player, tKey);

		// Drop the mission from the the player
		removeMisoFromPlayer(player, tKey, false);
		player->dropMission(tKey, true);
		player->sendSystemMessage("Mission Complete.");

		// Play mission complete music:
		PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
		player->sendMessage(pmm);

		// Reset terminal refresh
		player->setMisoRFC(0x01);

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionComplete()\n");

		unlock(doLock);
	}
}

/**
 * Mission Abort Events
 */
void MissionManagerImplementation::doMissionAbort(Player* player, uint64& oid, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(oid);
		if (miso == NULL) {
			error("miso object is NULL, exiting function: doMissionAbort()");
			unlock(doLock);
			return;
		}

		doMissionAbort(player, miso);

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAbort()");

		unlock(doLock);
	}
}

void MissionManagerImplementation::doMissionAbort(Player* player, const String& tKey, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(tKey);
		if (miso == NULL) {
			error("miso object is NULL, exiting function: doMissionAbort()");
			unlock(doLock);
			return;
		}

		doMissionAbort(player, miso);

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAbort()");

		unlock(doLock);
	}
}

void MissionManagerImplementation::doMissionAbort(Player* player, MissionObject* miso) {
	String tKey = miso->getDBKey();

	//Remove any mission save from the DB:
	deleteMissionSave(player, tKey);

	//Drop the mission from the player
	player->dropMission(tKey, false);
	removeMisoFromPlayer(miso, player);
	player->sendSystemMessage("Mission Failed.");

	// Reset terminal refresh
	player->setMisoRFC(0x01);
}

/**
 * Initiate reward calcs, kill counts etc for a mission. Called when player objectives need to be evaluated
 * This will call doMissionComplete (on completion) and abort (if failed)
 * The retSay is an update on the status of the mission. Can be "said" by an NPC or systemMsg
 * ex. You do not have: ___. You have not killed enough _____ or even: You are not assigned to any of my missions
 */
bool MissionManagerImplementation::evalMission(Player* player, const String& tKey, String& retSay) {
	if(!player->isOnCurMisoKey(tKey))
		return false;

	MissionObject* miso = player->getPlayerMission(tKey);
	if(miso == NULL)
		return false;

	// checkComplete() in MissionObject should have already been called after a condition was updated.
	// Run the appropriate event handler and build the return string
	if(miso->isFailure()) {
		doMissionAbort(player, miso);
		retSay = "You have violated a condition of the mission...come back when you are competent.";
	} else if(miso->isComplete()) {
		doMissionComplete(player, tKey, false);
		retSay = "Thank you! You have done exactly what was asked.";
	} else {
		retSay = "You have not completed all mission conditions.";
	}

	return true;
}

/**
 * Alternate evalMission if return str is no desired (instantComplete)
 */
bool MissionManagerImplementation::evalMission(Player* player, MissionObject* miso) {
	if(player == NULL || miso == NULL) {
		System::out << "player or miso is null, aborting evalMission" << endl;
		return false;
	}

	// checkComplete() in MissionObject should have already been called after a condition was updated.
	// Run the appropriate event handler and build the return string
	if(miso->isFailure()) {
		doMissionAbort(player, miso);
	} else if(miso->isComplete()) {
		doMissionComplete(player, miso->getDBKey(), false);
	} else {
		return false;
	}

	return true;
}

/**
 * Loads all missions for a player from mission_saves:
 */
void MissionManagerImplementation::loadPlayerMissions(Player* player, bool doLock) {
	try {
		lock(doLock);

		// Grab and instance all missions based on the saves:
		StringBuffer query;
		query << "SELECT * FROM mission_save WHERE character_id = " << player->getCharacterID();
		ResultSet* res = ServerDatabase::instance()->executeQuery(query.toString());

		while (res->next()) {
			String misoKey = res->getString(2);
			String objectiveSer = res->getString(3);

			// Now send the mission packets:
			MissionObject* miso = misoMap->get(misoKey);
			if (miso == NULL) {
				// If the mission, for some reason, no longer exists on the server: delete the save
				deleteMissionSave(player, misoKey);
				continue;
			}

			// Only need to send the baseline and link. Delta should only be used for refresh.
			sendMissionBase(player, miso);
			miso->doLinkToPlayer(player);

			// Instance the mission for the player:
			instanceMission(player, misoMap->get(misoKey), objectiveSer, false);
		}

		// Load and set currentMissionKeys & finishedMissionKeys:
		StringBuffer qCur, qFin;
		ResultSet* resCur;
		ResultSet* resFin;
		qCur << "SELECT currentMissionKeys FROM characters WHERE character_id = " << player->getCharacterID() << " and currentMissionKeys is not null;";
		resCur = ServerDatabase::instance()->executeQuery(qCur.toString());
		qFin << "SELECT finishedMissionKeys FROM characters WHERE character_id = " << player->getCharacterID() << " and finishedMissionKeys is not null;";
		resFin = ServerDatabase::instance()->executeQuery(qFin.toString());

		if (resCur->next())
			player->setCurrentMissionKeys(resCur->getString(0));

		//If there are no saves, cleanup the mission keys. Useful for recovering from server crashes
		if(res->size() == 0)
			player->setCurrentMissionKeys("");

		if (resFin->next())
			player->setFinishedMissionKeys(resFin->getString(0));

		delete res;
		delete resCur;
		delete resFin;

		unlock(doLock);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::loadPlayerMissions");
	} catch (...) {
		error("unreported Exception caught on loadPlayerMissions");

		unlock(doLock);
	}
}

//Saves OR updates missions for a player in mission_saves:
void MissionManagerImplementation::savePlayerMission(Player* player, MissionObject* miso) {
	ResultSet* msRes;

	try {
		if(miso == NULL)
			return;

		// Get the mission key and serialized object strings:
		String mkey = miso->getDBKey();
		String objectiveSer = "";
		miso->serializeObjectives(objectiveSer);

		if(mkey.isEmpty())
			return;

		// Check if the mission exists:
		StringBuffer query;
		query << "SELECT * FROM mission_save WHERE character_id = " << player->getCharacterID() << " and miso_key = '" << mkey << "';";
		msRes = ServerDatabase::instance()->executeQuery(query.toString());

		if (msRes->size() <= 0) { //Create a save if there is none:
			StringBuffer queryIns;
			queryIns << "INSERT INTO mission_save "
				<< "(character_id,miso_key,objective_vars) "
				<< "VALUES (" << player->getCharacterID() << ",'" << mkey << "','"
				<< objectiveSer << "');";

			ServerDatabase::instance()->executeStatement(queryIns.toString());
		} else { //A save is present, so update it:
			StringBuffer qUpdate;

			qUpdate << "UPDATE mission_save set "
				 << "objective_vars = '" << objectiveSer << "' ";

			qUpdate << "WHERE character_id = " << player->getCharacterID() << " and miso_key = '" << mkey << "';";
			ServerDatabase::instance()->executeStatement(qUpdate.toString());
		}
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::savePlayerMission()");
	} catch (...) {
		error("unreported Exception caught on savePlayerMission()");
	}

	delete msRes;
}

/**
 * Delete a mission save from the mission_save table
 */
void MissionManagerImplementation::deleteMissionSave(Player* player, const String& mkey) {
	try {

		StringBuffer query;
		query << "DELETE FROM mission_save WHERE character_id = " << player->getCharacterID() << " and ";
		query << "miso_key = '" << mkey << "';";
		ServerDatabase::instance()->executeStatement(query.toString());

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::deleteMissionSave()");
	} catch (...) {
		error("unreported Exception caught on deleteMissionSave()");
	}
}

/**
 * Save player data on current and completed missions
 */
void MissionManagerImplementation::savePlayerKeys(Player* player, const String& curMisoKeys, const String& finMisoKeys) {
	try {
		StringBuffer qUpdate;

		qUpdate << "UPDATE characters set currentMissionKeys = '" << curMisoKeys << "', finishedMissionKeys = '" << finMisoKeys << "' "
			<< "WHERE character_id = " << player->getCharacterID();

		ServerDatabase::instance()->executeStatement(qUpdate);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::deleteMissionSave()");
	} catch (...) {
		error("unreported Exception caught on deleteMissionSave()");
	}
}

/**
 * This function is called by server admins. Clears all mission variables for a player in the event such action needs to be done
 */
void MissionManagerImplementation::clearPlayerMissions(Player* target, bool lockTarget) {
	try {
		if(target == NULL)
			return;

		// Clear entries in mission_saves
		StringBuffer qSaves;
		qSaves << "DELETE FROM mission_save WHERE character_id = " << target->getCharacterID();
		ServerDatabase::instance()->executeStatement(qSaves);

		// Clear current & finished mission keys:
		StringBuffer qUpdate;
		qUpdate << "UPDATE characters set currentMissionKeys = '', finishedMissionKeys = '' WHERE character_id = " << target->getCharacterID();
		ServerDatabase::instance()->executeStatement(qUpdate);

		target->lock(lockTarget);

		// Clear all missions on the player object:
		target->dropAllMissions();

		target->unlock(lockTarget);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::deleteMissionSave()");
	} catch (...) {
		error("unreported Exception caught on clearPlayerMissions()");
	}
}

/// END OF SAVE FUNCS

/**
 * Packet send functions for missions in the pool
 */

void MissionManagerImplementation::sendMissionBase(Player* player, const String& tKey, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(tKey);

		if (miso != NULL) {
			miso->sendTo(player, true);
		} else {
			error("Invalid mission attempting to be sent. sendMissionBase (key)");
		}

		unlock(doLock);
	} catch (...) {
	error("unreported Exception caught on sendMissionBase() (key version)");

	unlock(doLock);
	}
}

void MissionManagerImplementation::sendMissionBase(Player* player, uint64& oid, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(oid);

		if (miso != NULL) {
			miso->sendTo(player, true);
		} else {
			error("Invalid mission attempting to be sent. sendMissionBase (id)");
		}

		unlock(doLock);
	} catch (...) {
	error("unreported Exception caught on sendMissionBase() (objid version)");

	unlock(doLock);
	}
}

void MissionManagerImplementation::sendMissionBase(Player* player, MissionObject* sMiso) {
	sMiso->sendTo(player, true);
}

void MissionManagerImplementation::sendMissionDelta(Player* player, const String& tKey, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(tKey);

		if (miso != NULL) {
			miso->sendDeltaTo(player);
		} else {
			error("Invalid mission attempting to be sent. sendMissionDelta (key)");
		}

		unlock(doLock);
	} catch (...) {
	error("unreported Exception caught on sendMissionDelta() (key version)");

	unlock(doLock);
	}
}

void MissionManagerImplementation::sendMissionDelta(Player* player, uint64& oid, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(oid);

		if (miso != NULL) {
			miso->sendDeltaTo(player);
		} else {
			error("Invalid mission attempting to be sent. sendMissionDelta (id)");
		}

		unlock(doLock);
	} catch (...) {
	error("unreported Exception caught on sendMissionDelta() (objid version)");

	unlock(doLock);
	}
}

void MissionManagerImplementation::sendMissionDelta(Player* player, MissionObject* sMiso) {
	sMiso->sendDeltaTo(player);
}

void MissionManagerImplementation::removeMisoFromPool(MissionObject* miso, bool doLock) {
	try {
		lock(doLock);

		misoMap->remove(miso->getObjectID());

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on removeMisoFromPool()");

		unlock(doLock);
	}
}

void MissionManagerImplementation::removeMisoFromPlayer(Player* player, const String& tKey, bool doLock) {
	MissionObject* miso;

	try {
		lock(doLock);

		miso = misoMap->get(tKey);

		if (miso != NULL) {
			miso->sendDestroyTo(player);
		} else {
			error("Invalid mission attempting to be removed from player. removeMisoFromPlayer (key)");
		}

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on removeMisoFromPlayer() (db key)");

		unlock(doLock);
	}
}

void MissionManagerImplementation::removeMisoFromPlayer(Player* player, uint64& oid, bool doLock) {
	MissionObject* miso;

	try {
		lock(doLock);

		miso = misoMap->get(oid);

		if (miso != NULL) {
			miso->sendDestroyTo(player);
		} else {
			error("Invalid mission attempting to be removed from player. removeMisoFromPlayer (id)");
		}

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on removeMisoFromPlayer() (objid)");

		unlock(doLock);
	}

	if (miso == NULL)
		return;
}

void MissionManagerImplementation::removeMisoFromPlayer(MissionObject* miso, Player* player) {
	miso->sendDestroyTo(player);
}

void MissionManagerImplementation::removeMissions() {
	for (int i = 0; i < misoMap->size(); ++i) {
		MissionObject* miso = misoMap->get(i);
		miso->finalize();
	}

	misoMap->removeAll();
}

//Script Functions:

void MissionManagerImplementation::registerFunctions() {
	lua_register(getLuaState(), "RunMissionFile", runMissionFile);
	lua_register(getLuaState(), "AddMissionToServer", addMissionToServer);
}

void MissionManagerImplementation::registerGlobals() {
	//Terminal Masks:
	setGlobalInt("TMASK_GENERAL", 1);
	setGlobalInt("TMASK_ENTERTAINER", 2);
	setGlobalInt("TMASK_EXPLORER", 4);
	setGlobalInt("TMASK_BOUNTY", 8);
	setGlobalInt("TMASK_ARTISAN", 16);
	setGlobalInt("TMASK_REBEL", 32);
	setGlobalInt("TMASK_IMPERIAL", 64);
}

void MissionManagerImplementation::loadMissionScripts() {
	runFile("scripts/mission/main.lua");
}

int MissionManagerImplementation::runMissionFile(lua_State* L) {
	String filename = getStringParameter(L);

	runFile("scripts/mission/" + filename, L);

	return 0;
}

int MissionManagerImplementation::addMissionToServer(lua_State* L) {
	LuaObject mission(L);

	String dbKey = "";

	if (!mission.isValidTable())
		return 1;

	try {
		instance->lock();

		//Server Vars
		dbKey = mission.getStringField("missionKey");
		if(dbKey.length() == 0) {
			System::out << "Mission script: mission key not provided\n";
			return 1;
		}

		// Title/Name
		String tempk = mission.getStringField("stfTitleKey");
		uint32 stfTitleKey = htonl(Integer::valueOf(tempk));
		String titleStf = mission.getStringField("titleStf");
		String customTitle = mission.getStringField("customTitle");

		// General: (type, terminal)
		int terminalMask = mission.getIntField("terminalMask");
		String typeStr = mission.getStringField("typeStr");
		uint32 typeCrc = mission.getIntField("typeCrc");
		String creatorName = mission.getStringField("creatorName");
		int difficultyLevel = mission.getIntField("difficultyLevel");

		// Location: Start (npc assigner)
		float startX = mission.getFloatField("startX");
		float startY = mission.getFloatField("startY");
		uint32 startPlanetCrc = Planet::getPlanetCRC(mission.getStringField("startPlanetStr"));

		// Location: Destination (target)
		float destX = mission.getFloatField("destinationX");
		float destY = mission.getFloatField("destinationY");
		uint32 destPlanetCrc = Planet::getPlanetCRC(mission.getStringField("destinationPlanetStr"));

		// Rewards
		int rewardCredits = mission.getIntField("rewardCredits");
		String rewardXp = mission.getStringField("rewardXP");
		String rewardBadgeIds = mission.getStringField("rewardBadgeIds");
		String rewardFactions = mission.getStringField("rewardFactions");
		String rewardObjects = mission.getStringField("rewardObjects");

		// Description
		tempk = mission.getStringField("stfDescriptionKey");
		uint32 stfDescriptionKey = htonl(Integer::valueOf(tempk));
		String descriptionStf = mission.getStringField("descriptionStf");
		String customDescription = mission.getStringField("customDescription");

		//Objective & target
		String targetName = mission.getStringField("targetName");
		uint32 depictedObjCrc = mission.getIntField("depictedObjectCrc");
		String objectives = mission.getStringField("objectiveDefaults");
		bool instantComplete = mission.getByteField("instantComplete");

		///////////
		//Create Mission Object, set vars
		///////////
		MissionObject* miso = new MissionObject(instance->getNextMissionID());

		//Server Vars
		miso->setDBKey(dbKey);

		// Title/Name
		miso->setTitleKey(stfTitleKey);
		miso->setTitleStf(titleStf);
		miso->setTitle(customTitle);

		// General: (type, terminal)
		miso->applyTerminalMask(terminalMask);
		miso->setTypeStr(typeStr);
		miso->setTypeCrc(typeCrc);
		miso->setCreatorName(creatorName);
		miso->setDifficultyLevel(difficultyLevel);

		// Location: Start (npc assigner)
		miso->setTargetX(startX);
		miso->setTargetY(startY);
		miso->setTargetPlanetCrc(startPlanetCrc);

		// Location: Destination (target)
		miso->setDestX(destX);
		miso->setDestY(destY);
		miso->setDestPlanetCrc(destPlanetCrc);

		// Rewards
		miso->setRewardCredits(rewardCredits);
		/*String rewardXp = mission.getStringField("rewardXP");
		String rewardBadgeIds = mission.getStringField("rewardBadgeIds");
		String rewardFactions = mission.getStringField("rewardFactions");
		String rewardObjects = mission.getStringField("rewardObjects");*/

		// Description
		miso->setDescKey(stfDescriptionKey);
		miso->setDescriptionStf(descriptionStf);
		miso->setDescription(customDescription);

		//Objective & target
		miso->setTargetName(targetName);
		miso->setDepictedObjCrc(depictedObjCrc);
		miso->setObjectiveDefaults(objectives);
		miso->setInstantComplete(instantComplete);

		//Add mission to pool:
		instance->poolMission(miso, false);

		instance->unlock();
	} catch (...) {

		System::out << "Failed to load mission script: " << dbKey << endl;
		instance->unlock();
	}

	return 0;
}

uint64 MissionManagerImplementation::getNextMissionID() {
	return zoneServer->getNextID();
}

