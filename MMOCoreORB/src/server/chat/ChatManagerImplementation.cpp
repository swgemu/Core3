/*
 * ChatManagerImplementation.cpp
 *
 *  Created on: 28/07/2009
 *      Author: victor
 */

#include "server/chat/ChatManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/player/PlayerMap.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/creature/PetManager.h"
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
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/chat/PersistentMessage.h"
#include "server/chat/ChatMessage.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "server/chat/room/ChatRoom.h"
#include "server/chat/room/ChatRoomMap.h"
#include "server/chat/SendMailTask.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

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

	loadSocialTypes();

	//gameRooms = new VectorMap<String, ManagedReference<ChatRoom*> >();

	//gameCommandHandler = new GameCommandHandler();

	loadSpatialChatTypes();
}

void ChatManagerImplementation::finalize() {
}

void ChatManagerImplementation::loadSpatialChatTypes() {
	TemplateManager* templateManager = TemplateManager::instance();
	IffStream* iffStream = templateManager->openIffFile("chat/spatial_chat_types.iff");

	if (iffStream == NULL) {
		error("Could not open chat/spatial_chat_types.iff");
		return;
	}

	iffStream->openForm('SPCT');

	Chunk* version = iffStream->openForm('0000');

	Chunk* data = iffStream->openChunk('TYPS');
	int i = 0;

	while (data->hasData()) {
		String key;
		data->readString(key);
		i++;

		spatialChatTypes.put(key, i);
	}

	iffStream->closeChunk('TYPS');

	Chunk* version2 = iffStream->openForm('VOLS');

	for (int j = 0; j < version2->getChunksSize(); j++) {
		Chunk* data2 = version2->getNextChunk();

		String name;
		data2->readString(name);

		uint16 distance = 0;

		distance = data2->readShort();

		if (name.isEmpty()) {
			defaultSpatialChatDistance = distance;
		} else {
			uint32 chatType = spatialChatTypes.get(name);

			spatialChatDistances.put(chatType, distance);
		}
	}

	iffStream->closeForm('VOLS');

	iffStream->closeForm('0000');
	iffStream->closeForm('SPCT');

	delete iffStream;
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

	core3Room = createRoom(server->getGalaxyName(), mainRoom);
	core3Room->setPrivate();
	mainRoom->addSubRoom(core3Room);

	groupRoom = createRoom("group", core3Room);
	groupRoom->setPrivate();
	core3Room->addSubRoom(groupRoom);

	guildRoom = createRoom("guild", core3Room);
	guildRoom->setPrivate();
	core3Room->addSubRoom(guildRoom);

	auctionRoom = createRoom("Auction", core3Room);
	core3Room->addSubRoom(auctionRoom);

	generalRoom = createRoom("General", core3Room);
	core3Room->addSubRoom(generalRoom);


}

void ChatManagerImplementation::initiatePlanetRooms() {
	// Planet Chat
	for (int i = 0; i < server->getZoneCount(); ++i) {
		ManagedReference<Zone*> zone = server->getZone(i);

		if (zone == NULL)
			continue;

		Locker locker(zone);

		ChatRoom* planetRoom = createRoom(zone->getZoneName(), core3Room);
		core3Room->addSubRoom(planetRoom);

		ChatRoom* planetaryChat = createRoom("Planet", planetRoom);
		planetRoom->addSubRoom(planetaryChat);
		zone->setChatRoom( planetaryChat );

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
	Locker _locker(_this.getReferenceUnsafeStaticCast());

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
	String name = sender->getFirstName();
	String fullName = "";

	if (sender->isPlayerCreature()) {
		ManagedReference<PlayerObject*> senderGhost = sender->getPlayerObject();

		if (senderGhost == NULL)
			return;

		if (senderGhost->isMuted()) {
			String reason = senderGhost->getMutedReason();

			if (reason != "")
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support for '" + reason + "'.");
			else
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support.");

			return;
		}

		if( senderGhost->isPrivileged() ){
			String tag = PermissionLevelList::instance()->getPermissionTag(sender->getPlayerObject()->getAdminLevel()).toString();
			fullName = name + " [" + tag + "]";
		}
	}

	ChatRoom* channel = getChatRoom(roomID);

	if (channel == NULL)
		return;

	if (!channel->hasPlayer(sender))
		return;

	Zone* zone = sender->getZone();
	if( zone == NULL ){
		return;
	}

	UnicodeString formattedMessage(formatMessage(message));

	ManagedReference<ChatRoom*> planetRoom = zone->getChatRoom();

	BaseMessage* msg = NULL;

	if (fullName == "")
		msg = new ChatRoomMessage(name, formattedMessage, roomID);
	else
		msg = new ChatRoomMessage(fullName, formattedMessage, roomID);

	// Auction Chat, General Chat, and Planet Chat should adhere to player ignore list
	if( auctionRoom != NULL && auctionRoom->getRoomID() == roomID ) {
		channel->broadcastMessageCheckIgnore(msg, name);
	} else if (generalRoom != NULL && generalRoom->getRoomID() == roomID) {
		channel->broadcastMessageCheckIgnore(msg, name);
	} else if( planetRoom != NULL && planetRoom->getRoomID() == roomID ) {
		channel->broadcastMessageCheckIgnore(msg, name);
	} else {
		channel->broadcastMessage(msg);
	}

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
	if (sender->isPlayerCreature()) {
		ManagedReference<PlayerObject*> senderGhost = sender->getPlayerObject();

		if (senderGhost == NULL)
			return;

		if (senderGhost->isMuted()) {
			String reason = senderGhost->getMutedReason();

			if (reason != "")
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support for '" + reason + "'.");
			else
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support.");

			return;
		}
	}

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
		sender->info("Null closeobjects vector in ChatManager::handleSocialInternalMessage", true);
		zone->getInRangeObjects(sender->getWorldPositionX(), sender->getWorldPositionX(), 128, &closeEntryObjects, true);
	}

	float range = defaultSpatialChatDistance;

	for (int i = 0; i < closeEntryObjects.size(); ++i) {
		SceneObject* object = cast<SceneObject*>(closeEntryObjects.get(i).get());

		if (object->isPlayerCreature()) {
			CreatureObject* creature = cast<CreatureObject*>(object);

			Reference<PlayerObject*> ghost = creature->getSlottedObject("ghost").castTo<PlayerObject*>();

			if (ghost == NULL)
				continue;

			if (!ghost->isIgnoring(firstName) && creature->isInRange(sender, range)) {
				Emote* emsg = new Emote(creature, sender, targetid, emoteid, showtext);
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
	Locker _locker(_this.getReferenceUnsafeStaticCast());

	String name = player->getFirstName().toLowerCase();
	playerMap->put(name, player, false);
}

CreatureObject* ChatManagerImplementation::getPlayer(const String& name) {
	Locker _locker(_this.getReferenceUnsafeStaticCast());

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
	Locker _locker(_this.getReferenceUnsafeStaticCast());

	String lName = name.toLowerCase();

	CreatureObject* player = playerMap->remove(lName, false);

	return player;
}

void ChatManagerImplementation::broadcastGalaxy(const String& message, const String& faction) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

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

	Locker locker(_this.getReferenceUnsafeStaticCast());
	//playerMap->lock();

	playerMap->resetIterator(false);

	while (playerMap->hasNext(false)) {
		ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);

		playerObject->sendSystemMessage(fullMessage.toString());
	}
}

void ChatManagerImplementation::broadcastMessage(BaseMessage* message) {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

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
	PlayerObject* myGhost = NULL;
	bool privileged = false;

	if (zone == NULL)
		return;

	int language = 0;
	String firstName;

	if (player->isPlayerCreature() /*|| !((Player *)player)->isChatMuted() */) {
		CreatureObject* playerCreature = cast<CreatureObject*>(player);
		if (playerCreature)
		{
			firstName = playerCreature->getFirstName().toLowerCase();
			myGhost = playerCreature->getPlayerObject();
		}

		if (myGhost)
			language = myGhost->getLanguageID();
	}

	if (myGhost)
	{
		if (myGhost->isPrivileged())
			privileged = true;
	}

	StringIdChatParameter* param = NULL;

	if (message[0] == '@' && message.indexOf(":") != -1) {
		param = new StringIdChatParameter(message.toString());
	}

	CloseObjectsVector* closeObjects = (CloseObjectsVector*) player->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeEntryObjects(200, 50);

	if (closeObjects != NULL) {
		closeObjects->safeCopyTo(closeEntryObjects);
	} else {
		player->info("Null closeobjects vector in ChatManager::broadcastMessage", true);
		zone->getInRangeObjects(player->getWorldPositionX(), player->getWorldPositionY(), 128, &closeEntryObjects, true);
	}

	float range = defaultSpatialChatDistance;

	float specialRange = spatialChatDistances.get(mood2);
	if (specialRange != -1) {
		range = specialRange;
	}

	try {
		for (int i = 0; i < closeEntryObjects.size(); ++i) {
			SceneObject* object = cast<SceneObject*>(closeEntryObjects.get(i).get());

			if (player->isInRange(object, range)) {

				//Notify observers that are expecting spatial chat.
				if (object->getObserverCount(ObserverEventType::SPATIALCHATRECEIVED)) {
					ManagedReference<ChatMessage*> chatMessage = new ChatMessage();
					chatMessage->setString(message.toString());

					EXECUTE_TASK_3(object, chatMessage, player, {
						if (player_p == NULL || object_p == NULL)
							return;

						Locker locker(object_p);

						SortedVector<ManagedReference<Observer*> > observers = object_p->getObservers(ObserverEventType::SPATIALCHATRECEIVED);
						for (int oc = 0; oc < observers.size(); oc++) {
							Observer* observer = observers.get(oc);
							Locker clocker(observer, object_p);
							if (observer->notifyObserverEvent(ObserverEventType::SPATIALCHATRECEIVED, object_p, chatMessage_p, player_p->getObjectID()) == 1)
								object_p->dropObserver(ObserverEventType::SPATIALCHATRECEIVED, observer);
						}
					});
				}

				if (object->isPlayerCreature()) {
					CreatureObject* creature = cast<CreatureObject*>(object);
					PlayerObject* ghost = creature->getPlayerObject();

					if (ghost == NULL)
						continue;

					if (!ghost->isIgnoring(firstName) || privileged) {
						SpatialChat* cmsg = NULL;

						if (param == NULL) {
							cmsg = new SpatialChat(player->getObjectID(), creature->getObjectID(), message, target, moodid, mood2, language);
						} else {
							cmsg = new SpatialChat(player->getObjectID(), creature->getObjectID(), *param, target, moodid, mood2);
						}

						creature->sendMessage(cmsg);
					}
				}
				else if( object->isPet() ){
					AiAgent* pet = cast<AiAgent*>(object);

					if (pet == NULL )
						continue;

					if( pet->isDead() || pet->isIncapacitated() )
						continue;

					PetManager* petManager = server->getPetManager();
					Locker clocker(pet, player);
					petManager->handleChat( player, pet, message.toString() );

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

void ChatManagerImplementation::broadcastMessage(CreatureObject* player, StringIdChatParameter& message,  uint64 target, uint32 moodid, uint32 mood2) {
	Zone* zone = player->getZone();
	PlayerObject* myGhost = NULL;
	bool privileged = false;

	if (zone == NULL)
		return;

	int language = 0;
	String firstName;

	if (player->isPlayerCreature() /*|| !((Player *)player)->isChatMuted() */) {
		CreatureObject* playerCreature = cast<CreatureObject*>(player);

		if (playerCreature)
		{
			firstName = playerCreature->getFirstName().toLowerCase();
			myGhost = playerCreature->getPlayerObject();
		}

		if (myGhost)
		{
			language = myGhost->getLanguageID();

			if (myGhost->isPrivileged())
				privileged = true;
		}
	}

	CloseObjectsVector* closeObjects = (CloseObjectsVector*) player->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeEntryObjects(200, 50);

	if (closeObjects != NULL) {
		closeObjects->safeCopyTo(closeEntryObjects);
	} else {
		player->info("Null closeobjects vector in ChatManager::broadcastMessage(StringId)", true);
		zone->getInRangeObjects(player->getWorldPositionX(), player->getWorldPositionY(), ZoneServer::CLOSEOBJECTRANGE, &closeEntryObjects, true);
	}

	try {
		for (int i = 0; i < closeEntryObjects.size(); ++i) {
			SceneObject* object = cast<SceneObject*>(closeEntryObjects.get(i).get());

			if (player->isInRange(object, 128)) {

				//Notify observers that are expecting spatial chat.
				if (object->getObserverCount(ObserverEventType::SPATIALCHATRECEIVED)) {
					ManagedReference<ChatMessage*> chatMessage = new ChatMessage();
					chatMessage->setString(message.toString());

					object->notifyObservers(ObserverEventType::SPATIALCHATRECEIVED, chatMessage, player->getObjectID());
				}

				if (object->isPlayerCreature()) {
					CreatureObject* creature = cast<CreatureObject*>(object);
					PlayerObject* ghost = creature->getPlayerObject();

					if (ghost == NULL)
						continue;

					if (!ghost->isIgnoring(firstName) || privileged) {
						SpatialChat* cmsg = new SpatialChat(player->getObjectID(), creature->getObjectID(), message, target, moodid, mood2);

						creature->sendMessage(cmsg);
					}
				}
			}
		}
	} catch (...) {
		throw;
	}
}

void ChatManagerImplementation::handleSpatialChatInternalMessage(CreatureObject* player, const UnicodeString& args) {
	if (player->isPlayerCreature()) {
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == NULL)
			return;

		if (ghost->isMuted()) {
			String reason = ghost->getMutedReason();

			if (reason != "")
				player->sendSystemMessage("Your chat abilities are currently disabled by Customer Support for '" + reason + "'.");
			else
				player->sendSystemMessage("Your chat abilities are currently disabled by Customer Support.");

			return;
		}
	}

	try {
		UnicodeTokenizer tokenizer(args);

		uint64 targetid = tokenizer.getLongToken();
		uint32 mood2 = tokenizer.getIntToken();
		uint32 moodid = tokenizer.getIntToken();
		uint32 unk2 = tokenizer.getIntToken();
		uint32 unk3 = tokenizer.getIntToken();

		UnicodeString msg;

		tokenizer.finalToken(msg);

		UnicodeString formattedMessage(formatMessage(msg));
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
		broadcastMessage(player, formattedMessage, targetid, moodid, mood2);

		ManagedReference<ChatMessage*> cm = new ChatMessage();
		cm->setString(formattedMessage.toString());
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
	bool privileged = false;

	if (sender == NULL)
		return;

	if (sender->isPlayerCreature()) {
		ManagedReference<PlayerObject*> senderGhost = NULL;
		senderGhost = sender->getPlayerObject();

		if (senderGhost == NULL)
			return;

		if (senderGhost->isPrivileged())
			privileged = true;

		if (senderGhost->isMuted()) {
			String reason = senderGhost->getMutedReason();

			if (reason != "")
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support for '" + reason + "'.");
			else
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support.");

			return;
		}
	}

	uint32 sequence = message->getSequence();

	// Pull out first name
	String fname = message->getName();
	int spc = fname.indexOf(" ");
	if (spc != -1) {
		fname = fname.subString(0, spc);
	}

	ManagedReference<CreatureObject*> receiver = getPlayer(fname);

	if (receiver == NULL || !receiver->isOnline()) {
		BaseMessage* amsg = new ChatOnSendInstantMessage(sequence, IM_OFFLINE);
		sender->sendMessage(amsg);

		return;
	}

	if (receiver->getPlayerObject()->isIgnoring(sender->getFirstName()) && !privileged) {
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

	text = formatMessage(text);

	String name = sender->getFirstName();
	if( privileged ){
		String tag = PermissionLevelList::instance()->getPermissionTag(sender->getPlayerObject()->getAdminLevel()).toString();
		name = name + " [" + tag + "]";
	}

	BaseMessage* msg = new ChatInstantMessageToClient("SWG", sender->getZoneServer()->getGalaxyName(), name, text);
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
	Locker _locker(_this.getReferenceUnsafeStaticCast());

	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getGalaxyName(), room->getRoomID());
	room->broadcastMessage(msg);
	room->removeAllPlayers();

	ManagedReference<ChatRoom*> parent = room->getParent();

	if (parent != NULL)
		parent->removeSubRoom(room);

	roomMap->remove(room->getRoomID());
}


void ChatManagerImplementation::handleGroupChat(CreatureObject* sender, const UnicodeString& message) {
	String name = sender->getFirstName();

	if (sender->isPlayerCreature()) {
		ManagedReference<PlayerObject*> senderGhost = sender->getPlayerObject();

		if (senderGhost == NULL)
			return;

		if (senderGhost->isMuted()) {
			String reason = senderGhost->getMutedReason();

			if (reason != "")
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support for '" + reason + "'.");
			else
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support.");

			return;
		}

		if( senderGhost->isPrivileged() ){
			String tag = PermissionLevelList::instance()->getPermissionTag(sender->getPlayerObject()->getAdminLevel()).toString();
			name = name + " [" + tag + "]";
		}
	}

	ManagedReference<GroupObject*> group = sender->getGroup();
	if (group == NULL) {
		sender->sendSystemMessage("@combat_effects:not_in_group"); // You must be in a group to perform this command.
		return;
	}

	StringTokenizer args(message.toString());
	if (!args.hasMoreTokens()) {
		sender->sendSystemMessage("@ui:im_no_message"); // You need to include a message!
		return;
	}

	UnicodeString formattedMessage(formatMessage(message));

	sender->unlock();

	try {
		group->wlock();

		ManagedReference<ChatRoom*> room = group->getGroupChannel();

		if (room != NULL) {
			BaseMessage* msg = new ChatRoomMessage(name, formattedMessage, room->getRoomID());
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
	String name = sender->getFirstName();

	if (sender->isPlayerCreature()) {
		ManagedReference<PlayerObject*> senderGhost = sender->getPlayerObject();

		if (senderGhost == NULL)
			return;

		if (senderGhost->isMuted()) {
			String reason = senderGhost->getMutedReason();

			if (reason != "")
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support for '" + reason + "'.");
			else
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support.");

			return;
		}

		if( senderGhost->isPrivileged() ){
			String tag = PermissionLevelList::instance()->getPermissionTag(sender->getPlayerObject()->getAdminLevel()).toString();
			name = name + " [" + tag + "]";
		}
	}

	ManagedReference<GuildObject*> guild = sender->getGuildObject();
	if (guild == NULL) {
		sender->sendSystemMessage("@error_message:not_in_guild"); // You are not in a guild.
		return;
	}

	StringTokenizer args(message.toString());
	if (!args.hasMoreTokens()) {
		sender->sendSystemMessage("@ui:im_no_message"); // You need to include a message!
		return;
	}

	UnicodeString formattedMessage(formatMessage(message));

	ManagedReference<ChatRoom*> room = guild->getChatRoom();
	if (room != NULL) {
		BaseMessage* msg = new ChatRoomMessage(name, formattedMessage, room->getRoomID());
		room->broadcastMessage(msg);
	}

}

void ChatManagerImplementation::handlePlanetChat(CreatureObject* sender, const UnicodeString& message) {
	String name = sender->getFirstName();
	String fullName = "";

	if (sender->isPlayerCreature()) {
		ManagedReference<PlayerObject*> senderGhost = sender->getPlayerObject();

		if (senderGhost == NULL)
			return;

		if (senderGhost->isMuted()) {
			String reason = senderGhost->getMutedReason();

			if (reason != "")
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support for '" + reason + "'.");
			else
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support.");

			return;
		}

		if( senderGhost->isPrivileged() ){
			String tag = PermissionLevelList::instance()->getPermissionTag(sender->getPlayerObject()->getAdminLevel()).toString();
			fullName = name + " [" + tag + "]";
		}
	}

	Zone* zone = sender->getZone();
	if( zone == NULL ){
		return;
	}

	StringTokenizer args(message.toString());
	if (!args.hasMoreTokens()) {
		sender->sendSystemMessage("@ui:im_no_message"); // You need to include a message!
		return;
	}

	UnicodeString formattedMessage(formatMessage(message));

	ManagedReference<ChatRoom*> room = zone->getChatRoom();
	BaseMessage* msg = NULL;

	if (room != NULL) {
		if (fullName == "")
				msg = new ChatRoomMessage(name, formattedMessage, room->getRoomID());
			else
				msg = new ChatRoomMessage(fullName, formattedMessage, room->getRoomID());

		room->broadcastMessageCheckIgnore(msg, name);
	}

}

void ChatManagerImplementation::handleAuctionChat(CreatureObject* sender, const UnicodeString& message) {
	String name = sender->getFirstName();
	String fullName = "";

	if (sender->isPlayerCreature()) {
		ManagedReference<PlayerObject*> senderGhost = sender->getPlayerObject();

		if (senderGhost == NULL)
			return;

		if (senderGhost->isMuted()) {
			String reason = senderGhost->getMutedReason();

			if (reason != "")
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support for '" + reason + "'.");
			else
				sender->sendSystemMessage("Your chat abilities are currently disabled by Customer Support.");

			return;
		}

		if( senderGhost->isPrivileged() ){
			String tag = PermissionLevelList::instance()->getPermissionTag(sender->getPlayerObject()->getAdminLevel()).toString();
			fullName = name + " [" + tag + "]";
		}
	}

	StringTokenizer args(message.toString());
	if (!args.hasMoreTokens()) {
		sender->sendSystemMessage("@ui:im_no_message"); // You need to include a message!
		return;
	}

	UnicodeString formattedMessage(formatMessage(message));

	BaseMessage* msg = NULL;

	if (auctionRoom != NULL) {
		if (fullName == "")
			msg = new ChatRoomMessage(name, formattedMessage, auctionRoom->getRoomID());
		else
			msg = new ChatRoomMessage(fullName, formattedMessage, auctionRoom->getRoomID());

		auctionRoom->broadcastMessageCheckIgnore(msg, name);
	}

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

	/*Locker _locker(player);

	ghost->addPersistentMessage(mail->getObjectID());

	if (player->isOnline())
		mail->sendTo(player, false);*/

	Reference<SendMailTask*> sendMailTask = new SendMailTask(player, mail, sendername);
	sendMailTask->execute();
}

int ChatManagerImplementation::sendMail(const String& sendername, const UnicodeString& subject, const UnicodeString& body, const String& recipientName, StringIdChatParameterVector* stringIdParameters, WaypointChatParameterVector* waypointParameters) {
	uint64 receiverObjectID = playerManager->getObjectID(recipientName);
	ManagedReference<SceneObject*> obj = server->getObject(receiverObjectID);
	ManagedReference<CreatureObject*> sender = NULL;
	bool privileged = false;

	if (obj == NULL || !obj->isPlayerCreature())
		return IM_OFFLINE;

	if (body.length() > PM_MAXSIZE)
		return IM_TOOLONG;

	sender = playerManager->getPlayer(sendername.toLowerCase());

	if (sender)
	{
		if (sender->isPlayerCreature()) {
			ManagedReference<PlayerObject*> senderPlayer = NULL;
			senderPlayer = sender->getPlayerObject();

			if (senderPlayer == NULL)
				return IM_OFFLINE;

			if (senderPlayer->isPrivileged())
				privileged = true;
		}
	}

	CreatureObject* receiver = cast<CreatureObject*>(obj.get());

	if (receiver->getPlayerObject()->isIgnoring(sendername) && !privileged)
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

	/*
	PlayerObject* ghost = receiver->getPlayerObject();

	ghost->addPersistentMessage(mail->getObjectID());

	if (receiver->isOnline())
		mail->sendTo(receiver, false);
	 */

	Reference<SendMailTask*> sendMailTask = new SendMailTask(receiver, mail, sendername);
	sendMailTask->execute();

	return IM_SUCCESS;
}

int ChatManagerImplementation::sendMail(const String& sendername, const UnicodeString& subject, StringIdChatParameter& body, const String& recipientName, WaypointObject* waypoint) {
	uint64 receiverObjectID = playerManager->getObjectID(recipientName);
	ManagedReference<SceneObject*> obj = server->getObject(receiverObjectID);
	ManagedReference<CreatureObject*> sender = NULL;
	bool privileged = false;

	if (obj == NULL || !obj->isPlayerCreature())
		return IM_OFFLINE;

	CreatureObject* receiver = cast<CreatureObject*>(obj.get());
	sender = playerManager->getPlayer(sendername.toLowerCase());

	if (sender)
	{
		if (sender->isPlayerCreature()) {
			ManagedReference<PlayerObject*> senderPlayer = NULL;
			senderPlayer = sender->getPlayerObject();

			if (senderPlayer == NULL)
				return IM_OFFLINE;

			if (senderPlayer->isPrivileged())
				privileged = true;
		}
	}

	PlayerObject* ghost = receiver->getPlayerObject();

	if (ghost == NULL ||
			(ghost->isIgnoring(sendername) && !privileged))
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

	Reference<SendMailTask*> sendMailTask = new SendMailTask(receiver, mail, sendername);
	sendMailTask->execute();
/*
	PlayerObject* ghost = receiver->getPlayerObject();

	ghost->addPersistentMessage(mail->getObjectID());

	if (receiver->isOnline())
		mail->sendTo(receiver, false);

		*/

	return IM_SUCCESS;
}

void ChatManagerImplementation::loadMail(CreatureObject* player) {
	Locker _locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	SortedVector<uint64>* messages = ghost->getPersistentMessages();

	for (int i = 0; i < messages->size(); ++i) {
		uint64 messageObjectID = messages->get(i);

		Reference<PersistentMessage*> mail = Core::getObjectBroker()->lookUp(messageObjectID).castTo<PersistentMessage*>();

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

	Reference<PersistentMessage*> mail = Core::getObjectBroker()->lookUp(messageObjectID).castTo<PersistentMessage*>();

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

UnicodeString ChatManagerImplementation::formatMessage(const UnicodeString& message) {
	UnicodeString text = message;

	while (text.indexOf("\\>") >= 0) {
		int index = text.indexOf("\\>");
		UnicodeString sub = "\\" + text.subString(index, index + 2);
		text = text.replaceFirst(sub,"");
	}

	return text;
}

void ChatManagerImplementation::loadSocialTypes() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/chat/social_types.iff");

	if (iffStream == NULL) {
		error("Could not load social types.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		String key;
		row->getCell(0)->getValue(key);
		socialTypes.put(i + 1, key);
	}

	info("Loaded " + String::valueOf(socialTypes.size()) + " social types.", true);
}
