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

#include "../../objects/terrain/Terrain.h"

#include "../../objects/tangible/weapons/Weapon.h"

#include "../../objects.h"
#include "../../objects/tangible/Inventory.h" 

#include "../../objects/creature/Creature.h"
#include "../../objects/creature/CreatureObject.h"

#include "../../objects/creature/trainer/TrainerCreature.h"
#include "../../objects/creature/recruiter/RecruiterCreature.h"
#include "../../objects/creature/shuttle/ShuttleCreature.h"

#include "../../objects/creature/CreatureGroup.h"
#include "../../objects/creature/CreatureGroupImplementation.h"

#include "../skills/SkillManager.h"

#include "CreatureManager.h"
#include "CreatureManagerImplementation.h"

#include "../../../ServerCore.h"

#include "../../ZoneProcessServerImplementation.h"

CreatureManagerImplementation* CreatureManagerImplementation::instance = NULL;

CreatureManagerImplementation::CreatureManagerImplementation(Zone* zone, ZoneProcessServerImplementation* serv) : CreatureManagerServant(), Thread(), Mutex("CreatureManager"), 
		Lua() {
	CreatureManagerImplementation::zone = zone;
		
	server = serv;
	
	creatureMap = new CreatureMap(20000);
	
	setLoggingName("CreatureManager" + zone->getZoneID());
	
	setLogging(false);
	setGlobalLogging(true);
}

CreatureManagerImplementation::~CreatureManagerImplementation() {
	if (creatureMap != NULL)
		delete creatureMap;
}

void CreatureManagerImplementation::init() {
	/*ZoneServer* server = zone->getZoneServer();
	scheduler = server->getScheduler();*/
	
	scheduler = new ScheduleManager("CreatureScheduler");
	
	// Scripting
	Lua::init();
	registerFunctions();
	registerGlobals();
	
	instance = this;
	loadCreatureFile();
	
	loadTrainers();
	loadRecruiters();
	loadStaticCreatures();
}

void CreatureManagerImplementation::run() {
	CreatureImplementation* creature;

	while ((creature = (CreatureImplementation*) creatureActivityQueue.get()) != NULL) {
		try {
			creature->activate();
		} catch (Exception& e) {
			error(e.getMessage());
		} catch (...) {
			error("unreported Exception caught");
		}
	}
}

void CreatureManagerImplementation::stop() {
	creatureActivityQueue.flush();
		
	join();

	creatureMap->resetIterator();
	
	while (creatureMap->hasNext()) {
		Creature* creature = creatureMap->next();
		
		creature->unload();
		
		creature->removeUndeploymentEvent();
		creature->finalize();
	}
	
	info("stopped");
}

void CreatureManagerImplementation::loadRecruiters() {
	if (zone->getZoneID() == 8) {
		RecruiterCreature* recruiter1 = spawnRecruiter("", "Recruiter", 0x8C73B91, 36, -5336);
		RecruiterCreature* recruiter2 = spawnRecruiter("", "Recruiter", 0x8C73B91, -1130, -3902);
	}
}

void CreatureManagerImplementation::loadTrainers() {
	ProfessionManager* professionManager = server->getProfessionManager();
	
	int planetid = zone->getZoneID();
	
	ResultSet* result;
	stringstream query;
	query << "SELECT * FROM trainers WHERE Planet = " << planetid << ";";
	result = ServerDatabase::instance()->executeQuery(query);
	
	while (result->next()) {
		string location = result->getString(0);
		string name = result->getString(1);
		string profession = result->getString(2);
		
		//Profession* prof = professionManager->professionMap.get(profession);
		
		uint64 crc1 = strtoul(result->getString(3),NULL,16);
		uint64 crc2 = strtoul(result->getString(4),NULL,16);
		uint64 crc3 = strtoul(result->getString(5),NULL,16);
		
		float x = result->getFloat(7);
		float y = result->getFloat(8);
		
		int rand = System::random(2);
		
		if (rand == 0 && crc1 != 0)
			TrainerCreature* trainer = spawnTrainer(profession, name, "", crc1, x, y);
		else if (rand == 1 && crc2 != 0)
			TrainerCreature* trainer = spawnTrainer(profession, name, "", crc2, x, y);
		else
			TrainerCreature* trainer = spawnTrainer(profession, name, "", crc3, x, y);									
	}
		
	delete result;

	if (zone->getZoneID() == 8) {
		professionManager->professionMap.resetIterator();
	
		for (int i = 0; professionManager->professionMap.hasNext(); i++) {
			Profession* prof = professionManager->professionMap.getNextValue();
			
			if ((int)prof->getName().find("jedi") >= 0 || (int)prof->getName().find("force") >= 0)
				continue;
		
			TrainerCreature* trainer = spawnTrainer(prof->getName(), "", prof->getName(), 0x8C73B91, -16 - (i*2.25), -5305 );
		}
	}
}

void CreatureManagerImplementation::loadStaticCreatures() {
}

CreatureGroup* CreatureManagerImplementation::spawnCreatureGroup(int count, const string& stfname, const string& name, int objCrc, float x, float y, int bitmask, int layout) {
	try {
		lock();

		CreatureGroupImplementation* groupImpl = new CreatureGroupImplementation();
		CreatureGroup* group = (CreatureGroup*)  groupImpl->deploy();

		for (int i = 0; i < count; i++) {
			Creature* creature = spawnCreature(stfname, name, objCrc, x, y, bitmask, false);

			creatureMap->put(creature->getObjectID(), creature);
			
			creature->setCreatureGroup(group);
			group->addCreature(creature);
		
			switch (layout) {
			case LINE_LAYOUT:
				x+= 1;
				break;
			case GRID_LAYOUT:
				break;
			case RANDOM_LAYOUT:
				break;
			}
		}
		
		unlock();
		
		return group;
	} catch (...) {
		error("unreported Exception caught on spawnWave()");
		unlock();
		
		return NULL;
	}
}

TrainerCreature* CreatureManagerImplementation::spawnTrainer(const string& profession, const string& stfname, const string& name, int objCrc, float x, float y, bool doLock) {
	try {
		lock(doLock);
		
		Profession* prof = server->getProfessionManager()->professionMap.get(profession);
		
		TrainerCreatureImplementation* trainerImpl = new TrainerCreatureImplementation(getNextCreatureID(), prof);

		if (!stfname.empty())
			trainerImpl->speciesName = stfname;
		else
			trainerImpl->characterName = unicode(name);
			
		trainerImpl->objectFile = "";
		trainerImpl->objectCRC = objCrc;

		trainerImpl->terrainName = Terrain::getTerrainName(zone->getZoneID());
	
		trainerImpl->height = 1.0f;
		trainerImpl->initializePosition(x, 0, y);
		trainerImpl->pvpStatusBitmask = 0;//0x01 + 0x02 + 0x20;
		
		load(trainerImpl);
		
		TrainerCreature* trainer = (TrainerCreature*) trainerImpl->deploy();
		
		trainer->insertToZone(zone);
		
		creatureMap->put(trainer->getObjectID(), trainer);

		unlock(doLock);
		return trainer;
	} catch (...) {
		error("unreported Exception caught on spawnTrainer()"); 

		unlock(doLock);
		return NULL;
	}
}

RecruiterCreature* CreatureManagerImplementation::spawnRecruiter(const string& stfname, const string& name, int objCrc, float x, float y, bool doLock) {
	try {
		lock(doLock);
		
		RecruiterCreatureImplementation* recruiterImpl = new RecruiterCreatureImplementation(getNextCreatureID());
	
		if (!stfname.empty())
			recruiterImpl->speciesName = stfname;
		else
			recruiterImpl->characterName = unicode(name);

		recruiterImpl->objectFile = "";
		recruiterImpl->objectCRC = objCrc;

		recruiterImpl->terrainName = Terrain::getTerrainName(zone->getZoneID());
	
		//ham stuff
		
		recruiterImpl->height = 1.0f;
		recruiterImpl->initializePosition(x, 0, y);
		recruiterImpl->pvpStatusBitmask = 0;//0x01 + 0x02 + 0x20;

		load(recruiterImpl);
		
		RecruiterCreature* creature = (RecruiterCreature*) recruiterImpl->deploy();
		
		creature->insertToZone(zone);
		
		creatureMap->put(creature->getObjectID(), creature);

		unlock(doLock);
		return creature;
	} catch (...) {
		error("unreported Exception caught on spawnRecruiter()"); 

		unlock(doLock);
		return NULL;
	}
}

ShuttleCreature* CreatureManagerImplementation::spawnShuttle(const string& Planet, const string& City, Coordinate* playerSpawnPoint, float x, float y, float z, bool doLock) {
	try {
		lock(doLock);
		
		ShuttleCreatureImplementation* shuttleImpl = new ShuttleCreatureImplementation(Planet, City, playerSpawnPoint, getNextCreatureID());
		
		shuttleImpl->terrainName = Terrain::getTerrainName(zone->getZoneID());
	
		shuttleImpl->height = 1.0f;
		shuttleImpl->initializePosition(x, z, y);
		
		load(shuttleImpl);
		
		ShuttleCreature* shuttle = (ShuttleCreature*) shuttleImpl->deploy();
		
		shuttle->insertToZone(zone);
		
		creatureMap->put(shuttle->getObjectID(), shuttle);

		unlock(doLock);
		return shuttle;
	} catch (...) {
		error("unreported Exception caught on spawnShuttle()"); 

		unlock(doLock);
		return NULL;
	}
}

Creature* CreatureManagerImplementation::spawnCreature(const string& stfname, const string& name, int objCrc, float x, float y, int bitmask, bool doLock) {
	try {
		lock(doLock);
		
		CreatureImplementation* creatureImpl = new CreatureImplementation(getNextCreatureID());
		
		if (!stfname.empty())
			creatureImpl->speciesName = stfname;
		else
			creatureImpl->characterName = unicode(name);

		creatureImpl->objectFile = "";
		creatureImpl->objectCRC = objCrc;

		creatureImpl->terrainName = Terrain::getTerrainName(zone->getZoneID());
	
		//ham stuff
		creatureImpl->health = 10000;
		creatureImpl->strength = 10000;
		creatureImpl->constitution = 10000;
		creatureImpl->action = 10000;
		creatureImpl->quickness = 10000;
		creatureImpl->stamina = 10000;
		creatureImpl->mind = 10000;
		creatureImpl->focus = 10000;
		creatureImpl->willpower = 10000;

		creatureImpl->healthMax = 10000;
		creatureImpl->strengthMax = 10000;
		creatureImpl->constitutionMax = 10000;
		creatureImpl->actionMax = 10000;
		creatureImpl->quicknessMax = 10000;
		creatureImpl->staminaMax = 10000;
		creatureImpl->mindMax = 10000;
		creatureImpl->focusMax = 10000;
		creatureImpl->willpowerMax = 10000;

		creatureImpl->height = 1.0f;
		creatureImpl->initializePosition(x, 0, y);
		creatureImpl->pvpStatusBitmask = bitmask;//0x01 + 0x02 + 0x20;

		load(creatureImpl);
		
		Creature* creature = (Creature*) creatureImpl->deploy();
		
		creature->loadItems();
		creature->insertToZone(zone);
		
		creatureMap->put(creature->getObjectID(), creature);

		unlock(doLock);
		return creature;
	} catch (...) {
		error("unreported Exception caught on spawnNPC()"); 

		unlock(doLock);
		return NULL;
	}
}

void CreatureManagerImplementation::despawnCreature(Creature* creature) {
	lock();
	
	unloadCreature(creature);
	
	unlock();
}

void CreatureManagerImplementation::respawnCreature(Creature* creature) {
	lock();
	
	creature->setObjectID(getNextCreatureID());
	
	creatureMap->put(creature->getObjectID(), creature);

	unlock();
}

void CreatureManagerImplementation::load(CreatureImplementation* creature) {
	creature->setCreatureManager(this);
	creature->setZoneProcessServer(server);
	
	// Load skills from lua's
	LuaFunction getCreature(getLuaState(), "getCreature", 1);
	getCreature << creature->objectCRC; // push first argument	
	callFunction(&getCreature);
	
	LuaObject result(getLuaState());
	if (!result.isValidTable())
		return;
	
	string objectName = result.getStringField("objectName");
	result.pop(); // remove table from stack
	
	LuaFunction getSkills(getLuaState(), objectName, "getNumberOfSkills", 1);
	callFunction(&getSkills);
	int res = getIntParameter(getLuaState());

	for (int i = 1; i <= res; i++) {
		LuaFunction getSkill(getLuaState(), objectName, "getSkill", 1);
		getSkill << i; // push arg

		callFunction(&getSkill);
		string skill = getStringParameter(getLuaState());

		SkillManager* sManager = server->getSkillManager();
		Skill* s = sManager->getSkill(skill);

		if (s == NULL) {
			cout << "Invalid Skill [" << skill << "] for {" << objectName << "}\n";
			continue;
		}

		creature->addSkill(s);
	}
}

void CreatureManagerImplementation::unloadCreature(Creature* creature) {
	creatureMap->remove(creature->getObjectID());
}

int CreatureManagerImplementation::addCreature(lua_State *L) {
	LuaObject creature(L);
	
	if (!creature.isValidTable())
		return 1;
	
	int planet = creature.getIntField("planet");
	
	if (planet != instance->getZone()->getZoneID())
		return 1;
	
	instance->lock();
	
	CreatureImplementation* creatureImpl = new CreatureImplementation(instance->getNextCreatureID());
	
	string objectName = creature.getStringField("objectName");
	string stfname = creature.getStringField("stfName");
	string name = creature.getStringField("name");

	creatureImpl->objectCRC = creature.getIntField("objectCRC");

	if (!stfname.empty())
		creatureImpl->characterName = stfname;
	else	
		if (creatureImpl->objectCRC == 0xBA7F23CD)
			creatureImpl->characterName = unicode(instance->makeStormTrooperName());
		else
			creatureImpl->characterName = unicode(instance->makeCreatureName(name));
	
	creatureImpl->terrainName = Terrain::getTerrainName(planet);

	//ham stuff
	creatureImpl->health = creature.getIntField("health");
	creatureImpl->strength = creature.getIntField("strength");
	creatureImpl->constitution = creature.getIntField("constitution");
	creatureImpl->action = creature.getIntField("action");
	creatureImpl->quickness = creature.getIntField("quickness");
	creatureImpl->stamina = creature.getIntField("stamina");
	creatureImpl->mind = creature.getIntField("mind");
	creatureImpl->focus = creature.getIntField("focus");
	creatureImpl->willpower = creature.getIntField("willpower");

	creatureImpl->health = creatureImpl->health + (creatureImpl->health * (System::random(100)) / 1111);
	creatureImpl->action = creatureImpl->action + (creatureImpl->action * (System::random(100)) / 1111);
	creatureImpl->mind = creatureImpl->mind + (creatureImpl->mind * (System::random(100)) / 1111);
	
	creatureImpl->healthMax = creatureImpl->health;
	creatureImpl->strengthMax = creatureImpl->strength;
	creatureImpl->constitutionMax = creatureImpl->constitution;
	creatureImpl->actionMax = creatureImpl->action;
	creatureImpl->quicknessMax = creatureImpl->quickness;
	creatureImpl->staminaMax = creatureImpl->stamina;
	creatureImpl->mindMax = creatureImpl->mind;
	creatureImpl->focusMax = creatureImpl->focus;
	creatureImpl->willpowerMax = creatureImpl->willpower;

	creatureImpl->baseHealth = creatureImpl->health;
	creatureImpl->baseStrength = creatureImpl->strength;
	creatureImpl->baseConstitution = creatureImpl->constitution;
	creatureImpl->baseAction = creatureImpl->action;
	creatureImpl->baseQuickness = creatureImpl->quickness;
	creatureImpl->baseStamina = creatureImpl->stamina;
	creatureImpl->baseMind = creatureImpl->mind;
	creatureImpl->baseFocus = creatureImpl->focus;
	creatureImpl->baseWillpower = creatureImpl->willpower;	
	
	creatureImpl->armor = creature.getIntField("armor");

	creatureImpl->kinetic = creature.getFloatField("kinetic");
	creatureImpl->energy = creature.getFloatField("energy");
	creatureImpl->electricity = creature.getFloatField("electricity");
	creatureImpl->stun = creature.getFloatField("stun");
	creatureImpl->blast = creature.getFloatField("blast");
	creatureImpl->heat = creature.getFloatField("heat");
	creatureImpl->cold = creature.getFloatField("cold");
	creatureImpl->acid = creature.getFloatField("acid");
	creatureImpl->lightSaber = creature.getFloatField("lightSaber");	

	creatureImpl->height = creature.getFloatField("height");
	float x = creature.getFloatField("positionX");
	float y = creature.getFloatField("positionY");
	float z = creature.getFloatField("positionZ");
	creatureImpl->initializePosition(x, z, y);
	
	creatureImpl->spawnPositionX = x;
	creatureImpl->spawnPositionY = y;
	creatureImpl->spawnPositionZ = z;	
	
	creatureImpl->accuracy = creature.getIntField("accuracy");
	creatureImpl->speed = creature.getFloatField("speed");
	creatureImpl->acceleration = creature.getFloatField("acceleration");
	creatureImpl->respawnTimer = creature.getIntField("respawnTimer");
	creatureImpl->level = creature.getIntField("level");
	creatureImpl->pvpStatusBitmask = creature.getIntField("combatFlags");
	creatureImpl->parent = instance->getZone()->lookupObject(creature.getLongField("cellID"));

	instance->load(creatureImpl);

	Creature* creatureObj = (Creature*) creatureImpl->deploy();

	creatureObj->loadItems();
	creatureObj->insertToZone(instance->zone);

	instance->creatureMap->put(creatureObj->getObjectID(), creatureObj);
	instance->unlock();

	return 0;
}

int CreatureManagerImplementation::addLair(lua_State * L) {
	LuaObject object(L);
	
	int planet = object.getIntField("planet");

	if (planet != instance->getZone()->getZoneID())
		return 1;
	
	instance->lock();
	uint32 objectCRC = object.getIntField("objectCRC");
	LairObjectImplementation* lairImpl = new LairObjectImplementation(objectCRC, instance->getNextCreatureID());
	float x = object.getFloatField("positionX");
	float y = object.getFloatField("positionY");
	float z = object.getFloatField("positionZ");
	
	lairImpl->initializePosition(x, z, y);
	
	LairObject* lairObject = (LairObject*) lairImpl->deploy();

	//lairObject->loadItems();
	lairObject->insertToZone(instance->zone);
	
	cout << "Spawning Lair with objcrc (" << objectCRC << ")" << "on position [" << x << "," << y << "]\n";
	object.pop();
	
	instance->unlock();
	
	return 0;
	
}

int CreatureManagerImplementation::runCreatureFile(lua_State* L) {
	string filename = getStringParameter(L);
	
	runFile("scripts/creatures/" + filename, L);
	
	return 0;
}


void CreatureManagerImplementation::registerFunctions() {
	//lua generic
	lua_register(getLuaState(), "RunCreatureFile", runCreatureFile);
	
	lua_register(getLuaState(), "AddCreatureToServer", addCreature);
	lua_register(getLuaState(), "AddLairToServer", addLair);	
}

void CreatureManagerImplementation::registerGlobals() {
	setGlobalInt("ATTACKABLE_FLAG", 1);
	setGlobalInt("AGGRESSIVE_FLAG", 2);
	setGlobalInt("ENEMY_FLAG", 0x20);
}

uint64 CreatureManagerImplementation::getNextCreatureID() {
	return zone->getZoneServer()->getNextCreatureID();
}

string CreatureManagerImplementation::makeStormTrooperName() {
	stringstream characterName;
	
	switch (System::random(4)) {
	case 0:
		characterName << "G";
		break;
	case 1:
		characterName << "L";
		break;
	case 2:
		characterName << "R";
		break;
	case 3:
		characterName << "T";
		break;
	case 4:
		characterName << "V";
		break;
	}
	
	characterName << "K-" << System::random(490)+10;
	
	return characterName.str();
}

string CreatureManagerImplementation::makeCreatureName(string charname) {
	
	bool lastName = System::random(1);
	bool inLastName = false;
	int nameLength = 3 + System::random(3);
	char name[nameLength];
	
	while (true) {
		int x = 0;
		
		name[0] = chooseNextLetter(' ', ' ');
		name[1] = chooseNextLetter(name[0], ' ');
		
		x = 2;
		
		for (; x < nameLength + 1; x++) {
			if (x < nameLength) {
				if (inLastName) {
					name[x] = toupper(chooseNextLetter(name[x-1], name[x-2]));
					inLastName = false;
				} else
					name[x] = chooseNextLetter(name[x-1], name[x-2]);
			} else {
				if (lastName && x == nameLength) {
					name[x] = ' ';
					nameLength += 4 + System::random(3);
					lastName = false;
					inLastName = true;
				} else {
					name[x] = '\0';
					break;
				}
			}
		}

		name[0] = toupper(name[0]);
		if (!isProfanity(name))
			break;
	}
	stringstream newname;
	newname << name << " (" << charname << ")";
	
	return newname.str();
}

char CreatureManagerImplementation::chooseNextLetter(const char lastLetter, const char letterBeforeLast) {

	if (letterBeforeLast == ' ' && lastLetter == ' ')
		return 97 + System::random(25);

	if ((!isVowel(lastLetter) && !isVowel(letterBeforeLast) && letterBeforeLast	!= ' ') 
			|| (lastLetter == 'u' && letterBeforeLast == 'q')) {
		char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
				'n', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
				'\0' };

		return chooseLetterExcluding(exclusion);
	}

	if ((isVowel(lastLetter) && isVowel(letterBeforeLast) && letterBeforeLast != ' ')) {
		char exclusion[] = { 'a', 'e', 'i', 'o', 'u', 'y', '\0' };

		return chooseLetterExcluding(exclusion);
	} else {
		switch (tolower(lastLetter)) {
		case 'a': {
			char exclusion[] = { 'a', 'e', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'b': {
			char exclusion[] = { 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k',
					'm', 'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'c': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n',
					'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'd': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'f': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'g': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n',
					'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'h': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
							'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
									'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'i': {
			char exclusion[] = { 'i', 'j', 'u', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'j': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'k': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'l': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
							'l', 'm', 'n', 'p', 'q', 'r', 's', 'v', 'w',
									'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'm': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'n': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'p': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n',
					'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'q':
			return 'u';
		case 'r': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
							'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
									'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 's': {
			char exclusion[] = { 'b', 'd', 'f', 'g', 'j', 'v', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 't': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'l', 'm',
					'n', 'p', 'q', 't', 'v', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'u': {
			char exclusion[] = { 'a', 'b', 'd', 'e', 'h', 'i', 'm', 'o', 'r',
					'u', 'v', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'v': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
							'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
									'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'w': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'l', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'x': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
							'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
									'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'y': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'z': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		default:
			return 97 + System::random(25);
		}
	}
}

bool CreatureManagerImplementation::isProfanity(const string inname) {
	if ((inname.find("anal") == string::npos) && (inname.find("ass")
			== string::npos) && (inname.find("asshole") == string::npos)
			&& (inname.find("assmunch") == string::npos)
			&& (inname.find("asswhole") == string::npos)
			&& (inname.find("biatch") == string::npos) && (inname.find("bitch")
			== string::npos) && (inname.find("boob") == string::npos)
			&& (inname.find("christ") == string::npos) && (inname.find("clit")
			== string::npos) && (inname.find("cock") == string::npos)
			&& (inname.find("cum") == string::npos)
			&& (inname.find("cumbubble") == string::npos)
			&& (inname.find("cumlicker") == string::npos)
			&& (inname.find("cunt") == string::npos) && (inname.find("damn")
			== string::npos) && (inname.find("devil") == string::npos)
			&& (inname.find("dick") == string::npos)
			&& (inname.find("dingleberry") == string::npos)
			&& (inname.find("dong") == string::npos) && (inname.find("dumbass")
			== string::npos) && (inname.find("fag") == string::npos)
			&& (inname.find("faggot") == string::npos) && (inname.find("fagot")
			== string::npos) && (inname.find("fuk") == string::npos)
			&& (inname.find("fuxxor") == string::npos)
			&& (inname.find("george lucas") == string::npos)
			&& (inname.find("gook") == string::npos) && (inname.find("hooker")
			== string::npos) && (inname.find("jackoff") == string::npos)
			&& (inname.find("jesus") == string::npos) && (inname.find("jew")
			== string::npos) && (inname.find("jizz") == string::npos)
			&& (inname.find("kike") == string::npos) && (inname.find("kunt")
			== string::npos) && (inname.find("labia") == string::npos)
			&& (inname.find("masterbait") == string::npos)
			&& (inname.find("masterbate") == string::npos)
			&& (inname.find("masturbait") == string::npos)
			&& (inname.find("nazi") == string::npos) && (inname.find("negro")
			== string::npos) && (inname.find("nigg") == string::npos)
			&& (inname.find("nigger") == string::npos)
			&& (inname.find("nipple") == string::npos) && (inname.find("penis")
			== string::npos) && (inname.find("piss") == string::npos)
			&& (inname.find("prick") == string::npos) && (inname.find("pussy")
			== string::npos) && (inname.find("satan") == string::npos)
			&& (inname.find("sex") == string::npos) && (inname.find("shit")
			== string::npos) && (inname.find("skank") == string::npos)
			&& (inname.find("slut") == string::npos)
			&& (inname.find("spawnthemonkey") == string::npos)
			&& (inname.find("spick") == string::npos) && (inname.find("sucks")
			== string::npos) && (inname.find("tit") == string::npos)
			&& (inname.find("tits") == string::npos) && (inname.find("titt")
			== string::npos) && (inname.find("twat") == string::npos)
			&& (inname.find("vagina") == string::npos) && (inname.find("whore")
			== string::npos) && (inname.find("wtf") == string::npos))
		return false;
	else
		return true;
}

inline bool CreatureManagerImplementation::isVowel(const char inChar) {
	
	if (inChar == 'a' || inChar == 'e' || inChar == 'i' || inChar == 'o'
			|| inChar == 'u' || inChar == 'y')
		return true;
	else
		return false;
}

inline char CreatureManagerImplementation::chooseLetterExcluding(const char exclude[]) {
	
	char x = 97 + System::random(25);

	for (int i = 0; i < 25; i++) {
		if (x == exclude[i]) {
			x = 97 + System::random(25);

			i = -1;
		}
	}
	
	return x;
}

inline string CreatureManagerImplementation::stringify(const int x) {
	ostringstream o;

	if (!(o << x))
		return "";
	else
		return o.str();
}

