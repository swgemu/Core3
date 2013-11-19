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

void DnaManager::generateSample(Creature* creature, CreatureObject* player,int quality){
	if (quality < 0 || quality > 7) {
		return;
	}
	Locker lock(creature,player);
	CreatureTemplate* creatureTemplate = dynamic_cast<CreatureTemplate*>(creature->getCreatureTemplate());

	int ferocity = creatureTemplate->getFerocity();
	int cl = creature->getLevel();
	int cle = instance()->generateScoreFor(DnaManager::CLEVERNESS,cl,quality);
	int cou = instance()->generateScoreFor(DnaManager::COURAGE,cl,quality);
	int dep = instance()->generateScoreFor(DnaManager::DEPENDABILITY,cl,quality);
	int dex = instance()->generateScoreFor(DnaManager::DEXTERITY,cl,quality);
	int end = instance()->generateScoreFor(DnaManager::ENDURANCE,cl,quality);
	int fie = instance()->generateScoreFor(DnaManager::FIERCENESS,ferocity,quality);
	int frt = instance()->generateScoreFor(DnaManager::FORTITUDE,cl,quality);
	int har = instance()->generateScoreFor(DnaManager::HARDINESS,cl,quality);
	int ite = instance()->generateScoreFor(DnaManager::INTELLIGENCE,cl,quality);
	int pow = instance()->generateScoreFor(DnaManager::POWER,cl,quality);
	// We should now have enough to generate a sample
	ManagedReference<DnaComponent*> prototype = player->getZoneServer()->createObject(qualityTemplates.get(quality), 1).castTo<DnaComponent*>();
	if (prototype == NULL) {
		return;
	}
	Locker clocker(prototype);
	prototype->setSource(creature->getObjectName()->getFullPath());
	prototype->setQuality(quality);
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
	CreatureAttackMap* attackMap = creatureTemplate->getAttacks();
	if (attackMap->size() > 0) {
		prototype->setSpecialAttackOne(String(attackMap->getCommand(0)));
		if(attackMap->size() > 1) {
			prototype->setSpecialAttackTwo(String(attackMap->getCommand(1)));
		}
	}

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory->hasFullContainerObjects()) {
		StringIdChatParameter err("survey", "no_inv_space");
		player->sendSystemMessage(err);
		player->setPosture(CreaturePosture::UPRIGHT, true);
		return;
	}

	Locker locker(inventory);
	inventory->transferObject(prototype, -1, true,false);
	inventory->broadcastObject(prototype, true);
}
