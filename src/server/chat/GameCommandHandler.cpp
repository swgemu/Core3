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

#include "ChatManager.h"

#include "../zone/managers/guild/GuildManager.h"
#include "../zone/managers/planet/PlanetManager.h"
#include "../zone/managers/structure/StructureManager.h"
#include "../zone/managers/combat/CombatManager.h"
#include "../zone/managers/mission/MissionManager.h"

GMCommandMap* GameCommandHandler::gmCommands = NULL;

void GameCommandHandler::init() {
	/* Admin Levels */
	const int DEVELOPER = 2; 	/* Admin/Dev  */
	const int CSR = 1;			/* CSR */
	const int EC = 4;			/* Event Coordinator */
	const int QA = 8;			/* Quality Assurance */
	const int NORMAL = 0;		/* Normal Player*/

	/* Admin Groups */
	const int ALL = DEVELOPER | CSR | EC | QA | NORMAL;	/* All Staff/Players */
	const int STAFF = DEVELOPER | CSR | EC | QA;		/* Staff Only */
	const int PRIVILEGED = DEVELOPER | CSR;				/* Admin,Dev/CSR */
	const int CSREVENTS = DEVELOPER | CSR | EC;			/* Admin,Dev/CSR/Event Coordinator */

	//TODO: We should script access levels and assign them to forum usergroups, and then script the
	//Access levels for the game commands. But can we still come up with a function pointer that way?

	gmCommands = new GMCommandMap();

	/*
	gmCommands->addCommand("commands", ALL,
			"Prints a list of commands.",
			"Usage: @commands [command]",
			&commands);
	gmCommands->addCommand("build", ALL,
			"Prints SVN build.",
			"Usage: @build",
			&buildInfo);
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
	gmCommands->addCommand("warpPlayer", PRIVILEGED,
			"Warps a player to a given location.",
			"Usage: @warpPlayer <player> <starport | hotel | shuttle | medical | bank | garage | salon | punish>",
			&warpPlayer);
	gmCommands->addCommand("summon", CSREVENTS,
			"Warps a player to your location.",
			"Usage: @summon <player>",
			&summon);
	gmCommands->addCommand("kick", PRIVILEGED,
			"Disconnects a player from the game.",
			"Usage: @kick <player>",
			&kick);
	gmCommands->addCommand("kickArea", PRIVILEGED,
			"Disconnects all players in a certain range.",
			"Usage: @kickArea [distance]",
			&kickArea);
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
			"Kills a player or creature.",
			"Usage: @kill <player name or current-target>",
			&kill);
	gmCommands->addCommand("ecKill", STAFF,
			"Kills a creature. EC version of the kill command.",
			"Usage: @ecKill <current-target>",
			&ecKill);
	gmCommands->addCommand("killArea", STAFF,
			"Kills all players or creatures within a certain range.",
			"Usage: @killArea <players> <distance>",
			&killArea);
	gmCommands->addCommand("muteChat", CSREVENTS,
			"Prevents players from speaking in spacial chat.",
			"Usage: @muteChat",
			&muteChat);
	gmCommands->addCommand("users", STAFF,
			"Prints the amount of users on the server.",
			"Usage: @users",
			&users);
	gmCommands->addCommand("setWeather", CSREVENTS,
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
	gmCommands->addCommand("awardBadge", CSREVENTS,
			"Awards a badge to targeted player.",
			"Usage: @awardBadge <badgeid>",
			&awardBadge);
	gmCommands->addCommand("revokeBadge", CSREVENTS,
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
	gmCommands->addCommand("buff", STAFF,
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
	gmCommands->addCommand("giveItemTemp", CSREVENTS | QA,
			"Adds a requested item to your inventory.",
			"Usage: @giveItemTemp <Item Type> [item sub-type]",
			&giveItemTemp);
	gmCommands->addCommand("clientEffect", CSREVENTS,
			"Plays a client effect animation around your character.",
			"Usage: @clientEffect <effect>",
			&clientEffect);
	gmCommands->addCommand("rez", STAFF,
			"Resurrects a player.",
			"Usage: @rez <playername or target player>",
			&rez);
	gmCommands->addCommand("immune", STAFF,
			"Toggles immunity.",
			"Usage: @immune",
			&immune);
	gmCommands->addCommand("invisible", PRIVILEGED ,
			"Toggles invisibility",
			"Usage: @invisible",
			&invisible);
	gmCommands->addCommand("flare", CSREVENTS,
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
	gmCommands->addCommand("factionSet", CSREVENTS,
			"Let you change a players faction. Will be applied IMMEDIATLY!",
			"Usage: @factionSet overt | covert | rebel | imperial | neutral",
			&factionSet);
	gmCommands->addCommand("getCredits", CSREVENTS,
			"Gives you cash credits",
			"Usage: @getCredits [amount]",
			&getCredits);
	gmCommands->addCommand("getXP", DEVELOPER | QA,
			"Gives you specified type of experience",
			"USAGE: @getXP [type] [amount]",
			&getXP);
	gmCommands->addCommand("adjustFP", DEVELOPER | QA,
			"Adjusts your faction points for specified faction",
			"USAGE: @adjustFP [faction] [points]",
			&adjustFP);
	gmCommands->addCommand("adminList", PRIVILEGED,
			"Returns a list of players with a level higher than normal (4)",
			"USAGE: @adminList",
			&adminList);
	gmCommands->addCommand("showChars", PRIVILEGED,
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
	gmCommands->addCommand("poofObject", PRIVILEGED,
			"Destroys an object.",
			"USAGE: @poofObject <target>",
			&poofObject);
	//Temporary for CSRs as long as structures and cell permissions not finally in
	gmCommands->addCommand("whoDroppedThis", PRIVILEGED,
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
	gmCommands->addCommand("rebelMessage", STAFF,
					"Sends a system message to all members of the Rebellion",
					"USAGE: @rebelMessage <message>",
					&rebelMessage);
	gmCommands->addCommand("imperialMessage", STAFF,
					"Sends a system message, to all members of the Empire.",
					"USAGE: @imperialMessage <message>",
					&imperialMessage);
	gmCommands->addCommand("eventMessage", STAFF,
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
	gmCommands->addCommand("deletePlayer", DEVELOPER,
				"Deletes target player from database",
				"USAGE: @deletePlayer <player first name>",
				&deletePlayer);
	gmCommands->addCommand("storeVehicle", CSREVENTS,
				"Stores the targeted vehicle",
				"USAGE: @storeVehicle <target vehicle>",
				&storeVehicle);
	gmCommands->addCommand("clearMissions", PRIVILEGED,
				"Clears mission vars for a player, in the event they are having problems",
				"USAGE: @clearMissions <player name>",
				&clearMissions);
 	gmCommands->addCommand("growUpPet", PRIVILEGED,
				"growUpPet",
				"USAGE: @growUpPet",
				&growUpPet);

 	gmCommands->addCommand("growUpPet", PRIVILEGED,
				"growUpPet",
				"USAGE: @growUpPet",
				&growUpPet);

	 gmCommands->addCommand("woundPet", DEVELOPER,
				"woundPet",
				"USAGE: @woundPet",
				&woundPet);

	 gmCommands->addCommand("changePetDatapadCRC", DEVELOPER,
				"changePetDatapadCRC",
				"USAGE: @changePetDatapadCRC",
				&changePetDatapadCRC);

	 gmCommands->addCommand("petAnimation", DEVELOPER,
				"petAnimation",
				"USAGE: @petAnimation",
				&petAnimation);

    gmCommands->addCommand("woundPet", DEVELOPER,
				"woundPet",
				"USAGE: @woundPet",
				&woundPet);
	gmCommands->addCommand("createTestPet", DEVELOPER,
				"createTestPet",
				"USAGE: @createTestPet <player name>",
				&createTestPet);

	gmCommands->addCommand("clearInventory", PRIVILEGED,
				"Clears all unequipped items in a player inventory, in the event they are having problems",
				"USAGE: @clearInventory <player name>",
				&clearInventory);

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
	//TODO: Rework commands. Disabled for now.
	return;

	try {
		String cmdLower = cmd.toLowerCase();
		if (!gmCommands->containsKey(cmdLower)) {
			//player->sendSystemMessage("Command not found.");
			return;
		}

		GMCommand * command = gmCommands->get(cmdLower);
		//if (command->getRequiredAdminLevel() & player->getAdminLevel())
			//command->exec(tokenizer, player);
		//else
			//player->sendSystemMessage("You do not have permission to use this command.");
	} catch (...) {
		//player->sendSystemMessage("Command not found.");
	}
}
