/*
 * InstrumentImplementation.cpp
 *
 *  Created on: 31/10/2010
 *      Author: victor
 */

#include "Instrument.h"
#include "InstrumentObserver.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/structure/StructureObject.h"

int InstrumentImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (instrumentType != OMNIBOX && instrumentType != NALARGON) {
		return 1;
	}

	if (selectedID == 69) {
		if (isInQuadTree())
			return 1;

		SceneObject* playerParent = player->getParent();

		if (playerParent != NULL) {
			if (!playerParent->isCellObject()) {
				return 1;
			} else {
				CellObject* cell = (CellObject*) playerParent;

				StructureObject* structureObject = dynamic_cast<StructureObject*>(cell->getParent());

				if (structureObject == NULL)
					return 1;

				if (!structureObject->isOnAdminList(player))
					spawnInForeignCell(player);
				else {
					spawnInAdminCell(player);
				}
			}
		} else {
			spawnOutside(player);
		}

	} else if (selectedID == 20) {
		if (!isInQuadTree())
			return 1;

		ManagedReference<Instrument*> instrument = dynamic_cast<Instrument*>(player->getSlottedObject("hold_r"));

		if (instrument != NULL) {
			player->sendSystemMessage("performance", "music_must_unequip");
			return 1;
		}

		PlayerObject* ghost = dynamic_cast<PlayerObject*>(player->getSlottedObject("ghost"));

		if (ghost == NULL)
			return 1;

		if (!ghost->hasSkill("startmusic")) {
			player->sendSystemMessage("performance", "music_lack_skill_instrument");
			return 1;
		}

		if (player->getDistanceTo(_this) >= 5)
			player->sendSystemMessage("elevator_text", "too_far");
		else
			player->executeObjectControllerAction(String("startmusic").hashCode(), getObjectID(), "");
	}

	return 0;
}

void InstrumentImplementation::spawnInForeignCell(PlayerCreature* player) {
	if (spawnedObject == NULL) {
		spawnedObject = ObjectManager::instance()->createObject(serverObjectCRC, 0, "sceneobjects");
		spawnedObject->setParent(NULL);
		spawnedObject->setZone(NULL);
	}

	if (spawnedObject->getZone() == NULL) {
		Instrument* instrument = (Instrument*) spawnedObject.get();
		player->getParent()->addObject(instrument, -1);
		instrument->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
		instrument->setSpawnerPlayer(player);
		instrument->insertToZone(player->getZone());

		ManagedReference<InstrumentObserver*> posObserver = new InstrumentObserver(instrument);
		player->registerObserver(ObserverEventType::POSITIONCHANGED, posObserver);
		player->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, posObserver);
	} else {
		spawnedObject->teleport(player->getPositionX(), player->getPositionZ(), player->getPositionY(), player->getParentID());
	}

	spawnerPlayer = player;
}

void InstrumentImplementation::spawnOutside(PlayerCreature* player) {
	if (spawnedObject == NULL) {
		spawnedObject = ObjectManager::instance()->createObject(serverObjectCRC, 0, "sceneobjects");
		spawnedObject->setParent(NULL);
		spawnedObject->setZone(NULL);
	}

	if (spawnedObject->getZone() == NULL) {
		Instrument* instrument = (Instrument*) spawnedObject.get();
		instrument->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
		instrument->setSpawnerPlayer(player);
		instrument->insertToZone(player->getZone());

		ManagedReference<InstrumentObserver*> posObserver = new InstrumentObserver(instrument);
		player->registerObserver(ObserverEventType::POSITIONCHANGED, posObserver);
		player->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, posObserver);
	} else {
		spawnedObject->teleport(player->getPositionX(), player->getPositionZ(), player->getPositionY(), player->getParentID());
	}

	spawnerPlayer = player;
}

void InstrumentImplementation::spawnInAdminCell(PlayerCreature* player) {
	StringBuffer arguments;
	arguments << player->getParent()->getObjectID() << " -1 " << player->getPositionX() << " " << player->getPositionZ() << " " << player->getPositionY();

	UnicodeString uni = arguments.toString();

	player->executeObjectControllerAction(String("transferitemmisc").hashCode(), _this->getObjectID(), uni);

	spawnerPlayer = NULL;

	if (spawnedObject != NULL) {
		spawnedObject->removeFromZone();
		spawnedObject = NULL;
	}
}
