/*
 * CreatureManagerImplementation.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "CreatureTemplateManager.h"
#include "DnaManager.h"
#include "SpawnAreaMap.h"
#include "AiMap.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/crafting/labratories/DroidMechanics.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/events/MilkCreatureTask.h"
#include "server/zone/objects/creature/events/TameCreatureTask.h"
#include "server/zone/objects/creature/events/SampleDnaTask.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/objects/region/Region.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/area/SpawnArea.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/managers/creature/DynamicSpawnObserver.h"
#include "server/zone/packets/object/SpatialChat.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/tangible/LairObject.h"

Mutex CreatureManagerImplementation::loadMutex;

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

SceneObject* CreatureManagerImplementation::spawn(unsigned int lairTemplate, int difficultyLevel, int difficulty, float x, float z, float y, float size) {
	LairTemplate* lairTmpl = creatureTemplateManager->getLairTemplate(lairTemplate);

	if (lairTmpl == NULL)
		return NULL;

	if (lairTmpl->getBuildingType() == LairTemplate::LAIR)
		return spawnLair(lairTemplate, difficultyLevel, difficulty, x, z, y, size);
	else if (lairTmpl->getBuildingType() == LairTemplate::THEATER)
		return spawnTheater(lairTemplate, difficulty, x, z, y, size);
	else if (lairTmpl->getBuildingType() == LairTemplate::NONE)
		return spawnDynamicSpawn(lairTemplate, difficulty, x, z, y, size);

	return NULL;
}

SceneObject* CreatureManagerImplementation::spawnLair(unsigned int lairTemplate, int difficultyLevel, int difficulty, float x, float z, float y, float size) {
	LairTemplate* lairTmpl = creatureTemplateManager->getLairTemplate(lairTemplate);

	if (lairTmpl == NULL || lairTmpl->getBuildingType() != LairTemplate::LAIR)
		return NULL;

 	String buildingToSpawn;

 	Vector<String>* mobiles = lairTmpl->getWeightedMobiles();

 	if (mobiles->size() == 0)
 		return NULL;

 	buildingToSpawn = lairTmpl->getBuilding((uint32)difficulty);

 	if (buildingToSpawn.isEmpty()) {
 		error("error spawning " + buildingToSpawn);
 		return NULL;
 	}

 	ManagedReference<LairObject*> building = zoneServer->createObject(buildingToSpawn.hashCode(), 0).castTo<LairObject*>();

 	if (building == NULL) {
 		error("error spawning " + buildingToSpawn);
 		return NULL;
 	}

 	Locker blocker(building);

 	building->setFaction(lairTmpl->getFaction());
 	building->setPvpStatusBitmask(CreatureFlag::ATTACKABLE);
 	building->setOptionsBitmask(0, false);
 	building->setMaxCondition(difficultyLevel * (900 + System::random(200)));
 	building->setConditionDamage(0, false);
 	building->initializePosition(x, z, y);
 	building->setDespawnOnNoPlayersInRange(true);

 	ManagedReference<LairObserver*> lairObserver = new LairObserver();
 	lairObserver->deploy();
 	lairObserver->setLairTemplate(lairTmpl);
 	lairObserver->setDifficulty(difficulty);
 	lairObserver->setObserverType(ObserverType::LAIR);
 	lairObserver->setSize(size);

 	building->registerObserver(ObserverEventType::OBJECTDESTRUCTION, lairObserver);
 	building->registerObserver(ObserverEventType::DAMAGERECEIVED, lairObserver);
 	building->registerObserver(ObserverEventType::AIMESSAGE, lairObserver);
 	building->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, lairObserver);

 	zone->transferObject(building, -1, false);

	lairObserver->checkForNewSpawns(building, NULL, true);

 	return building;
}

SceneObject* CreatureManagerImplementation::spawnTheater(unsigned int lairTemplate, int difficulty, float x, float z, float y, float size) {
	LairTemplate* lairTmpl = creatureTemplateManager->getLairTemplate(lairTemplate);

	if (lairTmpl == NULL || lairTmpl->getBuildingType() != LairTemplate::THEATER)
		return NULL;

 	Vector<String>* mobiles = lairTmpl->getWeightedMobiles();

 	if (mobiles->size() == 0)
 		return NULL;

 	String buildingToSpawn = lairTmpl->getBuilding((uint32)difficulty);

 	if (buildingToSpawn.isEmpty()) {
 		error("error spawning " + buildingToSpawn);
 		return NULL;
 	}

 	ManagedReference<TangibleObject*> building = zoneServer->createObject(buildingToSpawn.hashCode(), 0).castTo<TangibleObject*>();

 	if (building == NULL) {
 		error("error spawning " + buildingToSpawn);
 		return NULL;
 	}

 	Locker blocker(building);

 	building->initializePosition(x, z, y);

 	ManagedReference<DynamicSpawnObserver*> theaterObserver = new DynamicSpawnObserver();
 	theaterObserver->deploy();
 	theaterObserver->setLairTemplate(lairTmpl);
 	theaterObserver->setDifficulty(difficulty);
 	theaterObserver->setObserverType(ObserverType::LAIR);
 	theaterObserver->setSize(size);

 	building->registerObserver(ObserverEventType::CREATUREDESPAWNED, theaterObserver);


 	zone->transferObject(building, -1, false);

 	theaterObserver->spawnInitialMobiles(building);

 	return building;
}

SceneObject* CreatureManagerImplementation::spawnDynamicSpawn(unsigned int lairTemplate, int difficulty, float x, float z, float y, float size) {
	LairTemplate* lairTmpl = creatureTemplateManager->getLairTemplate(lairTemplate);

	if (lairTmpl == NULL || lairTmpl->getBuildingType() != LairTemplate::NONE)
		return NULL;

	Vector<String>* mobiles = lairTmpl->getWeightedMobiles();

	if (mobiles->size() == 0)
		return NULL;

	ManagedReference<ActiveArea*> area = zoneServer->createObject(String("object/active_area.iff").hashCode(), 0).castTo<ActiveArea*>();

	if (area == NULL) {
		error("error creating active area");
		return NULL;
	}

	Locker blocker(area);

	area->initializePosition(x, z, y);
	area->setRadius(64);
	area->setNoSpawnArea(true);
	area->setNoBuildArea(true);

	ManagedReference<DynamicSpawnObserver*> dynamicObserver = new DynamicSpawnObserver();
	dynamicObserver->deploy();
	dynamicObserver->setLairTemplate(lairTmpl);
	dynamicObserver->setDifficulty(difficulty);
	dynamicObserver->setObserverType(ObserverType::LAIR);
	dynamicObserver->setSize(size);

	area->registerObserver(ObserverEventType::CREATUREDESPAWNED, dynamicObserver);

	zone->transferObject(area, -1, false);

	dynamicObserver->spawnInitialMobiles(area);

	return area;
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

CreatureObject* CreatureManagerImplementation::spawnCreatureWithAi(uint32 templateCRC, float x, float z, float y, uint64 parentID, bool persistent) {
	CreatureObject* creature = spawnCreature(templateCRC, 0, x, z, y, parentID, persistent);

	if (creature != NULL && creature->isAiAgent())
		cast<AiAgent*>(creature)->activateLoad("");
	else {
		error("could not spawn template " + String::valueOf(templateCRC) + " with AI.");
		creature = NULL;
	}

	return creature;
}

String CreatureManagerImplementation::getTemplateToSpawn(uint32 templateCRC) {
	String templateToSpawn = "";

	CreatureTemplate* creoTempl = creatureTemplateManager->getTemplate(templateCRC);

	Vector<String> objTemps = creoTempl->getTemplates();

	if (objTemps.size() > 0) {
		uint32 randomTemp = System::random(objTemps.size() - 1);
		templateToSpawn = objTemps.get(randomTemp);
	} else {
		StringBuffer errMsg;
		errMsg << "could not spawn creature... no object templates in script " << creoTempl->getTemplateName();

		//error(errMsg.toString());
	}

	return templateToSpawn;
}

bool CreatureManagerImplementation::checkSpawnAsBaby(float tamingChance, int babiesSpawned, int chance) {
	if (tamingChance > 0) {
		if (babiesSpawned == 0) {
			if (System::random(chance) < (tamingChance * 100.0f)) {
				return true;
			}
		} else if (System::random(chance * babiesSpawned) < (tamingChance * 100.0f)) {
			return true;
		}
	}

	return false;
}

CreatureObject* CreatureManagerImplementation::spawnCreatureAsBaby(uint32 templateCRC, float x, float z, float y, uint64 parentID) {
	CreatureTemplate* creoTempl = creatureTemplateManager->getTemplate(templateCRC);

	if (creoTempl == NULL || creoTempl->getTame() <= 0)
		return NULL;

	CreatureObject* creo = NULL;

	String templateToSpawn = getTemplateToSpawn(templateCRC);
	uint32 objectCRC = templateToSpawn.hashCode();

	creo = createCreature(objectCRC, false, templateCRC);

	if (creo != NULL && creo->isCreature()) {
		Creature* creature = cast<Creature*>(creo);
		creature->loadTemplateDataForBaby(creoTempl);
	} else {
		error("could not spawn template " + templateToSpawn + " as baby.");
		creo = NULL;
	}

	placeCreature(creo, x, z, y, parentID);

	if (creo != NULL && creo->isAiAgent())
		cast<AiAgent*>(creo)->activateLoad("");
	else {
		error("could not spawn template " + templateToSpawn + " as baby with AI.");
		creo = NULL;
	}

	return creo;
}

CreatureObject* CreatureManagerImplementation::spawnCreatureAsEventMob(uint32 templateCRC, float x, float z, float y, uint64 parentID) {
	CreatureTemplate* creoTempl = creatureTemplateManager->getTemplate(templateCRC);

	if (creoTempl == NULL)
		return NULL;

	CreatureObject* creo = NULL;

	String templateToSpawn = getTemplateToSpawn(templateCRC);
	uint32 objectCRC = templateToSpawn.hashCode();

	creo = createCreature(objectCRC, false, templateCRC);

	if (creo != NULL && creo->isAiAgent()) {
		AiAgent* creature = cast<AiAgent*>(creo);
		creature->loadTemplateData(creoTempl);

		UnicodeString eventName;
		eventName = creature->getDisplayedName() + " (event)";
		creature->setCustomObjectName(eventName, false);

	} else if (creo == NULL) {
		error("could not spawn template " + templateToSpawn);
	}

	placeCreature(creo, x, z, y, parentID);

	if (creo != NULL && creo->isAiAgent())
		cast<AiAgent*>(creo)->activateLoad("");

	return creo;
}

CreatureObject* CreatureManagerImplementation::spawnCreature(uint32 templateCRC, uint32 objectCRC, float x, float z, float y, uint64 parentID, bool persistent) {
	CreatureTemplate* creoTempl = creatureTemplateManager->getTemplate(templateCRC);

	if (creoTempl == NULL)
		return spawnCreature(objectCRC, x, z, y, parentID);

	CreatureObject* creature = NULL;

	String templateToSpawn;

	if (objectCRC == 0) {
		templateToSpawn = getTemplateToSpawn(templateCRC);
		objectCRC = templateToSpawn.hashCode();
	}

	creature = createCreature(objectCRC, persistent, templateCRC);

	if (creature != NULL && creature->isAiAgent()) {
		AiAgent* npc = cast<AiAgent*>(creature);
		npc->loadTemplateData(creoTempl);
	} else if (creature == NULL) {
		error("could not spawn template " + templateToSpawn);
	}

	placeCreature(creature, x, z, y, parentID);

	return creature;
}

CreatureObject* CreatureManagerImplementation::createCreature(uint32 templateCRC,  bool persistent, uint32 mobileTemplateCRC) {
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

	if (!createCreatureChildrenObjects(creature, templateCRC, creature->isPersistent(), mobileTemplateCRC)) {
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

	Reference<SceneObject*> cellParent = NULL;

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

bool CreatureManagerImplementation::createCreatureChildrenObjects(CreatureObject* creature, uint32 templateCRC, bool persistent, uint32 mobileTemplateCRC) {
	if (creature->hasSlotDescriptor("default_weapon")) {

		uint32 defaultWeaponCRC = 0;
		if (creature->isNonPlayerCreatureObject()) {
			defaultWeaponCRC = String("object/weapon/melee/unarmed/unarmed_default.iff").hashCode();
		} else {
			defaultWeaponCRC = String("object/weapon/creature/creature_default_weapon.iff").hashCode();
		}
		ManagedReference<SceneObject*> defaultWeapon = zoneServer->createObject(defaultWeaponCRC, persistent);
		ManagedReference<SceneObject*> otherWeapon;

		if(mobileTemplateCRC != 0) {
			CreatureTemplate* creoTempl = creatureTemplateManager->getTemplate(mobileTemplateCRC);

			if(creoTempl != NULL && creoTempl->getDefaultWeapon() != ""){
				uint32 otherWeaponCRC = String(creoTempl->getDefaultWeapon()).hashCode();
				otherWeapon = zoneServer->createObject(otherWeaponCRC, persistent);
			}
		}

		if(otherWeapon != NULL) {
			if (defaultWeapon != NULL && defaultWeapon->isPersistent()) {
				defaultWeapon->destroyObjectFromDatabase(true);
			}

			defaultWeapon = otherWeapon;
		}

		if (defaultWeapon == NULL) {
			error("could not create creature default weapon");
			return false;
		}

		creature->transferObject(defaultWeapon, 4);
	}

	if (creature->hasSlotDescriptor("inventory")) {
		Reference<SceneObject*> creatureInventory = zoneServer->createObject(String("object/tangible/inventory/creature_inventory.iff").hashCode(), persistent);

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

	bool shouldRescheduleCorpseDestruction = false;

	try {
		ManagedReference<CreatureObject*> player = copyThreatMap.getHighestDamageGroupLeader();

		uint64 ownerID = 0;

		if (player != NULL) {

			if(player->isGrouped()) {
				ownerID = player->getGroupID();
			} else {
				ownerID = player->getObjectID();
			}

			if (player->isPlayerCreature()) {
				Locker locker(player, destructedObject);

				player->notifyObservers(ObserverEventType::KILLEDCREATURE, destructedObject);

				FactionManager* factionManager = FactionManager::instance();

				if (!destructedObject->getPvPFaction().isEmpty() && !destructedObject->isEventMob()) {
					int level = destructedObject->getLevel();
					if(!player->isGrouped())
						factionManager->awardFactionStanding(player, destructedObject->getPvPFaction(), level);
					else
						factionManager->awardFactionStanding(copyThreatMap.getHighestDamagePlayer(), destructedObject->getPvPFaction(), level);
				}
			}

		}

		if (playerManager != NULL)
			playerManager->disseminateExperience(destructedObject, &copyThreatMap);

		SceneObject* creatureInventory = destructedObject->getSlottedObject("inventory");

		if (creatureInventory != NULL && player != NULL && player->isPlayerCreature()) {
			LootManager* lootManager = zoneServer->getLootManager();

			if (destructedObject->isNonPlayerCreatureObject() && !destructedObject->isEventMob())
				destructedObject->setCashCredits(lootManager->calculateLootCredits(destructedObject->getLevel()));

			creatureInventory->setContainerOwnerID(ownerID);

			lootManager->createLoot(creatureInventory, destructedObject);
		}

		CombatManager::instance()->attemptPeace(destructedObject);

		// Check to see if we can expedite the despawn of this corpse
		// We can expedite the despawn when corpse has no loot, no credits, player cannot harvest, and no group members in range can harvest
		shouldRescheduleCorpseDestruction = playerManager->shouldRescheduleCorpseDestruction(player, destructedObject);

	} catch (...) {
		destructedObject->scheduleDespawn();

		// now we can safely lock destructor again
		if (destructedObject != destructor)
			destructor->wlock(destructedObject);

		throw;
	}

	destructedObject->scheduleDespawn();

	if (shouldRescheduleCorpseDestruction) {

		Reference<DespawnCreatureTask*> despawn = destructedObject->getPendingTask("despawn").castTo<DespawnCreatureTask*>();

		if (despawn != NULL) {
			despawn->cancel();
			despawn->reschedule(10000);
		}
	}

	// now we can safely lock destructor again
	if (destructedObject != destructor)
		destructor->wlock(destructedObject);

	return 1;
}

void CreatureManagerImplementation::droidHarvest(Creature* creature, CreatureObject* droid, int selectedID, int harvestBonus) {
	// droid and creature are locked coming in.
	ManagedReference<CreatureObject*> owner = droid->getLinkedCreature();
	if (owner == NULL) {
		return;
	}
	Locker pLock(owner);
	Zone* zone = creature->getZone();

	if (zone == NULL || !creature->isCreature()) {
		return;
	}

	// this will perform a range check on the corpse to the droid
	if (!creature->canDroidHarvestMe(owner,droid)) {
		owner->sendSystemMessage("@pet/droid_modules:cannot_access_corpse");
		return;
	}

	ManagedReference<ResourceManager*> resourceManager = zone->getZoneServer()->getResourceManager();
	String restype = "";
	float quantity = 0;

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
		owner->sendSystemMessage("Tried to harvest something this creature didn't have, please report this error");
		return;
	}
	int ownerSkill = owner->getSkillMod("creature_harvesting");
	int quantityExtracted = int(quantity * float(ownerSkill / 100.0f));
	// add in droid bonus
	quantityExtracted = MAX(quantityExtracted, 3);
	ManagedReference<ResourceSpawn*> resourceSpawn = resourceManager->getCurrentSpawn(restype, droid->getZone()->getZoneName());

	if (resourceSpawn == NULL) {
		owner->sendSystemMessage("Error: Server cannot locate a current spawn of " + restype);
		return;
	}

	float density = resourceSpawn->getDensityAt(droid->getZone()->getZoneName(), droid->getPositionX(), droid->getPositionY());

	String creatureHealth = "";

	if (density > 0.80f) {
		quantityExtracted = int(quantityExtracted * 1.25f);
		creatureHealth = "creature_quality_fat";
	} else if (density > 0.60f) {
		quantityExtracted = int(quantityExtracted * 1.00f);
		creatureHealth = "creature_quality_medium";
	} else if (density > 0.40f) {
		quantityExtracted = int(quantityExtracted * 0.75f);
		creatureHealth = "creature_quality_scrawny";
	} else {
		quantityExtracted = int(quantityExtracted * 0.50f);
		creatureHealth = "creature_quality_skinny";
	}

	float modifier = 1;
	int baseAmount = quantityExtracted;
	if (owner->isGrouped()) {
		modifier = owner->getGroup()->getGroupHarvestModifier(owner);

		quantityExtracted = (int)(quantityExtracted * modifier);
		if (owner->getGroup()->getGroupSize() > 2 ) {
			quantityExtracted -= quantityExtracted * 0.3; // 30% reduction
		}
	}

	if (creature->getParent().get() != NULL)
		quantityExtracted = 1;
	int droidBonus = DroidMechanics::determineDroidSkillBonus(ownerSkill,harvestBonus,quantityExtracted);

	quantityExtracted += droidBonus;
	// add to droid inventory if there is space available, otherwise to player
	DroidObject* pet = cast<DroidObject*>(droid);
	if (pet == NULL) {
		error("Incoming droid harvest call didnt include a droid!");
		return;
	}

	if (pet->hasStorage()) {
		bool didit = resourceManager->harvestResourceToPlayer(droid, resourceSpawn, quantityExtracted);
		if (!didit) {
			resourceManager->harvestResourceToPlayer(owner, resourceSpawn, quantityExtracted);
		}
	} else {
		resourceManager->harvestResourceToPlayer(owner, resourceSpawn, quantityExtracted);
	}

	/// Send System Messages
	StringIdChatParameter harvestMessage("skl_use", creatureHealth);

	harvestMessage.setDI(quantityExtracted);
	harvestMessage.setTU(resourceSpawn->getFinalClass());

	owner->sendSystemMessage(harvestMessage);

	/// Send bonus message
	if (modifier == 1.2f)
		owner->sendSystemMessage("@skl_use:group_harvest_bonus");
	else if (modifier == 1.3f)
		owner->sendSystemMessage("@skl_use:group_harvest_bonus_ranger");
	else if (modifier == 1.4f)
		owner->sendSystemMessage("@skl_use:group_harvest_bonus_masterranger");

	/// Send group spam
	if (owner->isGrouped()) {
		StringIdChatParameter bonusMessage("group", "notify_harvest_corpse");

		bonusMessage.setTU(droid->getDisplayedName());
		bonusMessage.setDI(quantityExtracted);
		bonusMessage.setTO(resourceSpawn->getFinalClass());
		bonusMessage.setTT(creature->getObjectNameStringIdFile(), creature->getObjectNameStringIdName());

		ChatSystemMessage* sysMessage = new ChatSystemMessage(bonusMessage);
		owner->getGroup()->broadcastMessage(owner, sysMessage, false);
	}

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	int xp = creature->getLevel() * 5 + 19;

	if(playerManager != NULL)
		playerManager->awardExperience(owner, "scout", xp, true);

	creature->addAlreadyHarvested(owner);

	if (!creature->hasLoot() && creature->getBankCredits() < 1 && creature->getCashCredits() < 1 && !playerManager->canGroupMemberHarvestCorpse(owner, creature)) {
		Reference<DespawnCreatureTask*> despawn = creature->getPendingTask("despawn").castTo<DespawnCreatureTask*>();

		if (despawn != NULL) {
			despawn->cancel();

			despawn->reschedule(1000);
		}
	}


}

void CreatureManagerImplementation::harvest(Creature* creature, CreatureObject* player, int selectedID) {
	Zone* zone = creature->getZone();

	if (zone == NULL || !creature->isCreature())
		return;

	if (!creature->canHarvestMe(player))
		return;
		
	if (!player->isInRange(creature, 7))
		return;

	ManagedReference<ResourceManager*> resourceManager = zone->getZoneServer()->getResourceManager();

	String restype = "";
	float quantity = 0;

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
		creatureHealth = "creature_quality_scrawny";
	} else {
		quantityExtracted = int(quantityExtracted * 0.50f);
		creatureHealth = "creature_quality_skinny";
	}

	float modifier = 1;
	int baseAmount = quantityExtracted;

	if (player->isGrouped()) {
		modifier = player->getGroup()->getGroupHarvestModifier(player);

		quantityExtracted = (int)(quantityExtracted * modifier);
	}

	if (creature->getParent().get() != NULL)
		quantityExtracted = 1;

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

	if (!creature->hasLoot() && creature->getBankCredits() < 1 && creature->getCashCredits() < 1 && !playerManager->canGroupMemberHarvestCorpse(player, creature)) {
		Reference<DespawnCreatureTask*> despawn = creature->getPendingTask("despawn").castTo<DespawnCreatureTask*>();

		if (despawn != NULL) {
			despawn->cancel();

			despawn->reschedule(1000);
		}
	}
}

void CreatureManagerImplementation::tame(Creature* creature, CreatureObject* player, bool force) {
	Zone* zone = creature->getZone();

	if (zone == NULL || !creature->isCreature())
		return;

	if(player->getPendingTask("tame_pet") != NULL) {
		player->sendSystemMessage("You are already taming a pet");
		return;
	}

	if(player->getPendingTask("call_pet") != NULL) {
		player->sendSystemMessage("You cannot tame a pet while another is being called");
		return;
	}

	if (!creature->canTameMe(player) || !creature->isAttackableBy(player)) {
		player->sendSystemMessage("@pet/pet_menu:sys_cant_tame"); // You can't tame that
		return;
	}

	CreatureTemplate* creatureTemplate = creature->getCreatureTemplate();

	if (creatureTemplate == NULL)
		return;

	int templateLevel = creatureTemplate->getLevel();
	int maxLevelofPets = player->getSkillMod("tame_level");

	if (!player->hasSkill("outdoors_creaturehandler_novice") || (templateLevel > maxLevelofPets)) {
		player->sendSystemMessage("@pet/pet_menu:sys_lack_skill"); // You lack the skill to be able to tame that creature.
		return;
	}

	if ((creature->isVicious() && player->getSkillMod("tame_aggro") < 1) || creature->getChanceToTame(player) <= 0) {
		player->sendSystemMessage("@pet/pet_menu:sys_lack_skill"); // You lack the skill to be able to tame that creature.
		return;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad == NULL)
		return;

	if (datapad->getContainerObjectsSize() >= datapad->getContainerVolumeLimit()) {
		player->sendSystemMessage("@faction_recruiter:datapad_full"); // Your datapad is full. You must first free some space.
		return;
	}

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	int numberStored = 0;
	int maxStoredPets = playerManager->getBaseStoredCreaturePets() + player->getSkillMod("stored_pets");

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object != NULL && object->isPetControlDevice()) {
			PetControlDevice* device = cast<PetControlDevice*>( object.get());

			if (device->getPetType() == PetManager::CREATUREPET) {
				if (++numberStored >= maxStoredPets) {
					player->sendSystemMessage("@pet/pet_menu:sys_too_many_stored"); // There are too many pets stored in this container. Release some of them to make room for more.
					return;
				}

			}
		}
	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	int currentlySpawned = 0;
	int spawnedLevel = 0;
	int level = creature->getLevel();
	int maxPets = player->getSkillMod("keep_creature");

	for (int i = 0; i < ghost->getActivePetsSize(); ++i) {
		ManagedReference<AiAgent*> object = ghost->getActivePet(i);

		if (object != NULL) {
			ManagedReference<PetControlDevice*> pcd = object->getControlDevice().get().castTo<PetControlDevice*>();

			if (pcd == NULL || pcd->getPetType() != PetManager::CREATUREPET) {
				continue;
			}

			if (++currentlySpawned >= maxPets) {
				player->sendSystemMessage("@pet/pet_menu:too_many"); // You can't control any more pets. Store one first
				return;
			}

			spawnedLevel += object->getLevel();

			if ((spawnedLevel + level) >= maxLevelofPets) {
				player->sendSystemMessage("Taming this pet would exceed your control level ability.");
				return;
			}
		}
	}

	if (force && !ghost->isPrivileged())
		force = false;

	ChatManager* chatManager = player->getZoneServer()->getChatManager();

	chatManager->broadcastMessage(player, "@hireling/hireling:taming_1"); // Easy.

	Locker clocker(creature);

	int mask = creature->getPvpStatusBitmask();
	creature->setPvpStatusBitmask(0, true);

	if (creature->isAiAgent()) {
		AiAgent* agent = cast<AiAgent*>(creature);
		agent->activateLoad("wait");
	}

	ManagedReference<TameCreatureTask*> task = new TameCreatureTask(creature, player, mask, force);

	player->addPendingTask("tame_pet", task, 8000);
}

void CreatureManagerImplementation::milk(Creature* creature, CreatureObject* player) {
	Zone* zone = creature->getZone();

	if (zone == NULL || !creature->isCreature())
		return;

	if (!creature->canMilkMe(player))
		return;

	if (player->isRidingMount()) {
		player->sendSystemMessage("@skl_use:skl_use"); //You cannot milk while mounted.
		return;
	}

	player->sendSystemMessage("@skl_use:milk_begin"); //You relax the creature and begin to milk it.

	Locker clocker(creature);

	creature->setMilkState(BEINGMILKED);

	ManagedReference<MilkCreatureTask*> task = new MilkCreatureTask(creature, player);

	task->schedule(10000);
}

void CreatureManagerImplementation::sample(Creature* creature, CreatureObject* player) {
	Zone* zone = creature->getZone();

	if (zone == NULL || !creature->isCreature() || creature->isNonPlayerCreatureObject()) {
		return;
	}

	if (!creature->canCollectDna(player)){
		player->sendSystemMessage("@bio_engineer:harvest_dna_cant_harvest");
		return;
	}

	if (player->isRidingMount()) {
		player->sendSystemMessage("You cannot sample DNA while mounted");
		return;
	}

	if(player->getPendingTask("sampledna") != NULL) {
		player->sendSystemMessage("@bio_engineer:harvest_dna_already_harvesting");
		return;
	}
	if (!creature->hasSkillToSampleMe(player)){
		player->sendSystemMessage("@bio_engineer:harvest_dna_skill_too_low");
		return;
	}

	Locker clocker(creature);

	ManagedReference<SampleDnaTask*> task = new SampleDnaTask(creature, player);
	player->addPendingTask("sampledna",task,0);

}

bool CreatureManagerImplementation::addWearableItem(CreatureObject* creature, TangibleObject* clothing) {

	if (!clothing->isWearableObject() && !clothing->isWeaponObject())
		return false;

	ChatManager* chatMan = zoneServer->getChatManager();

	SharedTangibleObjectTemplate* tanoData = dynamic_cast<SharedTangibleObjectTemplate*>(clothing->getObjectTemplate());
	Vector<uint32>* races = tanoData->getPlayerRaces();
	String race = creature->getObjectTemplate()->getFullTemplateString();

	if(clothing->isWearableObject()) {
		if (!races->contains(race.hashCode())) {
			UnicodeString message;

			if(creature->getObjectTemplate()->getFullTemplateString().contains("ithorian"))
				message = "@player_structure:wear_not_ithorian";
			else
				message = "@player_structure:wear_no";

			chatMan->broadcastMessage(creature, message, clothing->getObjectID(), creature->getMoodID(), 0);

			return false;
		}
	}

	ManagedReference<SceneObject*> clothingParent = clothing->getParent();

	if (clothingParent == NULL)
		return false;

	for (int i = 0; i < clothing->getArrangementDescriptorSize(); ++i) {
		Vector<String> descriptors = clothing->getArrangementDescriptor(i);

		for (int j = 0; j < descriptors.size(); ++j) {
			ManagedReference<SceneObject*> slot = creature->getSlottedObject(descriptors.get(j));

			if (slot != NULL) {
				slot->destroyObjectFromWorld(true);
				slot->destroyObjectFromDatabase(true);
			}
		}
	}

	creature->transferObject(clothing, 4, false);
	creature->doAnimation("pose_proudly");
	creature->broadcastObject(clothing, true);

	UnicodeString message;
	if(clothing->isWeaponObject())
		message = "@player_structure:wear_yes_weapon";
	else
		message = "@player_structure:wear_yes";

	chatMan->broadcastMessage(creature, message, clothing->getObjectID(), creature->getMoodID(), 0);

	return true;
}


Vector3 CreatureManagerImplementation::getRandomJediTrainer() {
	return spawnAreaMap.getRandomJediTrainer();
}
