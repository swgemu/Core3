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

#ifndef GAMECOMMANDHANDLER_H_
#define GAMECOMMANDHANDLER_H_

#include "engine/engine.h"
#include "../zone/objects/player/Player.h"

class GMCommand;
class GMCommandMap;
class GameCommandHandler;


class GMCommand {
	string command;
	string description;
	string usage;
	int requiredAdminLevel;
    void (*gmCommandFunc)(StringTokenizer tokenizer, Player * player);
	
public:
	GMCommand(string cmd, int reqAdminLevel, string desc, string use, void (*func)(StringTokenizer tokenizer, Player * player)) {
		command = cmd;
		description = desc;
		gmCommandFunc = func;
		usage = use;
		requiredAdminLevel = reqAdminLevel;
	}
	
	inline string& getDesc() {
		return description;
	}
	
	inline string& getName() {
		return command;
	}
	
	inline string& getUsage() {
		return usage;
	}
	
	inline int getRequiredAdminLevel() {
		return requiredAdminLevel;
	}
	
	inline void exec(StringTokenizer tokenizer, Player * player) {
		gmCommandFunc(tokenizer, player);
	}
	
};

class GMCommandMap : public HashTable<string, GMCommand *> {
private:
	LinkedList<string> commandList;
	
public:
	GMCommandMap() : HashTable<string, GMCommand *> () {
		
	}
	
	int hash(const string& str) {
			return String::hashCode(str);
	}
	
	void addCommand(string command, int reqAdminLevel, string disc, string usage, void (*gmCommandFunc)(StringTokenizer tokenizer, Player * player)) {
		put(command, new GMCommand(command, reqAdminLevel, disc, usage, gmCommandFunc));
		commandList.add(command);
	}
	
	LinkedList<string> getCommandList() {
		return commandList;
	}
};

class GameCommandHandler {
private:
	static GMCommandMap * gmCommands;
	static void gm_help(StringTokenizer tokenizer, Player * player);
	static void gm_map(StringTokenizer tokenizer, Player * player);
	static void gm_warp(StringTokenizer tokenizer, Player * player);
	static void gm_warpTo(StringTokenizer tokenizer, Player * player);
	static void gm_warpPlayer(StringTokenizer tokenizer, Player * player);
	static void gm_summon(StringTokenizer tokenizer, Player * player);
	static void gm_kick(StringTokenizer tokenizer, Player * player);
	static void gm_kickArea(StringTokenizer tokenizer, Player * player);
	static void gm_printRoomTree(StringTokenizer tokenizer, Player * player);
	static void gm_banUser(StringTokenizer tokenizer, Player * player);
	static void gm_mutePlayer(StringTokenizer tokenizer, Player * player);
	static void gm_kill(StringTokenizer tokenizer, Player * player);
	static void gm_killArea(StringTokenizer tokenizer, Player * player);
	static void gm_muteChat(StringTokenizer tokenizer, Player * player);
	static void gm_users(StringTokenizer tokenizer, Player * player);
	static void gm_setWeather(StringTokenizer tokenizer, Player * player);
	static void gm_ticketPurchase(StringTokenizer tokenizer, Player * player);
	static void gm_awardBadge(StringTokenizer tokenizer, Player * player);
	static void gm_systemMessage(StringTokenizer tokenizer, Player * player);
	static void gm_setForceMax(StringTokenizer tokenizer, Player * player);
	static void gm_setForce(StringTokenizer tokenizer, Player * player);
	static void gm_setDrinkFilling(StringTokenizer tokenizer, Player * player);
	static void gm_setFoodFilling(StringTokenizer tokenizer, Player * player);
	static void gm_getDrinkFilling(StringTokenizer tokenizer, Player * player);
	static void gm_getFoodFilling(StringTokenizer tokenizer, Player * player);
	static void gm_logAppearance(StringTokenizer tokenizer, Player * player);
	static void gm_updateAppearance(StringTokenizer tokenizer, Player * player);
	static void gm_setAppearanceVariable(StringTokenizer tokenizer, Player * player);
	static void gm_HAMStats(StringTokenizer tokenizer, Player * player);
	static void gm_buff(StringTokenizer tokenizer, Player * player);
	static void gm_spice(StringTokenizer tokenizer, Player * player);
	static void gm_dbStats(StringTokenizer tokenizer, Player * player);
	static void gm_dbShowDeleted(StringTokenizer tokenizer, Player * player);
	static void gm_dbPurge(StringTokenizer tokenizer, Player * player);
	static void gm_getDirection(StringTokenizer tokenizer, Player * player);
	static void gm_setAdminLevel(StringTokenizer tokenizer, Player * player);
	static void gm_getLocation(StringTokenizer tokenizer, Player * player);
	
	void init();
	
public:
	GameCommandHandler() {
		init();
	}
	
	
	
	void handleCommand(string cmd, StringTokenizer tokenizer, Player * player) {
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
};

#endif /*GAMECOMMANDHANDLER_H_*/
