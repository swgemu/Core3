/*
 * CreatureManagerImplementation.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CreatureManager.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "CreatureTemplateManager.h"
#include "SpawnAreaMap.h"
#include "AiMap.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/objects/region/Region.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/area/StaticSpawnArea.h"
#include "server/zone/objects/area/SpawnArea.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "LairObserver.h"

void CreatureManagerImplementation::setCreatureTemplateManager() {
	creatureTemplateManager = CreatureTemplateManager::instance();
	CreatureState::instance()->loadStateData();
	CreaturePosture::instance()->loadMovementData();
}

CreatureObject* CreatureManagerImplementation::spawnCreature(uint32 templateCRC, float x, float z, float y, uint64 parentID) {
	CreatureObject* creature = createCreature(templateCRC);

	placeCreature(creature, x, z, y, parentID);

	return creature;
}

void CreatureManagerImplementation::spawnRandomCreaturesAround(SceneObject* creature) {
	if (spawnedRandomCreatures > 1000)
		return;

	float newX = creature->getPositionX() + (-80.f + (float)System::random(160));
	float newY = creature->getPositionY() + (-80.f + (float)System::random(160));

	spawnRandomCreature(1, newX, zone->getHeight(newX, newY), newY);
}

TangibleObject* CreatureManagerImplementation::spawnLair(unsigned int lairTemplate, int minDifficulty, int maxDifficulty, float x, float z, float y) {
	LairTemplate* lairTmpl = creatureTemplateManager->getLairTemplate(lairTemplate);

	if (lairTmpl == NULL)
		return NULL;

 	String buildingToSpawn;

 	VectorMap<String, uint32>* mobiles = lairTmpl->getMobiles();

 	if (mobiles->size() == 0)
 		return NULL;

 	int rand = System::random(mobiles->size() - 1);

 	String mobile = mobiles->elementAt(rand).getKey();

 	buildingToSpawn = lairTmpl->getBuilding((uint32)maxDifficulty);

 	if (buildingToSpawn.isEmpty()) {
 		error("error spawning " + buildingToSpawn);
 		return NULL;
 	}

 	ManagedReference<TangibleObject*> building = dynamic_cast<TangibleObject*>(zoneServer->createObject(buildingToSpawn.hashCode(), 0));

 	if (building == NULL) {
 		error("error spawning " + buildingToSpawn);
 		return NULL;
 	}

 	Locker blocker(building);

 	building->setPvpStatusBitmask(CreatureFlag::ATTACKABLE);
 	building->setOptionsBitmask(0, false);
 	building->setMaxCondition(maxDifficulty * 1000);
 	building->setConditionDamage(0, false);
 	building->initializePosition(x, z, y);

 	ManagedReference<LairObserver*> lairObserver = new LairObserver();
 	lairObserver->deploy();
 	lairObserver->setLairTemplate(lairTmpl);
 	lairObserver->setDifficulty(minDifficulty, maxDifficulty);
 	lairObserver->setObserverType(ObserverType::LAIR);

 	building->registerObserver(ObserverEventType::OBJECTDESTRUCTION, lairObserver);
 	building->registerObserver(ObserverEventType::DAMAGERECEIVED, lairObserver);


 	zone->transferObject(building, -1, false);

 	int count = 1 + System::random(4);

 	for (int i = 0; i < count; ++i)
 		lairObserver->checkForNewSpawns(building, true);

 	return building;
}

void CreatureManagerImplementation::spawnRandomCreature(int number, float x, float z, float y, uint64 parentID) {
	Locker locker(_this.get());

	if (reservePool.size() != 0) {
		int id = System::random(reservePool.size() - 1);
		ManagedReference<AiAgent*> aiAgent = reservePool.get(id);
		reservePool.remove(id);

		locker.release();

		placeCreature(aiAgent, x, z, y, parentID);

		//aiAgent->info("respawning from reserve Pool", true);

		++spawnedRandomCreatures;

		return;
	}

	locker.release();

	if (creatureTemplateManager->size() == 0)
		return;

	int max = creatureTemplateManager->size() - 1;

	uint32 randomCreature = System::random(max);
	uint32 randomTemplate = 0;
	Reference<CreatureTemplate*> creoTempl = NULL;

	HashTableIterator<uint32, Reference<CreatureTemplate*> > iterator = creatureTemplateManager->iterator();

	for (int i = 0; i < randomCreature; ++i) {
		iterator.getNextKeyAndValue(randomTemplate, creoTempl);
		//randomTemplate = iterator.getNextKey();
	}

	if (creoTempl == NULL || creoTempl->getLevel() > 100)
		return;

	for (int i = 0; i < number; ++i) {
		if (spawnCreature(randomTemplate, 0, x, z, y, parentID) != NULL)
			++spawnedRandomCreatures;
	}
}

CreatureObject* CreatureManagerImplementation::spawnCreatureWithLevel(unsigned int mobileTemplateCRC, int level, float x, float z, float y, uint64 parentID ) {
	CreatureObject* creature = spawnCreature(mobileTemplateCRC, 0, x, z, y, parentID);

	if (creature != NULL)
		creature->setLevel(level);

	return creature;
}

CreatureObject* CreatureManagerImplementation::spawnCreature(uint32 templateCRC, uint32 objectCRC, float x, float z, float y, uint64 parentID, bool persistent) {
	CreatureTemplate* creoTempl = creatureTemplateManager->getTemplate(templateCRC);
	if (creoTempl == NULL)
		return spawnCreature(objectCRC, x, z, y, parentID);

	CreatureObject* creature = NULL;

	String templateToSpawn;

	if (objectCRC == 0) {
		Vector<String> objTemps = creoTempl->getTemplates();

		if (objTemps.size() > 0) {
			uint32 randomTemp = System::random(objTemps.size() - 1);
			templateToSpawn = objTemps.get(randomTemp);
			objectCRC = templateToSpawn.hashCode();
			//info("spawning " + objTemps.get(randomTemp), true);
		} else {
			StringBuffer errMsg;
			errMsg << "could not spawn creature... no object templates in script " << creoTempl->getTemplateName();

			//error(errMsg.toString());
			return NULL;
		}
	}

	creature = createCreature(objectCRC, persistent);

	if (creature != NULL && creature->isAiAgent()) {
		AiAgent* npc = cast<AiAgent*>(creature);
		npc->loadTemplateData(creoTempl);
	} else if (creature == NULL) {
		error("could not spawn template " + templateToSpawn);
	}

	placeCreature(creature, x, z, y, parentID);

	return creature;
}

CreatureObject* CreatureManagerImplementation::createCreature(uint32 templateCRC, bool persistent) {
	ManagedReference<SceneObject*> object = zoneServer->createObject(templateCRC, persistent);

	if (object == NULL) {
		StringBuffer errMsg;
		errMsg << "could not spawn creature... wrong template? 0x" << hex << templateCRC;

		error(errMsg.toString());

		return NULL;
	}

	if (!object->isCreatureObject()) {
		StringBuffer errMsg;
		errMsg << "server did not create a creature object wrong template? 0x" << hex << templateCRC;

		error(errMsg.toString());

		return NULL;
	}

	CreatureObject* creature = cast<CreatureObject*>( object.get());

	if (!createCreatureChildrenObjects(creature)) {
		StringBuffer errMsg;
		errMsg << "could not create children objects for creature... 0x" << templateCRC;
		error(errMsg.toString());

		return NULL;
	}

	return creature;
}

void CreatureManagerImplementation::placeCreature(CreatureObject* creature, float x, float z, float y, uint64 parentID) {
	if (creature == NULL)
		return;

	SceneObject* cellParent = NULL;

	if (parentID != 0) {
		cellParent = zoneServer->getObject(parentID);

		if (cellParent != NULL && !cellParent->isCellObject()) {
			error("trying to set a parent that is not a cell to creature");
			cellParent = NULL;
		}
	}

	//addCreatureToMap(creature);

	Locker _locker(creature);

	if (creature->isAiAgent()) {
		AiAgent* aio = cast<AiAgent*>(creature);
		aio->setHomeLocation(x, z, y, cellParent);
	}

	creature->initializePosition(x, z, y);

	//creature->insertToZone(zone);

	if (cellParent != NULL) {
		cellParent->transferObject(creature, -1);
	} else
		zone->transferObject(creature, -1, true);
}

SpawnArea* CreatureManagerImplementation::getSpawnArea(const String& areaname) {
	return spawnAreaMap.get(areaname.hashCode());
}

bool CreatureManagerImplementation::createCreatureChildrenObjects(CreatureObject* creature, bool persistent) {
	if (creature->hasSlotDescriptor("default_weapon")) {
		uint32 defaultWeaponCRC = String("object/weapon/creature/creature_default_weapon.iff").hashCode();

		SceneObject* defaultWeapon = zoneServer->createObject(defaultWeaponCRC, persistent);

		if (defaultWeapon == NULL) {
			error("could not create creature default weapon");

			return false;
		}

		creature->transferObject(defaultWeapon, 4);
	}

	if (creature->hasSlotDescriptor("inventory")) {
		//object/tangible/inventory/shared_creature_inventory.iff

		SceneObject* creatureInventory = zoneServer->createObject(String("object/tangible/inventory/creature_inventory.iff").hashCode(), persistent);

		if (creatureInventory == NULL) {
			error("could not create creature inventory");

			return false;
		}

		creatureInventory->setContainerDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
		creatureInventory->setContainerDenyPermission("owner", ContainerPermissions::MOVECONTAINER);
		creatureInventory->setContainerInheritPermissionsFromParent(false);

		creature->transferObject(creatureInventory, 4);
	}

	return true;
}

void CreatureManagerImplementation::loadSpawnAreas() {
	info("loading spawn areas...", true);
	spawnAreaMap.loadMap(zone);
}

void CreatureManagerImplementation::loadAiTemplates() {
	info("loading ai templates...", true);
	aiMap = AiMap::instance();
	aiMap->initialize();
	String msg = String("loaded ") + String::valueOf(aiMap->getSize()) + String(" ai templates.");
	info(msg, true);
}

void CreatureManagerImplementation::loadSingleSpawns() {
	info("Loading single spawns...", true);

	//TODO: Convert to Lua
	//Use zoneName

	//info("Static creatures spawned: " + String::valueOf(i), true);
}

int CreatureManagerImplementation::notifyDestruction(TangibleObject* destructor, AiAgent* destructedObject, int condition) {
	if (destructedObject->isDead())
		return 1;

	destructedObject->setPosture(CreaturePosture::DEAD, true);

	destructedObject->updateTimeOfDeath();

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	// lets unlock destructor so we dont get into complicated deadlocks

	// lets copy the damage map before we remove it all
	ThreatMap* threatMap = destructedObject->getThreatMap();
	ThreatMap copyThreatMap(*threatMap);

	threatMap->removeObservers();
	threatMap->removeAll(); // we can clear the original one

	if (destructedObject != destructor)
		destructor->unlock();

	try {
		ManagedReference<CreatureObject*> player = copyThreatMap.getHighestDamagePlayer();

		if (player != NULL) {
			Locker locker(player, destructedObject);

			player->notifyObservers(ObserverEventType::KILLEDCREATURE, destructedObject);

			FactionManager* factionManager = FactionManager::instance();
			factionManager->awardFactionStanding(player, destructedObject->getFactionString());

			if (destructedObject->getFaction() != 0) {
				if (destructedObject->isImperial())
					factionManager->awardFactionStanding(player, "imperial");
				else
					factionManager->awardFactionStanding(player, "rebel");
			}
		}

		if (playerManager != NULL)
			playerManager->disseminateExperience(destructedObject, &copyThreatMap);

		SceneObject* creatureInventory = destructedObject->getSlottedObject("inventory");

		if (creatureInventory != NULL) {
			LootManager* lootManager = zoneServer->getLootManager();

			if (destructedObject->isNonPlayerCreatureObject())
				destructedObject->setCashCredits(lootManager->calculateLootCredits(destructedObject->getLevel()));

			if (player != NULL)
				creatureInventory->setContainerOwnerID(player->getObjectID());

			lootManager->createLoot(creatureInventory, destructedObject);
		}

		CombatManager::instance()->attemptPeace(destructedObject);

	} catch (...) {
		destructedObject->scheduleDespawn();

		// now we can safely lock destructor again
		if (destructedObject != destructor)
			destructor->wlock(destructedObject);

		throw;
	}

	destructedObject->scheduleDespawn();

	// now we can safely lock destructor again
	if (destructedObject != destructor)
		destructor->wlock(destructedObject);

	return 1;
}

void CreatureManagerImplementation::loadTrainers() {
	info("loading trainers...", true);
	//TODO: Load trainers in same Lua as creatures.
}

void CreatureManagerImplementation::loadMissionSpawns() {
	info("loading mission spawns...", true);

	//TODO: Load in same lua as creatures.
}

void CreatureManagerImplementation::loadInformants() {
	info("loading informants...", true);

	//TODO: Load in same lua as creatures.
}

void CreatureManagerImplementation::harvest(Creature* creature, CreatureObject* player, int selectedID) {
	Zone* zone = creature->getZone();

	if (zone == NULL || !creature->isCreature())
		return;

	ManagedReference<ResourceManager*> resourceManager = zone->getZoneServer()->getResourceManager();

	String restype = "";
	int quantity = 0;

	if (selectedID == 112) {
		int type = System::random(2);

		if (quantity == 0 || type == 0) {
			if(creature->getHideMax() > 0) {
				restype = creature->getHideType();
				quantity = creature->getHideMax();
			}
		}

		if (quantity == 0 || type == 1) {
			if(creature->getMeatMax() > 0) {
				restype = creature->getMeatType();
				quantity = creature->getMeatMax();
			}
		}

		if (quantity == 0 || type == 2) {
			if(creature->getBoneMax() > 0) {
				restype = creature->getBoneType();
				quantity = creature->getBoneMax();
			}
		}
	}

	if (selectedID == 234) {
		restype = creature->getMeatType();
		quantity = creature->getMeatMax();
	} else if (selectedID == 235) {
		restype = creature->getHideType();
		quantity = creature->getHideMax();
	} else if (selectedID == 236) {
		restype = creature->getBoneType();
		quantity = creature->getBoneMax();
	}

	if(quantity == 0 || restype.isEmpty()) {
		player->sendSystemMessage("Tried to harvest something this creature didn't have, please report this error");
		return;
	}

	int quantityExtracted = int(quantity * float(player->getSkillMod("creature_harvesting") / 100.0f));
	quantityExtracted = MAX(quantityExtracted, 3);

	ManagedReference<ResourceSpawn*> resourceSpawn = resourceManager->getCurrentSpawn(restype, player->getZone()->getZoneName());

	if (resourceSpawn == NULL) {
		player->sendSystemMessage("Error: Server cannot locate a current spawn of " + restype);
		return;
	}

	float density = resourceSpawn->getDensityAt(player->getZone()->getZoneName(), player->getPositionX(), player->getPositionY());

	String creatureHealth = "";

	if (density > 0.80f) {
		quantityExtracted = int(quantityExtracted * 1.25f);
		creatureHealth = "creature_quality_fat";
	} else if (density > 0.60f) {
		quantityExtracted = int(quantityExtracted * 1.00f);
		creatureHealth = "creature_quality_medium";
	} else if (density > 0.40f) {
		quantityExtracted = int(quantityExtracted * 0.75f);
		creatureHealth = "creature_quality_skinny";
	} else {
		quantityExtracted = int(quantityExtracted * 0.50f);
		creatureHealth = "creature_quality_scrawny";
	}

	float modifier = 1;
	int baseAmount = quantityExtracted;

	if (player->isGrouped()) {
		modifier = player->getGroup()->getGroupHarvestModifier(player);

		quantityExtracted = (int)(quantityExtracted * modifier);
	}

	resourceManager->harvestResourceToPlayer(player, resourceSpawn, quantityExtracted);

	/// Send System Messages
	StringIdChatParameter harvestMessage("skl_use", creatureHealth);

	harvestMessage.setDI(quantityExtracted);
	harvestMessage.setTU(resourceSpawn->getFinalClass());

	player->sendSystemMessage(harvestMessage);

	/// Send bonus message
	if (modifier == 1.2f)
		player->sendSystemMessage("@skl_use:group_harvest_bonus");
	else if (modifier == 1.3f)
		player->sendSystemMessage("@skl_use:group_harvest_bonus_ranger");
	else if (modifier == 1.4f)
		player->sendSystemMessage("@skl_use:group_harvest_bonus_masterranger");

	/// Send group spam
	if (player->isGrouped()) {
		StringIdChatParameter bonusMessage("group", "notify_harvest_corpse");

		bonusMessage.setTU(player->getFirstName());
		bonusMessage.setDI(quantityExtracted);
		bonusMessage.setTO(resourceSpawn->getFinalClass());
		bonusMessage.setTT(creature->getObjectNameStringIdFile(), creature->getObjectNameStringIdName());

		ChatSystemMessage* sysMessage = new ChatSystemMessage(bonusMessage);
		player->getGroup()->broadcastMessage(player, sysMessage, false);
	}

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	int xp = creature->getLevel() * 5 + 19;

	if(playerManager != NULL)
		playerManager->awardExperience(player, "scout", xp, true);

	creature->addAlreadyHarvested(player);

	if (!player->isGrouped() && !creature->hasLoot()) {
		Reference<DespawnCreatureTask*> despawn = dynamic_cast<DespawnCreatureTask*>(creature->getPendingTask("despawn"));

		if (despawn != NULL) {
			despawn->cancel();

			despawn->reschedule(1000);
		}
	}
}

Vector3 CreatureManagerImplementation::getRandomJediTrainer() {
	return spawnAreaMap.getRandomJediTrainer();
}
