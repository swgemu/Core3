/*
 * CreatureManagerImplementation.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CreatureManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/trainer/TrainerCreature.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

CreatureObject* CreatureManagerImplementation::spawnCreature(uint32 templateCRC, float x, float z, float y, uint64 parentID) {
	ManagedReference<SceneObject*> object = server->createObject(templateCRC, 0);

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

	SceneObject* cellParent = NULL;

	if (parentID != 0) {
		cellParent = server->getObject(parentID);

		if (cellParent != NULL && !cellParent->isCellObject()) {
			error("trying to set a parent that is not a cell to creature");
			cellParent = NULL;
		}
	}

	if (!createCreatureChildrenObjects(creature)) {
		StringBuffer errMsg;
		errMsg << "could not create children objects for creature... 0x" << templateCRC;
		error(errMsg.toString());

		return NULL;
	}

	if (cellParent != NULL) {
		cellParent->addObject(object, -1);
	}

	//addCreatureToMap(creature);

	Locker _locker(creature);

	creature->initializePosition(x, z, y);

	creature->insertToZone(zone);

	return creature;
}

bool CreatureManagerImplementation::createCreatureChildrenObjects(CreatureObject* creature) {
	if (creature->hasSlotDescriptor("default_weapon")) {
		uint32 defaultWeaponCRC = String("object/weapon/creature/creature_default_weapon.iff").hashCode();

		SceneObject* defaultWeapon = server->createObject(defaultWeaponCRC, 0);

		if (defaultWeapon == NULL) {
			error("could not create creature default weapon");

			return false;
		}

		creature->addObject(defaultWeapon, 4);
	}

	return true;
}

void CreatureManagerImplementation::loadDynamicSpawnAreas() {
	info("loading dynamic spawn regions...", true);
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
					parentObject = server->getObject(parentid);
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
	destructedObject->setPosture(CreaturePosture::DEAD, true);

	destructedObject->updateTimeOfDeath();

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(destructedObject);
	despawn->schedule(10000);

	PlayerManager* playerManager = server->getPlayerManager();

	// lets unlock destructor so we dont get into complicated deadlocks

	if (destructedObject != destructor)
		destructor->unlock();

	try {
		playerManager->disseminateExperience(destructedObject, destructedObject->getDamageMap());

		CombatManager::instance()->attemptPeace(destructedObject);

	} catch (...) {

	}

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

		trainerCreature = spawnCreature(String("object/mobile/dressed_merchant_trainer_01.iff").hashCode(), x, z, y, cell);

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
