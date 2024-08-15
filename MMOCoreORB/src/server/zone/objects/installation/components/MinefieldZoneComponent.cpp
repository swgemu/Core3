/*
 * MinefieldZoneComponent.cpp
 *
 * Created on: Dec 17, 2012
 * Author: root
 */

#include "MinefieldZoneComponent.h"
#include "MinefieldDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "MinefieldAttackTask.h"
#include "server/zone/objects/installation/components/TurretObserver.h"

void MinefieldZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, TreeEntry* entry) const {
	if (sceneObject == nullptr || !sceneObject->isMinefield()) {
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

	MinefieldDataComponent* mineData = cast<MinefieldDataComponent*>(dataComponent->get());

	if (mineData == nullptr) {
		return;
	}

	try {
		auto creatureTarget = target->asCreatureObject();

		if (creatureTarget == nullptr) {
			return;
		}

		uint64 targetId = creatureTarget->getObjectID();

		ManagedReference<TangibleObject*> minefield = sceneObject->asTangibleObject();

		if (minefield == nullptr) {
			return;
		}

		// Check if the creature is attackable by the minefield (factional enemies)
		if (!creatureTarget->isAttackableBy(minefield)) {
			return;
		}

		// Check if they creature is in range
		if (sceneObject->isInRange(target, mineData->getMaxRange())) {
			// Add players to the notified list
			if (creatureTarget->isPlayerCreature() && !mineData->hasNotifiedPlayer(targetId)) {
				mineData->addNotifiedPlayer(targetId);

				creatureTarget->sendSystemMessage("@faction_perk:minefield_near"); // You have breached the perimeter of an enemy minefield.
			}

			if ((creatureTarget->getPosture() != CreaturePosture::PRONE) && mineData->canExplode() && sceneObject->getContainerObjectsSize() > 0) {
				Reference<MinefieldAttackTask*> task = new MinefieldAttackTask(minefield, creatureTarget);

				if (task != nullptr) {
					task->schedule(250);
				}
			}
		} else if (creatureTarget->isPlayerCreature() && mineData->hasNotifiedPlayer(targetId)) {
			creatureTarget->sendSystemMessage("@faction_perk:minefield_exit"); // You have left the perimeter of an enemy minefield.

			mineData->removeNotifiedPlayer(targetId);
		}
	} catch (Exception& e) {
	}

	return;
}

void MinefieldZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const {
	if (zne == nullptr)
		return;

	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);

	if (installation == nullptr)
		return;

	ManagedReference<TurretObserver*> observer = new TurretObserver();

	if (observer != nullptr)
		installation->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
}

void MinefieldZoneComponent::notifyDissapear(SceneObject* sceneObject, TreeEntry* entry) const {
	ManagedReference<CreatureObject*> player = cast<CreatureObject*>(entry);

	if (player == nullptr || !player->isPlayerCreature())
		return;

	MinefieldDataComponent* data = cast<MinefieldDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == nullptr)
		return;

	if (data->hasNotifiedPlayer(player->getObjectID())) {
		data->removeNotifiedPlayer(player->getObjectID());
		player->sendSystemMessage("@faction_perk:minefield_exit"); // You have left the perimeter of an enemy minefield.
	}
}
