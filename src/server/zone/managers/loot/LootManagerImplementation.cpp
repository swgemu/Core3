/*
 * LootManagerImplementation.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: Elvaron
 */

#include "LootManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/managers/loot/lootgroup/LootGroupObject.h"
#include "server/zone/managers/loot/lootgroup/LootObject.h"
#include "system/util/VectorMap.h"


void LootManagerImplementation::initialize() {
	info("Loading loottables...",true);

	int amountGroups = 0;
	int amountObjects = 0;
	try {
		ResultSet* result;
		StringBuffer query;

		query << "SELECT * FROM loottable;";
		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint32 lootGroup = result->getUnsignedInt(0);
			String name = result->getString(1);
			uint32 templateCRC = result->getUnsignedInt(2);
			int chance = result->getInt(8);
			uint32 lootObjectID = result->getUnsignedInt(15);

			if (lootGroups.contains(lootGroup)) {

				ManagedReference<LootGroupObject*> lootGroupObject = lootGroups.get(lootGroup);

				if (lootGroupObject->contains(lootObjectID)) {

					lootGroupObject->get(lootObjectID)->check(name, templateCRC, chance);

				} else {
					amountObjects++;

					lootGroupObject->put(lootObjectID, new LootObject(lootObjectID, name, templateCRC, lootGroup, chance));
				}
			} else {
				amountGroups++;
				// create new lootGroup
				ManagedReference<LootGroupObject*> lootGroupObject = createLootGroup(lootGroup);
				if (lootGroupObject != NULL) {
					lootGroups.put(lootGroup, lootGroupObject);
				}

				if (lootGroups.contains(lootGroup)) {
					amountObjects++;

					LootGroupObject* lootGroupObject = lootGroups.get(lootGroup);

					LootObject* lootObject = new LootObject(lootObjectID, name, templateCRC, lootGroup, chance);

					lootGroupObject->put(lootObjectID, lootObject);
				}
			}
		}

		delete result;
	}  catch (Exception& e) {
		error(e.getMessage());
	}

	info("Initialized " + String::valueOf(amountGroups) + " Groups and " + String::valueOf(amountObjects) + " Objects",true);
}

LootGroupObject* LootManagerImplementation::createLootGroup(uint32 lootGroup) {
	LootGroupObject* lootGroupObject;

	try {
		ResultSet* result;
		StringBuffer query;

		query << "SELECT * FROM lootgroup_weight WHERE lootgroup=" << lootGroup << ";";
		result = ServerDatabase::instance()->executeQuery(query);


		if (result->next()) {
			uint32 lootGroupID = result->getUnsignedInt(0);
			int weight = result->getInt(1);
			int maxDrop = result->getInt(2);

			lootGroupObject = new LootGroupObject(lootGroupID, weight, maxDrop);

		} else {
			info("Could not create LootGroup " + String::valueOf(lootGroup), true);
		}

		delete result;

	}  catch (Exception& e) {
		error(e.getMessage());
	}

	return lootGroupObject;
}

void LootManagerImplementation::createLoot(PlayerCreature* receiver, SceneObject* container, int level, Vector<uint32>* lootGroup) {
	if (container == NULL || level <= 0 || lootGroup == NULL || receiver == NULL)
		return;

	int itemcount = System::random(level / 20) + 1;

	if (itemcount > 5)
		itemcount = 5;

	int maxDrop = 0;
	//int groupSize = 0; // because size doesn't matter.

	Vector<uint32> groups;
	uint32 group;

	for (int i = 0; i < lootGroup->size(); i++) {
		group = lootGroup->get(i);
		if (!lootGroups.contains(group))
			continue;

		maxDrop += lootGroups.get(group)->getMaxDrop();
		//groupSize += group->getSize();

		for (int j = 0; j < lootGroups.get(group)->getWeight(); j++) {
			groups.add(group);
		}
	}

	if (itemcount > maxDrop)
		itemcount = maxDrop;

	// REMOVE AFTER TESTING!
	if (lootGroup->size() > 20) {
		itemcount = lootGroup->size();
	}
	// ENDREMOVE

	/*if (itemcount > group->size())
		itemcount = group->size();*/

	Vector<LootObject*> lootVector;
	ManagedReference<LootGroupObject*> tgroup;

	for (int i = 0; i < itemcount; i++) {
		if (groups.size() <= 0)
			break;

		int x = System::random(groups.size()-1);

		tgroup = lootGroups.get(groups.get(x));

		if (tgroup == NULL) {
			info("Critical Error in loot selection",true);
			break;
		}

		LootObject* lootObject = lootGroups.get(groups.get(x))->selectLoot();

		if (lootObject == NULL) {
			info("No Loot Object in loot selection", true);
			break;
		}
		groups.removeElementAt(x);

		lootVector.add(lootObject);

	}

	while (lootVector.size()>0) {
		if (!attachLoot(receiver, lootVector.get(0), container))
			break;
		//SceneObject* loot = craftingManager->createLootItem(lootVector.get(0)->getTemplateCRC(), level);
		//loot->sendTo(zone, true);
		//container->addObject(loot, -1, true);
		//add object to container, zone
		lootVector.removeElementAt(0);
	}
}

/*
 * if container is a creature, you'll get it once you loot the corpse
 * if container is an inventory, you'll get it immediately there (forage/medical forage)
*/
void LootManagerImplementation::createLoot(PlayerCreature* receiver, SceneObject* container, int level, uint32 lootGroup, int objectCount) {
	if (!contains(lootGroup) || container == NULL || level <= 0 || receiver == NULL)
		return;

	ManagedReference<LootGroupObject*> group = lootGroups.get(lootGroup);

	int itemcount = System::random(level / 20) + 1;

	if (itemcount > 5)
		itemcount = 5;

	if (itemcount > group->getMaxDrop())
		itemcount = group->getMaxDrop();

	Vector<LootObject*> lootVector;

	for (int i = 0; i < itemcount; i++) {
		lootVector.add(group->selectLoot());
	}

	while (lootVector.size()>0) {
		attachLoot(receiver, lootVector.get(0), container, objectCount);
		//SceneObject* loot = craftingManager->createLootItem(lootVector.get(0)->getTemplateCRC(), level);
		//loot->sendTo(zone, true);
		//container->addObject(loot, -1, true);
		//add object to container, zone
		lootVector.removeElementAt(0);
	}
}

bool LootManagerImplementation::attachLoot(PlayerCreature* receiver, LootObject* loot, SceneObject* container, int objectCount) {
	if (loot == NULL || container == NULL || receiver == NULL)
		return false;

	if (container->hasFullContainerObjects()) {
		info("TargetContainer is full.", true);
		return false;
	}

	SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(loot->getTemplateCRC());
	if (templateData == NULL) {
		info("Unknown Template: " + String::valueOf(loot->getTemplateCRC()), true);
		return true;
	}

	uint32 gameObjectType = templateData->getGameObjectType();

	if (!ObjectManager::instance()->contains(gameObjectType)) {
		info("Unregistered Object Type: " + String::valueOf(gameObjectType), true);
		return true;
	}
	SceneObject* item = zoneServer->createObject(loot->getTemplateCRC(), 2);

	if (objectCount > 0) {
		if (item->isTangibleObject()) {
			TangibleObject* tangibleItem = (TangibleObject*) item;
			tangibleItem->setUseCount(objectCount, true);
		}
	}

	item->sendTo(receiver, true);

	Locker clocker(container);
	container->addObject(item, -1, true);

	return true;
}

void LootManagerImplementation::testLoot(PlayerCreature* receiver, SceneObject* container) {

	Vector<uint32> groups;
	groups.add((uint32) 0);
	groups.add((uint32) 1);
	groups.add((uint32) 3);
	groups.add((uint32) 10);
	groups.add((uint32) 11);
	groups.add((uint32) 15);
	groups.add((uint32) 19);
	groups.add((uint32) 23);
	groups.add((uint32) 24);
	groups.add((uint32) 25);
	groups.add((uint32) 30);
	groups.add((uint32) 33);
	groups.add((uint32) 37);
	groups.add((uint32) 38);
	groups.add((uint32) 39);
	groups.add((uint32) 40);
	groups.add((uint32) 42);
	groups.add((uint32) 44);
	groups.add((uint32) 46);
	groups.add((uint32) 47);
	groups.add((uint32) 49);
	groups.add((uint32) 50);
	groups.add((uint32) 51);
	groups.add((uint32) 52);
	groups.add((uint32) 53);
	groups.add((uint32) 54);
	groups.add((uint32) 55);
	groups.add((uint32) 56);
	groups.add((uint32) 57);
	groups.add((uint32) 58);
	groups.add((uint32) 59);
	groups.add((uint32) 60);
	groups.add((uint32) 61);
	groups.add((uint32) 62);
	groups.add((uint32) 64);
	groups.add((uint32) 65);
	groups.add((uint32) 80);
	groups.add((uint32) 81);
	groups.add((uint32) 87);
	groups.add((uint32) 88);
	groups.add((uint32) 89);
	groups.add((uint32) 90);
	groups.add((uint32) 96);
	groups.add((uint32) 97);
	groups.add((uint32) 98);
	groups.add((uint32) 99);
	groups.add((uint32) 100);
	groups.add((uint32) 101);
	groups.add((uint32) 102);

	int level = 50;

	info("testing " + String::valueOf(groups.size()) + " cases", true);

	createLoot(receiver, container, level, 1, 2);
	info("finished testing", true);
}
