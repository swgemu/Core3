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
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/packets/chat/ChatRoomList.h"
#include "server/zone/packets/chat/ChatRoomMessage.h"
#include "server/zone/packets/object/SpatialChat.h"
#include "server/zone/packets/object/Emote.h"
#include "server/zone/packets/chat/ChatInstantMessageToCharacter.h"
#include "server/zone/packets/chat/ChatInstantMessageToClient.h"
#include "server/zone/packets/chat/ChatOnSendInstantMessage.h"
#include "server/zone/packets/chat/ChatOnSendRoomMessage.h"
#include "server/zone/packets/chat/ChatOnDestroyRoom.h"
#include "server/zone/packets/chat/ChatPersistentMessageToClient.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "PersistentMessage.h"
#include "ChatMessage.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "room/ChatRoom.h"
#include "room/ChatRoomMap.h"



ChatManagerImplementation::ChatManagerImplementation(ZoneServer* serv, int initsize) : ManagedServiceImplementation() {
	server = serv;

	//userManager = server->getUserManager();

	playerManager = NULL;
	//guildManager = playerManager->getGuildManager();

	//resourceManager = server->getResourceManager();

	ObjectDatabaseManager::instance()->loadObjectDatabase("mail", true);

	playerMap = new PlayerMap(initsize);
	//playerMap->deploy("ChatPlayerMap");

	roomMap = new ChatRoomMap(10000);

	mute = false;

	roomID = 0;

	setLoggingName("ChatManager");

	//gameRooms = new VectorMap<String, ManagedReference<ChatRoom*> >();

	//gameCommandHandler = new GameCommandHandler();
}

void ChatManagerImplementation::finalize() {
}

ChatRoom* ChatManagerImplementation::createRoom(const String& roomName, ChatRoom* parent) {
	ManagedReference<ChatRoom*> room = cast<ChatRoom*>(ObjectManager::instance()->createObject("ChatRoom", 0 , ""));
	room->init(server, parent, roomName, getNextRoomID());

	addRoom(room);

	return room;
}

void ChatManagerImplementation::initiateRooms() {
	gameRooms.setNullValue(NULL);

	ChatRoom* mainRoom = createRoom("SWG");
	mainRoom->setPrivate();
	gameRooms.put("SWG", mainRoom);

	ChatRoom* core3Room = createRoom(server->getGalaxyName(), mainRoom);
	core3Room->setPrivate();
	mainRoom->addSubRoom(core3Room);

	groupRoom = createRoom("group", core3Room);
	groupRoom->setPrivate();
	core3Room->addSubRoom(groupRoom);

	guildRoom = createRoom("guild", core3Room);
	guildRoom->setPrivate();
	core3Room->addSubRoom(guildRoom);

	ChatRoom* generalRoom = createRoom("general", core3Room);
	core3Room->addSubRoom(generalRoom);

	// Planet Chat
	for (int i = 0; i < server->getZoneCount(); ++i) {
		ManagedReference<Zone*> zone = server->getZone(i);

		if (zone == NULL)
			continue;

		ChatRoom* planetRoom = createRoom(zone->getZoneName(), core3Room);
		core3Room->addSubRoom(planetRoom);

		ChatRoom* planetaryChat = createRoom("chat", planetRoom);
		planetRoom->addSubRoom(planetaryChat);
	}
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

	ChatRoom* newRoom = createRoom(channel, room);
	room->addSubRoom(newRoom);

	return newRoom;
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


void ChatManagerImplementation::destroyRooms() {
	Locker _locker(_this.get());

	HashTableIterator<unsigned int, ManagedReference<ChatRoom* > > iter = roomMap->iterator();

	while (iter.hasNext()) {
		ChatRoom* room = iter.next();
		room->finalize();
	}

	roomMap->removeAll();

	gameRooms.removeAll();
}

void ChatManagerImplementation::populateRoomListMessage(ChatRoom* channel, ChatRoomList* msg) {
	if (channel->isPublic())
		msg->addChannel(channel);

	for (int i = 0; i < channel->getSubRoomsSize(); i++) {
		ChatRoom* chan = channel->getSubRoom(i);

		populateRoomListMessage(chan, msg);
	}
}

void ChatManagerImplementation::handleChatRoomMessage(CreatureObject* sender, const UnicodeString& message, unsigned int roomID, unsigned int counter) {
	/*if (sender->isChatMuted() && !sender->isPrivileged()) {
		sender->sendSystemMessage("Your chat abilities are currently disabled by the server administrators.");
		return;
	}*/

	String name = sender->getFirstName();

	ChatRoom* channel = getChatRoom(roomID);

	if (channel == NULL)
		return;

	if (!channel->hasPlayer(sender))
		return;

	BaseMessage* msg = new ChatRoomMessage(name, message, roomID);
	channel->broadcastMessage(msg);

	BaseMessage* amsg = new ChatOnSendRoomMessage(counter);
	channel->broadcastMessage(amsg);

	/*Vector<Message*> messages;
	messages.add(msg);
	messages.add(amsg);

	channel->broadcastMessage(messages);*/
}

void ChatManagerImplementation::handleChatEnterRoomById(CreatureObject* player, uint32 counter, uint32 roomID) {
	ManagedReference<ChatRoom*> room = getChatRoom(roomID);

	if (room == NULL)
		return;

	room->addPlayer(player);
}

void ChatManagerImplementation::handleSocialInternalMessage(CreatureObject* sender, const UnicodeString& arguments) {
	Zone* zone = sender->getZone();

	if (zone == NULL)
		return;

	StringTokenizer tokenizer(arguments.toString());
	uint64 targetid;
	uint32 emoteid, unkint, unkint2;

	try {
		targetid = tokenizer.getLongToken();
		emoteid = tokenizer.getIntToken();
		unkint = tokenizer.getIntToken();
		unkint2 = tokenizer.getIntToken();
	} catch (const Exception& e) {
		return;
	}

	//bool readlock = !zone->isLockedByCurrentThread();

	bool showtext = true;

	if (unkint2 == 0)
		showtext = false;

	String firstName;

	if (sender->isPlayerCreature())
		firstName = (cast<CreatureObject*>(sender))->getFirstName().toLowerCase();

	CloseObjectsVector* vec = (CloseObjectsVector*) sender->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeEntryObjects(200, 50);

	if (vec != NULL) {
		vec->safeCopyTo(closeEntryObjects);
	} else {
		zone->getInRangeObjects(sender->getWorldPositionX(), sender->getWorldPositionX(), 192, &closeEntryObjects, true);
	}

	//Vector<QuadTreeEntry*> closeEntryObjects(closeObjects->size(), 50);
	/*
	try {
//		zone->rlock(readlock);

	if (vec != NULL) {
		vec->safeCopyTo(closeEntryObjects);
	} else {
		zone->getInRangeObjects(sender->getWorldPositionX(), sender->getWorldPositionX(), 192, &closeEntryObjects, true);
	}

	//Vector<QuadTreeEntry*> closeEntryObjects(closeObjects->size(), 50);
	/*
	try {
//		zone->rlock(readlock);

		for (int i = 0; i < closeObjects->size(); ++i) {
			closeEntryObjects.add(closeObjects->get(i).get());
		}

//		zone->runlock(readlock);
	} catch (...) {
//		zone->runlock(readlock);
	}

	for (int i = 0; i < closeEntryObjects.size(); ++i) {
		SceneObject* object = cast<SceneObject*>(closeEntryObjects.get(i).get());

	for (int i = 0; i < closeObjects->size(); ++i) {
			closeEntryObjects.add(closeObjects->get(i).get());
		}

//		zone->runlock(readlock);
	} catch (...) {
//		zone->runlock(readlock);
	}
	 */
	for (int i = 0; i < closeEntryObjects.size(); ++i) {
		SceneObject* object = cast<SceneObject*>(closeEntryObjects.get(i).get());

		if (object->isPlayerCreature()) {
			CreatureObject* creature = cast<CreatureObject*>(object);

			PlayerObject* ghost = cast<PlayerObject*>(creature->getSlottedObject("ghost"));

			if (ghost == NULL)
				continue;

			if (!ghost->isIgnoring(firstName) && creature->isInRange(sender, 128)) {
				Emote* emsg = new Emote(creature, sender, targetid,
						emoteid, showtext);
				creature->sendMessage(emsg);

			}
		}
	}

}

void ChatManagerImplementation::sendRoomList(CreatureObject* player) {
	ChatRoomList* crl = new ChatRoomList();

	String game = "SWG";
	populateRoomListMessage(gameRooms.get(game), crl);

	crl->insertChannelListCount();
	player->sendMessage(crl);
}

void ChatManagerImplementation::addPlayer(CreatureObject* player) {
	Locker _locker(_this.get());

	String name = player->getFirstName().toLowerCase();
	playerMap->put(name, player, false);
}

CreatureObject* ChatManagerImplementation::getPlayer(const String& name) {
	Locker _locker(_this.get());

	CreatureObject* player = NULL;

	try {
		String lName = name.toLowerCase();

		player = playerMap->get(lName, false);
	} catch (Exception& e) {
		System::out << e.getMessage();
		e.printStackTrace();
	}

	return player;
}

CreatureObject* ChatManagerImplementation::removePlayer(const String& name) {
	Locker _locker(_this.get());

	String lName = name.toLowerCase();

	CreatureObject* player = playerMap->remove(lName, false);

	return player;
}

void ChatManagerImplementation::broadcastGalaxy(const String& message, const String& faction) {
	Locker locker(_this.get());

	playerMap->resetIterator(false);

	uint32 factionCRC = faction.hashCode();

	while (playerMap->hasNext(false)) {
		ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);

		if (playerObject->getFaction() == factionCRC || playerObject->getPlayerObject()->isPrivileged())
			playerObject->sendSystemMessage(message);
	}
}

void ChatManagerImplementation::broadcastGalaxy(CreatureObject* player, const String& message) {
	String firstName = "SKYNET";

	if (player != NULL)
		firstName = player->getFirstName();

	StringBuffer fullMessage;
	fullMessage << "[" << firstName << "] " << message;

	Locker locker(_this.get());
	//playerMap->lock();

	playerMap->resetIterator(false);

	while (playerMap->hasNext(false)) {
		ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);

		playerObject->sendSystemMessage(fullMessage.toString());
	}
}

void ChatManagerImplementation::broadcastMessage(BaseMessage* message) {
	Locker _lock(_this.get());

	playerMap->resetIterator(false);

	while (playerMap->hasNext(false)) {
		ManagedReference<CreatureObject*> player = playerMap->getNextValue(false);

		if (player == NULL || !player->isOnline())
			continue;

		player->sendMessage(message->clone());
	}

	delete message;
	message = NULL;
}

void ChatManagerImplementation::broadcastMessage(CreatureObject* player, const UnicodeString& message,  uint64 target, uint32 moodid, uint32 mood2) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	int language = 0;

	String firstName;

	if (player->isPlayerCreature() /*|| !((Player *)player)->isChatMuted() */) {
		CreatureObject* playerCreature = cast<CreatureObject*>(player);

		firstName = playerCreature->getFirstName().toLowerCase();
		PlayerObject* myGhost = playerCreature->getPlayerObject();

		if (myGhost == NULL)
			return;

		language = myGhost->getLanguageID();
	}

	StringIdChatParameter* param = NULL;

	if (message[0] == '@' && message.indexOf(":") != -1) {
		param = new StringIdChatParameter(message.toString());
	}

	//Locker zoneLocker(zone);
	//zone->rlock();

	CloseObjectsVector* closeObjects = (CloseObjectsVector*) player->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeEntryObjects(200, 50);

	if (closeObjects != NULL) {
		closeObjects->safeCopyTo(closeEntryObjects);
	} else {
		zone->getInRangeObjects(player->getWorldPositionX(), player->getWorldPositionY(), 192, &closeEntryObjects, true);
	}

	/*
=======
	CloseObjectsVector* closeObjects = (CloseObjectsVector*) player->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeEntryObjects(200, 50);

	if (closeObjects != NULL) {
		closeObjects->safeCopyTo(closeEntryObjects);
	} else {
		zone->getInRangeObjects(player->getWorldPositionX(), player->getWorldPositionY(), 192, &closeEntryObjects, true);
	}

/*
>>>>>>> .merge-right.r5676
	try {
		zone->rlock(readlock);

		for (int i = 0; i < closeObjects->size(); ++i) {
			closeEntryObjects.add(closeObjects->get(i).get());
		}

<<<<<<< .working
		zone->runlock(readlock);
	} catch (...) {
		zone->runlock(readlock);
	}
=======
		zone->runlock(readlock);
	} catch (...) {
		zone->runlock(readlock);
	}

	 */


	try {
		for (int i = 0; i < closeEntryObjects.size(); ++i) {
			SceneObject* object = cast<SceneObject*>(closeEntryObjects.get(i).get());

			if (player->isInRange(object, 128)) {

				//Notify observers that are expecting spatial chat.
				if (object->getObserverCount(ObserverEventType::SPATIALCHATRECEIVED)) {
					ManagedReference<ChatMessage*> chatMessage = new ChatMessage();
					chatMessage->setString(message.toString());

					object->notifyObservers(ObserverEventType::SPATIALCHATRECEIVED, chatMessage);
				}

				if (object->isPlayerCreature()) {
					CreatureObject* creature = cast<CreatureObject*>(object);
					PlayerObject* ghost = creature->getPlayerObject();

					if (ghost == NULL)
						continue;

					if (!ghost->isIgnoring(firstName)) {
						SpatialChat* cmsg = NULL;

						if (param == NULL) {
							cmsg = new SpatialChat(player->getObjectID(), creature->getObjectID(), message, target, moodid, mood2, language);
						} else {
							cmsg = new SpatialChat(player->getObjectID(), creature->getObjectID(), *param, target, moodid, mood2);
						}

						creature->sendMessage(cmsg);
					}
				}
			}
		}

		if (param != NULL) {
			delete param;
			param = NULL;
		}

	} catch (...) {
		//zone->runlock();

		//		zone->runlock(readlock);

		if (param != NULL) {
			delete param;
			param = NULL;
		}

		throw;
	}

	//zone->runlock();

}

void ChatManagerImplementation::handleSpatialChatInternalMessage(CreatureObject* player, const UnicodeString& args) {
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

		ManagedReference<ChatMessage*> cm = new ChatMessage();
		cm->setString(msg.toString());
		player->notifyObservers(ObserverEventType::CHAT, cm, 0);

	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in ChatManagerImplementation::handleMessage " << e.getMessage() << "\n";
		System::out << msg.toString();
		e.printStackTrace();
	}
}

//TODO: Refactor into a sendInstantMessage() method that returns a returnCode.
void ChatManagerImplementation::handleChatInstantMessageToCharacter(ChatInstantMessageToCharacter* message) {
	ManagedReference<CreatureObject*> sender = cast<CreatureObject*>(message->getClient()->getPlayer().get().get());

	if (sender == NULL)
		return;

	uint32 sequence = message->getSequence();

	ManagedReference<CreatureObject*> receiver = getPlayer(message->getName());

	if (receiver == NULL || !receiver->isOnline()) {
		BaseMessage* amsg = new ChatOnSendInstantMessage(sequence, IM_OFFLINE);
		sender->sendMessage(amsg);

		return;
	}

	if (receiver->getPlayerObject()->isIgnoring(sender->getFirstName())) {
		BaseMessage* amsg = new ChatOnSendInstantMessage(sequence, IM_IGNORED);
		sender->sendMessage(amsg);

		return;
	}

	UnicodeString text = message->getMessage();

	if (text.length() > IM_MAXSIZE) {
		BaseMessage* amsg = new ChatOnSendInstantMessage(sequence, IM_TOOLONG);
		sender->sendMessage(amsg);

		return;
	}

	BaseMessage* msg = new ChatInstantMessageToClient("SWG", sender->getZoneServer()->getGalaxyName(), sender->getFirstName(), text);
	receiver->sendMessage(msg);

	BaseMessage* amsg = new ChatOnSendInstantMessage(message->getSequence(), IM_SUCCESS);
	sender->sendMessage(amsg);
}

ChatRoom* ChatManagerImplementation::createGroupRoom(uint64 groupID, CreatureObject* creator) {
	// Pre: creator locked;
	// Post: creator locked.

	ManagedReference<ChatRoom*> groupChatRoom;

	StringBuffer name;
	name << groupID;

	ChatRoom* newGroupRoom = createRoom(name.toString(), groupRoom);
	newGroupRoom->setPrivate();
	groupRoom->addSubRoom(newGroupRoom);

	groupChatRoom = createRoom("GroupChat", newGroupRoom);

	groupChatRoom->setTitle(name.toString());
	groupChatRoom->setPrivate();

	groupChatRoom->sendTo(creator);
	groupChatRoom->addPlayer(creator, false);

	newGroupRoom->addSubRoom(groupChatRoom);

	return groupChatRoom;
}

void ChatManagerImplementation::destroyRoom(ChatRoom* room) {
	Locker _locker(_this.get());

	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getGalaxyName(), room->getRoomID());
	room->broadcastMessage(msg);
	room->removeAllPlayers();

	ManagedReference<ChatRoom*> parent = room->getParent();

	if (parent != NULL)
		parent->removeSubRoom(room);

	roomMap->remove(room->getRoomID());
}


void ChatManagerImplementation::handleGroupChat(CreatureObject* sender, const UnicodeString& message) {
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
		group->unlock();

		throw;
	}

	sender->wlock();
}

void ChatManagerImplementation::handleGuildChat(CreatureObject* sender, const UnicodeString& message) {
	/*if (sender->isChatMuted()) {
		sender->sendSystemMessage("Your chat abilities are currently disabled by the server administrators.");
		return;
	}*/

	String name = sender->getFirstName();

	ManagedReference<GuildObject*> guild = sender->getGuildObject();
	if (guild == NULL)
		return;

	sender->unlock();

	try {
		guild->wlock();

		ManagedReference<ChatRoom*> room = guild->getChatRoom();

		if (room != NULL) {
			BaseMessage* msg = new ChatRoomMessage(name, message, room->getRoomID());
			room->broadcastMessage(msg);
		}

		guild->unlock();
	} catch (...) {
		guild->unlock();

		throw;
	}

	sender->wlock();
}

void ChatManagerImplementation::sendMail(const String& sendername, const UnicodeString& header, const UnicodeString& body, const String& name) {
	uint64 receiverObjectID = playerManager->getObjectID(name);

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;

	if (receiverObjectID == 0) {
		error("unexistent name for persistent message");
		return;
	}

	ManagedReference<SceneObject*> receiver = server->getObject(receiverObjectID);

	if (receiver == NULL) {
		error("NULL receiver in send mail");

		return;
	}

	if (!receiver->isPlayerCreature()) {
		error("not player in send mail");

		return;
	}

	CreatureObject* player = cast<CreatureObject*>(receiver.get());
	PlayerObject* ghost = player->getPlayerObject();

	/*StringIdChatParameter test("base_player", "sale_fee");
	test.setDI(100);
	test.setUnknownByte(1);*/

	ManagedReference<PersistentMessage*> mail = new PersistentMessage();
	mail->setSenderName(sendername);
	mail->setSubject(header);
	mail->setBody(body);
	//mail->setParameterizedBody(test);
	mail->setReceiverObjectID(receiverObjectID);
	mail->setTimeStamp(currentTime);

	ObjectManager::instance()->persistObject(mail, 1, "mail");

	Locker _locker(player);

	ghost->addPersistentMessage(mail->getObjectID());

	if (player->isOnline())
		mail->sendTo(player, false);
}

int ChatManagerImplementation::sendMail(const String& sendername, const UnicodeString& subject, const UnicodeString& body, const String& recipientName, StringIdChatParameterVector* stringIdParameters, WaypointChatParameterVector* waypointParameters) {
	uint64 receiverObjectID = playerManager->getObjectID(recipientName);

	ManagedReference<SceneObject*> obj = server->getObject(receiverObjectID);

	if (obj == NULL || !obj->isPlayerCreature())
		return IM_OFFLINE;

	if (body.length() > PM_MAXSIZE)
		return IM_TOOLONG;

	CreatureObject* receiver = cast<CreatureObject*>(obj.get());

	if (receiver->getPlayerObject()->isIgnoring(sendername))
		return IM_IGNORED;

	ManagedReference<PersistentMessage*> mail = new PersistentMessage();
	mail->setSenderName(sendername);
	mail->setSubject(subject);
	mail->setBody(body);

	for (int i = 0; i < stringIdParameters->size(); ++i) {
		StringIdChatParameter* param = &stringIdParameters->get(i);

		if (param == NULL)
			continue;

		mail->addStringIdParameter(*param);
	}

	for (int i = 0; i < waypointParameters->size(); ++i) {
		WaypointChatParameter* param = &waypointParameters->get(i);

		if (param == NULL)
			continue;

		mail->addWaypointParameter(*param);
	}

	mail->setReceiverObjectID(receiverObjectID);

	ObjectManager::instance()->persistObject(mail, 1, "mail");

	Locker _locker(receiver);

	PlayerObject* ghost = receiver->getPlayerObject();

	ghost->addPersistentMessage(mail->getObjectID());

	if (receiver->isOnline())
		mail->sendTo(receiver, false);

	return IM_SUCCESS;
}

int ChatManagerImplementation::sendMail(const String& sendername, const UnicodeString& subject, StringIdChatParameter& body, const String& recipientName, WaypointObject* waypoint) {
	uint64 receiverObjectID = playerManager->getObjectID(recipientName);

	ManagedReference<SceneObject*> obj = server->getObject(receiverObjectID);

	if (obj == NULL || !obj->isPlayerCreature())
		return IM_OFFLINE;

	CreatureObject* receiver = cast<CreatureObject*>(obj.get());

	if (receiver->getPlayerObject()->isIgnoring(sendername))
		return IM_IGNORED;

	ManagedReference<PersistentMessage*> mail = new PersistentMessage();
	mail->setSenderName(sendername);
	mail->setSubject(subject);
	mail->addStringIdParameter(body);

	if (waypoint != NULL) {
		WaypointChatParameter waypointParam(waypoint);
		mail->addWaypointParameter(waypointParam);
	}
	mail->setReceiverObjectID(receiverObjectID);

	ObjectManager::instance()->persistObject(mail, 1, "mail");

	Locker _locker(receiver);

	PlayerObject* ghost = receiver->getPlayerObject();

	ghost->addPersistentMessage(mail->getObjectID());

	if (receiver->isOnline())
		mail->sendTo(receiver, false);

	return IM_SUCCESS;
}

void ChatManagerImplementation::loadMail(CreatureObject* player) {
	Locker _locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	SortedVector<uint64>* messages = ghost->getPersistentMessages();

	for (int i = 0; i < messages->size(); ++i) {
		uint64 messageObjectID = messages->get(i);

		ManagedReference<PersistentMessage*> mail = cast<PersistentMessage*>(Core::getObjectBroker()->lookUp(messageObjectID));

		if (mail == NULL) {
			messages->drop(messageObjectID);
			continue;
		}

		mail->sendTo(player, false);
	}
}

void ChatManagerImplementation::handleRequestPersistentMsg(CreatureObject* player, uint32 mailID) {
	Locker _locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	SortedVector<uint64>* messages = ghost->getPersistentMessages();

	uint64 messageObjectID = -1;

	for (int i = 0; i < messages->size(); ++i) {
		messageObjectID = messages->get(i);

		if (Long::hashCode(messageObjectID) == mailID)
			break;
	}

	if (messageObjectID == -1) {
		error("could not find mail in handleRequestPersistentMsg");
		return;
	}

	ManagedReference<PersistentMessage*> mail = cast<PersistentMessage*>(Core::getObjectBroker()->lookUp(messageObjectID));

	if (mail == NULL) {
		messages->drop(messageObjectID);
		return;
	}

	_locker.release();

	mail->setStatus('R');
	mail->sendTo(player, true);
}

void ChatManagerImplementation::deletePersistentMessage(CreatureObject* player, uint32 mailID) {
	Locker _locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	SortedVector<uint64>* messages = ghost->getPersistentMessages();

	uint64 messageObjectID = -1;

	for (int i = 0; i < messages->size(); ++i) {
		messageObjectID = messages->get(i);

		if (Long::hashCode(messageObjectID) == mailID)
			break;
	}

	if (messageObjectID == -1) {
		error("could not find mail in deletePersistentMessage");
		return;
	}

	messages->drop(messageObjectID);

	_locker.release();

	ObjectManager::instance()->destroyObjectFromDatabase(messageObjectID);
}
