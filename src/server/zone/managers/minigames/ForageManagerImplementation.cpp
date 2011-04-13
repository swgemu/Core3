/*
 * ForageManagerImplementation.cpp
 *
 *  Created on: Feb 20, 2011
 *      Author: Anakis
 */

#include "ForageManager.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/minigames/events/ForagingEvent.h"
#include "server/zone/objects/area/ForageArea.h"
#include "server/zone/objects/area/ForageAreaCollection.h"
#include "server/zone/objects/creature/CreatureAttribute.h"


void ForageManagerImplementation::startForaging(PlayerCreature* player, bool scoutForage) {
	if (player == NULL)
		return;

	Locker playerLocker(player);

	int actionCost = 50;

	//Check if already foraging.
	Reference<Task*> pendingForage = player->getPendingTask("foraging");
	if (pendingForage != NULL) {
		player->sendSystemMessage("@skl_use:sys_forage_already"); //"You are already foraging."
		return;
	}

	//Check if player is inside a structure.
	if (player->getParentID() != 0) {
		player->sendSystemMessage("@skl_use:sys_forage_inside"); //"You can't forage inside a structure."
		return;
	}

    //Check for action and deduct cost.
	if (player->getHAM(CreatureAttribute::ACTION) >= actionCost + 1)
		player->inflictDamage(player, CreatureAttribute::ACTION, actionCost, false, true);

	else {
		player->sendSystemMessage("@skl_use:sys_forage_attrib"); //"You need to rest before you can forage again."
		return;
	}

	//Collect player's current position.
	float playerX = player->getPositionX();
	float playerY = player->getPositionY();
	ManagedReference<ZoneServer*> zoneServer = player->getZoneServer();

	//Queue the foraging task.
	Reference<Task*> foragingEvent = new ForagingEvent(player, zoneServer, scoutForage, playerX, playerY, player->getZone()->getTerrainName());
	player->addPendingTask("foraging", foragingEvent);
	foragingEvent->schedule(8500);

	player->sendSystemMessage("@skl_use:sys_forage_start"); //"You begin to search the area for goods."
	player->doAnimation("forage");

}

void ForageManagerImplementation::finishForaging(PlayerCreature* player, bool scoutForage, float forageX, float forageY, const String& terrainName) {
	if (player == NULL)
		return;

	Locker playerLocker(player);
	Locker forageAreasLocker(_this);

	player->removePendingTask("foraging");

	//Check if player moved.
	float playerX = player->getPositionX();
	float playerY = player->getPositionY();

	if ((abs(playerX - forageX) > 2.0) || (abs(playerY - forageY) > 2.0) || player->getZone()->getTerrainName() != terrainName) {
		player->sendSystemMessage("@skl_use:sys_forage_movefail"); //"You fail to forage because you moved."
		return;
	}

	//Check if player is in combat.
	if (player->isInCombat()) {
		player->sendSystemMessage("@skl_use:sys_forage_combatfail"); //"Combat distracts you from your foraging attempt."
		return;
	}

	//Check if player is allowed to forage in this area.
	Reference<ForageAreaCollection*> forageAreaCollection = forageAreas.get(player->getFirstName());

	if (forageAreaCollection != NULL) { //Player has foraged before.
		if (!forageAreaCollection->checkForageAreas(forageX, forageY, terrainName)) {
			player->sendSystemMessage("@skl_use:sys_forage_empty"); //"There is nothing in this area to forage."
			return;
		}

	} else { //Player has not foraged before.
		forageAreaCollection = new ForageAreaCollection(player, forageX, forageY, terrainName);
		forageAreas.put(player->getFirstName(), forageAreaCollection);
	}

	//Calculate the player's chance to find an item.
	int chance;
	int skillMod;

	if (scoutForage) {
		skillMod = player->getSkillMod("foraging");
		chance = (int)(15 + (skillMod * 0.8));

	} else {
		skillMod = player->getSkillMod("medical_foraging");
		chance = (int)(15 + (skillMod * 0.6));
	}

	//Determine if player finds an item.
	if (chance > 100) //There could possibly be +foraging skill tapes.
		chance = 100;

	if (System::random(100) > chance) {
		player->sendSystemMessage("@skl_use:sys_forage_fail"); //"You failed to find anything worth foraging."

	} else {
		player->sendSystemMessage("@skl_use:sys_forage_success"); //"Your attempt at foraging was a success!
		forageGiveItems(player, scoutForage, forageX, forageY, terrainName);
	}

	return;

}

void ForageManagerImplementation::forageGiveItems(PlayerCreature* player, bool scoutForage, float forageX, float forageY, const String& planet) {
	if (player == NULL)
		return;

	Locker playerLocker(player);

	ManagedReference<LootManager*> lootManager = player->getZoneServer()->getLootManager();
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (lootManager == NULL || inventory == NULL)
		return;

	int level = 1;
	int itemCount = 1;
	int lootGroup;

	//Check if inventory is full.
	if (inventory->hasFullContainerObjects()) {
		player->sendSystemMessage("@skl_use:sys_forage_noroom"); //"Some foraged items were discarded, because your inventory is full."
		return;
	}

	//Determine how many items the player finds.
	if (scoutForage) {
		if (player->hasSkillBox("outdoors_scout_camp_03") && System::random(5) == 1)
			itemCount += 1;
		if (player->hasSkillBox("outdoors_scout_master") && System::random(5) == 1)
			itemCount += 1;
	}

	//Discard items if player's inventory does not have enough space.
	int inventorySpace = inventory->getContainerVolumeLimit() - inventory->getContainerObjectsSize();
	if (itemCount > inventorySpace) {
		itemCount = inventorySpace;
		player->sendSystemMessage("@skl_use:sys_forage_noroom"); //"Some foraged items were discarded, because your inventory is full."
	}

	//Determine what the player finds.
	int dice;
	int charges;

	if (scoutForage) {
		for (int i = 0; i < itemCount; i++) {
			dice = System::random(200);
			charges = 1;

			if (dice >= 0 && dice < 160)
				lootGroup = 4; //Forage food.

			else if (dice > 159 && dice < 200) {
				lootGroup = 8; //Bait.
				charges = System::random(4) + 1;

			} else
				lootGroup = 9; //Rare forage items.

			lootManager->createLoot(player, inventory, level, lootGroup, charges);
		}

	} else { //Medical Forage
		dice = System::random(200);
		charges = 1;

		if (dice >= 0 && dice < 40) //Forage food.
			lootGroup = 4;

		else if (dice > 39 && dice < 110) { //Resources.
			forageGiveResource(player, forageX, forageY, planet);
			return;
		}

		else if (dice > 109 && dice < 170) //Average components.
			lootGroup = 5;

		else if (dice > 169 && dice < 200) //Good components.
			lootGroup = 6;

		else //Exceptional Components
			lootGroup = 9; // 7 when items implemented

		lootManager->createLoot(player, inventory, level, lootGroup, charges);
	}

}

void ForageManagerImplementation::forageGiveResource(PlayerCreature* player, float forageX, float forageY, const String& planet) {
	if (player == NULL)
		return;

	Locker playerLocker(player);

	ManagedReference<ResourceManager*> resourceManager = player->getZoneServer()->getResourceManager();

	if (resourceManager == NULL)
		return;

	//Get a list of the flora on the planet.
	Vector<ManagedReference<ResourceSpawn*> > resources;
	//resourceManager->getResourceListByType(resources, 3, planet);
	if (resources.size() < 1)
		return;

	//Pick a random resource from the list and give it to the player if there is some in the area.
	ManagedReference<ResourceSpawn*> flora;
	float density;
	int key;
	int quantity = 1; //This can be changed after release to make the skill more useful.

	while (resources.size() > 0) {
		key = System::random(resources.size() - 1);
		flora = resources.get(key);
		//density = flora->getDensityAt(planet, forageX, forageY);

		if (!density > 0.0 && resources.size() > 1) { //No concentration of this resource near the player.
			resources.remove(key); //Remove and pick another one.

		} else { //If there is only one left, we give them that one even if density is 0.
			resourceManager->harvestResourceToPlayer(player, flora, quantity);
			break;
		}
	}

	return;

}
