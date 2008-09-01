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
#include "../../objects/creature/CreatureImplementation.h"
#include "../../objects/creature/CreatureObject.h"

#include "../../objects/creature/trainer/TrainerCreature.h"
#include "../../objects/creature/recruiter/RecruiterCreature.h"
#include "../../objects/creature/shuttle/ShuttleCreature.h"

#include "../../objects/creature/CreatureGroup.h"

#include "../skills/SkillManager.h"
#include "../name/NameManager.h"
#include "../planet/PlanetManager.h"

#include "CreatureManager.h"
#include "CreatureManagerImplementation.h"

#include "../../../ServerCore.h"

#include "../../ZoneProcessServerImplementation.h"

CreatureManagerImplementation* CreatureManagerImplementation::instance = NULL;

CreatureManagerImplementation::CreatureManagerImplementation(Zone* zone, ZoneProcessServerImplementation* serv) : CreatureManagerServant(), Thread(), Mutex("CreatureManager"),
		Lua() {
	CreatureManagerImplementation::zone = zone;

	server = serv;

	scheduler = NULL;

	creatureMap = new CreatureMap(20000);
	lairMap = new LairMap(1000);

	setLoggingName("CreatureManager" + zone->getZoneID());

	setLogging(false);
	setGlobalLogging(true);
}

CreatureManagerImplementation::~CreatureManagerImplementation() {
	if (creatureMap != NULL) {
		delete creatureMap;
		creatureMap = NULL;
	}

	if (lairMap != NULL) {
		delete lairMap;
		lairMap = NULL;
	}

	if (scheduler != NULL) {
		delete scheduler;
		scheduler = NULL;
	}
}

void CreatureManagerImplementation::init() {
	/*ZoneServer* server = zone->getZoneServer();
	scheduler = server->getScheduler();*/

	scheduler = new ScheduleManager("CreatureScheduler");

	instance = this;

	// Scripting
	Lua::init();
	registerFunctions();
	registerGlobals();
}

void CreatureManagerImplementation::loadCreatures() {
	loadCreatureFile();
	loadObjectFile();

	loadTrainers();
	loadRecruiters();
	loadStaticCreatures();
	loadBlueFrogs();
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

	lairMap->resetIterator();

	while (lairMap->hasNext()) {
		LairObject* lair = lairMap->next();

		lair->removeFromZone(true);
		zone->deleteObject(lair);

		lair->removeUndeploymentEvent();
		lair->finalize();
	}

	info("stopped");
}

void CreatureManagerImplementation::loadRecruiters() {
	if (zone->getZoneID() == 8) {
		RecruiterCreature* recruiter1 = spawnRecruiter("", "Recruiter", 0x8C73B91, 36, -5336);
		RecruiterCreature* recruiter2 = spawnRecruiter("", "Recruiter", 0x8C73B91, -1130, -3902);
	} else if (zone->getZoneID() == 5) {
		RecruiterCreature* recruiter3 = spawnRecruiter("", "Recruiter", 0xAFE6BE84, -4936, 4231);
		RecruiterCreature* recruiter4 = spawnRecruiter("", "Recruiter", 0xBCDF9016, -4928, 4231);
	}
}

void CreatureManagerImplementation::loadBlueFrogs() {
	runFile("scripts/creatures/blueFrogSpawns.lua");
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

		uint64 cell = result->getUnsignedLong(7);
		float x = result->getFloat(8);
		float y = result->getFloat(9);
		float z = result->getFloat(10);
		float oY = result->getFloat(11);
		float oW = result->getFloat(12);

		int rand = System::random(2);

		if (rand == 0 && crc1 != 0)
			TrainerCreature* trainer = spawnTrainer(profession, name, "", crc1, cell, x, y, z, oY, oW);
		else if (rand == 1 && crc2 != 0)
			TrainerCreature* trainer = spawnTrainer(profession, name, "", crc2, cell, x, y, z, oY, oW);
		else
			TrainerCreature* trainer = spawnTrainer(profession, name, "", crc3, cell, x, y, z, oY, oW);
	}

	delete result;

	if (zone->getZoneID() == 5) {
		professionManager->professionMap.resetIterator();

		for (int i = 0; professionManager->professionMap.hasNext(); i++) {
			Profession* prof = professionManager->professionMap.getNextValue();

			if ((int)prof->getName().find("jedi") >= 0 || (int)prof->getName().find("force") >= 0)
				continue;

			TrainerCreature* trainer = spawnTrainer(prof->getName(), "", prof->getName(), 0x8C73B91, 0, -4967 - (i*1), 4043, 6, 0, 0);
		}
	}
}

void CreatureManagerImplementation::loadStaticCreatures() {
}

/* TODO:  Rewrite this to use the new lua based spawnCreature.
CreatureGroup* CreatureManagerImplementation::spawnCreatureGroup(int count, const string& stfname, const string& name, int objCrc, float x, float y, int bitmask, int layout) {
	try {
		lock();

		CreatureGroup* group = new CreatureGroup();
		group->deploy();

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
*/

BlueFrogCreature* CreatureManagerImplementation::spawnBlueFrog(float x, float y, float oY, float oW, int type, uint64 cellid, bool doLock) {
	try {
		lock(doLock);

		BlueFrogCreature* bluefrog = new BlueFrogCreature(getNextCreatureID());

		bluefrog->setTerrainName(Terrain::getTerrainName(zone->getZoneID()));

		bluefrog->setHeight(1.0f);
		bluefrog->initializePosition(x, 0, y);
		bluefrog->setParent(instance->getZone()->lookupObject(cellid));
		bluefrog->setDirection(0, 0, oY, oW);
		bluefrog->setPvpStatusBitmask(0);//0x01 + 0x02 + 0x20;
		bluefrog->setBFType(type);

		load(bluefrog);

		bluefrog->insertToZone(zone);

		creatureMap->put(bluefrog->getObjectID(), bluefrog);

		unlock(doLock);
		return bluefrog;
	} catch (...) {
		error("unreported Exception caught on spawnBlueFrog()");

		unlock(doLock);
		return NULL;
	}
}

TrainerCreature* CreatureManagerImplementation::spawnTrainer(const string& profession, const string& stfname, const string& name, int objCrc, uint64 cell, float x, float y, float z, float oy, float ow, bool doLock) {
	try {
		lock(doLock);

		Profession* prof = server->getProfessionManager()->professionMap.get(profession);

		TrainerCreature* trainer = new TrainerCreature(getNextCreatureID(), prof);
		trainer->deploy();

		if (!stfname.empty())
			trainer->setSpeciesName(stfname);
		else
			trainer->setCharacterName(unicode(name));

		trainer->setObjectCRC(objCrc);
		trainer->setObjectFileName("");

		trainer->setTerrainName(Terrain::getTerrainName(zone->getZoneID()));

		trainer->setHeight(1.0f);
		trainer->initializePosition(x, 0, y);
		trainer->setParent(instance->getZone()->lookupObject(cell));
		trainer->setDirection(0, 0, oy, ow);
		trainer->setPvpStatusBitmask(0);
		trainer->setZoneProcessServer(server);

		load(trainer);

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

		RecruiterCreature* recruiter = new RecruiterCreature(getNextCreatureID());
		recruiter->deploy();

		if (!stfname.empty())
			recruiter->setSpeciesName(stfname);
		else
			recruiter->setCharacterName(unicode(name));

		recruiter->setObjectFileName("");
		recruiter->setObjectCRC(objCrc);

		recruiter->setTerrainName(Terrain::getTerrainName(zone->getZoneID()));

		recruiter->setHeight(1.0f);
		recruiter->initializePosition(x, 0, y);
		recruiter->setPvpStatusBitmask(0);

		load(recruiter);

		recruiter->insertToZone(zone);

		creatureMap->put(recruiter->getObjectID(), recruiter);

		unlock(doLock);
		return recruiter;
	} catch (...) {
		error("unreported Exception caught on spawnRecruiter()");

		unlock(doLock);
		return NULL;
	}
}

ShuttleCreature* CreatureManagerImplementation::spawnShuttle(const string& Planet, const string& City, Coordinate* playerSpawnPoint, float x, float y, float z, uint32 tax, bool starport, bool doLock) {
	try {
		lock(doLock);

		ShuttleCreature* shuttle = new ShuttleCreature(Planet, City, playerSpawnPoint, getNextCreatureID(), tax, starport);
		shuttle->deploy();

		shuttle->setTerrainName(Terrain::getTerrainName(zone->getZoneID()));

		shuttle->setHeight(1.0f);
		shuttle->initializePosition(x, z, y);

		shuttle->setCreatureManager(this);
		shuttle->setZoneProcessServer(server);

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


Creature* CreatureManagerImplementation::spawnCreature(uint32 objcrc, uint64 cellid, float x, float y, int bitmask, bool baby, bool doLock) {
	instance->lock(doLock);
	Creature* creature = new Creature(getNextCreatureID());

	try {

		creature->setObjectCRC(objcrc);

		// Load creature from lua
		LuaFunction getCreature(getLuaState(), "getCreature", 1);
		getCreature << objcrc; // push first argument
		callFunction(&getCreature);

		LuaObject result(getLuaState());
		if (!result.isValidTable()) {
			cout << "Unknown object CRC " << objcrc << endl;
			return NULL;
		}

		string objectName = result.getStringField("objectName");
		string stfname = result.getStringField("stfName");
		if (baby)
			stfname += " baby";
		string name = result.getStringField("name");

		if (!stfname.empty())
			creature->setCharacterName(stfname);
		else if (objcrc == 0xBA7F23CD)
			creature->setCharacterName(unicode(instance->makeStormTrooperName()));
		else
			creature->setCharacterName(unicode(instance->makeCreatureName(name)));

		creature->setTerrainName(Terrain::getTerrainName(instance->getZone()->getZoneID()));

		setCreatureAttributes(creature, &result);

		// TODO: Implement baby stats properly
		if(baby) {
			creature->setHealth(creature->getHealth() / 2);
			creature->setAction(creature->getAction() / 2);
			creature->setMind(creature->getMind() / 2);

			creature->setHealthMax(creature->getHealth());
			creature->setActionMax(creature->getAction());
			creature->setMindMax(creature->getMind());

			creature->setBaseHealth(creature->getHealth());
			creature->setBaseAction(creature->getAction());
			creature->setBaseMind(creature->getMind());

			creature->setHeight(creature->getHeight() / 2);
		}

		creature->initializePosition(x, 0.0, y);

		//TODO: add code to set random direction
		float oY = 0;
		float oW = 0;

		creature->setRespawnTimer(0);
		creature->setParent(instance->getZone()->lookupObject(cellid));
		creature->setDirection(0, 0, oY, oW);


		result.pop(); // remove table from stack

		instance->load(creature);

		creature->loadItems();
		creature->insertToZone(zone);

		instance->creatureMap->put(creature->getObjectID(), creature);

	} catch (...) {
		instance->unlock(doLock);
		return NULL;
	}

	instance->unlock(doLock);
	return creature;
}

void CreatureManagerImplementation::setCreatureAttributes(Creature* creature, LuaObject* creatureConfig) {

	creature->setCreatureFaction(creatureConfig->getStringField("faction"));
	creature->setGender(creatureConfig->getStringField("gender"));

	creature->setXP(creatureConfig->getIntField("xp"));

	creature->setHealer(creatureConfig->getIntField("healer"));
	creature->setPack(creatureConfig->getIntField("pack"));
	creature->setHerd(creatureConfig->getIntField("herd"));
	creature->setStalker(creatureConfig->getIntField("stalker"));
	creature->setKiller(creatureConfig->getIntField("killer"));
	creature->setAggressive(creatureConfig->getIntField("aggressive"));

	//creature->setBehaviorScript(creatureConfig.getStringField("behaviorScript"));


	//Harvesting stuff
	creature->setBoneType(creatureConfig->getStringField("boneType"));
	creature->setBoneMax(creatureConfig->getIntField("boneMax"));

	creature->setHideType(creatureConfig->getStringField("hideType"));
	creature->setHideMax(creatureConfig->getIntField("hideMax"));

	creature->setMeatType(creatureConfig->getStringField("meatType"));
	creature->setMeatMax(creatureConfig->getIntField("meatMax"));

	creature->setMilk(creatureConfig->getIntField("milk"));


	//Loot
	creature->setLootGroup(creatureConfig->getStringField("lootGroup"));

	//CH stuff
	creature->setTame(creatureConfig->getFloatField("tame"));

	string preLead;
	try {
		//Testing, if this creature has the alternate weapon field set
		(creature->setCreatureWeapon(creatureConfig->getStringField("alternateWeapon")));
		if (creatureConfig->getStringField("alternateWeapon") !="" ) {
			// No exception: Creature got two weapons
			switch (System::random(1)) {
			case 0:
				preLead = "w";
				break;
			case 1:
				preLead = "alternateW";
				break;
			}
		} else
			preLead = "w";

	} catch (...) {
		//Exception - So likely the creature has only one weapon (if any...)
		preLead = "w";
	}

	try {
		creature->setCreatureWeapon(creatureConfig->getStringField(preLead + "eapon"));
		creature->setCreatureWeaponName(creatureConfig->getStringField(preLead + "eaponName"));
		creature->setCreatureWeaponTemp(creatureConfig->getStringField(preLead + "eaponTemp"));
		creature->setCreatureWeaponClass(creatureConfig->getStringField(preLead + "eaponClass"));
		creature->setCreatureWeaponEquipped(creatureConfig->getIntField(preLead + "eaponEquipped"));
		creature->setCreatureWeaponMinDamage(creatureConfig->getIntField(preLead + "eaponMinDamage"));
		creature->setCreatureWeaponMaxDamage(creatureConfig->getIntField(preLead + "eaponMaxDamage"));
		creature->setCreatureWeaponAttackSpeed(creatureConfig->getFloatField(preLead + "eaponAttackSpeed"));
		creature->setCreatureWeaponDamageType(creatureConfig->getStringField(preLead + "eaponDamageType"));
		creature->setCreatureWeaponArmorPiercing(creatureConfig->getStringField(preLead + "eaponArmorPiercing"));
	} catch (...) {
			// ...the creature has no weapon at all
	}

	creature->setInternalNPCDamageModifier(creatureConfig->getFloatField("internalNPCDamageModifier"));

	//ham stuff - Please remove these IF lines till ELSE after all creature lua's have been changed, its just a safety-net !
	//Test for LUA-line healthMax. Very likely, if this one is missing the others are too..
	if (!creatureConfig->getIntField("healthMax")) {
		creature->setHealth(creatureConfig->getIntField("health"));
		creature->setHealth(creature->getHealth() + (creature->getHealth() * (System::random(100)) / 1111));

		creature->setAction(creatureConfig->getIntField("action"));
		creature->setAction(creature->getAction() + (creature->getAction() * (System::random(100)) / 1111));

		creature->setMind(creatureConfig->getIntField("mind"));
		creature->setMind(creature->getMind() + (creature->getMind() * (System::random(100)) / 1111));
		cout << "ATTENTION: The LUA creature script for " << creature->getSpeciesName()  << " is obv. still in the old format ! \n";
	} else {
		//red
		creature->setHealth(creatureConfig->getIntField("healthMin") + System::random(creatureConfig->getIntField("healthMax")-creatureConfig->getIntField("healthMin")));
		creature->setStrength(creatureConfig->getIntField("strength"));
		creature->setConstitution(creatureConfig->getIntField("constitution"));

		//green
		creature->setAction(creatureConfig->getIntField("actionMin") + System::random(creatureConfig->getIntField("actionMax")-creatureConfig->getIntField("actionMin")));
		creature->setQuickness(creatureConfig->getIntField("quickness"));
		creature->setStamina(creatureConfig->getIntField("stamina"));

		//blue
		creature->setMind(creatureConfig->getIntField("mindMin") + System::random(creatureConfig->getIntField("mindMax")-creatureConfig->getIntField("mindMin")));
		creature->setFocus(creatureConfig->getIntField("focus"));
		creature->setWillpower(creatureConfig->getIntField("willpower"));
	}

	creature->setHealth(creature->getHealth() + (creature->getHealth() * (System::random(100)) / 1111));
	creature->setAction(creature->getAction() + (creature->getAction() * (System::random(100)) / 1111));
	creature->setMind(creature->getMind() + (creature->getMind() * (System::random(100)) / 1111));

	creature->setHealthMax(creature->getHealth());
	creature->setStrengthMax(creature->getStrength());
	creature->setConstitutionMax(creature->getConstitution());
	creature->setActionMax(creature->getAction());
	creature->setQuicknessMax(creature->getQuickness());
	creature->setStaminaMax(creature->getStamina());
	creature->setMindMax(creature->getMind());
	creature->setFocusMax(creature->getFocus());
	creature->setWillpowerMax(creature->getWillpower());

	creature->setBaseHealth(creature->getHealth());
	creature->setBaseStrength(creature->getStrength());
	creature->setBaseConstitution(creature->getConstitution());
	creature->setBaseAction(creature->getAction());
	creature->setBaseQuickness(creature->getQuickness());
	creature->setBaseStamina(creature->getStamina());
	creature->setBaseMind(creature->getMind());
	creature->setBaseFocus(creature->getFocus());
	creature->setBaseWillpower(creature->getWillpower());

	creature->setArmor(creatureConfig->getIntField("armor"));

	creature->setKinetic(creatureConfig->getFloatField("kinetic"));
	creature->setEnergy(creatureConfig->getFloatField("energy"));
	creature->setElectricity(creatureConfig->getFloatField("electricity"));
	creature->setStun(creatureConfig->getFloatField("stun"));
	creature->setBlast(creatureConfig->getFloatField("blast"));
	creature->setHeat(creatureConfig->getFloatField("heat"));
	creature->setCold(creatureConfig->getFloatField("cold"));
	creature->setAcid(creatureConfig->getFloatField("acid"));
	creature->setLightSaber(creatureConfig->getFloatField("lightSaber"));

	creature->setHeight(creatureConfig->getFloatField("height"));

	creature->setAccuracy(creatureConfig->getIntField("accuracy"));
	creature->setSpeed(creatureConfig->getFloatField("speed"));
	creature->setAcceleration(creatureConfig->getFloatField("acceleration"));
	creature->setRespawnTimer(creatureConfig->getIntField("respawnTimer"));
	creature->setLevel(creatureConfig->getIntField("level"));
	creature->setPvpStatusBitmask(creatureConfig->getIntField("combatFlags"));
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

LairObject* CreatureManagerImplementation::spawnLair(const string& type, float x, float y, float z, bool doLock) {
	LairObject* lair;

	lock(doLock);

	try {

		// Load lair from lua
		LuaFunction getObject(getLuaState(), "getObject", 1);
		string typeStr = type;
		getObject << typeStr; // push first argument
		callFunction(&getObject);

		LuaObject result(getLuaState());
		if (!result.isValidTable()) {
			cout << "Unknown lair type " << typeStr << endl;
			return NULL;
		}

		uint32 objectCRC = result.getLongField("objectCRC");

		cout << "CRC = " << objectCRC << endl;

		lair = new LairObject(objectCRC, getNextCreatureID());

		//string objectName = result.getStringField("objectName");
		string stfname = result.getStringField("stfName");

		cout << "Setup lair type " << typeStr << endl;

		int planet = result.getIntField("planet");

		if (planet != instance->getZone()->getZoneID()) {
			info("Lair spawned to wrong planet");
			return NULL;
		}
		lair->deploy();

		int maxCondition = result.getIntField("maxCondition");

		lair->setMaxCondition(maxCondition);

		string stfName = result.getStringField("stfName");

		lair->setTemplateName(stfName);

		uint32 creatureCRC = result.getIntField("creatureCRC");
		int	spawnSize = result.getIntField("spawnSize");
		int babiesPerMillion = result.getIntField("babiesPerMillion");

		result.pop();

		lair->setCreatureCRC(creatureCRC);
		lair->setSpawnSize(spawnSize);
		lair->setBabiesPerMillion(babiesPerMillion);

		lair->initializePosition(x, z, y);

		lair->insertToZone(instance->getZone());
		lairMap->put(lair->getObjectID(), lair);

		lair->spawnCreatures();

		unlock(doLock);
		return  lair;
	} catch (...) {
		error("unreported Exception caught on spawnLair()");

		instance->unlock(doLock);
		return NULL;
	}
}

void CreatureManagerImplementation::load(Creature* creature) {
	creature->setCreatureManager(this);
	creature->setZoneProcessServer(server);

	// Load skills from lua's
	LuaFunction getCreature(getLuaState(), "getCreature", 1);
	getCreature << creature->getObjectCRC(); // push first argument
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

int CreatureManagerImplementation::addBlueFrog(lua_State *L) {
	LuaObject creatureConfig(L);

	if (!creatureConfig.isValidTable())
		return 1;

	float x = creatureConfig.getFloatField("X");
	float y = creatureConfig.getFloatField("Y");
	float oY = creatureConfig.getFloatField("oY");
	float oW = creatureConfig.getFloatField("oW");
	int type = creatureConfig.getIntField("bfType");
	uint64 cellid = creatureConfig.getLongField("cellId");

	instance->spawnBlueFrog(x,y,oY,oW,type,cellid);

	return 0;
}

int CreatureManagerImplementation::addCreature(lua_State *L) {
	LuaObject creatureConfig(L);

	if (!creatureConfig.isValidTable())
		return 1;

	int planet = creatureConfig.getIntField("planet");

	if (planet != instance->getZone()->getZoneID())
		return 1;

	instance->lock();

	Creature* creature = new Creature(instance->getNextCreatureID());
	creature->deploy();

	string objectName = creatureConfig.getStringField("objectName");
	string stfname = creatureConfig.getStringField("stfName");
	string name = creatureConfig.getStringField("name");

	creature->setObjectCRC(creatureConfig.getIntField("objectCRC"));


	if (!stfname.empty())
		creature->setCharacterName(stfname);
	else
		if (creature->getObjectCRC() == 0xBA7F23CD)
			creature->setCharacterName(unicode(instance->makeStormTrooperName()));

		else if (creature->getObjectCRC() == 0x4E38DA33)
			creature->setCharacterName(unicode(instance->makeDarkTrooperName()));

		else
			creature->setCharacterName(unicode(instance->makeCreatureName(name)));

	creature->setTerrainName(Terrain::getTerrainName(planet));


	try {
		string dummy = creatureConfig.getStringField("faction");
		dummy = creatureConfig.getStringField("gender");
		dummy = creatureConfig.getStringField("boneType");
		dummy = creatureConfig.getStringField("hideType");
		dummy = creatureConfig.getStringField("meatType");
	} catch (...) {
		cout << "The LUA script for \'" << objectName << "\' is at least missing one of these fields:\n";
		cout << "faction, gender, boneType,hideType,meatType.\nMake sure they do exist in the lua script!\n\n";
		instance->unlock();
		return 1;
	}

	instance->setCreatureAttributes(creature, &creatureConfig);

	uint64 cellID = creatureConfig.getLongField("cellID");

	float x = creatureConfig.getFloatField("positionX");
	float y = creatureConfig.getFloatField("positionY");
	float z = creatureConfig.getFloatField("positionZ");

	creature->initializePosition(x, z, y);

	creature->setSpawnPosition(x, z, y, cellID);

	creature->setParent(instance->getZone()->lookupObject(cellID));

	instance->load(creature);

	creature->loadItems();
	creature->insertToZone(instance->zone);

	instance->creatureMap->put(creature->getObjectID(), creature);
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

	LairObject* lair = new LairObject(objectCRC, instance->getNextCreatureID());
	lair->deploy();

	float x = object.getFloatField("positionX");
	float y = object.getFloatField("positionY");
	float z = object.getFloatField("positionZ");
	int maxCondition = object.getIntField("maxCondition");

	lair->setMaxCondition(maxCondition);

	string stfName = object.getStringField("stfName");

	lair->setTemplateName(stfName);

	uint32 creatureCRC = object.getIntField("creatureCRC");
	int	spawnSize = object.getIntField("spawnSize");
	int babiesPerMillion = object.getIntField("babiesPerMillion");

	object.pop();

	lair->setCreatureCRC(creatureCRC);
	lair->setSpawnSize(spawnSize);
	lair->setBabiesPerMillion(babiesPerMillion);

	lair->initializePosition(x, z, y);

	lair->insertToZone(instance->getZone());
	lair->spawnCreatures();

	instance->lairMap->put(lair->getObjectID(), lair);

	instance->unlock();

	return 0;
}

int CreatureManagerImplementation::runCreatureFile(lua_State* L) {
	string filename = getStringParameter(L);

	runFile("scripts/creatures/" + filename, L);

	return 0;
}

int CreatureManagerImplementation::runObjectFile(lua_State* L) {
	string filename = getStringParameter(L);

	runFile("scripts/sceneobjects/" + filename, L);

	return 0;
}

void CreatureManagerImplementation::registerFunctions() {
	//lua generic
	lua_register(getLuaState(), "RunCreatureFile", runCreatureFile);
	lua_register(getLuaState(), "RunObjectFile", runObjectFile);

	lua_register(getLuaState(), "AddCreatureToServer", addCreature);
	lua_register(getLuaState(), "AddLairToServer", addLair);

	lua_register(getLuaState(), "AddBlueFrogToServer", addBlueFrog);
}

void CreatureManagerImplementation::registerGlobals() {
	setGlobalInt("ATTACKABLE_FLAG", 1);
	setGlobalInt("AGGRESSIVE_FLAG", 2);
	setGlobalInt("ENEMY_FLAG", 0x20);
	setGlobalInt("NPC_FLAG", 0x15);
	setGlobalInt("PLANET_ID", instance->zone->getZoneID());
	setGlobalInt("JAWA", BlueFrogCreatureImplementation::JAWA);
	setGlobalInt("GUNGAN", BlueFrogCreatureImplementation::GUNGAN);
	setGlobalInt("BARTENDER", BlueFrogCreatureImplementation::BARTENDER);
	setGlobalInt("MEDDROID", BlueFrogCreatureImplementation::MEDDROID);
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

string CreatureManagerImplementation::makeDarkTrooperName() {
	stringstream characterName;

	switch (System::random(4)) {
	case 0:
		characterName << "GL";
		break;
	case 1:
		characterName << "KP";
		break;
	case 2:
		characterName << "RV";
		break;
	case 3:
		characterName << "TM";
		break;
	case 4:
		characterName << "VX";
		break;
	}

	characterName << "N-" << System::random(490)+10;

	return characterName.str();
}

string CreatureManagerImplementation::makeCreatureName(string charname) {

	stringstream newname;
	newname << server->getNameManager()->makeCreatureName(System::random(1)) << " (" << charname << ")";

	return newname.str();
}

inline string CreatureManagerImplementation::stringify(const int x) {
	ostringstream o;

	if (!(o << x))
		return "";
	else
		return o.str();
}



