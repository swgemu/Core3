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

#include "../db/ForumsDatabase.h"

class GMCommand;
class GMCommandMap;
class GameCommandHandler;


class GMCommand {
	String command;
	String description;
	String usage;

	int requiredAdminLevel;

    void (*gmCommandFunc)(StringTokenizer tokenizer, Player* player);

public:
	GMCommand(String cmd, int reqAdminLevel, String desc, String use,
			void (*func)(StringTokenizer tokenizer, Player* player)) {
		command = cmd;
		description = desc;
		gmCommandFunc = func;
		usage = use;
		requiredAdminLevel = reqAdminLevel;
	}

	inline String& getDesc() {
		return description;
	}

	inline String& getName() {
		return command;
	}

	inline String& getUsage() {
		return usage;
	}

	inline int getRequiredAdminLevel() {
		return requiredAdminLevel;
	}

	inline void exec(StringTokenizer tokenizer, Player* player) {
		gmCommandFunc(tokenizer, player);
	}

};

class GMCommandMap : public HashTable<String, GMCommand*> {
private:
	LinkedList<String> commandList;

	int hash(const String& str) {
		return str.hashCode();
	}

public:
	GMCommandMap() : HashTable<String, GMCommand*> () {
	}

	~GMCommandMap() {
		HashTableIterator<String, GMCommand*> iterator(this);

		iterator.resetIterator();

		while (iterator.hasNext()) {
			GMCommand* command = iterator.next();

			delete command;
		}

		removeAll();
	}

	void addCommand(String command, int reqAdminLevel, String disc, String usage,
			void (*gmCommandFunc)(StringTokenizer tokenizer, Player* player)) {
		String cmdLower = command.toLowerCase();

		put(cmdLower, new GMCommand(command, reqAdminLevel, disc, usage, gmCommandFunc));

		commandList.add(cmdLower);
	}

	LinkedList<String> getCommandList() {
		return commandList;
	}
};

class GameCommandHandler {
private:
	static GMCommandMap* gmCommands;

	static void commands(StringTokenizer tokenizer, Player* player);
	static void map(StringTokenizer tokenizer, Player* player);
	static void warp(StringTokenizer tokenizer, Player* player);
	static void warpTo(StringTokenizer tokenizer, Player* player);
	static void warpToWP(StringTokenizer tokenizer, Player* player);
	static void warpPlayer(StringTokenizer tokenizer, Player* player);
	static void summon(StringTokenizer tokenizer, Player* player);
	static void kick(StringTokenizer tokenizer, Player* player);
	static void kickArea(StringTokenizer tokenizer, Player* player);
	static void printRoomTree(StringTokenizer tokenizer, Player* player);
	static void banUser(StringTokenizer tokenizer, Player* player);
	static void getForumName(StringTokenizer tokenizer, Player* player);
	static void mutePlayer(StringTokenizer tokenizer, Player* player);
	static void kill(StringTokenizer tokenizer, Player* player);
	static void killArea(StringTokenizer tokenizer, Player* player);
	static void muteChat(StringTokenizer tokenizer, Player* player);
	static void users(StringTokenizer tokenizer, Player* player);
	static void setWeather(StringTokenizer tokenizer, Player* player);
	static void enableWeather(StringTokenizer tokenizer, Player* player);
	static void disableWeather(StringTokenizer tokenizer, Player* player);
	static void ticketPurchase(StringTokenizer tokenizer, Player* player);
	static void awardBadge(StringTokenizer tokenizer, Player* player);
	static void systemMessage(StringTokenizer tokenizer, Player* player);
	static void setForce(StringTokenizer tokenizer, Player* player);
	static void setDrinkFilling(StringTokenizer tokenizer, Player* player);
	static void setFoodFilling(StringTokenizer tokenizer, Player* player);
	static void getDrinkFilling(StringTokenizer tokenizer, Player* player);
	static void getFoodFilling(StringTokenizer tokenizer, Player* player);
	static void logAppearance(StringTokenizer tokenizer, Player* player);
	static void updateAppearance(StringTokenizer tokenizer, Player* player);
	static void setAppearanceVariable(StringTokenizer tokenizer, Player* player);
	static void HAMStats(StringTokenizer tokenizer, Player* player);
	static void buff(StringTokenizer tokenizer, Player* player);
	static void spice(StringTokenizer tokenizer, Player* player);
	static void dbStats(StringTokenizer tokenizer, Player* player);
	static void dbShowDeleted(StringTokenizer tokenizer, Player* player);
	static void dbPurge(StringTokenizer tokenizer, Player* player);
	static void getDirection(StringTokenizer tokenizer, Player* player);
	static void setAdminLevel(StringTokenizer tokenizer, Player* player);
	static void getLocation(StringTokenizer tokenizer, Player* player);
	static void getTargetLocation(StringTokenizer tokenizer, Player* player);
	static void getCords(StringTokenizer tokenizer, Player* player);
	static void giveItemTemp(StringTokenizer tokenizer, Player* player);
	static void clientEffect(StringTokenizer tokenizer, Player* player);
	static void rez(StringTokenizer tokenizer, Player* player);
	static void immune(StringTokenizer tokenizer, Player* player);
	static void invisible(StringTokenizer tokenizer, Player* player);
	static void flare(StringTokenizer tokenizer, Player* player);
	static void reloadSchematics(StringTokenizer tokenizer, Player* player);
	static void spawn(StringTokenizer tokenizer, Player* player);
	static void guildAdmin(StringTokenizer tokenizer, Player* player);
	static void endGuildAdmin(StringTokenizer tokenizer, Player* player);
	static void factionSet(StringTokenizer tokenizer, Player* player);
	static void getCredits(StringTokenizer tokenizer, Player* player);
	static void getXP(StringTokenizer tokenizer, Player* player);
	static void adjustFP(StringTokenizer tokenizer, Player* player);
	static void adminList(StringTokenizer tokenizer, Player* player);
	static void showChars(StringTokenizer tokenizer, Player* player);

	static void ecKill(StringTokenizer tokenizer, Player * player);
	static void poofObject(StringTokenizer tokenizer, Player * player);
	static void whoDroppedThis(StringTokenizer tokenizer, Player * player);
	static void openInventory(StringTokenizer tokenizer, Player * player);
	//static void toggleCombat(StringTokenizer tokenizer, Player* player);
	static void lockServer(StringTokenizer tokenizer, Player* player);
	static void unlockServer(StringTokenizer tokenizer, Player* player);
	static void sendp(StringTokenizer tokenizer, Player* player);
	static void requestStartingLocations(StringTokenizer tokenizer, Player* player);
	static void help(StringTokenizer tokenizer, Player* player);
	static void bug(StringTokenizer tokenizer, Player* player);
	static void freezePlayer(StringTokenizer tokenizer, Player* player);
	static void unfreezePlayer(StringTokenizer tokenizer, Player* player);
	static void changeTemplate(StringTokenizer tokenizer, Player* player);
	static void setSpeed(StringTokenizer tokenizer, Player* player);
	static void setHeight(StringTokenizer tokenizer, Player* player);
	static void warpAreaToWP(StringTokenizer tokenizer, Player* player);
	static void scaleXP(StringTokenizer tokenizer, Player* player);
	static void spawnAA(StringTokenizer tokenizer, Player* player);
	static void revokeBadge(StringTokenizer tokenizer, Player* player);
	static void setLocation(StringTokenizer tokenizer, Player* player);
	static void drag(StringTokenizer tokenizer, Player* player);
	static void damage(StringTokenizer tokenizer, Player* player);
	static void deleteFromZone(StringTokenizer tokenizer, Player* player);
	static void playAudio(StringTokenizer tokenizer, Player* player);
	static void setMOTD(StringTokenizer tokenizer, Player* player);
	static void displayMOTD(StringTokenizer tokenizer, Player* player);
	static void applyDot(StringTokenizer tokenizer, Player* player);

	static void eventMessage(StringTokenizer tokenizer, Player* player);
	static void eventCloner(StringTokenizer tokenizer, Player* player);

	static void createTestPet(StringTokenizer tokenizer, Player* player);
	static void moveToMe(StringTokenizer tokenizer, Player* player);
	static void woundPet(StringTokenizer tokenizer, Player* player);

	static void storeVehicle(StringTokenizer tokenizer, Player* player);
	static void clearMissions(StringTokenizer tokenizer, Player* player);
	static void clearInventory(StringTokenizer tokenizer, Player* player);

	void init();

public:
	GameCommandHandler() {
		init();
	}

	~GameCommandHandler();

	void handleCommand(String cmd, StringTokenizer tokenizer, Player* player);
};

#endif /*GAMECOMMANDHANDLER_H_*/
