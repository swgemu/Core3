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
#include "../../managers/player/PlayerManager.h"

class Player;
class PlayerObject;


class FriendsListImplementation : public FriendsListServant {

	Vector<string> friendName;
	Vector<string> friendServer;
	
	Player* player;
	
public:
	FriendsListImplementation(Player* pl): FriendsListServant(){
		
		player = pl;
		
	}
	~FriendsListImplementation(){
	
	}
	
	inline void init(){
		
	}

	int getCount(){
			
		return friendName.size();
		
	}
	
	string& getFriendsName(const int i){
		
		return friendName.get(i);
		
	}
	
	string& getFriendsServer(const int i){
		
		return friendServer.get(i);
		
	}
	
	void addFriend(string& name, string& server) {

		PlayerObject* playerObject = player->getPlayerObject();

		friendName.add(name);
		friendServer.add(server);
		 
		toString();
		
		AddFriendInitiateMessage* init = new AddFriendInitiateMessage();
		player->sendMessage(init);

		AddFriendMessage* add = new AddFriendMessage(player->getObjectID(),
				name, server, true);
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

        FriendListMessage* list = new FriendListMessage(player);
        player->sendMessage(list);
		
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
		dplay9->updateFriendList();
		dplay9->close();
		player->sendMessage(dplay9);

		
	}
	
	void removeFriend(const string& name) {

		PlayerObject* playerObject = player->getPlayerObject();

		int index = 0;
		for(int i = 0; i < friendName.size(); ++i){
			
			if(friendName.get(i) == name){
				index = i;
				break;
			}
		}
		
		if(index == 0)
			return;
		
		string inServer = friendServer.get(index);
		
		friendName.remove(index);
		friendServer.remove(index);
		
		toString();
		
		AddFriendMessage* remove = new AddFriendMessage(player->getObjectID(),
				name, inServer, false);
		player->sendMessage(remove);
		
		stringstream friendString;
		friendString << name << " is no longer your friend.";
		unicode message = unicode(friendString.str());
		player->sendSystemMessage(message);
		
        FriendListMessage* list = new FriendListMessage(player);
        player->sendMessage(list);

		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
		dplay9->updateFriendList();
		dplay9->close();
		player->sendMessage(dplay9);


	}

	void toString() {
		
		cout << "Friend List for " << player->getFirstName() << endl;
		cout << "Number of friends = " << friendName.size() << endl;
		
		for(int i = 0; i < friendName.size(); ++i){
			
			cout << friendName.get(i) << " on " << friendServer.get(i) << endl;
			
		}

	}

};
#endif /*FRIENDSLISTIMPLEMENTATION_H_*/
