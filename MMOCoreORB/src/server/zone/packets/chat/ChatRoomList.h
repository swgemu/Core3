/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATROOMLIST_H_
#define CHATROOMLIST_H_

#include "engine/engine.h"

#include "server/chat/room/ChatRoom.h"
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
