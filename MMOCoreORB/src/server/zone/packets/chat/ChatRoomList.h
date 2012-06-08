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

#ifndef CHATROOMLIST_H_
#define CHATROOMLIST_H_

#include "engine/engine.h"

#include "../../../chat/room/ChatRoom.h"
#include "../MessageCallback.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"

#include "server/chat/ChatManager.h"

namespace server {
namespace zone {
namespace packets {
namespace chat {

class ChatRoomList : public BaseMessage {
	int channelCounter;
	
public:
	ChatRoomList() : BaseMessage() {
		insertShort(0x02);
		insertInt(0x70DEB197);  // Opcode
		
		insertInt(0); //List Count
		
		channelCounter = 0;

		setCompression(true);
	}
	
	void addChannel(ChatRoom* channel) {
		channelCounter++;
		
		insertInt(channel->getRoomID());
		insertInt(1);
		insertByte(0);

		insertAscii(channel->getFullPath());
		
		insertAscii("SWG");
		insertAscii(channel->getGalaxyName());
		insertAscii(channel->getOwner());	
		
		//This struct is a ChatAvatarId
		insertAscii("SWG");
		insertAscii(channel->getGalaxyName());
		insertAscii(channel->getCreator());
		
		insertUnicode(channel->getTitle());
		
		addToUnknownListA(channel);
		addToUnknownListB();
	}
	
	void insertChannelListCount() {
		insertInt(10, channelCounter);
	}
	
	void addToUnknownListA(ChatRoom* room) {
		insertInt(0);
		
		/*int size = room->playerList.size(); 
		insertInt(size);
		
		for (int i = 0; i < size; i++) {
			insertAscii("SWG");
			insertAscii(room->getGalaxyName());
			insertAscii(room->playerList.get(i)->getFirstName());
		}*/
		
		/*insertInt(1); //List Count of Players in Room?
		insertAscii("SWG");
		insertAscii(serverName.toCharArray());
		insertAscii(name.toCharArray());*/
	}
	
	void addToUnknownListB() {
		insertInt(0); //List Count
		/*insertAscii("SWG");
		insertAscii(serverName.toCharArray());
		insertAscii(name);*/	
	}


};

class ChatRequestRoomListCallback : public MessageCallback {
public:
	ChatRequestRoomListCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {

	}

	void run() {
		ZoneServer* zoneServer = server->getZoneServer();
		ChatManager* chatManager = zoneServer->getChatManager();

		ManagedReference<SceneObject*> strongRef = client->getPlayer();

		if (strongRef == NULL)
			return;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(strongRef.get());

		if (player != NULL)
			chatManager->sendRoomList(player);
	}
};

}
}
}
}

using namespace server::zone::packets::chat;

#endif /*CHATROOMLIST_H_*/
