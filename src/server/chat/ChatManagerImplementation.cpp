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
#include <iostream>
#include <fstream>

#include "../zone/Zone.h"
#include "../zone/ZoneClientSession.h"
#include "../zone/ZoneServer.h"

#include "../zone/packets.h"
#include "../zone/objects.h"

#include "../zone/managers/creature/CreatureManager.h"
#include "../zone/managers/player/ProfessionManager.h"
#include "../zone/managers/resource/ResourceManager.h"

#include "../zone/managers/player/PlayerManager.h"
#include "../zone/managers/user/UserManager.h"

#include "../zone/managers/item/ItemManager.h"

#include "../zone/managers/guild/GuildManager.h"

#include "ChatManager.h"
#include "ChatManagerImplementation.h"

#include "room/ChatRoomImplementation.h"

#include "room/ChatRoom.h"
#include "room/ChatRoomMap.h"

#include "../zone/managers/player/PlayerMapImplementation.h"

#include "../zone/objects/player/sui/listbox/SuiListBoxImplementation.h"
#include "../zone/objects/player/sui/colorpicker/SuiColorPickerImplementation.h"

#include "../zone/objects/tangible/CustomizationVariables.h"

#include "../zone/managers/planet/PlanetManager.h"

ChatManagerImplementation::ChatManagerImplementation(ZoneServer* serv, int initsize) : ChatManagerServant(), Mutex("ChatManager") {
	server = serv;

	userManager = server->getUserManager();

	playerManager = serv->getPlayerManager();
	guildManager = playerManager->getGuildManager();

	resourceManager = server->getResourceManager();

	playerMap = new PlayerMap(initsize);
	playerMap->deploy("ChatPlayerMap");

	roomMap = new ChatRoomMap(10000);

	mute = false;

	roomID = 0;

	gameCommandHandler = new GameCommandHandler();

	initiateRooms();
}

ChatManagerImplementation::~ChatManagerImplementation() {
	destroyRooms();

	playerMap->finalize();
	playerMap = NULL;

	delete roomMap;
	roomMap = NULL;

	delete gameCommandHandler;
	gameCommandHandler = NULL;
}

void ChatManagerImplementation::initiateRooms() {
	gameRooms.setNullValue(NULL);

	ChatRoom* mainRoom = new ChatRoom(server, "SWG", getNextRoomID());
	mainRoom->deploy();
	mainRoom->setPrivate();
	addRoom(mainRoom);
	gameRooms.put("SWG", mainRoom);

	ChatRoom* core3Room = new ChatRoom(server, mainRoom, server->getServerName(), getNextRoomID());
	core3Room->deploy();
	core3Room->setPrivate();
	mainRoom->addSubRoom(core3Room);
	addRoom(core3Room);

	groupRoom = new ChatRoom(server, core3Room, "group", getNextRoomID());
	groupRoom->deploy();
	groupRoom->setPrivate();
	core3Room->addSubRoom(groupRoom);
	addRoom(groupRoom);

	guildRoom = new ChatRoom(server, core3Room, "guild", getNextRoomID());
	guildRoom->deploy();
	guildRoom->setPrivate();
	core3Room->addSubRoom(guildRoom);
	addRoom(guildRoom);

	ChatRoom* generalRoom = new ChatRoom(server, core3Room, "general", getNextRoomID());
	generalRoom->deploy();
	core3Room->addSubRoom(generalRoom);
	addRoom(generalRoom);

	// Planet Chat

	// Naboo
	ChatRoom* nabooRoom = new ChatRoom(server, core3Room, "naboo", getNextRoomID());
	nabooRoom->deploy();
	core3Room->addSubRoom(nabooRoom);
	addRoom(nabooRoom);

	ChatRoom* nabooPlanetary = new ChatRoom(server, nabooRoom, "chat", getNextRoomID());
	nabooPlanetary->deploy();
	nabooRoom->addSubRoom(nabooPlanetary);
	addRoom(nabooPlanetary);
}

void ChatManagerImplementation::destroyRooms() {
	lock();

	roomMap->resetIterator();

	while (roomMap->hasNext()) {
		ChatRoom* room = roomMap->next();
		room->finalize();
	}

	roomMap->removeAll();

	gameRooms.removeAll();

	unlock();
}

void ChatManagerImplementation::handleTellMessage(Player* sender, Message* pack) {
	if (sender->isChatMuted())
		return;

	String game, galaxy, name;
	UnicodeString message;


	uint32 seq = ChatInstantMessageToCharacter::parse(pack, game, galaxy, name, message);

	Player* receiver = getPlayer(name);

	if (receiver == NULL || !receiver->isOnline() || receiver->isLoggingOut()) {
		BaseMessage* amsg = new ChatOnSendInstantMessage(seq, true);
		sender->sendMessage(amsg);

		return;
	}

	BaseMessage* msg = new ChatInstantMessageToClient(game, galaxy, sender->getFirstName(), message);
	receiver->sendMessage(msg);

	BaseMessage* amsg = new ChatOnSendInstantMessage(seq, false);
	sender->sendMessage(amsg);
}

void ChatManagerImplementation::sendSystemMessage(Player* player, UnicodeString& message) {
	ChatSystemMessage* smsg = new ChatSystemMessage(message);
	player->sendMessage(smsg);
}

void ChatManagerImplementation::sendSystemMessage(Player* player, const String& file, const String& str, StfParameter * param) {
	ChatSystemMessage* smsg = new ChatSystemMessage(file, str, param);
	player->sendMessage(smsg);
}

void ChatManagerImplementation::broadcastMessage(CreatureObject* player, const String& file, const String& str, StfParameter * param, uint64 target, uint32 moodid, uint32 mood2) {
	if ( !player->isPlayer() || !((Player *)player)->isChatMuted() ) {
		Zone* zone = player->getZone();

		/*if (message.toCharArray() == "LAG") {
			ZoneClientSession* client = player->getClient();

			client->reportStats(true);

			Logger::slog("Client (" + client->getAddress() + ") is experiencing lag", true);
			return;
		} else if (message.toCharArray() == "QUEUE") {
			ZoneClientSession* client = player->getClient();

			client->reportStats(true);

			Logger::slog("Client (" + client->getAddress() + ") is experiencing queue lag", true);
			return;
		}*/

		try {
			zone->lock();

			for (int i = 0; i < player->inRangeObjectCount(); ++i) {
				SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_this);

				if (object->isPlayer()) {
					Player* creature = (Player*) object;

					if (player->isInRange(creature, 128)) {
						SpatialChat* cmsg = new SpatialChat(player->getObjectID(), creature->getObjectID(), file, str, param, target, moodid, mood2);
						creature->sendMessage(cmsg);
					}
				}
			}
			delete param;
			zone->unlock();
		} catch (...) {

			zone->unlock();

			System::out << "exception ChatManagerImplementation::broadcastMessage(Player* player, UnicodeString& message,  uint64 target, uint32 moodid, uint32 mood2)\n";
		}
	}
}

void ChatManagerImplementation::broadcastMessage(CreatureObject* player, UnicodeString& message,  uint64 target, uint32 moodid, uint32 mood2) {
	if ( !player->isPlayer() || !((Player *)player)->isChatMuted() ) {
		Zone* zone = player->getZone();

		/*if (message.toCharArray() == "LAG") {
			ZoneClientSession* client = player->getClient();

			client->reportStats(true);

			Logger::slog("Client (" + client->getAddress() + ") is experiencing lag", true);
			return;
		} else if (message.toCharArray() == "QUEUE") {
			ZoneClientSession* client = player->getClient();

			client->reportStats(true);

			Logger::slog("Client (" + client->getAddress() + ") is experiencing queue lag", true);
			return;
		}*/

		try {
			zone->lock();

			for (int i = 0; i < player->inRangeObjectCount(); ++i) {
				SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_this);

				if (object->isPlayer()) {
					Player* creature = (Player*) object;

					if (player->isInRange(creature, 128)) {
						SpatialChat* cmsg = new SpatialChat(player->getObjectID(), creature->getObjectID(), message, target, moodid, mood2);
						creature->sendMessage(cmsg);
					}
				}
			}

			zone->unlock();
		} catch (...) {

			zone->unlock();

			System::out << "exception ChatManagerImplementation::broadcastMessage(Player* player, UnicodeString& message,  uint64 target, uint32 moodid, uint32 mood2)\n";
		}
	}
}

void ChatManagerImplementation::broadcastMessage(const String& message) {
	lock();

	playerMap->resetIterator(false);

	while (playerMap->hasNext(false)) {
		Player* player = playerMap->getNextValue(false);

		player->sendSystemMessage(message);
	}

	unlock();
}

void ChatManagerImplementation::broadcastMessageRange(Player* player, const String& message, float range) {
	try {
		lock();

		//TODO make it polling the spatial indexer instead of iterating the whole hash table
		playerMap->resetIterator(false);

		while (playerMap->hasNext(false)) {
			Player* trgplayer = playerMap->getNextValue(false);

			if (player->isInRange((SceneObject*)trgplayer, range)) {
				trgplayer->sendSystemMessage(message);
			}
		}

		unlock();
	} catch (...) {

		unlock();

		System::out << "exception ChatManagerImplementation::broadcastMessageRange(const String& message)\n";
	}
}

void ChatManagerImplementation::handleMessage(Player* player, Message* pack) {
	try {
		pack->parseLong();
		UnicodeString msg;

		UnicodeString text;
		pack->parseUnicode(text);

		UnicodeTokenizer tokenizer(text);

		uint64 targetid = tokenizer.getLongToken();
		uint32 mood2 = tokenizer.getIntToken();
		uint32 moodid = tokenizer.getIntToken();
		uint32 unk2 = tokenizer.getIntToken();
		uint32 unk3 = tokenizer.getIntToken();

		tokenizer.finalToken(msg);

		if (msg[0] == '@') {
			handleGameCommand(player, msg.toString());
		} else {
			if (isMute()) {
				if (player->getAdminLevel() & PlayerImplementation::ADMIN) {
					broadcastMessage(player, msg, targetid, moodid, mood2);
				} else {
					((CreatureObject*) player)->sendSystemMessage("Chat has been muted by the admins");
				}
			} else {
				broadcastMessage(player, msg, targetid, moodid, mood2);
			}
		}
	} catch (PacketIndexOutOfBoundsException& e) {
		System::out << e.getMessage() << "\n" << pack->toString() << "\n";
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in ChatManagerImplementation::handleMessage " << e.getMessage() << "\n";
		System::out << msg.toString();
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught in ChatManagerImplementation::handleMessage\n";
	}

}

void ChatManagerImplementation::handleEmote(Player* player, Message* pack) {
	if (player->isChatMuted()) {
		player->sendSystemMessage("Chat has been muted by the admins");
		return;
	}

	UnicodeString emote;
	Zone* zone = player->getZone();

	pack->parseLong();
	pack->parseUnicode(emote);

	StringTokenizer tokenizer(emote.toString());

	try {
		zone->lock();

		uint64 targetid = tokenizer.getLongToken();
		uint32 emoteid = tokenizer.getIntToken();
		uint32 unkint = tokenizer.getIntToken();
		uint32 unkint2 = tokenizer.getIntToken();

		bool showtext = true;

		if (unkint2 == 0)
			showtext = false;

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_this);

			if (object->isPlayer()) {
				Player* creature = (Player*) object;

				Emote* emsg = new Emote(creature, player, targetid, emoteid, showtext);
				creature->sendMessage(emsg);
			}
		}

		zone->unlock();
	} catch (...) {

		zone->unlock();

		System::out << "exception ChatManagerImplementation::handleEmote(Player* player, Message* pack)\n";
	}
}

void ChatManagerImplementation::handleMood(Player* player, Message* pack) {
	UnicodeString mood;

	pack->parseLong();
	pack->parseUnicode(mood);

	StringTokenizer tokenizer(mood.toString());

	if (!tokenizer.hasMoreTokens())
		return;

	uint8 moodid = (uint8)tokenizer.getIntToken();

	player->setMood(moodid);

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(player);
	dcreo6->updateMoodID();
	dcreo6->updateMoodStr();
	dcreo6->close();

	player->broadcastMessage(dcreo6);
}

void ChatManagerImplementation::handleGameCommand(Player* player, const String& command) {
	StringTokenizer tokenizer(command);

	String cmd;
	tokenizer.getStringToken(cmd);

	cmd = cmd.subString(1, cmd.length());
	gameCommandHandler->handleCommand(cmd, tokenizer, player);
}

void ChatManagerImplementation::addPlayer(Player* player) {
	lock();

	String name = player->getFirstName().toLowerCase();
	playerMap->put(name, player, false);

	unlock();
}

Player* ChatManagerImplementation::getPlayer(String& name) {
	lock();

	String lName = name.toLowerCase();

	Player* player = playerMap->get(lName, false);

	unlock();
	return player;
}

Player* ChatManagerImplementation::removePlayer(String& name) {
	lock();

	String lName = name.toLowerCase();

	Player* player = playerMap->remove(lName, false);

	unlock();
	return player;
}

void ChatManagerImplementation::sendMail(const String& sendername, UnicodeString& header, UnicodeString& body, const String& name) {
	Player* receiver = NULL;

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;

	String playerName = name.toLowerCase();

	receiver = getPlayer(playerName);

  	//guild mail?
  	String checkReceiver = playerName;
  	String guildSender = sendername;

  	if (checkReceiver == "guild") {
		Player* sender = getPlayer(guildSender);
		if (sender == NULL)
			return;

  		if (!(sender->getGuildPermissions() & PlayerImplementation::GUILDMAIL)) {
			sender->sendSystemMessage("@guild:generic_fail_no_permission");
			return;
		}

  		GuildManager* gm = server->getGuildManager();
  		if (gm == NULL)
  			return;

  		StringBuffer mySender;
  		mySender << "Guildmail: " << sendername;

  		gm->sendGuildMail(sender, mySender.toString(), header.toString() , body.toString(), false);

  		return;
  	}
  	//end guildmail

  	try {
		MySqlDatabase::escapeString(playerName);

		uint64 receiverObjId;

		//receiver = valid player?
		StringBuffer idqry;
		idqry << "SELECT character_id FROM characters WHERE lower(firstname) = '" << playerName << "';";

		ResultSet* rescid = ServerDatabase::instance()->executeQuery(idqry);
		if (rescid->next())
			receiverObjId = rescid->getInt(0);
		else {
			delete rescid;
			return;
		}

		delete rescid;

		//Receiver is valid: Insert mail into db.

	  	String headerString = header.toString();
	  	MySqlDatabase::escapeString(headerString);

	  	String bodyString = body.toString();
	  	MySqlDatabase::escapeString(bodyString);

	  	String senderName = sendername;
	  	MySqlDatabase::escapeString(senderName);

		StringBuffer inmqry;
	    inmqry << "INSERT INTO `mail` "
	        << "(`sender_name`,`recv_name`,`subject`,`body`,`time`,`read`)"
		    << "VALUES ('" << senderName << "','" << playerName << "','" << headerString << "','" << bodyString << "',"
		    << currentTime << ",0);" ;

		ServerDatabase::instance()->executeStatement(inmqry);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		return;
	}

	if (receiver == NULL)
		return;

	try {
		//receiver->wlock();

		StringBuffer query;
		query << "SELECT mail_id FROM mail WHERE time = " << currentTime << " and lower(recv_name) = '" << playerName << "';";

		ResultSet* mail = ServerDatabase::instance()->executeQuery(query);

		while (mail->next()) {
			int mailid = mail->getInt(0);

			BaseMessage* mmsg = new ChatPersistentMessageToClient(sendername, mailid, 0x01, header, body, currentTime, 'N');
			receiver->sendMessage(mmsg);


			StringBuffer update;
			update << "UPDATE `mail` SET `read` = 1 WHERE mail_id = " << mailid << ";";
			ServerDatabase::instance()->executeStatement(update);

		}

		delete mail;

		//receiver->unlock();
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		//receiver->unlock();
		return;
	}
}

void ChatManagerImplementation::sendMailBody(Player* receiver, uint32 mailid) {
	if (!receiver->isOnline())
		return;

	try {

		StringBuffer query;
		query << "SELECT * FROM mail WHERE mail_id = " << mailid << ";";

		ResultSet* mail = ServerDatabase::instance()->executeQuery(query);

		if (mail->next()) {
			String sender = mail->getString(1);
			UnicodeString subject = mail->getString(3);
			UnicodeString body = mail->getString(4);

			BaseMessage* mmsg = new ChatPersistentMessageToClient(sender, mailid, 0, subject, body);
			receiver->sendMessage(mmsg);

			StringBuffer update;
			update << "UPDATE `mail` SET `read` = 2 WHERE mail_id = " << mailid << ";";
			ServerDatabase::instance()->executeStatement(update);
		}


		delete mail;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

void ChatManagerImplementation::listMail(Player* ply) {
	try {
		String name = ply->getFirstName();
		MySqlDatabase::escapeString(name);
		StringBuffer query;
		query << "SELECT * FROM mail WHERE recv_name = '" << name <<"';";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			uint32 mailid = res->getInt(0);
			String sendername = res->getString(1);
			UnicodeString header = res->getString(3);
			UnicodeString body = res->getString(4);
			uint32 mailTime = res->getUnsignedInt(5);
			short read = res->getInt(7);

			char status;
			if (read == 2)
				status = 'R';
			else if (read == 1)
				status = 'U';
			else {
				status = 'N';
				read++;
			}

			BaseMessage* mmsg = new ChatPersistentMessageToClient(sendername, mailid, 0x01, header, body, mailTime, status);
			ply->sendMessage(mmsg);

			StringBuffer update;
			update << "UPDATE `mail` SET `read` = " << read << " WHERE mail_id = " << mailid << ";";
			ServerDatabase::instance()->executeStatement(update);
		}

		delete res;
	} catch(DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

void ChatManagerImplementation::deleteMail(uint32 mailid) {
	try {
		StringBuffer query;
		query << "DELETE FROM mail WHERE mail_id = '" << mailid <<"';";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

void ChatManagerImplementation::handleChatRoomMessage(Player* sender, Message* pack) {
	if (sender->isChatMuted()) {
		sender->sendSystemMessage("Chat has been muted by the admins");
		return;
	}

	String name = sender->getFirstName();

	UnicodeString message;
	pack->parseUnicode(message);

	String adminmsg = message.toString();

	if (adminmsg[0] == '@') {
		try {
			sender->wlock();

			handleGameCommand(sender, adminmsg);

			sender->unlock();
			return;
		} catch (...) {
			sender->error("error while executing gameCommand in ChatManagerImplementation::handleChatRoomMessage(Player* sender, Message* pack)");
			sender->unlock();
		}
	}

	pack->shiftOffset(4);

	uint32 channelid = pack->parseInt();

	uint32 counter = pack->parseInt();

	ChatRoom* channel = getChatRoom(channelid);

	if (channel == NULL)
		return;

	if (!channel->hasPlayer(sender))
		return;

	BaseMessage* msg = new ChatRoomMessage(name, message, channelid);
	channel->broadcastMessage(msg);

	BaseMessage* amsg = new ChatOnSendRoomMessage(counter);
	channel->broadcastMessage(amsg);

	/*Vector<Message*> messages;
	messages.add(msg);
	messages.add(amsg);

	channel->broadcastMessage(messages);*/
}

void ChatManagerImplementation::handleGroupChat(Player* sender, Message* pack) {
	if (sender->isChatMuted()) {
		sender->sendSystemMessage("Chat has been muted by the admins");
		return;
	}

	String name = sender->getFirstName();
	pack->shiftOffset(8);

	UnicodeString message;
	pack->parseUnicode(message);


	String adminmsg = message.toString();

	if (adminmsg[0] == '@') {
		handleGameCommand(sender, adminmsg);
		return;
	}


	GroupObject* group = sender->getGroupObject();
	if (group == NULL)
		return;

	sender->unlock();

	try {
		group->wlock();

		BaseMessage* msg = new ChatRoomMessage(name, message, group->getGroupChannel()->getRoomID());
		group->broadcastMessage(msg);

		group->unlock();
	} catch (...) {
		System::out << "Exception in ChatManagerImplementation::handleGroupChat(Player* sender, Message* pack)\n";
		group->unlock();
	}
	sender->wlock();
}

void ChatManagerImplementation::handleGuildChat(Player* sender, Message* pack) {
	String name = sender->getFirstName();
	pack->shiftOffset(8);

	UnicodeString message;
	pack->parseUnicode(message);


	String adminmsg = message.toString();

	if (adminmsg[0] == '@') {
		handleGameCommand(sender, adminmsg);
		return;
	}


	Guild* kuild;
	kuild = sender->getGuild();

	if (kuild == NULL) {
		return;
	}

	ChatRoom* guildChat = kuild->getGuildChat();

	if (guildChat == NULL) {
		return;
	}

	sender->unlock();

	try {
		kuild->wlock();

		BaseMessage* msg = new ChatRoomMessage(name, message, guildChat->getRoomID());
		guildChat->broadcastMessage(msg);

		kuild->unlock();
	} catch (...) {
		System::out << "Exception in ChatManagerImplementation::handleGuildChat(Player* sender, Message* pack)\n";
		kuild->unlock();
	}

	sender->wlock();
}

void ChatManagerImplementation::handleChatEnterRoomById(Player* player, Message* pack) {
	uint32 counter = pack->parseInt();
	uint32 roomID = pack->parseInt();

	ChatRoom* room = getChatRoom(roomID);

	if (room == NULL)
		return;

	if (room->isPublic())
		room->addPlayer(player);
}

void ChatManagerImplementation::handleCreateRoom(Player* player, Message* pack) {
	pack->shiftOffset(4); // Unknown

	String fullPath;
	pack->parseAscii(fullPath);

	ChatRoom* newRoom = createRoomByFullPath(fullPath);

	if (newRoom == NULL)
		return;

	String title;
	pack->parseAscii(title);

	uint32 counter = pack->parseInt();

	newRoom->setTitle(title);
	newRoom->setCreator(player->getFirstName());
	newRoom->setOwner(player->getFirstName());

	addRoom(newRoom);

	ChatOnCreateRoom* msg = new ChatOnCreateRoom(newRoom, counter);
	player->sendMessage(msg);
}

void ChatManagerImplementation::handleChatDestroyRoom(Player* player, Message* pack) {
	uint32 id = pack->parseInt();
	uint32 counter = pack->parseInt();

	ChatRoom* room = getChatRoom(id);

	if (room == NULL)
		return;

	if (room->getOwner() != player->getFirstName())
		return;

	destroyRoom(room);
}

void ChatManagerImplementation::handleChatRemoveAvatarFromRoom(Player* player, Message* pack) {
	String game;
	pack->parseAscii(game);

	String Server;
	pack->parseAscii(Server);

	String Player;
	pack->parseAscii(Player);

	String chanPath;
	pack->parseAscii(chanPath);

	ChatRoom* room = getChatRoomByFullPath(chanPath);
	if (room == NULL)
		return;

	if (!room->hasPlayer(Player))
		return;

	if ((player->getFirstName() == Player) ||  player->getFirstName() == room->getOwner())
		room->removePlayer(Player);
}

ChatRoom* ChatManagerImplementation::createRoomByFullPath(const String& path) {
	StringTokenizer tokenizer(path);
	tokenizer.setDelimeter(".");

	String game;
	tokenizer.getStringToken(game);

	ChatRoom* gameRoom = getGameRoom(game);

	if (gameRoom == NULL)
		return NULL;

	String channel;

	ChatRoom* room = gameRoom;
	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(channel);

		if (room->getSubRoom(channel) == NULL)
			break;
		else
			room = room->getSubRoom(channel);
	}

	if (room == gameRoom)
		return NULL;

	if (room->isPrivate())
		return NULL;

	ChatRoom* newRoom = new ChatRoom(server, room, channel, getNextRoomID());
	newRoom->deploy();

	room->addSubRoom(newRoom);

	return newRoom;
}

ChatRoom* ChatManagerImplementation::getChatRoom(uint32 id) {
	lock();

	ChatRoom* channel = roomMap->get(id);

	unlock();

	return channel;
}

void ChatManagerImplementation::addRoom(ChatRoom* channel) {
	lock();

	roomMap->put(channel->getRoomID(), channel);

	unlock();
}

void ChatManagerImplementation::removeRoom(ChatRoom* channel) {
	lock();

	roomMap->remove(channel->getRoomID());

	unlock();
}

void ChatManagerImplementation::sendRoomList(Player* player) {
	ChatRoomList* crl = new ChatRoomList();

	String game = "SWG";
	populateRoomListMessage(gameRooms.get(game), crl);

 	crl->insertChannelListCount();
 	player->sendMessage(crl);
}

void ChatManagerImplementation::sendGuildChat(Player* player) {
	if (player->getGuildID() == 0)
		return;

	Guild* playerGuild = player->getGuild();
	//No Null Check: Player has always a guild (Default guild (unguilded) is 0 )

	playerGuild->wlock();

	ChatRoom* guildchat = playerGuild->getGuildChat();

	playerGuild->unlock();

	if (guildchat == NULL) {
		uint32 guildid = player->getGuildID();

		initGuildChannel(player,guildid);
	} else {
		guildchat->sendTo(player);
		guildchat->addPlayer(player, false);
	}
}


void ChatManagerImplementation::populateRoomListMessage(ChatRoom* channel, ChatRoomList* msg) {
	if (channel->isPublic())
		msg->addChannel(channel);

	for (int i = 0; i < channel->getSubRoomsSize(); i++) {
		ChatRoom* chan = channel->getSubRoom(i);

		populateRoomListMessage(chan, msg);
	}
}

void ChatManagerImplementation::printRoomTree(ChatRoom* channel, String name) {
	if (channel == NULL)
		return;

	name = name + channel->getName();

	System::out << "Name: " << name << "\n" << endl;

	for (int i = 0; i < channel->getSubRoomsSize(); i++) {
		ChatRoom* chan = channel->getSubRoom(i);
		printRoomTree(chan, name + ".");
	}
}

ChatRoom* ChatManagerImplementation::getChatRoomByGamePath(ChatRoom* game, const String& path) {
	StringTokenizer tokenizer(path);
	tokenizer.setDelimeter(".");

	String channel;
	ChatRoom* room = game;

	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(channel);

		room = room->getSubRoom(channel);
		if (room == NULL)
			return NULL;
	}

	if (room == game)
		return NULL;
	else
		return room;
}

ChatRoom* ChatManagerImplementation::getChatRoomByFullPath(const String& path) {
	StringTokenizer tokenizer(path);
	tokenizer.setDelimeter(".");

	if (!tokenizer.hasMoreTokens())
		return NULL;

	String game;
	tokenizer.getStringToken(game);

	ChatRoom* gameRoom = getGameRoom(game);

	if (gameRoom == NULL)
		return NULL;

	String gamePath;
	tokenizer.finalToken(gamePath);

	return getChatRoomByGamePath(gameRoom, gamePath);
}

ChatRoom* ChatManagerImplementation::getGameRoom(const String& game) {
	return gameRooms.get(game);
}

ChatRoom* ChatManagerImplementation::createGroupRoom(uint32 groupID, Player* creator) {
	// Pre: creator locked;
	// Post: creator locked.


	ChatRoom* groupChatRoom;

	StringBuffer name;
	name << groupID;

	ChatRoom* newGroupRoom = new ChatRoom(server, groupRoom, name.toString(), getNextRoomID());
	newGroupRoom->deploy();

	newGroupRoom->setPrivate();
	groupRoom->addSubRoom(newGroupRoom);
	addRoom(newGroupRoom);

	groupChatRoom = new ChatRoom(server, newGroupRoom, "GroupChat", getNextRoomID());
	groupChatRoom->deploy();

	groupChatRoom->setTitle(name.toString());
	groupChatRoom->setPrivate();

	groupChatRoom->sendTo(creator);
	groupChatRoom->addPlayer(creator, false);

	newGroupRoom->addSubRoom(groupChatRoom);
	addRoom(groupChatRoom);

	return groupChatRoom;
}

void ChatManagerImplementation::initGuildChannel(Player* creator, uint32 gid) {
	// Pre: creator locked;
	// Post: creator locked.

	Guild* kuild;
	kuild = creator->getGuild();

	kuild->wlock();

	if (kuild->getGuildChat() != NULL) {
		kuild->unlock();
		return;
	}

	StringBuffer name;

	uint32 guildID = gid;

	ChatRoom* newGuildRoom = new ChatRoom(server, guildRoom, name.toString(), getNextRoomID());
	newGuildRoom->deploy();

	newGuildRoom->setPrivate();
	guildRoom->addSubRoom(newGuildRoom);
	addRoom(newGuildRoom);

	ChatRoom* guildChatRoom = new ChatRoom(server, newGuildRoom, "GuildChat", getNextRoomID());
	guildChatRoom->deploy();

	guildChatRoom->setTitle(name.toString());
	guildChatRoom->setPrivate();

	guildChatRoom->sendTo(creator);
	guildChatRoom->addPlayer(creator, false);

	newGuildRoom->addSubRoom(guildChatRoom);
	addRoom(guildChatRoom);

	kuild->setGuildChat(guildChatRoom);

	kuild->unlock();
}

void ChatManagerImplementation::destroyRoom(ChatRoom* room) {
	lock();

	roomMap->remove(room->getRoomID());

	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getServerName(), room->getRoomID());
	room->broadcastMessage(msg);
	room->removeAllPlayers();

	ChatRoom* parent = room->getParent();

	if (parent != NULL)
		parent->removeSubRoom(room);

	room->finalize();

	unlock();
}
