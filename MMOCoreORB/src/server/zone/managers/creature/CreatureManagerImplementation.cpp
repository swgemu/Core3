/*
 * CreatureManagerImplementation.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CreatureManager.h"
#include "CreatureTemplate.h"
#include "CreatureTemplateManager.h"
#include "SpawnAreaMap.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/objects/creature/trainer/TrainerCreature.h"
#include "server/zone/objects/creature/informant/InformantCreature.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/player/PlayerCreature.h"
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

void CreatureManagerImplementation::setCreatureTemplateManager() {
	creatureTemplateManager = CreatureTemplateManager::instance();
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

void CreatureManagerImplementation::spawnRandomCreature(int number, float x, float z, float y, uint64 parentID) {
	Locker locker(_this);

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

	HashTableIterator<uint32, Reference<CreatureTemplate*> > iterator(creatureTemplateManager);

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

CreatureObject* CreatureManagerImplementation::spawnCreature(uint32 templateCRC, uint32 objectCRC, float x, float z, float y, uint64 parentID) {
	CreatureTemplate* creoTempl = creatureTemplateManager->getTemplate(templateCRC);
	if (creoTempl == NULL)
		return spawnCreature(objectCRC, x, z, y, parentID);

	CreatureObject* creature = NULL;

	if (objectCRC == 0) {
		Vector<String> objTemps = creoTempl->getTemplates();

		if (objTemps.size() > 0) {
			uint32 randomTemp = System::random(objTemps.size() - 1);
			objectCRC = objTemps.get(randomTemp).hashCode();
			//info("spawning " + objTemps.get(randomTemp), true);
		} else {
			StringBuffer errMsg;
			errMsg << "could not spawn creature... no object templates in script " << creoTempl->getTemplateName();

			//error(errMsg.toString());
			return NULL;
		}
	}

	creature = createCreature(objectCRC);

	if (creature != NULL && creature->isAiAgent()) {
		AiAgent* npc = (AiAgent*)creature;
		npc->loadTemplateData(creoTempl);
	}

	placeCreature(creature, x, z, y, parentID);

	return creature;
}

CreatureObject* CreatureManagerImplementation::createCreature(uint32 templateCRC) {
	ManagedReference<SceneObject*> object = zoneServer->createObject(templateCRC, 0);

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

	CreatureObject* creature = (CreatureObject*) object.get();

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

	if (cellParent != NULL) {
		cellParent->addObject(creature, -1);
	}

	//addCreatureToMap(creature);

	Locker _locker(creature);

	if (creature->isAiAgent()) {
		AiAgent* aio = (AiAgent*)creature;
		aio->setHomeLocation(x, z, y, cellParent);
	}

	creature->initializePosition(x, z, y);

	creature->insertToZone(zone);
}

bool CreatureManagerImplementation::createCreatureChildrenObjects(CreatureObject* creature) {
	if (creature->hasSlotDescriptor("default_weapon")) {
		uint32 defaultWeaponCRC = String("object/weapon/creature/creature_default_weapon.iff").hashCode();

		SceneObject* defaultWeapon = zoneServer->createObject(defaultWeaponCRC, 0);

		if (defaultWeapon == NULL) {
			error("could not create creature default weapon");

			return false;
		}

		creature->addObject(defaultWeapon, 4);
	}

	return true;
}

void CreatureManagerImplementation::loadSpawnAreas() {
	info("loading spawn areas...", true);
	spawnAreaMap.loadMap(zone);
}

void CreatureManagerImplementation::loadSingleSpawns() {
	info("loading single spawns...", true);

	int planetid = zone->getZoneID();

	ResultSet* result = NULL;
	StringBuffer query;
	query << "SELECT * FROM world_server_static_spawns WHERE zoneid = " << planetid << ";";

	int i = 0;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 parentid = result->getUnsignedLong(2);
			String templateFile = result->getString(3);
			float ox = result->getFloat(4);
			float oy = result->getFloat(5);
			float oz = result->getFloat(6);
			float ow = result->getFloat(7);
			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);
			int level = result->getInt(11);
			String anim = result->getString(12);
			int creatureBitmask = result->getInt(13);
			int combatFlags = result->getInt(14);
			float respawnTimer = result->getFloat(15);

			if (z == 0 && parentid == 0)
				z = zone->getHeight(x, y);

			ManagedReference<CreatureObject*> creature = spawnCreature(templateFile.hashCode(), x, z, y, parentid);

			if (creature == NULL) {
				error("trying to spawn unknown creature " + templateFile);
			} else {
				ManagedReference<SceneObject*> parentObject;

				if (parentid != 0) {
					parentObject = zoneServer->getObject(parentid);
				}

				creature->setDirection(ow, ox, oy, oz);
				creature->setLevel(level);
				creature->setMoodString(anim);
				creature->setPvpStatusBitmask(combatFlags);
				creature->setOptionsBitmask(creatureBitmask);

				if (creature->isAiAgent()) {
					AiAgent* aiAgent = (AiAgent*)creature.get();
					aiAgent->setHomeLocation(x, z, y, parentObject);
					aiAgent->setRespawnTimer(respawnTimer);
					aiAgent->setDespawnOnNoPlayerInRange(false);
				}
			}

			/*int id = result->getInt(0);

			String templateFile = result->getString(3);

			uint32 templateCRC = UnsignedInteger::valueOf(templateFile);
			String fullString;

			try {
				fullString = TemplateManager::instance()->getTemplateFile(templateCRC);
			} catch (...) {
				error("wrong crc " + String::valueOf(templateCRC));
				continue;
			}

			fullString = fullString.replaceAll("shared_", "");

			StringBuffer query;
			query << "UPDATE world_server_static_spawns SET file = '" << fullString << "' WHERE id = " << id;
			ServerDatabase::instance()->executeStatement(query);*/

			++i;

		}

	} catch (Exception& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in CreatureManagerImplementation::loadSingleSpawns()");
	}

	info("static creatures spawned: " + String::valueOf(i), true);

	delete result;
}

int CreatureManagerImplementation::notifyDestruction(TangibleObject* destructor, AiAgent* destructedObject, int condition) {
	if (destructedObject->isDead())
		return 1;

	destructedObject->setPosture(CreaturePosture::DEAD, true);

	destructedObject->updateTimeOfDeath();

	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	// lets unlock destructor so we dont get into complicated deadlocks

	// lets copy the damage map before we remove it all
	DamageMap* damageMap = destructedObject->getDamageMap();
	DamageMap copyDamageMap(*damageMap);
	damageMap->removeAll(); // we can clear the original one

	if (destructedObject != destructor)
		destructor->unlock();

	try {
		ManagedReference<PlayerCreature*> player = copyDamageMap.getHighestDamagePlayer();
		if (player != NULL)
			player->notifyObservers(ObserverEventType::KILLEDCREATURE, destructedObject);

		destructedObject->setLootOwner(player);

		if (playerManager != NULL)
			playerManager->disseminateExperience(destructedObject, &copyDamageMap);

		CombatManager::instance()->attemptPeace(destructedObject);

	} catch (...) {

	}

	destructedObject->scheduleDespawn();

	// now we can safely lock destructor again
	if (destructedObject != destructor)
		destructor->wlock(destructedObject);

	return 1;
}

void CreatureManagerImplementation::loadTrainers() {
	info("loading trainers...", true);

	ProfessionManager* professionManager = ProfessionManager::instance();

	int planetid = zone->getZoneID();

	ResultSet* result;
	StringBuffer query;
	query << "SELECT * FROM trainers WHERE Planet = " << planetid << ";";
	result = ServerDatabase::instance()->executeQuery(query);

	while (result->next()) {
		String location = result->getString(0);
		String customname = result->getString(1);
		String name = result->getString(2);
		String profession = result->getString(3);

		uint64 crc1 = strtoul(result->getString(4), NULL, 16);
		uint64 crc2 = strtoul(result->getString(5), NULL, 16);
		uint64 crc3 = strtoul(result->getString(6), NULL, 16);

		uint64 cell = result->getUnsignedLong(8);
		float worldx = result->getFloat(9);
		float worldy = result->getFloat(10);
		float worldz = result->getFloat(11);
		float cellx = result->getFloat(12);
		float celly = result->getFloat(13);
		float cellz = result->getFloat(14);
		float oY = result->getFloat(15);
		float oW = result->getFloat(16);

		uint8 planetmapid = result->getInt(18);

		float x = worldx;
		float y = worldy;
		float z = worldz;

		if (cell != 0) {
			x = cellx;
			y = celly;
			z = cellz;
		}

		int trainerID = result->getInt(17);

		int rand = System::random(2);

		TrainerCreature* trainer = NULL;
		Profession* professionObject = professionManager->getProfession(profession);


		ManagedReference<CreatureObject*> trainerCreature = NULL;

		//TODO: convert the trainer table crcs to server templates with appropiate game object type see object/mobile/dressed_merchant_trainer_01.lua
		/*if (rand == 0 && crc1 != 0) {
			trainerCreature = spawnCreature(crc1, x, z, y, cell);
		} else if (rand == 1 && crc2 != 0) {
			trainerCreature = spawnCreature(crc2, x, z, y, cell);
		} else {
			trainerCreature = spawnCreature(crc3, x, z, y, cell);
		}*/

		uint64 CRC = 0;
		if (rand == 0 && crc1 != 0)
			CRC = crc1;
		else if (rand == 1 && crc2 != 0)
			CRC = crc2;
		else
			CRC = crc3;

		trainerCreature = spawnCreature(CRC, x, z, y, cell);

		//trainerCreature

		if (trainerCreature->isTrainerCreature()) {
			trainer = (TrainerCreature*) trainerCreature.get();
			StringId nameId("creature_names", name);
			trainer->setObjectName(nameId);

			trainer->setProfession(professionObject);
			trainer->setTrainerID(trainerID);

			trainer->setDirection(oW, 0, oY, 0);

			trainer->setLocation(location);
		}


		/*if (rand == 0 && crc1 != 0)
			trainer = spawnTrainer(profession, name, "", crc1, cell, x, y, z, oY, oW, true, trainerID);
		else if (rand == 1 && crc2 != 0)
			trainer = spawnTrainer(profession, name, "", crc2, cell, x, y, z, oY, oW, true, trainerID);
		else
			trainer = spawnTrainer(profession, name, "", crc3, cell, x, y, z, oY, oW, true, trainerID);

			*/


		//TODO: Replace this once thoop commits his trainer fix.
		//UnicodeString trainername = makeCreatureName(customname);
		trainer->setCustomObjectName(customname, false);

		/*if (planetmapid > 0)
			zone->addMapLocation(trainer->getObjectID(), trainername, worldx, worldy, 19, planetmapid, 0);*/
	}

	delete result;
}

void CreatureManagerImplementation::loadMissionSpawns() {
	info("loading mission spawns...", true);

	int planetid = zone->getZoneID();

	ResultSet* result = NULL;
	StringBuffer query;
	query << "SELECT * FROM mission_manager_npcs WHERE zoneid = " << planetid << ";";

	//int i = 0;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 parentid = result->getUnsignedLong(2);
			String templateFile = result->getString(3);
			float ox = result->getFloat(4);
			float oy = result->getFloat(5);
			float oz = result->getFloat(6);
			float ow = result->getFloat(7);
			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);
			int level = result->getInt(11);
			String anim = result->getString(12);
			int creatureBitmask = result->getInt(13);

			if (z == 0 && parentid == 0)
				z = zone->getHeight(x, y);

			ManagedReference<CreatureObject*> creature = spawnCreature(templateFile.hashCode(), x, z, y, parentid);

			if (creature == NULL) {
				error("trying to spawn unknown creature " + templateFile);
			} else {
				ManagedReference<SceneObject*> parentObject;

				if (parentid != 0) {
					parentObject = zoneServer->getObject(parentid);
				}

				creature->setDirection(ow, ox, oy, oz);
				creature->setLevel(level);
				creature->setMoodString(anim);
				creature->setPvpStatusBitmask(0);
				creature->setOptionsBitmask(creatureBitmask);

				if (creature->isAiAgent()) {
					AiAgent* aiAgent = (AiAgent*)creature.get();
					aiAgent->setHomeLocation(x, z, y, parentObject);
					aiAgent->setRespawnTimer(60);
					aiAgent->setDespawnOnNoPlayerInRange(false);

					NameManager* nm = zoneProcessor->getNameManager();
					if (nm != NULL)
						aiAgent->setCustomObjectName(nm->makeCreatureName(true), false);

					PlanetManager* pmng = zone->getPlanetManager();

					if (pmng != NULL)
						pmng->addMissionNpc(aiAgent);
				}
			}

			//++i;
		}

	} catch (Exception& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in CreatureManagerImplementation::loadMissionSpawns()");
	}

	//info("mission npcs spawned: " + String::valueOf(i), true);

	delete result;
}

void CreatureManagerImplementation::loadInformants() {
	info("loading informants...", true);

	int planetid = zone->getZoneID();

	ResultSet* result;
	StringBuffer query;
	query << "SELECT * FROM mission_manager_informants WHERE planet = " << planetid << ";";

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 cell = result->getUnsignedLong(2);
			float x = result->getFloat(3);
			float y = result->getFloat(4);
			float z = result->getFloat(5);
			float oY = result->getFloat(6);
			float oW = result->getFloat(7);
			int level = result->getInt(8);

			InformantCreature* informant = NULL;
			ManagedReference<CreatureObject*> informantCreature = NULL;

			// is this the only informant CRC?
			informantCreature = spawnCreature(String("object/mobile/dressed_hutt_informant_quest.iff").hashCode(), x, z, y, cell);

			if (informantCreature->isInformantCreature()) {
				informant = (InformantCreature*) informantCreature.get();
				informant->setLevel(level);

				informant->setDirection(oW, 0, oY, 0);
			}

			NameManager* nm = zoneProcessor->getNameManager();
			if (nm != NULL && informant != NULL)
				informant->setCustomObjectName(nm->makeCreatureName(true), false);
		}
	} catch (Exception& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in CreatureManagerImplementation::loadInformants()");
	}

	delete result;
}

void CreatureManagerImplementation::harvest(Creature* creature, PlayerCreature* player, int selectedID) {
	Zone* zone = creature->getZone();

	if (zone == NULL)
		return;

	ManagedReference<ResourceManager*> resourceManager = zone->getZoneServer()->getResourceManager();

	String restype = "";
	int quantity = 0;

	if (selectedID == 112) {
		int type = System::random(2);

		switch (type) {
		case 0:
			restype = creature->getMeatType();
			quantity = creature->getMeatMax();
			break;
		case 1:
			restype = creature->getHideType();
			quantity = creature->getHideMax();
			break;
		case 2:
			restype = creature->getBoneType();
			quantity = creature->getBoneMax();
			break;
		default:
			restype = creature->getHideType();
			quantity = creature->getHideMax();
			break;
		}
	}

	if (selectedID == 234) {
		restype = creature->getMeatType();
		quantity = creature->getMeatMax();
	}

	if (selectedID == 235) {
		restype = creature->getHideType();
		quantity = creature->getHideMax();
	}

	if (selectedID == 236) {
		restype = creature->getBoneType();
		quantity = creature->getBoneMax();
	}

	int quantityExtracted = int(quantity * float(player->getSkillMod("creature_harvesting") / 100.0f));

	ManagedReference<ResourceSpawn*> resourceSpawn = resourceManager->getCurrentSpawn(restype, player->getZone()->getZoneID());

	if (resourceSpawn == NULL) {
		player->sendSystemMessage("Error: Server cannot locate a current spawn of " + restype);
		return;
	}

	float density = resourceSpawn->getDensityAt(player->getZone()->getZoneID(), player->getPositionX(), player->getPositionY());

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
		player->sendSystemMessage("skl_use", "group_harvest_bonus");
	else if (modifier == 1.3f)
		player->sendSystemMessage("skl_use", "group_harvest_bonus_ranger");
	else if (modifier == 1.4f)
		player->sendSystemMessage("skl_use", "group_harvest_bonus_masterranger");

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

	if (!creature->hasLoot()) {
		Reference<DespawnCreatureTask*> despawn = dynamic_cast<DespawnCreatureTask*>(creature->getPendingTask("despawn"));

		if (despawn != NULL) {
			despawn->cancel();

			despawn->reschedule(1000);
		}
	}
}
