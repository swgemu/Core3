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

	// Temporary Hardcode missions
	//setupHardcodeMissions();
}

void MissionManagerImplementation::unloadManager() {
}

//Standard Functions:
MissionObject* MissionManagerImplementation::poolMission(const String& dbKey, int termMask, const String& typeStr, uint32 descKey, uint32 titleKey, uint32 diffLv, float destX, float destY, uint32 destPlanetCrc,
		const String& creatorName, uint32 rewardAmount, float targetX, float targetY, uint32 targetPlanetCrc, uint32 depictedObjCrc, const String& targetName,
		const String& description, const String& title, uint32 typeCrc, const String& objectiveDefaults, bool instantComplete, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = new MissionObject(getNextMissionID());
		miso->deploy();

		//Internal key that we use to identify the mission, referenced in db. Set in script.
		miso->setDBKey(dbKey);
		miso->applyTerminalMask(termMask);

		miso->setTypeStr(typeStr);
		//miso->setDescKey(descKey);
		//miso->setTitleKey(titleKey);
		miso->setDifficultyLevel(diffLv);

		miso->setDestX(destX);
		miso->setDestY(destY);
		miso->setDestPlanetCrc(destPlanetCrc);

		miso->setTargetName(targetName);
		miso->setCreatorName(UnicodeString(creatorName));
		miso->setReward(rewardAmount);

		miso->setTargetX(targetX);
		miso->setTargetY(targetY);
		miso->setTargetPlanetCrc(targetPlanetCrc);

		miso->setDepictedObjCrc(depictedObjCrc);
		//miso->setDescriptionStf(descriptionStf);
		//miso->setTitleStf(titleStf);
		miso->setTitle(title);
		miso->setDescription(description);
		miso->setTypeCrc(typeCrc);

		miso->setObjectiveDefaults(objectiveDefaults);
		miso->setInstantComplete(instantComplete);

		//load(miso);

		if (misoMap->get(dbKey) != NULL) {
			String err = "Mission Key Collision with " + dbKey;
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
void MissionManagerImplementation::instanceMission(Player* player, MissionObject* misoCopy, const String& objectives) {
	if(misoCopy == NULL/* || objectives.isEmpty()*/) {
		System::out << "instanceMission: misoCopy is null or objectives is empty. objectives: " << objectives << endl;
		return;
	}

	//object id can be the same, no need to waste id space. Also set owner object
	MissionObject* miso = new MissionObject(misoCopy->getObjectID(), player);
	miso->deploy();

	miso->lock();

	// Clone vars:
	miso->setDBKey(misoCopy->getDBKey());
	miso->applyTerminalMask(misoCopy->getTerminalMask());
	miso->setTypeStr(misoCopy->getTypeStr());
	miso->setDifficultyLevel(misoCopy->getDifficultyLevel());
	miso->setDestX(misoCopy->getDestX());
	miso->setDestY(misoCopy->getDestY());
	miso->setDestPlanetCrc(misoCopy->getDestPlanetCrc());
	miso->setTargetName(misoCopy->getTargetName());
	miso->setCreatorName(misoCopy->getCreatorName());
	miso->setReward(misoCopy->getReward());
	miso->setTargetX(misoCopy->getTargetX());
	miso->setTargetY(misoCopy->getTargetY());
	miso->setTargetPlanetCrc(misoCopy->getTargetPlanetCrc());
	miso->setDepictedObjCrc(misoCopy->getDepictedObjCrc());
	miso->setDescription(misoCopy->getDescription());
	miso->setTitle(misoCopy->getTitle());
	miso->setTypeCrc(misoCopy->getTypeCrc());
	miso->setInstantComplete(misoCopy->isInstantComplete());

	//Spawn objectives:
	miso->spawnObjectives(objectives);

	//Add the mission to the player:
	player->addMission(miso->getDBKey(), miso);

	//Setup Mission assets
	miso->assetSetup();

	miso->unlock();
}

void MissionManagerImplementation::setupHardcodeMissions() {
}

//terminal
void MissionManagerImplementation::sendTerminalData(Player* player, int termBitmask, bool doLock) {
	try {
		lock(doLock);

		for (int i = 0; i < misoMap->size(); i++) {
			MissionObject* miso = misoMap->get(i);
			if (miso == NULL)
				continue;

			//Do planet mission check here using the current player class:

			//Check if player is already on mission:
			if (player->isOnCurMisoKey(miso->getDBKey()))
				continue;

			if(player->getMisoRFC() == 0x01) {
				sendMissionBase(player, miso);
			} else {
				sendMissionDelta(player, miso);
			}
		}

		player->nextMisoRFC();

			//Make sure the terminal and mission in the misoMap are in the same category:

			/*if ((termBitmask & TMASK_GENERAL) && (miso->getTerminalMask() & TMASK_GENERAL)) {
				if (player->getMisoRFC() == 0x01)
					sendMissionBase(player, miso);
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_ENTERTAINER) && (miso->getTerminalMask() & TMASK_ENTERTAINER)) {
				if (player->getMisoRFC() == 0x01)
					sendMissionBase(player, miso);
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_EXPLORER) && (miso->getTerminalMask() & TMASK_EXPLORER)) {
				if (player->getMisoRFC() == 0x01)
					sendMissionBase(player, miso);
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_BOUNTY) && (miso->getTerminalMask() & TMASK_BOUNTY)) {
				if (player->getMisoRFC() == 0x01)
					sendMissionBase(player, miso);
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_ARTISAN) && (miso->getTerminalMask() & TMASK_ARTISAN)) {
				if (player->getMisoRFC() == 0x01)
					sendMissionBase(player, miso);
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_REBEL) && (miso->getTerminalMask() & TMASK_REBEL)) {
				if (player->getMisoRFC() == 0x01)
					sendMissionBase(player, miso);
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_IMPERIAL) && (miso->getTerminalMask() & TMASK_IMPERIAL)) {
				if (player->getMisoRFC() == 0x01)
					sendMissionBase(player, miso);
				sendMissionDelta(player, miso);
				continue;
			}
		}*/

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on sendTerminalData()");

		unlock(doLock);
	}
}

void MissionManagerImplementation::sendMission(Player* player, const String& tKey, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(tKey);

		if (miso == NULL) {
			error("miso object is NULL, exiting function: sendMission()");
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

		MissionObject* miso = misoMap->get(oid);
		if (miso == NULL) {
			error("miso object is NULL, exiting function: doMissionAccept()");
			unlock(doLock);
			return;
		}

		//Check if player is already on mission:
		if (player->isOnCurMisoKey(miso->getDBKey()))
			return;

		// Give the mission to the player:
		miso->doLinkToPlayer(player);
		instanceMission(player, miso, miso->getObjectiveDefaults());
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

		//Remove any mission save from the DB:
		deleteMissionSave(player, tKey);

		//Drop the mission from the the player
		removeMisoFromPlayer(player, tKey, false);
		player->dropMission(tKey, true);
		player->sendSystemMessage("Mission Complete.");

		// Play mission complete music:
		PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
		player->sendMessage(pmm);

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

//Loads all missions for a player from mission_saves:
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

			sendMissionBase(player, miso);
			sendMissionDelta(player, miso);
			miso->doLinkToPlayer(player);

			// Instance the mission for the player:
			instanceMission(player, misoMap->get(misoKey), objectiveSer);
		}

		delete res;


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

		if (resFin->next())
			player->setFinishedMissionKeys(resFin->getString(0));

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

	//player->removeAllInventoryByMisoKey(miso->getDBKey());
}

void MissionManagerImplementation::removeMisoFromPlayer(MissionObject* miso, Player* player) {
	miso->sendDestroyTo(player);

	//player->removeAllInventoryByMisoKey(miso->getDBKey());
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

		int terminalMask = mission.getIntField("terminalMask");

		//Basic mission info setup:
		String typeStr = mission.getStringField("typeStr");

		String tempk = mission.getStringField("stfDescriptionKey");
		uint32 stfDescriptionKey = htonl(Integer::valueOf(tempk));
		tempk = mission.getStringField("stfTitleKey");
		uint32 stfTitleKey = htonl(Integer::valueOf(tempk));

		int difficultyLevel = mission.getIntField("difficultyLevel");

		float destX = mission.getFloatField("destinationX");
		float destY = mission.getFloatField("destinationY");
		//String targetName = mission.getStringField("targetName");
		uint32 destPlanetCrc = Planet::getPlanetCRC(mission.getStringField("destinationPlanetStr"));

		String creatorName = mission.getStringField("creatorName");
		int rewardAmount = mission.getIntField("rewardAmount");

		float startX = mission.getFloatField("startX");
		float startY = mission.getFloatField("startY");
		uint32 startPlanetCrc = Planet::getPlanetCRC(mission.getStringField("startPlanetStr"));

		String targetName = mission.getStringField("targetName");
		uint32 depictedObjCrc = mission.getIntField("depictedObjectCrc");
		String descriptionStf = mission.getStringField("descriptionStf");
		if(descriptionStf.length() == 0) {
			descriptionStf = mission.getStringField("customDescription");
		}
		String titleStf = mission.getStringField("titleStf");
		if(titleStf.length() == 0) {
			titleStf = mission.getStringField("customTitle");
		}

		uint32 typeCrc = mission.getIntField("typeCrc");

		//Objectives:
		String objectives = mission.getStringField("objectiveDefaults");
		bool instantComplete = mission.getByteField("instantComplete");

		//Add mission to pool:
		instance->poolMission(dbKey, terminalMask, typeStr, stfDescriptionKey, stfTitleKey, difficultyLevel, destX, destY, destPlanetCrc,
				creatorName, rewardAmount, startX, startY, startPlanetCrc, depictedObjCrc, targetName,
				descriptionStf, titleStf, typeCrc, objectives, instantComplete, false);

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

