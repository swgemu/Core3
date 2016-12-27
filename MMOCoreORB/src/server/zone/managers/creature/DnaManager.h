/*
 *
 * DNAManager.h
 *
 *  Created on: July 7, 2013
 *      Author: washu
 */

#ifndef DNAMANAGER_H_
#define DNAMANAGER_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/objects/tangible/deed/pet/PetDeed.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class DnaManager : public Singleton<DnaManager>, public Object, public Logger {
protected:
	// how to store this?
	ArrayList<float> dnaHit;
	ArrayList<int> dnaHam;
	ArrayList<int> dnaDPS;
	ArrayList<int> dnaArmor;
	ArrayList<int> dnaRegen;

	HashTable<int,uint32> qualityTemplates;
	Lua* lua;
	static AtomicInteger loadedDnaData;
public:
	DnaManager();
	virtual ~DnaManager();
	void loadSampleData();
	int generateXp(int creatureLevel);
	static int addQualityTemplate(lua_State* L);
	enum {
		FORTITUDE     = 1,
		ENDURANCE     = 2,
		CLEVERNESS    = 3,
		INTELLIGENCE  = 4,
		DEXTERITY     = 5,
		HARDINESS     = 6,
		DEPENDABILITY = 7,
		COURAGE       = 8,
		POWER         = 9,
		FIERCENESS    = 10
	};
	enum {
		HIT_LEVEL = 1,
		HAM_LEVEL = 2,
		DPS_LEVEL = 3,
		ARM_LEVEL = 4,
		REG_LEVEL = 5
	};
	void generateSample(Creature* creature, CreatureObject* player, int quality);
	void generationalSample(PetDeed* deed, CreatureObject* player, int quality);
	int levelForScore(int type, float value);
	float valueForLevel(int type, int level);
protected:
	int reduceByPercent(int source, int percent) {
		float reduceBy = (100.0 - (float)percent) / 100.0;
		uint32 newValue = (int)( ((float)source) * reduceBy );
		if (newValue < 1)
			newValue = 1;
		return newValue;
	}
};

}
}
}
}

using namespace server::zone::managers::creature;

#endif /* DNAMANAGER_H_ */
