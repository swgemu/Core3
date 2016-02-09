/*
 * TurretZoneComponent.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: root
 */

#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "TurretZoneComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "TurretDataComponent.h"

#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/objects/installation/components/TurretObserver.h"

#include "server/zone/managers/combat/CreatureAttackData.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "TurretFireTask.h"

void TurretZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zne) {
	if (zne == NULL)
		return;

	ManagedReference<TurretObserver*> observer = new TurretObserver();
	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);
	if (installation == NULL)
		return;

	installation->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
}

void TurretZoneComponent::notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry) {
	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if (!sceneObject->isTurret() || target == NULL || !target->isPlayerCreature())
		return;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(sceneObject);
	TurretDataComponent* turretData = cast<TurretDataComponent*>(sceneObject->getDataObjectComponent()->get());
	CreatureObject* player = target.castTo<CreatureObject*>();

	if (turret == NULL || turretData == NULL || player == NULL || player->isInvisible())
		return;

	Locker locker(turret);

	int newValue = (int) turretData->incrementNumberOfPlayersInRange();

	if (newValue == 1) {
		turretData->scheduleFireTask(NULL, NULL, System::random(1000));
	}
}

void TurretZoneComponent::notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) {
	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if (!sceneObject->isTurret() || target == NULL || !target->isPlayerCreature())
		return;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(sceneObject);
	TurretDataComponent* turretData = cast<TurretDataComponent*>(sceneObject->getDataObjectComponent()->get());
	CreatureObject* player = target.castTo<CreatureObject*>();

	if (turret == NULL || turretData == NULL || player == NULL || player->isInvisible())
		return;

	Locker locker(turret);

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
