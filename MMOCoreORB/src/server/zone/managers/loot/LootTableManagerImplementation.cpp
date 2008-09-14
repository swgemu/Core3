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

#include "engine/engine.h"

#include "../../ZoneServer.h"
#include "../../ZoneProcessServerImplementation.h"

#include "LootTableManager.h"
#include "LootTableManagerImplementation.h"

#include "../../objects/creature/Creature.h"

#include "../item/ItemManagerImplementation.h"

#include "../../packets.h"
#include "../../objects.h"


LootTableManagerImplementation::LootTableManagerImplementation(ZoneServer* inserver,
		ZoneProcessServerImplementation* inserv) : LootTableManagerServant(), Mutex("LootTableManager"), Lua() {

	setLoggingName("LootTableManager");

	init();

	serv = inserv;

	setLogging(false);
	setGlobalLogging(true);

}

LootTableManagerImplementation::~LootTableManagerImplementation() {
	for (int i = 0; i < 500; ++i) {
		for (int j = 0; j < lootTableMap[i]->size(); ++j)
			delete lootTableMap[i]->get(j);

		lootTableMap[i]->removeAll();

		delete lootTableMap[i];
		lootTableMap[i] = NULL;
	}

	if (lootWeightMap != NULL) {
		delete lootWeightMap;
		lootWeightMap = NULL;
	}

	if (lootMaxDrop != NULL) {
		delete lootMaxDrop;
		lootMaxDrop = NULL;
	}

}


void LootTableManagerImplementation::init() {
	for (int i = 0; i < 500; ++i)
		lootTableMap[i] = new Vector<LootTableTemplate*>();

	lootWeightMap = new VectorMap<uint,uint>();
	lootMaxDrop = new Vector<int>();

	info("Initializing Loot Table Manager");
	buildLootMap();

}

void LootTableManagerImplementation::buildLootMap() {
	int i = 0, rememberLootGroup = 0;
	ResultSet* lootRes;
	ResultSet* weightRes;
	LootTableTemplate* lootTableTemp;

	stringstream query;
	try {
		query << "SELECT "
				<< "lootgroup,name,template_crc,template_type,template_name,container,attributes,appearance,level,"
				<< "chance,lastdropstamp,dontdropbefore,`unique`,notrade,`race`,itemMask "
				<< "FROM loottable order by lootgroup asc;";

		lootRes = ServerDatabase::instance()->executeQuery(query);

	} catch (...) {
		cout << "Exception in DB query LootTableManagerImplementation::loadLootItems \n";
	}
	query.str("");



	stringstream query2;
	try {

		query2 << "SELECT lootgroup,weight,max_drop_from_this_group from lootgroup_weight order by lootgroup asc;";
		weightRes = ServerDatabase::instance()->executeQuery(query2);

	} catch (...) {
		cout << "Exception in DB query LootTableManagerImplementation::loadLootWeight_Table \n";
	}
	query2.str("");

	while (weightRes->next()) {
		lootWeightMap->put(weightRes->getInt(0), weightRes->getInt(1));
		lootMaxDrop->add(weightRes->getInt(2));
	}


	while (lootRes->next()) {
		i++;
		lootTableTemp = new LootTableTemplate;

		lootTableTemp->setLootItemGroup(lootRes->getInt(0));
		lootTableTemp->setLootItemName(lootRes->getString(1));
		lootTableTemp->setLootItemTemplateCRC(lootRes->getUnsignedLong(2));
		lootTableTemp->setLootItemTemplateType(lootRes->getUnsignedLong(3));
		lootTableTemp->setLootItemTemplateName(lootRes->getString(4));
		lootTableTemp->setLootItemAttributes(lootRes->getString(6));
		lootTableTemp->setLootItemAppearance(lootRes->getString(7));
		lootTableTemp->setLootItemLevel(lootRes->getInt(8));
		lootTableTemp->setLootItemChance(lootRes->getInt(9));
		lootTableTemp->setLootItemLastDropStamp(lootRes->getString(10));
		lootTableTemp->setLootItemDontDropBefore(lootRes->getString(11));
		lootTableTemp->setLootItemUnique(lootRes->getInt(12));
		lootTableTemp->setLootItemNoTrade(lootRes->getInt(13));
		lootTableTemp->setLootItemRace(lootRes->getString(14));
		lootTableTemp->setLootItemMask(lootRes->getUnsignedInt(15));

		lootTableMap[lootRes->getInt(0)]->add(lootTableTemp);
		//for testing: cout << "Adding item " << lootRes->getString(1) << "to lootMap No." << lootRes->getInt(0) << endl;
	}


	stringstream msg;
	msg << "Loot table built from database with <" << i << "> loot items.";
	info(msg.str());

	//Garbage collection
	delete lootRes;
	delete weightRes;
	query.clear();
	msg.clear();
}


void LootTableManagerImplementation::createLootItem(Creature* creature, int level, Player* player) {
	//lock(); TA: moved selectedLootTableMap into the function
	//to avoid locking the whole manager so the server can create the loot items for more then one creature at once

	if (creature == NULL) {
		//unlock();
		return;
	}

	int i, itemcount;
	i = 0;

	uint32 objectCRC = creature->getObjectCRC();
	LootTableTemplate* lootTableTemp;
	ItemManagerImplementation* im;

	Vector<LootTableTemplate*> selectedLootTableMap;

	int lootGroup = makeLootGroup(creature);
	int maxDrop = lootMaxDrop->get(lootGroup);

	for (int i = 0; i < lootTableMap[lootGroup]->size(); ++i) {
		lootTableTemp = lootTableMap[lootGroup]->get(i);

		if (lootTableTemp->getLootItemLevel() <= level) {
			int compare = lootTableTemp->getLootItemRace().find (player->getSpeciesName());

			if (compare >= 0 || lootTableTemp->getLootItemRace() == "all" )
				selectedLootTableMap.add(lootTableTemp);

		}
	}

	//How many loot items will spawn
	itemcount = System::random(level / 20) + 1;

	//We never drop more then 5 items, no matter what
	if (itemcount > 5 )
		itemcount = 5;

	//make sure itemcount is not > lootMap entrys
	if (itemcount > selectedLootTableMap.size())
		itemcount = selectedLootTableMap.size();

	//Finally, consider the maxDrop value for this lootgroup
	if (itemcount > maxDrop)
		itemcount = maxDrop;

	//For testing: itemcount = 100;

	//Randomized offset for the loot item map to avoid looting the same items all time
	int offset = System::random(selectedLootTableMap.size() - itemcount);


	//Make sure we are not pointing behind the last item
	if (offset + itemcount > selectedLootTableMap.size())
		offset = selectedLootTableMap.size() - itemcount;


	TangibleObject* item[itemcount];

	for (int i = 0; i < itemcount; ++i) {
		lootTableTemp = selectedLootTableMap.get(i+offset);

		int itemType = lootTableTemp->getLootItemTemplateType();
		unicode clearName = (unicode)lootTableTemp->getLootItemName();
		uint64 itemCRC = lootTableTemp->getLootItemTemplateCRC();
		string itemName = lootTableTemp->getLootItemTemplateName();
		string lootAttributes = lootTableTemp->getLootItemAttributes();
		uint16 itemMask = lootTableTemp->getLootItemMask();

		//for testing: cout << "Selected lootitem is " << lootTableTemp->getLootItemName() << endl;

		item[i] = im->createPlayerObjectTemplate(itemType, creature->getNewItemID(), itemCRC,
				clearName, itemName, false, true, lootAttributes, level);

		item[i]->setPlayerUseMask(itemMask);

		creature->addLootItem(item[i]);
	}

	//unlock();

}

int LootTableManagerImplementation::makeLootGroup(Creature* creature) {
	Vector<int> weightHelper;
	Vector<string> parsedStrings;

	string parseHelper;
	int retLG = 0;

	string line = creature->getLootGroup();

	for (int i = 0; i < line.size(); i++) {
		char currentChar = line.at(i);

		if (currentChar != ' ') {
			if (currentChar == ',') {
				parsedStrings.add(parseHelper);
				parseHelper.clear();
			} else {
				parseHelper += currentChar;
			}
		}

	}
	// The last template name has to be added because it was not added during the loop
	parsedStrings.add(parseHelper);


	if (parsedStrings.size() > 0) {

		for (int i = 0; i < parsedStrings.size(); i++) {

			//lootgroup the creature belongs to
			int lootGroup = atoi(parsedStrings.get(i).c_str());

			//determining the weight of this lootgroup
			int weight = lootWeightMap->get(lootGroup);

			//The chance of the weight-value is best reflected by adding the lootgroup multiple times, based on its weight
			for (int j = 0; j < weight ; j++)
				weightHelper.add(lootGroup);
		}

		int rand = System::random(weightHelper.size()-1);
		retLG = weightHelper.get(rand);
	}

	//Garbage collection
	parsedStrings.removeAll();
	weightHelper.removeAll();
	parseHelper.clear();
	line.clear();

	return retLG;
}
