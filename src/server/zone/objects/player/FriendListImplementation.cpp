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

#include "FriendsListImplementation.h"

#include "Player.h"
#include "PlayerObject.h"

#include "../../packets/player/AddFriendInitiateMessage.h"
#include "../../packets/player/FriendStatusChangeMessage.h"
#include "../../packets/player/AddFriendMessage.h"
#include "../../packets/player/FriendListMessage.h"
#include "../../packets/player/PlayerObjectDeltaMessage9.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "../../objects/terrain/PlanetNames.h"

#include "../../managers/player/PlayerManager.h"

#include "../waypoint/WaypointObject.h"
#include "../../managers/object/ObjectManager.h"

FriendsListImplementation::FriendsListImplementation(Player* pl): FriendsListServant(){
	player = pl;
	friendsMagicNumber = 0;
}

void FriendsListImplementation::addFriend(String& name, String& server) {
	PlayerObject* playerObject = player->getPlayerObject();

	int magicnumber = friendsMagicNumber;
	uint32 offlineCharID;

	name = name.toLowerCase();

	for (int i = 0; i < friendName.size(); ++i) {
		if (friendName.get(i) == name){
			StringBuffer friendString;
			friendString << name << " is already your friend.";

			UnicodeString message = UnicodeString(friendString.toString());
			player->sendSystemMessage(message);
			return;
		}
	}


	ResultSet* friends = pullMyFriendsFromDB(name);
	if (friends == NULL)
		return;


	offlineCharID = friends->getInt(0);

	friendName.add(name);
	friendServer.add(server);

	friendsMagicNumber = magicnumber + (friendName.size() +1);

	AddFriendInitiateMessage* init = new AddFriendInitiateMessage();
	player->sendMessage(init);

	AddFriendMessage* add = new AddFriendMessage(player->getObjectID(),	name, server, true);
	player->sendMessage(add);

	Player* playerToAdd = player->getZone()->getZoneServer()->getPlayerManager()->getPlayer(name);

	if (playerToAdd != NULL) {
		if (playerToAdd->isOnline()) {
			FriendStatusChangeMessage* notifyStatus =
				new FriendStatusChangeMessage(name, server, true);

			player->sendMessage(notifyStatus);

			PlayerObject* playerToAddObject = playerToAdd->getPlayerObject();
			if (playerToAddObject != NULL)
				playerToAddObject->pokeReverseFriendList(player->getObjectID());
		}
	}

	populateReverseFriendListForOfflineToonInDB(player->getObjectID(), offlineCharID);

	StringBuffer friendString;
	friendString << name << " is now your friend.";
	UnicodeString message = UnicodeString(friendString.toString());
	player->sendSystemMessage(message);

	FriendsListMessage* list = new FriendsListMessage(player);
	player->sendMessage(list);

	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
	dplay9->updateFriendsList();
	dplay9->close();
	player->sendMessage(dplay9);

	delete friends;
}

ResultSet* FriendsListImplementation::pullMyFriendsFromDB(String name) {
	ResultSet* friends;

	try {
		StringBuffer query;
		String mysqlName = name;
		MySqlDatabase::escapeString(mysqlName);

		query << "SELECT * from `characters` where lower(`firstname`) = '" << mysqlName << "';";
		friends = ServerDatabase::instance()->executeQuery(query);

		if (!friends->next()) {
			StringBuffer friendString;
			friendString << name << " is not a valid friend name.";

			UnicodeString message = UnicodeString(friendString.toString());
			player->sendSystemMessage(message);

			delete friends;
			return NULL;

		}
	} catch (DatabaseException& e) {
		System::out << "exception at Friendlist::addFriend()\n" << e.getMessage();
		return NULL;
	} catch (...) {
		System::out << "unreported exception at Friendlist::addFriend()\n";
		return NULL;
	}

	return friends;
}

void FriendsListImplementation::populateReverseFriendListForOfflineToonInDB(uint64 poid, uint32 myPlayer) {
	try {
		StringBuffer query;
		query << "INSERT DELAYED INTO friendlist_reverse set charID = " << myPlayer << ", gotMePOID = " << poid << ";";

		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		System::out << "FriendsListImplementation::populateReverseFriendListForOfflineToonInDB(uint64 poid, uint32 myPlayer) DB exception! \n";

		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in FriendsListImplementation::populateReverseFriendListForOfflineToonInDB\n";
	}
}

void FriendsListImplementation::removeFriend(String& name) {
	int i = 0;
	int magicnumber = friendsMagicNumber;

	name = name.toLowerCase();

	PlayerObject* playerObject = player->getPlayerObject();

	for (int i = 0; i < friendName.size(); ++i) {
		if (friendName.get(i) == name) {
			String inServer = friendServer.get(i);

			friendName.remove(i);
			friendServer.remove(i);

			friendsMagicNumber = magicnumber + (friendName.size() +1);

			//toString();


			Player* playerToRemove = player->getZone()->getZoneServer()->getPlayerManager()->getPlayer(name);

			if (playerToRemove != NULL) {
				if (playerToRemove->isOnline()) {
					PlayerObject* playerToRemoveObject = playerToRemove->getPlayerObject();
					if (playerToRemoveObject != NULL) {
						playerToRemoveObject->removeFromReverseFriendList(player->getObjectID());
					}
				}
			}


			AddFriendMessage* remove = new AddFriendMessage(player->getObjectID(),name, inServer, false);
			player->sendMessage(remove);

			StringBuffer friendString;
			friendString << name << " is no longer your friend.";
			UnicodeString message = UnicodeString(friendString.toString());
			player->sendSystemMessage(message);

			FriendsListMessage* list = new FriendsListMessage(player);
			player->sendMessage(list);

			PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
			dplay9->updateFriendsList();
			dplay9->close();
			player->sendMessage(dplay9);

			break;
		}
	}
}

void FriendsListImplementation::findFriend(String& name, PlayerManager* playerManager) {
	name = name.toLowerCase();

	Player* targetPlayer;
	PlayerObject* targetObject;

	String myName = player->getFirstName();
	myName = myName.toLowerCase();

	int i = 0;

	try {
		targetPlayer = playerManager->getPlayer(name);
		if (targetPlayer == NULL)
			return;

		targetObject = targetPlayer->getPlayerObject();

	} catch (...) {
		player->sendSystemMessage("Usage: /findFriend <friend name>\n");
		return;
	}

	//Set wp->internalNote and check if we have a FindFriend-Wapoint for this buddy already
	StringBuffer friendString;
	friendString << "FINDFRIEND:" << name;

	WaypointObject* returnWP = player->searchWaypoint(player, friendString.toString(), 1);

	FriendsList* friendsList = targetObject->getFriendsList();

	for (int i = 0; i < friendsList->getCount(); ++i) {
		if (friendsList->getFriendsName(i) == myName) {
			float x = targetPlayer->getPositionX();
			float y = targetPlayer->getPositionY();;

			String targetPlanet = Planet::getPlanetName(targetPlayer->getZoneID());

			//If the friend is in a cell, we need world cords from the parent or even parent-parent object
			SceneObject* plPar = targetPlayer->getParent();

			if (plPar != NULL) {
				if (plPar->isCell()) {
					SceneObject* parpar = plPar->getParent();

					if (parpar != NULL) {
						x = parpar->getPositionX();
						y = parpar->getPositionY();
					}
				}
			}

			if (returnWP != NULL) {
				returnWP->setPlanetName(targetPlanet);
				returnWP->setPosition(x, 0.0f, y);
				returnWP->changeStatus(true);
				player->updateWaypoint(returnWP);

				StringBuffer friendString;
				friendString << "The friend waypoint has been updated to the location of " << name << ".";

				UnicodeString message = UnicodeString(friendString.toString());
				player->sendSystemMessage(message);

				break;

			} else {
				WaypointObject* wp = new WaypointObject(player, player->getNewItemID());

				StringBuffer friendString;
				friendString << "FINDFRIEND:" << name;

				wp->setInternalNote(friendString.toString());
				wp->setName(name);
				wp->setPlanetName(targetPlanet);
				wp->setPosition(x, 0.0f, y);
				wp->changeStatus(true);
				player->addWaypoint(wp);

				friendString.deleteAll();
				friendString << "A friend waypoint has been created for the location of " << name << ".";

				UnicodeString message = UnicodeString(friendString.toString());
				player->sendSystemMessage(message);

				break;
			}
		}
	}
}

void FriendsListImplementation::toString() {
	System::out << "Friend List for " << player->getFirstName() << endl;
	System::out << "Number of friends = " << friendName.size() << endl;

	for (int i = 0; i < friendName.size(); ++i) {
		System::out << friendName.get(i) << " on " << friendServer.get(i) << ". Current magicnumber is " << friendsMagicNumber << endl;
	}
}

void FriendsListImplementation::loadFriends() {
	int magicnumber;

	//Clean before loading! Some server functions (eg. reInserting a player) are using cached objects.
	// We dont want the friendlist entries get doubled !
	friendsMagicNumber = 0;
	friendName.removeAll();
	friendServer.removeAll();

	try {
		StringBuffer loadQuery;
		loadQuery << "SELECT friendlist.character_id,friendlist.friend_id,friendlist.friend_galaxy,	characters.firstname "
				  << "FROM friendlist Inner Join characters ON friendlist.friend_id = characters.character_id "
				  << "WHERE friendlist.character_id = " << player->getCharacterID() << ";";

		ResultSet* friends = ServerDatabase::instance()->executeQuery(loadQuery);

		while (friends->next()) {
			magicnumber = friendsMagicNumber;

			String server = friends->getString(2);
			String name = String(friends->getString(3)).toLowerCase();

			friendName.add(name);
			friendServer.add(friends->getString(2));

			int newMagicNumber = magicnumber + (friendName.size() +1);
			friendsMagicNumber = newMagicNumber;

			//toString();

			AddFriendInitiateMessage* init = new AddFriendInitiateMessage();
			player->sendMessage(init);

			AddFriendMessage* add = new AddFriendMessage(player->getObjectID(),	name, server, true);
			player->sendMessage(add);

			Player* playerToAdd = player->getZone()->getZoneServer()->getPlayerManager()->getPlayer(name);

			if (playerToAdd != NULL){
				if (playerToAdd->isOnline()){
					FriendStatusChangeMessage* notifyStatus =
						new FriendStatusChangeMessage(name, server, true);
					player->sendMessage(notifyStatus);
				}
			}

			FriendsListMessage* list = new FriendsListMessage(player);
			player->sendMessage(list);

			PlayerObject* playerObject = player->getPlayerObject();
			PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
			dplay9->updateFriendsList();
			dplay9->close();
			player->sendMessage(dplay9);
		}

		delete friends;
	} catch (DatabaseException& e) {
		System::out << "FriendlistImplementation void loadFriends -> Select DB Query exception! \n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in FriendsListImplementation::loadFriends()\n";
	}
}

void FriendsListImplementation::updateAllFriends(PlayerObject* playerObject) {
	int i = 0;

	if (playerObject == NULL)
		return;

	for (int i = 0; i < playerObject->getFriendsList()->getCount(); ++i) {
		String name = playerObject->getFriendsList()->getFriendsName(i);
		String server = playerObject->getFriendsList()->getFriendsServer(i);

		FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(name, server, false);
		player->sendMessage(notifyStatus);
	}

	StringBuffer friendString;
	friendString << "The following friendlist status messages are caused by the client reloading without a complete shutdown. "
				 << "These messages do not reflect the real activities of your buddies in this case.\n";

	UnicodeString message = UnicodeString(friendString.toString());
	player->sendSystemMessage(message);
}

void FriendsListImplementation::saveFriends() {
	int i = 0 ;

	String lcaseName;

	try {
		StringBuffer deleteQuery;
		deleteQuery << "DELETE FROM friendlist WHERE character_id = " << player->getCharacterID();

		ServerDatabase::instance()->executeStatement(deleteQuery);
	} catch (DatabaseException& e) {
		System::out << "FriendlistImplementation void saveFriends -> Delete from friendlist Query exception! \n";

		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in FriendsListImplementation::saveFriends()\n";
	}

	for (int i = 0; i < friendName.size(); ++i){
		try {
			String lcaseName = friendName.get(i).toLowerCase();

			StringBuffer query;
			query << "SELECT * FROM characters WHERE lower(firstname) = \"" + lcaseName + "\"";

			ResultSet* friends = ServerDatabase::instance()->executeQuery(query);

			if (friends->next()) {
				StringBuffer saveQuery;
				saveQuery << "INSERT INTO `friendlist` "
						  << "(`character_id`,`friend_id`,`friend_galaxy`)"
						  << " VALUES ('"
						  << player->getCharacterID() << "','" << friends->getUnsignedInt(0) << "','"
						  << friends->getUnsignedInt(2) << "');";

				ServerDatabase::instance()->executeStatement(saveQuery);
			}

			delete friends;
		} catch (DatabaseException& e) {
			System::out << "FriendlistImplementation void saveFriends -> Insert DB Query exception! \n";

			System::out << e.getMessage() << endl;
		} catch (...) {
			System::out << "unreported exception caught in FriendlistImplementation::saveFriends()\n";
		}
	}
}
