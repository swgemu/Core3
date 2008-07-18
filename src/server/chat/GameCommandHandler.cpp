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

#include "GameCommandHandler.h"
#include "../zone/objects/building/BuildingObject.h"
#include "../zone/managers/planet/PlanetManager.h"
#include "../zone/managers/item/ItemManager.h"
#include "../zone/Zone.h"
#include "../zone/packets.h"

#include "ChatManager.h"

GMCommandMap * GameCommandHandler::gmCommands = NULL;

void GameCommandHandler::init() {
	const int DEVELOPER = PlayerImplementation::DEVELOPER;
	const int CSR = PlayerImplementation::CSR;
	const int NORMAL = PlayerImplementation::NORMAL;
	const int QA = PlayerImplementation::QA;
	const int PRIVLIDGED = DEVELOPER | CSR;
	const int ALL = DEVELOPER | NORMAL | CSR | QA;
	
	gmCommands = new GMCommandMap();
	
	gmCommands->addCommand("help", ALL, 
			"Prints a list of commands.",
			"Usage: @help [command]",
			&gm_help);
	gmCommands->addCommand("map", PRIVLIDGED | QA, 
			"Warps you to a different map.", 
			"Usage: @map <planetid> \n PlanetId List: 0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor, 4=Lok, 5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin ",
			&gm_map);
	gmCommands->addCommand("warp", PRIVLIDGED | QA, 
			"Warps you to a given set of coordinates.",
			"Usage: @warp <x> <y>",
			&gm_warp);
	gmCommands->addCommand("warpTo", PRIVLIDGED | QA,
			"Warps you to a player\'s location ",
			"Usage @warpTo <player>",
			&gm_warpTo);
	gmCommands->addCommand("warpPlayer", PRIVLIDGED,
			"Warps a player to a given set of coordinates.",
			"Usage: @warpPlayer <player> <starport |hotel | shuttle | medical | bank | garage | salon>",
			&gm_warpPlayer);
	gmCommands->addCommand("summon", PRIVLIDGED, 
			"Warps a player to your location.",
			"Usage: @summon <player>",
			&gm_summon);
	gmCommands->addCommand("kick", PRIVLIDGED, 
			"Disconnects a player from the game.",
			"Usage: @kick <player>",
			&gm_kick);
	gmCommands->addCommand("kickArea", PRIVLIDGED, 
			"Disconnects all players in a certain range.",
			"Usage: @kickArea [distance]",
			&gm_kickArea);
	gmCommands->addCommand("printRoomTree", DEVELOPER, 
			"Prints the room tree.",
			"Usage: @printRoomTree",
			&gm_printRoomTree);
	gmCommands->addCommand("banUser", DEVELOPER, 
			"Bans a user from logging in to the server.",
			"Usage: @banUser <player>",
			&gm_banUser);
	gmCommands->addCommand("mutePlayer", PRIVLIDGED, 
			"Prevents a player from speaking in spacial chat.",
			"Usage: @mutePlayer <player>",
			&gm_mutePlayer);
	gmCommands->addCommand("kill", PRIVLIDGED, 
			"Kills a player.", 
			"Usage: @kill <player>",
			&gm_kill);
	gmCommands->addCommand("killArea", PRIVLIDGED, 
			"Kills all players within a certain range.", 
			"Usage: @killArea [distance]",
			&gm_killArea);
	gmCommands->addCommand("muteChat", PRIVLIDGED, 
			"Prevents players from speaking in chat.", 
			"Usage: @muteChat",
			&gm_muteChat);
	gmCommands->addCommand("users", PRIVLIDGED, 
			"Prints the amount of users on the server.",
			"Usage: @users",
			&gm_users);
	gmCommands->addCommand("setWeather", DEVELOPER, 
			"Changes the weather conditions on the planet.", 
			"Usage: @setWeather <1-5>",
			&gm_setWeather);
	gmCommands->addCommand("ticketPurchase", PRIVLIDGED, 
			"Gives you a travel ticket.", 
			"Usage: @ticketPurchase <planet> <city>",
			&gm_ticketPurchase);
	gmCommands->addCommand("awardBadge", DEVELOPER, 
			"Awards a badge to targeted player.", 
			"Usage: @awardBadge <badgeid>",
			&gm_awardBadge);
	gmCommands->addCommand("systemMessage", PRIVLIDGED, 
			"Sends a message to all players on the server.",
			"Usage: @systemMessage <range> <message>",
			&gm_systemMessage);
	gmCommands->addCommand("setForceMax", DEVELOPER, 
			"Sets your force bar to the max level.", 
			"Usage: @setForceMax",
			&gm_setForceMax);
	gmCommands->addCommand("setForce", DEVELOPER, 
			"Sets your force bar to a given level.",
			"Usage: @setForce <value>",
			&gm_setForce);
	gmCommands->addCommand("setDrinkFilling", DEVELOPER, 
			"Sets your player's drink filling.", 
			"Usage: @setDrinkFilling <value>",
			&gm_setDrinkFilling);
	gmCommands->addCommand("setFoodFilling", DEVELOPER, 
			"Sets your player's food filling.",
			"Usage: @setFoodFilling <value>",
			&gm_setFoodFilling);
	gmCommands->addCommand("getDrinkFilling", DEVELOPER, 
			"Prints your current drink fill level.", 
			"Usage: @getDrinkFilling",
			&gm_getDrinkFilling);
	gmCommands->addCommand("getFoodFilling", DEVELOPER, 
			"Prints your current food fill level.", 
			"Usage: @getFoodFilling",
			&gm_getFoodFilling);
	gmCommands->addCommand("logAppearance", DEVELOPER, 
			"Prints your appearance stats.", 
			"Usage: @logApperarance",
			&gm_logAppearance);
	gmCommands->addCommand("updateAppearance", DEVELOPER, 
			"Reloads your character\'s appearance.", 
			"Usage: @updateAppearance",
			&gm_updateAppearance);
	gmCommands->addCommand("setAppearanceVariable", DEVELOPER, 
			"Sets an apperance variable for your character.",
			"Usage: @setAppearanceVariable <variable> <value>",
			&gm_setAppearanceVariable);
	gmCommands->addCommand("HAMStats", DEVELOPER, 
			"Prints your current HAM stats.", 
			"Usage: @HAMStats",
			&gm_HAMStats);
	gmCommands->addCommand("buff", ALL, 
			"Buffs your player.",
			"Usage: @buff",
			&gm_buff);
	gmCommands->addCommand("spice", ALL, 
			"Gives your player a certain spice.",
			"Usage: @spice <spice>",
			&gm_spice);
	gmCommands->addCommand("dbStats", DEVELOPER, 
			"Prints various database stats.", 
			"Usage: @dbStats",
			&gm_dbStats);
	gmCommands->addCommand("dbShowDeleted", DEVELOPER, 
			"Prints deleted items from the database.", 
			"Usage: @dbShowDeleted",
			&gm_dbShowDeleted);
	gmCommands->addCommand("dbPurge", DEVELOPER, 
			"Purges deleted items from the database.", 
			"Usage: @dbPurge",
			&gm_dbPurge);
	gmCommands->addCommand("getDirection", DEVELOPER, 
			"Prints out your direction or the direction of a targeted object.",
			"Usage: @getDirection",
			&gm_getDirection);
	gmCommands->addCommand("setAdminLevel", DEVELOPER, 
			"Sets your admin level.",
			"Usage: @setAdminLevel <player> <level> \n Levels: 1-CSR 2-DEVELOPER 4-PLAYER 8-QA",
			&gm_setAdminLevel);

}

void GameCommandHandler::gm_help(StringTokenizer tokenizer, Player * player) {
	if (tokenizer.hasMoreTokens()) {
		string token;
		tokenizer.getStringToken(token);
		
		if(gmCommands->containsKey(token)) {
			player->sendSystemMessage(gmCommands->get(token)->getDesc());
			player->sendSystemMessage(gmCommands->get(token)->getUsage());		
			return;
		}
	}
	
	LinkedList<string> list = gmCommands->getCommandList();
	stringstream ss;
	ss << "Command List: ";
	
	for(int i = 0; i < list.size(); i++) {
		string cmd = list.get(i);
		if(gmCommands->get(cmd)->getRequiredAdminLevel() & player->getAdminLevel())
			ss << list.get(i) << ", ";
	}
		
	player->sendSystemMessage(ss.str().substr(0, ss.str().length() - 2));
}

void GameCommandHandler::gm_map(StringTokenizer tokenizer, Player * player) {
	if (tokenizer.hasMoreTokens()) {
		int planetid = tokenizer.getIntToken();
		if (planetid >= 0 && planetid < 50)
			player->switchMap(planetid);
	} else {
		player->sendSystemMessage("Usage: map <planetid>\n"
		"0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor,\n"
		"5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin 4");
	}
}

void GameCommandHandler::gm_warp(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::gm_warpTo(StringTokenizer tokenizer, Player * player) {
	ChatManager * chatManager = player->getZone()->getChatManager();
	
	string name;
	tokenizer.getStringToken(name);
	
	Player* target = chatManager->getPlayer(name);
	
	if (target != NULL)
		player->doWarp(target->getPositionX(), target->getPositionY(), 0, 64);
}

void GameCommandHandler::gm_warpPlayer(StringTokenizer tokenizer, Player * player) {
	string name, whereTo = "";
	Player* targetPlayer;
	
	ChatManager * chatManager = player->getZone()->getChatManager();
	
	
	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(name);
		
		if (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(whereTo);
			targetPlayer = chatManager->getPlayer(name);
		} else {
			whereTo = name;

			SceneObject* obj = player->getTarget();

			if (obj != NULL && obj->isPlayer()) {
				targetPlayer = (Player*) obj;
			} else {
				player->sendSystemMessage("useage: @warpPlayer <SUPPLY PLAYERNAME OR CURRENT TARGET> <starport> <hotel> <shuttle> <medical> <bank> <garage> <salon> \n");
				return;
			}
		}

		float targetX = targetPlayer->getPositionX();
		float targetY = targetPlayer->getPositionY();

		Zone* targetZone = targetPlayer->getZone();
		if (targetZone == NULL)
			return;

		try {
			targetZone->lock();

			if (whereTo != "") {
				PlanetManager* planetManager = targetZone->getPlanetManager();

				BuildingObject* buiID = planetManager->findBuildingType(whereTo, targetX, targetY);

				if (buiID) {
					targetZone->unlock();
					targetPlayer->doWarp(buiID->getPositionX(), buiID->getPositionY(), 0, 0);
				} else {
					targetZone->unlock();
					player->sendSystemMessage("@warpPlayer didn't return a valid building ?! \n");
					return;
				}
			} else {
				targetZone->unlock();
				player->sendSystemMessage("useage: @warpPlayer <SUPPLY PLAYERNAME OR CURRENT TARGET> <starport> <hotel> <shuttle> <medical> <bank> <garage> <salon> \n");
			}
		} catch (...) {
			targetZone->unlock();
		}
	} else {
		player->sendSystemMessage("useage: @warpPlayer <SUPPLY PLAYERNAME OR CURRENT TARGET> <starport> <hotel> <shuttle> <medical> <bank> <garage> <salon> \n");
	}					
}

void GameCommandHandler::gm_summon(StringTokenizer tokenizer, Player * player) {
	string name;
	Player* targetPlayer;

	ChatManager * chatManager = player->getZone()->getChatManager();
	
	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(name);
		targetPlayer = chatManager->getPlayer(name);

		if (targetPlayer == NULL)
			return;
	} else {
		SceneObject* obj = player->getTarget();
		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;
			name = targetPlayer->getFirstName();
		} else {
			return;
		}
	}

	if (targetPlayer->getZoneIndex() != player->getZoneIndex()) {
		player->sendSystemMessage("You cant summon a player on a different planet! This feature will be added soon(R). \n");
		return;
	}

	Zone* targetZone = targetPlayer->getZone();
	if (targetZone == NULL)
		return;

	try {
		targetZone->lock();

		if (name != player->getFirstName()) {
			targetZone->unlock();
			targetPlayer->doWarp(player->getPositionX(), player->getPositionY(), 0, 10);
		} else {
			targetZone->unlock();
			player->sendSystemMessage("useage: @summon <SUPPLY PLAYERNAME OR CURRENT TARGET> \n");
			return;
		}
	} catch (...) {
		targetZone->unlock();
	}
}

void GameCommandHandler::gm_kick(StringTokenizer tokenizer, Player * player) {
	string name;
	Player* targetPlayer;
	ZoneServer * server = player->getZone()->getZoneServer();
	
	ChatManager * chatManager = player->getZone()->getChatManager();
		
	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(name);
		
		targetPlayer = chatManager->getPlayer(name);

		if (targetPlayer == NULL)
			return;
	} else {
		SceneObject* obj = player->getTarget();
		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;
			name = targetPlayer->getFirstName();
		} else {
			return;
		}
	}

	if (name != player->getFirstName()) {
		if (server->kickUser(name, player->getFirstName())) {
			player->sendSystemMessage("player \'" + name
					+ "\' has been kicked.");
		} else
			player->sendSystemMessage("unable to kick player \'" + name + "\'");

	} else
		player->sendSystemMessage("You can't kick yourself. Use /logout please. \n");
}

void GameCommandHandler::gm_kickArea(StringTokenizer tokenizer, Player * player) {
	ZoneServer * server = player->getZone()->getZoneServer();
	
	string name = player->getFirstName();
	//Default
	int meter = 32;
	//..as you wish my master
	meter = tokenizer.getIntToken();

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	try {
		zone->lock();

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

			if (obj->isPlayer()) {
				Player* otherPlayer = (Player*) obj;
				string otherName = otherPlayer->getFirstName();

				if (otherName != name && player->isInRange(otherPlayer, meter)) {
					zone->unlock();

					if (server->kickUser(otherName, name)) {
						player->sendSystemMessage("player \'" + otherName + "\' has been kicked.");
						i--;
					} else
					player->sendSystemMessage("unable to kick player \'" + otherName + "\'");

					zone->lock();
				}
			}
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();
	}
}

void GameCommandHandler::gm_printRoomTree(StringTokenizer tokenizer, Player * player) {
	ChatManager * chatManager = player->getZone()->getChatManager();
	ChatRoom * game = chatManager->getGameRoom("SWG");

	if (game != NULL) {
		chatManager->printRoomTree(game);
	}
}

void GameCommandHandler::gm_banUser(StringTokenizer tokenizer, Player * player) {
	ZoneServer * server = player->getZone()->getZoneServer();
	ChatManager * chatManager = player->getZone()->getChatManager();
	
	string name;
	Player* targetPlayer;

	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(name);
		
		targetPlayer = chatManager->getPlayer(name);

		if (targetPlayer == NULL)
			return;
	} else {
		SceneObject* obj = player->getTarget();
		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;
			name = targetPlayer->getFirstName();
		} else {
			return;
		}
	}

	if (server->banUser(name, player->getFirstName())) {
		player->sendSystemMessage("player \'" + name + "\' is banned");
	} else {
		player->sendSystemMessage("unable to ban player \'" + name + "\'");
	}
}

void GameCommandHandler::gm_mutePlayer(StringTokenizer tokenizer, Player * player) {
	string name;
	Player* targetPlayer;
	
	ChatManager * chatManager = player->getZone()->getChatManager();
	
	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(name);
		targetPlayer = chatManager->getPlayer(name);

		if (targetPlayer == NULL)
			return;
	} else {
		SceneObject* obj = player->getTarget();
		if (obj != NULL && obj->isPlayer())
			targetPlayer = (Player*) obj;
		else
			return;
	}

	try {
		if (targetPlayer != player)
		targetPlayer->wlock(player);

		name = targetPlayer->getFirstName();
		targetPlayer->mutePlayer();

		if ( targetPlayer->isChatMuted() ) {
			player->sendSystemMessage("Spatial chat for player \'" + name + "\' set MUTED.");
			targetPlayer->sendSystemMessage("Your (spatial) chat abilities were set to MUTED by \'" + player->getFirstName() + "\'.");
		} else {
			player->sendSystemMessage("Spatial chat for player \'" + name + "\' set to UNMUTED.");
			targetPlayer->sendSystemMessage("Your (spatial) chat abilities were RESTORED by \'" + player->getFirstName() + "\'.");
		}

		if (targetPlayer != player)
		targetPlayer->unlock();
	} catch (...) {
		if (targetPlayer != player)
		targetPlayer->unlock();
	}
}

void GameCommandHandler::gm_kill(StringTokenizer tokenizer, Player * player) {
	string name;
	Player* targetPlayer;

	ChatManager * chatManager = player->getZone()->getChatManager();
	
	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(name);
		targetPlayer = chatManager->getPlayer(name);

		if (targetPlayer == NULL)
			return;
	} else {
		SceneObject* obj = player->getTarget();
		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;
			name = targetPlayer->getFirstName();
		} else {
			return;
		}
	}

	try {
		if (targetPlayer != player)
		targetPlayer->wlock(player);

		targetPlayer->kill();

		targetPlayer->sendSystemMessage("Your character has been killed by \'" + player->getFirstName() + "\'.");
		player->sendSystemMessage("You killed the character \'" + name + "\'.");

		if (targetPlayer != player)
		targetPlayer->unlock();

	} catch (...) {
		if (targetPlayer != player)
		targetPlayer->unlock();
	}
}

void GameCommandHandler::gm_killArea(StringTokenizer tokenizer, Player * player) {
	string name = player->getFirstName();
	//Default
	int meter = 32;
	//..as you wish my master
	meter = tokenizer.getIntToken();

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	try {
		zone->lock();

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

			if (obj->isPlayer()) {
				Player* otherPlayer = (Player*) obj;
				string otherName = otherPlayer->getFirstName();

				if (otherName != name && player->isInRange(otherPlayer, meter)) {
					zone->unlock();

					try {
						if (otherPlayer != player)
						otherPlayer->wlock(player);

						otherPlayer->kill();

						if (otherPlayer != player)
						otherPlayer->unlock();

						player->sendSystemMessage("player \'" + otherName + "\' has been killed.");
					} catch (...) {
						if (otherPlayer != player)
						otherPlayer->unlock();
						player->sendSystemMessage("unable to kill player \'" + otherName + "\'");
					}

					zone->lock();
				}
			}
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();
	}
}

void GameCommandHandler::gm_muteChat(StringTokenizer tokenizer, Player * player) {
	ChatManager * chatManager = player->getZone()->getChatManager();
	
	if (chatManager->isMute()) {
		chatManager->setMute(false);
		player->sendSystemMessage("Chat has been unmuted.");
	} else {
		chatManager->setMute(true);
		player->sendSystemMessage("Chat has been muted.");
	}
}

void GameCommandHandler::gm_users(StringTokenizer tokenizer, Player * player) {
	ZoneServer * server = player->getZone()->getZoneServer();
	
	stringstream msg;
	msg << server->getConnectionCount() << " users connected";

	player->sendSystemMessage(msg.str());
}

void GameCommandHandler::gm_setWeather(StringTokenizer tokenizer, Player * player) {
	int weatherid = tokenizer.getIntToken();

	ServerWeatherMessage* swm = new ServerWeatherMessage(weatherid);
	player->broadcastMessage(swm);
}

void GameCommandHandler::gm_ticketPurchase(StringTokenizer tokenizer, Player * player) {
	string planet;
	tokenizer.getStringToken(planet);
	string city;
	tokenizer.getStringToken(city);

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(planet,city);
	player->sendMessage(etpm);			
}

void GameCommandHandler::gm_awardBadge(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::gm_systemMessage(StringTokenizer tokenizer, Player * player) {
	float range = tokenizer.getFloatToken();
	ChatManager * chatManager = player->getZone()->getChatManager();

	stringstream message;
	message << "System Message from " << player->getFirstName() << ": ";

	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(message);
		message << " ";
	}

	if (range == 0)
		chatManager->broadcastMessage(message.str());
	else
		chatManager->broadcastMessageRange(player, message.str(), range);
}

void GameCommandHandler::gm_setForceMax(StringTokenizer tokenizer, Player * player) {
	int fp = tokenizer.getIntToken();
	player->setMaxForcePowerBar(fp);
	stringstream message;
	message << "Set Force Power Max to: " << fp << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_setForce(StringTokenizer tokenizer, Player * player) {
	int fp = tokenizer.getIntToken();
	player->setForcePowerBar(fp);
	stringstream message;
	message << "Set Force Power to: " << fp << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_setDrinkFilling(StringTokenizer tokenizer, Player * player) {
	int fill = tokenizer.getIntToken();
	player->setDrinkFilling(fill);
	stringstream message;
	message << "Set drink filling: " << fill << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_setFoodFilling(StringTokenizer tokenizer, Player * player) {
	int fill = tokenizer.getIntToken();
	player->setFoodFilling(fill);
	stringstream message;
	message << "Set food filling: " << fill << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_getDrinkFilling(StringTokenizer tokenizer, Player * player) {
	int fill = player->getDrinkFilling();
	stringstream message;
	message << "Drink filling: " << fill << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_getFoodFilling(StringTokenizer tokenizer, Player * player) {
	int fill = player->getFoodFilling();
	stringstream message;
	message << "Food filling: " << fill << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_logAppearance(StringTokenizer tokenizer, Player * player) {
	string appearance;
	player->getCharacterAppearance(appearance);

	stringstream message;
	message << "Character Appearance:  " << uppercase << hex;

	for (int i = 0; i < appearance.size(); ++i) {
		unsigned int byte = ((unsigned int )appearance[i]) & 0xFF;

		if ((byte & 0xF0) == 0)
			message << "0" << byte << " ";
		else
			message << byte << " ";
	}

	message << dec << " Hair Appearance: " << uppercase << hex;

	string hairData;
	player->getHairAppearance(hairData);

	for (int i = 0; i < hairData.size(); ++i) {
		unsigned int byte = ((unsigned int )hairData[i]) & 0xFF;

		if ((byte & 0xF0) == 0)
			message << "0" << byte << " ";
		else
			message << byte << " ";
	}

	message << dec << " Height: " << std::fixed;
	message.precision(8);
	message << player->getHeight();

	player->info(message.str());
}

void GameCommandHandler::gm_updateAppearance(StringTokenizer tokenizer, Player * player) {
	((CreatureObject*) player)->updateCharacterAppearance();

	stringstream message;
	message << "Character Appearance updated.";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_setAppearanceVariable(StringTokenizer tokenizer, Player * player) {
	if (!tokenizer.hasMoreTokens())
		return;

	string variable;
	tokenizer.getStringToken(variable);

	if (!tokenizer.hasMoreTokens())
		return;

	int value = tokenizer.getIntToken();

	if (value < 0 || value > 255) //out of range
		return;

	((CreatureObject*) player)->setAppearanceAttribute(variable, (uint8)value);

	stringstream message;
	message << "Character Appearance Attribute Updated.";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_HAMStats(StringTokenizer tokenizer, Player * player) {
	stringstream message;

	message << "Health:  " << player->getHealth() << "/"
			<< player->getHealthMax() << "/" << player->getBaseHealth() << ".";
	message << " Action:  " << player->getAction() << "/"
			<< player->getActionMax() << "/" << player->getBaseAction() << ".";
	message << " Mind:  " << player->getMind() << "/" << player->getMindMax()
			<< "/" << player->getBaseMind() << ".";

	message << " Strength:  " << player->getStrength() << "/"
			<< player->getStrengthMax() << "/" << player->getBaseStrength()
			<< ".";
	message << " Constitution:  " << player->getConstitution() << "/"
			<< player->getConstitutionMax() << "/"
			<< player->getBaseConstitution() << ".";

	message << " Quickness:  " << player->getQuickness() << "/"
			<< player->getQuicknessMax() << "/" << player->getBaseQuickness()
			<< ".";
	message << " Stamina:  " << player->getStamina() << "/"
			<< player->getStaminaMax() << "/" << player->getBaseStamina()
			<< ".";

	message << " Focus:  " << player->getFocus() << "/"
			<< player->getFocusMax() << "/" << player->getBaseFocus() << ".";
	message << " Willpower:  " << player->getWillpower() << "/"
			<< player->getWillpowerMax() << "/" << player->getBaseWillpower()
			<< ".";

	player->sendSystemMessage(message.str());
}

void GameCommandHandler::gm_buff(StringTokenizer tokenizer, Player * player) {
	if (player->getHealthMax() == player->getBaseHealth()) {

		int buffValue = 3000;
		//float buffDuration = 10.0f; // Testing purposes
		float buffDuration = 10800.0f;

		Buff *buff; //pointer for each buff
		BuffObject *bo; //distributed object that contains the payload

		// Health
		buff
				= new Buff(BuffCRC::MEDICAL_ENHANCE_HEALTH, BuffType::MEDICAL, buffDuration);
		buff->setHealthBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		// Strength
		buff
				= new Buff(BuffCRC::MEDICAL_ENHANCE_STRENGTH, BuffType::MEDICAL, buffDuration);
		buff->setStrengthBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		// Constitution
		buff
				= new Buff(BuffCRC::MEDICAL_ENHANCE_CONSTITUTION, BuffType::MEDICAL, buffDuration);
		buff->setConstitutionBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		// Action
		buff
				= new Buff(BuffCRC::MEDICAL_ENHANCE_ACTION, BuffType::MEDICAL, buffDuration);
		buff->setActionBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		// Quickness
		buff
				= new Buff(BuffCRC::MEDICAL_ENHANCE_QUICKNESS, BuffType::MEDICAL, buffDuration);
		buff->setQuicknessBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		// Stamina
		buff
				= new Buff(BuffCRC::MEDICAL_ENHANCE_STAMINA, BuffType::MEDICAL, buffDuration);
		buff->setStaminaBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		// Mind
		buff
				= new Buff(BuffCRC::PERFORMANCE_ENHANCE_DANCE_MIND, BuffType::PERFORMANCE, buffDuration);
		buff->setMindBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		buff
				= new Buff(BuffCRC::PERFORMANCE_ENHANCE_MUSIC_FOCUS, BuffType::PERFORMANCE, buffDuration);
		buff->setFocusBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		buff
				= new Buff(BuffCRC::PERFORMANCE_ENHANCE_MUSIC_WILLPOWER, BuffType::PERFORMANCE, buffDuration);
		buff->setWillpowerBuff(buffValue);
		bo = new BuffObject(buff);
		player->applyBuff(bo);

		player->sendSystemMessage("Buffs applied");

	} else {
		player->sendSystemMessage("Already buffed");
	}
}

void GameCommandHandler::gm_spice(StringTokenizer tokenizer, Player * player) {
	if (player->hasSpice()) {
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

		switch (String::hashCode(spice_up.str())) {

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
}

void GameCommandHandler::gm_dbStats(StringTokenizer tokenizer, Player * player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->showDbStats(player);
}

void GameCommandHandler::gm_dbShowDeleted(StringTokenizer tokenizer, Player * player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->showDbDeleted(player);
}

void GameCommandHandler::gm_dbPurge(StringTokenizer tokenizer, Player * player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->purgeDbDeleted(player);
}

void GameCommandHandler::gm_getDirection(StringTokenizer tokenizer, Player * player) {
	SceneObject* target = player->getTarget();

	if (target == NULL)
		target = player;

	stringstream ss;
	ss << "oX: " << target->getDirectionX() << endl << "oZ: "
	   << target->getDirectionZ() << endl;
	ss << "oY: " << target->getDirectionY() << endl << "oW: "
	   << target->getDirectionW();
	player->sendSystemMessage(ss.str());
}

void GameCommandHandler::gm_setAdminLevel(StringTokenizer tokenizer, Player * player) {
	
	ChatManager * chatManager = player->getZone()->getChatManager();


	string name;
	tokenizer.getStringToken(name);
	
	if (!tokenizer.hasMoreTokens())
			return;
	
	int level = tokenizer.getIntToken();
	
	Player * target = chatManager->getPlayer(name);
	
	if (target != NULL) {
		target->setAdminLevel(level);
		stringstream ss;
		ss << player->getFirstName() << " has changed your admin level.";
		target->sendSystemMessage(ss.str());
	}
	
	ostringstream query;
	query << "UPDATE characters SET " << "adminLevel ='"
		  << level
		  << "' WHERE firstname=\'" << name << "\';";

	ServerDatabase::instance()->executeStatement(query.str());
	
	player->sendSystemMessage("Admin level set.");
}


