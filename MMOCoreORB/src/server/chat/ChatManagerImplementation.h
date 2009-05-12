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

#ifndef CHATMANAGERIMPLEMENTATION_H_
#define CHATMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

class UserManager;
class ItemManager;
class ProfessionManager;
class CreatureManager;

class ChatRoom;
class ChatRoomMap;

#include "../zone/managers/player/PlayerMap.h"

#include "../zone/packets.h"

#include "ChatManager.h"
#include "GameCommandHandler.h"

#include "../zone/objects/creature/CreatureObject.h"

class ZoneServer;

class ChatManagerImplementation : public ChatManagerServant, public Mutex {
	ZoneServer* server;

	UserManager* userManager;

	PlayerManager* playerManager;
	GuildManager* guildManager;

	GameCommandHandler * gameCommandHandler;

	ResourceManager* resourceManager;

	PlayerMap* playerMap;

	VectorMap<String, ChatRoom*> gameRooms;

	ChatRoom* groupRoom;
	ChatRoom* guildRoom;
	ChatRoomMap* roomMap;

	uint32 roomID;

	bool mute;

private:
	void populateRoomListMessage(ChatRoom* channel, ChatRoomList* msg);
	void printRoomTree(ChatRoom* channel, String name);

public:
	ChatManagerImplementation(ZoneServer* serv, int initsize);

	~ChatManagerImplementation();

	void addPlayer(Player* player);
	Player* getPlayer(String& name);
	Player* removePlayer(String& name);

	void sendMail(const String& sendername, UnicodeString& header, UnicodeString& body, const String& name);
	void sendMailBody(Player* receiver, uint32 mailid);
	void listMail(Player* ply);
	void deleteMail(uint32 mailid);

	void handleTellMessage(Player* player, Message* pack);
	void handleMessage(Player* player, Message* pack);
	static void handleEmote(Player* player, Message* pack);
	static void handleMood(Player* player, Message* pack);

	void handleGameCommand(Player* player, const String& command);
	static void sendSystemMessage(Player* player, UnicodeString& message);
	static void sendSystemMessage(Player* player, const String& file, const String& str, StfParameter * param);

	static void broadcastMessage(CreatureObject* player, const UnicodeString& message, uint64 target = 0, uint32 moodid = 0, uint32 mood2 = 0);
	static void broadcastMessage(CreatureObject* player, const String& file, const String& str, StfParameter * param, uint64 target = 0, uint32 moodid = 0, uint32 mood2 = 0);

	void broadcastFactionMessage(uint32 factionmask, const String& message);

	void broadcastMessage(const String& message);
	void broadcastMessageRange(Player* player, const String& message, float range);

	// ChatRooms
	void initiateRooms();
	void initGuildChannel(Player* creator, uint32 gid);

	void destroyRooms();

	void handleChatRoomMessage(Player* player, Message* pack);
	void handleGroupChat(Player* player, Message* pack);
	void handleGuildChat(Player* player, Message* pack);

	void handleCreateRoom(Player* player, Message* pack);
	void handleChatEnterRoomById(Player* player, Message* pack);
	void handleChatDestroyRoom(Player* player, Message* pack);
	void handleChatRemoveAvatarFromRoom(Player* player, Message* pack);

	ChatRoom* getChatRoom(uint32 id);

	void addRoom(ChatRoom* channel);
	void removeRoom(ChatRoom* channel);

	void sendRoomList(Player* player);

	void sendGuildChat(Player* player);

	ChatRoom* createGroupRoom(uint32 groupID, Player* creator);

	ChatRoom* createRoomByFullPath(const String& path);

	void destroyRoom(ChatRoom* room);

	void printRoomTree(ChatRoom* channel) {
		String name;
		printRoomTree(channel, name);
	}

	ChatRoom* getChatRoomByFullPath(const String& path);

	ChatRoom* getGameRoom(const String& game);
	ChatRoom* getChatRoomByGamePath(ChatRoom* game, const String& path);

	inline uint32 getNextRoomID() {
		return ++roomID;
	}

	inline int getPlayerCount() {
		return playerMap->size();
	}

	inline bool isMute() {
		return mute;
	}

	inline void setMute(bool isMuted) {
		mute = isMuted;
	}

};

#endif /*CHATMANAGERIMPLEMENTATION_H_*/

