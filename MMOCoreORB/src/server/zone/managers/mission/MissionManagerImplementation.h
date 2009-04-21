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

#ifndef MISSIONMANAGERIMPLEMENTATION_H_
#define MISSIONMANAGERIMPLEMENTATION_H_


#include "engine/engine.h"

#include "../../objects.h"

#include "../../../db/ServerDatabase.h"

#include "../../Zone.h"

#include "../../objects/mission/MissionObject.h"
#include "../../objects/mission/MissionObjectImplementation.h"

#include "../../objects/tangible/TangibleObject.h"
#include "../../objects/tangible/TangibleObjectImplementation.h"

#include "MissionMap.h"

#include "MissionManager.h"

class ZoneServerImplementation;
class ZoneProcessServerImplementation;

class MissionManagerImplementation : public MissionManagerServant, public Mutex, public Lua {
	ZoneProcessServerImplementation* processServer;
	ZoneServer*	zoneServer;

	MissionMap* misoMap;

	static MissionManagerImplementation* instance;

public:
	MissionManagerImplementation(ZoneServer* zs, ZoneProcessServerImplementation* ps);

	~MissionManagerImplementation();

	void init();
	void unloadManager();
	void removeMissions();

	// creation methods
	MissionObject* poolMission(const String& dbKey, int termMask, const String& typeStr, uint32 descKey, uint32 titleKey, uint32 diffLv, float destX, float destY, uint32 destPlanetCrc,
			const String& creatorName, uint32 rewardAmount, float targetX, float targetY, uint32 targetPlanetCrc, uint32 depictedObjCrc, const String& targetName,
			const String& description, const String& title, uint32 typeCrc, const String& objectiveDefaults, bool instantComplete, bool doLock = true);

	void instanceMission(Player* player, MissionObject* misoCopy, const String& objectives);

	//Test
	void setupHardcodeMissions();

	//data setup
	void sendTerminalData(Player* player, int termBitmask, bool doLock = true);
	void sendMission(Player* player, const String& tKey, bool doLock = true);

	//events
	void doMissionAccept(Player* player, uint64& oid, bool doLock = true);
	void doMissionComplete(Player* player, const String& tKey, bool doLock = true);
	void doMissionAbort(Player* player, uint64& oid, bool doLock = true);
	void doMissionAbort(Player* player, const String& tKey, bool doLock = true);

	//Evaluate Mission, Fire abort/completion events if necessary
	bool evalMission(Player* player, const String& tKey, String& retSay);
	bool evalMission(Player* player, MissionObject* miso);

	////
	//New Save Mission State Functions:
	//Save functions should be called on state saves and login/logout
	//-> Variables that are saved should ALWAYS be in memory. There is NO reason to call these functions
	//to regularly grab data.
	//-> Save States / Mission Saves are only for missions the player is CURRENTLY on. Not for completed
	// or past missions (failed etc)
	////

	//Loads all missions for a player from mission_saves:
	void loadPlayerMissions(Player* player, bool doLock = true);

	//Saves OR updates a mission for a player in mission_saves:
	void savePlayerMission(Player* player, MissionObject* miso);

	//Saves mission keys to the DB, called automatically on player save event
	void savePlayerKeys(Player* player, const String& curMisoKeys, const String& finMisoKeys);

	void clearPlayerMissions(Player* target, bool lockTarget = false);

	// Script methods
	void registerFunctions();
	void registerGlobals();
	void loadMissionScripts();

	// Lua functions
	static int runMissionFile(lua_State* L);
	static int addMissionToServer(lua_State *L);

private:

	//Private events
	void doMissionAbort(Player* player, MissionObject* miso);

	//Called by various internal functions to delete a mission save:
	void deleteMissionSave(Player* player, const String& mkey);

	//Completely remove the mission from the server:
	void removeMisoFromPool(MissionObject* miso, bool doLock = true);

	//Send mission baselines to the player:
	void sendMissionBase(Player* player, const String& tKey, bool doLock = true);
	void sendMissionBase(Player* player, uint64& oid, bool doLock = true);
	void sendMissionBase(Player* player, MissionObject* sMiso);

	//Send mission delta to player (for mission listing):
	void sendMissionDelta(Player* player, const String& tKey, bool doLock = true);
	void sendMissionDelta(Player* player, uint64& oid, bool doLock = true);
	void sendMissionDelta(Player* player, MissionObject* sMiso);

	//These functions will essentially "hide" the mission from the player.
	//Use these methods when the player completes/abandons/fails the mission.
	void removeMisoFromPlayer(Player* player, const String& tKey, bool doLock = true);
	void removeMisoFromPlayer(Player* player, uint64& oid, bool doLock = true);
	void removeMisoFromPlayer(MissionObject* miso, Player* player);

	uint64 getNextMissionID();

public:
	//terminal masks. If this is changed, modify in missionterminal object and lua global register
	const static int TMASK_GENERAL = 1;
	const static int TMASK_ENTERTAINER = 2;
	const static int TMASK_EXPLORER = 4;
	const static int TMASK_BOUNTY = 8;
	const static int TMASK_ARTISAN = 16;
	const static int TMASK_REBEL = 32;
	const static int TMASK_IMPERIAL = 64;
	//128, 256, 512, 1024 = reserved

};

#endif /*MissionManagerIMPLEMENTATION_H_*/

