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

ChatManagerImplementation::ChatManagerImplementation(ZoneServer* serv, int initsize) : ChatManagerServant(), Mutex("ChatManager") {
	server = serv;
		
	userManager = server->getUserManager();

	playerManager = serv->getPlayerManager();
	guildManager = playerManager->getGuildManager();
	
	resourceManager = server->getResourceManager();
	//playerMap = new PlayerMap(initsize);
	
	playerMap = new PlayerMap(initsize);
	playerMap->deploy("ChatPlayerMap");

	roomMap = new ChatRoomMap(10000);
				
	mute = false;
	
	roomID = 0;
	
	initiateRooms();
}

ChatManagerImplementation::~ChatManagerImplementation() {
	destroyRooms();
	
	playerMap->finalize();
	
	delete roomMap;
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
				if(!userManager->isAdmin(player->getFirstName())) {
					((CreatureObject*) player)->sendSystemMessage("Chat has been muted by the admins");
				} else {
					unicode mess = msg;
					broadcastMessage(player, mess, targetid, moodid, mood2);
				}
			} else {
				unicode mess = msg;
				broadcastMessage(player, mess, targetid, moodid, mood2);
			}
		}
	} catch (PacketIndexOutOfBoundsException& e) {
		cout << e.getMessage() << "\n" << pack->toString() << "\n";
	} catch (...) {
		cout << "exception while parsing chat\n";
	}

}

void ChatManagerImplementation::handleEmote(Player* player, Message* pack) {
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

	CreatureManager* creatureManager = player->getZone()->getCreatureManager();
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	try {
		if (cmd == "@help") {
			if (userManager->isAdmin(player->getFirstName())) {
				player->sendSystemMessage("Command List: map, warp, printRoomTree, banUser, kill, muteChat, "
						"users, setWeather, ticketPurchase, awardBadge, setGuildID, createGuild"
						"deleteGuildByID, npcc, setAdminLevel, dbStats, dbShowDeleted, dbPurge, getDirection"); 
			}
		} else if (cmd == "@map") {
			if (userManager->isAdmin(player->getFirstName())) {
				if (tokenizer.hasMoreTokens()) {
					int planetid = tokenizer.getIntToken();
					if (planetid >= 0 && planetid < 50)
						player->switchMap(planetid);
				} else {
					player->sendSystemMessage("Useage: map <planetid>\n"
						"0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor,\n"
						"5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin 4");
				}
			}
		} else if (cmd == "@warp") {
			if (userManager->isAdmin(player->getFirstName())) {
				float x = tokenizer.getFloatToken();
				float y = tokenizer.getFloatToken();
				
				uint64 cellID = 0;
				
				if (tokenizer.hasMoreTokens())
					cellID = tokenizer.getLongToken();
			
				if (x >= -8192 && x < 8192 && y >= -8192 && y < 8192) {
					if (cellID == 0)
						player->doWarp(x, y);
					else
						player->doWarp(x, y, -1600.f, 0, cellID);
				}
			}
		} else if (cmd == "@warpTo") {
			if (userManager->isAdmin(player->getFirstName())) {
				string name;
				tokenizer.getStringToken(name);

				Player* target = playerMap->get(name);
				if (target != NULL)
					player->doWarp(target->getPositionX(), target->getPositionY(), 0, 64);
			}
			
		} else if(cmd == "@kick") {
			if (userManager->isAdmin(player->getFirstName())) {
				string name;
				
				try {
					tokenizer.getStringToken(name);
				} catch (...) {
					SceneObject* target = player->getTarget();
					
					if (target != NULL && target->isPlayer())
						name = ((Player*) target)->getFirstName();
				}
				
				if (name != player->getFirstName()) {
					if (server->kickUser(name, player->getFirstName())) {
						player->sendSystemMessage("player \'" + name + "\' has been kicked.");
					} else 
						player->sendSystemMessage("unable to kick player \'" + name + "\'");
				
				} else 
					player->sendSystemMessage("You can't kick yourself. Use /logout please. \n");
			}
 		} /*else if (cmd == "@playAnim") {
			string anim;
			tokenizer.getStringToken(anim);
	                       
			if(anim == "force_lightning" || !anim.find_first_of("test_")) {
				player->sendSystemMessage("Banned animation command.");
			} else {
 	            Zone* zone = player->getZone();
 	           
 	                       
 	            CreatureObject* tar = (CreatureObject*) zone->lookupObject(player->getTargetID());
 	            if (tar != NULL)
					player->doCombatAnimation(tar, String::hashCode(anim), 1);
			}
		}*/ else if (cmd == "@printRoomTree") {
			if (userManager->isAdmin(player->getFirstName())) {
				
				ChatRoom* game = gameRooms.get("SWG");
				
				if (game != NULL) {
					printRoomTree(game);										
				}
			}
		} else if (cmd == "@banUser") {
			if (userManager->isAdmin(player->getFirstName())) {
				string name;

				try {
					tokenizer.getStringToken(name);
				} catch (...) {
					SceneObject* target = player->getTarget();
					
					if (target != NULL && target->isPlayer())
						name = ((Player*) target)->getFirstName();
				}
			
				if (server->banUser(name, player->getFirstName())) {
					player->sendSystemMessage("player \'" + name + "\' is banned");
				} else {
					player->sendSystemMessage("unable to ban player \'" + name + "\'");
				}
			}
		} else if (cmd == "@kill") {
			if (userManager->isAdmin(player->getFirstName())) {
				SceneObject* victim = (CreatureObject*) player->getTarget();
				
				if (victim != NULL) {
					try {
						if (victim != player)
							victim->wlock(player);

						if (victim->isPlayer())
							((Player*) victim)->kill();

						if (victim != player)
							victim->unlock();
					} catch (...) {
						if (victim != player)
							victim->unlock();
					}
				}
			}
		} else if (cmd == "@muteChat") {
			if (userManager->isAdmin(player->getFirstName())) {
				if (mute) {
					mute = false;
					player->sendSystemMessage("Chat has been unmuted.");
				} else {
					mute = true;
					player->sendSystemMessage("Chat has been muted.");
				}
			}
		} else if (cmd == "@users") {
			if (userManager->isAdmin(player->getFirstName())) {
				stringstream msg;
				msg << server->getConnectionCount() << " users connected";
				
				player->sendSystemMessage(msg.str());
			}
		} else if (cmd == "@setWeather") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		int weatherid = tokenizer.getIntToken();
		 
				ServerWeatherMessage* swm = new ServerWeatherMessage(weatherid);
				player->broadcastMessage(swm);
			}
		}/* else if (cmd == "@spawnNpc") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		string npcName;
		 		tokenizer.getStringToken(npcName);
		 		
		 		float x = tokenizer.getFloatToken();
		 		float y = tokenizer.getFloatToken();
		 		
		 		int pvpstatus = tokenizer.getIntToken();
		 		
		 		if (npcName == "krayt")
		 			Creature* creature = creatureManager->spawnCreature("", "a canyon krayt dragon", 0x49D9837F, x, y, pvpstatus);
		 		else if (npcName == "vader")
		 			Creature* creature = creatureManager->spawnCreature("", "Darth Vader", 0x8C70914, x, y, pvpstatus);
		 		else
		 			Creature* creature = creatureManager->spawnCreature("", "snow's mom", 0x22B045DD, x, y, pvpstatus);	
				
			}
		}*/ else if (cmd == "@ticketPurchase") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		string planet;
		 		tokenizer.getStringToken(planet);
		 		string city;
		 		tokenizer.getStringToken(city);

				EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(planet,city);
				player->sendMessage(etpm);
			}
		} else if (cmd == "@awardBadge") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		
		 		int badgeid = tokenizer.getIntToken();
		 		CreatureObject* target = (CreatureObject*) player->getTarget();
 	            if (target != NULL && target->isPlayer()) {
 	            	Player* targetPlayer = (Player*) target;
 	            	
		 			if (targetPlayer->awardBadge(badgeid)) {
		 				player->sendSystemMessage("You have awarded a badge.");
		 				targetPlayer->sendSystemMessage("You have been awarded a badge.");
		 			} else
		 				player->sendSystemMessage("Invalid Badge ID");	
				} else
					player->sendSystemMessage("Invalid target.");	
			}
		} else if (cmd == "@setGuildID") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		/*int guildid = tokenizer.getIntToken();
		 		CreatureObject* target = (CreatureObject*) player->getTarget();
 	           
 	           	if (target == NULL) {
 	           		player->sendSystemMessage("No target selected.");	
 	           		return;
 	           	}
 	           	
 	            if (target->isPlayer() || target->isNonPlayerCreature()) {
 	            	Player* targetPlayer = (Player*) target;			
		 			
		 			if (targetPlayer->updateGuild(guildid)) {
		 				player->sendSystemMessage("You have changed your target's guild.");
		 				targetPlayer->sendSystemMessage("Your guild has been changed.");
		 			} else
		 				player->sendSystemMessage("Invalid Guild ID");	
				} else
					player->sendSystemMessage("Invalid target.");	*/
			}
		} else if (cmd == "@createGuild") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		/*string guildtag;
		 		string tmpString;
		 		stringstream guildname;
		 		
		 		tokenizer.getStringToken(guildtag);
		 		
		 		while (tokenizer.hasMoreTokens()) {
		 			tokenizer.getStringToken(tmpString);
		 			
		 			if (tokenizer.hasMoreTokens()) {
		 				guildname << tmpString << " ";
		 			} else {
		 				guildname << tmpString;	
		 			}
		 		}
		 		
		 		player->unlock();
		 		
		 		string gname = guildname.str();
		 		if (guildManager->createGuild(guildtag, gname))
		 			player->sendSystemMessage("Guild created.");
		 		else
		 			player->sendSystemMessage("Error creating guild.");
		 			
		 		player->wlock();*/
			}
		} else if (cmd == "@deleteGuildByID") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		/*int guildid = tokenizer.getIntToken();
				
				if (guildManager->removeGuild(guildid))
					player->sendSystemMessage("Guild deleted.");
				else
					player->sendSystemMessage("Error deleting guild.");	*/
			}
			
		/*} else if (cmd == "@deleteGuildByTag") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		
		 		string guildtag; 
		 		tokenizer.getStringToken(guildtag);
		 		Guild* guild = new Guild();
				
				int guildid = guild->getGuildIdByTag(guildtag);
				
				if (guild->deleteGuild(guildtag)) {
					player->sendSystemMessage("Guild deleted.");
				} else {
					player->sendSystemMessage("Error deleting guild.");
				}
				
				if (guildid <= 0) {
				player->sendSystemMessage("Error updating players.");
				} else {
					guild->removePlayersFromGuild(guildid);
				}
					
				delete guild;
			}*/
		} else if (cmd == "@npcc") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		/*uint64 id = player->getNewItemID();
		 		uint64 cell1 = player->getNewItemID();
		 		uint64 cell2 = player->getNewItemID();
		 		uint64 cell3 = player->getNewItemID();
		 		
		 		//buios
		 		SceneObjectCreateMessage* cr = new SceneObjectCreateMessage(id,0x4BE3D3D2);
		 		player->sendMessage(cr);
		 		
		 		BaseMessage* tano3 = new BuildingObjectMessage3(id);
		 		player->sendMessage(tano3);

		 		BaseMessage* tano6 = new BuildingObjectMessage6(id);
		 		player->sendMessage(tano6);
		 		
		 		//cell 1 		
		 		SceneObjectCreateMessage* cr1 = new SceneObjectCreateMessage(cell1, 0xC5401EE);
		 		player->sendMessage(cr1);
		 		
		 		UpdateContainmentMessage* link1 = new UpdateContainmentMessage(cell1, id, 0xFFFFFFFF);
		 		player->sendMessage(link1);
		 		
		 		CellObjectMessage3* cellMsg3 = new CellObjectMessage3(cell1, 1);
		 		player->sendMessage(cellMsg3);
		 		
		 		CellObjectMessage6* cellMsg6 = new CellObjectMessage6(cell1);
		 		player->sendMessage(cellMsg6);
		 		
		 		UpdateCellPermissionsMessage* perm = new UpdateCellPermissionsMessage(cell1);
		 		player->sendMessage(perm);
		 		
		 		SceneObjectCloseMessage* closeCell1 = new SceneObjectCloseMessage(cell1);
		 		player->sendMessage(closeCell1);
		 		
		 		
		 		//cell 2
		 		cr1 = new SceneObjectCreateMessage(cell2, 0xC5401EE);
		 		player->sendMessage(cr1);

		 		link1 = new UpdateContainmentMessage(cell2, id, 0xFFFFFFFF);
		 		player->sendMessage(link1);

		 		cellMsg3 = new CellObjectMessage3(cell2, 2);
		 		player->sendMessage(cellMsg3);

		 		cellMsg6 = new CellObjectMessage6(cell2);
		 		player->sendMessage(cellMsg6);

		 		perm = new UpdateCellPermissionsMessage(cell2);
		 		player->sendMessage(perm);

		 		closeCell1 = new SceneObjectCloseMessage(cell2);
		 		player->sendMessage(closeCell1);
		 		
		 		//cell 3
		 		cr1 = new SceneObjectCreateMessage(cell3, 0xC5401EE);
		 		player->sendMessage(cr1);

		 		link1 = new UpdateContainmentMessage(cell3, id, 0xFFFFFFFF);
		 		player->sendMessage(link1);

		 		cellMsg3 = new CellObjectMessage3(cell3, 3);
		 		player->sendMessage(cellMsg3);

		 		cellMsg6 = new CellObjectMessage6(cell3);
		 		player->sendMessage(cellMsg6);

		 		perm = new UpdateCellPermissionsMessage(cell3);
		 		player->sendMessage(perm);

		 		closeCell1 = new SceneObjectCloseMessage(cell3);
		 		player->sendMessage(closeCell1);
		 		 		
		 		SceneObjectCloseMessage* cl = new SceneObjectCloseMessage(id);
		 		player->sendMessage(cl);*/
		 	}
		} else if (cmd == "@setAdminLevel") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		int level = tokenizer.getIntToken();
		 		player->setAdminLevel(level);
		 	}	
		} else if (cmd =="@test") {
			/*string vendorinfo = "testvendor";
			string vendorowner = "testnpc";
			
			BaseMessage* packet = new BaseMessage();
			
            packet->insertShort(0x08);
            packet->insertInt(0xFA500E52);  // opcode
		
            packet->insertInt(0); //updateCount from QueryRequest
            packet->insertInt(2); //??
		
		
            packet->insertInt(3); //COUNTER OF ASCII STRINGS
            packet->insertAscii(vendorinfo);
            packet->insertAscii(vendorowner);
            packet->insertShort(0); //??
		
            packet->insertInt(1); //Counter
            unicode testitem = "Test Item";
            packet->insertUnicode(testitem);
		
            
            packet->insertInt(2); // you n00b, there was 1 here for the block size ;}
            
            packet->insertLong(0);
            packet->insertByte(0);
            packet->insertInt(0);
            packet->insertInt(0);
            packet->insertByte(0);
            packet->insertShort(0);
            packet->insertLong(0);
            packet->insertShort(0);
            packet->insertLong(0);
            packet->insertShort(0);
            packet->insertInt(0);
            packet->insertInt(0);
            packet->insertInt(0);
            packet->insertInt(0);
		
            packet->insertLong(0);
            packet->insertByte(0);
            packet->insertInt(0);
            packet->insertInt(0);
            packet->insertByte(0);
            packet->insertShort(0);
            packet->insertLong(0);
            packet->insertShort(0);
            packet->insertLong(0);
            packet->insertShort(0);
            packet->insertInt(0);
            packet->insertInt(0);
            packet->insertInt(0);
            packet->insertInt(0);
            //End of list #2
		
		
            packet->insertShort(0);
            packet->insertByte(0);
		
            //I HAD TO ADD THIS OR ELSE IT CRASHES.
            packet->insertInt(0);
            packet->insertShort(0);
            
            Thread::sleep(5000);
            
            player->sendMessage(packet);*/
		} else if(cmd == "@systemMessage") {
			if (userManager->isAdmin(player->getFirstName())) {
				float range = tokenizer.getFloatToken();

				stringstream message;
				message << "System Message from " << player->getFirstName() << ": ";

				while (tokenizer.hasMoreTokens()) {
					tokenizer.getStringToken(message);
					message << " ";
				}
				
				if (range == 0)
					broadcastMessage(message.str());
				else
					broadcastMessageRange(player, message.str(), range);
			}
		} else if(cmd == "@setForceMax") {
			if (userManager->isAdmin(player->getFirstName())) {
				int fp = tokenizer.getIntToken();
				player->setMaxForcePowerBar(fp);
				stringstream message;
				message << "Set Force Power Max to: " << fp << ".";
				player->sendSystemMessage(message.str());
			}
		} else if(cmd == "@setForce") {
			if (userManager->isAdmin(player->getFirstName())) {
				int fp = tokenizer.getIntToken();
				player->setForcePowerBar(fp);
				stringstream message;
				message << "Set Force Power to: " << fp << ".";
				player->sendSystemMessage(message.str());
			}		
			
		} else if(cmd == "@setDrinkFilling") {
			int fill = tokenizer.getIntToken();
			player->setDrinkFilling(fill);
			stringstream message;
			message << "Set drink filling: " << fill << ".";
			player->sendSystemMessage(message.str());
		} else if(cmd == "@setFoodFilling") {
			int fill = tokenizer.getIntToken();
			player->setFoodFilling(fill);
			stringstream message;
			message << "Set food filling: " << fill << ".";
			player->sendSystemMessage(message.str());
		} else if(cmd == "@getDrinkFilling") {
			if (userManager->isAdmin(player->getFirstName())) {
				int fill = player->getDrinkFilling();
				stringstream message;
				message << "Drink filling: " << fill << ".";
				player->sendSystemMessage(message.str());
			}
		} else if(cmd == "@getFoodFilling") {
			if (userManager->isAdmin(player->getFirstName())) {
				int fill = player->getFoodFilling();
				stringstream message;
				message << "Food filling: " << fill << ".";
				player->sendSystemMessage(message.str());
			}
		} else if(cmd == "@HAMStats") {
			if (userManager->isAdmin(player->getFirstName())) {
				stringstream message;
				
				message << "Health:  " << player->getHealth() << "/" << player->getHealthMax() << "/" << player->getBaseHealth() << ".";
				message << " Action:  " << player->getAction() << "/" << player->getActionMax() << "/" << player->getBaseAction() << ".";
				message << " Mind:  " << player->getMind() << "/" << player->getMindMax() << "/" << player->getBaseMind() << ".";
				
				message << " Strength:  " << player->getStrength() << "/" << player->getStrengthMax() << "/" << player->getBaseStrength() << ".";
				message << " Constitution:  " << player->getConstitution() << "/" << player->getConstitutionMax() << "/" << player->getBaseConstitution() << ".";
				
				message << " Quickness:  " << player->getQuickness() << "/" << player->getQuicknessMax() << "/" << player->getBaseQuickness() << ".";
				message << " Stamina:  " << player->getStamina() << "/" << player->getStaminaMax() << "/" << player->getBaseStamina() << ".";
				
				message << " Focus:  " << player->getFocus() << "/" << player->getFocusMax() << "/" << player->getBaseFocus() << ".";
				message << " Willpower:  " << player->getWillpower() << "/" << player->getWillpowerMax() << "/" << player->getBaseWillpower() << ".";
				
				player->sendSystemMessage(message.str());
			}		
		} else if (cmd == "@buff") {
			if (player->getHealthMax() == player->getBaseHealth()) {

				int buffValue = 3000;
				//float buffDuration = 10.0f; // Testing purposes
				float buffDuration = 10800.0f;

				Buff *buff; //pointer for each buff
				BuffObject *bo; //distributed object that contains the payload
				
				// Health
				buff = new Buff(BuffCRC::MEDICAL_ENHANCE_HEALTH, BuffType::MEDICAL, buffDuration);
				buff->setHealthBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);

				// Strength
				buff = new Buff(BuffCRC::MEDICAL_ENHANCE_STRENGTH, BuffType::MEDICAL, buffDuration);
				buff->setStrengthBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);

				// Constitution
				buff = new Buff(BuffCRC::MEDICAL_ENHANCE_CONSTITUTION, BuffType::MEDICAL, buffDuration);
				buff->setConstitutionBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);

				// Action
				buff = new Buff(BuffCRC::MEDICAL_ENHANCE_ACTION, BuffType::MEDICAL, buffDuration);
				buff->setActionBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);

				// Quickness
				buff = new Buff(BuffCRC::MEDICAL_ENHANCE_QUICKNESS, BuffType::MEDICAL, buffDuration);
				buff->setQuicknessBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);
				
				// Stamina
				buff = new Buff(BuffCRC::MEDICAL_ENHANCE_STAMINA, BuffType::MEDICAL, buffDuration);
				buff->setStaminaBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);
				
				// Mind
				buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_DANCE_MIND, BuffType::PERFORMANCE, buffDuration);
				buff->setMindBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);
				
				buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_MUSIC_FOCUS, BuffType::PERFORMANCE, buffDuration);
				buff->setFocusBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);
				
				buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_MUSIC_WILLPOWER, BuffType::PERFORMANCE, buffDuration);
				buff->setWillpowerBuff(buffValue);
				bo = new BuffObject(buff);
				player->applyBuff(bo);

				player->sendSystemMessage("Buffs applied");
				

			} else {
				player->sendSystemMessage("Already buffed");
			}
/*		} else if (cmd == "@buffcrc") {
			
			
			if (tokenizer.hasMoreTokens()) {
				string buff;
				tokenizer.getStringToken(buff);
				player->addBuff(String::hashCode(buff), 300);
				
			} else {
				player->sendSystemMessage("Useage: buffcrc int");
			}*/
		} else if (cmd == "@spice") {
			if(player->hasSpice())
			{
				player->sendSystemMessage("You already have spice.");
			} else if (tokenizer.hasMoreTokens()) {
				string name;
				tokenizer.getStringToken(name);
				
				stringstream spice_up;
				spice_up << "spice." << name << ".up";

				stringstream spice_down;
				spice_down << "spice." << name << ".down";
				
				Buff *buff = NULL;
				BuffObject *bo = NULL;
				
				switch(String::hashCode(spice_up.str())) {
				
				
				//spice.booster_blue.up	
				case 0x18A5AEFB:
					buff = new Buff(BuffCRC::SPICE_BOOSTER_BLUE_UP, BuffType::SPICE, 600.0f);
					buff->setActionBuff(400);
					buff->setQuicknessBuff(400);
					buff->setBuffDownerCRC(BuffCRC::SPICE_BOOSTER_BLUE_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
					
				//spice.crash_n_burn.up	
				case 0x5E1BE4D6:
					buff = new Buff(BuffCRC::SPICE_CRASH_N_BURN_UP, BuffType::SPICE, 600.0f);
					buff->setActionBuff(-200);
					buff->setQuicknessBuff(-200);
					buff->setMindBuff(400);
					buff->setFocusBuff(200);
					buff->setBuffDownerCRC(BuffCRC::SPICE_CRASH_N_BURN_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.droid_lube.up	
				case 0x0C969AE9:
					buff = new Buff(BuffCRC::SPICE_DROID_LUBE_UP, BuffType::SPICE, 600.0f);
					buff->setHealthBuff(250);
					buff->setStrengthBuff(250);
					buff->setConstitutionBuff(250);
					buff->setBuffDownerCRC(BuffCRC::SPICE_DROID_LUBE_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.giggledust.up	
				case 0x3E41BA17:
					buff = new Buff(BuffCRC::SPICE_GIGGLEDUST_UP, BuffType::SPICE, 600.0f);
					buff->setActionBuff(300);
					buff->setQuicknessBuff(300);
					buff->setFocusBuff(-100);
					buff->setBuffDownerCRC(BuffCRC::SPICE_GIGGLEDUST_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.grey_gabaki.up	
				case 0xE5C9CD20:
					buff = new Buff(BuffCRC::SPICE_GREY_GABAKI_UP, BuffType::SPICE, 500.0f);
					buff->setFocusBuff(500);
					buff->setBuffDownerCRC(BuffCRC::SPICE_GREY_GABAKI_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.gunjack.up	
				case 0x09B6F8FC:
					buff = new Buff(BuffCRC::SPICE_GUNJACK_UP, BuffType::SPICE, 600.0f);
					buff->setStrengthBuff(500);
					buff->setQuicknessBuff(-200);
					buff->setFocusBuff(-100);
					buff->setBuffDownerCRC(BuffCRC::SPICE_GUNJACK_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.muon_gold.up	
				case 0xFBE87E37:
					buff = new Buff(BuffCRC::SPICE_MUON_GOLD_UP, BuffType::SPICE, 600.0f);
					buff->setMindBuff(500);
					buff->setFocusBuff(500);
					buff->setWillpowerBuff(500);
					buff->setBuffDownerCRC(BuffCRC::SPICE_MUON_GOLD_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.neutron_pixey.up	
				case 0x5DC6921F:
					buff = new Buff(BuffCRC::SPICE_NEUTRON_PIXEY_UP, BuffType::SPICE, 800.0f);
					buff->setHealthBuff(1000);
					buff->setStrengthBuff(200);
					buff->setConstitutionBuff(200);
					buff->setActionBuff(500);
					buff->setQuicknessBuff(50);
					buff->setStaminaBuff(50);
					buff->setBuffDownerCRC(BuffCRC::SPICE_NEUTRON_PIXEY_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.pyrepenol.up	
				case 0x1EBC62E5:
					buff = new Buff(BuffCRC::SPICE_PYREPENOL_UP, BuffType::SPICE, 600.0f);
					buff->setStrengthBuff(300);
					buff->setQuicknessBuff(-100);
					buff->setFocusBuff(-50);
					buff->setBuffDownerCRC(BuffCRC::SPICE_PYREPENOL_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.scramjet.up	
				case 0x2E03F676:
					buff = new Buff(BuffCRC::SPICE_SCRAMJET_UP, BuffType::SPICE, 700.0f);
					buff->setStrengthBuff(300);
					buff->setBuffDownerCRC(BuffCRC::SPICE_SCRAMJET_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.sedative_h4b.up	
				case 0xD7A72ACF:
					buff = new Buff(BuffCRC::SPICE_SEDATIVE_H4B_UP, BuffType::SPICE, 600.0f);
					buff->setHealthBuff(400);
					buff->setConstitutionBuff(300);
					buff->setMindBuff(-100);
					buff->setFocusBuff(-100);
					buff->setBuffDownerCRC(BuffCRC::SPICE_SEDATIVE_H4B_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.shadowpaw.up	
				case 0x3AAD2B89:
					buff = new Buff(BuffCRC::SPICE_SHADOWPAW_UP, BuffType::SPICE, 600.0f);
					buff->setStrengthBuff(-100);
					buff->setActionBuff(250);
					buff->setQuicknessBuff(250);
					buff->setBuffDownerCRC(BuffCRC::SPICE_SHADOWPAW_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.sweetblossom.up	
				case 0x7EC00CB8:
					buff = new Buff(BuffCRC::SPICE_SWEETBLOSSOM_UP, BuffType::SPICE, 600.0f);
					buff->setActionBuff(400);
					buff->setQuicknessBuff(400);
					buff->setBuffDownerCRC(BuffCRC::SPICE_SWEETBLOSSOM_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.thruster_head.up	
				case 0x530E31B7:
					buff = new Buff(BuffCRC::SPICE_THRUSTER_HEAD_UP, BuffType::SPICE, 600.0f);
					buff->setHealthBuff(100);
					buff->setConstitutionBuff(600);
					buff->setActionBuff(-100);
					buff->setQuicknessBuff(-100);
					buff->setFocusBuff(-200);
					buff->setBuffDownerCRC(BuffCRC::SPICE_THRUSTER_HEAD_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.yarrock.up	
				case 0xE7F8C957:
					buff = new Buff(BuffCRC::SPICE_YARROCK_UP, BuffType::SPICE, 600.0f);
					buff->setMindBuff(200);
					buff->setFocusBuff(100);
					buff->setWillpowerBuff(100);
					buff->setBuffDownerCRC(BuffCRC::SPICE_YARROCK_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.kliknik_boost.up	
				case 0x37173CAD:
					buff = new Buff(BuffCRC::SPICE_KLIKNIK_BOOST_UP, BuffType::SPICE, 240.0f);
					buff->setStrengthBuff(500);
					buff->setActionBuff(100);
					buff->setQuicknessBuff(700);
					buff->setStaminaBuff(100);
					buff->setFocusBuff(500);
					buff->setBuffDownerCRC(BuffCRC::SPICE_KLIKNIK_BOOST_DOWN);
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				//spice.kwi_boost.up	
				case 0x629FA918:
					buff = new Buff(BuffCRC::SPICE_KWI_BOOST_UP, BuffType::SPICE, 60.0f);
					buff->setHealthBuff(100);
					buff->setConstitutionBuff(900);
					buff->setActionBuff(100);
					buff->setStaminaBuff(900);
					buff->setMindBuff(100);
					buff->setFocusBuff(900);
					buff->setBuffDownerCRC(BuffCRC::SPICE_KWO_BOOST_DOWN); // stupid typo in IIFs
					bo = new BuffObject(buff);
					player->applyBuff(bo);
					break;
				
				default:
					player->sendSystemMessage("Useage: @spice [spice_name] (available: booster_blue | crash_n_burn | droid_lube | giggledust | grey_gabaki | gunjack | muon_gold | neutron_pixey | pyrepenol | scramjet | sedative_h4b | shadowpaw | sweetblossom | thruster_head | yarrock | kliknik_boost | kwi_boost)");
				}
			} else {
				player->sendSystemMessage("Useage: @spice [spice_name] (available: booster_blue | crash_n_burn | droid_lube | giggledust | grey_gabaki | gunjack | muon_gold | neutron_pixey | pyrepenol | scramjet | sedative_h4b | shadowpaw | sweetblossom | thruster_head | yarrock | kliknik_boost | kwi_boost)");
			}
		} else if (cmd == "@dbStats") {
			if (userManager->isAdmin(player->getFirstName())) {
				itemManager->showDbStats(player);
				}
		} else if (cmd == "@dbShowDeleted") {
			if (userManager->isAdmin(player->getFirstName())) {
				itemManager->showDbDeleted(player);
			}	
		} else if (cmd == "@dbPurge") {
			if (userManager->isAdmin(player->getFirstName())) {
				itemManager->purgeDbDeleted(player);
			}	
		} else if (cmd == "@giveItemTemp") {
			//Give TANO
			string itemType;
			tokenizer.getStringToken(itemType);
			
			if (userManager->isAdmin(player->getFirstName()) && itemType == "Holocron") {
				Holocron* item = new Holocron(player, 0x9BA06548, unicode("Holocron"), "object/tangible/jedi/shared_jedi_holocron_light.iff");
				player->addInventoryItem(item);

				item->sendTo(player);
			} else if (userManager->isAdmin(player->getFirstName())&& itemType == "Firework") {
				Firework* item = new Firework(player, 0x7C540DEB, unicode("a Firework"), "object/tangible/firework/shared_firework_s04.iff");
				player->addInventoryItem(item);
				
				item->sendTo(player);
			} else if (userManager->isAdmin(player->getFirstName())&& itemType == "AA") {
				Attachment* item = new Attachment(player->getNewItemID(), AttachmentImplementation::ARMOR);
				item->setSkillMods(System::random(500));
				
				player->addInventoryItem(item);
				
				item->sendTo(player);
			} else if (userManager->isAdmin(player->getFirstName())&& itemType == "Powerup") {
				Powerup* item = new Powerup(player->getNewItemID());
				item->setPowerupStats(System::random(500));
				
				player->addInventoryItem(item);
				
				item->sendTo(player);
			} else if (itemType == "SurveyTools") {
				SurveyTool* minSurv = new SurveyTool(player, 0xAA9AB32C, unicode("Mineral Survey Tool"), "survey_tool_mineral");
				player->addInventoryItem(minSurv);
				minSurv->sendTo(player);
			 	
			 	SurveyTool* solSurv = new SurveyTool(player, 0x8B95C48D, unicode("Solar Survey Tool"), "survey_tool_solar");
			 	player->addInventoryItem(solSurv);
			 	solSurv->sendTo(player);
			 	
			 	SurveyTool* chemSurv = new SurveyTool(player, 0x85A7C02A, unicode("Chemical Survey Tool"), "survey_tool_chemical");
			 	player->addInventoryItem(chemSurv);
			 	chemSurv->sendTo(player);
			 	
			 	SurveyTool* floSurv = new SurveyTool(player, 0x4F38AD50, unicode("Flora Survey Tool"), "survey_tool_flora");
			 	player->addInventoryItem(floSurv);
			 	floSurv->sendTo(player);
			 	
			 	SurveyTool* gasSurv = new SurveyTool(player, 0x3F1F6443, unicode("Gas Survey Tool"), "survey_tool_gas");
			 	player->addInventoryItem(gasSurv);
			 	gasSurv->sendTo(player);
			 	
			 	SurveyTool* watSurv = new SurveyTool(player, 0x81AE2438, unicode("Water Survey Tool"), "survey_tool_water");
			 	player->addInventoryItem(watSurv);
			 	watSurv->sendTo(player);
			 	
			 	SurveyTool* windSurv = new SurveyTool(player, 0x21C39BD0, unicode("Wind Survey Tool"), "survey_tool_wind");
			 	player->addInventoryItem(windSurv);
			 	windSurv->sendTo(player);
			} else {
				player->sendSystemMessage("Unknown Item Type.");
			}
		} else if (cmd == "@getDirection") {
			SceneObject* target = player->getTarget();
			
			if(target == NULL)
				target = player;
			
			stringstream ss;
			ss << "oX: " << target->getDirectionX() << endl << "oZ: " << target->getDirectionZ() << endl;
			ss << "oY: " << target->getDirectionY() << endl << "oW: " << target->getDirectionW();
			player->sendSystemMessage(ss.str());
		} else {
			player->sendSystemMessage("Unknown Command: " + cmd);
		}
	} catch (Exception& e) {
		//cout << "not enough parameter for command \'" << cmd << "\'\n"; 
	}
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



