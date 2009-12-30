/*
 * ChatManagerImplementation.cpp
 *
 *  Created on: 28/07/2009
 *      Author: victor
 */

#include "ChatManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/player/PlayerMap.h"
#include "server/zone/packets/chat/ChatRoomList.h"
#include "server/zone/packets/chat/ChatRoomMessage.h"
#include "server/zone/packets/object/SpatialChat.h"
#include "server/zone/packets/chat/ChatInstantMessageToCharacter.h"
#include "server/zone/packets/chat/ChatInstantMessageToClient.h"
#include "server/zone/packets/chat/ChatOnSendInstantMessage.h"
#include "server/zone/packets/chat/ChatOnDestroyRoom.h"
#include "server/zone/objects/group/GroupObject.h"

#include "room/ChatRoom.h"
#include "room/ChatRoomMap.h"

ChatManagerImplementation::ChatManagerImplementation(ZoneServer* serv, int initsize) : ManagedObjectImplementation() {
	server = serv;

	//userManager = server->getUserManager();

	playerManager = serv->getPlayerManager();
	//guildManager = playerManager->getGuildManager();

	//resourceManager = server->getResourceManager();

	playerMap = new PlayerMap(initsize);
	//playerMap->deploy("ChatPlayerMap");

	roomMap = new ChatRoomMap(10000);

	mute = false;

	roomID = 0xFFFFFFFF;
	roomID = roomID << 32;

	//gameRooms = new VectorMap<String, ManagedReference<ChatRoom*> >();

	//gameCommandHandler = new GameCommandHandler();
}

/*ChatManagerImplementation::~ChatManagerImplementation() {
	destroyRooms();

	playerMap->finalize();
	playerMap = NULL;

	delete roomMap;
	roomMap = NULL;

	delete gameCommandHandler;
	gameCommandHandler = NULL;
}*/

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

/*void ChatManagerImplementation::wlock() {
	ManagedObjectImplementation::wlock(true);
}

void ChatManagerImplementation::unlock() {
	ManagedObjectImplementation::unlock(true);
}*/

void ChatManagerImplementation::destroyRooms() {
	wlock();

	roomMap->resetIterator();

	while (roomMap->hasNext()) {
		ChatRoom* room = roomMap->next();
		room->finalize();
	}

	roomMap->removeAll();

	gameRooms.removeAll();

	unlock();
}

void ChatManagerImplementation::addRoom(ChatRoom* channel) {
	wlock();

	roomMap->put(channel->getRoomID(), channel);

	unlock();
}

void ChatManagerImplementation::removeRoom(ChatRoom* channel) {
	wlock();

	roomMap->remove(channel->getRoomID());

	unlock();
}

void ChatManagerImplementation::populateRoomListMessage(ChatRoom* channel, ChatRoomList* msg) {
	if (channel->isPublic())
		msg->addChannel(channel);

	for (int i = 0; i < channel->getSubRoomsSize(); i++) {
		ChatRoom* chan = channel->getSubRoom(i);

		populateRoomListMessage(chan, msg);
	}
}

void ChatManagerImplementation::sendRoomList(PlayerCreature* player) {
	ChatRoomList* crl = new ChatRoomList();

	String game = "SWG";
	populateRoomListMessage(gameRooms.get(game), crl);

 	crl->insertChannelListCount();
 	player->sendMessage(crl);
}

void ChatManagerImplementation::addPlayer(PlayerCreature* player) {
	wlock();

	String name = player->getFirstName().toLowerCase();
	playerMap->put(name, player, false);

	unlock();
}

PlayerCreature* ChatManagerImplementation::getPlayer(const String& name) {
	wlock();

	PlayerCreature* player = NULL;

	try {
		String lName = name.toLowerCase();

		player = playerMap->get(lName, false);
	} catch (Exception& e) {
		System::out << e.getMessage();
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught in ChatManagerImplementation::getPlayer";
	}

	unlock();
	return player;
}

PlayerCreature* ChatManagerImplementation::removePlayer(const String& name) {
	wlock();

	String lName = name.toLowerCase();

	PlayerCreature* player = playerMap->remove(lName, false);

	unlock();
	return player;
}

void ChatManagerImplementation::broadcastMessage(CreatureObject* player, const UnicodeString& message,  uint64 target, uint32 moodid, uint32 mood2) {
	if (player->isPlayerCreature() /*|| !((Player *)player)->isChatMuted() */) {
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

		if (zone == NULL)
			return;

		Locker zoneLocker(zone);

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_this);

			if (object->isPlayerCreature()) {
				PlayerCreature* creature = (PlayerCreature*) object;

				if (player->isInRange(creature, 128)) {
					SpatialChat* cmsg = new SpatialChat(player->getObjectID(), creature->getObjectID(), message, target, moodid, mood2);
					creature->sendMessage(cmsg);
				}
			}
		}

	}
}

void ChatManagerImplementation::handleSpatialChatInternalMessage(PlayerCreature* player, const UnicodeString& args) {
	try {
		UnicodeTokenizer tokenizer(args);

		uint64 targetid = tokenizer.getLongToken();
		uint32 mood2 = tokenizer.getIntToken();
		uint32 moodid = tokenizer.getIntToken();
		uint32 unk2 = tokenizer.getIntToken();
		uint32 unk3 = tokenizer.getIntToken();

		UnicodeString msg;

		tokenizer.finalToken(msg);

		/*if (msg[0] == '@') {
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
		}*/
		broadcastMessage(player, msg, targetid, moodid, mood2);

	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in ChatManagerImplementation::handleMessage " << e.getMessage() << "\n";
		System::out << msg.toString();
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught in ChatManagerImplementation::handleMessage\n";
	}
}

void ChatManagerImplementation::handleChatInstantMessageToCharacter(ChatInstantMessageToCharacter* message) {
	ManagedReference<PlayerCreature*> sender = (PlayerCreature*) message->getClient()->getPlayer();
	PlayerCreature* receiver = getPlayer(message->getName());

	if (receiver == NULL || !receiver->isOnline()) {
		BaseMessage* amsg = new ChatOnSendInstantMessage(message->getSequence(), true);
		sender->sendMessage(amsg);

		return;
	}

	BaseMessage* msg = new ChatInstantMessageToClient(message->getGame(), message->getGalaxy(), sender->getFirstName(), message->getMessage());
	receiver->sendMessage(msg);

	BaseMessage* amsg = new ChatOnSendInstantMessage(message->getSequence(), false);
	sender->sendMessage(amsg);
}

ChatRoom* ChatManagerImplementation::createGroupRoom(uint64 groupID, PlayerCreature* creator) {
	// Pre: creator locked;
	// Post: creator locked.

	ManagedReference<ChatRoom*> groupChatRoom;

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

void ChatManagerImplementation::destroyRoom(ChatRoom* room) {
	Locker _locker(_this);

	roomMap->remove(room->getRoomID());

	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getServerName(), room->getRoomID());
	room->broadcastMessage(msg);
	room->removeAllPlayers();

	ManagedReference<ChatRoom*> parent = room->getParent();

	if (parent != NULL)
		parent->removeSubRoom(room);
}


void ChatManagerImplementation::handleGroupChat(PlayerCreature* sender, const UnicodeString& message) {
	/*if (sender->isChatMuted()) {
		sender->sendSystemMessage("Your chat abilities are currently disabled by the server administrators.");
		return;
	}*/

	String name = sender->getFirstName();

	ManagedReference<GroupObject*> group = sender->getGroup();
	if (group == NULL)
		return;

	sender->unlock();

	try {
		group->wlock();

		ManagedReference<ChatRoom*> room = group->getGroupChannel();

		if (room != NULL) {
			BaseMessage* msg = new ChatRoomMessage(name, message, room->getRoomID());
			group->broadcastMessage(msg);
		}

		group->unlock();
	} catch (...) {
		System::out << "Exception in ChatManagerImplementation::handleGroupChat(Player* sender, Message* pack)\n";
		group->unlock();
	}

	sender->wlock();
}
