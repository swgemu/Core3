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

	setLogging(true); //set to false after debugging
	setGlobalLogging(true);

	init();
}

MissionManagerImplementation::~MissionManagerImplementation() {
	removeMissions();

	delete misoMap;
	misoMap = NULL;
}

void MissionManagerImplementation::init() {
	lock();
	// Scripting
	/*Lua::init();
	registerFunctions();
	registerGlobals();*/
	instance = this;
	//loadMissionScripts();

	// Temporary Hardcode missions
	setupHardcodeMissions();
	unlock();
}

void MissionManagerImplementation::unloadManager() {
}

//Standard Functions:
MissionObject* MissionManagerImplementation::poolMission(const String& dbKey, int termMask, const String& typeStr, uint32 descKey, uint32 titleKey, uint32 diffLv, float destX, float destY, uint32 destPlanetCrc,
		const String& creatorName, uint32 rewardAmount, float targetX, float targetY, uint32 targetPlanetCrc, uint32 depictedObjCrc,
		const String& descriptionStf, const String& titleStf, uint32 typeCrc, const String& objectiveDefaults, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = new MissionObject(getNextMissionID());
		miso->deploy();

		//Internal key that we use to identify the mission, referenced in db. Set in script.
		miso->setDBKey(dbKey);
		miso->applyTerminalMask(termMask);

		miso->setTypeStr(typeStr);
		miso->setDescKey(descKey);
		miso->setTitleKey(titleKey);
		miso->setDifficultyLevel(diffLv);

		miso->setDestX(destX);
		miso->setDestY(destY);
		miso->setDestPlanetCrc(destPlanetCrc);

		miso->setCreatorName(UnicodeString(creatorName));
		miso->setReward(rewardAmount);

		miso->setTargetX(targetX);
		miso->setTargetY(targetY);
		miso->setTargetPlanetCrc(targetPlanetCrc);

		miso->setDepictedObjCrc(depictedObjCrc);
		miso->setDescriptionStf(descriptionStf);
		miso->setTitleStf(titleStf);
		miso->setMissionName(titleStf);
		miso->setTypeCrc(typeCrc);

		miso->setObjectiveDefaults(objectiveDefaults);

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
	miso->setDescKey(misoCopy->getDescKey());
	miso->setTitleKey(misoCopy->getTitleKey());
	miso->setDifficultyLevel(misoCopy->getDifficultyLevel());
	miso->setDestX(misoCopy->getDestX());
	miso->setDestY(misoCopy->getDestY());
	miso->setDestPlanetCrc(misoCopy->getDestPlanetCrc());
	miso->setCreatorName(misoCopy->getCreatorName());
	miso->setReward(misoCopy->getReward());
	miso->setTargetX(misoCopy->getTargetX());
	miso->setTargetY(misoCopy->getTargetY());
	miso->setTargetPlanetCrc(misoCopy->getTargetPlanetCrc());
	miso->setDepictedObjCrc(misoCopy->getDepictedObjCrc());
	miso->setDescriptionStf(misoCopy->getDescriptionStf());
	miso->setTitleStf(misoCopy->getTitleStf());
	miso->setTypeCrc(misoCopy->getTypeCrc());

	//Spawn objectives:
	miso->spawnObjectives(objectives);

	//Add the mission to the player:
	player->addMission(miso->getDBKey(), miso);

	//Setup Mission assets
	miso->assetSetup();

	miso->unlock();
}

void MissionManagerImplementation::setupHardcodeMissions() {
	String dbKey = "";
	dbKey = "testM27";
	int tmask = TMASK_GENERAL; //terminal mask (GENERAL)
	String typeStr = "mission_deliver";
	String objectiveDefaults = "1:1217993661:0:2:null:0";
	//HAS_KILLS:humbaba_crc:none killed:kill limit 2:null str var:not a failure on complete

	//uint32 descKey = htonl(atoi("m27d"));
	//uint32 titleKey = htonl(atoi("m27t"));
	//For custom missions:
	uint32 descKey = 0;
	uint32 titleKey = 0;

	uint32 diffLv = 1;
	float destX = -5049.0f;
	float destY = 4225.0f;
	uint32 destPlanetCrc = Planet::getPlanetCRC("corellia");
	String creatorName = "Ramsey";
	uint32 rewardAmount = 50;
	float targetX = -4844.0f;
	float targetY = 4155.0f;
	uint32 targetPlanetCrc = Planet::getPlanetCRC("corellia");
	uint32 depictedObjCrc = 0x9BA06548; //holocron/secret box crc

	//String descriptionStf = "mission/mission_deliver_neutral_easy";
	//String titleStf = "mission/mission_deliver_neutral_easy";
	//For custom missions:
	String descriptionStf = "Test Description";
	String titleStf = "The Kill";

	uint32 typeCrc = 0xE5C27EC6; //0xC6, 0x7E, 0xC2, 0xE5, //crc("deliver");

	poolMission(dbKey, tmask, typeStr, descKey, titleKey, diffLv, destX, destY, destPlanetCrc,
			creatorName, rewardAmount, targetX, targetY, targetPlanetCrc, depictedObjCrc,
			descriptionStf, titleStf, typeCrc, objectiveDefaults, true);
}

//terminal
void MissionManagerImplementation::sendTerminalData(Player* player, int termBitmask, bool doLock) {
	try {
		lock(doLock);

		int sentBases = 0;

		for (int i = 0; i < misoMap->size(); i++) {
			MissionObject* miso = misoMap->get(i);
			if (miso == NULL)
				continue;

			//Do planet mission check here using the current player class:

			//Check if player is already on mission:
			if (player->isOnCurMisoKey(miso->getDBKey())) {
				//error("player is already on mission, continuing to next miso in list.");
				continue;
			}

			//Make sure the terminal and mission in the misoMap are in the same category:

			if ((termBitmask & TMASK_GENERAL) && (miso->getTerminalMask() & TMASK_GENERAL)) {
				if (!player->checkMisoBSB(TMASK_GENERAL)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_GENERAL;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_ENTERTAINER) && (miso->getTerminalMask() & TMASK_ENTERTAINER)) {
				if (!player->checkMisoBSB(TMASK_ENTERTAINER)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_ENTERTAINER;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_EXPLORER) && (miso->getTerminalMask() & TMASK_EXPLORER)) {
				if (!player->checkMisoBSB(TMASK_EXPLORER)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_EXPLORER;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_BOUNTY) && (miso->getTerminalMask() & TMASK_BOUNTY)) {
				if (!player->checkMisoBSB(TMASK_BOUNTY)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_BOUNTY;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_ARTISAN) && (miso->getTerminalMask() & TMASK_ARTISAN)) {
				if (!player->checkMisoBSB(TMASK_ARTISAN)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_ARTISAN;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_REBEL) && (miso->getTerminalMask() & TMASK_REBEL)) {
				if (!player->checkMisoBSB(TMASK_REBEL)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_REBEL;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_IMPERIAL) && (miso->getTerminalMask() & TMASK_IMPERIAL)) {
				if (!player->checkMisoBSB(TMASK_IMPERIAL)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_IMPERIAL;
				}
				sendMissionDelta(player, miso);
				continue;
			}
		}

		player->setMisoBSB(sentBases);

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

//events:
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
		if (player->isOnCurMisoKey(miso->getDBKey())) {
			//error("Player is already on mission!");
			return;
		}

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

void MissionManagerImplementation::doMissionComplete(Player* player, const String& tKey, bool doLock) {
	try {
		lock(doLock);

		//Remove any mission save from the DB:
		deleteMissionSave(player, tKey, false);

		//Drop the mission from the the player
		removeMisoFromPlayer(player, tKey, false);
		player->dropMission(tKey, true);
		player->sendSystemMessage("Mission Complete.");
		//PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
		//player->sendMessage(pmm);

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionComplete()\n");

		unlock(doLock);
	}
}

void MissionManagerImplementation::doMissionAbort(Player* player, uint64& oid, bool doLock) {
	try {
		lock(doLock);

		MissionObject* miso = misoMap->get(oid);
		if (miso == NULL) {
			error("miso object is NULL, exiting function: doMissionAbort()");
			unlock(doLock);
			return;
		}

		String misoKey = miso->getDBKey();

		//Remove any mission save from the DB:
		deleteMissionSave(player, misoKey, false);

		//Drop the mission from the player
		player->dropMission(misoKey, false);
		removeMisoFromPlayer(miso, player);
		player->sendSystemMessage("Mission Failed.");

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

		//Remove any mission save from the DB:
		deleteMissionSave(player, tKey, false);

		//Drop the mission from the player
		player->dropMission(tKey, false);
		removeMisoFromPlayer(miso, player);
		player->sendSystemMessage("Mission Failed.");

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAbort()");

		unlock(doLock);
	}
}

//Initiate reward calcs, kill counts etc for a mission. Called when player objectives need to be evaluated
//This will call doMissionComplete (on completion) and abort (if failed)
//The retSay is an update on the status of the mission. Can be "said" by an NPC or systemMsg
//ex. You do not have: ___. You have not killed enough _____ or even: You are not assigned to any of my missions
void MissionManagerImplementation::evalMission(Player* player, const String& tKey, String& retSay) {
	MissionObject* miso = player->getPlayerMission(tKey);
	if(miso == NULL)
		return;

	// checkComplete() in MissionObject should have already been called after a condition was updated.
	// Run the appropriate event handler and build the return string
	if(miso->isFailure()) {
		doMissionAbort(player, tKey, false);
		//retSay = miso->getStatusStr() + ". You have violated a condition of the mission...come back when you are competent.";
		retSay = "You have violated a condition of the mission...come back when you are competent.";
	} else if(miso->isComplete()) {
		doMissionComplete(player, tKey, false);
		//retSay = miso->getStatusStr() + ". Thank you! You have done exactly what was asked.";
		retSay = "Thank you! You have done exactly what was asked.";
	} else {
		//retSay = miso->getStatusStr() + ". You have not completed all mission conditions.";
		retSay = "You have not completed all mission conditions.";
	}
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
				error("miso object is NULL: loadPlayerMissions");
				unlock(doLock);
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
void MissionManagerImplementation::savePlayerMission(Player* player, MissionObject* miso, bool doLock) {
	ResultSet* msRes;

	try {
		lock(doLock);

		if(miso == NULL) {
			System::out << "Miso is null in savePlayerMission, from player: " << player->getFirstName() << endl;
			return;
		}

		// Get the mission key and serialized object strings:
		String mkey = miso->getDBKey();
		String objectiveSer = "";
		miso->serializeObjectives(objectiveSer);

		if(mkey.isEmpty()/* || objectiveSer.isEmpty()*/) {
			System::out << "Miso key or objectiveSer is empty in savePlayerMission, from player: " << player->getFirstName() << endl;
			return;
		}

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

		unlock(doLock);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::savePlayerMission()");
	} catch (...) {
		error("unreported Exception caught on savePlayerMission()");

		unlock(doLock);
	}

	delete msRes;
}

void MissionManagerImplementation::deleteMissionSave(Player* player, const String& mkey, bool doLock) {
	try {
		lock(doLock);

		StringBuffer query;
		query << "DELETE FROM mission_save WHERE character_id = " << player->getCharacterID() << " and ";
		query << "miso_key = '" << mkey << "';";
		ServerDatabase::instance()->executeStatement(query.toString());

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::deleteMissionSave()");
	} catch (...) {
		error("unreported Exception caught on deleteMissionSave()");

		unlock(doLock);
	}
}

void MissionManagerImplementation::savePlayerKeys(Player* player, const String& curMisoKeys, const String& finMisoKeys, bool doLock) {
	try {
		lock(doLock);

		StringBuffer qUpdate;

		qUpdate << "UPDATE characters set currentMissionKeys = '" << curMisoKeys << "', finishedMissionKeys = '" << finMisoKeys << "' "
			<< "WHERE character_id = " << player->getCharacterID();

		ServerDatabase::instance()->executeStatement(qUpdate);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::deleteMissionSave()");
	} catch (...) {
		error("unreported Exception caught on deleteMissionSave()");

		unlock(doLock);
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

	player->removeAllInventoryByMisoKey(miso->getDBKey());
}

void MissionManagerImplementation::removeMisoFromPlayer(MissionObject* miso, Player* player) {
	miso->sendDestroyTo(player);

	player->removeAllInventoryByMisoKey(miso->getDBKey());
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
	//lua_register(getLuaState(), "RunMissionFile", runMissionFile);
	//lua_register(getLuaState(), "AddMissionToServer", addMissionToServer);
}

void MissionManagerImplementation::registerGlobals() {
	/*//Terminal Masks:
	setGlobalInt("TMASK_GENERAL", 1);
	setGlobalInt("TMASK_ENTERTAINER", 2);
	setGlobalInt("TMASK_EXPLORER", 4);
	setGlobalInt("TMASK_BOUNTY", 8);
	setGlobalInt("TMASK_ARTISAN", 16);
	setGlobalInt("TMASK_REBEL", 32);
	setGlobalInt("TMASK_IMPERIAL", 64);

	//Action Masks:
	setGlobalInt("ATYPE_MOVE", 1);
	setGlobalInt("ATYPE_PATROL", 2);
	setGlobalInt("ATYPE_CONVERSE", 4);
	setGlobalInt("ATYPE_SAY", 8);
	setGlobalInt("ATYPE_GIVEITEM", 16);
	setGlobalInt("ATYPE_TAKEITEM", 32);
	setGlobalInt("ATYPE_GIVEMISSION", 64);
	setGlobalInt("ATYPE_COMPMISSION", 128);
	setGlobalInt("ATYPE_FAILMISSION", 256);
	setGlobalInt("ATYPE_ADDKILL", 512);

	//Action Prereq:
	setGlobalInt("AMEET_HASMISSION", 1);
	setGlobalInt("AMEET_KILLCOUNTLIMIT", 2);*/
}

void MissionManagerImplementation::loadMissionScripts() {
	//runFile("scripts/mission/main.lua");
}

int MissionManagerImplementation::runMissionFile(lua_State* L) {
	/*String filename = getStringParameter(L);

	runFile("scripts/mission/" + filename, L);

	return 0;*/
}

int MissionManagerImplementation::addMissionToServer(lua_State* L) {
	/*LuaObject mission(L);

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
		uint32 destPlanetCrc = Planet::getPlanetCRC(mission.getStringField("destinationPlanetStr"));

		String creatorName = mission.getStringField("creatorName");
		int rewardAmount = mission.getIntField("rewardAmount");

		float startX = mission.getFloatField("startX");
		float startY = mission.getFloatField("startY");
		uint32 startPlanetCrc = Planet::getPlanetCRC(mission.getStringField("startPlanetStr"));

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

		//Add mission to pool:
		instance->poolMission(dbKey, terminalMask, typeStr, stfDescriptionKey, stfTitleKey, difficultyLevel, destX, destY, destPlanetCrc,
				creatorName, rewardAmount, startX, startY, startPlanetCrc, depictedObjCrc,
				descriptionStf, titleStf, typeCrc, NULL, false);

		instance->unlock();
	} catch (...) {

		System::out << "Failed to load mission script: " << dbKey << endl;
		instance->unlock();
	}

	return 0;*/
}
/*
int MissionManagerImplementation::addActionCreatureToServer(lua_State* L) {
	int actCount = lua_gettop(L);
	ActionCreature* actCreature;

	for(int i = actCount; i >= 1; i--) {

		if(i == actCount) {
			actCreature = addActionCreature(L, i);
		} else {
			if(actCreature != NULL) {
				addAction(L, i, actCreature);
			}
		}
		lua_settop(L, i-1);
	}

	//Clear stack
	lua_settop(L, 0);

	return 0;
}

ActionCreature* MissionManagerImplementation::addActionCreature(lua_State* L, int sIdx) {
	char numBuf[10];
	sprintf(numBuf,"%d",sIdx);
	LuaObject creatureConfig(L, numBuf);
	ActionCreature* creature;

	if (!creatureConfig.isValidTable())
		return NULL;

	try {
		instance->lock();

		String objectName = creatureConfig.getStringField("objectName");

		String stfname = creatureConfig.getStringField("stfName");
		String name = creatureConfig.getStringField("name");
		String speciesName = creatureConfig.getStringField("speciesName");

		String misoKey = creatureConfig.getStringField("missionKey");

		int planet = creatureConfig.getIntField("planet");
		if(planet == -1) {
			System::out << "Planet not set in ActionCreature script. Mission Key = " << misoKey << ", ActionCreature Name = " << name << endl;
			return NULL;
		}

		CreatureManager* cm = instance->zoneServer->getCreatureManager(planet);
		creature = new ActionCreature(0, creatureConfig.getIntField("objectCRC"), name, stfname, misoKey);
		creature->deploy();
		creature->setObjectCRC(creatureConfig.getIntField("objectCRC"));

		if (!stfname.isEmpty() && !speciesName.isEmpty()) {
			creature->setStfFile(stfname);
			creature->setStfName(speciesName);
		} else if (!stfname.isEmpty()) {
			creature->setCharacterName(stfname);
		}

		instance->setCreatureAttributes(creature, &creatureConfig);

		uint64 cellID = creatureConfig.getLongField("cellID");

		float x = creatureConfig.getFloatField("positionX");
		float y = creatureConfig.getFloatField("positionY");
		float z = creatureConfig.getFloatField("positionZ");

		float oY = creatureConfig.getFloatField("directionY");
		float oX = creatureConfig.getFloatField("directionX");
		float oW = creatureConfig.getFloatField("directionW");
		float oZ = creatureConfig.getFloatField("directionZ");

		uint8 randMovement = creatureConfig.getByteField("randomMovement");

		creature->setRandomMovement(randMovement);

		creature->initializePosition(x, z, y);

		creature->setDirection(oX, oZ, oY, oW);

		uint32 creatureBitmask = creatureConfig.getIntField("creatureBitmask");
		if (creatureBitmask != 0)
			creature->setOptionsBitmask(creatureBitmask);

		creature->setSpawnPosition(x, z, y, cellID);

		creature->setMisoMgr(instance);

		//TODO: Ramsey...:
		//Is this calling the "wrong" function ?
		//It's calling spawnActionCreature(ActionCreature* tac, bool doLock = true);
		//But i think it should call:
		//ActionCreature* spawnActionCreature(String& name, String& stfname, uint32 objCrc, const String misoKey, float x, float y, float oY, float oW, uint64 cellid = 0, bool doLock = true);

		//Changing/fixing the compiler warning for now:
		//cm->spawnActionCreature(creature, &creatureConfig);
		cm->spawnActionCreature(creature, true);

		instance->unlock();
	} catch (...) {
		System::out << "Failed to load action creature in mission script." << endl;
		instance->unlock();
	}

	return creature;
}

void MissionManagerImplementation::addAction(lua_State* L, int sIdx, ActionCreature* actCreature) {
	char numBuf[10];
	sprintf(numBuf,"%d",sIdx);
	LuaObject actionConfig(L, numBuf);
	String actionKey = "";
	Action* action = new Action((SceneObject*)actCreature, actionKey, 0, 0);

	if (!actionConfig.isValidTable())
		return;

	try {
		instance->lock();

		actionKey = actionConfig.getStringField("actionKey");
		action->setActionKey(actionKey);

		int prereqMask = actionConfig.getIntField("prereqMask");
		action->setPrereq(prereqMask);

		int actionMask = actionConfig.getIntField("actionMask");
		action->setActionMask(actionMask);

		// Load Optional Triggers: (set in ActionCreature later)
		bool onConverse = actionConfig.getByteField("onConverse");
		if(onConverse)
			actCreature->onConverse(actionKey);

		bool onTrade = actionConfig.getByteField("onTrade");
		if(onTrade)
			actCreature->onTrade(actionKey);

		bool onAttack = actionConfig.getByteField("onAttack");
		if(onAttack)
			actCreature->onAttack(actionKey);

		bool onDeath = actionConfig.getByteField("onDeath");
		if(onDeath)
			actCreature->onDeath(actionKey);

		/////////////////////
		// Prereq Vars
		/////////////////////

		//prereq:HASMISSION:
		String hasMisoKey = actionConfig.getStringField("meet_hasMission");
		action->setMeetHasMission(hasMisoKey);

		//prereq:killcountlimit
		String killCountLimitList = actionConfig.getStringField("meet_killLimitList");
		action->setMeetKillLimitList(killCountLimitList);

		/////////////////////
		// ACTION VARS
		/////////////////////

		//Action:GiveItem:

		if((actionMask & ATYPE_GIVEITEM)) {

		}

		//Action:Conversation:
		if ((actionMask & ATYPE_CONVERSE)) {
			//Grab list with convo screen ids
			String convoScreenList = actionConfig.getStringField("convoScreenList");

			//Parse convoScreenList String (format: key,key,key,")
			StringTokenizer cslist(convoScreenList);
			cslist.setDelimeter(",");
			String sid = "";

			//Loop through screen keys, grab screen from from the lua table. Parse. Add to C action convo screens
			while (cslist.hasMoreTokens()) {
				cslist.getStringToken(sid);

				if (!sid.isEmpty()) {
					//Call lua function "getConvoScreen(id)" to grab conversation screen from table:
					LuaFunction getConvoScreen(L, "getConvoScreen", 1);
					getConvoScreen << sid.toCharArray(); // push first argument
					callFunction(&getConvoScreen);

					//Parse lua screen object:
					LuaObject retScreen(L);
					if (!retScreen.isValidTable())
						return;

					//Get screen id
					String screenId = retScreen.getStringField("id");

					//Get dialog (left) box for the current screen
					String leftBox = retScreen.getStringField("leftDialog");

					//Get option count
					int optCount = retScreen.getIntField("optionCount");

					//Get compiled options String
					String compOptionText = retScreen.getStringField("compOptionText");

					//Get compiled option links
					String compOptionLinks = retScreen.getStringField("compOptionLinks");

					//Add the screen to the action
					action->addConvoScreen(screenId, leftBox, optCount, compOptionText, compOptionLinks);

					retScreen.pop(); // remove screen from stack
				}
			}
			//Call lua function "clearGlobalScreens()". Cleans up for next actions
			LuaFunction clearScreenTable(L, "clearScreenTable", 0);
			callFunction(&clearScreenTable);
		} //End of conversation var check

		//Add the action to the ActionCreature:
		actCreature->addActionObj(actionKey, action);

		instance->unlock();
	} catch (...) {
		System::out << "Failed to load action in mission script." << endl;
		instance->unlock();
	}
}*/

uint64 MissionManagerImplementation::getNextMissionID() {
	return zoneServer->getNextID();
}

