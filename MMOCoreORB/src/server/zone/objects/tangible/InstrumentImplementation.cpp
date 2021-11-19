/*
 * InstrumentImplementation.cpp
 *
 *  Created on: 31/10/2010
 *      Author: victor
 */

#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/tangible/tasks/InstrumentPulseTask.h"

bool InstrumentImplementation::isActiveInstrument(CreatureObject* player) {
	Reference<Instrument*> playableInstrument = player->getPlayableInstrument();

	if (playableInstrument == nullptr)
		return false;

	Reference<Instrument*> heldObject = player->getSlottedObject("hold_r").castTo<Instrument*>();

	if (heldObject != nullptr) {
		Instrument* heldInstrument = heldObject.castTo<Instrument*>();

		if (heldInstrument != nullptr) {
			return heldInstrument->getObjectID() == getObjectID();
		}
	}

	if (isASubChildOf(player) && !isEquipped())
		return false;

	return true;
}

bool InstrumentImplementation::isEquipped() {
	ManagedReference<SceneObject*> parent = getParent().get();
	if (parent != nullptr && parent->isPlayerCreature())
		return true;

	return false;
}

void InstrumentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (isActiveInstrument(player) && player->isPlayingMusic())
		menuResponse->addRadialMenuItem(20, 3, "@radial_performance:stop_playing");
	else if (isASubChildOf(player) && isUnequippable())
		menuResponse->addRadialMenuItem(20, 3, "@ui_radial:item_use");
	else if (isActiveInstrument(player) || isUnequippable())
		menuResponse->addRadialMenuItem(20, 3, "@radial_performance:play_instrument");

	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
}

void InstrumentImplementation::notifyLoadFromDatabase() {
	TangibleObjectImplementation::notifyLoadFromDatabase();

	Reference<SceneObject* > spawnedObject = this->spawnedObject;

	if (spawnedObject != nullptr) {
		Core::getTaskManager()->executeTask( [spawnedObject] () {
			Locker locker(spawnedObject);

			spawnedObject->destroyObjectFromWorld(false);
		}, "DespawnInstrumentLambda");
	}
}


int InstrumentImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20)
		return 1;

	bool isStatic = getObjectID() < 10000000;
	bool isOwnedByPlayer = spawnerPlayer == player;
	bool isInWorld = getParentRecursively(SceneObjectType::PLAYERCREATURE) == nullptr;

	if (player->isPlayingMusic()) {
		player->executeObjectControllerAction(STRING_HASHCODE("stopmusic"), getObjectID(), "");
	} else if (isActiveInstrument(player) && !player->isPlayingMusic()) {
		if (isInWorld && isUnequippable()) {
			if (isOwnedByPlayer) {
				initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
				setDirection(*player->getDirection());
			} else if (isStatic) {
				player->setDirection(*_this.getReferenceUnsafeStaticCast()->getDirection());
				player->teleport(getPositionX(), getPositionZ(), getPositionY(), getParentID());
			}
		}
		player->executeObjectControllerAction(STRING_HASHCODE("startmusic"), getObjectID(), "");
	} else if (isUnequippable() && !isInWorld) {
		if (spawnedObject != nullptr) {
			Locker locker(spawnedObject);
			spawnedObject->destroyObjectFromWorld(true);

			if (instrumentPulse != nullptr)
				instrumentPulse->cancel();
		}

		spawnedObject = ObjectManager::instance()->createObject(serverObjectCRC, 0, "sceneobjects");

		if (spawnedObject == nullptr)
			return 1;

		Instrument* instrument = spawnedObject.castTo<Instrument*>();

		if (instrument == nullptr)
			return 1;

		Locker locker(instrument);

		instrument->setSpawnerPlayer(player);
		instrument->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
		instrument->setDirection(*player->getDirection());

		ManagedReference<SceneObject*> parent = player->getParent().get();
		Zone* zone = player->getZone();

		if (parent != nullptr) {
			parent->transferObject(instrument, -1);
		} else if (zone != nullptr) {
			zone->transferObject(instrument, -1, true);
		} else {
			return 1;
		}

		instrumentPulse = new InstrumentPulseTask(instrument);
		instrumentPulse->schedule(5000);
	} else if (!isInRange(player, 2.0f)) {
		player->sendSystemMessage("You are too far away to use that instrument.");
	} else {
		player->sendSystemMessage("You must unequip your current instrument to use this instrument.");
	}

	return 0;
}

bool InstrumentImplementation::canBeTransferred(SceneObject* newContainer) {
	ManagedReference<CreatureObject*> strongOwner = getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (strongOwner != nullptr)
		setSpawnerPlayer(strongOwner);

	if (spawnedObject != nullptr) {
		Locker locker(spawnedObject);
		spawnedObject->destroyObjectFromWorld(true);

		if (instrumentPulse != nullptr)
			instrumentPulse->cancel();
	}

	return true;
}
