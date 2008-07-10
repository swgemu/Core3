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

#ifndef FRIENDSLISTIMPLEMENTATION_H_
#define FRIENDSLISTIMPLEMENTATION_H_

#include "FriendsList.h" 
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
#include "../../managers/player/PlayerMapImplementation.h"

#include "../waypoint/WaypointObject.h"
#include "../../managers/object/ObjectManager.h"

class Player;
class PlayerObject;

class FriendsListImplementation : public FriendsListServant {
	Vector<string> friendName;
	Vector<string> friendServer;
	
	int friendsMagicNumber;
	Player* player;
	PlayerMap* playerMap;
	
public:
	FriendsListImplementation(Player* pl): FriendsListServant(){		
		player = pl;		
		friendsMagicNumber = 0;
	}
	~FriendsListImplementation(){
	}
	
	
	
	inline void init(){
	}

	int getCount(){
			return friendName.size();
	}
	
	int getMagicNumber(){
		return friendsMagicNumber;
	}

	string& getFriendsName(const int i){
		return friendName.get(i);
	}
	
	string& getFriendsServer(const int i){
		return friendServer.get(i);
	}
	
	void friendsMagicNumberReset() {
		friendsMagicNumber = 0;	
	}
	
	
	void addFriend(string& name, string& server) {
		PlayerObject* playerObject = player->getPlayerObject();
		int magicnumber;
		String::toLower(name);
		
		for(int i = 0; i < friendName.size(); ++i){
			if(friendName.get(i) == name){
				stringstream friendString;
				friendString << name << " is already your friend.";
				unicode message = unicode(friendString.str());
				player->sendSystemMessage(message);
				return;
			}
		}		
		
		try {
			stringstream query;
			query << "SELECT * from `characters` where lower(`firstname`) = '" << name << "';";
			ResultSet* friends = ServerDatabase::instance()->executeQuery(query);
		
			if (!friends->next()) {
				stringstream friendString;
				friendString << name << " is not a valid friend name.";
				unicode message = unicode(friendString.str());
				player->sendSystemMessage(message);
				
				delete friends;
				return;
			}
		
		} catch (DatabaseException& e) {
			cout << "FriendlistImplementation void addFriend -> Select DB Query exception! \n";
			return;
		}

		magicnumber = friendsMagicNumber;	
		
		friendName.add(name);
		friendServer.add(server);		
		
		friendsMagicNumber = magicnumber + (friendName.size() +1);
		
		//toString();
		
		AddFriendInitiateMessage* init = new AddFriendInitiateMessage();
		player->sendMessage(init);

		AddFriendMessage* add = new AddFriendMessage(player->getObjectID(),	name, server, true);
		player->sendMessage(add);
	    
		Player* playerToAdd = player->getZone()->getZoneServer()->getPlayerManager()->getPlayer(name);
		
		if(playerToAdd != NULL){
			
			if(playerToAdd->isOnline()){
			
				FriendStatusChangeMessage* notifyStatus = 
						new FriendStatusChangeMessage(name, server, true);
				player->sendMessage(notifyStatus);
				
			} 
			
		}
	
		stringstream friendString;
		friendString << name << " is now your friend.";
		unicode message = unicode(friendString.str());
		player->sendSystemMessage(message);

        FriendsListMessage* list = new FriendsListMessage(player);
        player->sendMessage(list);
		
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
		dplay9->updateFriendsList();
		dplay9->close();
		player->sendMessage(dplay9);
	}
	
	void removeFriend(string& name) {		
		int i = 0;
		int magicnumber;
		String::toLower(name);	
		
		PlayerObject* playerObject = player->getPlayerObject();
		
		magicnumber = friendsMagicNumber;
		
		for(int i = 0; i < friendName.size(); ++i){
			if(friendName.get(i) == name){
				string inServer = friendServer.get(i);
				
				friendName.remove(i);
				friendServer.remove(i);

				friendsMagicNumber = magicnumber + (friendName.size() +1);
						
				//toString();
				
				AddFriendMessage* remove = new AddFriendMessage(player->getObjectID(),name, inServer, false);
				player->sendMessage(remove);
				
				stringstream friendString;
				friendString << name << " is no longer your friend.";
				unicode message = unicode(friendString.str());
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
	
	void findFriend(string& name, PlayerManager* playerManager) {
		String::toLower(name);
		Player* targetPlayer = playerManager->getPlayer(name);
		PlayerObject* targetObject = targetPlayer->getPlayerObject();

		if (targetPlayer == NULL)
			return;		
			
		string myName = player->getFirstName();
		int i =0;

		//Set wp->internalNote and check if we have a FindFriend-Wapoint for this buddy already
		stringstream friendString;
		friendString.str("");
		friendString << "FINDFRIEND:" << name;
		WaypointObject* returnWP = player->searchWaypoint(player,friendString.str());

		
		for(int i = 0; i < targetObject->getFriendsList()->getCount(); ++i){
	
			if(targetObject->getFriendsList()->getFriendsName(i) == myName){
				stringstream friendString;

				friendString << "A waypoint for " << name << " has been added.";
				unicode message = unicode(friendString.str());
				player->sendSystemMessage(message);
				
				float x = targetPlayer->getPositionX();
				float y  = targetPlayer->getPositionY();
				string targetPlanet = Planet::getPlanetName(targetPlayer->getZoneID());
				
				if (returnWP != NULL) {
					returnWP->setPlanetName(targetPlanet);
					returnWP->setPosition(x, 0.0f, y);
					returnWP->changeStatus(true);
					player->updateWaypoint(returnWP);
					break;
				} else {
					WaypointObject* wp = new WaypointObject(player, player->getNewItemID());
					friendString.str("");					
					friendString << "FINDFRIEND:" << name;
					
					wp->setInternalNote(friendString.str());
					wp->setName(name);				
					wp->setPlanetName(targetPlanet);
					wp->setPosition(x, 0.0f, y);
					wp->changeStatus(true);
					player->addWaypoint(wp);
					break;
				}
			}
		}
	}
	
	void toString() {		
		cout << "Friend List for " << player->getFirstName() << endl;
		cout << "Number of friends = " << friendName.size() << endl;
		
		for(int i = 0; i < friendName.size(); ++i){			
			cout << friendName.get(i) << " on " << friendServer.get(i) << ". Current magicnumber is " << friendsMagicNumber << endl;			
		}
	}
	
	void loadFriends() {
		int magicnumber;		
		
		//Clean before loading! Some server functions (eg. reInserting a player) are using cached objects.
		// We dont want the frindlist entries get doubled !
		friendsMagicNumber = 0;
		friendName.removeAll();
		friendServer.removeAll();		
		
		try {
			stringstream loadQuery;
			
			loadQuery.str("");
			loadQuery << "SELECT * from `friendlist` where `character_id` = '" << player->getCharacterID() << "';";
			ResultSet* friends = ServerDatabase::instance()->executeQuery(loadQuery);
			
			while (friends->next()) {
				magicnumber = friendsMagicNumber;
				
				string server = friends->getString(6);
				string name = friends->getString(4);
				String::toLower(name);
				
				friendName.add(name);
				friendServer.add(friends->getString(6));

				int newMagicNumber = magicnumber + (friendName.size() +1);
				friendsMagicNumber = newMagicNumber;
		
				//toString();
			
				AddFriendInitiateMessage* init = new AddFriendInitiateMessage();
				player->sendMessage(init);
				
				AddFriendMessage* add = new AddFriendMessage(player->getObjectID(),	name, server, true);
				player->sendMessage(add);
				
				Player* playerToAdd = player->getZone()->getZoneServer()->getPlayerManager()->getPlayer(name);
			
				if(playerToAdd != NULL){
					if(playerToAdd->isOnline()){
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
		} catch (DatabaseException& e) {
			cout << "FriendlistImplementation void loadFriends -> Select DB Query exception! \n";
		}
	}

	void updateAllFriends(PlayerObject* playerObject) {
		int i = 0;
		
		if (playerObject == NULL)
			return;

		for(int i = 0; i < playerObject->getFriendsList()->getCount(); ++i){

			string name = playerObject->getFriendsList()->getFriendsName(i);
			string server = playerObject->getFriendsList()->getFriendsServer(i);

			FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(name, server, false);
			player->sendMessage(notifyStatus);
		}

		stringstream friendString;
		friendString 	<< "The following friendlist status messages are caused by the client reloading without a complete shutdown. "
						<< "These messages do not reflect the real activities of your buddies in this case.\n";
		unicode message = unicode(friendString.str());
		player->sendSystemMessage(message);
	}
	
	
	void saveFriends() {
		int i = 0 ;
		string lcaseName;
		stringstream deleteQuery;
		
		try {		
			deleteQuery.str("");
			deleteQuery << "DELETE FROM friendlist WHERE character_id = " << player->getCharacterID();
			ServerDatabase::instance()->executeStatement(deleteQuery);			
		} catch (...) {
			cout << "FriendlistImplementation void saveFriends -> Delete from friendlist Query exception! \n";
		}
		
		
		for(int i = 0; i < friendName.size(); ++i){
			try {
				stringstream query;
				string lcaseName = friendName.get(i);
				String::toLower(lcaseName);
				
				query.str("");
				query << "SELECT * FROM characters WHERE lower(firstname) = \"" + lcaseName + "\""; 
				ResultSet* friends = ServerDatabase::instance()->executeQuery(query);
			
				if (friends->next()) {
					string lcaseFriend = friends->getString(3);
					String::toLower(lcaseFriend);
					
					stringstream saveQuery;
					saveQuery.str("");
					saveQuery << "INSERT INTO `friendlist` "
					<< "(`character_id`,`firstname`,`surname`,`friend_id`,`friend_firstname`,`friend_surname`,`friend_galaxy`)"
					<< " VALUES ('"
					<< player->getCharacterID() << "','" << player->getFirstName() << "','"
					<< player->getLastName() << "','" <<  friends->getUnsignedInt(0) << "','" 
					<< lcaseFriend << "','" << friends->getString(4) << "','" 
					<< friends->getUnsignedInt(2) << "');";

					ServerDatabase::instance()->executeStatement(saveQuery);	

					FriendStatusChangeMessage* notifyStatus = new FriendStatusChangeMessage(lcaseFriend, "Core3", false);
					player->sendMessage(notifyStatus);
						
				}			
			} catch (...) {
					cout << "FriendlistImplementation void saveFriends -> Insert DB Query exception! \n";
			}
		}
	}

};
#endif /*FRIENDSLISTIMPLEMENTATION_H_*/
