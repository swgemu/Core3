/*
 * DNAManager.cpp
 *
 *  Created on: July 7, 2012
 *      Author: washu
 */

#include "DnaManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/CreatureTemplate.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"
#include "server/zone/objects/tangible/deed/pet/PetDeed.h"
#include "server/zone/managers/crafting/labratories/Genetics.h"
#include "server/zone/managers/crafting/CraftingManager.h"

// #define DEBUG_GENETIC_LAB
// #define DEBUG_GENERATION_SAMPLE
// #define WRITE_DNA_TABLE

AtomicInteger DnaManager::loadedDnaData;

DnaManager::DnaManager() : Logger("DnaManager") {
	lua = new Lua();
	lua->init();
	lua->registerFunction("addQualityTemplate", addQualityTemplate);

	lua->setGlobalInt("FORTITUDE", DnaManager::FORTITUDE);
	lua->setGlobalInt("ENDURANCE", DnaManager::ENDURANCE);
	lua->setGlobalInt("CLEVERNESS", DnaManager::CLEVERNESS);
	lua->setGlobalInt("COURAGE", DnaManager::COURAGE);
	lua->setGlobalInt("POWER", DnaManager::POWER);
	lua->setGlobalInt("DEPENDABILITY", DnaManager::DEPENDABILITY);
	lua->setGlobalInt("DEXTERITY", DnaManager::DEXTERITY);
	lua->setGlobalInt("FIERCENESS", DnaManager::FIERCENESS);
	lua->setGlobalInt("HARDINESS", DnaManager::HARDINESS);
	lua->setGlobalInt("INTELLIGENCE", DnaManager::INTELLIGENCE);
}

DnaManager::~DnaManager() {
	if (lua != nullptr) {
		delete lua;
		lua = nullptr;
	}
}

void DnaManager::loadSampleData() {
	info("Loading DNA Information",true);
	try {
		lua->runFile("scripts/managers/dna_manager.lua");
		LuaObject luaObject = lua->getGlobalObject("DNACharacteristics");

#ifdef WRITE_DNA_TABLE
		FileWriter* writer = new FileWriter(new File("scripts/managers/dna_manager_new.lua"));
#endif

			if (luaObject.isValidTable()) {
#ifdef WRITE_DNA_TABLE
				int lastDam = 0;
				int lastHAM = 2000;
				float lastHit = 0.100f;
				int lastArmor = 0;
				int lastRegen = 0;
#endif

				for (int i = 1; i <= luaObject.getTableSize(); ++i) {
					LuaObject statRow = luaObject.getObjectAt(i);

					if (statRow.isValidTable()) {
						int level = statRow.getIntAt(1);
						int dps = statRow.getIntAt(2);
						float hit = statRow.getFloatAt(3);
						int ham = statRow.getIntAt(4);
						int armorBase = statRow.getIntAt(5);
						int regen = statRow.getIntAt(6);

#ifdef WRITE_DNA_TABLE
						StringBuffer table;

						if (i <= 20) {
							lastDam = (i * 2);
							lastHAM = ((i - 1) * 100.f) + 3000;
							lastHit = ((i - 1) * 1.00f) + 10.0f;
							lastArmor = 0;
							lastRegen = ((i - 1) * 4.00f) + 4.0f;

							table << "	{ " << level << ", " << lastDam << ", " << lastHit << ", " << lastHAM << ", " << lastArmor << ", " << lastRegen << "},";
						} else if (i <= 30) {
							lastDam += 10;
							lastHAM += 250;
							lastHit += 0.30f;
							lastArmor += 25;
							lastRegen += 3.0f;

							table << "	{ " << level << ", " << lastDam << ", " << lastHit << ", " << lastHAM << ", " << lastArmor << ", " << lastRegen << "},";
						} else if (i <= 40) {
							lastDam += 10;
							lastHAM += 200;
							lastHit += 0.30f;
							lastArmor += 25;
							lastRegen += 3.0f;

							table << "	{ " << level << ", " << lastDam << ", " << lastHit << ", " << lastHAM << ", " << lastArmor << ", " << lastRegen << "},";
						} else if (i <= 50) {
							lastDam += 3;
							lastHAM += 50;
							lastHit += 0.20f;
							lastArmor += 50;
							lastRegen += 2.0f;

							table << "	{ " << level << ", " << lastDam << ", " << lastHit << ", " << lastHAM << ", " << lastArmor << ", " << lastRegen << "},";
						} else if (i <= 60) {
							lastDam += 2;
							lastHAM += 50;
							lastHit += 0.20f;
							lastArmor += 50;
							lastRegen += 2.0f;

							table << "	{ " << level << ", " << lastDam << ", " << lastHit << ", " << lastHAM << ", " << lastArmor << ", " << lastRegen << "},";
						} else {
							lastDam += 2;
							lastHAM += 100;
							lastHit += 0.225f;
							lastArmor += 50;
							lastRegen += 2.0f;

							table << "	{ " << level << ", " << lastDam << ", " << lastHit << ", " << lastHAM << ", " << lastArmor << ", " << lastRegen << "},";
						}

						writer->writeLine(table.toString());
#endif

						dnaDPS.add(dps);
						dnaArmor.add(armorBase);
						dnaHam.add(ham);
						dnaHit.add(hit);
						dnaRegen.add(regen);
					}
					statRow.pop();
				}
			}
			luaObject.pop();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
	info("Loaded " + String::valueOf(dnaDPS.size()) + " dna stats.", true);
	delete lua;
	lua = nullptr;
}

int DnaManager::generateXp(int creatureLevel) {
	float x1 = 0.00001896378 * (creatureLevel * 4);
	float x2 = 0.0025801845 * (creatureLevel * 3);
	float x3 = 0.1673150401 * (creatureLevel * 2);
	float x4 = 6.757844921 * creatureLevel;
	float x5 = 46.75746899f;
	return (int)ceil(x1-x2+x3+x4+x5);
}
int DnaManager::addQualityTemplate(lua_State * L) {
	int qual = lua_tointeger(L,-2);
	String ascii = lua_tostring(L,-1);
	uint32 crc = (uint32) ascii.hashCode();
	DnaManager::instance()->qualityTemplates.put(qual,crc);
	return 0;
}

void DnaManager::generationalSample(PetDeed* deed, CreatureObject* player, int quality) {
	if (deed == nullptr || player == nullptr)
		return;

#ifdef DEBUG_GENERATION_SAMPLE
	info(true) << "DnaManager::generationalSample - called";
#endif

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return;

	auto craftingManager = zoneServer->getCraftingManager();

	if (craftingManager == nullptr)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr)
		return;

	if (inventory->isContainerFullRecursive()) {
		StringIdChatParameter err("survey", "no_inv_space");
		player->sendSystemMessage(err);
		player->setPosture(CreaturePosture::UPRIGHT, true);

		return;
	}

	const CreatureTemplate* creatureTemplate = deed->getCreatureTemplate();

	if (creatureTemplate == nullptr) {
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "generationalSample - Creature Template is null";
#endif
		return;
	}

	int ferocity = creatureTemplate->getFerocity();
	int creatureLevel = deed->getLevel();

	int hardiness = Genetics::hamToValue(deed->getHealth(), quality);
	int fortitude = Genetics::randomizeValue(deed->getFortitude(), quality);
	int dexterity = Genetics::hamToValue(deed->getAction(), quality);
	int endurance = Genetics::randomizeValue(500, quality);
	int intellect = Genetics::hamToValue(deed->getMind(), quality);
	int cleverness = Genetics::hitChanceToValue(deed->getHitChance(), quality);
	int dependability = Genetics::dietToValue(creatureTemplate->getDiet(), quality);
	int courage = Genetics::meatTypeToValue(creatureTemplate->getMeatType(), quality);
	int fierceness = Genetics::ferocityToValue(ferocity, quality);
	int power = Genetics::damageToValue((deed->getMinDamage() + deed->getMaxDamage()) / 2, quality);

#ifdef DEBUG_GENERATION_SAMPLE
	info(true) << "Hardiness: " << hardiness;
	info(true) << "Fortitude: " << fortitude;
	info(true) << "Dexterity: " << dexterity;
	info(true) << "Endurance: " << endurance;
	info(true) << "Intellect: " << intellect;
	info(true) << "Cleverness: " << cleverness;
	info(true) << "Dependability: " << dependability;
	info(true) << "Courage: " << courage;
	info(true) << "Fierceness: " << fierceness;
	info(true) << "Power: " << power;
#endif

	// calculate rest of stats here
	ManagedReference<DnaComponent*> prototype = zoneServer->createObject(qualityTemplates.get(quality), 1).castTo<DnaComponent*>();

	if (prototype == nullptr) {
		return;
	}

	Locker clocker(prototype);

	// Check Here for unique npcs
	prototype->setSource(deed->getTemplateName());
	prototype->setQuality(quality);
	prototype->setLevel(creatureLevel);

	String serial = craftingManager->generateSerial();

	// Set Serial Number
	prototype->setSerialNumber(serial);

	// Set Genetic Stats
	prototype->setStats(cleverness, endurance, fierceness, power, intellect, courage, dependability, dexterity, fortitude, hardiness);

	prototype->setStun(deed->getStun());
	prototype->setKinetic(deed->getKinetic());
	prototype->setEnergy(deed->getEnergy());
	prototype->setBlast(deed->getBlast());
	prototype->setHeat(deed->getHeat());
	prototype->setCold(deed->getCold());
	prototype->setElectric(deed->getElectric());
	prototype->setAcid(deed->getAcid());
	prototype->setSaber(deed->getSaber());
	prototype->setRanged(deed->getRanged());
	prototype->setArmorRating(deed->getArmor());
	prototype->setSpecialAttackOne(deed->getSpecial1());
	prototype->setSpecialAttackTwo(deed->getSpecial2());

	// info(true) << "DnaManager::generationalSample - checking resistances";

	if (deed->isSpecialResist(SharedWeaponObjectTemplate::STUN)) {
		prototype->setSpecialResist(SharedWeaponObjectTemplate::STUN);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist STUN";
#endif
	}
	if (deed->isSpecialResist(SharedWeaponObjectTemplate::KINETIC)) {
		prototype->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist KINETIC";
#endif
	}
	if (deed->isSpecialResist(SharedWeaponObjectTemplate::ENERGY)) {
		prototype->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist ENERGY";
#endif
	}
	if (deed->isSpecialResist(SharedWeaponObjectTemplate::BLAST)) {
		prototype->setSpecialResist(SharedWeaponObjectTemplate::BLAST);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist BLAST";
#endif
	}
	if (deed->isSpecialResist(SharedWeaponObjectTemplate::HEAT)) {
		prototype->setSpecialResist(SharedWeaponObjectTemplate::HEAT);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist HEAT";
#endif
	}
	if (deed->isSpecialResist(SharedWeaponObjectTemplate::COLD)) {
		prototype->setSpecialResist(SharedWeaponObjectTemplate::COLD);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist COLD";
#endif
	}
	if (deed->isSpecialResist(SharedWeaponObjectTemplate::ELECTRICITY)) {
		prototype->setSpecialResist(SharedWeaponObjectTemplate::ELECTRICITY);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist ELECTRICITY";
#endif
	}
	if (deed->isSpecialResist(SharedWeaponObjectTemplate::ACID)) {
		prototype->setSpecialResist(SharedWeaponObjectTemplate::ACID);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist ACID";
#endif
	}

	/*if (deed->isSpecialResist(SharedWeaponObjectTemplate::LIGHTSABER))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::LIGHTSABER);
#ifdef DEBUG_GENERATION_SAMPLE
		info(true) << "setting special resist LIGHTSABER";
#endif
	*/

	Locker locker(inventory, prototype);

	if (inventory->transferObject(prototype, -1, true, false)) {
		inventory->broadcastObject(prototype, true);
	} else {
		prototype->destroyObjectFromDatabase(true);
	}
}

void DnaManager::generateSample(Creature* creature, CreatureObject* player, int quality){
	if (quality < 0 || quality > 7) {
		return;
	}

	if (creature == nullptr || player == nullptr)
		return;

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return;

	auto craftingManager = zoneServer->getCraftingManager();

	if (craftingManager == nullptr)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr)
		return;

	if (inventory->isContainerFullRecursive()) {
		StringIdChatParameter err("survey", "no_inv_space");

		player->sendSystemMessage(err);
		player->setPosture(CreaturePosture::UPRIGHT, true);

		return;
	}

	Locker lock(creature, player);

	auto creatureTemplate = dynamic_cast<const CreatureTemplate*>(creature->getCreatureTemplate());

	if (creatureTemplate == nullptr)
		return;

	int ferocity = creatureTemplate->getFerocity();
	int creatureLevel = creature->getLevel();

	int hardiness = Genetics::hamToValue(creature->getMaxHAM(0), quality);
	int fortitude = Genetics::resistanceToValue(creature->getEffectiveResist(), creature->getArmor(), quality);
	int dexterity = Genetics::hamToValue(creature->getMaxHAM(3), quality);
	int endurance = Genetics::randomizeValue(500, quality);
	int intellect = Genetics::hamToValue(creature->getMaxHAM(6), quality);
	int cleverness = Genetics::hitChanceToValue(creature->getChanceHit(), quality);
	int dependability = Genetics::dietToValue(creatureTemplate->getDiet(), quality);
	int courage = Genetics::meatTypeToValue(creatureTemplate->getMeatType(), quality);
	int fierceness = Genetics::ferocityToValue(ferocity, quality);
	int power = Genetics::damageToValue((creature->getDamageMin() + creature->getDamageMax()) / 2, quality);

	// We should now have enough to generate a sample
	ManagedReference<DnaComponent*> prototype = zoneServer->createObject(qualityTemplates.get(quality), 1).castTo<DnaComponent*>();

	if (prototype == nullptr) {
		return;
	}

	Locker clocker(prototype);

	// Check Here for unique npcs
	const StringId* nameId = creature->getObjectName();

	if (nameId->getFile().isEmpty() || nameId->getStringID().isEmpty()) {
		prototype->setSource(creature->getCreatureName().toString());
	} else {
		prototype->setSource(nameId->getFullPath());
	}

	prototype->setQuality(quality);
	prototype->setLevel(creatureLevel);

	String serial = craftingManager->generateSerial();

	prototype->setSerialNumber(serial);
	prototype->setStats(cleverness, endurance, fierceness, power, intellect, courage, dependability, dexterity, fortitude, hardiness);
	prototype->setStun(creatureTemplate->getStun());
	prototype->setKinetic(creatureTemplate->getKinetic());
	prototype->setEnergy(creatureTemplate->getEnergy());
	prototype->setBlast(creatureTemplate->getBlast());
	prototype->setHeat(creatureTemplate->getHeat());
	prototype->setCold(creatureTemplate->getCold());
	prototype->setElectric(creatureTemplate->getElectricity());
	prototype->setAcid(creatureTemplate->getAcid());
	prototype->setSaber(creatureTemplate->getLightSaber());
	prototype->setArmorRating(creatureTemplate->getArmor());

	bool hasRanged = false;

	if (creature->isAiAgent()) {
		auto agent = creature->asAiAgent();

		if (agent != nullptr)
			hasRanged = agent->hasRangedWeapon();
	}

	prototype->setRanged(hasRanged);

	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::STUN))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::STUN);
	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::KINETIC))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::ENERGY))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);
	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::BLAST))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::BLAST);
	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::HEAT))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::HEAT);
	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::COLD))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::COLD);
	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::ELECTRICITY))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::ELECTRICITY);
	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::ACID))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::ACID);
	if (creatureTemplate->isSpecialProtection(SharedWeaponObjectTemplate::LIGHTSABER))
		prototype->setSpecialResist(SharedWeaponObjectTemplate::LIGHTSABER);

	auto attackMap = creatureTemplate->getPrimaryAttacks();

	if (attackMap->size() > 0) {
		prototype->setSpecialAttackOne(String(attackMap->getCommand(0)));
		if(attackMap->size() > 1) {
			prototype->setSpecialAttackTwo(String(attackMap->getCommand(1)));
		}
	}

	Locker locker(inventory);

	if (inventory->transferObject(prototype, -1, true, false)) {
		inventory->broadcastObject(prototype, true);
	} else {
		prototype->destroyObjectFromDatabase(true);
	}
}

float DnaManager::valueForLevel(int type, int level) {
	float rc = 0;
	switch(type) {
		case HIT_LEVEL:
			return dnaHit.get(level);
		case DPS_LEVEL:
			return dnaDPS.get(level);
		case HAM_LEVEL:
			return dnaHam.get(level);
		case ARM_LEVEL:
			return dnaArmor.get(level);
		case REG_LEVEL:
			return dnaRegen.get(level);
	}
	return rc;
}

int DnaManager::levelForScore(int type, float value) {
	int rc = 0;

	switch (type) {
		case HIT_LEVEL:
			value *= 100.00f;

			for (int i = 0; i < dnaHit.size(); i++) {
				float lvminus = 1.00f, lvplus = 3.00f;

				if (i > 0)
					lvminus = dnaHit.get(i - 1);

				if (i < (dnaHit.size() - 1))
					lvplus = dnaHit.get(i + 1);

				float lv = dnaHit.get(i);

				if (value >= (lvminus + lv) / 2.000f && value <= (lvplus + lv) / 2.000f) {
					rc = i;
					break;
				}
			}

#ifdef DEBUG_GENETIC_LAB
			info(true) << "HIT_LEVEL - Checking: " << value << " Returning: " << rc;
#endif
			break;
		case DPS_LEVEL:
			for (int i = 0; i < dnaDPS.size(); i++) {
				float lvminus = 0, lvplus = 1000;

				if (i > 0)
					lvminus = dnaDPS.get(i - 1);

				if (i < (dnaDPS.size() - 1))
					lvplus = dnaDPS.get(i + 1);

				float lv = dnaDPS.get(i);

				if (value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}
#ifdef DEBUG_GENETIC_LAB
			info(true) << "DPS_LEVEL - Checking: " << value << " Returning: " << rc;
#endif
			break;
		case HAM_LEVEL:
			for (int i = 0; i < dnaHam.size(); i++) {
				float lvminus = 0, lvplus = 500000;

				if (i > 0)
					lvminus = dnaHam.get(i - 1);

				if (i < (dnaHam.size() - 1))
					lvplus = dnaHam.get(i + 1);

				float lv = dnaHam.get(i);

				if (value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}

#ifdef DEBUG_GENETIC_LAB
			info(true) << "HAM_LEVEL - Checking: " << value << " Returning: " << rc;
#endif
			break;
		case ARM_LEVEL:
			for (int i = 0; i < dnaArmor.size(); i++) {
				float lvminus = 0, lvplus = 2000;

				if (i > 0)
					lvminus = dnaArmor.get(i - 1);

				if (i < (dnaArmor.size() - 1))
					lvplus = dnaArmor.get(i + 1);

				float lv = dnaArmor.get(i);

				if (value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}
#ifdef DEBUG_GENETIC_LAB
			info(true) << "ARM_LEVEL - Checking: " << value << " Returning: " << rc;
#endif
			break;
		case REG_LEVEL:
			for (int i = 0; i < dnaRegen.size(); i++) {
				float lvminus = 0, lvplus = 50000;

				if (i > 0)
					lvminus = dnaRegen.get(i - 1);

				if (i < (dnaRegen.size() - 1))
					lvplus = dnaRegen.get(i + 1);

				float lv = dnaRegen.get(i);

				if (value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}
#ifdef DEBUG_GENETIC_LAB
			info(true) << "REG_LEVEL - Checking: " << value << " Returning: " << rc;
#endif
			break;
		default:
			rc = 0;
	}

	return rc;
}
