#ifndef LOOTTABLEMANAGERIMPLEMENTATION_
#define LOOTTABLEMANAGERIMPLEMENTATION_

#include <vector>

#include "engine/engine.h"

#include "../../ZoneServer.h"
#include "../../ZoneProcessServerImplementation.h"

#include "LootTableManager.h"

#include "LootTableTemplate.h"


class LootTableManagerImplementation : public LootTableManagerServant, public Mutex, public Lua  {
	ZoneProcessServerImplementation* serv;

	Vector<LootTableTemplate*>* lootTableMap;
	Vector<LootTableTemplate*>* selectedLootTableMap;


public:
	LootTableManagerImplementation(ZoneServer* inserver, ZoneProcessServerImplementation* inserv);
	~LootTableManagerImplementation();

	void stop();
	void createLootItem(Creature* creature, int level, Player* player);
	

private:
	void init();

	void buildLootMap();

};

#endif /*LOOTTABLEMANAGERIMPLEMENTATION_*/
