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

ChatManagerImplementation::ChatManagerImplementation(ZoneServer* serv, int initsize) : ChatManagerServant(), Mutex("ChatManager") {
	server = serv;
		
	userManager = server->getUserManager();

	playerManager = serv->getPlayerManager();
	guildManager = playerManager->getGuildManager();
	
	resourceManager = server->getResourceManager();
	//playerMap = new PlayerMap(initsize);
	
	PlayerMapImplementation* mapImpl = new PlayerMapImplementation(initsize);
	playerMap = (PlayerMap*) mapImpl->deploy("ChatPlayerMap");

	roomMap = new ChatRoomMap(10000);
				
	mute = false;
	
	roomID = 0;
	
	initiateRooms();
}

void ChatManagerImplementation::initiateRooms() {
	gameRooms.setNullValue(NULL);
	
	ChatRoomImplementation* mainRoomImpl = new ChatRoomImplementation(server, "SWG", getNextRoomID());
	ChatRoom* mainRoom = mainRoomImpl->deploy();
	mainRoom->setPrivate();
	addRoom(mainRoom);
	gameRooms.put("SWG", mainRoom);
	
	ChatRoomImplementation* core3Impl = new ChatRoomImplementation(server, mainRoom, server->getServerName(), getNextRoomID());
	ChatRoom* core3 = core3Impl->deploy();
	core3->setPrivate();
	mainRoom->addSubRoom(core3);
	addRoom(core3);
	
	ChatRoomImplementation* groupRoomImpl = new ChatRoomImplementation(server, core3, "group", getNextRoomID());
	groupRoom = groupRoomImpl->deploy();
	groupRoom->setPrivate();
	core3->addSubRoom(groupRoom);
	addRoom(groupRoom);
	
	ChatRoomImplementation* generalRoomImpl = new ChatRoomImplementation(server, core3, "general", getNextRoomID());
	ChatRoom* general = generalRoomImpl->deploy();
	core3->addSubRoom(general);
	addRoom(general);

}

void ChatManagerImplementation::handleTellMessage(Player* sender, Message* pack) {
	string game, galaxy, name;
	unicode message;
	
	uint32 seq = ChatInstantMessageToCharacter::parse(pack, game, galaxy, name, message);

	String::toLower(name);
	Player* receiver = getPlayer(name);

	if (receiver == NULL || !receiver->isOnline() || receiver->isLoggingOut()) {
		Message* amsg = new ChatOnSendInstantMessage(seq, true);
		sender->sendMessage(amsg);

		return;
	}

	Message* msg = new ChatInstantMessageToClient(game, galaxy, sender->getFirstName(), message);
	receiver->sendMessage(msg);
		
	Message* amsg = new ChatOnSendInstantMessage(seq, false);
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
	
	playerMap->resetIterator();
	
	while (playerMap->hasNext()) {
		Player* player = playerMap->getNextValue();
		
		player->sendSystemMessage(message);
	}

	unlock();
}

void ChatManagerImplementation::broadcastMessageRange(Player* player, const string& message, float range) {
	try {
		lock();

		//TODO make it polling the spatial indexer instead of iterating the whole hash table
		playerMap->resetIterator();
	
		while (playerMap->hasNext()) {
			Player* trgplayer = playerMap->getNextValue();
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
						"deleteGuildByID, npcc, setAdminLevel, dbStats, dbShowDeleted, dbPurge"); 
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
			
				if (x >= -8192 && x < 8192 && y >= -8192 && y < 8192)
					player->doWarp(x, y);
			}
		} else if (cmd == "@spawnResource") {
			if (userManager->isAdmin(player->getFirstName())) {
				string resource;
				resourceManager->makeResourceName(resource, true);
				
				player->sendSystemMessage("Resource is \'" + resource + "\'");
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
				tokenizer.getStringToken(name);
			
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
		 		int guildid = tokenizer.getIntToken();
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
					player->sendSystemMessage("Invalid target.");	
			}
		} else if (cmd == "@createGuild") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		string guildtag;
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
		 			
		 		player->wlock();
			}
		} else if (cmd == "@deleteGuildByID") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		int guildid = tokenizer.getIntToken();
				
				if (guildManager->removeGuild(guildid))
					player->sendSystemMessage("Guild deleted.");
				else
					player->sendSystemMessage("Error deleting guild.");	
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
		 		/*SuiCreatePageMessage* sui = new SuiCreatePageMessage();
		 		sui->ticketPurchased();
		 		
		 		player->sendMessage(sui);*/
		 	}
		} else if (cmd == "@setAdminLevel") {
		 	if (userManager->isAdmin(player->getFirstName())) {
		 		int level = tokenizer.getIntToken();
		 		player->setAdminLevel(level);
		 	}	
		} else if (cmd =="@test") {
			string vendorinfo = "testvendor";
			string vendorowner = "testnpc";
			
			Message* packet = new Message();
			
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
            /*packet->insertInt(0);
            packet->insertShort(0);*/
            
            Thread::sleepMili(5000);
            
            player->sendMessage(packet);
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
		} else if (cmd == "@buff") {
			if (player->getHealthMax() == player->getBaseHealth()) {
				int buffValue = 3000;
				float buffDuration = 10800.0f;

				player->applyBuff("health", buffValue, buffDuration);
				player->applyBuff("strength", buffValue, buffDuration);
				player->applyBuff("constitution", buffValue, buffDuration);
				player->applyBuff("action", buffValue, buffDuration);
				player->applyBuff("quickness", buffValue, buffDuration);
				player->applyBuff("stamina", buffValue, buffDuration);
				player->applyBuff("mind", buffValue, buffDuration);
				player->applyBuff("focus", buffValue, buffDuration);
				player->applyBuff("willpower", buffValue, buffDuration);

				player->sendSystemMessage("Buffs applied");
			} else {
				player->sendSystemMessage("Already buffed");
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
		} else if (cmd == "@sliceWeapon") {
			SuiCreatePageMessage* list;
			list = new ListBox(0xBEEFAAAA, "Weapon Upgrade Kit", "Select the item you wish to slice");
			
			int items = player->getInventory()->objectsSize();
			
			for (int i = 0; i < items; i++)
				if (((TangibleObject*)player->getInventory()->getObject(i))->getObjectSubType()==2)
					if (!((Weapon*)player->getInventory()->getObject(i))->isSliced())
						((ListBox*)list)->addItem(((TangibleObject*)player->getInventory()->getObject(i))->getName().c_str());	
			
			((ListBox*)list)->generateMessage();

			player->sendMessage(list);
		}
		/*else if (cmd == "@open") {
					CreatureObject* target = (CreatureObject*)player->getTarget();
					if (target != NULL) {
						Message* packet = new Message();
						packet->insertShort(0x04);
						packet->insertInt(0xDCA57409);
						packet->insertLong(player->getTarget()->getObjectID());
						packet->insertInt(0);
						packet->insertShort(0x00);
						player->sendMessage(packet);
					}
		}*/
		else {
			player->sendSystemMessage("Unknown Command: " + cmd);
		}
	} catch (Exception& e) {
		//cout << "not enough parameter for command \'" << cmd << "\'\n"; 
	}
}

void ChatManagerImplementation::addPlayer(Player* player) {
	lock();

	string& name = player->getFirstName();
	playerMap->put(name, player);
	
	unlock();
}

Player* ChatManagerImplementation::getPlayer(string& name) {
	lock();

	Player* player = playerMap->get(name); 

	unlock();
	return player;
}

Player* ChatManagerImplementation::removePlayer(string& name) {
	lock();
	
	Player* player = playerMap->remove(name); 

	unlock();
	return player;
}

void ChatManagerImplementation::sendMail(const string& sendername, unicode& header, unicode& body, const string& name) {
	Player* receiver = NULL;

  	struct tm * timeinfo;
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
	  	time_t mailtime;
	  	time ( &mailtime );
	  	timeinfo = localtime ( &mailtime );
	  	
	  	string headerString = header.c_str();
	  	MySqlDatabase::escapeString(headerString);
		
	  	string bodyString = body.c_str();
	  	MySqlDatabase::escapeString(bodyString);
	  	
	  	string senderName = sendername;
	  	MySqlDatabase::escapeString(senderName);
	  	
		stringstream inmqry;
	    inmqry << "INSERT INTO `mail` "
	        << "(`sender_name`,`recv_name`,`subject`,`body`,`time`)"
		    << "VALUES ('" << senderName << "','" << Name << "','" << headerString << "','" << bodyString << "','" << asctime(timeinfo)
		    << "');" ;
		
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
		query << "SELECT mail_id FROM mail WHERE time = '" << asctime(timeinfo) << "';";
		
		ResultSet* mail = ServerDatabase::instance()->executeQuery(query);
		
		if (mail->next()) {
			int mailid = mail->getInt(0);
		
			Message* mmsg = new ChatPersistentMessageToClient(sendername, mailid, 0x01, header, body);
			receiver->sendMessage(mmsg);
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
		//receiver->wlock();
	
		stringstream query;
		query << "SELECT * FROM mail WHERE mail_id = '" << mailid << "';";
	
		ResultSet* mail = ServerDatabase::instance()->executeQuery(query);
	
		if (mail->next()) {
			string sender = mail->getString(1);
			unicode subject = mail->getString(3);
			unicode body = mail->getString(4);

			Message* mmsg = new ChatPersistentMessageToClient(sender, mailid, 0, subject, body);
			receiver->sendMessage(mmsg);
		}
	
		//receiver->unlock();
	
		delete mail;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		
		//receiver->unlock();
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
		
			Message* mmsg = new ChatPersistentMessageToClient(sendername, mailid, 0x01, header, body);
			ply->sendMessage(mmsg);
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
	
	Message* msg = new ChatRoomMessage(name, message, channelid);
	channel->broadcastMessage(msg);
	Message* amsg = new ChatOnSendRoomMessage(counter);
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
	
		Message* msg = new ChatRoomMessage(name, message, group->getGroupChannel()->getRoomID());
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
		
	ChatRoomImplementation* newRoomImpl = new ChatRoomImplementation(server, room, channel, getNextRoomID());
	ChatRoom* newRoom = newRoomImpl->deploy();
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
	
	ChatRoomImplementation* groupImpl = new ChatRoomImplementation(server, groupRoom, name.str(), getNextRoomID());
	ChatRoom* group = groupImpl->deploy();
	group->setPrivate();
	groupRoom->addSubRoom(group);
	addRoom(group);
	
	ChatRoomImplementation* groupChatImpl = new ChatRoomImplementation(server, group, "GroupChat", getNextRoomID());
	ChatRoom* groupChat = groupChatImpl->deploy();
	groupChat->setTitle(name.str());
	groupChat->setPrivate();
	groupChat->sendTo(creator);
	groupChat->addPlayer(creator, false);
	group->addSubRoom(groupChat);
	addRoom(groupChat);
	
	return groupChat;
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
	
	delete room;
}

