/*
 * DNAManager.cpp
 *
 *  Created on: July 7, 2012
 *      Author: washu
 */

#include "DnaManager.h"
#include "server/conf/ConfigManager.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/templates/tangible/DnaSampleTemplate.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"
#include "server/zone/objects/tangible/deed/pet/PetDeed.h"
#include "server/zone/managers/crafting/labratories/Genetics.h"

AtomicInteger DnaManager::loadedDnaData;

DnaManager::DnaManager() : Logger("DnaManager") {
	lua = new Lua();
	lua->init();
	lua_register(lua->getLuaState(), "addQualityTemplate", addQualityTemplate);

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

}

void DnaManager::loadSampleData() {
	info("Loading DNA Information",true);
	try {
		lua->runFile("scripts/managers/dna_manager.lua");
		// pull stat balcne out and set it up.
		LuaObject luaObject = lua->getGlobalObject("DNACharacteristics");

			if (luaObject.isValidTable()) {
				for (int i = 1; i <= luaObject.getTableSize(); ++i) {
					LuaObject statRow = luaObject.getObjectAt(i);

					if (statRow.isValidTable()) {
						int level = statRow.getIntAt(1);
						int dps = statRow.getIntAt(2);
						float hit = statRow.getFloatAt(3);
						int ham = statRow.getIntAt(4);
						int armorBase = statRow.getIntAt(5);
						int regen = statRow.getIntAt(6);
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
	lua = NULL;
}

int DnaManager::generateXp(int creatureLevel) {
	float x1 = 0.00001896378 * (creatureLevel * 4);
	float x2 = 0.0025801845 * (creatureLevel * 3);
	float x3 = 0.1673150401 * (creatureLevel * 2);
	float x4 = 6.757844921 * creatureLevel;
	float x5 = 46.75746899;
	return (int)ceil(x1-x2+x3+x4+x5);
}
int DnaManager::addQualityTemplate(lua_State * L) {
	int qual = lua_tointeger(L,-2);
	String ascii = lua_tostring(L,-1);
	uint32 crc = (uint32) ascii.hashCode();
	DnaManager::instance()->qualityTemplates.put(qual,crc);
	return 0;
}
void DnaManager::generationalSample(PetDeed* deed, CreatureObject* player,int quality) {
	// We are making a generational sample rules are a little different.
	// Reduce each stat by lets say 10% as the max to be on par with old docs
	int cl = deed->getLevel();
	int ferocity = 0; // 1 highest 7 lowest
	int factor = (int)System::random(quality) - 7;
	int reductionAmount = (factor + 15 + quality) ;
	int cle = reduceByPercent(deed->getCleverness(),reductionAmount);
	int cou = reduceByPercent(deed->getCourage(),reductionAmount);
	int dep = reduceByPercent(deed->getDependency(),reductionAmount);
	int dex = reduceByPercent(deed->getDexterity(),reductionAmount);
	int end = reduceByPercent(deed->getEndurance(),reductionAmount);
	int fie = reduceByPercent(deed->getFierceness(),reductionAmount);
	int frt = reduceByPercent(deed->getFortitude(),reductionAmount);
	int har = reduceByPercent(deed->getHardiness(),reductionAmount);
	int ite = reduceByPercent(deed->getIntelligence(),reductionAmount);
	int pow = reduceByPercent(deed->getPower(),reductionAmount);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory->isContainerFullRecursive()) {
		StringIdChatParameter err("survey", "no_inv_space");
		player->sendSystemMessage(err);
		player->setPosture(CreaturePosture::UPRIGHT, true);
		return;
	}

	// calculate rest of stats here
	ManagedReference<DnaComponent*> prototype = player->getZoneServer()->createObject(qualityTemplates.get(quality), 1).castTo<DnaComponent*>();
	if (prototype == NULL) {
		return;
	}
	Locker clocker(prototype);
	// Check Here for unique npcs
	prototype->setSource(deed->getTemplateName());
	prototype->setQuality(quality);
	prototype->setLevel(cl);
	String serial = player->getZoneServer()->getCraftingManager()->generateSerial();
	prototype->setSerialNumber(serial);
	prototype->setStats(cle,end,fie,pow,ite,cou,dep,dex,frt,har);
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
	if (deed->isSpecialResist(WeaponObject::STUN))
		prototype->setSpecialResist(WeaponObject::STUN);
	if (deed->isSpecialResist(WeaponObject::KINETIC))
		prototype->setSpecialResist(WeaponObject::KINETIC);
	if (deed->isSpecialResist(WeaponObject::ENERGY))
		prototype->setSpecialResist(WeaponObject::ENERGY);
	if (deed->isSpecialResist(WeaponObject::BLAST))
		prototype->setSpecialResist(WeaponObject::BLAST);
	if (deed->isSpecialResist(WeaponObject::HEAT))
		prototype->setSpecialResist(WeaponObject::HEAT);
	if (deed->isSpecialResist(WeaponObject::COLD))
		prototype->setSpecialResist(WeaponObject::COLD);
	if (deed->isSpecialResist(WeaponObject::ELECTRICITY))
		prototype->setSpecialResist(WeaponObject::ELECTRICITY);
	if (deed->isSpecialResist(WeaponObject::ACID))
		prototype->setSpecialResist(WeaponObject::ACID);
	if (deed->isSpecialResist(WeaponObject::LIGHTSABER))
		prototype->setSpecialResist(WeaponObject::LIGHTSABER);

	Locker locker(inventory);
	if (inventory->transferObject(prototype, -1, true, false)) {
		inventory->broadcastObject(prototype, true);
	} else {
		prototype->destroyObjectFromDatabase(true);
	}

}
void DnaManager::generateSample(Creature* creature, CreatureObject* player,int quality){
	if (quality < 0 || quality > 7) {
		return;
	}
	Locker lock(creature,player);
	CreatureTemplate* creatureTemplate = dynamic_cast<CreatureTemplate*>(creature->getCreatureTemplate());

	int ferocity = creatureTemplate->getFerocity();
	int cl = creature->getLevel();
	int cle = Genetics::hitChanceToValue(creature->getChanceHit(),quality);
	int cou = Genetics::meatTypeToValue(creature->getMeatType(),quality);
	int dep = Genetics::dietToValue(creature->getDiet(),quality);
	int dex = Genetics::hamToValue(creature->getMaxHAM(3),quality);
	int end = Genetics::accelerationToValue(creature->getWalkAcceleration(),quality);
	int fie = Genetics::ferocityToValue(ferocity,quality);
	int frt = Genetics::resistanceToValue(creature->getEffectiveResist(),creature->getArmor(),quality);
	int har = Genetics::hamToValue(creature->getMaxHAM(0),quality);
	int ite = Genetics::hamToValue(creature->getMaxHAM(6),quality);
	int pow = Genetics::damageToValue((creature->getDamageMax() + creature->getDamageMin())/2,quality);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory->isContainerFullRecursive()) {
		StringIdChatParameter err("survey", "no_inv_space");
		player->sendSystemMessage(err);
		player->setPosture(CreaturePosture::UPRIGHT, true);
		return;
	}

	// We should now have enough to generate a sample
	ManagedReference<DnaComponent*> prototype = player->getZoneServer()->createObject(qualityTemplates.get(quality), 1).castTo<DnaComponent*>();
	if (prototype == NULL) {
		return;
	}
	Locker clocker(prototype);
	// Check Here for unique npcs
	StringId* nameId = creature->getObjectName();
	if (nameId->getFile().isEmpty() || nameId->getStringID().isEmpty()) {
		prototype->setSource(creature->getCreatureName().toString());
	} else {
		prototype->setSource(nameId->getFullPath());
	}
	prototype->setQuality(quality);
	prototype->setLevel(cl);
	String serial = player->getZoneServer()->getCraftingManager()->generateSerial();
	prototype->setSerialNumber(serial);
	prototype->setStats(cle,end,fie,pow,ite,cou,dep,dex,frt,har);
	prototype->setStun(creatureTemplate->getStun());
	prototype->setKinetic(creatureTemplate->getKinetic());
	prototype->setEnergy(creatureTemplate->getEnergy());
	prototype->setBlast(creatureTemplate->getBlast());
	prototype->setHeat(creatureTemplate->getHeat());
	prototype->setCold(creatureTemplate->getCold());
	prototype->setElectric(creatureTemplate->getElectricity());
	prototype->setAcid(creatureTemplate->getAcid());
	prototype->setSaber(creatureTemplate->getLightSaber());
	prototype->setRanged(creatureTemplate->getWeapons().size() > 0);
	prototype->setArmorRating(creatureTemplate->getArmor());

	if (creatureTemplate->isSpecialProtection(WeaponObject::STUN))
		prototype->setSpecialResist(WeaponObject::STUN);
	if (creatureTemplate->isSpecialProtection(WeaponObject::KINETIC))
		prototype->setSpecialResist(WeaponObject::KINETIC);
	if (creatureTemplate->isSpecialProtection(WeaponObject::ENERGY))
		prototype->setSpecialResist(WeaponObject::ENERGY);
	if (creatureTemplate->isSpecialProtection(WeaponObject::BLAST))
		prototype->setSpecialResist(WeaponObject::BLAST);
	if (creatureTemplate->isSpecialProtection(WeaponObject::HEAT))
		prototype->setSpecialResist(WeaponObject::HEAT);
	if (creatureTemplate->isSpecialProtection(WeaponObject::COLD))
		prototype->setSpecialResist(WeaponObject::COLD);
	if (creatureTemplate->isSpecialProtection(WeaponObject::ELECTRICITY))
		prototype->setSpecialResist(WeaponObject::ELECTRICITY);
	if (creatureTemplate->isSpecialProtection(WeaponObject::ACID))
		prototype->setSpecialResist(WeaponObject::ACID);
	if (creatureTemplate->isSpecialProtection(WeaponObject::LIGHTSABER))
		prototype->setSpecialResist(WeaponObject::LIGHTSABER);

	CreatureAttackMap* attackMap = creatureTemplate->getAttacks();
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
	switch(type) {
		case HIT_LEVEL:
			for (int i=0;i<dnaHit.size();i++) {
				float lvminus = 0, lvplus = 3;

				if (i > 0)
					lvminus = dnaHit.get(i - 1);

				if (i < (dnaHit.size() - 1))
					lvplus = dnaHit.get(i + 1);

				float lv = dnaHit.get(i);

				if(value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}
			break;
		case DPS_LEVEL:
			for (int i=0;i<dnaDPS.size();i++) {
				float lvminus = 0, lvplus = 1000;

				if (i > 0)
					lvminus = dnaDPS.get(i - 1);

				if (i < (dnaDPS.size() - 1))
					lvplus = dnaDPS.get(i + 1);

				float lv = dnaDPS.get(i);

				if(value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}
			break;
		case HAM_LEVEL:
			for (int i=0;i<dnaHam.size();i++) {
				float lvminus = 0, lvplus = 500000;

				if (i > 0)
					lvminus = dnaHam.get(i - 1);

				if (i < (dnaHam.size() - 1))
					lvplus = dnaHam.get(i + 1);

				float lv = dnaHam.get(i);

				if(value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}
			break;
		case ARM_LEVEL:
			for (int i=0;i<dnaArmor.size();i++) {
				float lvminus = 0, lvplus = 2000;

				if (i > 0)
					lvminus = dnaArmor.get(i - 1);

				if (i < (dnaArmor.size() - 1))
					lvplus = dnaArmor.get(i + 1);

				float lv = dnaArmor.get(i);

				if(value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}
			break;
		case REG_LEVEL:
			for (int i=0;i<dnaRegen.size();i++) {
				float lvminus = 0, lvplus = 50000;

				if (i > 0)
					lvminus = dnaRegen.get(i - 1);

				if (i < (dnaRegen.size() - 1))
					lvplus = dnaRegen.get(i + 1);

				float lv = dnaRegen.get(i);

				if(value >= (lvminus + lv) / 2.0 && value <= (lvplus + lv) / 2.0) {
					rc = i;
					break;
				}
			}
			break;
		default:
			rc = 0;
	}
	return rc;
}
