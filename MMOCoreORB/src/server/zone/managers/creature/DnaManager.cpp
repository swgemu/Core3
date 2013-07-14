/*
 * DNAManager.cpp
 *
 *  Created on: July 7, 2012
 *      Author: washu
 */

#include "DnaManager.h"
#include "server/conf/ConfigManager.h"

AtomicInteger DnaManager::loadedDnaData;

DnaManager::DnaManager() : Logger("DnaManager") {

	lua = new Lua();
	lua->init();
	lua_register(lua->getLuaState(), "addRange", addRange);

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

int generateXp(int creatureLevel) {
	float x1 = 0.00001896378 * (creatureLevel * 4);
	float x2 = 0.0025801845 * (creatureLevel * 3);
	float x3 = 0.1673150401 * (creatureLevel * 2);
	float x4 = 6.757844921 * creatureLevel;
	float x5 = 46.75746899;
	return (int)ceil(x1-x2+x3+x4+x5);
}
int DnaManager::addRange(lua_State* L) {
	int stat = lua_tointeger(L,-3);
	int level = lua_tointeger(L,-2);
	LuaObject obj(L);
	Reference<DnaSampleRange*> range = new DnaSampleRange(obj);
	// Find the right Range
	switch(stat) {
		case DnaManager::CLEVERNESS: {
			DnaManager::instance()->cleverness.put(level,range);
			break;
		}
		case DnaManager::COURAGE: {
			DnaManager::instance()->courage.put(level,range);
			break;
		}
		case DnaManager::DEPENDABILITY: {
			DnaManager::instance()->dependency.put(level,range);
			break;
		}
		case DnaManager::DEXTERITY: {
			DnaManager::instance()->dexerity.put(level,range);
			break;
		}
		case DnaManager::ENDURANCE: {
			DnaManager::instance()->endurance.put(level,range);
			break;
		}
		case DnaManager::FIERCENESS: {
			DnaManager::instance()->fierceness.put(level,range);
			break;
		}
		case DnaManager::FORTITUDE: {
			DnaManager::instance()->fortitude.put(level,range);
			break;
		}
		case DnaManager::HARDINESS: {
			DnaManager::instance()->hardiness.put(level,range);
			break;
		}
		case DnaManager::INTELLIGENCE: {
			DnaManager::instance()->intelligence.put(level,range);
			break;
		}
		case DnaManager::POWER: {
			DnaManager::instance()->power.put(level,range);
			break;
		}
		default: {
			DnaManager::instance()->info("Unknown stat provided "+stat);
		}
	}
	int count = loadedDnaData.increment();
	if (ConfigManager::instance()->isProgressMonitorActivated())
		printf("\r\tLoading dna range: [%d] / [745]\t", count);

	return 0;
}
