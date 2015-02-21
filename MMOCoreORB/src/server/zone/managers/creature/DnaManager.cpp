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
	lua_register(lua->getLuaState(), "addRange", addRange);
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
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

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
int DnaManager::getLevelForStat(int stat, int value) {
	HashTable<uint32, DnaSampleRange* > ranges;
	switch(stat) {
		case DnaManager::CLEVERNESS:
			ranges = instance()->cleverness;
			break;
		case DnaManager::COURAGE:
			ranges = instance()->courage;
			break;
		case DnaManager::DEPENDABILITY:
			ranges = instance()->dependency;
			break;
		case DnaManager::ENDURANCE:
			ranges = instance()->endurance;
			break;
		case DnaManager::DEXTERITY:
			ranges = instance()->dexerity;
			break;
		case DnaManager::FIERCENESS:
			ranges = instance()->fierceness;
			break;
		case DnaManager::FORTITUDE:
			ranges = instance()->fortitude;
			break;
		case DnaManager::HARDINESS:
			ranges = instance()->hardiness;
			break;
		case DnaManager::INTELLIGENCE:
			ranges = instance()->intelligence;
			break;
		case DnaManager::POWER:
			ranges = instance()->power;
			break;
		default:
			return 1;
	}
	int level = 1;
	// walk the walk ranges and see what level this should be
	for(int i=1;i<80;i++) {
		DnaSampleRange* range = ranges.get(i);
		if (range == NULL)
			return level;
		if (range->inRange(value)) {
			return level;
		}
	}
	return level;
}
int DnaManager::generateScoreFor(int stat, int cl, int quality) {
	int actualCl;
	actualCl = cl;
	if (actualCl > 80) {
		actualCl = 80;
	}
	switch(stat){
		case DnaManager::CLEVERNESS:
			return instance()->cleverness.get(actualCl)->generateValue(quality);
		case DnaManager::COURAGE:
			return instance()->courage.get(actualCl)->generateValue(quality);
		case DnaManager::DEPENDABILITY:
			return instance()->dependency.get(actualCl)->generateValue(quality);
		case DnaManager::DEXTERITY:
			return instance()->dexerity.get(actualCl)->generateValue(quality);
		case DnaManager::ENDURANCE:
			return instance()->endurance.get(actualCl)->generateValue(quality);
		case DnaManager::FIERCENESS:
			if (actualCl > 20) {
				actualCl = 20;
			}
			return instance()->fierceness.get(actualCl)->generateValue(quality);
		case DnaManager::FORTITUDE:
			return instance()->fortitude.get(actualCl)->generateValue(quality);
		case DnaManager::HARDINESS:
			return instance()->hardiness.get(actualCl)->generateValue(quality);
		case DnaManager::INTELLIGENCE:
			return instance()->intelligence.get(actualCl)->generateValue(quality);
		case DnaManager::POWER:
			return instance()->power.get(actualCl)->generateValue(quality);
		default:
			return 0;
	}
}
int DnaManager::addQualityTemplate(lua_State * L) {
	int qual = lua_tointeger(L,-2);
	String ascii = lua_tostring(L,-1);
	uint32 crc = (uint32) ascii.hashCode();
	DnaManager::instance()->qualityTemplates.put(qual,crc);
	return 0;
}
int DnaManager::addRange(lua_State* L) {
	int stat = lua_tointeger(L,-3);
	int level = lua_tointeger(L,-2);
	LuaObject obj(L);
	// Find the right Range
	switch(stat) {
		case DnaManager::CLEVERNESS: {
			DnaManager::instance()->cleverness.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::COURAGE: {
			DnaManager::instance()->courage.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::DEPENDABILITY: {
			DnaManager::instance()->dependency.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::DEXTERITY: {
			DnaManager::instance()->dexerity.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::ENDURANCE: {
			DnaManager::instance()->endurance.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::FIERCENESS: {
			DnaManager::instance()->fierceness.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::FORTITUDE: {
			DnaManager::instance()->fortitude.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::HARDINESS: {
			DnaManager::instance()->hardiness.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::INTELLIGENCE: {
			DnaManager::instance()->intelligence.put(level,new DnaSampleRange(obj));
			break;
		}
		case DnaManager::POWER: {
			DnaManager::instance()->power.put(level,new DnaSampleRange(obj));
			break;
		}
		default: {
			DnaManager::instance()->info("Unknown stat provided "+ String::valueOf(stat));
			break;
		}
	}
	obj.pop();
	int count = loadedDnaData.increment();
	if (ConfigManager::instance()->isProgressMonitorActivated())
		printf("\r\tLoading dna range: [%d] / [745]\t", count);
	return 0;
}
void DnaManager::generationalSample(PetDeed* deed, CreatureObject* player,int quality) {
	// We are making a generational sample rules are a little different.
	// Reduce each stat by lets say 10% as the max to be on par with old docs
	int cl = deed->getLevel();
	int ferocity = 0;
	int factor = (int)System::random(quality) - 7;
	int reductionAmount = (factor + 15 + quality) ;
	int cle = reduceByPercent(deed->getCleverness(),reductionAmount);
	int cou = deed->getCourage();
	int dep = deed->getDependency();
	int dex = reduceByPercent(deed->getDexterity(),reductionAmount);
	int end = deed->getEndurance();
	int fie = reduceByPercent(deed->getFierceness(),reductionAmount);
	int frt = reduceByPercent(deed->getFortitude(),reductionAmount);
	int har = reduceByPercent(deed->getHardiness(),reductionAmount);
	int ite = reduceByPercent(deed->getIntelligence(),reductionAmount);
	int pow = reduceByPercent(deed->getPower(),reductionAmount);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory->hasFullContainerObjects()) {
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
	int cle = Genetics::reverseHit(creature->getChanceHit(),quality);
	int cou = (int)System::random(545-485)+485; // random fixed range
	int dep = (int)System::random(780-500)+500; // random fixed range
	int dex = Genetics::reverseHam(creature->getMaxHAM(3),quality);
	int end = (int)System::random(525-470)+470; // random fixed range
	int baseFerocity = (ferocity * 45) + 95;
	int minFie = baseFerocity-20-quality;
	int maxFie = (baseFerocity+11-quality);
	int fie = (int)(System::random(maxFie-minFie) + minFie);
	int frt = Genetics::reverseResistance(creature->getEffectiveResist(),creature->getArmor());
	int har = Genetics::reverseHam(creature->getMaxHAM(0),quality);
	int ite = Genetics::reverseHam(creature->getMaxHAM(6),quality);
	int pow = Genetics::reverseDamage(creature->getDamageMax(),quality);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory->hasFullContainerObjects()) {
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
