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

#include "../../Zone.h"
#include "../../ZoneClientSession.h"

#include "../../packets.h"
#include "../../objects.h"

#include "MissionObject.h"
#include "MissionObjectImplementation.h"

#include "../../managers/mission/MissionManager.h"
#include "../../managers/mission/MissionManagerImplementation.h"

MissionObjectImplementation::MissionObjectImplementation(uint64 oid, Player* owner) : SceneObjectImplementation(oid, MISSION) {
	StringBuffer name;
	name << "MissionObject :" << oid;
	setLoggingName(name.toString());

	setLogging(false); //set false after debug
	setGlobalLogging(true);

	ownerObject = owner;

	init();
}

MissionObjectImplementation::~MissionObjectImplementation() {
	for (int i = 0; i < objectiveList.size(); ++i) {
		MissionObjective* mo = objectiveList.get(i);
		mo->finalize();
	}

	objectiveList.removeAll();

	if(deliverContainer != NULL) {
		deliverContainer->finalize();
		deliverContainer = NULL;
	}

	if(awardContainer != NULL) {
		awardContainer->finalize();
		awardContainer = NULL;
	}
}

void MissionObjectImplementation::init() {
	deliverContainer = NULL;
	awardContainer = NULL;

	objectiveDefaults = "";
	instantComplete = true;
	completed = false;
	failed = false;
	statusStr = "";

	objectCRC = 0xDF064E7A; //0x7a,0x4e,0x06,0xdf,
	objectType = SceneObjectImplementation::MISSION;

	dbKey = "";
	terminalMask = 0;

	//MISO3:
	typeStr = ""; //3
	descKey = 0; //4
	titleKey = 0; //4
	difficultyLevel = 0; //5
	//6:
		destX = 0.0f;
		destY = 0.0f;
		destPlanetCrc = 0;
	//
	//creatorName = ""; //7 UNICODE
	rewardAmount = 0; //8
	//9:
		targetX = 0.0f;
		targetY = 0.0f;
		targetPlanetCrc = 0;
		targetName = "";
	//
	depictedObjCrc = 0; //10 (0A)
	descriptionStf = ""; //11 (0B)
	descriptionStr = "";
	titleStf = ""; //12 (0C)
	titleStr = "";
	refreshCount = 0x00; //13 (0D)
	typeCrc = 0; //14 (0E)
}

void MissionObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	create(client);

	BaseMessage* miso3 = new MissionObjectMessage3((MissionObject*) _this);
	client->sendMessage(miso3);

	BaseMessage* miso6 = new MissionObjectMessage6((MissionObject*) _this);
	client->sendMessage(miso6);

	if (doClose) {
		close(client);
	}
}

void MissionObjectImplementation::sendDeltaTo(Player* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	MissionObjectDeltaMessage3* dmiso3 = new MissionObjectDeltaMessage3((MissionObject*) _this);

	/*int posD = descriptionStf.indexOf("mission/");
	int posT = titleStf.indexOf("mission/");

	if (posD == -1) {
		dmiso3->updateDescriptionStf(false); //11 (0B)
	} else {
		dmiso3->updateDescriptionStf(true); //11 (0B)
		dmiso3->updateDescKey(); //4
	}

	dmiso3->updateDifficultyLv(); //5
	dmiso3->updateDestination(); //6
	dmiso3->updateCreator(); //7
	dmiso3->updateTypeCrc(); //14 (0E)
	dmiso3->updateReward(); //8
	dmiso3->updateTarget(); //9
	dmiso3->updateDepictedObject(); //10 (0A)

	if (posD == -1) {
		dmiso3->updateTitleStf(false); //12 (0C)
	} else {
		dmiso3->updateTitleStf(true); //12 (0C)
		dmiso3->updateTitleKey(); //4
	}*/

	dmiso3->updateRefreshCount(player->nextMisoRFC()); //13 (0D)

	dmiso3->close();

	client->sendMessage(dmiso3);
}

void MissionObjectImplementation::doLinkToPlayer(Player* player) {
	player->sendMessage(link(player->getDatapad()->getObjectID(), 0xFFFFFFFF));
}

//Use this function to remove the mission from the player.
//This does NOT remove the actual mission Object from the pool
void MissionObjectImplementation::sendDestroyTo(Player* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	destroy(client);
}

//Asset Setup:
/**
 * When owner accepts a mission, this function will send mission specific assets like
 * deliver items, waypoints etc
 */
void MissionObjectImplementation::assetSetup() {
	if(ownerObject == NULL)
		return;

	//Create & Send destination waypoint
	WaypointObject* waypoint = new WaypointObject(ownerObject, ownerObject->getNewItemID());
	waypoint->setPlanetName(Planet::getPlanetNameByCrc(destPlanetCrc));
	waypoint->setPosition(destX, 0, destY);
	waypoint->setName(titleStr);
	waypoint->changeStatus(true);

	ownerObject->addWaypoint(waypoint);
}

/**
 * Called when an owner is "parting" with a mission.
 * This function will remove deliver items on mission complete/abort and send rewards on complete
 */
void MissionObjectImplementation::assetPart(bool award) {
	if(ownerObject == NULL)
		return;

	if(award) {
		ownerObject->addCashCredits(rewardAmount);
		ownerObject->sendSystemMessage("You have been awarded " + String::valueOf(rewardAmount) + " for your efforts");
	}
}

//Container Methods:

void MissionObjectImplementation::addDeliverItem(TangibleObject* item) {
	deliverContainer->addObject(item);
}

TangibleObject* MissionObjectImplementation::getDeliverItem(uint64 oid) {
	if (deliverContainer != NULL)
		return (TangibleObject*) deliverContainer->getObject(oid);
	else
		return NULL;
}

void MissionObjectImplementation::removeDeliverItem(SceneObject* item) {
	deliverContainer->removeObject(item->getObjectID());
}

void MissionObjectImplementation::addAwardItem(TangibleObject* item) {
	awardContainer->addObject(item);
}

TangibleObject* MissionObjectImplementation::getAwardItem(uint64 oid) {
	if (awardContainer != NULL)
		return (TangibleObject*) awardContainer->getObject(oid);
	else
		return NULL;
}

void MissionObjectImplementation::removeAwardItem(SceneObject* item) {
	awardContainer->removeObject(item->getObjectID());
}

/////
//Objectives:
/////

/**
 * Add an objective to the map
 */
void MissionObjectImplementation::addObjective(MissionObjective* mo) {
	if(mo == NULL)
		return;

	objectiveList.add(mo);
}

/**
 * Deserialize the objectives from serialized string and creates the actual objective objects
 * If a player accepts a mission from the first time, defaults are loaded. If a player already has
 * the mission and is spawning, load from mission_saves
 * Default objectives are kept in a serialized string while in the mission manager pool. objective spawning
 * only takes place when a player owns the mission object
 */

void MissionObjectImplementation::spawnObjectives(const String& objectives) {
	if(objectives.isEmpty())
		return;

	//Deserialize objective chain:
	StringTokenizer serTok(objectives);
	String objt = "";
	serTok.setDelimeter("~");

	// Go through the serialized string and spawn each individual objective
	while(serTok.hasMoreTokens()) {
		serTok.getStringToken(objt);
		MissionObjective* mo = new MissionObjective(objt);
		objectiveList.add(mo);
	}
	checkComplete();
}

//Combines all objectives into a serialized string for saving
void MissionObjectImplementation::serializeObjectives(String& ret) {
	String temp;
	for(int i = 0; i < objectiveList.size(); i++) {
		MissionObjective* mo = objectiveList.get(i);
		temp += mo->serializeObjective();
		if((i+1) != objectiveList.size())
			ret.concat("~");
	}
	ret = temp;
}

/**
 * Used to update the objective set when a new event (kill, delivery attempt, death) is fired
 * Returns true if an objective was changed
 */
int MissionObjectImplementation::updateStatus(int type, uint32 objCrc, const String& str, String& updateStr, int increment) {
	int doUpdate = 0;

	for(int i = 0; i < objectiveList.size(); i++) {
		MissionObjective* mo = objectiveList.get(i);
		if(mo == NULL)
			continue;

		/*System::out << "MissionObject,updateStatus: stored targetcrc: " << mo->getTargetCrc() << ". objCrc: " << objCrc
				<< "stored str var: " << mo->getStrVar() << ". str: " << str << endl;*/

		// Make sure crc & str vars match, if applicable
		if((mo->getTargetCrc() == 0) || (mo->getTargetCrc() == objCrc)) {
			if((mo->getStrVar().compareTo("null") == 0) || (str.compareTo(mo->getStrVar()) == 0))
				doUpdate = 1;
		}

		if(doUpdate == 1) {
			switch(type) {
				case MissionObjectiveImplementation::HAS_KILLS:
					// Increment the # of confirmed kills
					mo->incrementVar(increment);

					// Update the kill specific status string:
					updateStr += "(" + String::valueOf(mo->getVar()) + "/" + String::valueOf(mo->getLimit()) + ") confirmed ";
					if(mo->getStrVar().compareTo("null") != 0)
						updateStr += mo->getStrVar() + " kills.";
				break;

				case MissionObjectiveImplementation::WAS_KIA:
					mo->incrementVar(increment);
				break;

				/**
				 * Do an inventory check for this. Modify getItemByMisoKey
				 case MissionObjectiveImplementation::HAS_ITEMS:
					 checkOwnerDelivery(); //checks owners inventory against the delivery container
					mo-updateVar(increment);
				break;*/

				default:
					doUpdate = 0;
				break;
			}
			// Run completion checks at the end of an objective update
			mo->checkObjectiveStatus();
			checkComplete();
			break;
		}
	}

	// Check if objective is instant complete (used when npc return is not desired for eval)
	// Note: instant complete also means instant fail.
	if((failed || completed) && instantComplete) {
		doUpdate = 2;
	}

	return doUpdate;
}

/**
 * Checks all objectives in the list. Updates completed or failed status
 */
void MissionObjectImplementation::checkComplete() {
	for(int i = 0; i < objectiveList.size(); i++) {
		MissionObjective* mo = objectiveList.get(i);
		if(mo == NULL)
			continue;

		if(mo->hasFailed()) {
			completed = false;
			failed = true;
			break;
		}

		if(mo->hasCompleted())
			completed = true;
		else
			completed = false;
	}
}

