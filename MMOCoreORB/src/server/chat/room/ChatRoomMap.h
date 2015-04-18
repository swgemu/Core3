/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATROOMMAP_H_
#define CHATROOMMAP_H_

#include "engine/engine.h"

#include "server/chat/room/ChatRoom.h"

namespace server {
namespace chat {
namespace room {

class ChatRoomMap : public Object {
	HashTable<uint32, ManagedReference<ChatRoom*> > rooms;

public:
	ChatRoomMap(int initsize) : rooms(initsize) {
	}

	void put(uint32 key, ChatRoom* room) {
		rooms.put(key, room);
	}

	ChatRoom* get(uint32 key) {
		return rooms.get(key);
	}

	void remove(uint32 key) {
		rooms.remove(key);
	}

	void removeAll() {
		rooms.removeAll();
	}

	HashTableIterator<uint32, ManagedReference<ChatRoom*> > iterator() {
		return rooms.iterator();
	}
};


}
}
}

using namespace server::chat::room;

#endif /*CHATROOMMAP_H_*/
