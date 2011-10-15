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

#ifndef COMMANDCONFIGMANAGER_H_
#define COMMANDCONFIGMANAGER_H_

#include "engine/engine.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "CommandFactory.h"

namespace server {
namespace zone {
class ZoneProcessServer;
}
}

using namespace server::zone;

namespace server {
namespace zone {
namespace managers {
namespace objectcontroller {
namespace command {

class CommandList;

class CommandConfigManager : public Lua {
public:
	// These numbers correspond to command_table.iff
	static const int COMMANDNAME = 0; // 0: commandName
	static const int DEFAULTPRIORITY = 1; // 1: defaultPriority
	static const int SCRIPTHOOK = 2; // 2: scriptHook
	static const int FAILSCRIPT_HOOK = 3; // 3: failScriptHook
	static const int CPPHOOK = 4; // 4: cppHook
	static const int FAILCPPHOOK = 5; // 5: failCppHook
	static const int DEFAULTTIME = 6; // 6: defaultTime
	static const int CHARACTERABILITY = 7; // 7: characterAbility

	// locomotion
	static const int STANDING = 8; // 8: L:standing
	static const int SNEAKING = 9; // 9: L:sneaking
	static const int WALKING = 10; // 10: L:walking
	static const int RUNNING = 11; // 11: L:running
	static const int KNEELING = 12; // 12: L:kneeling
	static const int CROUCHSNEAKING = 13; // 13: L:crouchSneaking
	static const int CROUCHWALKING = 14; // 14: L:crouchWalking
	static const int PRONE = 15; // 15: L:prone
	static const int CRAWLING = 16; // 16: L:crawling
	static const int CLIMBINGSTATIONARY = 17; // 17: L:climbingStationary
	static const int CLIMBING = 18; // 18: L:climbing
	static const int HOVERING = 19; // 19: L:hovering
	static const int FLYING = 20; // 20: L:flying
	static const int LYINGDOWN = 21; // 21: L:lyingDown
	static const int SITTING = 22; // 22: L:sitting
	static const int SKILLANIMATING = 23; // 23: L:skillAnimating
	static const int DRIVINGVEHICLE = 24; // 24: L:drivingVehicle
	static const int RIDINGCREATURE = 25; // 25: L:ridingCreature
	static const int KNOCKEDDOWN = 26; // 26: L:knockedDown
	static const int INCAPACITATED = 27; // 27: L:incapacitated
	static const int DEAD = 28; // 28: L:dead
	static const int BLOCKING = 29; // 29: L:blocking

	// states
	static const int COVER = 30; // 30: S:cover
	static const int COMBAT = 31; // 31: S:combat
	static const int PEACE = 32; // 32: S:peace
	static const int AIMING = 33; // 33: S:aiming
	static const int ALERT = 34; // 34: S:alert
	static const int BERSERK = 35; // 35: S:berserk
	static const int FEIGNDEATH = 36; // 36: S:feignDeath
	static const int COMBATATTITUDEEVASIVE = 37; // 37: S:combatAttitudeEvasive
	static const int COMBATATTITUDENORMAL = 38; // 38: S:combatAttitudeNormal
	static const int COMBATATTITUDEAGGRESSIVE = 39; // 39: S:combatAttitudeAggressive
	static const int TUMBLING = 40; // 40: S:tumbling
	static const int RALLIED = 41; // 41: S:rallied
	static const int STUNNED = 42; // 42: S:stunned
	static const int BLINDED = 43; // 43: S:blinded
	static const int DIZZY = 44; // 44: S:dizzy
	static const int INTIMIDATED = 45; // 45: S:intimidated
	static const int IMMOBILIZED = 46; // 46: S:immobilized
	static const int FROZEN = 47; // 47: S:frozen
	static const int SWIMMING = 48; // 48: S:swimming
	static const int SITTINGONCHAIR = 49; // 49: S:sittingOnChair
	static const int CRAFTING = 50; // 50: S:crafting
	static const int GLOWINGJEDI = 51; // 51: S:glowingJedi
	static const int MASKSCENT = 52; // 52: S:maskScent
	static const int POISONED = 53; // 53: S:poisoned
	static const int BLEEDING = 54; // 54: S:bleeding
	static const int DISEASED = 55; // 55: S:diseased
	static const int ONFIRE = 56; // 56: S:onFire
	static const int RIDINGMOUNT = 57; // 57: S:ridingMount
	static const int MOUNTEDCREATURE = 58; // 58: S:mountedCreature
	static const int PILOTINGSHIP = 59; // 59: S:pilotingShip
	static const int PILOTINGPOBSHIP = 60; // 60: S:pilotingPobShip
	static const int SHIPOPERATIONS = 61; // 61: S:shipOperations
	static const int SHIPGUNNER = 62; // 62: S:shipGunner
	static const int SHIPINTERIOR = 63; // 63: S:shipInterior

	static const int TEMPSCRIPT = 64; // 64: tempScript
	static const int TARGETTYPE = 65; // 65: targetType
	static const int STRINGID = 66; // 66: stringId
	static const int VISIBLE = 67; // 67: visible
	static const int CALLONTARGET = 68; // 68: callOnTarget
	static const int COMMANDGROUP = 69; // 69: commandGroup
	static const int DISABLED = 70; // 70: disabled
	static const int MAXRANGETOTARGET = 71; // 71: maxRangeToTarget
	static const int GODLEVEL = 72; // 72: godLevel
	static const int DISPLAYGROUP = 73; // 73: displayGroup
	static const int ADDTOCOMBATQUEUE = 74; // 74: addToCombatQueue

	CommandFactory<QueueCommand* (String, ZoneProcessServer*), String> commandFactory;

	static ZoneProcessServer* server;
	static CommandList* slashCommands;

	CommandConfigManager(ZoneProcessServer* serv);

	void registerFunctions();
	void registerGlobals();
	void registerCommands();

	void registerSpecialCommands();

	bool loadSlashCommandsFile(CommandList* sCommands) {
		slashCommands = sCommands;
		info("Loading commands...");
		loadCommandData("datatables/command/command_tables_shared.iff");
		loadCommandData("datatables/command/command_tables_shared_ground.iff");
		loadCommandData("datatables/command/command_tables_shared_space.iff");

		return runFile("scripts/commands/commands.lua");
	}

	bool contains(String name) {
		return commandFactory.containsCommand(name);
	}

	void loadCommandData(const String& filename);
	QueueCommand* createCommand(const String& name);

	//lua functions
	static int runSlashCommandsFile(lua_State* L);

	static void parseOptions(LuaObject& slashcommand, QueueCommand* command);
	static void parseAlternativeNames(String& alternativeNames, QueueCommand* slashCommand);
	static void parseVariableData(String varName, LuaObject &command, QueueCommand* slashCommand);

	// AddSlashCommand functions
	static int addCommand(lua_State* L);
	static int hashCode(lua_State* L);
};

}
}
}
}
}

using namespace server::zone::managers::objectcontroller::command;



#endif /*SLASHCOMMANDCONFIGMANAGER_H_*/
