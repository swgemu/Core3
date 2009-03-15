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
#include "../zone/managers/combat/CombatManager.h"

#include "../zone/objects/area/TestActiveArea.h"

GMCommandMap * GameCommandHandler::gmCommands = NULL;

void GameCommandHandler::init() {
	/* Admin Levels */
	const int DEVELOPER = PlayerImplementation::DEVELOPER; 				/* Admin/Dev  */
	const int CSR = PlayerImplementation::CSR;							/* CSR */
	const int EC = PlayerImplementation::EC;							/* Event Coordinator */
	const int CSRJR = PlayerImplementation::CSRJR;						/* JR CSR */
	const int ECJR = PlayerImplementation::ECJR;						/* JR Event Coordinator */
	const int QA = PlayerImplementation::QA;							/* Quality Assurance */
	const int NORMAL = PlayerImplementation::NORMAL;					/* Normal Player*/

	/* Admin Groups */
	const int ALL = DEVELOPER | CSR | CSRJR | EC | ECJR | QA | NORMAL;	/* All Staff/Players */
	const int STAFF = DEVELOPER | CSR | CSRJR | EC | ECJR | QA;			/* Staff Only */
	const int PRIVILEGED = DEVELOPER | CSR;								/* Admin,Dev/CSR */
	const int PRIVILEGEDJR = DEVELOPER | CSR | CSRJR;					/* Admin,Dev/CSR /CSRJR*/
	const int CSREVENTS = DEVELOPER | CSR | EC;							/* Admin,Dev/CSR/Event Coordinator */
	const int CSREVENTSJR = DEVELOPER | CSR | EC | CSRJR | ECJR;		/* Admin,Dev/CSR/EC/CSRJR/ECJR */

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
			"Warps you to the waypoint of the given name (case sensitive).",
			"Usage: @warpToWP <waypointName>",
			&warpToWP);
	gmCommands->addCommand("warpTo", STAFF,
			"Warps you to a player\'s location ",
			"Usage @warpTo <player>",
			&warpTo);
	gmCommands->addCommand("warpPlayer", PRIVILEGEDJR,
			"Warps a player to a given location.",
			"Usage: @warpPlayer <player> <starport | hotel | shuttle | medical | bank | garage | salon | punish>",
			&warpPlayer);
	gmCommands->addCommand("summon", CSREVENTSJR,
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
	gmCommands->addCommand("banUser", PRIVILEGED,
			"Bans a user from logging in to the server.",
			"Usage: @banUser <name> <ban time in minutes> <reason>",
			&banUser);
	gmCommands->addCommand("getForumName", PRIVILEGEDJR,
			"Returns forum name for select character.",
			"Usage: @getForumName <player>",
			&getForumName);
	gmCommands->addCommand("mutePlayer", CSREVENTSJR,
			"Prevents a player from speaking in spacial chat.",
			"Usage: @mutePlayer <player>",
			&mutePlayer);
	gmCommands->addCommand("kill", PRIVILEGED,
			"Kills a player or creature.",
			"Usage: @kill <player name or current-target>",
			&kill);
	gmCommands->addCommand("ecKill", CSREVENTSJR,
			"Kills a creature. EC version of the kill command.",
			"Usage: @ecKill <current-target>",
			&ecKill);
	gmCommands->addCommand("killArea", DEVELOPER,
			"Kills all players or creatures within a certain range.",
			"Usage: @killArea [distance]",
			&killArea);
	gmCommands->addCommand("muteChat", CSREVENTSJR,
			"Prevents players from speaking in spacial chat.",
			"Usage: @muteChat",
			&muteChat);
	gmCommands->addCommand("users", STAFF,
			"Prints the amount of users on the server.",
			"Usage: @users",
			&users);
	gmCommands->addCommand("setWeather", CSREVENTSJR,
			"Changes the weather conditions on the planet.",
			"Usage: @setWeather <0-4>",
			&setWeather);
	gmCommands->addCommand("enableWeather", DEVELOPER,
			"Turn on weather randomization for the current planet.",
			"Usage: @enableWeather",
			&enableWeather);
	gmCommands->addCommand("disableWeather", DEVELOPER,
			"Turn off weather randomization for the current planet.",
			"Usage: @disableWeather",
			&disableWeather);
	gmCommands->addCommand("ticketPurchase", DEVELOPER,
			"Gives you a travel ticket.",
			"Usage: @ticketPurchase <planet> <city>",
			&ticketPurchase);
	gmCommands->addCommand("awardBadge", CSREVENTSJR,
			"Awards a badge to targeted player.",
			"Usage: @awardBadge <badgeid>",
			&awardBadge);
	gmCommands->addCommand("revokeBadge", CSREVENTSJR,
			"Remove a badge from a targeted player.",
			"Usage: @revokeBadge <badgeid>",
			&revokeBadge);
	gmCommands->addCommand("systemMessage", CSREVENTS,
			"Sends a message to all players on the server within the given range.",
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
			"Sets an appearance variable for your character.",
			"Usage: @setAppearanceVariable <variable> <value>",
			&setAppearanceVariable);
	gmCommands->addCommand("HAMStats", DEVELOPER,
			"Prints your current HAM stats.",
			"Usage: @HAMStats",
			&HAMStats);
	gmCommands->addCommand("buff", CSREVENTSJR,
			"Buffs your player or target player.",
			"Usage: @buff <target>",
			&buff);
	gmCommands->addCommand("spice", ALL,
			"Gives your player a certain spice.",
			"Usage: @spice <spice>",
			&spice);
	gmCommands->addCommand("getDirection", ALL,
			"Prints out your direction or the direction of a targeted object.",
			"Usage: @getDirection",
			&getDirection);
	gmCommands->addCommand("setAdminLevel", DEVELOPER,
			"Sets your admin level.",
			"Usage: @setAdminLevel <player> <level> \n Levels: 1-CSR 2-DEVELOPER 4-PLAYER 8-QA 16-EC 32-CSRJR 64-ECJR",
			&setAdminLevel);
	gmCommands->addCommand("getLocation", ALL,
			"Gives full details of your location.",
			"Usage: @getLocation",
			&getLocation);
	gmCommands->addCommand("getTargetLocation", ALL,
			"Gives full details of targeted object location.",
			"Usage: @getTargetLocation",
			&getTargetLocation);
	gmCommands->addCommand("giveItemTemp", CSREVENTS,
			"Adds a requested item to your inventory.",
			"Usage: @giveItemTemp <Item Type> [item sub-type]",
			&giveItemTemp);
	gmCommands->addCommand("clientEffect", CSREVENTS,
			"Plays a client effect animation around your character.",
			"Usage: @clientEffect <effect>",
			&clientEffect);
	gmCommands->addCommand("rez", CSREVENTSJR,
			"Resurrects a player.",
			"Usage: @rez <playername or target player>",
			&rez);
	gmCommands->addCommand("immune", CSREVENTSJR,
			"Toggles immunity.",
			"Usage: @immune",
			&immune);
	/*gmCommands->addCommand("invisible", PRIVILEGED ,
			"Toggles invisibility",
			"Usage: @invisible",
			&invisible);*/ // TA: review this, remove inRangeObject hacks
	gmCommands->addCommand("flare", PRIVILEGED,
			"Fires a flare at your position...",
			"Usage: @flare",
			&flare);
	gmCommands->addCommand("reloadSchematics", DEVELOPER,
			"Hot Loads schematic tables.",
			"Usage: @reloadSchematics",
			&reloadSchematics);
	gmCommands->addCommand("spawn", CSREVENTS,
			"Spawn a creature.",
			"Usage: @spawn <creaturetype> <moves (0,1)> <height> <x> <y> <baby>",
			&spawn);
	gmCommands->addCommand("guildAdmin", PRIVILEGED,
			"Let you join a guild temporarily to administer the guild via guildterminal.",
			"Usage: @guildAdmin GUILDTAG",
			&guildAdmin);
	gmCommands->addCommand("endGuildAdmin", PRIVILEGED,
			"Let you leave the guild you temporarily joined for support actions.",
			"Usage: @endGuildAdmin",
			&endGuildAdmin);
	gmCommands->addCommand("factionSet", CSREVENTSJR,
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
	gmCommands->addCommand("adminList", DEVELOPER,
			"Returns a list of players with a level higher than normal (4)",
			"USAGE: @adminList",
			&adminList);
	gmCommands->addCommand("showChars", PRIVILEGEDJR,
			"Returns a list of characters a player has registered with this server.",
			"USAGE: @showChars <Forum Nickname>",
			&showChars);
	gmCommands->addCommand("lockServer", DEVELOPER,
			"Locks the server for internal testing.",
			"USAGE: @lockServer",
			&lockServer);
	gmCommands->addCommand("unlockServer", DEVELOPER,
			"Unlocks the server for public testing.",
			"USAGE: @lockServer",
			&unlockServer);
	gmCommands->addCommand("sendp", DEVELOPER,
			"Send a Packet Test.",
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
	gmCommands->addCommand("bug", ALL,
			"Launch a web browser to the SWGEmu Bug Reporting Site.",
			"Usage: @bug",
			&bug);
	gmCommands->addCommand("openInventory", PRIVILEGED,
			"Open a players (target) inventory. - THIS ACTION IS LOGGED",
			"Usage: @openInventory (with a player as the current target)",
			&openInventory);
	//Temporary for CSRs as long as structures and cell permissions not finally in
	gmCommands->addCommand("poofObject", PRIVILEGEDJR,
			"Destroys an object.",
			"USAGE: @poofObject <target>",
			&poofObject);
	//Temporary for CSRs as long as structures and cell permissions not finally in
	gmCommands->addCommand("whoDroppedThis", PRIVILEGEDJR,
			"Shows the characters name who dropped the current target (item).",
			"USAGE: @whoDroppedThis <target>",
			&whoDroppedThis);
	gmCommands->addCommand("freezePlayer", PRIVILEGED,
			"Freezes a player to prevent movement.",
			"Usage: @freezePlayer name.",
			&freezePlayer);
	gmCommands->addCommand("unfreezePlayer", PRIVILEGED,
			"Freezes a player to prevent movement.",
			"Usage: @unfreezePlayer name.",
			&unfreezePlayer);
	/**/
	gmCommands->addCommand("setSpeed", PRIVILEGED,
			"Sets a players speed/acceleration.",
			"Usage: @setSpeed speed acceleration.",
			&setSpeed);
	gmCommands->addCommand("setHeight", PRIVILEGED,
			"Sets the height of a player or creature.",
			"Usage: @setHeight number.",
			&setHeight);
	gmCommands->addCommand("warpAreaToWP", CSREVENTS,
			"Warps all players in a set radius to a specific waypoint",
			"Usage: @warpAreaToWP <waypointName> <radius>",
			&warpAreaToWP);
	gmCommands->addCommand("scaleXP", DEVELOPER,
			"Sets the multiplier for serverwide experience",
			"Usage: @scaleXP <scaler>",
			&scaleXP);
	gmCommands->addCommand("drag", CSREVENTS,
			"Drags a dead or incapacitated player toward yourself.",
			"Usage: @drag",
			&drag);
	gmCommands->addCommand("playAudio", DEVELOPER,
				"Plays the specified audio file",
				"USAGE: @playAudio [soundfile]",
				&playAudio);
	gmCommands->addCommand("eventMessage", CSREVENTSJR,
				"Sends a system message, tailored for announcing events.",
				"USAGE: @eventMessage <message>",
				&eventMessage);
	gmCommands->addCommand("eventCloner", CSREVENTS,
				"Spawns a cloning facility at the current location.",
				"USAGE: @eventCloner <decaying> <wounding> <buffValue> <neutral|rebel|imperial>",
				&eventCloner);
	gmCommands->addCommand("setMOTD", PRIVILEGED,
				"Edit the Message of the Day",
				"USAGE: @setMOTD",
				&setMOTD);
	gmCommands->addCommand("tasks", ALL,
				"Displays the current Message of the Day",
				"USAGE: @tasks",
				&displayMOTD);
	/* Disabled Commands

	gmCommands->addCommand("applyDot", DEVELOPER,
				"applyDot",
				"USAGE: @applyDot ",
				&applyDot);
	gmCommands->addCommand("damage", DEVELOPER,
					"damage.",
					"Usage: @damage",
					&damage);
	gmCommands->addCommand("deleteFromZone", DEVELOPER,
			"Deletes the target item from the zone.",
			"Usage: @deleteFromZone",
			&deleteFromZone);
	gmCommands->addCommand("setLocation", DEVELOPER,
			"Shows your setLocation",
			"Usage: @setLocation>",
			&setLocation);
	gmCommands->addCommand("toggleCombat", DEVELOPER,
			"Enables/Disables combat.",
			"USAGE: @toggleCombat",
			&toggleCombat);
	//Uncomment for use on DEV servers
	gmCommands->addCommand("getCords", DEVELOPER,
			"Command to aid the cave devs placing of creatures, SpawnCreature command is written pre-formatted to a file.",
			"Usage: @getCords <nameOfCreatureFile>",
			&getCords);
	gmCommands->addCommand("changeTemplate", PRIVILEGED,
			"Changes the objects template. Useful for CSR Events.",
			"Usage: @changeTemplate newtemplate.",
			&changeTemplate);
	gmCommands->addCommand("dbStats", DEVELOPER,
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
			&dbPurge);
	gmCommands->addCommand("printRoomTree", DEVELOPER,
			"Prints the room tree.",
			"Usage: @printRoomTree",
			&printRoomTree);
	gmCommands->addCommand("spawnAA", DEVELOPER,
			"Spawns a test Action Area",
			"Usage: @spawnAA <x> <y> <z> <range>",
			&spawnAA);

	Disabled Commands */
}

GameCommandHandler::~GameCommandHandler() {
	if (gmCommands != NULL) {
		delete gmCommands;
		gmCommands = NULL;
	}
}

void GameCommandHandler::handleCommand(String cmd, StringTokenizer tokenizer, Player* player) {
	String cmdLower = cmd.toLowerCase();
	if (!gmCommands->containsKey(cmdLower)) {
		player->sendSystemMessage("Command not found.");
		return;
	}

	GMCommand * command = gmCommands->get(cmdLower);
	if (command->getRequiredAdminLevel() & player->getAdminLevel())
		command->exec(tokenizer, player);
	else
		player->sendSystemMessage("You do not have permission to use this command.");
}

void GameCommandHandler::commands(StringTokenizer tokenizer, Player* player) {
	if (tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);

		if (gmCommands->containsKey(token)) {
			player->sendSystemMessage(gmCommands->get(token)->getDesc());
			player->sendSystemMessage(gmCommands->get(token)->getUsage());
			return;
		}
	}

	LinkedList<String> list = gmCommands->getCommandList();

	StringBuffer str;
	str << "Command List: ";

	SuiListBox* commandsList = new SuiListBox(player, 0);
	commandsList->setPromptTitle("Available Commands");
	commandsList->setPromptText("The following commands are available to you.");

	for (int i = 0; i < list.size(); i++) {
		String cmdKey = list.get(i);
		GMCommand* cmd = gmCommands->get(cmdKey);

		if (cmd->getRequiredAdminLevel() & player->getAdminLevel()) {
			String cmdName = cmd->getName();

			if (cmdName != "commands")
				commandsList->addMenuItem(cmdName);
		}
	}

	player->sendMessage(commandsList->generateMessage());
	commandsList->finalize();
}

void GameCommandHandler::map(StringTokenizer tokenizer, Player* player) {
	if (tokenizer.hasMoreTokens()) {
		int planetid = tokenizer.getIntToken();
		if ((planetid >= 0 && planetid <= 10) || planetid == 42) //Servercrash risk! Do not change this back to 50 since there are no managers initialized
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

		targetPlayer->crashClient();

		if (server->kickUser(name, player->getFirstName())) {
			player->sendSystemMessage("player \'" + name
					+ "\' has been kicked.");
		} else
			player->sendSystemMessage("Unable to kick player \'" + name + "\'");
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
						otherPlayer->crashClient();
					} else
					player->sendSystemMessage("Unable to kick player \'" + otherName + "\'");

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
		ChatManager * chatManager = player->getZone()->getChatManager();

		targetPlayer = chatManager->getPlayer(name);

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
			player->sendSystemMessage("Invalid ban format, please specify a reason.");
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
				player->sendSystemMessage("You can't ban yourself, idiot.");
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
					player->sendSystemMessage("You can only ban standard users with this command.");
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

			if(targetPlayer != NULL)
				targetPlayer->crashClient();

			server->kickUser(name, player->getFirstNameProper());

		} catch (...) {

			player->sendSystemMessage("Unable to ban player \'" + name
					+ "\'  (Forum Account = " + offendersAccountName + ")");

		}
	} else if (server->banUser(name, player->getFirstName())) {

		if(targetPlayer != NULL)
			targetPlayer->crashClient();

		player->sendSystemMessage("Player \'" + name + "\' is banned (IP)");

	} else {
		player->sendSystemMessage("Unable to ban player \'" + name + "\' (IP)");
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
			player->sendSystemMessage("Unable to get forum account info...");
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

	if (!player->isDuelListEmpty()) {
		//Using this command while dueling is causing a deadlock!
		player->sendSystemMessage("You can't use @kill while dueling.");
		return;
	}

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

	if (targetPlayer != player)
		player->unlock();

	if (targetPlayer != NULL) {
		try {
			if (targetPlayer != player)
				targetPlayer->wlock();

			targetPlayer->explode(2, false);
			targetPlayer->die();

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
	} else if (creature != NULL && creature->getOptionsBitmask() != 0x108 && creature->getOptionsBitmask() != 0x1080) {
		try {
			creature->wlock();

			creature->explode(2, false);
			uint damage = 100000000;

			player->inflictDamage(creature, CreatureAttribute::HEALTH, damage);

			creature->unlock();

		} catch (...) {
			creature->unlock();
		}

	}

	if (targetPlayer != player)
		player->wlock();
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
	if (creature != NULL && creature->getOptionsBitmask() != 0x108 && creature->getOptionsBitmask() != 0x1080) {
		try {
			creature->wlock(player);

			creature->explode(2, false);
			uint damage = 100000000;

			player->inflictDamage(creature, CreatureAttribute::HEALTH, damage);

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
			ManagedReference<SceneObject> obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

			if (obj->isPlayer()) {
				Player* otherPlayer = (Player*) obj.get();
				String otherName = otherPlayer->getFirstName();

				if (otherName != name && player->isInRange(otherPlayer, meter)
						&& (otherPlayer->getAdminLevel()
								== PlayerImplementation::NORMAL)) {
					zone->unlock();

					if (otherPlayer != player)
						player->unlock();

					try {
						if (otherPlayer != player)
							otherPlayer->wlock();

						otherPlayer->explode(2, false);
						otherPlayer->die();

						if (otherPlayer != player)
							otherPlayer->unlock();

						player->sendSystemMessage("player \'" + otherName
								+ "\' has been killed.");
					} catch (...) {
						if (otherPlayer != player)
							otherPlayer->unlock();
						player->sendSystemMessage("Unable to kill player \'"
								+ otherName + "\'");
					}

					if (otherPlayer != player)
						player->wlock();

					zone->lock();
				}
			} else if (obj->isNonPlayerCreature()) {

				Creature* creature = (Creature*) obj.get();

				//if (creature->isInRange(creature, meter) && !creature->isTrainer() && !creature->isRecruiter()) {
				if (player->isInRange(creature, meter) && creature->getOptionsBitmask() != 0x108 && creature->getOptionsBitmask() != 0x1080) {
					zone->unlock();

					try {
						uint32 damage = 100000000;

						creature->wlock(player);

						creature->explode(2, false);
						player->inflictDamage(creature, CreatureAttribute::HEALTH, damage);
						player->sendSystemMessage("Creature has been killed.");

						creature->unlock();
					} catch (...) {
						player->sendSystemMessage("Unable to kill creature");
						creature->unlock();
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
		System::out << "Unreported exception caught in GameCommandHandler::muteChat()\n";
	}
}

void GameCommandHandler::users(StringTokenizer tokenizer, Player* player) {
	ZoneServer * server = player->getZone()->getZoneServer();

	StringBuffer msg;
	msg << server->getConnectionCount() << " users connected";

	player->sendSystemMessage(msg.toString());
}

void GameCommandHandler::setWeather(StringTokenizer tokenizer, Player* player) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	PlanetManager* planet = zone->getPlanetManager();
	if (planet == NULL)
		return;

	int weatherID;

	if (tokenizer.hasMoreTokens()) {
		weatherID = tokenizer.getIntToken();
	} else {
		player->sendSystemMessage("Usage example: @setWeather 3");
		player->sendSystemMessage("Weather ID must be 0-4.");
		return;
	}

	if (zone->getZoneID() > 9) {
		player->sendSystemMessage("You can't change the weather here.");
		return;
	}

	if (weatherID >= 0 && weatherID < 5) {
		try {
			player->unlock();

			zone->setWeatherID(weatherID);
			planet->weatherUpdatePlayers();
			player->sendSystemMessage("Weather has been set.");

			player->wlock();

		} catch (...) {
			player->wlock();
			System::out << "Unreported Exception in GameCommandHandler::setWeather()\n";
		}

	} else {
		player->sendSystemMessage("Weather ID must be 0-4.");
		return;
	}
}

void GameCommandHandler::enableWeather(StringTokenizer tokenizer, Player * player) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	PlanetManager* planet = zone->getPlanetManager();
	if (planet == NULL)
		return;

	if (zone->getZoneID() > 9) {
		player->sendSystemMessage("You can't change the weather here.");
		return;
	}

	if (zone->isWeatherEnabled()) {
		player->sendSystemMessage("Weather on this planet is already enabled.");
		return;

	} else {
		try {
			player->unlock();

			zone->setWeatherEnabled(true);
			planet->weatherChange();
			player->sendSystemMessage("Weather on this planet is now enabled.");

			player->wlock();

		} catch (...) {
			player->wlock();
			System::out << "Unreported Exception in GameCommandHandler::enableWeather()\n";
		}
	}
}

void GameCommandHandler::disableWeather(StringTokenizer tokenizer, Player * player) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	PlanetManager* planet = zone->getPlanetManager();
	if (planet == NULL)
		return;

	if (zone->getZoneID() > 9) {
		player->sendSystemMessage("You can't change the weather here.");
		return;
	}

	if (!zone->isWeatherEnabled()) {
		player->sendSystemMessage("Weather on this planet is already disabled.");
		return;

	} else {
		try {
			player->unlock();

			zone->setWeatherEnabled(false);
			zone->setWeatherID(0);
			planet->weatherUpdatePlayers();
			planet->weatherRemoveEvents();
			player->sendSystemMessage("Weather on this planet is now disabled.");

			player->wlock();

		} catch (...) {
			player->wlock();
			System::out << "Unreported Exception in GameCommandHandler::disableWeather()\n";
		}
	}
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

		targetPlayer->awardBadge(badgeid);

		if (targetPlayer != player)
			targetPlayer->unlock();
	} else
		player->sendSystemMessage("Invalid target.");
}

void GameCommandHandler::revokeBadge(StringTokenizer tokenizer, Player* player) {
	int badgeid = tokenizer.getIntToken();
	CreatureObject* target = (CreatureObject*) player->getTarget();

	if (target != NULL && target->isPlayer()) {
		Player* targetPlayer = (Player*) target;

		if (targetPlayer != player)
			targetPlayer->wlock(player);

		targetPlayer->removeBadge(badgeid);

		if (targetPlayer != player)
			targetPlayer->unlock();
	} else
		player->sendSystemMessage("Invalid target.");
}

void GameCommandHandler::systemMessage(StringTokenizer tokenizer, Player* player) {
	uint32 range = 0;

	try {
		if (tokenizer.hasMoreTokens())
			range = tokenizer.getIntToken();

		if (!tokenizer.hasMoreTokens()) {
			player->sendSystemMessage("Error sending systemMessage - Usage: systemMessage RANGE TEXT");
			return;
		}

		ChatManager * chatManager = player->getZone()->getChatManager();

		StringBuffer message;
		String msg;
		message << "System Message from " << player->getFirstName() << ": ";

		while (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(msg);
			message << msg << " ";
		}

		if (range == 0)
			chatManager->broadcastMessage(message.toString());
		else
			chatManager->broadcastMessageRange(player, message.toString(), range);

	} catch (...) {
		player->sendSystemMessage("Error sending systemMessage - Usage: systemMessage RANGE TEXT");
	}
}

void GameCommandHandler::eventMessage(StringTokenizer tokenizer, Player* player) {
	String message;
	try {
		ChatManager * chatManager = player->getZone()->getChatManager();

		StringBuffer message;
		String msg;
		message << "[\\#ffaa33\\Event\\#ffffff\\] ";

		while (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(msg);
			message << msg << " ";
		}

		System::out << message.toString() << endl;
		chatManager->broadcastMessage(message.toString());

	} catch (...) {
		player->sendSystemMessage("Error sending eventMessage - Usage: @systemMessage <message>");
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
	player->getCustomizationString(appearance);

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

	((CreatureObject*) player)->setCustomizationVariable(variable, (uint8)value);

	StringBuffer message;
	message << "Character Appearance Attribute Updated.";
	player->sendSystemMessage(message.toString());
}

void GameCommandHandler::HAMStats(StringTokenizer tokenizer, Player* player) {
	StringBuffer message;

	message << "Health:  " << player->getHealth() << "/"
			<< player->getHealthMax() << "/" << player->getBaseHealth() <<"/" << player->getHealthWounds() << ".";
	message << " Action:  " << player->getAction() << "/"
			<< player->getActionMax() << "/" << player->getBaseAction()<< "/" << player->getActionWounds() << ".";
	message << " Mind:  " << player->getMind() << "/" << player->getMindMax()
			<< "/" << player->getBaseMind() << "/"<< player->getMindWounds()<< ".";

	message << " Strength:  " << player->getStrength() << "/"
			<< player->getStrengthMax() << "/" << player->getBaseStrength()
			<< "/" << player->getStrengthWounds() << ".";
	message << " Constitution:  " << player->getConstitution() << "/"
			<< player->getConstitutionMax() << "/"
			<< player->getBaseConstitution() << "/" << player->getConstitutionWounds() << ".";

	message << " Quickness:  " << player->getQuickness() << "/"
			<< player->getQuicknessMax() << "/" << player->getBaseQuickness()
			<< "/" << player->getQuicknessWounds() << ".";
	message << " Stamina:  " << player->getStamina() << "/"
			<< player->getStaminaMax() << "/" << player->getBaseStamina()
			<< "/" << player->getStaminaWounds() << ".";

	message << " Focus:  " << player->getFocus() << "/"
			<< player->getFocusMax() << "/" << player->getBaseFocus() << ".";
	message << " Willpower:  " << player->getWillpower() << "/"
			<< player->getWillpowerMax() << "/" << player->getBaseWillpower()
			<< "/" << player->getWillpowerWounds() << ".";

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

	//If the player has a target, the target player is buffed
	//This function is for developers (privileged) so they can re-buff
	//players which lost buffs due to bugs or participate in stress test
	//and can't find someone buffing them.

	Player* targetPlayer;
	Player* buffie;

	buffie = player;

	try {
		SceneObject* obj = player->getTarget();

		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;

			if (targetPlayer != NULL && targetPlayer != player) {
				buffie = targetPlayer;
				buffie->wlock(player);
			}
		}

		int buffValue = 2750;

		if (devBuff > 0 )
			buffValue = devBuff;


		if ( (buffie->getHealthMax() == buffie->getBaseHealth()) || (devBuff > 0)  ) {
			//Heal wounds at first
			buffie->changeActionWoundsBar(-1500);
			buffie->changeConstitutionWoundsBar(-1500);
			buffie->changeHealthWoundsBar(-1500);
			buffie->changeMindWoundsBar(-1500);
			buffie->changeQuicknessWoundsBar(-1500);
			buffie->changeStaminaWoundsBar(-1500);
			buffie->changeStrengthWoundsBar(-1500);
			buffie->changeWillpowerWoundsBar(-1500);
			buffie->changeFocusWoundsBar(-1500);
			buffie->changeShockWounds(-1000);

			//now buff
			float buffDuration = 10800.0f;

			Buff *buff; //pointer for each buff
			BuffObject *bo; //distributed object that contains the payload

			// Health
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_HEALTH, BuffType::MEDICAL, buffDuration);
			buff->setHealthBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			// Strength
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_STRENGTH, BuffType::MEDICAL, buffDuration);
			buff->setStrengthBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			// Constitution
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_CONSTITUTION, BuffType::MEDICAL, buffDuration);
			buff->setConstitutionBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			// Action
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_ACTION, BuffType::MEDICAL, buffDuration);
			buff->setActionBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			// Quickness
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_QUICKNESS, BuffType::MEDICAL, buffDuration);
			buff->setQuicknessBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			// Stamina
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_STAMINA, BuffType::MEDICAL, buffDuration);
			buff->setStaminaBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			// Mind
			buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_DANCE_MIND, BuffType::PERFORMANCE, buffDuration);
			buff->setMindBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_MUSIC_FOCUS, BuffType::PERFORMANCE, buffDuration);
			buff->setFocusBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_MUSIC_WILLPOWER, BuffType::PERFORMANCE, buffDuration);
			buff->setWillpowerBuff(buffValue);
			bo = new BuffObject(buff);
			buffie->applyBuff(bo);

			player->sendSystemMessage("Buffs applied and you feel no fatigue");

		} else {
			player->sendSystemMessage("Already buffed");
		}

		if (buffie != player)
			buffie->unlock();

	} catch (...) {
		if (buffie != player)
			buffie->unlock();

		player->sendSystemMessage("Error buffing player.");
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
	ss << " oY: " << target->getDirectionY() << endl << "oW: "
	   << target->getDirectionW();
	player->sendSystemMessage(ss.toString());
}

void GameCommandHandler::setAdminLevel(StringTokenizer tokenizer, Player* player) {
	ChatManager* chatManager = player->getZone()->getChatManager();

	String name;
	int level;

	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(name);
	} else {
		player->sendSystemMessage("Usage: @setAdminLevel <player> <level>");
		return;
	}

	if (tokenizer.hasMoreTokens()) {
		level = tokenizer.getIntToken();
	} else {
		player->sendSystemMessage("Usage: @setAdminLevel <player> <level>");
		return;
	}

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

		StringBuffer query;
		query << "UPDATE characters SET " << "adminLevel ='"
		  << level
		  << "' WHERE firstname=\'" << name << "\';";

		ServerDatabase::instance()->executeStatement(query);

		player->sendSystemMessage("Admin level set.");

	} else {
		player->sendSystemMessage("The specified player was not found.");
		return;
	}
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

void GameCommandHandler::getTargetLocation(StringTokenizer tokenizer, Player* player) {
	StringBuffer ss;

	SceneObject* target = player->getTarget();

	if (target != NULL) {

		ss << "planet: " << target->getZoneID() << " cell: "
				<< target->getParentID() << endl;
		ss << " X: " << target->getPositionX() << " Y: "
				<< target->getPositionY();
		ss << " Z: " << target->getPositionZ() << endl;
		ss << "oX: " << target->getDirectionX() << " oZ: "
				<< target->getDirectionZ();
		ss << "oY: " << target->getDirectionY() << " oW: "
				<< target->getDirectionW();

		player->sendSystemMessage(ss.toString());
	}
}

/*  Needs filewriter fixing, Errors on Cygwin engine/Compile.
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

	File* cordFile = new File("cords.txt");

	try {
		FileOutputStream cordWriter(cordFile);

		if ((player->getParentID() == 0)) {
			cordWriter << "spawnCreature(" << name << ", " << player->getZoneIndex()
					   << ", " << player->getPositionX() << ", "
					   << player->getPositionY() << ")\n";
		} else {
			cordWriter << "spawnCreatureInCell(" << name << ", "
					   << player->getZoneIndex() << ", " << player->getPositionX()
					   << ", " << player->getPositionZ() << ", "
					   << player->getPositionY() << ", " << player->getParentID()
					   << ")\n";
		}

		cordWriter.close();
	} catch (FileNotFoundException& e) {
	}

	delete cordFile;
}
*/

void GameCommandHandler::giveItemTemp(StringTokenizer tokenizer, Player* player) {
	//Give TANO
	if (!tokenizer.hasMoreTokens())
		return;

	String itemType;
	tokenizer.getStringToken(itemType);

	ZoneServer * server = player->getZone()->getZoneServer();
	if (server == NULL)
		return;

	if (itemType == "Holocron") {
		Holocron * item = new Holocron(player, 0x9BA06548, UnicodeString("Holocron"), "object/tangible/jedi/shared_jedi_holocron_light.iff");
		server->addObject(item);
		player->addInventoryItem(item);
		item->sendTo(player);

	} else if (itemType == "Jetpack") {
		VehicleDeed * item = new VehicleDeed(player, 0x9899666C, UnicodeString("Deed for: Jetpack"), "jetpack_deed");
		server->addObject(item);
		player->addInventoryItem(item);
		item->sendTo(player);

	} else if (itemType == "Swoop") {
		VehicleDeed * item = new VehicleDeed(player, 0x1D885457, UnicodeString("Deed for: Speederbike Swoop"), "speederbike_swoop_deed");
		server->addObject(item);
		player->addInventoryItem(item);
		item->sendTo(player);

	} else if (itemType == "ResourceDeed") {
		ResourceDeed * item = new ResourceDeed(player, 0x7D28DE23, UnicodeString("A Crate of Free Resources"), "resourceDeed");
		server->addObject(item);
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
				player->sendSystemMessage("Usage: @giveItemTemp Firework <1-8>");
				return;
			}

			server->addObject(item);
			player->addInventoryItem(item);
			item->sendTo(player);

		} else {
			player->sendSystemMessage("Please submit the Firework animation (1-8).");
		}

	} else if (itemType == "AA") {
		Attachment* item = new Attachment(player->getNewItemID(), AttachmentImplementation::ARMOR);
		item->setSkillMods(System::random(500));

		server->addObject(item);
		player->addInventoryItem(item);
		item->sendTo(player);

	} else if (itemType == "Powerup") {
		Powerup* item = new Powerup(player->getNewItemID());
		item->setPowerupStats(System::random(500));

		server->addObject(item);
		player->addInventoryItem(item);
		item->sendTo(player);

	} else if (itemType == "DotWeapon") {
		PistolRangedWeapon* item = new PistolRangedWeapon(player->getNewItemID(), 0x37DB11ED, UnicodeString("Dot CDEF Pistol"), "object/weapon/ranged/pistol/shared_pistol_cdef.iff", false);

		item->setDamageType(WeaponImplementation::ENERGY);
		item->setArmorPiercing(WeaponImplementation::NONE);
		item->setAttackSpeed(1.8f);
		item->setMinDamage(10.0f + System::random(5));
		item->setMaxDamage(35.0f + System::random(20));


		if (tokenizer.hasMoreTokens()) {
			uint64 type = 0;
			int token = tokenizer.getIntToken();
			if (token == 1)
				type = CreatureState::BLEEDING;
			if (token == 2)
				type = CreatureState::ONFIRE;
			if (token == 3)
				type = CreatureState::POISONED;
			if (token == 4)
				type = CreatureState::DISEASED;

			item->setDot0Type(type);

			int pool = System::random(3);
			int attr = 0;
			if (pool == 0)
				attr = CreatureAttribute::ACTION;
			if (pool == 1)
				attr = CreatureAttribute::MIND;
			else
				attr = CreatureAttribute::HEALTH;

			item->setDot0Attribute(attr);
			item->setDot0Uses(System::random(1000));
			item->setDot0Potency(100);
			item->setDot0Strength(System::random(100));
			item->setDot0Duration(System::random(60));
		}

		server->addObject(item);
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

		player->resuscitate(targetPlayer, true);

		targetPlayer->sendSystemMessage("You have been restored...");
		player->sendSystemMessage("You resuscitate " + name + ".");

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

void GameCommandHandler::invisible(StringTokenizer tokenizer, Player* player) {
	player->activateInvisible();
}

void GameCommandHandler::flare(StringTokenizer tokenizer, Player* player) {
	if (player->isInBuilding()) {
		player->sendSystemMessage("You can't fire a flare indoors.");
		return;
	}

	PlayClientEffectLoc* effect = new PlayClientEffectLoc("clienteffect/pl_force_resist_bleeding_self.cef", player->getZoneID(), player->getPositionX(), player->getPositionZ(), player->getPositionY());
	player->broadcastMessage(effect);
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
	bool baby = false;
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


	if (tokenizer.hasMoreTokens()) {
		baby = tokenizer.getIntToken();
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
				0, baby, true, height);

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
		StringBuffer query;

		query << "SELECT character_id,firstname,surname,adminLevel from characters where adminLevel <> 4 order by character_id asc;";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {

			StringBuffer msg, appendix;

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
				appendix << "32 (CSR JR)";
				break;
			case (64):
				appendix << "64 (EC JR)";
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

// TODO: Needs to be redone without using a variable in CombatManager
/*
void GameCommandHandler::toggleCombat(StringTokenizer tokenizer, Player * player) {
	ZoneProcessServerImplementation* srv = player->getZoneProcessServer();
	if (srv == NULL)
		return;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	CombatManager* combatManager = srv->getCombatManager();

	combatManager->toggleCombat();

	ChatManager * chatManager = zone->getChatManager();

	if (combatManager->isCombatEnabled()) {
		StringBuffer message;
		message << player->getFirstName() << " enabled Combat";

		chatManager->broadcastMessage(message.toString());
	} else {
		StringBuffer message;
		message << player->getFirstName() << " disabled Combat";

		chatManager->broadcastMessage(message.toString());
	}
}
*/

void GameCommandHandler::lockServer(StringTokenizer tokenizer, Player * player) {
	ZoneProcessServerImplementation* srv = player->getZoneProcessServer();
	if (srv == NULL)
		return;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();
	ChatManager * chatManager = zone->getChatManager();

	zoneServer->setServerStateLocked();

	StringBuffer message;
	message <<  player->getFirstName() << " locked the server";

	chatManager->broadcastMessage(message.toString());
}

void GameCommandHandler::unlockServer(StringTokenizer tokenizer, Player * player) {
	ZoneProcessServerImplementation* srv = player->getZoneProcessServer();
	if (srv == NULL)
		return;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();
	ChatManager * chatManager = zone->getChatManager();

	zoneServer->setServerStateOnline();

	StringBuffer message;
	message << player->getFirstName() << " unlocked the server";

	chatManager->broadcastMessage(message.toString());

}

void GameCommandHandler::poofObject(StringTokenizer tokenizer, Player * player) {
	SceneObject* obj = player->getTarget();
	uint64 oid;

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	if (obj == NULL || obj->isPlayer()) {
		player->sendSystemMessage("This object was not dropped by a player - it can't be deleted!");
		return;
	}

	player->unlock();

	try {
		obj->wlock();

		oid = obj->getObjectID();

		StringBuffer query;

		query << "SELECT item_id FROM player_storage WHERE item_id = '" << oid << "';";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		if (!res->next()) {
			player->sendSystemMessage("This object was not dropped by a player - it can't be deleted!");
			obj->unlock();
			player->wlock();
			return;
		}

		delete res;

		query.deleteAll();
		query << "DELETE FROM player_storage WHERE item_id = " << oid << " or container = " << oid << ";";
		ServerDatabase::instance()->executeStatement(query);


		if (((TangibleObject*) obj)->isContainer()) {
			Container* container = (Container*) obj;

			while (!container->isContainerEmpty()) {
				SceneObject* sco = container->getObject(0);

				container->removeObject(0);

				sco->removeFromZone(true);
			}
		}

		obj->removeFromZone(true);

		obj->unlock();
	} catch (DatabaseException& e) {
		player->info("Database Exception in GameCommandHandler::poofObject(StringTokenizer tokenizer, Player * player)");
		player->info(e.getMessage());
		System::out << e.getMessage() << endl;
		obj->unlock();

	} catch (...) {
		player->info("Unreported Exception in GameCommandHandler::poofObject(StringTokenizer tokenizer, Player * player)");
		obj->unlock();
	}

	player->wlock();
}

void GameCommandHandler::whoDroppedThis(StringTokenizer tokenizer, Player * player) {
	SceneObject* obj = player->getTarget();

	if (obj == NULL || obj->isPlayer())
		return;

	uint64 oid = 0;

	try {
		obj->wlock(player);

		oid = obj->getObjectID();

		obj->unlock();

	} catch (...) {
		obj->unlock();
		player->info("Unreported Exception in GameCommandHandler::whoDroppedThis(StringTokenizer tokenizer, Player * player)\n");
		return;
	}

	StringBuffer itemInfo, msg;

	itemInfo << "SELECT player_storage.dropped_by_character, characters.firstname "
			<< "FROM player_storage "
			<< "Inner Join characters ON player_storage.dropped_by_character = characters.character_id "
			<< "Where item_id = " << oid << ";";

	try {
		ResultSet* res = ServerDatabase::instance()->executeQuery(itemInfo);

		if (res->next()) {
			msg.deleteAll();
			msg << "This item was dropped by character ID: " << res->getInt(0) << "    Charactername: " << res->getString(1);

			player->sendSystemMessage(msg.toString());
		}

		delete res;

	} catch (DatabaseException& e) {
		player->info("Database Exception in GameCommandHandler::whoDroppedThis(StringTokenizer tokenizer, Player * player)");
		player->info(e.getMessage());
		System::out << e.getMessage() << endl;
	} catch (...) {
		player->info("Unreported Exception in GameCommandHandler::whoDroppedThis(StringTokenizer tokenizer, Player * player)");
	}
}

void GameCommandHandler::sendp(StringTokenizer tokenizer, Player* player) {
	//TESTING PURPOSES ULTYMAS.
	player->savePlayerState(false);
	player->sendSystemMessage("char saved");

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
	LaunchBrowserMessage* lbm = new LaunchBrowserMessage("http://www.swgemu.com/forums/forumdisplay.php?f=137");
	player->sendMessage(lbm);
}

void GameCommandHandler::bug(StringTokenizer tokenizer, Player * player) {
	LaunchBrowserMessage* lbm = new LaunchBrowserMessage("http://www.swgemu.com/bugs");
	player->sendMessage(lbm);
}

void GameCommandHandler::openInventory(StringTokenizer tokenizer, Player * player) {
	Player* targetPlayer;

	try {
		SceneObject* obj = player->getTarget();

		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;
		} else {
			player->sendSystemMessage("Usage: @openInventory <with a player as the current target>\n");
			return;
		}


		if (targetPlayer == player || targetPlayer == NULL)
			return;

		targetPlayer->wlock(player);

		Container* othersInventory = targetPlayer->getInventory();

		if (othersInventory != NULL) {
			othersInventory->sendTo(player);
			othersInventory->sendItemsTo(player);
			othersInventory->openTo(player);
		}

		StringBuffer devLog;
		devLog << "Player " << player->getFirstName() << " is using @openInventory on player "
			   << targetPlayer->getFirstName() << "\n";

		player->info(devLog.toString(), true);

		targetPlayer->unlock();

	} catch (...) {
		System::out << "Unreported exception caught in GameCommandHandler::openInventory(StringTokenizer tokenizer, Player * player)";
		targetPlayer->unlock();
	}
}

void GameCommandHandler::freezePlayer(StringTokenizer tokenizer, Player* player) {
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

		//By right here, we should have a player object. or not.
				try {
					if (targetPlayer != player)
						targetPlayer->wlock(player);

					targetPlayer->updateSpeed(0,0);

					targetPlayer->setFrozen(true);

					CreatureObjectDeltaMessage6* codm = new CreatureObjectDeltaMessage6(targetPlayer);
					codm->setFrozen(true);
					codm->close();
					player->broadcastMessage(codm);

					targetPlayer->sendSystemMessage(
							"You have been frozen by \'"
									+ player->getFirstName() + "\'.");
					player->sendSystemMessage("You have frozen \'" + name
							+ "\'.");

					if (targetPlayer != player)
						targetPlayer->unlock();

				} catch (...) {
					if (targetPlayer != player)
						targetPlayer->unlock();
				}


}

void GameCommandHandler::unfreezePlayer(StringTokenizer tokenizer, Player* player) {
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

			//By right here, we should have a player object. or not.
					try {
						if (targetPlayer != player)
							targetPlayer->wlock(player);

						targetPlayer->updateSpeed(5.376, 1.549f);

						targetPlayer->setFrozen(false);

						CreatureObjectDeltaMessage6* codm = new CreatureObjectDeltaMessage6(targetPlayer);
						codm->setFrozen(false);
						codm->close();
						player->broadcastMessage(codm);

						targetPlayer->sendSystemMessage(
								"You have been unfrozen by \'"
										+ player->getFirstName() + "\'.");
						player->sendSystemMessage("You have unfrozen \'" + name
								+ "\'.");

						if (targetPlayer != player)
							targetPlayer->unlock();

					} catch (...) {
						if (targetPlayer != player)
							targetPlayer->unlock();
					}


}

void GameCommandHandler::changeTemplate(StringTokenizer tokenizer, Player* player) {
	String newTemplateString;

	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(newTemplateString);
	} else {
		player->sendSystemMessage("Usage: @changeTemplate [string]");
		return;
	}

	player->setTemplateString(newTemplateString);

	CreatureObjectDeltaMessage6* codm = new CreatureObjectDeltaMessage6(player);
	codm->updateTemplateString();
	codm->close();
	player->broadcastMessage(codm);
}

void GameCommandHandler::setSpeed(StringTokenizer tokenizer, Player* player) {
	Player* targetPlayer;
	SceneObject* obj = player->getTarget();
		if (obj != NULL && obj->isPlayer()) {
			targetPlayer = (Player*) obj;
		} else {
			return;
		}
		//Now we want to make sure theres more tokens.
		if (!tokenizer.hasMoreTokens())
			return;

		float speed = tokenizer.getFloatToken();

		if (!tokenizer.hasMoreTokens())
				return;

		float acceleration = tokenizer.getFloatToken();

		int defaultFlag;
		defaultFlag = 0;
		if (tokenizer.hasMoreTokens()) {
			defaultFlag = tokenizer.getIntToken();
		}


		//By right here, we should have a player object. or not.
		try {
			if (targetPlayer != player)
				targetPlayer->wlock(player);

			if (defaultFlag == 0) {
				targetPlayer->updateSpeed(speed, acceleration);
				targetPlayer->sendSystemMessage("Your speed has been changed.");
				player->sendSystemMessage("You have changed their speed.");
			} else {
				targetPlayer->updateSpeed(5.376, 1.549f);
				targetPlayer->sendSystemMessage("Your speed has been defaulted back to normal.");
				player->sendSystemMessage("You have changed their speed back to default.");
			}

			if (targetPlayer != player)
				targetPlayer->unlock();

		} catch (...) {
			if (targetPlayer != player)
				targetPlayer->unlock();
		}

}

void GameCommandHandler::setHeight(StringTokenizer tokenizer, Player* player) {
	CreatureObject* targetObject;
	SceneObject* obj = player->getTarget();
		if (obj != NULL) {
			targetObject = (CreatureObject*) obj;
		} else {
				return;
		}

		if (!tokenizer.hasMoreTokens())
				return;

		float height = tokenizer.getFloatToken();


		//By right here, we should have a player object. or not.
							try {
								if (targetObject != player)
									targetObject->wlock(player);

								targetObject->setHeight(height);

								CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(targetObject);
								dcreo3->updateHeight();
								dcreo3->close();
								player->broadcastMessage(dcreo3);

								//targetObject->sendSystemMessage("Your height has been changed.");
								player->sendSystemMessage("You have changed their height.");

								if (targetObject != player)
									targetObject->unlock();

							} catch (...) {
								if (targetObject != player)
									targetObject->unlock();
							}

}

void GameCommandHandler::warpAreaToWP(StringTokenizer tokenizer, Player* player) {
	float x,y;
	String wpName;

	if (!tokenizer.hasMoreTokens())
		return;
	tokenizer.getStringToken(wpName);

	if (!tokenizer.hasMoreTokens())
		return;
		int meter = tokenizer.getIntToken();

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

		String name = player->getFirstName();

		Zone* zone = player->getZone();
		if (zone == NULL)
			return;

		try {
			zone->lock();

			for (int i = 0; i < player->inRangeObjectCount(); ++i) {
				SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

				if (obj->isPlayer()) {
					Player* otherPlayer = (Player*) obj;
					String otherName = otherPlayer->getFirstName();

					if (otherName != name && player->isInRange(otherPlayer,meter)
							&& (otherPlayer->getAdminLevel() == PlayerImplementation::NORMAL)) {
						zone->unlock();

						if (otherPlayer != player)
							player->unlock();

						try {
							if (otherPlayer != player)
								otherPlayer->wlock();

							if (planet != otherPlayer->getZoneIndex())
								otherPlayer->switchMap(planet);

							otherPlayer->doWarp(x, y);

							player->sendSystemMessage("player \'" + otherName + "\' has been warped.");

							if (otherPlayer != player)
								otherPlayer->unlock();
						} catch (...) {
							player->sendSystemMessage("Unable to warp player \'" + otherName + "\'");
							if (otherPlayer != player)
								otherPlayer->unlock();
						}

						if (otherPlayer != player)
							player->wlock();

						zone->lock();
					}
				}
			}
			zone->unlock();
		} catch (...) {
			zone->unlock();
		}
	}
}

void GameCommandHandler::scaleXP(StringTokenizer tokenizer, Player* player) {
	int scale;

	ZoneProcessServerImplementation* srv = player->getZoneProcessServer();
	if (srv == NULL)
		return;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	PlayerManager* pmng = srv->getPlayerManager();
	if (pmng == NULL)
		return;

	if (!tokenizer.hasMoreTokens())
		return;

	scale = tokenizer.getIntToken();

	pmng->setXpScale(scale);

	ChatManager * chatManager = zone->getChatManager();

	StringBuffer message;
	message << player->getFirstNameProper() << " set XP scale to " << scale << ".";
	chatManager->broadcastMessage(message.toString());
}

void GameCommandHandler::spawnAA(StringTokenizer tokenizer, Player* player) {
	Zone* zone = player->getZone();
	PlanetManager * planetManager = zone->getPlanetManager();

	float x, y, z, range;


	if (tokenizer.hasMoreTokens()) {
		x = tokenizer.getFloatToken();
	} else {
		return;
	}

	if (tokenizer.hasMoreTokens()) {
		y = tokenizer.getFloatToken();
	} else {
		return;
	}

	if (tokenizer.hasMoreTokens()) {
		z = tokenizer.getFloatToken();
	} else {
		return;
	}

	if (tokenizer.hasMoreTokens()) {
		range = tokenizer.getFloatToken();
	} else {
		return;
	}

	TestActiveArea * testArea = new TestActiveArea(x,y,z,range);

	planetManager->spawnActiveArea(testArea);
}


void GameCommandHandler::setLocation(StringTokenizer tokenizer, Player* player) {
	SceneObject* obj;
	try {
		CampSite* camp = player->getCamp();

		if (camp == NULL)
			return;

		int num = 0;

		if (tokenizer.hasMoreTokens())
			num = tokenizer.getIntToken();
		else
			return;

		camp->wlock();

		obj = camp->getCampObject(num);

		float x = camp->getPositionX();
		float y = camp->getPositionY();
		float z = camp->getPositionZ();

		Zone* zone = camp->getOwner()->getZone();

		camp->unlock();

		if (obj == NULL)
			return;

		obj->wlock(player);

		float oX = 0;
		float oY = 0;
		float oW = 0;

		float diffX = x - player->getPositionX();
		float diffY = y - player->getPositionY();

		if (tokenizer.hasMoreTokens())
			diffX = tokenizer.getFloatToken();
		if (tokenizer.hasMoreTokens())
			diffY = tokenizer.getFloatToken();

		if (tokenizer.hasMoreTokens())
			oX = tokenizer.getFloatToken();
		if (tokenizer.hasMoreTokens())
			oY = tokenizer.getFloatToken();
		if (tokenizer.hasMoreTokens())
			oW = tokenizer.getFloatToken();

		obj->removeFromZone();

		obj->initializePosition((x + diffX), z, (y + diffY));
		obj->setDirection(oX,0,oY,oW);

		obj->insertToZone(zone);

		obj->unlock();
	} catch (...) {
		obj->unlock();
	}
}

void GameCommandHandler::drag(StringTokenizer tokenizer, Player* player) {
	SceneObject* obj = player->getTarget();
	Player* targetPlayer;

	if (obj == NULL) {
		player->sendSystemMessage("healing_response", "healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
		return;
	}

	if (obj->isPlayer()) {
		targetPlayer = (Player*)obj;

		if (targetPlayer == player) {
			player->sendSystemMessage("healing_response", "healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return;
		} else {
			targetPlayer->wlock(player);

			player->drag(targetPlayer, 128.0f, 20.0f, false, true);

			targetPlayer->unlock();
		}

	} else {
		player->sendSystemMessage("healing_response", "healing_response_a6"); //"You may only drag players!"
		return;
	}
}

void GameCommandHandler::damage(StringTokenizer tokenizer, Player* player) {
	SceneObject* obj = player->getTarget();
	CreatureObject* target;

	if (obj == NULL) {

		return;
	}

	if (obj->isPlayer() || obj->isNonPlayerCreature()) {

		target = (CreatureObject*) obj;

		player->inflictDamage(target, CreatureAttribute::HEALTH, 500);
		player->inflictDamage(target, CreatureAttribute::ACTION, 500);

	}
}
void GameCommandHandler::applyDot(StringTokenizer tokenizer, Player* player) {
	SceneObject* obj = player->getTarget();
	CreatureObject* target;


	if (obj == NULL) {

		return;
	}

	uint8 attr = CreatureAttribute::HEALTH;
	uint64 type = CreatureState::BLEEDING;
	uint32 bleedingDotStrength = 50;

	if (tokenizer.hasMoreTokens()) {
		int token = tokenizer.getIntToken();
		if (token == 1)
			type = CreatureState::BLEEDING;
		if (token == 2)
			type = CreatureState::ONFIRE;
		if (token == 3)
			type = CreatureState::POISONED;
		if (token == 4)
			type = CreatureState::DISEASED;
	}

	if (tokenizer.hasMoreTokens())
		attr = tokenizer.getIntToken();

	if (tokenizer.hasMoreTokens())
		bleedingDotStrength = tokenizer.getIntToken();

	if (obj->isPlayer() || obj->isNonPlayerCreature()) {

		target = (CreatureObject*) obj;

		target->addDotState(player,System::random(10000),type, bleedingDotStrength, attr, 60,50,0);

	}
}

void GameCommandHandler::deleteFromZone(StringTokenizer tokenizer, Player* player) {
	SceneObject* obj = player->getTarget();

	if (obj == NULL) {
		return;
	}

	obj->removeFromZone(true);
	obj->finalize();
}

void GameCommandHandler::playAudio(StringTokenizer tokenizer, Player* player) {
	//SceneObject* obj = player->getTarget();

	//if (obj == NULL) {
	//	return;
	//}
	String audioFile;

		if (!tokenizer.hasMoreTokens())
			return;
		tokenizer.getStringToken(audioFile);

	PlayMusicMessage* pmm = new PlayMusicMessage(audioFile);
	player->sendMessage(pmm);

}

void GameCommandHandler::setMOTD(StringTokenizer tokenizer, Player * player) {

	SuiInputBox* suiInpBox = new SuiInputBox(player, SuiWindowType::SET_MOTD, 0);

	suiInpBox->setPromptTitle("Set MOTD");
	suiInpBox->setPromptText("Input the new message of the day below. (char limit 1024)");
	suiInpBox->setCancelButton(true, "");
	suiInpBox->setMaxInputSize(1024);

	player->addSuiBox(suiInpBox);
	player->sendMessage(suiInpBox->generateMessage());

}

void GameCommandHandler::displayMOTD(StringTokenizer tokenizer, Player* player) {
	player->displayMessageoftheDay();
}

void GameCommandHandler::eventCloner(StringTokenizer tokenizer, Player* player) {
	bool decayItems = true;
	bool giveWounds = true;
	uint32 buffAmount = 0;
	String faction = "neutral";

	if (tokenizer.hasMoreTokens())
		decayItems = (bool) tokenizer.getIntToken();

	if (tokenizer.hasMoreTokens())
		giveWounds = (bool) tokenizer.getIntToken();

	if (tokenizer.hasMoreTokens())
		buffAmount = (uint32) tokenizer.getIntToken();

	if (tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);

		if (token == "rebel" || token == "neutral" || token == "imperial")
			faction = token;
	}

	//Create the temp cloner
	//Put it in the world at the current players location
	//Set the options it has
}

