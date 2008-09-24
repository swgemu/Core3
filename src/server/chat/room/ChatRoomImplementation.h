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

#ifndef CHATROOMIMPLEMENTATION_H_
#define CHATROOMIMPLEMENTATION_H_

#include "engine/engine.h"

class ZoneServer;
class Player;

#include "ChatRoom.h"

class ChatRoomImplementation : public ChatRoomServant, public Mutex {
	ZoneServer* server;

	string name;
	string fullPath;

	string owner;
	string creator;

	unicode title;
	uint32 roomID;

	ManagedReference<ChatRoom> parent;

	//SortedVector<Player*> playerList;
	VectorMap<string, Player*> playerList;
	VectorMap<string, ChatRoom*> subRooms;

	bool isPublicRoom;

public:
	ChatRoomImplementation(ZoneServer* serv, const string& Name, uint32 channelId);
	ChatRoomImplementation(ZoneServer* serv, ChatRoom* Parent, const string& Name, uint32 channelId);

	virtual ~ChatRoomImplementation();

	void sendTo(Player* player);
	void sendDestroyTo(Player* player);

	void addSubRoom(ChatRoom* channel);

	void removeSubRoom(ChatRoom* channel);

	ChatRoom* getSubRoom(int i);
	ChatRoom* getSubRoom(const string& name);

	void addPlayer(Player* player, bool doLock = true);
	void removePlayer(Player* player, bool doLock = true);
	void removePlayer(const string& player);

	void broadcastMessage(BaseMessage* msg);
	void broadcastMessage(Vector<BaseMessage*>& messages);

	bool hasPlayer(Player* player);
	bool hasPlayer(const string& name);

	void removeAllPlayers();

	void setPrivate() {
		isPublicRoom = false;
	}

	void setPublic() {
		isPublicRoom = true;
	}

	inline bool isPublic() {
		return isPublicRoom == true;
	}

	inline bool isPrivate() {
		return isPublicRoom == false;
	}

	Player* getPlayer(int idx) {
		return playerList.get(idx);
	}

	int getPlayerSize() {
		return playerList.size();
	}

	void setName(const string& Name) {
		name = Name;
	}

	inline string& getName() {
		return name;
	}

	inline string& getFullPath() {
		return fullPath;
	}

	inline string& getOwner() {
		return owner;
	}

	inline string& getCreator() {
		return creator;
	}

	inline unicode& getTitle() {
		return title;
	}

	string& getServerName();

	inline void setOwner(const string& Owner) {
		owner = Owner;
	}

	inline void setCreator(const string& Creator) {
		creator = Creator;
	}

	inline void setTitle(const string& Title) {
		title = unicode(Title);
	}

	inline uint32 getRoomID() {
		return roomID;
	}

	int getSubRoomsSize() {
		return subRooms.size();
	}

	ChatRoom* getParent() {
		return parent;
	}

	int compareTo(ChatRoom* obj) {
		if (roomID < obj->getRoomID())
			return 1;
		else if (roomID > obj->getRoomID())
			return -1;
		else
			return 0;
	}

	friend class ChatRoomList;
	friend class ChatOnCreateRoom;

};

#endif /*CHATROOMIMPLEMENTATION_H_*/
