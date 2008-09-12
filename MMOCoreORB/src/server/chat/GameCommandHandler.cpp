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

#include "../zone/Zone.h"
#include "../zone/packets.h"
#include "../zone/objects.h"

#include "ChatManager.h"

GMCommandMap * GameCommandHandler::gmCommands = NULL;

void GameCommandHandler::init() {
	const int DEVELOPER = PlayerImplementation::DEVELOPER;
	const int CSR = PlayerImplementation::CSR;
	const int NORMAL = PlayerImplementation::NORMAL;
	const int QA = PlayerImplementation::QA;
	const int EC = PlayerImplementation::EC;
	const int PRIVILEGED = DEVELOPER | CSR;
	const int ALL = DEVELOPER | NORMAL | CSR | QA | EC;

	gmCommands = new GMCommandMap();

	gmCommands->addCommand("help", ALL,
			"Prints a list of commands.",
			"Usage: @help [command]",
			&help);
	gmCommands->addCommand("map", PRIVILEGED | QA | EC,
			"Warps you to a different map.",
			"Usage: @map <planetid> \n PlanetId List: 0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor, 4=Lok, 5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin 4",
			&map);
	gmCommands->addCommand("warp", PRIVILEGED | QA | EC,
			"Warps you to a given set of coordinates.",
			"Usage: @warp <x> <y>",
			&warp);
	gmCommands->addCommand("warpToWP", PRIVILEGED | QA,
			"Warps you to the waypoint of the given name (casesensitive).",
			"Usage: @warpToWP <waypointName>",
			&warpToWP);
	gmCommands->addCommand("warpTo", PRIVILEGED | QA,
			"Warps you to a player\'s location ",
			"Usage @warpTo <player>",
			&warpTo);
	gmCommands->addCommand("warpPlayer", PRIVILEGED,
			"Warps a player to a given set of coordinates.",
			"Usage: @warpPlayer <player> <starport |hotel | shuttle | medical | bank | garage | salon | punish>",
			&warpPlayer);
	gmCommands->addCommand("summon", PRIVILEGED,
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
			"Usage: @banUser <player>",
			&banUser);
	gmCommands->addCommand("getForumName", PRIVILEGED,
			"Returns forum name for select character.",
			"Usage: @getForumName <player>",
			&getForumName);
	gmCommands->addCommand("mutePlayer", PRIVILEGED | EC,
			"Prevents a player from speaking in spacial chat.",
			"Usage: @mutePlayer <player>",
			&mutePlayer);
	gmCommands->addCommand("kill", PRIVILEGED,
			"Kills a player.",
			"Usage: @kill <player>",
			&kill);
	gmCommands->addCommand("killArea", DEVELOPER,
			"Kills all players within a certain range.",
			"Usage: @killArea [distance]",
			&killArea);
	gmCommands->addCommand("muteChat", PRIVILEGED | EC,
			"Prevents players from speaking in chat.",
			"Usage: @muteChat",
			&muteChat);
	gmCommands->addCommand("users", PRIVILEGED | EC,
			"Prints the amount of users on the server.",
			"Usage: @users",
			&users);
	gmCommands->addCommand("setWeather", PRIVILEGED | EC,
			"Changes the weather conditions on the planet.",
			"Usage: @setWeather <1-5>",
			&setWeather);
	gmCommands->addCommand("ticketPurchase", PRIVILEGED,
			"Gives you a travel ticket.",
			"Usage: @ticketPurchase <planet> <city>",
			&ticketPurchase);
	gmCommands->addCommand("awardBadge", DEVELOPER,
			"Awards a badge to targeted player.",
			"Usage: @awardBadge <badgeid>",
			&awardBadge);
	gmCommands->addCommand("systemMessage", PRIVILEGED | EC,
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
	gmCommands->addCommand("buff", PRIVILEGED,
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
	gmCommands->addCommand("getDirection", PRIVILEGED,
			"Prints out your direction or the direction of a targeted object.",
			"Usage: @getDirection",
			&getDirection);
	gmCommands->addCommand("setAdminLevel", DEVELOPER,
			"Sets your admin level.",
			"Usage: @setAdminLevel <player> <level> \n Levels: 1-CSR 2-DEVELOPER 4-PLAYER 8-QA 16-EC",
			&setAdminLevel);
	gmCommands->addCommand("getLocation", PRIVILEGED,
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
	gmCommands->addCommand("clientEffect", DEVELOPER,
			"Plays a client effect animation around your character.",
			"Usage: @clientEffect <effect>",
			&clientEffect);
	gmCommands->addCommand("revive", PRIVILEGED,
			"Revives a player.",
			"Usage: @revive <player>",
			&revive);
	gmCommands->addCommand("immune", PRIVILEGED,
			"Toggles immunity.",
			"Usage: @immune",
			&immune);
}

GameCommandHandler::~GameCommandHandler() {
	if (gmCommands != NULL) {
		delete gmCommands;
		gmCommands = NULL;
	}
}

void GameCommandHandler::handleCommand(string cmd, StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::help(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::map(StringTokenizer tokenizer, Player * player) {
	if (tokenizer.hasMoreTokens()) {
		int planetid = tokenizer.getIntToken();
		if (planetid >= 0 && planetid <= 10) //Servercrash risk! Do not change this back to 50 since there are no managers initialized
			player->switchMap(planetid);
	} else {
		player->sendSystemMessage("Usage: map <planetid>\n"
		"0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor,\n"
		"5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin 4, 10=Bad player prison (Space)");
	}
}

void GameCommandHandler::warp(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::warpTo(StringTokenizer tokenizer, Player * player) {
	if (!tokenizer.hasMoreTokens())
		return;

	ChatManager * chatManager = player->getZone()->getChatManager();

	string name;
	tokenizer.getStringToken(name);

	Player* target = chatManager->getPlayer(name);

	if (target != NULL)
		player->doWarp(target->getPositionX(), target->getPositionY(), 0, 5, target->getParentID());
}

void GameCommandHandler::warpPlayer(StringTokenizer tokenizer, Player * player) {
	string name, whereTo = "";
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

				BuildingObject* buiID = planetManager->findBuildingType(whereTo, targetX, targetY);

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
				player->sendSystemMessage("Usage: @warpPlayer <SUPPLY PLAYERNAME OR CURRENT TARGET> <starport> <hotel> <shuttle> <medical> <bank> <garage> <salon> \n");
			}
		} catch (...) {
			targetPlayer->unlock();
		}
	} else {
		player->sendSystemMessage("Usage: @warpPlayer <SUPPLY PLAYERNAME OR CURRENT TARGET> <starport> <hotel> <shuttle> <medical> <bank> <garage> <salon> \n");
	}
}

void GameCommandHandler::warpToWP(StringTokenizer tokenizer, Player * player) {
	int i = 0;
	float x,y;
	string wpName;

	//PlayerObjectImplementation* playOI = (PlayerObjectImplementation*)player->getPlayerObject();

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
	} else {
		player->sendSystemMessage("Waypoint not found ?! Make sure the spelling is correct.\n");
		return;
	}

	player->doWarp(x, y);
}

void GameCommandHandler::summon(StringTokenizer tokenizer, Player * player) {
	string name;
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

void GameCommandHandler::kick(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::kickArea(StringTokenizer tokenizer, Player * player) {
	ZoneServer * server = player->getZone()->getZoneServer();

	string name = player->getFirstName();
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
				string otherName = otherPlayer->getFirstName();

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

void GameCommandHandler::printRoomTree(StringTokenizer tokenizer, Player * player) {
	ChatManager * chatManager = player->getZone()->getChatManager();
	ChatRoom * game = chatManager->getGameRoom("SWG");

	if (game != NULL) {
		chatManager->printRoomTree(game);
	}
}

void GameCommandHandler::banUser(StringTokenizer tokenizer, Player* player) {
	ZoneServer* server = player->getZone()->getZoneServer();
	ChatManager* chatManager = player->getZone()->getChatManager();

	string name;
	stringstream banMessage;
	int banTime;
	Player* targetPlayer;

	int offendersAccountId = -1, adminsAccountId = -1;
	string offendersAccountName = "", adminsAccountName = "";

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

		if(banTime != 0)
			banTime += time(0);

		string tempString;

		while (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(tempString);

			banMessage << tempString << " ";

		}

		if (banMessage.str() == "") {
			player->sendSystemMessage("Invalid ban format, please specify reason");
			return;
		}

	} else {

		if(ForumsDatabase::instance() != NULL){
			player->sendSystemMessage("Invalid ban format, please specify duration and reason");
			return;
		}
	}

	player->unlock();

	if (ForumsDatabase::instance() != NULL) {

		try {
			stringstream query, query2, query3, query4, query5;

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

			stringstream getAdminID;
			getAdminID  << "SELECT " << ForumsDatabase::userTable() << ".userid FROM "
					    << ForumsDatabase::userTable() << " WHERE "
					    << ForumsDatabase::userTable() << ".username = '" << adminsAccountName << "'";

			res = ForumsDatabase::instance()->executeQuery(getAdminID);

			if (res->next()) {

				adminsAccountId = res->getInt(0);

			}

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

				string userid = res->getString(0);
				string usergroupid = res->getString(1);

				if(usergroupid != ForumsDatabase::standardGroup()){
					player->sendSystemMessage("You can only ban standard users with this command");
					player->wlock();
					return;
				}

				string displaygroupid = res->getString(2);
				string usertitle = res->getString(3);
				string customtitle = res->getString(4);

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
					   << banTime << "', '" << banMessage.str() << "')";

				ForumsDatabase::instance()->executeStatement(query5);


			} else {

				player->sendSystemMessage("Failed to retrieve forum info");

			}

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

	string name;

	Player* targetPlayer;

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

	player->unlock();

	if (ForumsDatabase::instance() != NULL) {

		try {
			stringstream query, query2, query3, query4, query5;

			query   << "SELECT account.account_id, account.username FROM account "
					<< "INNER JOIN characters ON "
					<< "characters.account_id = account.account_id WHERE characters.firstname = '"
					<< name << "'";

			ResultSet* res = ServerDatabase::instance()->executeQuery(query);

			int offendersAccountId = -1;
			string offendersAccountName = "";

			if (res->next()) {
				offendersAccountId = res->getInt(0);
				offendersAccountName = res->getString(1);
			}

			player->sendSystemMessage("Forum account name: " + offendersAccountName);

		} catch (...) {

			player->sendSystemMessage("unable to get forum account info");

		}
	} else  {

		player->sendSystemMessage("Unable to get forum account for " + name);

	}
	player->wlock();
}

void GameCommandHandler::mutePlayer(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::kill(StringTokenizer tokenizer, Player * player) {
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

		targetPlayer->explode(2, false);
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

void GameCommandHandler::killArea(StringTokenizer tokenizer, Player * player) {
	string name = player->getFirstName();
	//Default
	int meter = 32;
	//..as you wish my master
	if (!tokenizer.hasMoreTokens())
		return;

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

				if (otherName != name && player->isInRange(otherPlayer, meter) && (otherPlayer->getAdminLevel() == PlayerImplementation::NORMAL)) {
					zone->unlock();

					try {
						if (otherPlayer != player)
							otherPlayer->wlock(player);

						otherPlayer->explode(2, false);
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

void GameCommandHandler::muteChat(StringTokenizer tokenizer, Player * player) {
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
		cout << "unreported exception caught in GameCommandHandler::muteChat()\n";
	}
}

void GameCommandHandler::users(StringTokenizer tokenizer, Player * player) {
	ZoneServer * server = player->getZone()->getZoneServer();

	stringstream msg;
	msg << server->getConnectionCount() << " users connected";

	player->sendSystemMessage(msg.str());
}

void GameCommandHandler::setWeather(StringTokenizer tokenizer, Player * player) {
	int weatherid = tokenizer.getIntToken();

	ServerWeatherMessage* swm = new ServerWeatherMessage(weatherid);
	player->broadcastMessage(swm);
}

void GameCommandHandler::ticketPurchase(StringTokenizer tokenizer, Player * player) {
	string planet;
	tokenizer.getStringToken(planet);
	string city;
	tokenizer.getStringToken(city);

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(planet,city);
	player->sendMessage(etpm);
}

void GameCommandHandler::awardBadge(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::systemMessage(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::setForce(StringTokenizer tokenizer, Player * player) {
	int fp = tokenizer.getIntToken();
	player->setForcePowerBar(fp);
	stringstream message;
	message << "Set Force Power to: " << fp << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::setDrinkFilling(StringTokenizer tokenizer, Player * player) {
	int fill = tokenizer.getIntToken();
	player->setDrinkFilling(fill);
	stringstream message;
	message << "Set drink filling: " << fill << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::setFoodFilling(StringTokenizer tokenizer, Player * player) {
	int fill = tokenizer.getIntToken();
	player->setFoodFilling(fill);
	stringstream message;
	message << "Set food filling: " << fill << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::getDrinkFilling(StringTokenizer tokenizer, Player * player) {
	int fill = player->getDrinkFilling();
	stringstream message;
	message << "Drink filling: " << fill << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::getFoodFilling(StringTokenizer tokenizer, Player * player) {
	int fill = player->getFoodFilling();
	stringstream message;
	message << "Food filling: " << fill << ".";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::logAppearance(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::updateAppearance(StringTokenizer tokenizer, Player * player) {
	((CreatureObject*) player)->updateCharacterAppearance();

	stringstream message;
	message << "Character Appearance updated.";
	player->sendSystemMessage(message.str());
}

void GameCommandHandler::setAppearanceVariable(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::HAMStats(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::buff(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::spice(StringTokenizer tokenizer, Player * player) {
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
			player->sendSystemMessage("Usage: @spice [spice_name] (available: booster_blue | crash_n_burn | droid_lube | giggledust | grey_gabaki | gunjack | muon_gold | neutron_pixey | pyrepenol | scramjet | sedative_h4b | shadowpaw | sweetblossom | thruster_head | yarrock | kliknik_boost | kwi_boost)");
		}
	} else {
		player->sendSystemMessage("Usage: @spice [spice_name] (available: booster_blue | crash_n_burn | droid_lube | giggledust | grey_gabaki | gunjack | muon_gold | neutron_pixey | pyrepenol | scramjet | sedative_h4b | shadowpaw | sweetblossom | thruster_head | yarrock | kliknik_boost | kwi_boost)");
	}
}

void GameCommandHandler::dbStats(StringTokenizer tokenizer, Player * player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->showDbStats(player);
}

void GameCommandHandler::dbShowDeleted(StringTokenizer tokenizer, Player * player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->showDbDeleted(player);
}

void GameCommandHandler::dbPurge(StringTokenizer tokenizer, Player * player) {
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	itemManager->purgeDbDeleted(player);
}

void GameCommandHandler::getDirection(StringTokenizer tokenizer, Player * player) {
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

void GameCommandHandler::setAdminLevel(StringTokenizer tokenizer, Player * player) {

	ChatManager * chatManager = player->getZone()->getChatManager();

	string name;
	tokenizer.getStringToken(name);

	if (!tokenizer.hasMoreTokens())
			return;

	int level = tokenizer.getIntToken();

	Player * target = chatManager->getPlayer(name);

	if (target != NULL) {

		if (target != player)
			target->wlock(player);

		target->setAdminLevel(level);

		if (target != player)
			target->unlock();

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


void GameCommandHandler::getLocation(StringTokenizer tokenizer, Player * player) {

	stringstream ss;
	ss << "planet: " << player->getZoneID() << " cell: " << player->getParentID() << endl;
	ss << " X: " << player->getPositionX() << " Y: " << player->getPositionY();
	ss << " Z: " << player->getPositionZ() << endl;
	ss << "oX: " << player->getDirectionX() << " oZ: " << player->getDirectionZ();
	ss << "oY: " << player->getDirectionY() << " oW: " << player->getDirectionW();
	player->sendSystemMessage(ss.str());
}

void GameCommandHandler::getCords(StringTokenizer tokenizer, Player * player) {
	//This command is for the cave devs, helping them building the needed LUA files.
	//Please dont delete it from the SVN , Uncomment for use on dev Servers.
	stringstream msg;
	string name;

	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(name);
	else
		name = "nameOfMob";

	msg << "X " << (player->getPositionX()) << " \n" << "Z "
			<< (player->getPositionZ()) << " \n" << "Y "
			<< (player->getPositionY()) << " \n";
	player->sendSystemMessage(msg.str());

	msg << "Cell-ID is " << (player->getParentID()) << " \n";
	player->sendSystemMessage(msg.str());

	msg << "Planet-ID is " << (player->getZoneIndex()) << " \n";
	player->sendSystemMessage(msg.str());

	msg << "Mobname is " << name << " \n";
	player->sendSystemMessage(msg.str());

	ofstream cordFile;
	cordFile.open("cords.txt", ios::app);

	if ((player->getParentID() == 0))
		cordFile << "spawnCreature(" << name << ", " << player->getZoneIndex()
				<< ", " << player->getPositionX() << ", "
				<< player->getPositionY() << ")\n";
	else
		cordFile << "spawnCreatureInCell(" << name << ", "
				<< player->getZoneIndex() << ", " << player->getPositionX()
				<< ", " << player->getPositionZ() << ", "
				<< player->getPositionY() << ", " << player->getParentID()
				<< ")\n";

	cordFile << flush;
	cordFile.close();
}

void GameCommandHandler::giveItemTemp(StringTokenizer tokenizer, Player * player) {
	//Give TANO
	if (!tokenizer.hasMoreTokens())
		return;

	string itemType;
	tokenizer.getStringToken(itemType);

	if (itemType == "Holocron") {
		Holocron * item = new Holocron(player, 0x9BA06548, unicode("Holocron"), "object/tangible/jedi/shared_jedi_holocron_light.iff");
		player->addInventoryItem(item);

		item->sendTo(player);
	} else if (itemType == "Jetpack") {
			VehicleDeed * item = new VehicleDeed(player, 0x9899666C, unicode("Deed for: Jetpack"), "jetpack_deed");
			player->addInventoryItem(item);

			item->sendTo(player);

	} else if (itemType == "Firework") {
		if (tokenizer.hasMoreTokens()) {
			int fwAniType = tokenizer.getIntToken();

			Firework* item;
			switch (fwAniType) {
			//Firework diff. animation
			case 1:
				item = new Firework(player, 0x7C540DEB, unicode("a Firework Type-4"), "object/tangible/firework/shared_firework_s04.iff",1);
				break;
			case 2:
				item = new Firework(player, 0x15ADE9E5, unicode("a Firework Type-1"), "object/tangible/firework/shared_firework_s01.iff",2);
				break;
			case 3:
				item = new Firework(player, 0xCEBA4172, unicode("a Firework Type-2"), "object/tangible/firework/shared_firework_s02.iff",3);
				break;
			case 4:
				item = new Firework(player, 0x87B726FF, unicode("a Firework Type-3"), "object/tangible/firework/shared_firework_s03.iff",4);
				break;
			case 5:
				item = new Firework(player, 0x35596A66, unicode("a Firework Type-5"), "object/tangible/firework/shared_firework_s05.iff",5);
				break;
			case 6:
				item = new Firework(player, 0x47888310, unicode("a Firework Type-6"), "object/tangible/firework/shared_firework_s10.iff",6);
				break;
			case 7:
				item = new Firework(player, 0xE85E49D, unicode("a Firework Type-7"), "object/tangible/firework/shared_firework_s11.iff",7);
				break;
			case 8:
				item = new Firework(player, 0x6618416, unicode("a Firework Type-8"), "object/tangible/firework/shared_firework_s18.iff",8);
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

void GameCommandHandler::clientEffect(StringTokenizer tokenizer, Player * player) {
	if(!tokenizer.hasMoreTokens())
		return;

	string effect;
	tokenizer.getStringToken(effect);

	stringstream ss;
	ss << "clienteffect/" << effect << ".cef";

	PlayClientEffectObjectMessage* explode = new PlayClientEffectObjectMessage(player, ss.str(), "");
	player->broadcastMessage(explode);

	PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc(ss.str(), player->getZoneID(), player->getPositionX(), player->getPositionZ(), player->getPositionY());
	player->broadcastMessage(explodeLoc);
}


void GameCommandHandler::revive(StringTokenizer tokenizer, Player * player) {
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
		if (!targetPlayer->isDead()) {
			player->sendSystemMessage("healing_response", "healing_response_a4"); //Your target does not require resuscitation!
			return;
		}
		if (targetPlayer != player)
			targetPlayer->wlock(player);

		targetPlayer->revive();

		targetPlayer->sendSystemMessage("Your character has been revived by \'" + player->getFirstName() + "\'.");
		player->sendSystemMessage("You revived the character \'" + name + "\'.");

		if (targetPlayer != player)
			targetPlayer->unlock();

	} catch (...) {
		if (targetPlayer != player)
			targetPlayer->unlock();
	}
}

void GameCommandHandler::immune(StringTokenizer tokenizer, Player * player) {
	player->toggleImmune();
}
