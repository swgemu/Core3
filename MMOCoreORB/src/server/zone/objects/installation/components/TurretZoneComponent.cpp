/*
 * TurretZoneComponent.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: root
 */

#include "TurretZoneComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/installation/TurretObject.h"
#include "TurretDataComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/installation/components/TurretObserver.h"
#include "MinefieldAttackTask.h"
#include "templates/faction/Factions.h"

void TurretZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) const {
	if (zone == nullptr)
		return;

	ManagedReference<TurretObject*> turret = cast<TurretObject*>(sceneObject);

	if (turret == nullptr) {
		return;
	}

	SortedVector<ManagedReference<Observer*> > destructionObservers = turret->getObservers(ObserverEventType::OBJECTDESTRUCTION);

	for (int i = 0; i < destructionObservers.size(); i++) {
		TurretObserver* turretObserver = destructionObservers.get(i).castTo<TurretObserver*>();

		if (turretObserver != nullptr) {
			return;
		}
	}

	ManagedReference<TurretObserver*> observer = new TurretObserver();

	turret->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
}

void TurretZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) const {
	if (sceneObject == nullptr || !sceneObject->isTurret()) {
		return;
	}

	ManagedReference<TurretObject*> turret = cast<TurretObject*>(sceneObject);

	if (turret == nullptr) {
		return;
	}

	Reference<WeaponObject*> turretWeapon = turret->getTurretWeapon();

	if (turretWeapon != nullptr) {
		Locker clock(turretWeapon, turret);

		turretWeapon->destroyObjectFromWorld(true);
		turretWeapon->destroyObjectFromDatabase(true);
	}

	turret->setTurretWeapon(nullptr);
}

void TurretZoneComponent::notifyInsert(SceneObject* sceneObject, TreeEntry* entry) const {
	if (sceneObject == nullptr || !sceneObject->isTurret() || entry == nullptr) {
		return;
	}

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(sceneObject);

	if (turret == nullptr) {
		return;
	}

	auto dataComponent = sceneObject->getDataObjectComponent()->get();

	if (dataComponent == nullptr) {
		return;
	}

	auto turretData = cast<TurretDataComponent*>(dataComponent);

	if (turretData == nullptr) {
		return;
	}

	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if (target == nullptr || !target->isPlayerCreature()) {
		return;
	}

	auto player = target->asCreatureObject();

	if (player == nullptr || player->isInvisible()) {
		return;
	}

	int newValue = (int)turretData->incrementNumberOfPlayersInRange();

	if (newValue == 1) {
		Reference<TangibleObject*> turretRef = turret;
		Reference<TurretDataComponent*> turretDataRef = turretData;

		Core::getTaskManager()->executeTask([turretRef, turretDataRef] () {
			if (turretRef == nullptr || turretDataRef == nullptr) {
				return;
			}

			Locker locker(turretRef);

			turretDataRef->scheduleFireTask(nullptr, nullptr, System::random(1000));
		}, "ScheduleTurretFireTaskLambda");
	}
}

void TurretZoneComponent::notifyDissapear(SceneObject* sceneObject, TreeEntry* entry) const {
	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if (!sceneObject->isTurret() || target == nullptr || !target->isPlayerCreature())
		return;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(sceneObject);
	TurretDataComponent* turretData = cast<TurretDataComponent*>(sceneObject->getDataObjectComponent()->get());
	CreatureObject* player = target.castTo<CreatureObject*>();

	if (turret == nullptr || turretData == nullptr || player == nullptr || player->isInvisible())
		return;

	int32 newValue = (int32) turretData->decrementNumberOfPlayersInRange();

	if (newValue < 0) {
		int oldValue;

		do {
			oldValue = (int)turretData->getNumberOfPlayersInRange();

			newValue = oldValue;

			if (newValue < 0)
				newValue = 0;
		} while (!turretData->compareAndSetNumberOfPlayersInRange((uint32)oldValue, (uint32)newValue));
	}
}

void TurretZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, TreeEntry* entry) const {
	if (sceneObject == nullptr || !sceneObject->isTurret()) {
		return;
	}

	ManagedReference<TurretObject*> turret = cast<TurretObject*>(sceneObject);

	if (turret == nullptr || (turret->getFaction() == Factions::FACTIONNEUTRAL) || (turret->getOwnerObjectID() < 1)) {
		return;
	}

	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if (target == nullptr || !target->isCreatureObject()) {
		return;
	}

	DataObjectComponentReference* dataComponent = sceneObject->getDataObjectComponent();

	if (dataComponent == nullptr) {
		return;
	}

	TurretDataComponent* turretData = cast<TurretDataComponent*>(dataComponent->get());

	if (turretData == nullptr) {
		return;
	}

	try {
		auto creatureTarget = target->asCreatureObject();

		if (creatureTarget == nullptr) {
			return;
		}

		uint64 targetId = creatureTarget->getObjectID();

		// Check if the creature is attackable by the turret (factional enemies)
		if (!creatureTarget->isAttackableBy(turret)) {
			return;
		}

		// Check if they creature is in range
		if (sceneObject->isInRange(target, turretData->getMaxMineRange())) {
			// Add players to the notified list
			if (creatureTarget->isPlayerCreature() && !turretData->hasNotifiedPlayer(targetId)) {
				turretData->addNotifiedPlayer(targetId);

				creatureTarget->sendSystemMessage("@faction_perk:minefield_near"); // You have breached the perimeter of an enemy minefield.
			}

			if ((creatureTarget->getPosture() != CreaturePosture::PRONE) && turretData->canExplodeMine() && sceneObject->getContainerObjectsSize() > 0) {
				Reference<MinefieldAttackTask*> task = new MinefieldAttackTask(turret, creatureTarget);

				if (task != nullptr) {
					task->schedule(250);
				}
			}
		} else if (creatureTarget->isPlayerCreature() && turretData->hasNotifiedPlayer(targetId)) {
			creatureTarget->sendSystemMessage("@faction_perk:minefield_exit"); // You have left the perimeter of an enemy minefield.

			turretData->removeNotifiedPlayer(targetId);
		}
	} catch (Exception& e) {
	}

	return;
}
