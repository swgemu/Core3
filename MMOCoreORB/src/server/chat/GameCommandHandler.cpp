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

#include "GameCommandHandler.h"

#include "../zone/managers/planet/PlanetManager.h"
#include "../zone/managers/item/ItemManager.h"
#include "../zone/managers/player/PlayerManager.h"
#include "../zone/managers/player/PlayerMap.h"

#include "../zone/Zone.h"
#include "../zone/packets.h"
#include "../zone/objects.h"

#include "ChatManager.h"

#include "../zone/managers/guild/GuildManager.h"
#include "../zone/managers/planet/PlanetManager.h"
#include "../zone/managers/structure/StructureManager.h"

GMCommandMap * GameCommandHandler::gmCommands = NULL;

void GameCommandHandler::init() {
	/* Admin Levels */
	const int DEVELOPER = PlayerImplementation::DEVELOPER; 						/* Admin/Dev  */
	const int CSR = PlayerImplementation::CSR;									/* CSR */
	const int EC = PlayerImplementation::EC;									/* Event Coordinator */
	const int LEADQA = PlayerImplementation::LEADQA;							/* Lead - Quality Assurance */
	const int QA = PlayerImplementation::QA;									/* Quality Assurance */
	const int EMUSTAFF = PlayerImplementation::EMUSTAFF;						/* Misc Emu Staff */
	const int NORMAL = PlayerImplementation::NORMAL;							/* Normal Player*/

	/* Admin Groups */
	const int ALL = DEVELOPER | CSR | EC | LEADQA | QA | EMUSTAFF | NORMAL;		/* All Staff/Players */
	const int STAFF = DEVELOPER | CSR | EC | LEADQA | QA | EMUSTAFF;			/* EMU Staff Only */
	const int PRIVILEGED = DEVELOPER | CSR;										/* Admin,Dev/CSR */
	const int CSREVENTS = DEVELOPER | CSR | EC;									/* Admin,Dev/CSR/Event Coordinator */

	gmCommands = new GMCommandMap();

	gmCommands->addCommand("commands", ALL,
			"Prints a list of commands.",
			"Usage: @commands [command]",
			&commands);
	gmCommands->addCommand("map", STAFF,
			"Warps you to a different map.",
			"Usage: @map <planetid> \n PlanetId List: 0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor, 4=Lok, 5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin 4",
			&map);
	gmCommands->addCommand("warp", STAFF,
			"Warps you to a given set of coordinates.",
			"Usage: @warp <x> <y>",
			&warp);
	gmCommands->addCommand("warpToWP", STAFF,
			"Warps you to the waypoint of the given name (casesensitive).",
			"Usage: @warpToWP <waypointName>",
			&warpToWP);
	gmCommands->addCommand("warpTo", STAFF,
			"Warps you to a player\'s location ",
			"Usage @warpTo <player>",
			&warpTo);
	gmCommands->addCommand("warpPlayer", PRIVILEGED,
			"Warps a player to a given set of coordinates.",
			"Usage: @warpPlayer <player> <starport |hotel | shuttle | medical | bank | garage | salon | punish>",
			&warpPlayer);
	gmCommands->addCommand("summon", PRIVILEGED | LEADQA,
			"Warps a player to your location.",
			"Usage: @summon <player>",
			&summon);
	gmCommands->addCommand("kick", PRIVILEGED,
			"Disconnects a player from the game.",
			"Usage: @kick <player>",
			&kick);
	gmCommands->addCommand("kickArea", DEVELOPER,
			"Disconnects all players in a certain range.",
			"Usage: @kickArea [distance]",
			&kickArea);
	/*gmCommands->addCommand("printRoomTree", DEVELOPER,
			"Prints the room tree.",
			"Usage: @printRoomTree",
			&printRoomTree);*/
	gmCommands->addCommand("banUser", PRIVILEGED,
			"Bans a user from logging in to the server.",
			"Usage: @banUser <name> <ban time in minutes> <reason>",
			&banUser);
	gmCommands->addCommand("getForumName", PRIVILEGED,
			"Returns forum name for select character.",
			"Usage: @getForumName <player>",
			&getForumName);
	gmCommands->addCommand("mutePlayer", CSREVENTS,
			"Prevents a player from speaking in spacial chat.",
			"Usage: @mutePlayer <player>",
			&mutePlayer);
	gmCommands->addCommand("kill", PRIVILEGED,
			"Kills a creature.",
			"Usage: @kill <player name or current-target>",
			&kill);
	gmCommands->addCommand("ecKill", CSREVENTS,
			"Kills a creature. EC version of the kill command.",
			"Usage: @ecKill <current-target>",
			&ecKill);
	gmCommands->addCommand("killArea", DEVELOPER,
			"Kills all players within a certain range.",
			"Usage: @killArea [distance]",
			&killArea);
	gmCommands->addCommand("muteChat", CSREVENTS,
			"Prevents players from speaking in chat.",
			"Usage: @muteChat",
			&muteChat);
	gmCommands->addCommand("users", STAFF,
			"Prints the amount of users on the server.",
			"Usage: @users",
			&users);
	gmCommands->addCommand("setWeather", CSREVENTS,
			"Changes the weather conditions on the planet.",
			"Usage: @setWeather <1-5>",
			&setWeather);
	gmCommands->addCommand("ticketPurchase", DEVELOPER,
			"Gives you a travel ticket.",
			"Usage: @ticketPurchase <planet> <city>",
			&ticketPurchase);
	gmCommands->addCommand("awardBadge", DEVELOPER,
			"Awards a badge to targeted player.",
			"Usage: @awardBadge <badgeid>",
			&awardBadge);
	gmCommands->addCommand("systemMessage", CSREVENTS | LEADQA,
			"Sends a message to all players on the server.",
			"Usage: @systemMessage <range> <message>",
			&systemMessage);
	gmCommands->addCommand("setForce", DEVELOPER,
			"Sets your force bar to a given level.",
			"Usage: @setForce <value>",
			&setForce);
	gmCommands->addCommand("setDrinkFilling", DEVELOPER,
			"Sets your player's drink filling.",
			"Usage: @setDrinkFilling <value>",
			&setDrinkFilling);
	gmCommands->addCommand("setFoodFilling", DEVELOPER,
			"Sets your player's food filling.",
			"Usage: @setFoodFilling <value>",
			&setFoodFilling);
	gmCommands->addCommand("getDrinkFilling", DEVELOPER,
			"Prints your current drink fill level.",
			"Usage: @getDrinkFilling",
			&getDrinkFilling);
	gmCommands->addCommand("getFoodFilling", DEVELOPER,
			"Prints your current food fill level.",
			"Usage: @getFoodFilling",
			&getFoodFilling);
	gmCommands->addCommand("logAppearance", DEVELOPER,
			"Prints your appearance stats.",
			"Usage: @logApperarance",
			&logAppearance);
	gmCommands->addCommand("updateAppearance", DEVELOPER,
			"Reloads your character\'s appearance.",
			"Usage: @updateAppearance",
			&updateAppearance);
	gmCommands->addCommand("setAppearanceVariable", DEVELOPER,
			"Sets an apperance variable for your character.",
			"Usage: @setAppearanceVariable <variable> <value>",
			&setAppearanceVariable);
	gmCommands->addCommand("HAMStats", DEVELOPER,
			"Prints your current HAM stats.",
			"Usage: @HAMStats",
			&HAMStats);
	gmCommands->addCommand("buff", PRIVILEGED | LEADQA,
			"Buffs your player.",
			"Usage: @buff",
			&buff);
	gmCommands->addCommand("spice", ALL,
			"Gives your player a certain spice.",
			"Usage: @spice <spice>",
			&spice);
	/*gmCommands->addCommand("dbStats", DEVELOPER,
			"Prints various database stats.",
			"Usage: @dbStats",
			&dbStats);
	gmCommands->addCommand("dbShowDeleted", DEVELOPER,
			"Prints deleted items from the database.",
			"Usage: @dbShowDeleted",
			&dbShowDeleted);
	gmCommands->addCommand("dbPurge", DEVELOPER,
			"Purges deleted items from the database.",
			"Usage: @dbPurge",
			&dbPurge);*/
	gmCommands->addCommand("getDirection", STAFF,
			"Prints out your direction or the direction of a targeted object.",
			"Usage: @getDirection",
			&getDirection);
	gmCommands->addCommand("setAdminLevel", DEVELOPER,
			"Sets your admin level.",
			"Usage: @setAdminLevel <player> <level> \n Levels: 1-CSR 2-DEVELOPER 4-PLAYER 8-QA 16-EC 32-LEADQA",
			&setAdminLevel);
	gmCommands->addCommand("getLocation", ALL,
			"Gives full detailsofyour location.",
			"Usage: @getLocation",
			&getLocation);
	/* Uncomment for use on DEV servers
	gmCommands->addCommand("getCords", DEVELOPER,
			"Command to aid the cave devs placing of creatures, SpawnCreature command is written pre-formatted to a file.",
			"Usage: @getCords <nameOfCreatureFile>",
			&getCords); */
	gmCommands->addCommand("giveItemTemp", DEVELOPER,
			"Adds a requested item to your inventory.",
			"Usage: @giveItemTemp <Item Type> [item sub-type]",
			&giveItemTemp);
	gmCommands->addCommand("clientEffect", CSREVENTS,
			"Plays a client effect animation around your character.",
			"Usage: @clientEffect <effect>",
			&clientEffect);
	gmCommands->addCommand("rez", PRIVILEGED | LEADQA,
			"Resurrects a player.",
			"Usage: @rez <player>",
			&rez);
	gmCommands->addCommand("immune", CSREVENTS | LEADQA,
			"Toggles immunity.",
			"Usage: @immune",
			&immune);
	gmCommands->addCommand("reloadSchematics", DEVELOPER,
			"Hot Loads schematic tables.",
			"Usage: @reloadSchematics",
			&reloadSchematics);
	gmCommands->addCommand("spawn", CSREVENTS,
			"Spawn a creature.",
			"Usage: @spawn <creaturetype> <moves (0,1)> <cellid> <x> <y> <bitmask> <baby>",
			&spawn);
	gmCommands->addCommand("guildAdmin", PRIVILEGED,
			"Let you join a guild temporarily to administer the guild via guildterminal.",
			"Usage: @guildAdmin GUILDTAG",
			&guildAdmin);
	gmCommands->addCommand("endGuildAdmin", PRIVILEGED,
			"Let you leave the guild you temporarily joined for support actions.",
			"Usage: @endGuildAdmin",
			&endGuildAdmin);
	gmCommands->addCommand("factionSet", CSREVENTS,
			"Let you change a players faction. Will be applied IMMEDIATLY!",
			"Usage: @factionSet overt | covert | rebel | imperial | neutral",
			&factionSet);
	gmCommands->addCommand("getCredits", CSREVENTS,
			"Gives you cash credits",
			"Usage: @getCredits [amount]",
			&getCredits);
	gmCommands->addCommand("getXP", DEVELOPER,
			"Gives you specified type of experience",
			"USAGE: @getXP [type] [amount]",
			&getXP);
	gmCommands->addCommand("adminList", PRIVILEGED,
			"Returns a list of players with a level higher than normal (4)",
			"USAGE: @adminList",
			&adminList);
	gmCommands->addCommand("showChars", PRIVILEGED,
			"Returns a list of characters a player has registrated with this server.",
			"USAGE: @showChars <Forum Nickname>",
			&showChars);
	gmCommands->addCommand("sendp", DEVELOPER,
			"Send Packet Test.",
			"Usage: @sendp",
			&sendp);
	gmCommands->addCommand("requestStartingLocations", ALL,
				"Resends the Starting Locations packet in case you accidentally close the window.",
				"Usage: @requestStartingLocations",
				&requestStartingLocations);
	gmCommands->addCommand("help", ALL,
				"Launch a web browser to the SWGEmu Support site.",
				"Usage: @help",
				&help);
}

GameCommandHandler::~GameCommandHandler() {
	if (gmCommands != NULL) {
		delete gmCommands;
		gmCommands = NULL;
	}
}

void GameCommandHandler::handleCommand(String cmd, StringTokenizer tokenizer, Player* player) {
	if (!gmCommands->containsKey(cmd)) {
		player->sendSystemMessage("Command not found.");
		return;
	}

	GMCommand * command = gmCommands->get(cmd);
	if (command->getRequiredAdminLevel() & player->getAdminLevel())
		command->exec(tokenizer, player);
	else
		player->sendSystemMessage("You do not have permission to use this command.");
}

void GameCommandHandler::commands(StringTokenizer tokenizer, Player* player) {
	if (tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);

		if ( gmCommands->containsKey(token)) {
			player->sendSystemMessage(gmCommands->get(token)->getDesc());
			player->sendSystemMessage(gmCommands->get(token)->getUsage());
			return;
		}
	}

	LinkedList<String> list = gmCommands->getCommandList();

	StringBuffer str;
	str << "Command List: ";

	for (int i = 0; i < list.size(); i++) {
		String cmd = list.get(i);

		if (gmCommands->get(cmd)->getRequiredAdminLevel() & player->getAdminLevel())
			str << list.get(i) << ", ";
	}

	str.removeRange(str.length() - 3, str.length() - 1);

	player->sendSystemMessage(str.toString());
}

void GameCommandHandler::map(StringTokenizer tokenizer, Player* player) {
	if (tokenizer.hasMoreTokens()) {
		int planetid = tokenizer.getIntToken();
		if (planetid >= 0 && planetid <= 45) //Servercrash risk! Do not change this back to 50 since there are no managers initialized
			player->switchMap(planetid);
	} else {
		player->sendSystemMessage("Usage: map <planetid>\n"
		"0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor, 4=Lok,\n"
		"5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin 4, 10=Bad player prison (Space)");
	}
}

void GameCommandHandler::warp(StringTokenizer tokenizer, Player* player) {
	if (!tokenizer.hasMoreTokens())
		return;

	float x = tokenizer.getFloatToken();

	if (!tokenizer.hasMoreTokens())
		return;

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

void GameCommandHandler::warpTo(StringTokenizer tokenizer, Player* player) {
	if (!tokenizer.hasMoreTokens())
		return;

	ChatManager * chatManager = player->getZone()->getChatManager();

	String name, myName;
	tokenizer.getStringToken(name);

	Player* target = chatManager->getPlayer(name);

	if (target == NULL || target == player)
		return;

	try {
		target->wlock(player);

		if (name != player->getFirstName()) {
			if (target->getZoneIndex() != player->getZoneIndex())
				player->switchMap(target->getZoneIndex());

			player->doWarp(target->getPositionX(), target->getPositionY(), 0, 5, target->getParentID());
		}

		target->unlock();

	} catch (...) {
		target->unlock();
		player->sendSystemMessage("Error in @warpTo - please submit a detailed ticket on the support site, tnx :)");
	}
}

void GameCommandHandler::warpPlayer(StringTokenizer tokenizer, Player* player) {
	String name, whereTo = "";
	Player* targetPlayer = NULL;

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
				player->sendSystemMessage("Usage: @warpPlayer <SUPPLY PLAYERNAME OR CURRENT TARGET> <starport> <hotel> <shuttle> <medical> <bank> <garage> <salon> <punish>\n");
				return;
			}
		}

		if (targetPlayer == player || targetPlayer == NULL)
			return;

		try {
			targetPlayer->wlock(player);

			float targetX = targetPlayer->getPositionX();
			float targetY = targetPlayer->getPositionY();

			Zone* targetZone = targetPlayer->getZone();

			if (targetZone == NULL) {
				targetPlayer->unlock();
				return;
			}

			if (whereTo != "") {
				PlanetManager* planetManager = targetZone->getPlanetManager();

				if (whereTo == "punish") {
					targetPlayer->switchMap(10); // Corellia Space as a punish room - no way back from there till CSR summons back
					targetPlayer->unlock();
					return;
				}

				StructureManager* structureManager = planetManager->getStructureManager();
				if (structureManager == NULL) {
					targetPlayer->unlock();
					return;
				}

				BuildingObject* buiID = structureManager->findBuildingType(whereTo, targetX, targetY);

				if (buiID) {
					targetPlayer->doWarp(buiID->getPositionX(), buiID->getPositionY(), 0, 0);
					targetPlayer->unlock();
				} else {
					targetPlayer->unlock();
					player->sendSystemMessage("@warpPlayer didn't return a valid building ?! \n");
					return;
				}
			} else {
				targetPlayer->unlock();
				player->sendSystemMessage("Usage: @warpPlayer <SUPPLY PLAYERNAME OR CURRENT TARGET> <starport> <hotel> <shuttle> <medical> <bank> <garage> <salon> <punish> \n");
			}
		} catch (...) {
			targetPlayer->unlock();
		}
	} else {
		player->sendSystemMessage("Usage: @warpPlayer <SUPPLY PLAYERNAME OR CURRENT TARGET> <starport> <hotel> <shuttle> <medical> <bank> <garage> <salon> <punish> \n");
	}
}

void GameCommandHandler::warpToWP(StringTokenizer tokenizer, Player* player) {
	float x,y;
	String wpName;

	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(wpName);
	} else {
		player->sendSystemMessage("Usage: @warpToWP <NameOfWaypoint>\n");
		return;
	}

	WaypointObject* waypoint = player->searchWaypoint(player, wpName,2);

	if (waypoint != NULL) {
		x = waypoint->getPositionX();
		y = waypoint->getPositionY();

		String planetName = waypoint->getPlanetName();
		int planet = player->getZoneIndex();

		if (planetName == "corellia")
			planet = 0;
		else if (planetName == "dantooine")
			planet = 1;
		else if (planetName == "dathomir")
			planet = 2;
		else if (planetName == "endor")
			planet = 3;
		else if (planetName == "lok")
			planet = 4;
		else if (planetName == "naboo")
			planet = 5;
		else if (planetName == "rori")
			planet = 6;
		else if (planetName == "talus")
			planet = 7;
		else if (planetName == "tatooine")
			planet = 8;
		else if (planetName == "yavin4")
			planet = 9;

		if (planet != player->getZoneIndex())
			player->switchMap(planet);

		player->doWarp(x, y);

	} else {
		player->sendSystemMessage("Waypoint not found ?! Make sure the spelling is correct.\n");
		return;
	}
}

void GameCommandHandler::summon(StringTokenizer tokenizer, Player* player) {
	String name;
	Player* targetPlayer = NULL;

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

	//I don't think targetPlayer can be NULL here anymore.. ?
	if (targetPlayer == NULL || targetPlayer == player)
		return;

	try {
		targetPlayer->wlock(player);

		if (targetPlayer->isMounted()) {
			targetPlayer->dismount(true, true);
			}


		Zone* targetZone = targetPlayer->getZone();

		if (targetZone == NULL) {
			targetPlayer->unlock();
			return;
		}

		if (name != player->getFirstName()) {
			if (targetPlayer->getZoneIndex() != player->getZoneIndex())
				targetPlayer->switchMap(player->getZoneIndex());

			targetPlayer->doWarp(player->getPositionX(), player->getPositionY(), 0, 10);
			targetPlayer->unlock();
		} else {
			targetPlayer->unlock();
			player->sendSystemMessage("Usage: @summon <SUPPLY PLAYERNAME OR CURRENT TARGET> \n");
			return;
		}
	} catch (...) {
		targetPlayer->unlock();
	}
}

void GameCommandHandler::kick(StringTokenizer tokenizer, Player* player) {
	String name;
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

	player->unlock();

	if (name != player->getFirstName()) {
		if (server->kickUser(name, player->getFirstName())) {
			player->sendSystemMessage("player \'" + name
					+ "\' has been kicked.");
		} else
			player->sendSystemMessage("unable to kick player \'" + name + "\'");

	} else
		player->sendSystemMessage("You can't kick yourself. Use /logout please. \n");

	player->wlock();
}

void GameCommandHandler::kickArea(StringTokenizer tokenizer, Player* player) {
	ZoneServer * server = player->getZone()->getZoneServer();

	String name = player->getFirstName();
	//Default
	int meter = 32;
	//..as you wish my master
	meter = tokenizer.getIntToken();

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	player->unlock();

	try {
		zone->lock();

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

			if (obj->isPlayer()) {
				Player* otherPlayer = (Player*) obj;
				String otherName = otherPlayer->getFirstName();

				if (otherName != name && player->isInRange(otherPlayer, meter) && (otherPlayer->getAdminLevel() == PlayerImplementation::NORMAL)) {
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

	player->wlock();
}

void GameCommandHandler::printRoomTree(StringTokenizer tokenizer, Player* player) {
	ChatManager * chatManager = player->getZone()->getChatManager();
	ChatRoom * game = chatManager->getGameRoom("SWG");

	if (game != NULL) {
		chatManager->printRoomTree(game);
	}
}

void GameCommandHandler::banUser(StringTokenizer tokenizer, Player* player) {
	ZoneServer* server = player->getZone()->getZoneServer();
	ChatManager* chatManager = player->getZone()->getChatManager();

	String name;
	StringBuffer banMessage;
	int banTime;
	Player* targetPlayer;

	int offendersAccountId = -1, adminsAccountId = -1;
	String offendersAccountName = "", adminsAccountName = "";

	if (tokenizer.hasMoreTokens()) {

		tokenizer.getStringToken(name);

	} else {

		player->sendSystemMessage("Standard IP ban Usage: @banUser <name>");
		player->sendSystemMessage("Forum Integration Usage: @banUser <name> <ban time in minutes> <reason>");
		player->sendSystemMessage("Bantime:  Permanent = 0; 1 Hour = 60; 1 Day = 3600;  1 Week = 25200");
		return;
	}

	if (tokenizer.hasMoreTokens()) {
		banTime = tokenizer.getIntToken();

		banTime *= 60;

		if (banTime != 0)
			banTime += time(0);

		String tempString;

		while (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(tempString);

			banMessage << tempString << " ";

		}

		if (banMessage.toString() == "") {
			player->sendSystemMessage("Invalid ban format, please specify reason");
			return;
		}

	} else {

		if (ForumsDatabase::instance() != NULL){
			player->sendSystemMessage("Invalid ban format, please specify duration and reason");
			return;
		}
	}

	player->unlock();

	if (ForumsDatabase::instance() != NULL) {

		try {
			StringBuffer query, query2, query3, query4, query5;

			query   << "SELECT account.account_id, account.username FROM account "
					<< "INNER JOIN characters ON "
					<< "characters.account_id = account.account_id WHERE characters.firstname = '"
					<< name << "'";

			query2  << "SELECT account.account_id, account.username FROM account "
					<< "INNER JOIN characters ON "
					<< "characters.account_id = account.account_id WHERE characters.firstname = '"
					<< player->getFirstName() << "'";

			ResultSet* res = ServerDatabase::instance()->executeQuery(query);

			if (res->next()) {
				offendersAccountId = res->getInt(0);
				offendersAccountName = res->getString(1);
			}

			res = ServerDatabase::instance()->executeQuery(query2);

			if (res->next()) {
				adminsAccountId = res->getInt(0);
				adminsAccountName = res->getString(1);
			}

			delete res;

			if (offendersAccountId == -1 || adminsAccountId == -1
					|| offendersAccountName == "" || adminsAccountName == "") {
				player->sendSystemMessage("Error getting account info");
				player->wlock();
				return;
			}

			if (offendersAccountName == adminsAccountName) {
				player->sendSystemMessage("You can't ban yourself.  Idiot");
				player->wlock();
				return;
			}

			StringBuffer getAdminID;
			getAdminID  << "SELECT " << ForumsDatabase::userTable() << ".userid FROM "
					    << ForumsDatabase::userTable() << " WHERE "
					    << ForumsDatabase::userTable() << ".username = '" << adminsAccountName << "'";

			res = ForumsDatabase::instance()->executeQuery(getAdminID);

			if (res->next()) {

				adminsAccountId = res->getInt(0);

			}

			delete res;

			query3  << "SELECT "
				    << ForumsDatabase::userTable() << ".userid, "
				    << ForumsDatabase::userTable() << ".usergroupid, "
				    << ForumsDatabase::userTable() << ".displaygroupid, "
				    << ForumsDatabase::userTable() << ".usertitle,"
				    << ForumsDatabase::userTable() << ".customtitle "
					<< " FROM "
					<< ForumsDatabase::userTable()
			        << " WHERE "
			        << ForumsDatabase::userTable() << ".username = '"
					<< offendersAccountName << "'";

			res = ForumsDatabase::instance()->executeQuery(query3);

			if (res->next()) {

				String userid = res->getString(0);
				String usergroupid = res->getString(1);

				if (usergroupid != ForumsDatabase::standardGroup()){
					delete res;
					player->sendSystemMessage("You can only ban standard users with this command");
					player->wlock();
					return;
				}

				String displaygroupid = res->getString(2);
				String usertitle = res->getString(3);
				String customtitle = res->getString(4);

				MySqlDatabase::escapeString(usertitle);
				MySqlDatabase::escapeString(customtitle);


				// Update Ban on USer
				query4 << "UPDATE "
				        << ForumsDatabase::userTable()
				        << " SET "
				        << ForumsDatabase::userTable() << ".usergroupid = '"
						<< ForumsDatabase::bannedGroup()
						<< "' WHERE "
						<< ForumsDatabase::userTable() << ".username = '" << offendersAccountName
						<< "'";

				ForumsDatabase::instance()->executeStatement(query4);

				// Update Banned user table
				query5 << "INSERT INTO "
					   << ForumsDatabase::bannedTable()
					   << " VALUES ('" << userid
					   << "', '" << usergroupid << "', '" << displaygroupid
					   << "', '" << usertitle << "', '" << customtitle
					   << "', '" << adminsAccountId << "', '" << time(0) << "', '"
					   << banTime << "', '" << banMessage.toString() << "')";

				ForumsDatabase::instance()->executeStatement(query5);


			} else {

				player->sendSystemMessage("Failed to retrieve forum info");

			}

			delete res;

			player->sendSystemMessage("player \'" + name
					+ "\' is banned (Forum Account = " + offendersAccountName + ")");

			server->kickUser(name, player->getFirstNameProper());

		} catch (...) {

			player->sendSystemMessage("unable to ban player \'" + name
					+ "\'  (Forum Account = " + offendersAccountName + ")");

		}
	} else if (server->banUser(name, player->getFirstName())) {

		player->sendSystemMessage("player \'" + name + "\' is banned (IP)");

	} else {
		player->sendSystemMessage("unable to ban player \'" + name + "\' (IP)");
	}

	player->wlock();
}

void GameCommandHandler::getForumName(StringTokenizer tokenizer, Player* player) {
	ZoneServer* server = player->getZone()->getZoneServer();
	PlayerManager* playerManager = server->getPlayerManager();

	String name;

	Player* targetPlayer = NULL;

	if (tokenizer.hasMoreTokens()) {

		tokenizer.getStringToken(name);


	} else {

		SceneObject* obj = player->getTarget();
		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;
			name = targetPlayer->getFirstName();
		} else {
			return;
		}

	}

	if (ForumsDatabase::instance() != NULL) {
		try {
			StringBuffer query;

			query   << "SELECT account.account_id, account.username FROM account "
					<< "INNER JOIN characters ON "
					<< "characters.account_id = account.account_id WHERE characters.firstname = '"
					<< name << "'";

			ResultSet* res = ServerDatabase::instance()->executeQuery(query);

			int offendersAccountId = -1;
			String offendersAccountName = "";

			if (res->next()) {
				offendersAccountId = res->getInt(0);
				offendersAccountName = res->getString(1);
			}

			delete res;

			player->sendSystemMessage("Forum account name: " + offendersAccountName);
		} catch (...) {
			player->sendSystemMessage("unable to get forum account info");
		}
	} else  {
		player->sendSystemMessage("Unable to get forum account for " + name);
	}
}

void GameCommandHandler::mutePlayer(StringTokenizer tokenizer, Player* player) {
	String name;
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
			player->sendSystemMessage("Chat for player \'" + name + "\' set MUTED.");
			targetPlayer->sendSystemMessage("Your chat abilities were set to MUTED by \'" + player->getFirstName() + "\'.");
		} else {
			player->sendSystemMessage("Chat for player \'" + name + "\' set to UNMUTED.");
			targetPlayer->sendSystemMessage("Your chat abilities were RESTORED by \'" + player->getFirstName() + "\'.");
		}

		if (targetPlayer != player)
			targetPlayer->unlock();
	} catch (...) {
		if (targetPlayer != player)
			targetPlayer->unlock();
	}
}

void GameCommandHandler::kill(StringTokenizer tokenizer, Player* player) {
	String name;
	Player* targetPlayer = NULL;
	Creature* creature = NULL;

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
		} else if (obj != NULL && obj->isNonPlayerCreature()) {
			creature = (Creature*) obj;
			name = creature->getName();
		} else {
			return;
		}

	}
	if (targetPlayer != NULL) {
		try {
			if (targetPlayer != player)
				targetPlayer->wlock(player);

			targetPlayer->explode(2, false);
			targetPlayer->kill();

			targetPlayer->sendSystemMessage(
					"Your character has been killed by \'"
							+ player->getFirstName() + "\'.");
			player->sendSystemMessage("You killed the character \'" + name
					+ "\'.");

			if (targetPlayer != player)
				targetPlayer->unlock();

		} catch (...) {
			if (targetPlayer != player)
				targetPlayer->unlock();
		}
	//} else if (creature != NULL  && !creature->isTrainer() && !creature->isRecruiter() && !creature->isMount()) {
	} else if (creature != NULL && creature->getCreatureBitmask() != 0x108 && creature->getCreatureBitmask() != 0x1080) {

		try {
			creature->wlock(player);

			creature->explode(2, false);
			uint damage = 100000000;

			creature->addDamage(player, damage);
			creature->takeHealthDamage(damage);

			creature->unlock();

		} catch (...) {
			creature->unlock();
		}

	}
}

void GameCommandHandler::ecKill(StringTokenizer tokenizer, Player* player) {
	Creature* creature = NULL;

	SceneObject* obj = player->getTarget();

	String name;

	if (obj != NULL && obj->isNonPlayerCreature()) {
		creature = (Creature*) obj;
		name = creature->getName();
	} else {
		return;
	}

	//if (creature != NULL  && !creature->isTrainer() && !creature->isRecruiter() && !creature->isMount()) {
	if (creature != NULL && creature->getCreatureBitmask() != 0x108 && creature->getCreatureBitmask() != 0x1080) {
		try {
			creature->wlock(player);

			creature->explode(2, false);
			uint damage = 100000000;

			creature->addDamage(player, damage);
			creature->takeHealthDamage(damage);

			creature->unlock();

		} catch (...) {
			creature->unlock();
		}
	}
}

void GameCommandHandler::killArea(StringTokenizer tokenizer, Player* player) {
	String name = player->getFirstName();
	//Default
	int meter;

	if (tokenizer.hasMoreTokens())
		meter = tokenizer.getIntToken();
	else
		meter = 32;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	try {
		zone->lock();

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject
					* obj =
							(SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(
									i))->_getStub());

			if (obj->isPlayer()) {
				Player* otherPlayer = (Player*) obj;
				String otherName = otherPlayer->getFirstName();

				if (otherName != name && player->isInRange(otherPlayer, meter)
						&& (otherPlayer->getAdminLevel()
								== PlayerImplementation::NORMAL)) {
					zone->unlock();

					try {
						if (otherPlayer != player)
							otherPlayer->wlock(player);

						otherPlayer->explode(2, false);
						otherPlayer->kill();

						if (otherPlayer != player)
							otherPlayer->unlock();

						player->sendSystemMessage("player \'" + otherName
								+ "\' has been killed.");
					} catch (...) {
						if (otherPlayer != player)
							otherPlayer->unlock();
						player->sendSystemMessage("unable to kill player \'"
								+ otherName + "\'");
					}

					zone->lock();
				}
			} else if (obj->isNonPlayerCreature()) {

				Creature* creature = (Creature*) obj;

				//if (creature->isInRange(creature, meter) && !creature->isTrainer() && !creature->isRecruiter()) {
				if (player->isInRange(creature, meter) && creature->getCreatureBitmask() != 0x108 && creature->getCreatureBitmask() != 0x1080) {
					zone->unlock();

					try {
						uint damage = 100000000;
						creature->explode(2, false);
						creature->addDamage(player, damage);
						creature->takeHealthDamage(damage);
						player->sendSystemMessage("creature has been killed.");
					} catch (...) {
						player->sendSystemMessage("unable to kill creature");
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

void GameCommandHandler::muteChat(StringTokenizer tokenizer, Player* player) {
	ChatManager * chatManager = player->getZone()->getChatManager();

	try {
		chatManager->lock();

		if (chatManager->isMute()) {
			chatManager->setMute(false);
			player->sendSystemMessage("Chat has been unmuted.");
		} else {
			chatManager->setMute(true);
			player->sendSystemMessage("Chat has been muted.");
		}

		chatManager->unlock();
	} catch (...) {
		chatManager->unlock();
		System::out << "unreported exception caught in GameCommandHandler::muteChat()\n";
	}
}

void GameCommandHandler::users(StringTokenizer tokenizer, Player* player) {
	ZoneServer * server = player->getZone()->getZoneServer();

	StringBuffer msg;
	msg << server->getConnectionCount() << " users connected";

	player->sendSystemMessage(msg.toString());
}

void GameCommandHandler::setWeather(StringTokenizer tokenizer, Player* player) {
	int weatherid = tokenizer.getIntToken();

	ServerWeatherMessage* swm = new ServerWeatherMessage(weatherid);
	player->broadcastMessage(swm);
}

void GameCommandHandler::ticketPurchase(StringTokenizer tokenizer, Player* player) {
	String planet;
	tokenizer.getStringToken(planet);

	String city;
	tokenizer.getStringToken(city);

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(planet,city);
	player->sendMessage(etpm);
}

void GameCommandHandler::awardBadge(StringTokenizer tokenizer, Player* player) {
	int badgeid = tokenizer.getIntToken();
	CreatureObject* target = (CreatureObject*) player->getTarget();

	if (target != NULL && target->isPlayer()) {
		Player* targetPlayer = (Player*) target;

		if (targetPlayer != player)
			targetPlayer->wlock(player);

		if (targetPlayer->awardBadge(badgeid)) {
			player->sendSystemMessage("You have awarded a badge.");
			targetPlayer->sendSystemMessage("You have been awarded a badge.");
		} else
			player->sendSystemMessage("Invalid Badge ID");

		if (targetPlayer != player)
			targetPlayer->unlock();
	} else
		player->sendSystemMessage("Invalid target.");
}

void GameCommandHandler::systemMessage(StringTokenizer tokenizer, Player* player) {
	uint32 range;

	try {
		if (tokenizer.hasMoreTokens())
			float range = tokenizer.getFloatToken();
		else
			range = 0;

		if (!tokenizer.hasMoreTokens()) {
			player->sendSystemMessage("Error sending systemMessage - Usage: systemMessage RANGE TEXT");
			return;
		}

		ChatManager * chatManager = player->getZone()->getChatManager();

		StringBuffer message;
		message << "System Message from " << player->getFirstName() << ": ";

		while (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(message);
			message << " ";
		}

		if (range == 0)
			chatManager->broadcastMessage(message.toString());
		else
			chatManager->broadcastMessageRange(player, message.toString(), range);

	} catch (...) {
		player->sendSystemMessage("Error sending systemMessage - Usage: systemMessage RANGE TEXT");
	}
}

void GameCommandHandler::setForce(StringTokenizer tokenizer, Player* player) {
	int fp = tokenizer.getIntToken();
	player->setForcePowerBar(fp);
	StringBuffer message;
	message << "Set Force Power to: " << fp << ".";
	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::setDrinkFilling(StringTokenizer tokenizer, Player* player) {
	int fill = tokenizer.getIntToken();
	player->setDrinkFilling(fill);
	StringBuffer message;
	message << "Set drink filling: " << fill << ".";
	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::setFoodFilling(StringTokenizer tokenizer, Player* player) {
	int fill = tokenizer.getIntToken();
	player->setFoodFilling(fill);
	StringBuffer message;
	message << "Set food filling: " << fill << ".";
	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::getDrinkFilling(StringTokenizer tokenizer, Player* player) {
	int fill = player->getDrinkFilling();
	StringBuffer message;
	message << "Drink filling: " << fill << ".";
	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::getFoodFilling(StringTokenizer tokenizer, Player* player) {
	int fill = player->getFoodFilling();
	StringBuffer message;
	message << "Food filling: " << fill << ".";
	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::logAppearance(StringTokenizer tokenizer, Player* player) {
	String appearance;
	player->getCharacterAppearance(appearance);

	StringBuffer message;
	message << "Character Appearance:  " << uppercase << hex;

	for (int i = 0; i < appearance.length(); ++i) {
		byte bt = (byte) appearance.charAt(i);

		if ((bt & 0xF0) == 0)
			message << "0" << bt << " ";
		else
			message << bt << " ";
	}

	message << dec << " Hair Appearance: " << uppercase << hex;

	String hairData;
	player->getHairAppearance(hairData);

	for (int i = 0; i < hairData.length(); ++i) {
		byte bt = (byte) hairData.charAt(i);

		if ((bt & 0xF0) == 0)
			message << "0" << bt << " ";
		else
			message << bt << " ";
	}

	//TODO: after the StringBuffer update need to add preciosion of 8 here
	message << dec << " Height: " << player->getHeight();

	player->info(message.toString());
}

void GameCommandHandler::updateAppearance(StringTokenizer tokenizer, Player* player) {
	((CreatureObject*) player)->updateCharacterAppearance();

	StringBuffer message;
	message << "Character Appearance updated.";

	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::setAppearanceVariable(StringTokenizer tokenizer, Player* player) {
	if (!tokenizer.hasMoreTokens())
		return;

	String variable;
	tokenizer.getStringToken(variable);

	if (!tokenizer.hasMoreTokens())
		return;

	int value = tokenizer.getIntToken();

	if (value < 0 || value > 255) //out of range
		return;

	((CreatureObject*) player)->setAppearanceAttribute(variable, (uint8)value);

	StringBuffer message;
	message << "Character Appearance Attribute Updated.";
	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::HAMStats(StringTokenizer tokenizer, Player* player) {
	StringBuffer message;

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

	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::buff(StringTokenizer tokenizer, Player* player) {
	int devBuff;
	devBuff = 0;

	try {
		if (tokenizer.hasMoreTokens())
			devBuff = tokenizer.getIntToken();

	} catch (...) {
		player->sendSystemMessage("Format for DEV/CSR buffs is @buff <value of buffstrenght, eg. 12000.\'.");
		devBuff = 0;
	}


	int buffValue = 3000;

	if (devBuff > 0 )
		buffValue = devBuff;


	if ( (player->getHealthMax() == player->getBaseHealth()) || (devBuff > 0)  ) {
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

void GameCommandHandler::spice(StringTokenizer tokenizer, Player* player) {
	if (player->hasSpice()) {
		player->sendSystemMessage("You already have spice.");
	} else if (tokenizer.hasMoreTokens()) {
		String name;
		tokenizer.getStringToken(name);

		StringBuffer spiceUp;
		spiceUp << "spice." << name << ".up";

		StringBuffer spiceDown;
		spiceDown << "spice." << name << ".down";

		Buff* buff = NULL;
		BuffObject* bo = NULL;

		switch (spiceUp.toString().hashCode()) {
		case 0x18A5AEFB: //spice.booster_blue.up
			buff = new Buff(BuffCRC::SPICE_BOOSTER_BLUE_UP, BuffType::SPICE, 600.0f);
			buff->setActionBuff(400);
			buff->setQuicknessBuff(400);
			buff->setBuffDownerCRC(BuffCRC::SPICE_BOOSTER_BLUE_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x5E1BE4D6: //spice.crash_n_burn.up
			buff = new Buff(BuffCRC::SPICE_CRASH_N_BURN_UP, BuffType::SPICE, 600.0f);
			buff->setActionBuff(-200);
			buff->setQuicknessBuff(-200);
			buff->setMindBuff(400);
			buff->setFocusBuff(200);
			buff->setBuffDownerCRC(BuffCRC::SPICE_CRASH_N_BURN_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x0C969AE9: //spice.droid_lube.up
			buff = new Buff(BuffCRC::SPICE_DROID_LUBE_UP, BuffType::SPICE, 600.0f);
			buff->setHealthBuff(250);
			buff->setStrengthBuff(250);
			buff->setConstitutionBuff(250);
			buff->setBuffDownerCRC(BuffCRC::SPICE_DROID_LUBE_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x3E41BA17: //spice.giggledust.up
			buff = new Buff(BuffCRC::SPICE_GIGGLEDUST_UP, BuffType::SPICE, 600.0f);
			buff->setActionBuff(300);
			buff->setQuicknessBuff(300);
			buff->setFocusBuff(-100);
			buff->setBuffDownerCRC(BuffCRC::SPICE_GIGGLEDUST_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0xE5C9CD20: //spice.grey_gabaki.up
			buff = new Buff(BuffCRC::SPICE_GREY_GABAKI_UP, BuffType::SPICE, 500.0f);
			buff->setFocusBuff(500);
			buff->setBuffDownerCRC(BuffCRC::SPICE_GREY_GABAKI_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x09B6F8FC: //spice.gunjack.up
			buff = new Buff(BuffCRC::SPICE_GUNJACK_UP, BuffType::SPICE, 600.0f);
			buff->setStrengthBuff(500);
			buff->setQuicknessBuff(-200);
			buff->setFocusBuff(-100);
			buff->setBuffDownerCRC(BuffCRC::SPICE_GUNJACK_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0xFBE87E37: //spice.muon_gold.up
			buff = new Buff(BuffCRC::SPICE_MUON_GOLD_UP, BuffType::SPICE, 600.0f);
			buff->setMindBuff(500);
			buff->setFocusBuff(500);
			buff->setWillpowerBuff(500);
			buff->setBuffDownerCRC(BuffCRC::SPICE_MUON_GOLD_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x5DC6921F: //spice.neutron_pixey.up
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
		case 0x1EBC62E5: //spice.pyrepenol.up
			buff = new Buff(BuffCRC::SPICE_PYREPENOL_UP, BuffType::SPICE, 600.0f);
			buff->setStrengthBuff(300);
			buff->setQuicknessBuff(-100);
			buff->setFocusBuff(-50);
			buff->setBuffDownerCRC(BuffCRC::SPICE_PYREPENOL_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x2E03F676: //spice.scramjet.up
			buff = new Buff(BuffCRC::SPICE_SCRAMJET_UP, BuffType::SPICE, 700.0f);
			buff->setStrengthBuff(300);
			buff->setBuffDownerCRC(BuffCRC::SPICE_SCRAMJET_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0xD7A72ACF: //spice.sedative_h4b.up
			buff = new Buff(BuffCRC::SPICE_SEDATIVE_H4B_UP, BuffType::SPICE, 600.0f);
			buff->setHealthBuff(400);
			buff->setConstitutionBuff(300);
			buff->setMindBuff(-100);
			buff->setFocusBuff(-100);
			buff->setBuffDownerCRC(BuffCRC::SPICE_SEDATIVE_H4B_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x3AAD2B89: //spice.shadowpaw.up
			buff = new Buff(BuffCRC::SPICE_SHADOWPAW_UP, BuffType::SPICE, 600.0f);
			buff->setStrengthBuff(-100);
			buff->setActionBuff(250);
			buff->setQuicknessBuff(250);
			buff->setBuffDownerCRC(BuffCRC::SPICE_SHADOWPAW_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x7EC00CB8: //spice.sweetblossom.up
			buff = new Buff(BuffCRC::SPICE_SWEETBLOSSOM_UP, BuffType::SPICE, 600.0f);
			buff->setActionBuff(400);
			buff->setQuicknessBuff(400);
			buff->setBuffDownerCRC(BuffCRC::SPICE_SWEETBLOSSOM_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x530E31B7: //spice.thruster_head.up
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
		case 0xE7F8C957: //spice.yarrock.up
			buff = new Buff(BuffCRC::SPICE_YARROCK_UP, BuffType::SPICE, 600.0f);
			buff->setMindBuff(200);
			buff->setFocusBuff(100);
			buff->setWillpowerBuff(100);
			buff->setBuffDownerCRC(BuffCRC::SPICE_YARROCK_DOWN);
			bo = new BuffObject(buff);
			player->applyBuff(bo);
			break;
		case 0x37173CAD: //spice.kliknik_boost.up
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
		case 0x629FA918: //spice.kwi_boost.up
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
			player->sendSystemMessage("Usage: @spice [spice_name] (available: booster_blue | crash_n_burn | droid_lube | giggledust | grey_gabaki | gunjack | muon_gold | neutron_pixey | pyrepenol | scramjet | sedative_h4b | shadowpaw | sweetblossom | thruster_head | yarrock | kliknik_boost | kwi_boost)");
		}
	} else {
		player->sendSystemMessage("Usage: @spice [spice_name] (available: booster_blue | crash_n_burn | droid_lube | giggledust | grey_gabaki | gunjack | muon_gold | neutron_pixey | pyrepenol | scramjet | sedative_h4b | shadowpaw | sweetblossom | thruster_head | yarrock | kliknik_boost | kwi_boost)");
	}
}

void GameCommandHandler::dbStats(StringTokenizer tokenizer, Player* player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->showDbStats(player);
}

void GameCommandHandler::dbShowDeleted(StringTokenizer tokenizer, Player* player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->showDbDeleted(player);
}

void GameCommandHandler::dbPurge(StringTokenizer tokenizer, Player* player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->purgeDbDeleted(player);
}

void GameCommandHandler::getDirection(StringTokenizer tokenizer, Player* player) {
	SceneObject* target = player->getTarget();

	if (target == NULL)
		target = player;

	StringBuffer ss;
	ss << "oX: " << target->getDirectionX() << endl << "oZ: "
	   << target->getDirectionZ() << endl;
	ss << "oY: " << target->getDirectionY() << endl << "oW: "
	   << target->getDirectionW();
	player->sendSystemMessage(ss.toString());
}

void GameCommandHandler::setAdminLevel(StringTokenizer tokenizer, Player* player) {
	ChatManager* chatManager = player->getZone()->getChatManager();

	String name;
	tokenizer.getStringToken(name);

	if (!tokenizer.hasMoreTokens())
		return;

	int level = tokenizer.getIntToken();

	Player* target = chatManager->getPlayer(name);

	if (target != NULL) {
		if (target != player)
			target->wlock(player);

		target->setAdminLevel(level);

		if (target != player)
			target->unlock();

		StringBuffer str;
		str << player->getFirstName() << " has changed your admin level.";
		target->sendSystemMessage(str.toString());
	}

	StringBuffer query;
	query << "UPDATE characters SET " << "adminLevel ='"
		  << level
		  << "' WHERE firstname=\'" << name << "\';";

	ServerDatabase::instance()->executeStatement(query);

	player->sendSystemMessage("Admin level set.");
}


void GameCommandHandler::getLocation(StringTokenizer tokenizer, Player* player) {
	StringBuffer ss;
	ss << "planet: " << player->getZoneID() << " cell: " << player->getParentID() << endl;
	ss << " X: " << player->getPositionX() << " Y: " << player->getPositionY();
	ss << " Z: " << player->getPositionZ() << endl;
	ss << "oX: " << player->getDirectionX() << " oZ: " << player->getDirectionZ();
	ss << "oY: " << player->getDirectionY() << " oW: " << player->getDirectionW();

	player->sendSystemMessage(ss.toString());
}

void GameCommandHandler::getCords(StringTokenizer tokenizer, Player* player) {
	//This command is for the cave devs, helping them building the needed LUA files.
	//Please dont delete it from the SVN , Uncomment for use on dev Servers.
	StringBuffer msg;
	String name;

	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(name);
	else
		name = "nameOfMob";

	msg << "X " << (player->getPositionX()) << " \n" << "Z "
			<< (player->getPositionZ()) << " \n" << "Y "
			<< (player->getPositionY()) << " \n";
	player->sendSystemMessage(msg.toString());

	msg << "Cell-ID is " << (player->getParentID()) << " \n";
	player->sendSystemMessage(msg.toString());

	msg << "Planet-ID is " << (player->getZoneIndex()) << " \n";
	player->sendSystemMessage(msg.toString());

	msg << "Mobname is " << name << " \n";
	player->sendSystemMessage(msg.toString());

	FileWriter cordFile(new File("cords.txt"));

	if ((player->getParentID() == 0)) {
		cordFile << "spawnCreature(" << name << ", " << player->getZoneIndex()
				<< ", " << player->getPositionX() << ", "
				<< player->getPositionY() << ")\n";
	} else {
		cordFile << "spawnCreatureInCell(" << name << ", "
				<< player->getZoneIndex() << ", " << player->getPositionX()
				<< ", " << player->getPositionZ() << ", "
				<< player->getPositionY() << ", " << player->getParentID()
				<< ")\n";
	}

	cordFile.close();
}

void GameCommandHandler::giveItemTemp(StringTokenizer tokenizer, Player* player) {
	//Give TANO
	if (!tokenizer.hasMoreTokens())
		return;

	String itemType;
	tokenizer.getStringToken(itemType);

	if (itemType == "Holocron") {
		Holocron * item = new Holocron(player, 0x9BA06548, UnicodeString("Holocron"), "object/tangible/jedi/shared_jedi_holocron_light.iff");
		player->addInventoryItem(item);

		item->sendTo(player);
	} else if (itemType == "Jetpack") {
			VehicleDeed * item = new VehicleDeed(player, 0x9899666C, UnicodeString("Deed for: Jetpack"), "jetpack_deed");
			player->addInventoryItem(item);

			item->sendTo(player);

	} else if (itemType == "ResourceDeed") {
			ResourceDeed * item = new ResourceDeed(player, 0x7D28DE23, UnicodeString("A Crate of Free Resources"), "resourceDeed");
			player->addInventoryItem(item);

			item->sendTo(player);
	} else if (itemType == "Firework") {
		if (tokenizer.hasMoreTokens()) {
			int fwAniType = tokenizer.getIntToken();

			Firework* item;
			switch (fwAniType) {
			//Firework diff. animation
			case 1:
				item = new Firework(player, 0x7C540DEB, UnicodeString("a Firework Type-4"), "object/tangible/firework/shared_firework_s04.iff",1);
				break;
			case 2:
				item = new Firework(player, 0x15ADE9E5, UnicodeString("a Firework Type-1"), "object/tangible/firework/shared_firework_s01.iff",2);
				break;
			case 3:
				item = new Firework(player, 0xCEBA4172, UnicodeString("a Firework Type-2"), "object/tangible/firework/shared_firework_s02.iff",3);
				break;
			case 4:
				item = new Firework(player, 0x87B726FF, UnicodeString("a Firework Type-3"), "object/tangible/firework/shared_firework_s03.iff",4);
				break;
			case 5:
				item = new Firework(player, 0x35596A66, UnicodeString("a Firework Type-5"), "object/tangible/firework/shared_firework_s05.iff",5);
				break;
			case 6:
				item = new Firework(player, 0x47888310, UnicodeString("a Firework Type-6"), "object/tangible/firework/shared_firework_s10.iff",6);
				break;
			case 7:
				item = new Firework(player, 0xE85E49D, UnicodeString("a Firework Type-7"), "object/tangible/firework/shared_firework_s11.iff",7);
				break;
			case 8:
				item = new Firework(player, 0x6618416, UnicodeString("a Firework Type-8"), "object/tangible/firework/shared_firework_s18.iff",8);
				break;
			default:
				player->sendSystemMessage("Useage: @giveItemTemp Firework <1-8>");
				return;
			}

			player->addInventoryItem(item);
			item->sendTo(player);

		} else {
			player->sendSystemMessage("Please submit the Firework animation (1-8).");
		}

	} else if (itemType == "AA") {
		Attachment* item = new Attachment(player->getNewItemID(), AttachmentImplementation::ARMOR);
		item->setSkillMods(System::random(500));

		player->addInventoryItem(item);

		item->sendTo(player);
	} else if (itemType == "Powerup") {
		Powerup* item = new Powerup(player->getNewItemID());
		item->setPowerupStats(System::random(500));

		player->addInventoryItem(item);

		item->sendTo(player);
	} else {
		player->sendSystemMessage("Unknown Item Type.");
	}
}

void GameCommandHandler::clientEffect(StringTokenizer tokenizer, Player* player) {
	if (!tokenizer.hasMoreTokens())
		return;

	String effect;
	tokenizer.getStringToken(effect);

	StringBuffer ss;
	ss << "clienteffect/" << effect << ".cef";

	PlayClientEffectObjectMessage* explode = new PlayClientEffectObjectMessage(player, ss.toString(), "");
	player->broadcastMessage(explode);

	PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc(ss.toString(), player->getZoneID(), player->getPositionX(), player->getPositionZ(), player->getPositionY());
	player->broadcastMessage(explodeLoc);
}


void GameCommandHandler::rez(StringTokenizer tokenizer, Player* player) {
	String name;
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
		if (!targetPlayer->isDead()) {
			player->sendSystemMessage("healing_response", "healing_response_a4"); //Your target does not require resuscitation!
			return;
		}
		if (targetPlayer != player)
			targetPlayer->wlock(player);

		((CreatureObject*)player)->resurrect(targetPlayer, true);

		targetPlayer->sendSystemMessage("Your character has been resuscitated by \'" + player->getFirstName() + "\'.");
		player->sendSystemMessage("You resuscitate the character \'" + name + "\'.");

		if (targetPlayer != player)
			targetPlayer->unlock();

	} catch (...) {
		if (targetPlayer != player)
			targetPlayer->unlock();
	}
}

void GameCommandHandler::immune(StringTokenizer tokenizer, Player* player) {
	player->toggleImmune();
}

void GameCommandHandler::reloadSchematics(StringTokenizer tokenizer,
		Player* player) {

	Zone* zone = player->getZone();
	ZoneServer* server = zone->getZoneServer();
	CraftingManager* craftingManager = server->getCraftingManager();
	PlayerManager* playerManager = server->getPlayerManager();

	PlayerMap* playerMap = playerManager->getPlayerMap();

	Player* targetPlayer;

	craftingManager->reloadSchematicTable();

	playerMap->resetIterator();

	while (playerMap->hasNext()) {

		targetPlayer = playerMap->next();

		if (targetPlayer != NULL) {

			craftingManager->refreshDraftSchematics(targetPlayer);
		}

	}
}
void GameCommandHandler::spawn(StringTokenizer tokenizer, Player* player) {
	Zone* zone = player->getZone();
	CreatureManager* creatureManager = zone->getCreatureManager();

	String name;
	uint64 cellid;
	uint32 objcrc;
	float x, y;
	bool stationary = false;

	// spawnCreature(uint32 objcrc, uint64 cellid, float x, float y, int bitmask, bool baby, bool doLock)

	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(name);
	} else {
		return;
	}


	if (player->getParent() != NULL) {
		cellid = player->getParent()->getObjectID();
	} else {
		cellid = 0;
	}

	float height = 1;
	x = player->getPositionX();
	y = player->getPositionY();

	if (tokenizer.hasMoreTokens()) {
		stationary = (bool) tokenizer.getIntToken();
	}

	if (tokenizer.hasMoreTokens())
		height = tokenizer.getFloatToken();

	if (tokenizer.hasMoreTokens()) {
		x = tokenizer.getFloatToken();
	}

	if (tokenizer.hasMoreTokens()) {
		y = tokenizer.getFloatToken();
	}



	if (height > 100)
		height = 100;

	if (height < .01f)
		height = .01f;

	if (x > 7680)
		x = 7680;
	if (x < -7680)
		x = -7680;

	if (y > 7680)
		y = 7680;
	if (y < -7680)
		y = -7680;

	if (creatureManager->verifyCreatureSpawn(name)) {

		uint32 objcrc = creatureManager->getCreatureCrc(name);

		Creature* creature = creatureManager->spawnCreature(objcrc, cellid, x, y,
				0, false, true, height);

		Zone* zone;

		if (creature != NULL && ((zone = creature->getZone()) != NULL)) {
			creature->setRespawnTimer(0);
			creature->setHeight(height);

			if (stationary)
				creature->setRandomMovement(false);

			CreatureImplementation * creoImpl = (CreatureImplementation *) creature->_getImplementation();

			try {
				zone->lock();

				for (int i = 0; i < creoImpl->inRangeObjectCount(); ++i) {
					SceneObjectImplementation * obj = (SceneObjectImplementation *) creoImpl->getInRangeObject(i);

					if (!(obj->isPlayer() || obj->isNonPlayerCreature()) || !creoImpl->isInRange((SceneObject *) obj->_getStub(), 24))
						continue;

					obj->notifyPositionUpdate(creoImpl);
					creoImpl->notifyPositionUpdate(obj);
				}

				zone->unlock();
			} catch (...) {
				zone->unlock();
			}
		}

	} else
		player->sendSystemMessage("Cannot spawn creature");
}


void GameCommandHandler::guildAdmin(StringTokenizer tokenizer, Player* player) {
	String tag;

	if (!tokenizer.hasMoreTokens()) {
		player->sendSystemMessage("Wrong format: Guildtag/abbrev. missing!");
		return;
	} else {
			tokenizer.getStringToken(tag);
	}

	ZoneServer* server;

	GuildManager* guildManager;

	Guild* playerGuild;

	ChatRoom* room;

	try {
		server = player->getZone()->getZoneServer();
		if (server == NULL)
			return;


		guildManager = server->getGuildManager();
		if (guildManager == NULL)
			return;


		playerGuild = guildManager->getGuild(tag, true);

		if (playerGuild == NULL) {
			player->sendSystemMessage("Guild not found!  Remember: Tag/abbrev. is case sensitive.");
				return;
		}

		player->setGuild(playerGuild);
		player->updateGuild(playerGuild);
		player->setGuildLeader(true);
		player->setGuildPermissions(255);

		room = playerGuild->getGuildChat();

		if (room != NULL) {
			room->sendTo(player);
			room->addPlayer(player, false);
		}


		StringBuffer message;

		message << "You have become part and temporarily co-leader of the guild '" << playerGuild->getGuildName() << "'.\n"
			<< "Please make sure, after you finished support actions, to leave the guild by typing @endGuildAdmin.";

		player->sendSystemMessage(message.toString());

	} catch (...) {
		return;
	}
}

void GameCommandHandler::endGuildAdmin(StringTokenizer tokenizer, Player* player) {
	uint64 defGuild = 0;

	Guild* playerGuild;

	ChatRoom* room;

	try {
		playerGuild = player->getGuild();

		if (playerGuild != 0) {

			room = playerGuild->getGuildChat();
			if (room != NULL)
				room->removePlayer(player, false);

			player->setGuild(defGuild);
			player->updateGuild(defGuild);
			player->setGuildLeader(false);
			player->setGuildPermissions(0);

			player->sendSystemMessage("You left the guild.");

		}

	} catch (...) {
		return;
	}
}

void GameCommandHandler::factionSet(StringTokenizer tokenizer, Player* player) {
	String tag;
	uint64 faction;
	Player* targetPlayer;

	if (!tokenizer.hasMoreTokens()) {
		player->sendSystemMessage("Usage: @factionSet overt | covert | onLeave | rebel | imperial | neutral");
		return;
	} else
		tokenizer.getStringToken(tag);


	try {
		SceneObject* obj = player->getTarget();

		if (obj == NULL)
			obj = player;

		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;

			if (targetPlayer != player)
				targetPlayer->wlock(player);

			if (tag == "rebel")
				faction = String("rebel").hashCode();
			else if (tag == "imperial")
				faction = String("imperial").hashCode();
			else if (tag == "neutral")
				faction = 0;
			else if (tag == "covert")
				faction = targetPlayer->getFaction();
			else if (tag == "overt")
				faction = targetPlayer->getFaction();
			else if (tag == "onLeave")
				faction = targetPlayer->getFaction();
			else {
				player->sendSystemMessage("Usage: @factionSet overt | covert | onLeave | rebel | imperial | neutral");

				if (targetPlayer != player)
					targetPlayer->unlock();

				return;
			}

			targetPlayer->setFaction(faction);

			if (tag == "onLeave" || tag == "neutral")
				targetPlayer->setOnLeave();
			else if (tag == "covert")
				targetPlayer->setCovert();
			else
				targetPlayer->setOvert();

			StringBuffer msg;
			msg << "You change " << targetPlayer->getFirstNameProper() << "'s GWC state to '" << tag << "'.";
			player->sendSystemMessage(msg.toString());

			targetPlayer->makeCharacterMask();

			if (targetPlayer != player)
				targetPlayer->unlock();
		}
	} catch (...) {
		if (targetPlayer != player)
			targetPlayer->unlock();
	}

}

void GameCommandHandler::getCredits(StringTokenizer tokenizer, Player* player) {
	uint32 credits;

	if (tokenizer.hasMoreTokens())
		credits = tokenizer.getIntToken();
	else
		credits = 100000;

	player->addCashCredits(credits);
}

void GameCommandHandler::getXP(StringTokenizer tokenizer, Player* player) {
	int xpamount;
	String xptype;

	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(xptype);
		if (tokenizer.hasMoreTokens())
			xpamount = tokenizer.getIntToken();
		else {
			player->sendSystemMessage("Usage: @getXP [xptype] [xpamount]");
			return;
		}
	} else {
		player->sendSystemMessage("Usage: @getXP [xptype] [xpamount]");
		return;
	}

	player->addXp(xptype, xpamount, true);
}

void GameCommandHandler::adminList(StringTokenizer tokenizer, Player* player) {
	try {
		StringBuffer query, msg, appendix;

		query << "SELECT character_id,firstname,surname,adminLevel from characters where adminLevel <> 4 order by character_id asc;";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			switch (res->getInt(3)) {
			case (1):
				appendix << "1 (CSR)";
				break;
			case (2):
				appendix << "2 (DEV)";
				break;
			case (8):
				appendix << "8 (QA)";
				break;
			case (16):
				appendix << "16 (EC)";
				break;
			case (32):
				appendix << "32 (LEAD QA)";
				break;
			case (64):
				appendix << "64 (EMU STAFF)";
				break;
			default:
				appendix << res->getInt(3) << "(UNKNOWN VALUE)";
			}

			msg << "Character ID: " << res->getUnsignedInt(0) << "    named: " << res->getString(1) << " "
				<< res->getString(1) << "     with level: " << appendix.toString();

			player->sendSystemMessage(msg.toString());

		}

		delete res;
	} catch (...) {
		player->info("Unreported Exception in GameCommandHandler::adminList(StringTokenizer tokenizer, Player* player)");
	}
}

void GameCommandHandler::showChars(StringTokenizer tokenizer, Player* player) {
	StringBuffer name, getToons, msg;
	String stringName;

	Player* targetPlayer;
	ResultSet* res;

	uint32 accountID = 0;

	ChatManager* chatManager = player->getZone()->getChatManager();

	try {
		if (!tokenizer.hasMoreTokens()) {
			player->sendSystemMessage("Usage: @showChars <Forum Nickname>");
			return;
		}

		while (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(stringName);
			name << stringName << " ";
		}

		stringName = name.toString().toLowerCase();

		MySqlDatabase::escapeString(stringName);

		getToons << "SELECT characters.character_id, characters.account_id, characters.firstname "
				 << "FROM characters Inner Join account ON account.account_id = characters.account_id "
				 << "WHERE LCASE(account.username) = '" << stringName << "' "
				 << "ORDER BY characters.account_id ASC, characters.firstname ASC;";

		res = ServerDatabase::instance()->executeQuery(getToons);

		msg << "The player " << stringName << "has registered the following characters: ";

		player->sendSystemMessage(msg.toString());

		while (res->next()) {
			msg.deleteAll();
			msg << "Character ID: " << res->getInt(0) << "    Charactername: " << res->getString(2);

			player->sendSystemMessage(msg.toString());
		}

		delete res;
	} catch (DatabaseException& e) {
		player->info("Database Exception in GameCommandHandler::showChars(StringTokenizer tokenizer, Player* player:");
		player->info(e.getMessage());

		System::out << e.getMessage() << endl;
	} catch (...) {
		player->info("Unreported Exception in GameCommandHandler::showChars(StringTokenizer tokenizer, Player* player)");
	}
}

void GameCommandHandler::sendp(StringTokenizer tokenizer, Player * player) {
	//TESTING PURPOSES ULTYMAS.
	uint32 type;

		if (tokenizer.hasMoreTokens())
			type = tokenizer.getIntToken();
		else
			type = 0;

		if (type == 0) {
			LaunchBrowserMessage* lbm = new LaunchBrowserMessage("www.swgemu.com");
			player->sendMessage(lbm);
		} else if (type == 1) {
			//GetArticleResponseMessage

		} else if (type == 2) {
			String command;
			tokenizer.getStringToken(command);

			ExecuteConsoleCommand* ecm = new ExecuteConsoleCommand(command);
			player->sendMessage(ecm);
		}  else if (type == 3) {
			String hud;
			tokenizer.getStringToken(hud);

			NewbieTutorialEnableHudElement* nthud = new NewbieTutorialEnableHudElement(hud);
			player->sendMessage(nthud);
		} else if (type == 4) {
			int flagtest;
			flagtest = tokenizer.getIntToken();

			ChatServerStatus* css = new ChatServerStatus(flagtest);
			player->sendMessage(css);
		}  else if (type == 5) {
			ConnectionServerTestMessage* csmf = new ConnectionServerTestMessage();
			player->sendMessage(csmf);

		} else if (type == 6) {
			unkZone* uzp = new unkZone();
			player->sendMessage(uzp);
		} else if (type == 7) {
			unkZoneTwo* uzp = new unkZoneTwo();
			player->sendMessage(uzp);
		} else if (type == 8) {
			unkZoneThree* uzp = new unkZoneThree();
			player->sendMessage(uzp);
		} else if (type == 9) {
			StartingLocationList* sll = new StartingLocationList(player);
			sll->AddLocation("tatooine", "mos_eisley", true);
			sll->AddLocation("naboo", "theed", true);
			player->sendMessage(sll);
		} else if (type == 10) {
			CommoditiesItemTypeListResponse* citlr = new CommoditiesItemTypeListResponse();
			player->sendMessage(citlr);
		}

	}

void GameCommandHandler::requestStartingLocations(StringTokenizer tokenizer, Player * player) {

	if (player->getZoneID() == 42) {
		StartingLocationList* sll = new StartingLocationList(player);
		player->sendMessage(sll);
	 } else {
		 player->sendSystemMessage("You can only use this command from the tutorial.");
	 }
}

void GameCommandHandler::help(StringTokenizer tokenizer, Player * player) {
			LaunchBrowserMessage* lbm = new LaunchBrowserMessage("www.swgemu.com/support");
			player->sendMessage(lbm);
}


