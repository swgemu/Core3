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

//MissionManagerImplementation* MissionManagerImplementation::instance = NULL;

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

	misoMap = NULL;
}

void MissionManagerImplementation::init() {
	// Scripting
	/*
	Lua::init();
	registerFunctions();
	registerGlobals();
	*/
	
	//instance = this;
	setupHardcodeMissions();
}

void MissionManagerImplementation::unloadManager() {
}

//Standard Functions:
MissionObject* MissionManagerImplementation::poolMission(string& dbKey, int termMask, const string& typeStr, uint32 descKey, uint32 titleKey, uint32 diffLv, float destX, float destY, uint32 destPlanetCrc,
		const string& creatorName, uint32 rewardAmount, float targetX, float targetY, uint32 targetPlanetCrc, uint32 depictedObjCrc, 
		const string& descriptionStf, const string& titleStf, uint32 typeCrc, TangibleObject* deliverItem, bool doLock) {
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
		
		miso->setCreatorName(unicode(creatorName));
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
		
		if(misoMap->get(dbKey) != NULL) {
			string err = "Mission Key Collision with " + dbKey;
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
	/*
	string dbKey = "testM27";
	int tmask = TMASK_GENERAL; //terminal mask (GENERAL)
	string typeStr = "mission_deliver"; 
	
	//uint32 descKey = htonl(atoi("m27d"));
	//uint32 titleKey = htonl(atoi("m27t"));
	//For custom missions:
	uint32 descKey = 0;
	uint32 titleKey = 0;
	
	uint32 diffLv = 1; 
	float destX = 1337.0f; 
	float destY = 1337.0f; 
	uint32 destPlanetCrc = Planet::getPlanetCRC("naboo");
	string creatorName = "Ramsey";
	uint32 rewardAmount = 50;
	float targetX = 1234.0f; 
	float targetY = 1234.0f; 
	uint32 targetPlanetCrc = Planet::getPlanetCRC("naboo");
	uint32 depictedObjCrc = 0x2D589F5B; //0x5B, 0x9F, 0x58, 0x2D, butterfly
	
	//string descriptionStf = "mission/mission_deliver_neutral_easy"; 
	//string titleStf = "mission/mission_deliver_neutral_easy"; 
	//For custom missions:
	string descriptionStf = "Deliver this secret box to MAN O' Action.";
	string titleStf = "The Box";
	
	uint32 typeCrc = 0xE5C27EC6; //0xC6, 0x7E, 0xC2, 0xE5, //crc("deliver");
	
	//Deliver Item:
	TangibleObject* dvli = new TangibleObject(getNextMissionID(), 0x9BA06548, unicode("Secret Box"), "object/tangible/jedi/shared_jedi_holocron_light.iff");
	
	poolMission(dbKey, tmask, typeStr, descKey, titleKey, diffLv, destX, destY, destPlanetCrc,
			creatorName, rewardAmount, targetX, targetY, targetPlanetCrc, depictedObjCrc, 
			descriptionStf, titleStf, typeCrc, dvli, true);
	
	//test 2nd mission:
	dbKey = "testM28";
	titleStf = "The Box 2";
	
	poolMission(dbKey, tmask, typeStr, descKey, titleKey, diffLv, destX, destY, destPlanetCrc,
			creatorName, rewardAmount, targetX, targetY, targetPlanetCrc, depictedObjCrc, 
			descriptionStf, titleStf, typeCrc, NULL, true);
	*/
}

//terminal
void MissionManagerImplementation::sendTerminalData(Player* player, int termBitmask, bool doLock) {
	try {
		lock(doLock);
		
		int sentBases = 0;
		
		for(int i = 0; i < misoMap->size(); i++) {
			MissionObject* miso = misoMap->get(i);
			if(miso == NULL)
				continue;
				
			//Do planet mission check here using the current player class:
			
			//Check if player is already on mission:
			if(player->isOnCurMisoKey(miso->getDBKey())) {
				//error("player is already on mission, continuing to next miso in list.");
				continue;
			}
				
			//Make sure the terminal and mission in the misoMap are in the same category:
				
			if ((termBitmask & TMASK_GENERAL) && (miso->getTerminalMask() & TMASK_GENERAL)) {
				if(!player->checkMisoBSB(TMASK_GENERAL)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_GENERAL;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_ENTERTAINER) && (miso->getTerminalMask() & TMASK_ENTERTAINER)) {
				if(!player->checkMisoBSB(TMASK_ENTERTAINER)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_ENTERTAINER;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_EXPLORER) && (miso->getTerminalMask() & TMASK_EXPLORER)) {
				if(!player->checkMisoBSB(TMASK_EXPLORER)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_EXPLORER;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_BOUNTY) && (miso->getTerminalMask() & TMASK_BOUNTY)) {
				if(!player->checkMisoBSB(TMASK_BOUNTY)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_BOUNTY;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_ARTISAN) && (miso->getTerminalMask() & TMASK_ARTISAN)) {
				if(!player->checkMisoBSB(TMASK_ARTISAN)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_ARTISAN;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_REBEL) && (miso->getTerminalMask() & TMASK_REBEL)) {
				if(!player->checkMisoBSB(TMASK_REBEL)) {
					sendMissionBase(player, miso);
					sentBases |= TMASK_REBEL;
				}
				sendMissionDelta(player, miso);
				continue;
			}

			if ((termBitmask & TMASK_IMPERIAL) && (miso->getTerminalMask() & TMASK_IMPERIAL)) {
				if(!player->checkMisoBSB(TMASK_IMPERIAL)) {
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

void MissionManagerImplementation::sendMission(Player* player, string& tKey, bool doLock) {
	try {
		lock(doLock);
		
		MissionObject* miso = misoMap->get(tKey);
		
		if(miso == NULL) {
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
		if(miso == NULL) {
			error("miso object is NULL, exiting function: doMissionAccept()");
			unlock(doLock);
			return;
		}
		
		//Check if player is already on mission:
		if(player->isOnCurMisoKey(miso->getDBKey())) {
			error("Player is already on mission!");
			return;
		}
		
		miso->doLinkToPlayer(player);
		
		player->addToCurMisoKeys(miso->getDBKey());
		player->sendSystemMessage("You have accepted the mission and it has been added to your datapad.");
		
		PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_accepted.snd");
		player->sendMessage(pmm);
		
		//Create Mission Waypoint here
		
		//Give deliver item to player:
		if(miso->getTypeStr() == "mission_deliver" && (miso->getDeliverItem() != NULL)) {
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

void MissionManagerImplementation::doMissionComplete(Player* player, string& tKey) {
	//system msg: "Mission Complete. You have been awarded: <rewards>"
	player->sendSystemMessage("Mission Complete.");
	
	PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
	player->sendMessage(pmm);
	
	removeMisoFromPlayer(player, tKey, true);
	
	player->addToFinMisoKeys(tKey);
	player->removeFromCurMisoKeys(tKey);
}

void MissionManagerImplementation::doMissionAbort(Player* player, uint64& oid, bool doLock) {
	try {
		lock(doLock);
		
		MissionObject* miso = misoMap->get(oid);
		if(miso == NULL) {
			error("miso object is NULL, exiting function: doMissionAbort()");
			unlock(doLock);
			return;
		}
		
		removeMisoFromPlayer(miso, player);
		player->sendSystemMessage("Mission Failed.");
		player->removeFromCurMisoKeys(miso->getDBKey());
		
		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAbort()"); 

		unlock(doLock);
	}
}

void MissionManagerImplementation::doMissionAbort(Player* player, string& tKey, bool doLock) {
	try {
		lock(doLock);
		
		MissionObject* miso = misoMap->get(tKey);
		if(miso == NULL) {
			error("miso object is NULL, exiting function: doMissionAbort()");
			unlock(doLock);
			return;
		}
		
		removeMisoFromPlayer(miso, player);
		player->sendSystemMessage("Mission Failed.");
		player->removeFromCurMisoKeys(tKey);
		
		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on doMissionAbort()"); 

		unlock(doLock);
	}
}
		
void MissionManagerImplementation::sendMissionBase(Player* player, string& tKey, bool doLock) {
	try {
		lock(doLock);
		
		MissionObject* miso = misoMap->get(tKey);
		
		if(miso != NULL) {
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
		
		if(miso != NULL) {
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

void MissionManagerImplementation::sendMissionDelta(Player* player, string& tKey, bool doLock) {
	try {
		lock(doLock);
		
		MissionObject* miso = misoMap->get(tKey);
		
		if(miso != NULL) {
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
		
		if(miso != NULL) {
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

void MissionManagerImplementation::removeMisoFromPlayer(Player* player, string& tKey, bool doLock) {
	MissionObject* miso = NULL;
	
	try {
		lock(doLock);
	
		miso = misoMap->get(tKey);
		
		if(miso != NULL) {
			miso->sendDestroyTo(player);
		} else {
			error("Invalid mission attempting to be removed from player. removeMisoFromPlayer (key)");
		}
	
		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on removeMisoFromPlayer() (db key)"); 

		unlock(doLock);
	}
	
	if(miso == NULL)
		return;
	
	if(miso->getTypeStr() == "mission_deliver" && (miso->getDeliverItem() != NULL)) {
		TangibleObject* tmpi = (TangibleObject*)player->getMissionItem(miso->getDBKey());
		if(tmpi == NULL) {
			return;
		}

		player->removeInventoryItem(tmpi->getObjectID());
		tmpi->sendDestroyTo(player);
		tmpi->finalize();
	}
}

void MissionManagerImplementation::removeMisoFromPlayer(Player* player, uint64& oid, bool doLock) {
	MissionObject* miso = NULL;
	
	try {
		lock(doLock);
	
		miso = misoMap->get(oid);
		
		if(miso != NULL) {
			miso->sendDestroyTo(player);
		} else {
			error("Invalid mission attempting to be removed from player. removeMisoFromPlayer (id)");
		}
	
		unlock(doLock);
	} catch (...) {
		error("unreported Exception caught on removeMisoFromPlayer() (objid)"); 

		unlock(doLock);
	}
	
	if(miso == NULL)
		return;
	
	if(miso->getTypeStr() == "mission_deliver" && (miso->getDeliverItem() != NULL)) {
		TangibleObject* tmpi = (TangibleObject*)player->getMissionItem(miso->getDBKey());
		if(tmpi == NULL) {
			return;
		}

		player->removeInventoryItem(tmpi->getObjectID());
		tmpi->sendDestroyTo(player);
		tmpi->finalize();
	}
}

void MissionManagerImplementation::removeMisoFromPlayer(MissionObject* miso, Player* player) {
	if(miso->getTypeStr() == "mission_deliver" && (miso->getDeliverItem() != NULL)) {
		TangibleObject* tmpi = (TangibleObject*)player->getMissionItem(miso->getDBKey());
		if(tmpi == NULL) {
			return;
		}

		player->removeInventoryItem(tmpi->getObjectID());
		tmpi->sendDestroyTo(player);
		tmpi->finalize();
	}
	
	miso->sendDestroyTo(player);
}

void MissionManagerImplementation::removeMissions() {
	for (int i = 0; i < misoMap->size(); ++i) {
		MissionObject* miso = misoMap->get(i);
		miso->finalize();
	}
	
	misoMap->removeAll();
}

uint32 MissionManagerImplementation::getMissionItemCrc(string& tKey, bool doLock) {
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
	//lua_register(getLuaState(), "RunMissionFile", runMissionFile);
	//lua_register(getLuaState(), "AddMissionToServer", addMission);
}

void MissionManagerImplementation::registerGlobals() {
}

void MissionManagerImplementation::loadMissionScripts() {
	//runFile("scripts/mission/main.lua");
}
/*
int MissionManagerImplementation::runMissionFile(lua_State* L) {
	string filename = getStringParameter(L);
	
	runFile("scripts/mission/objects" + filename, L);
	
	return 0;
}
*/

uint64 MissionManagerImplementation::getNextMissionID() {
	return zoneServer->getNextID();
}

