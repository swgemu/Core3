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

#ifndef CREATUREMANAGERIMPLEMENTATION_H_
#define CREATUREMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../db/ServerDatabase.h"

#include "../../ZoneServer.h"
#include "../../Zone.h"

#include "../player/ProfessionManager.h"

#include "../../objects/creature/Creature.h"
#include "../../objects/creature/CreatureImplementation.h"
#include "../../objects/creature/bluefrog/BlueFrogCreature.h"
#include "../../objects/creature/bluefrog/BlueFrogCreatureImplementation.h"
#include "../../objects/creature/action/ActionCreature.h"
#include "../../objects/creature/action/ActionCreatureImplementation.h"
#include "../../objects/creature/action/Action.h"
#include "../../objects/creature/action/ActionImplementation.h"

#include "CreatureMap.h"
#include "LairMap.h"
#include "SpawnInfoMap.h"

#include "CreatureManager.h"

class ZoneProcessServerImplementation;
class BlueFrogCreatureImplementation;

class CreatureManagerImplementation : public CreatureManagerServant, public Thread, public Mutex, public Lua {
	Zone* zone;
	ScheduleManager* scheduler;

	CreatureMap* creatureMap;
	LairMap* lairMap;

	EventQueue creatureActivityQueue;

	ZoneProcessServerImplementation* server;

	static SpawnInfoMap* spawnInfoMap;
	static CreatureManagerImplementation* instance;

public:

	static const int LINE_LAYOUT = 1;
	static const int GRID_LAYOUT = 2;
	static const int RANDOM_LAYOUT = 3;

public:
	CreatureManagerImplementation(Zone* zone, ZoneProcessServerImplementation* serv);

	~CreatureManagerImplementation();

	void init();
	void loadCreatures();

	void run();

	void stop();

	// creature loading methods
	void loadTrainers();
	void loadRecruiters();
	void loadStaticCreatures();
	void loadBlueFrogs();
	void loadMissionCreatures();

	void load(Creature* creature);
	void unloadCreature(Creature* creature);

	// creation methods
	//Creature* spawnCreature(const string& stfname, const string& name, int objCrc, float x, float y, int bitmask = 0x00, bool doLock = true);
	Creature* spawnCreature(uint32 objcrc, uint64 cellid, float x, float y, int bitmask = 0, bool baby = false, bool doLock = true, float height = 1);
	TrainerCreature* spawnTrainer(const string& profession, const string& stfname, const string& name, int objCrc, uint64 cell, float x, float y, float z, float oy, float ow, bool doLock = true);
	ShuttleCreature* spawnShuttle(const string& Planet, const string& City, Coordinate* playerSpawnPoint, uint64 cellid,float x, float y, float z, uint32 tax = 0, bool starport = false, bool doLock = true);
	RecruiterCreature* spawnRecruiter(const string& stfname, const string& name, int objCrc, float x, float y, bool doLock = true);
	BlueFrogCreature* spawnBlueFrog(float x, float y, float oY, float oW, int type = 0, uint64 cellid = 0, bool doLock = true);
	ActionCreature* spawnActionCreature(string& name, string& stfname, uint32 objCrc, string misoKey, float x, float y, float oY, float oW, uint64 cellid = 0, bool doLock = true);
	//CreatureGroup* spawnCreatureGroup(int count, const string& stfname, const string& name, int objCrc, float x, float y, int bitmask = 0x00, int layout = LINE_LAYOUT);
	LairObject* spawnLair(const string& type, float x, float y, float z, bool doLock = true);
	void despawnCreature(Creature* creature);
	void respawnCreature(Creature* creature);

	uint32 getCreatureCrc(string name);

	void unloadManager();

	void registerFunctions();
	void registerGlobals();

	void loadCreatureFile() {
		runFile("scripts/creatures/main.lua");
	}

	void loadObjectFile() {
		runFile("scripts/sceneobjects/main.lua");
	}

	bool hotLoadCreature(string name);

	//creature naming
	string makeStormTrooperName();
	string makeDarkTrooperName();
	string makeCreatureName(string charname);

	inline string stringify(const int x);

	//lua functions
	static int runCreatureFile(lua_State* L);
	static int runObjectFile(lua_State* L);

	static int addCreature(lua_State *L);
	static int addLair(lua_State * L);
	static int testServer(lua_State * L);

	static int addBlueFrog(lua_State *L);

	void queueActivity(CreatureImplementation* creature, uint32 time = 1000) {
		creature->update(time);
		creatureActivityQueue.add(creature);
	}

	void dequeueActivity(CreatureImplementation* creature) {
		creatureActivityQueue.remove(creature);
	}


private:
	uint64 getNextCreatureID();
	void setCreatureAttributes(Creature* creature, LuaObject* creatureConfig);

public:
	// setters and getters
	inline Creature* getCreature(uint64& oid) {
		return creatureMap->get(oid);
	}

	inline Zone* getZone() {
		return zone;
	}

};


#endif /*CREATUREMANAGERIMPLEMENTATION_H_*/
