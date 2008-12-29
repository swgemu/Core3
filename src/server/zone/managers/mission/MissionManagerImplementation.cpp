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
#include "../../objects/creature/action/ActionCreature.h"
#include "../../objects/creature/action/Action.h"

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
MissionObject* MissionManagerImplementation::poolMission(String& dbKey, int termMask, const String& typeStr, uint32 descKey, uint32 titleKey, uint32 diffLv, float destX, float destY, uint32 destPlanetCrc,
		const String& creatorName, uint32 rewardAmount, float targetX, float targetY, uint32 targetPlanetCrc, uint32 depictedObjCrc,
		const String& descriptionStf, const String& titleStf, uint32 typeCrc, TangibleObject* deliverItem, bool doLock) {
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
		miso->setTypeCrc(typeCrc);

		miso->setDeliverItem(deliverItem);

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

void MissionManagerImplementation::setupHardcodeMissions() {
	String dbKey = "";
	dbKey = "testM27";
	int tmask = TMASK_GENERAL; //terminal mask (GENERAL)
	String typeStr = "mission_deliver";

	//uint32 descKey = htonl(atoi("m27d"));
	//uint32 titleKey = htonl(atoi("m27t"));
	//For custom missions:
	uint32 descKey = 0;
	uint32 titleKey = 0;

	uint32 diffLv = 1;
	float destX = -5049.0f;
	float destY = 4225.0f;
	uint32 destPlanetCrc = Planet::getPlanetCRC("naboo");
	String creatorName = "Ramsey";
	uint32 rewardAmount = 50;
	float targetX = -4844.0f;
	float targetY = 4155.0f;
	uint32 targetPlanetCrc = Planet::getPlanetCRC("naboo");
	uint32 depictedObjCrc = 0x9BA06548; //holocron/secret box crc

	//String descriptionStf = "mission/mission_deliver_neutral_easy";
	//String titleStf = "mission/mission_deliver_neutral_easy";
	//For custom missions:
	String descriptionStf = "Deliver this secret box to MAN O' Action. The last time I checked he was at -5049, 4225.";
	String titleStf = "The Box";

	uint32 typeCrc = 0xE5C27EC6; //0xC6, 0x7E, 0xC2, 0xE5, //crc("deliver");

	//Deliver Item:
	TangibleObject* dvli = new TangibleObject(getNextMissionID(), 0x9BA06548, UnicodeString("Secret Box"), "object/tangible/jedi/shared_jedi_holocron_light.iff");

	poolMission(dbKey, tmask, typeStr, descKey, titleKey, diffLv, destX, destY, destPlanetCrc,
			creatorName, rewardAmount, targetX, targetY, targetPlanetCrc, depictedObjCrc,
			descriptionStf, titleStf, typeCrc, dvli, true);

	//Setup NPC:
	CreatureManager* cm = zoneServer->getCreatureManager(5);

	String name = "MAN O' ACTION";
	String stf = "";
	ActionCreature* tac;
	tac = cm->spawnActionCreature(name, stf, 0x8C73B91, "testM27", -5049.0f, 4225.0f, -0.0339502f, 0.999424f);
	tac->setMisoMgr(this);

	int actmsk = 0;
	actmsk |= ActionImplementation::TYPE_CONVERSE;
	Action* act = new Action((SceneObject*)tac, actmsk, 0);
	String scrnId = "0";
	String leftBox = "Do you have...it?";
	String Options = "Yes, here.|The weather is quite nice!|No, sorry I forgot."; //separate by |
	String optLink = "1,none|2,none|ENDCNV,none"; //separate by | (nextScreenID,actionKey)
	act->addConvoScreen(scrnId, leftBox, 3, Options, optLink);

	//Converstaion window in response to Yes, Here:
	scrnId = "1";
	leftBox = "Cool you have it? Give it to me!";
	Options = "Here|No, bye.";
	optLink = "EXECACTION,finm27|ENDCNV,none";
	act->addConvoScreen(scrnId, leftBox, 1, Options, optLink);

	//Conversation window in response to weather:
	scrnId = "2";
	leftBox = "Yea the weather is pretty nice..";
	Options = "Bye.";
	optLink = "ENDCNV,none";
	act->addConvoScreen(scrnId, leftBox, 1, Options, optLink);

	String actionKey = "KEYA";
	tac->addAction(actionKey, act);
	tac->onConverse(actionKey); //link onConverse to action "KEYA"

	//Complete Mission Key:
	actmsk = 0;
	actmsk |= ActionImplementation::TYPE_TAKEITEM;
	actmsk |= ActionImplementation::TYPE_COMPMISSION;
	Action* act2 = new Action((SceneObject*)tac, actmsk, 0);

	actionKey = "finm27";
	tac->addAction(actionKey, act2);
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

void MissionManagerImplementation::sendMission(Player* player, String& tKey, bool doLock) {
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

		miso->doLinkToPlayer(player);

		player->addToCurMisoKeys(miso->getDBKey());
		player->sendSystemMessage("You have accepted the mission and it has been added to your datapad.");

		PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_accepted.snd");
		player->sendMessage(pmm);

		//Create a mission save in the db:
		hasMissionSave(player, miso->getDBKey(), true, false);

		//Set mission key in "currentMissionKeys"
		setMisoKeyCurrent(player, miso->getDBKey(), false, false);

		//Create Mission Waypoint here

		//Give deliver item to player:
		if (miso->getTypeStr() == "mission_deliver" && (miso->getDeliverItem() != NULL)) {
			TangibleObject* itemTemp = miso->getDeliverItem();
			TangibleObject* playerItem = new TangibleObject(player->getNewItemID(), itemTemp->getObjectCRC(), itemTemp->getName(), itemTemp->getTemplateName());

			playerItem->setMisoAsocKey(miso->getDBKey());
			player->addInventoryItem(playerItem);
			playerItem->sendTo(player);
		}

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAccept()");

		unlock(doLock);
	}
}

void MissionManagerImplementation::doMissionComplete(Player* player, String& tKey, bool doLock) {
	try {
		lock(doLock);

		removeMisoFromPlayer(player, tKey, false);

		//Remove any mission save from the DB:
		deleteMissionSave(player, tKey, false);

		//Remove mission key from "currentMissionKeys", add to "finishedMissionKeys"
		setMisoKeyCurrent(player, tKey, true, false);
		setMisoKeyFinished(player, tKey, false, false);

		//system msg: "Mission Complete. You have been awarded: <rewards>"
		player->sendSystemMessage("Mission Complete.");
		//PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
		//player->sendMessage(pmm);
		player->addToFinMisoKeys(tKey);
		player->removeFromCurMisoKeys(tKey);

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

		//Remove mission key from "currentMissionKeys", add to "finishedMissionKeys"
		setMisoKeyCurrent(player, misoKey, true, false);
		setMisoKeyFinished(player, misoKey, false, false);

		removeMisoFromPlayer(miso, player);
		player->sendSystemMessage("Mission Failed.");
		player->removeFromCurMisoKeys(miso->getDBKey());

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAbort()");

		unlock(doLock);
	}
}

void MissionManagerImplementation::doMissionAbort(Player* player, String& tKey, bool doLock) {
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

		//Remove mission key from "currentMissionKeys", add to "finishedMissionKeys"
		setMisoKeyCurrent(player, tKey, true, false);
		setMisoKeyFinished(player, tKey, false, false);

		removeMisoFromPlayer(miso, player);
		player->sendSystemMessage("Mission Failed.");
		player->removeFromCurMisoKeys(tKey);

		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAbort()");

		unlock(doLock);
	}
}

void MissionManagerImplementation::doMissionSave(Player* player, const String& mkey, const String& objectivevars, const String& killcountvars, bool doLock) {
	try {
		////printf("doMissionSave, 1\n");
		lock(doLock);

		////printf("doMissionSave, 2\n");
		//Create mission save if it doesnt exist.
		if(!hasMissionSave(player, mkey, true, false))
			return;

		////printf("doMissionSave, 3\n");
		//Update the mission save:

		//If no update vars are passed, abort save.
		if((objectivevars.length() == 0) && (killcountvars.length() == 0)) {
			return;
		}

		//Build save query
		StringBuffer query2;
		bool prevStr = false;

		query2 << "UPDATE mission_save set ";
		if(objectivevars.length() != 0) {
			query2 << "objective_vars = '" << objectivevars << "'";
			prevStr = true;
		}

		if(killcountvars.length() == 0) {
			query2 << "kill_count_vars = '" << killcountvars << "'";
			prevStr = true;
		}

		////printf("doMissionSave, 4\n");

		if(!prevStr) //If we havent added anything to the query, bail.
			return;

		////printf("doMissionSave, 5\n");

		query2 << "WHERE character_id = " << player->getCharacterID() << " and miso_key = '" << mkey << "';";
		ServerDatabase::instance()->executeStatement(query2);

		unlock(doLock);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::doMissionSave()");
	} catch (...) {
		error("unreported Exception caught on doMissionSave()");

		unlock(doLock);
	}
	////printf("doMissionSave, 6, end\n");
}

void MissionManagerImplementation::deleteMissionSave(Player* player, const String& mkey, bool doLock) {
	try {
		////printf("deleteMissionSave, 1\n");
		lock(doLock);

		////printf("deleteMissionSave, 2\n");

		//Check to see if player even has a mission save to delete. Abort if false.
		if(!hasMissionSave(player, mkey, false, false))
				return;

		////printf("deleteMissionSave, 3\n");

		StringBuffer query;
		query << "DELETE FROM mission_save WHERE character_id = " << player->getCharacterID() << " and ";
		query << "miso_key = '" << mkey << "';";
		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::doMissionSave()");
	} catch (...) {
		error("unreported Exception caught on doMissionSave()");

		unlock(doLock);
	}
	////printf("deleteMissionSave, 4, end\n");
}

bool MissionManagerImplementation::hasMissionSave(Player* player, const String& mkey, bool createIfNone, bool doLock) {
	bool ret = false;
	ResultSet* msRes;
	try {
		////printf("hasMissionSave, 1\n");
		lock(doLock);

		StringBuffer query;
		//Check if the database has an entry for the playerid & misokey:
		query << "SELECT * FROM mission_save WHERE character_id = " << player->getCharacterID() << " and miso_key = '" << mkey << "';";
		////printf("executing query: %s\n", query.str());
		msRes = ServerDatabase::instance()->executeQuery(query);

		////printf("hasMissionSave, 2\n");

		//If db doesnt have an entry AND createIfNone is true, we'll create one
		if ((msRes->size() <= 0) && createIfNone) {
			ret = true;

			StringBuffer queryIns;
			queryIns << "INSERT INTO mission_save "
				<< "(character_id,miso_key) "
				<< "VALUES (" << player->getCharacterID() << ",'" << mkey << "'"
				<< ");";

			////printf("executing insert query: %s\n", query.str());
			ServerDatabase::instance()->executeStatement(queryIns);
		} else if ((msRes->size() <= 0)) { //No db entry, create is false
			ret = false;
		} else { //If an entry is present, just set the return to true
			ret = true;
		}

		////printf("hasMissionSave, 3\n");

		unlock(doLock);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::hasMissionSave()");
	} catch (...) {
		error("unreported Exception caught on hasMissionSave()");

		unlock(doLock);
	}

	delete msRes;

	////printf("hasMissionSave, 4, end\n");

	return ret;
}

void MissionManagerImplementation::getMissionSaveVarLine(Player* player, const String& mkey, const String& dbVar, String& retStr, bool doLock) {
	StringBuffer query;
	String varline = "";
	ResultSet* res;
	try {
		//printf("getMissionSaveVarLine, 1\n");
		lock(doLock);

		query << "SELECT " << dbVar << " FROM mission_save WHERE character_id = " << player->getCharacterID() << " and miso_key = '" << mkey << "';";

		res = ServerDatabase::instance()->executeQuery(query);

		if (res->next() && (res->size() > 0)) {
			varline = res->getString(0);
		}

		//printf("getMissionSaveVarLine, 2\n");

		unlock(doLock);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::getMissionSaveVarLine()");
	} catch (...) {
		error("unreported Exception caught on getMissionSaveVarLine()");

		unlock(doLock);
	}

	delete res;

	//printf("getMissionSaveVarLine, 3, end. Return = %s\n", retStr.toCharArray());

	retStr = varline;
}

void MissionManagerImplementation::getMisoKeysStatus(Player* player, bool finKeys, String& retStr, bool doLock) {
	StringBuffer query;
	ResultSet* res;
	String misoKeys = "";

	try {
		//printf("getMisoKeysStatus, 1\n");
		lock(doLock);

		String dbCol = "";
		if(finKeys) {
			dbCol = "finishedMissionKeys";
		} else {
			dbCol = "currentMissionKeys";
		}

		query << "SELECT " << dbCol << " FROM characters WHERE character_id = " << player->getCharacterID() << " and " << dbCol << " is not null;";

		res = ServerDatabase::instance()->executeQuery(query);

		if (res->next() && (res->size() > 0)) {
			misoKeys = res->getString(0);
		}

		//printf("getMisoKeysStatus, 2\n");

		unlock(doLock);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::getMisoKeysStatus()");
	} catch (...) {
		error("unreported Exception caught on getMisoKeysStatus");

		unlock(doLock);
	}

	delete res;

	//printf("getMisoKeysStatus, 3, end. returning: %s\n", retStr.toCharArray());

	retStr = misoKeys;
}

void MissionManagerImplementation::setMisoKeyCurrent(Player* player, String misoKey, bool remove, bool doLock) {
	ResultSet* res;

	try {
		//printf("setMisoKeyCurrent, 1\n");
		lock(doLock);

		StringBuffer query;
		String keyList;

		////printf("character id = %i\n", player->getCharacterID());

		//Get either the current or finished miso
		query << "SELECT 'characters.currentMissionKeys' FROM characters WHERE character_id = " << player->getCharacterID() << ";";
		res = ServerDatabase::instance()->executeQuery(query);
		////printf("setMisoKeyCurrent, 1.7\n");

		if(res == NULL) {
			//printf("the result set is NULL!\n");
			delete res;
			return;
		}

		if(res->size() > 0) {
			//printf("res size above 0\n");
			keyList = res->getString(0);
		} else {
			//printf("res size at 0\n");
		}

		//printf("setMisoKeyCurrent, 2\n");

		//Check if the key already exists in the list:
		StringTokenizer klistTok(keyList);

		String tk = "";
		String newList = "";
		bool hadMatch = false;

		klistTok.setDelimeter(",");

		while (klistTok.hasMoreTokens()) {
			klistTok.getStringToken(tk);

			//If there isnt a collision and we arent trying to remove it, add to the new list
			if (misoKey != tk && !remove) {
				newList += tk + ",";
			} else {
				hadMatch = true;
			}
		}

		//printf("setMisoKeyCurrent, 3\n");

		//if there was a match, add the key. This makes sure there is only 1 key
		if (hadMatch && !remove) {
			newList += misoKey + ",";
		}

		//Commit the list into the DB:
		StringBuffer query2;
		query2 << "UPDATE characters set currentMissionKeys = '" << newList << "' WHERE character_id = " << player->getCharacterID() << ";";
		ServerDatabase::instance()->executeStatement(query2);

		//printf("setMisoKeyCurrent, 4\n");

		unlock(doLock);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::setMisoKeyCurrent()");
	} catch (...) {
		error("unreported Exception caught on setMisoKeyCurrent");

		unlock(doLock);
	}
	delete res;
	//printf("setMisoKeyCurrent, 5, end.\n");
}

void MissionManagerImplementation::setMisoKeyFinished(Player* player, String misoKey, bool remove, bool doLock) {
	StringBuffer query;
	ResultSet* res;

	try {
		//printf("setMisoKeyFinished, 1\n");
		lock(doLock);

		String keyList = "";

		//Get either the current or finished miso
		query << "SELECT finishedMissionKeys FROM characters WHERE character_id = " << player->getCharacterID() << ";";
		res = ServerDatabase::instance()->executeQuery(query);
		if (res->next()) {
			keyList = res->getString(0);
		}

		//printf("setMisoKeyFinished, 2\n");

		//Check if the key already exists in the list:
		StringTokenizer klistTok(keyList);

		String tk = "";
		String newList = "";

		bool hadMatch = false;

		klistTok.setDelimeter(",");

		while (klistTok.hasMoreTokens()) {
			klistTok.getStringToken(tk);

			//If there isnt a collision and we arent trying to remove it, add to the new list
			if (misoKey != tk && !remove) {
				newList += tk + ",";
			} else {
				hadMatch = true;
			}
		}

		//if there was a match, add the key. This makes sure there is only 1 key
		if (hadMatch && !remove) {
			newList += misoKey + ",";
		}

		//Commit the list into the DB:
		StringBuffer query2;
		query2 << "UPDATE characters set finishedMissionKeys = '" << newList << "' WHERE character_id = " << player->getCharacterID() << ";";
		ServerDatabase::instance()->executeStatement(query2);

		//printf("setMisoKeyFinished, 3\n");

		unlock(doLock);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		error("DB Exception in MissionManagerImplementation::setMisoKeyFinished()");
	} catch (...) {
		error("unreported Exception caught on setMisoKeyFinished");

		unlock(doLock);
	}
	delete res;

	//printf("setMisoKeyFinished, 4, end.\n");
}

/// END OF SAVE FUNCS

void MissionManagerImplementation::sendMissionBase(Player* player, String& tKey, bool doLock) {
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

void MissionManagerImplementation::sendMissionDelta(Player* player, String& tKey, bool doLock) {
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

void MissionManagerImplementation::removeMisoFromPlayer(Player* player, String& tKey, bool doLock) {
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

	if (miso == NULL)
		return;

	player->removeAllInventoryByMisoKey(miso->getDBKey());
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

uint32 MissionManagerImplementation::getMissionItemCrc(String& tKey, bool doLock) {
	uint32 crc = 0;

	try {
		lock(doLock);
		MissionObject* miso = misoMap->get(tKey);
		TangibleObject* ttano = miso->getDeliverItem();
		crc = ttano->getObjectCRC();
		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on removeMisoFromPlayer() (objid)");
		unlock(doLock);
	}
	return crc;
}

//Script Functions:

void MissionManagerImplementation::registerFunctions() {
	lua_register(getLuaState(), "RunMissionFile", runMissionFile);
	lua_register(getLuaState(), "AddMissionToServer", addMissionToServer);
	lua_register(getLuaState(), "AddActionCreatureToServer", addActionCreatureToServer);
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
	setGlobalInt("AMEET_KILLCOUNTLIMIT", 2);
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

	return 0;
}

int MissionManagerImplementation::addActionCreatureToServer(lua_State* L) {
	int actCount = lua_gettop(L);
	ActionCreature* actCreature;

	for(int i = actCount; i >= 1; i--) {
		//printf("i = %i\n", i);

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
		//printf("loading script object. objectname: %s. numBuf = %s\n", objectName.toCharArray(), numBuf);

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
			creature->setStfName(stfname);
			creature->setSpeciesName(speciesName);
		} else if (!stfname.isEmpty()) {
			creature->setCharacterName(stfname);
		}

		String faction = creatureConfig.getStringField("faction");
		creature->setFaction(faction.hashCode());

		try {
			String dummy = creatureConfig.getStringField("gender");
			dummy = creatureConfig.getStringField("boneType");
			dummy = creatureConfig.getStringField("hideType");
			dummy = creatureConfig.getStringField("meatType");
		} catch (...) {
			System::out << "The LUA script for \'" << objectName << "\' is at least missing one of these fields:\n";
			System::out << "faction, gender, boneType,hideType,meatType.\nMake sure they do exist in the lua script!\n\n";
			instance->unlock();
			return NULL;
		}

		//cm->setCreatureAttributes(creature, &creatureConfig);

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
			creature->setCreatureBitmask(creatureBitmask);

		creature->setSpawnPosition(x, z, y, cellID);

		creature->setMisoMgr(instance);

		cm->spawnActionCreature(creature, &creatureConfig);

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
	Action* action = new Action((SceneObject*)actCreature, 0, 0);

	if (!actionConfig.isValidTable())
		return;

	try {
		instance->lock();

		String actionKey = actionConfig.getStringField("actionKey");

		//printf("Adding action. Key: %s \n", actionKey.toCharArray());

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

		//printf("done loading optional triggers\n");

		/////////////////////
		// Prereq Vars
		/////////////////////

		//TODO: Ramsey, where are the following functions?
		//prereq:HASMISSION:
		/*String hasMisoKey = actionConfig.getStringField("meet_hasMission");
		action->setMeetHasMission(hasMisoKey);

		//prereq:killcountlimit
		String killCountLimitList = actionConfig.getStringField("meet_killLimitList");
		action->setMeetKillLimitList(killCountLimitList);*/

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
					//printf("compOptionText: %s\n", compOptionText.toCharArray());

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
		actCreature->addAction(actionKey, action);

		instance->unlock();
	} catch (...) {
		System::out << "Failed to load action in mission script." << endl;
		instance->unlock();
	}
}

uint64 MissionManagerImplementation::getNextMissionID() {
	return zoneServer->getNextID();
}

