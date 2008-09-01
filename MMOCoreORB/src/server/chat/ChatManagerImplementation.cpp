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
#include "../zone/ZoneClient.h"
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

	ChatRoom* generalRoom = new ChatRoom(server, core3Room, "general", getNextRoomID());
	generalRoom->deploy();
	core3Room->addSubRoom(generalRoom);
	addRoom(generalRoom);
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

	string game, galaxy, name;
	unicode message;


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

void ChatManagerImplementation::sendSystemMessage(Player* player, unicode& message) {
	ChatSystemMessage* smsg = new ChatSystemMessage(message);
	player->sendMessage(smsg);
}

void ChatManagerImplementation::broadcastMessage(Player* player, unicode& message,  uint64 target, uint32 moodid, uint32 mood2) {
	if ( !player->isChatMuted() ) {
		Zone* zone = player->getZone();

		/*if (message.c_str() == "LAG") {
			ZoneClient* client = player->getClient();

			client->reportStats(true);

			Logger::slog("Client (" + client->getAddress() + ") is experiencing lag", true);
			return;
		} else if (message.c_str() == "QUEUE") {
			ZoneClient* client = player->getClient();

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

			cout << "exception ChatManagerImplementation::broadcastMessage(Player* player, unicode& message,  uint64 target, uint32 moodid, uint32 mood2)\n";
		}
	}
}

void ChatManagerImplementation::broadcastMessage(const string& message) {
	lock();

	playerMap->resetIterator(false);

	while (playerMap->hasNext(false)) {
		Player* player = playerMap->getNextValue(false);

		player->sendSystemMessage(message);
	}

	unlock();
}

void ChatManagerImplementation::broadcastMessageRange(Player* player, const string& message, float range) {
	try {
		lock();

		//TODO make it polling the spatial indexer instead of iterating the whole hash table
		playerMap->resetIterator(false);

		while (playerMap->hasNext(false)) {
			Player* trgplayer = playerMap->getNextValue(false);

			if(player->isInRange((SceneObject*)trgplayer, range)) {
				trgplayer->sendSystemMessage(message);
			}
		}

		unlock();
	} catch (...) {

		unlock();

		cout << "exception ChatManagerImplementation::broadcastMessageRange(const string& message)\n";
	}
}

void ChatManagerImplementation::handleMessage(Player* player, Message* pack) {
	try {
		pack->parseLong();
		string msg;

		unicode text;
		pack->parseUnicode(text);

		StringTokenizer tokenizer(text.c_str());

		uint64 targetid = tokenizer.getLongToken();
		uint32 mood2 = tokenizer.getIntToken();
		uint32 moodid = tokenizer.getIntToken();
		uint32 unk2 = tokenizer.getIntToken();
		uint32 unk3 = tokenizer.getIntToken();

		tokenizer.finalToken(msg);

		if (msg[0] == '@') {
			handleGameCommand(player, msg.c_str());
		} else {
			if(isMute()) {
				if(player->getAdminLevel() & PlayerImplementation::ADMIN) {
					unicode mess = msg;
					broadcastMessage(player, mess, targetid, moodid, mood2);
				} else {
					((CreatureObject*) player)->sendSystemMessage("Chat has been muted by the admins");
				}
			} else {
				unicode mess = msg;
				broadcastMessage(player, mess, targetid, moodid, mood2);
			}
		}
	} catch (PacketIndexOutOfBoundsException& e) {
		cout << e.getMessage() << "\n" << pack->toString() << "\n";
	} catch (Exception& e) {
		stringstream msg;
		msg << "Exception in ChatManagerImplementation::handleMessage " << e.getMessage() << "\n";
		cout << msg.str();
		e.printStackTrace();
	} catch (...) {
		cout << "unreported exception caught in ChatManagerImplementation::handleMessage\n";
	}

}

void ChatManagerImplementation::handleEmote(Player* player, Message* pack) {
	if (player->isChatMuted()) {
		player->sendSystemMessage("Chat has been muted by the admins");
		return;
	}

	unicode emote;
	Zone* zone = player->getZone();

	pack->parseLong();
	pack->parseUnicode(emote);

	StringTokenizer tokenizer(emote.c_str());

	try {
		zone->lock();

		uint64 targetid = tokenizer.getLongToken();
		uint32 emoteid = tokenizer.getIntToken();
		uint32 unkint = tokenizer.getIntToken();
		uint32 unkint2 = tokenizer.getIntToken();

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_this);

			if (object->isPlayer()) {
				Player* creature = (Player*) object;

				Emote* emsg = new Emote(creature, player, targetid, emoteid);
				creature->sendMessage(emsg);
			}
		}

		zone->unlock();
	} catch (...) {

		zone->unlock();

		cout << "exception ChatManagerImplementation::handleEmote(Player* player, Message* pack)\n";
	}
}

void ChatManagerImplementation::handleMood(Player* player, Message* pack) {
	unicode mood;

	pack->parseLong();
	pack->parseUnicode(mood);

	StringTokenizer tokenizer(mood.c_str());

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

void ChatManagerImplementation::handleGameCommand(Player* player, const string& command) {
	StringTokenizer tokenizer(command);

	string cmd;
	tokenizer.getStringToken(cmd);

	cmd = cmd.substr(1, cmd.length() - 1);
	gameCommandHandler->handleCommand(cmd, tokenizer, player);
}

void ChatManagerImplementation::addPlayer(Player* player) {
	lock();

	string& name = player->getFirstName();
	String::toLower(name);
	playerMap->put(name, player, false);

	unlock();
}

Player* ChatManagerImplementation::getPlayer(string& name) {
	lock();

	String::toLower(name);
	Player* player = playerMap->get(name, false);

	unlock();
	return player;
}

Player* ChatManagerImplementation::removePlayer(string& name) {
	lock();

	String::toLower(name);
	Player* player = playerMap->remove(name, false);

	unlock();
	return player;
}

void ChatManagerImplementation::sendMail(const string& sendername, unicode& header, unicode& body, const string& name) {
	Player* receiver = NULL;

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;

	string Name = name;
  	String::toLower(Name);
  	receiver = getPlayer(Name);

  	try {
		MySqlDatabase::escapeString(Name);

		uint64 receiverObjId;

		stringstream idqry;
		idqry << "SELECT character_id FROM characters WHERE lower(firstname) = '" << Name << "';";

		ResultSet* rescid = ServerDatabase::instance()->executeQuery(idqry);
		if (rescid->next())
			receiverObjId = rescid->getInt(0);
		else {
			delete rescid;
			return;
		}

		delete rescid;

		//Insert mail into db.

	  	string headerString = header.c_str();
	  	MySqlDatabase::escapeString(headerString);

	  	string bodyString = body.c_str();
	  	MySqlDatabase::escapeString(bodyString);

	  	string senderName = sendername;
	  	MySqlDatabase::escapeString(senderName);

		stringstream inmqry;
	    inmqry << "INSERT INTO `mail` "
	        << "(`sender_name`,`recv_name`,`subject`,`body`,`time`,`read`)"
		    << "VALUES ('" << senderName << "','" << Name << "','" << headerString << "','" << bodyString << "',"
		    << currentTime << ",0);" ;

		ServerDatabase::instance()->executeStatement(inmqry);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";

		return;
	}

	if (receiver == NULL)
		return;

	try {
		//receiver->wlock();

		stringstream query;
		query << "SELECT mail_id FROM mail WHERE time = " << currentTime << ";";

		ResultSet* mail = ServerDatabase::instance()->executeQuery(query);

		if (mail->next()) {
			int mailid = mail->getInt(0);

			BaseMessage* mmsg = new ChatPersistentMessageToClient(sendername, mailid, 0x01, header, body, currentTime, 'N');
			receiver->sendMessage(mmsg);

			stringstream update;
			update << "UPDATE `mail` SET `read` = 1 WHERE mail_id = " << mailid << ";";
			ServerDatabase::instance()->executeQuery(update);

		}

		delete mail;

		//receiver->unlock();
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";

		//receiver->unlock();
		return;
	}
}

void ChatManagerImplementation::sendMailBody(Player* receiver, uint32 mailid) {
	if (!receiver->isOnline())
		return;

	try {

		stringstream query;
		query << "SELECT * FROM mail WHERE mail_id = " << mailid << ";";

		ResultSet* mail = ServerDatabase::instance()->executeQuery(query);

		if (mail->next()) {
			string sender = mail->getString(1);
			unicode subject = mail->getString(3);
			unicode body = mail->getString(4);

			BaseMessage* mmsg = new ChatPersistentMessageToClient(sender, mailid, 0, subject, body);
			receiver->sendMessage(mmsg);

			stringstream update;
			update << "UPDATE `mail` SET `read` = 2 WHERE mail_id = " << mailid << ";";
			ServerDatabase::instance()->executeQuery(update);
		}


		delete mail;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ChatManagerImplementation::listMail(Player* ply) {
	try {
		string name = ply->getFirstName();
		MySqlDatabase::escapeString(name);
		stringstream query;
		query << "SELECT * FROM mail WHERE recv_name = '" << name <<"';";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			uint32 mailid = res->getInt(0);
			string sendername = res->getString(1);
			unicode header = res->getString(3);
			unicode body = res->getString(4);
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

			stringstream update;
			update << "UPDATE `mail` SET `read` = " << read << " WHERE mail_id = " << mailid << ";";
			ServerDatabase::instance()->executeQuery(update);
		}

		delete res;
	} catch(DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ChatManagerImplementation::deleteMail(uint32 mailid) {
	try {
		stringstream query;
		query << "DELETE FROM mail WHERE mail_id = '" << mailid <<"';";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ChatManagerImplementation::handleChatRoomMessage(Player* sender, Message* pack) {
	if (sender->isChatMuted()) {
		sender->sendSystemMessage("Chat has been muted by the admins");
		return;
	}

	string name = sender->getFirstName();

	unicode message;
	pack->parseUnicode(message);

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

	string name = sender->getFirstName();
	pack->shiftOffset(8);

	unicode message;
	pack->parseUnicode(message);

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
		cout << "Exception in ChatManagerImplementation::handleGroupChat(Player* sender, Message* pack)\n";
		group->unlock();
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
	pack->shiftOffset(4); // Unkown

	string fullPath;
	pack->parseAscii(fullPath);

	ChatRoom* newRoom = createRoomByFullPath(fullPath);

	if (newRoom == NULL)
		return;

	string title;
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
	string game;
	pack->parseAscii(game);

	string Server;
	pack->parseAscii(Server);

	string Player;
	pack->parseAscii(Player);

	string chanPath;
	pack->parseAscii(chanPath);

	ChatRoom* room = getChatRoomByFullPath(chanPath);
	if (room == NULL)
		return;

	if (!room->hasPlayer(Player))
		return;

	if ((player->getFirstName() == Player) ||  player->getFirstName() == room->getOwner())
		room->removePlayer(Player);
}

ChatRoom* ChatManagerImplementation::createRoomByFullPath(const string& path) {
	StringTokenizer tokenizer(path);
	tokenizer.setDelimeter(".");

	string game;
	tokenizer.getStringToken(game);

	ChatRoom* gameRoom = getGameRoom(game);

	if (gameRoom == NULL)
		return NULL;

	string channel;

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

	string game = "SWG";
	populateRoomListMessage(gameRooms.get(game), crl);

 	crl->insertChannelListCount();
 	player->sendMessage(crl);
}


void ChatManagerImplementation::populateRoomListMessage(ChatRoom* channel, ChatRoomList* msg) {
	if (channel->isPublic())
		msg->addChannel(channel);

	for (int i = 0; i < channel->getSubRoomsSize(); i++) {
		ChatRoom* chan = channel->getSubRoom(i);

		populateRoomListMessage(chan, msg);
	}
}

void ChatManagerImplementation::printRoomTree(ChatRoom* channel, string name) {
	if (channel == NULL)
		return;

	name = name + channel->getName();

	cout << "Name: " << name << "\n";

	for (int i = 0; i < channel->getSubRoomsSize(); i++) {
		ChatRoom* chan = channel->getSubRoom(i);
		printRoomTree(chan, name + ".");
	}
}

ChatRoom* ChatManagerImplementation::getChatRoomByGamePath(ChatRoom* game, const string& path) {
	StringTokenizer tokenizer(path);
	tokenizer.setDelimeter(".");

	string channel;
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

ChatRoom* ChatManagerImplementation::getChatRoomByFullPath(const string& path) {
	StringTokenizer tokenizer(path);
	tokenizer.setDelimeter(".");

	if (!tokenizer.hasMoreTokens())
		return NULL;

	string game;
	tokenizer.getStringToken(game);

	ChatRoom* gameRoom = getGameRoom(game);

	if (gameRoom == NULL)
		return NULL;

	string gamePath;
	tokenizer.finalToken(gamePath);

	return getChatRoomByGamePath(gameRoom, gamePath);
}

ChatRoom* ChatManagerImplementation::getGameRoom(const string& game) {
	return gameRooms.get(game);
}

ChatRoom* ChatManagerImplementation::createGroupRoom(uint32 groupID, Player* creator) {
	// Pre: creator locked;
	// Post: creator locked.
	stringstream name;
	name << groupID;

	ChatRoom* newGroupRoom = new ChatRoom(server, groupRoom, name.str(), getNextRoomID());
	newGroupRoom->deploy();

	newGroupRoom->setPrivate();
	groupRoom->addSubRoom(newGroupRoom);
	addRoom(newGroupRoom);

	ChatRoom* groupChatRoom = new ChatRoom(server, newGroupRoom, "GroupChat", getNextRoomID());
	groupChatRoom->deploy();

	groupChatRoom->setTitle(name.str());
	groupChatRoom->setPrivate();

	groupChatRoom->sendTo(creator);

	groupChatRoom->addPlayer(creator, false);

	newGroupRoom->addSubRoom(groupChatRoom);
	addRoom(groupChatRoom);

	return groupChatRoom;
}

void ChatManagerImplementation::destroyRoom(ChatRoom* room) {
	lock();

	roomMap->remove(room->getRoomID());

	unlock();

	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getServerName(), room->getRoomID());
	room->broadcastMessage(msg);
	room->removeAllPlayers();

	ChatRoom* parent = room->getParent();

	if (parent != NULL)
		parent->removeSubRoom(room);

	room->finalize();
}















