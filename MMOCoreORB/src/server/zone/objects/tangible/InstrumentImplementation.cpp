/*
 * InstrumentImplementation.cpp
 *
 *  Created on: 31/10/2010
 *      Author: victor
 */

#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/tangible/InstrumentObserver.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/Zone.h"

void InstrumentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (instrumentType != OMNIBOX && instrumentType != NALARGON)
		return;

	if (canDropInstrument()) {
		ManagedReference<SceneObject*> parent = getParentRecursively(SceneObjectType::PLAYERCREATURE);

		if (parent != NULL && parent == player->asSceneObject())
			menuResponse->addRadialMenuItem(20, 3, "@ui_radial:item_use");
	} else {
		if (spawnerPlayer != NULL && spawnerPlayer == player) {
			if (!player->isPlayingMusic())
				menuResponse->addRadialMenuItem(20, 3, "@radial_performance:play_instrument");
			else
				menuResponse->addRadialMenuItem(20, 3, "@radial_performance:stop_playing");
		}
	}

	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
}

void InstrumentImplementation::notifyLoadFromDatabase() {
	TangibleObjectImplementation::notifyLoadFromDatabase();

	beingUsed = false;

	Reference<SceneObject* > spawnedObject = this->spawnedObject;

	if (spawnedObject != nullptr) {
		Core::getTaskManager()->executeTask( [spawnedObject] () {
			Locker locker(spawnedObject);

			spawnedObject->destroyObjectFromWorld(false);
		}, "DespawnInstrumentLambda");
	}
}


int InstrumentImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (instrumentType != OMNIBOX && instrumentType != NALARGON)
		return 1;

	if (selectedID != 20)
		return 1;

	if (canDropInstrument()) {
		ManagedReference<SceneObject*> parent = getParentRecursively(SceneObjectType::PLAYERCREATURE);

		if (parent == NULL || parent != player->asSceneObject())
			return 1;

		if (player->isSkillAnimating()) {
			player->sendSystemMessage("@performance:music_fail"); // You are unable to do that at this time.
			return 1;
		}

		SortedVector<ManagedReference<Observer* > > observers = player->getObservers(ObserverEventType::POSITIONCHANGED);

		for (int i = 0; i < observers.size(); ++i) {
			InstrumentObserver* observer = dynamic_cast<InstrumentObserver*>(observers.get(i).get());

			if (observer != NULL) {
				ManagedReference<Instrument*> oldInstrument = observer->getInstrument().get();

				if (oldInstrument != NULL) {
					Locker locker(oldInstrument);
					oldInstrument->destroyObjectFromWorld(true);
					player->dropObserver(ObserverEventType::POSITIONCHANGED, observer);
					player->dropObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, observer);
				}
			}
		}

		ManagedReference<SceneObject*> playerParent = player->getParent().get();

		if (playerParent != NULL) {
			if (!playerParent->isCellObject()) {
				return 1;
			} else {
				CellObject* cell = playerParent.castTo<CellObject*>();

				StructureObject* structureObject = dynamic_cast<StructureObject*>(cell->getParent().get().get());

				if (structureObject == NULL)
					return 1;

				if (!structureObject->isOnAdminList(player))
					spawnNonAdmin(player);
				else {
					spawnInAdminCell(player);
				}
			}
		} else {
			spawnNonAdmin(player);
		}
	} else {
		if (getZone() == NULL)
			return 1;

		if (spawnerPlayer == NULL || spawnerPlayer != player)
			return 1;

		if (player->isPlayingMusic()) {
			player->executeObjectControllerAction(STRING_HASHCODE("stopmusic"), getObjectID(), "");
		} else {

			Reference<Instrument*> instrument = player->getSlottedObject("hold_r").castTo<Instrument*>();

			if (instrument != NULL) {
				player->sendSystemMessage("@performance:music_must_unequip");
				return 1;
			}

			Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

			if (ghost == NULL)
				return 1;

			if (!ghost->hasAbility("startmusic")) {
				player->sendSystemMessage("@performance:music_lack_skill_instrument");
				return 1;
			}

			if (player->getDistanceTo(_this.getReferenceUnsafeStaticCast()) >= 5) {
				player->sendSystemMessage("@elevator_text:too_far");
			} else
				player->executeObjectControllerAction(STRING_HASHCODE("startmusic"), getObjectID(), "");
		}
	}

	return 0;
}

bool InstrumentImplementation::canDropInstrument() {
	ManagedReference<SceneObject*> parent = getParent().get();

	if (isInQuadTree() || (parent != NULL && parent->isCellObject()))
		return false;

	return true;
}

void InstrumentImplementation::spawnNonAdmin(CreatureObject* player) {
	if (spawnedObject == NULL) {
		spawnedObject = ObjectManager::instance()->createObject(serverObjectCRC, 0, "sceneobjects");
	}

	if (spawnedObject->getZone() == NULL) {
		Instrument* instrument = spawnedObject.castTo<Instrument*>();

		if (instrument == NULL)
			return;

		Locker locker(instrument);

		instrument->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
		instrument->setSpawnerPlayer(player);

		ManagedReference<SceneObject*> parent = player->getParent().get();
		Zone* zone = player->getZone();

		if (parent != NULL) {
			parent->transferObject(instrument, -1);
		} else if (zone != NULL) {
			zone->transferObject(instrument, -1, true);
		} else {
			return;
		}

		ManagedReference<InstrumentObserver*> posObserver = new InstrumentObserver(instrument);
		player->registerObserver(ObserverEventType::POSITIONCHANGED, posObserver);
		player->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, posObserver);
	} else {
		spawnedObject->teleport(player->getPositionX(), player->getPositionZ(), player->getPositionY(), player->getParentID());
	}

	spawnerPlayer = player;
}

void InstrumentImplementation::spawnInAdminCell(CreatureObject* player) {
	StringBuffer arguments;
	arguments << player->getParent().get()->getObjectID() << " -1 " << player->getPositionX() << " " << player->getPositionZ() << " " << player->getPositionY();

	UnicodeString uni = arguments.toString();

	player->executeObjectControllerAction(STRING_HASHCODE("transferitemmisc"), _this.getReferenceUnsafeStaticCast()->getObjectID(), uni);

	spawnerPlayer = NULL;

	if (spawnedObject != NULL) {
		Locker locker(spawnedObject);
		spawnedObject->destroyObjectFromWorld(true);
		spawnedObject = NULL;
	}
}
