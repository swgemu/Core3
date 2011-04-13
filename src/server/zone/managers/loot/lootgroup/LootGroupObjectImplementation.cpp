/*
 * LootGroupObjectImplementation.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: Elvaron
 */

#include "LootGroupObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "LootObject.h"
#include "system/util/VectorMap.h"

void LootGroupObjectImplementation::put(uint32 index, LootObject* obj) {
	if (obj != NULL) {
		lootObjects.put(index, obj);
		if (obj->getChance() > maxChance)
			maxChance = obj->getChance();
	}
}

LootObject* LootGroupObjectImplementation::selectLoot() {
	int x = System::random(maxChance)+1;
	int j = 0;
	LootObject* loot = NULL;

	for (int i = 0; i <= lootObjects.size(); i++) {

		j = System::random(lootObjects.size() - 1);
		loot = lootObjects.get(j);

		if (loot == NULL) {
			info("NULL! " + String::valueOf(i) + " Rolled: " + String::valueOf(j), true);
			continue;
		}

		if (loot->getChance() > x)
			break;
	}

	return loot;
}
