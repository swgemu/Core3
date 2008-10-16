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

#include "../../packets.h"
#include "../../objects.h"
#include "../../ZoneClientSession.h"
#include "system/lang.h"

#include "../scene/SceneObject.h"

#include "Player.h"

#include "PlayerObject.h"

#include "PlayerObjectImplementation.h"

#include "FriendsList.h"
#include "FriendsListImplementation.h"

#include "IgnoreList.h"
#include "IgnoreListImplementation.h"


PlayerObjectImplementation::PlayerObjectImplementation(Player* pl) : PlayerObjectServant(pl->getObjectID() + 0x0C, PLAYEROBJECT) {
	player = pl;

	objectCRC = 0x619BAE21;

	// PLAY8 operands
	forcePower = player->getSkillMod("jedi_force_power_max");
	forcePowerMax = player->getSkillMod("jedi_force_power_max");
	experienceListCount = 0;
	waypointListCount = 0;
	waypointList.setNullValue(NULL);
	waypointList.setInsertPlan(SortedVector<WaypointObject*>::NO_DUPLICATE);

	forceRegen = player->getSkillMod("jedi_force_power_regen");

	// PLAY9 operands
	jediState = 0x08;

	drinkFilling = 0;
	drinkFillingMax = 100;

	foodFilling = 0;
	foodFillingMax = 100;

	characterBitmask = ANONYMOUS;

	friendsList = new FriendsList(player);
	ignoreList = new IgnoreList(player);
}

PlayerObjectImplementation::~PlayerObjectImplementation() {
	for (int i = 0; i < waypointList.size(); ++i) {
		WaypointObject* waypoint = waypointList.get(i);
		waypoint->finalize();
	}

	if (friendsList != NULL) {
		friendsList->finalize();
		friendsList = NULL;
	}

	if (ignoreList != NULL) {
		ignoreList->finalize();
		ignoreList = NULL;
	}
}

void PlayerObjectImplementation::sendToOwner() {
	ZoneClientSession* client = player->getClient();

	create(client);
	link(client, player);

	BaseMessage* play3 = new PlayerObjectMessage3((PlayerObject*) _this);
	client->sendMessage(play3);

	BaseMessage* play6 = new PlayerObjectMessage6((PlayerObject*) _this);
	client->sendMessage(play6);

	BaseMessage* play8 = new PlayerObjectMessage8(this);
	client->sendMessage(play8);

	BaseMessage* play9 = new PlayerObjectMessage9(this);
	client->sendMessage(play9);

	close(client);
}

void PlayerObjectImplementation::sendTo(Player* targetPlayer, bool doClose) {
	ZoneClientSession* client = targetPlayer->getClient();
	if (client == NULL)
		return;

	create(client);
	link(client, player);

	// add dplays here for others
	//Message* play8 = new PlayerObjectMessage8(this);
	//client->sendMessage(play8);

	BaseMessage* play3 = new PlayerObjectMessage3((PlayerObject*) _this);
	client->sendMessage(play3);

	BaseMessage* play6 = new PlayerObjectMessage6((PlayerObject*) _this);
	client->sendMessage(play6);

	if (targetPlayer == player) {
		BaseMessage* play8 = new PlayerObjectMessage8(this);
		client->sendMessage(play8);

		BaseMessage* play9 = new PlayerObjectMessage9(this);
		client->sendMessage(play9);
	}

	if (doClose)
		close(client);
}

void PlayerObjectImplementation::addExperience(const string& xpType, int xp, bool updateClient) {
	if (experienceList.containsKey(xpType)) {
		xp += experienceList.get(xpType);
		if (xp <= 0) {
			removeExperience(xpType, xp, updateClient);
			return;
		}
		experienceList.remove(xpType);
	}
	experienceList.put(xpType, xp);

	if (updateClient) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);

		dplay8->startExperienceUpdate(1);
		dplay8->addExperience(xpType, xp);
		dplay8->close();

		player->sendMessage(dplay8);
	}
}

void PlayerObjectImplementation::removeExperience(const string& xpType, int xp, bool updateClient) {
	if (experienceList.containsKey(xpType)) {
		experienceList.remove(xpType);
	} else
		return;

	if (updateClient) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);

		dplay8->startExperienceUpdate(1);
		dplay8->removeExperience(xpType);
		dplay8->close();

		player->sendMessage(dplay8);
	}
}

void PlayerObjectImplementation::loadExperience(const string& xpStr) {
	StringTokenizer xptokens(xpStr.c_str());
	xptokens.setDelimeter(":");
	
	while (xptokens.hasMoreTokens()) {
		string xptype, xpvalue;
		int xpamount;
		
		xptokens.getStringToken(xptype);
		xpamount = xptokens.getIntToken();

		addExperience(xptype, xpamount, false);
	}
	
}

string& PlayerObjectImplementation::saveExperience() {
	stringstream xpstr;
	experienceList.resetIterator();
	
	while (experienceList.hasNext()) {
		string key;
		int value;
		experienceList.getNextKeyAndValue(key, value);
		xpstr << key << ":" << value << ":";
	}

	experienceData = xpstr.str();
	
	return experienceData;
}

bool PlayerObjectImplementation::setCharacterBit(uint32 bit, bool updateClient) {
	if (!(characterBitmask & bit)) {
		characterBitmask |= bit;

		if (updateClient && player != NULL) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3((PlayerObject*) _this);
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			player->broadcastMessage(delta);
		}
		return true;
	} else
		return false;
}

bool PlayerObjectImplementation::clearCharacterBit(uint32 bit, bool updateClient) {
	if (characterBitmask & bit) {
		characterBitmask &= ~bit;

		if (updateClient && player != NULL) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3((PlayerObject*) _this);
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			player->broadcastMessage(delta);
		}

		return true;
	} else
		return false;
}

void PlayerObjectImplementation::setAdminLevel(uint32 level, bool updateClient) {
	adminLevel = level;

	if (updateClient) {
		PlayerObjectDeltaMessage6* dplay6 = new PlayerObjectDeltaMessage6((PlayerObject*) _this);
		dplay6->setAdminLevel(level);
		dplay6->close();
		player->broadcastMessage(dplay6);
	}
}

void PlayerObjectImplementation::setCurrentTitle(string& nTitle, bool updateClient) {
  	title = nTitle;

	if (updateClient) {
		PlayerObjectDeltaMessage3* dplay3 = new PlayerObjectDeltaMessage3((PlayerObject*) _this);
		dplay3->setCurrentTitle(nTitle);
		dplay3->close();
		player->broadcastMessage(dplay3); //update the zone.
	}
}

void PlayerObjectImplementation::setForcePowerBar(uint32 fp) {
	if (fp == forcePower)
		return;
	forcePower = fp;


	PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
	dplay8->updateForcePower();
	dplay8->close();

	// TODO: broadcastMessage ?
	player->sendMessage(dplay8);
}


void PlayerObjectImplementation::updateMaxForcePowerBar(bool updateClient) {
	if(updateClient && player != NULL) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->updateForcePowerMax();
		dplay8->close();

		player->sendMessage(dplay8);
	}

	if(getForcePower() > getForcePowerMax())
	{
		if(updateClient)
			setForcePowerBar(getForcePowerMax());
		else
			setForcePower(getForcePowerMax());
	}
}


void PlayerObjectImplementation::addWaypoint(WaypointObject* wp, bool updateClient) {
	wlock();

	if (waypointList.put(wp->getObjectID(), wp) != -1) {
		if (updateClient && player != NULL) {
			PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);

			dplay8->startWaypointUpdate();
			dplay8->addWaypoint(0, wp);
			dplay8->close();
			player->sendMessage(dplay8);
		}
	}
	unlock();
}

bool PlayerObjectImplementation::removeWaypoint(WaypointObject* wp, bool updateClient) {
	wlock();

	if (waypointList.drop(wp->getObjectID())) {

		if (updateClient && player != NULL) {
			PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);

			dplay8->startWaypointUpdate();
			dplay8->addWaypoint(1, wp);
			dplay8->close();
			player->sendMessage(dplay8);
		}
		unlock();
		return true;
	}
	unlock();
	return false;
}

WaypointObject* PlayerObjectImplementation::getWaypoint(uint64 id) {
	WaypointObject* waypoint = NULL;

	wlock();

	waypoint = waypointList.get(id);

	unlock();

	return waypoint;
}

int PlayerObjectImplementation::getWaypointListSize() {
	int size = 0;
	wlock();

	size = waypointList.size();

	unlock();

	return size;
}

void PlayerObjectImplementation::updateWaypoint(WaypointObject* wp) {
	wlock();

	if (waypointList.contains(wp->getObjectID())) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);

		dplay8->startWaypointUpdate();
		dplay8->addWaypoint(0, wp);
		dplay8->close();

		player->sendMessage(dplay8);
	}

	unlock();
}

void PlayerObjectImplementation::saveWaypoints(Player* player) {
	wlock();
	stringstream query;

	try {
		query.str( "" );
		query << "DELETE FROM waypoints WHERE owner_id = '" << player->getCharacterID() <<"';";
		ServerDatabase::instance()->executeStatement(query);

		string name;

		for (int i = 0; i < waypointList.size() ; ++i) {
			WaypointObject* wpl = waypointList.get(i);

			name = wpl->getName();
			MySqlDatabase::escapeString(name);

			query.str( "" );
			query << "INSERT DELAYED INTO waypoints (`waypoint_id`,`owner_id`,`waypoint_name`,`x`,`y`,`planet_name`,`internal_note`,`active`)"
			<< " VALUES ('"
			<< wpl->getObjectID() << "','"
			<< player->getCharacterID() << "','"
			<< name << "','"
			<< wpl->getPositionX() << "','"
			<< wpl->getPositionY() << "','"
			<< wpl->getPlanetName() << "','"
			<< wpl->getInternalNote() << "',"
			<< wpl->getStatus() << ");" ;

			ServerDatabase::instance()->executeStatement(query);
		}
	} catch (DatabaseException& e) {
		cout << "exception in PlayerObject::saveWaypoints()\n" << e.getMessage();
	} catch (...) {
		cout << "exception in PlayerObject::saveWaypoints\n";
	}

	unlock();
}

WaypointObject* PlayerObjectImplementation::searchWaypoint(Player* player, const string& name, int mode) {
	wlock();

	WaypointObject* waypoint = NULL;
	WaypointObject* returnWP = NULL;
	int i = 0;
	string sName;

	if (mode == 1 ) {
		//Lookup InternalNote field
		for (int i = 0; i < waypointList.size(); ++i) {
			waypoint = waypointList.get(i);

			if (waypoint->getInternalNote() == name) {
				returnWP = waypoint;
				break;
			}
		}
	} else if (mode == 2 ) {
		//Lookup WaypointName field
		sName = name.c_str();
		String::toLower(sName);

		for (int i = 0; i < waypointList.size(); ++i) {
			waypoint = waypointList.get(i);
			string wpName = waypoint->getName();
			String::toLower(wpName);

			if (wpName == sName) {
				returnWP = waypoint;
				break;
			}
		}
	}

	unlock();
	return returnWP;
}
