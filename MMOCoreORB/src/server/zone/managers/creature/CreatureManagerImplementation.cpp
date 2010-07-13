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
	info("loading random spawn regions...", true);
}

int CreatureManagerImplementation::notifyDestruction(TangibleObject* destructor, NonPlayerCreatureObject* destructedObject, int condition) {
	destructedObject->setPosture(CreaturePosture::DEAD, true);

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(destructedObject);
	despawn->schedule(10000);

	disseminateExperience(destructor, destructedObject);

	CombatManager::instance()->attemptPeace(destructedObject);

	return 1;
}

void CreatureManagerImplementation::disseminateExperience(TangibleObject* destructor, NonPlayerCreatureObject* creature) {
	DamageMap* damageMap = creature->getDamageMap();

	uint32 totalDamage = damageMap->getTotalDamage();

	PlayerManager* playerManager = server->getPlayerManager();

	int level = creature->getLevel();

	//info("level: " + String::valueOf(level), true);

	for (int i = 0; i < damageMap->size(); ++i) {
		ManagedReference<PlayerCreature*> player = damageMap->elementAt(i).getKey();

		DamageMapEntry* entry = &damageMap->elementAt(i).getValue();

		Locker crossLocker(player, destructor);

		uint32 totalPlayerDamage = 0;
		uint32 playerWeaponXp = 0;

		for (int j = 0; j < entry->size(); ++j) {
			ManagedReference<WeaponObject*> weapon = entry->elementAt(j).getKey();

			uint32 damage = entry->elementAt(j).getValue();

			totalPlayerDamage += damage;

			String xpType = weapon->getXpType();

			int xpAmmount = (int) (float((float(damage) / float(totalDamage))) * 40.f * level);

			//info("xpAmmount: " + String::valueOf(xpAmmount), true);

			playerWeaponXp += xpAmmount;

			playerManager->awardExperience(player, xpType, xpAmmount);
		}

		playerManager->awardExperience(player, "combat_general", playerWeaponXp / 10);
	}

	damageMap->removeAll();
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
