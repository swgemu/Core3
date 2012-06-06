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
#include "server/zone/objects/area/ActiveArea.h"

void ForageManagerImplementation::startForaging(CreatureObject* player, int forageType) {
	if (player == NULL)
		return;

	Locker playerLocker(player);

	int actionCost = 50;
	int mindCostShellfish = 100;
	int actionCostShellfish =  100;

	//Check if already foraging.
	Reference<Task*> pendingForage = player->getPendingTask("foraging");
	if (pendingForage != NULL) {

		if (forageType == ForageManager::SHELLFISH)
			player->sendSystemMessage("@harvesting:busy");
		else
			player->sendSystemMessage("@skl_use:sys_forage_already"); //"You are already foraging."
		return;
	}

	//Check if player is inside a structure.
	if (player->getParentID() != 0) {
		if (forageType == ForageManager::SHELLFISH)
			player->sendSystemMessage("@harvesting:inside");
		else
			player->sendSystemMessage("@skl_use:sys_forage_inside"); //"You can't forage inside a structure."
		return;
	}

	//Check if a player is swimming for shellfish harvesting
	if (forageType == ForageManager::SHELLFISH && player->isSwimming()){
		player->sendSystemMessage("@harvesting:swimming");
		return;
	}

	//Check if player is in water for shellfish harvesting
	if (forageType == ForageManager::SHELLFISH && !player->isInWater()){
		player->sendSystemMessage("@harvesting:in_water");
		return;
	}
    //Check for action and deduct cost.

	if (forageType == ForageManager::SHELLFISH){

		if (player->getHAM(CreatureAttribute::MIND) < mindCostShellfish + 1 || player->getHAM(CreatureAttribute::ACTION) < actionCostShellfish + 1)
			return;
		else {
			player->inflictDamage(player, CreatureAttribute::MIND, mindCostShellfish, false, true);
			player->inflictDamage(player, CreatureAttribute::ACTION, actionCostShellfish, false, true);
		}
	}
	else {

		if (player->getHAM(CreatureAttribute::ACTION) >= actionCost + 1)
			player->inflictDamage(player, CreatureAttribute::ACTION, actionCost, false, true);

		else {
			player->sendSystemMessage("@skl_use:sys_forage_attrib"); //"You need to rest before you can forage again."
			return;
		}
	}


	//Collect player's current position.
	float playerX = player->getPositionX();
	float playerY = player->getPositionY();
	ManagedReference<ZoneServer*> zoneServer = player->getZoneServer();

	//Queue the foraging task.
	Reference<Task*> foragingEvent = new ForagingEvent(player, forageType, playerX, playerY, player->getZone()->getZoneName());
	player->addPendingTask("foraging", foragingEvent, 8500);

	player->sendSystemMessage("@skl_use:sys_forage_start"); //"You begin to search the area for goods."

	player->doAnimation("forage");

}

void ForageManagerImplementation::finishForaging(CreatureObject* player, int forageType, float forageX, float forageY, const String& zoneName) {
	if (player == NULL)
		return;

	Locker playerLocker(player);
	Locker forageAreasLocker(_this.get());

	player->removePendingTask("foraging");

	if (player->getZone() == NULL)
		return;

	//Check if player moved.
	if (forageType != ForageManager::SHELLFISH) {
		float playerX = player->getPositionX();
		float playerY = player->getPositionY();

		if ((abs(playerX - forageX) > 2.0) || (abs(playerY - forageY) > 2.0) || player->getZone()->getZoneName() != zoneName) {
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
			if (!forageAreaCollection->checkForageAreas(forageX, forageY, zoneName)) {
				player->sendSystemMessage("@skl_use:sys_forage_empty"); //"There is nothing in this area to forage."
				return;
			}

		} else { //Player has not foraged before.
			forageAreaCollection = new ForageAreaCollection(player, forageX, forageY, zoneName);
			forageAreas.put(player->getFirstName(), forageAreaCollection);
		}
	}
	//Calculate the player's chance to find an item.
	int chance;
	int skillMod;

	switch(forageType) {
	case ForageManager::SCOUT:
	case ForageManager::LAIR:
		skillMod = player->getSkillMod("foraging");
		chance = (int)(15 + (skillMod * 0.8));
		break;
	case ForageManager::MEDICAL:
		skillMod = player->getSkillMod("medical_foraging");
		chance = (int)(15 + (skillMod * 0.6));
		break;
	default:
		skillMod = 20;
		chance = (int)(15 + (skillMod * 0.6));
		break;
	}

	//Determine if player finds an item.
	if (chance > 100) //There could possibly be +foraging skill tapes.
		chance = 100;

	if (System::random(80) > chance) {
		if (forageType == ForageManager::SHELLFISH)
			player->sendSystemMessage("@harvesting:found_nothing");
		else if (forageType == ForageManager::LAIR)
			player->sendSystemMessage("@lair_n:found_nothing");
		else
			player->sendSystemMessage("@skl_use:sys_forage_fail"); //"You failed to find anything worth foraging."

	} else {

		forageGiveItems(player, forageType, forageX, forageY, zoneName);

	}

	return;

}

bool ForageManagerImplementation::forageGiveItems(CreatureObject* player, int forageType, float forageX, float forageY, const String& planet) {
	if (player == NULL)
		return false;

	Locker playerLocker(player);

	ManagedReference<LootManager*> lootManager = player->getZoneServer()->getLootManager();
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (lootManager == NULL || inventory == NULL) {
		player->sendSystemMessage("@skl_use:sys_forage_fail");
		return false;
	}

	//Check if inventory is full.
	if (inventory->hasFullContainerObjects()) {
		player->sendSystemMessage("@skl_use:sys_forage_noroom"); //"Some foraged items were discarded, because your inventory is full."
		return false;
	}

	int itemCount = 1;
	//Determine how many items the player finds.
	if (forageType == ForageManager::SCOUT) {
		if (player->hasSkill("outdoors_scout_camp_03") && System::random(5) == 1)
			itemCount += 1;
		if (player->hasSkill("outdoors_scout_master") && System::random(5) == 1)
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
	int level = 1;
	String lootGroup = "";
	String resName = "";

	if (forageType == ForageManager::SHELLFISH){
		bool mullosks = false;
		if (System::random(100) > 50) {
			resName = "seafood_mollusk";
			mullosks = true;
		}
		else
			resName = "seafood_crustacean";

		if(forageGiveResource(player, forageX, forageY, planet, resName)) {
			if (mullosks)
				player->sendSystemMessage("@harvesting:found_mollusks");
			else
				player->sendSystemMessage("@harvesting:found_crustaceans");
			return true;
		}
		else {
			player->sendSystemMessage("@harvesting:found_nothing");
			return false;
		}

	}


	if (forageType == ForageManager::SCOUT) {

		for (int i = 0; i < itemCount; i++) {
			dice = System::random(200);
			level = 1;

			if (dice >= 0 && dice < 160) {
				lootGroup = "forage_food";
			} else if (dice > 159 && dice < 200) {
				lootGroup = "forage_bait";
			} else {
				lootGroup = "forage_rare";
			}

			lootManager->createLoot(inventory, lootGroup, level);
		}

	} else if (forageType == ForageManager::MEDICAL) { //Medical Forage
		dice = System::random(200);
		level = 1;

		if (dice >= 0 && dice < 40) { //Forage food.
			lootGroup = "forage_food";

		} else if (dice > 39 && dice < 110) { //Resources.
			if(forageGiveResource(player, forageX, forageY, planet, resName)) {
				player->sendSystemMessage("@skl_use:sys_forage_success");
				return true;
			} else {
				player->sendSystemMessage("@skl_use:sys_forage_fail");
				return false;
			}
		} else if (dice > 109 && dice < 170) { //Average components.
			lootGroup = "forage_medical_component";
			level = 1;
		} else if (dice > 169 && dice < 200) { //Good components.
			lootGroup = "forage_medical_component";
			level = 60;
		} else { //Exceptional Components
			lootGroup = "forage_medical_component";
			level = 200;
		}

		lootManager->createLoot(inventory, lootGroup, level);

	} else if (forageType == ForageManager::LAIR) { //Lair Search
		dice = System::random(200);
		level = 1;

		if (dice >= 0 && dice < 40) { // Live Creatures
			lootGroup = "forage_live_creatures";
		}

		else if (dice > 39 && dice < 110) { // Eggs
			resName = "meat_egg";
			if(forageGiveResource(player, forageX, forageY, planet, resName)) {
				player->sendSystemMessage("@lair_n:found_eggs");
				return true;
			} else {
				player->sendSystemMessage("@lair_n:found_nothing");
				return false;
			}
		}

		else  {//if (dice > 109 && dice < 200) // Horn
			resName = "bone_horn";
			if(forageGiveResource(player, forageX, forageY, planet, resName)) {
				player->sendSystemMessage("@skl_use:sys_forage_success");
				return true;
			} else {
				player->sendSystemMessage("@skl_use:sys_forage_fail");
				return false;
			}
		}

		if(!lootManager->createLoot(inventory, lootGroup, level)) {
			player->sendSystemMessage("Unable to create loot for lootgroup " + lootGroup);
			return false;
		}

		player->sendSystemMessage("@lair_n:found_bugs");
		return true;
	}

	player->sendSystemMessage("@skl_use:sys_forage_success");
	return true;
}

bool ForageManagerImplementation::forageGiveResource(CreatureObject* player, float forageX, float forageY, const String& planet, String& resType) {
	if (player == NULL)
		return false;

	ManagedReference<ResourceManager*> resourceManager = player->getZoneServer()->getResourceManager();

	if (resourceManager == NULL)
		return false;

	ManagedReference<ResourceSpawn*> resource = NULL;

	if(resType.isEmpty()) {
		//Get a list of the flora on the planet.
		Vector<ManagedReference<ResourceSpawn*> > resources;
		resourceManager->getResourceListByType(resources, 3, planet);
		if (resources.size() < 1)
			return false;

		while (resources.size() > 0) {
			int key = System::random(resources.size() - 1);
			float density = resources.get(key)->getDensityAt(planet, forageX, forageY);

			if (density <= 0.0 && resources.size() > 1) { //No concentration of this resource near the player.
				resources.remove(key); //Remove and pick another one.

			} else { //If there is only one left, we give them that one even if density is 0.
				resource = resources.get(key);
				break;
			}
		}
	} else {
		if(player->getZone() == NULL)
			return false;

		resType = resType + "_" + player->getZone()->getZoneName();
		resource = resourceManager->getCurrentSpawn(resType, player->getZone()->getZoneName());

		if(resource == NULL) {
			StringBuffer message;
			message << "Resource type not available: " << resType << " on " << player->getZone()->getZoneName();
			warning(message.toString());
			return false;
		}
	}

	int quantity = System::random(30) + 10;
	resourceManager->harvestResourceToPlayer(player, resource, quantity);
	return true;
}
