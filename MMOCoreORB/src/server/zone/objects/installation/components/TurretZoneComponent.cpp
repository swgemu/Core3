/*
 * TurretZoneComponent.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: root
 */

#include "TurretZoneComponent.h"

#include <stddef.h>
#include <algorithm>

#include "TurretDataComponent.h"
#include "engine/core/Core.h"
#include "engine/core/ManagedReference.h"
#include "engine/core/TaskManager.h"
#include "engine/util/Observer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/installation/components/TurretObserver.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/components/DataObjectComponentReference.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "system/lang/System.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "system/thread/Locker.h"
#include "system/util/SortedVector.h"
#include "templates/params/ObserverEventType.h"

namespace server {
namespace zone {
class QuadTreeEntry;
class Zone;
}  // namespace zone
}  // namespace server

void TurretZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const {
	if (zne == NULL)
		return;

	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);
	if (installation == NULL)
		return;

	SortedVector<ManagedReference<Observer*> > destructionObservers = installation->getObservers(ObserverEventType::OBJECTDESTRUCTION);

	for (int i = 0; i < destructionObservers.size(); i++) {
		TurretObserver* turretObserver = destructionObservers.get(i).castTo<TurretObserver*>();

		if (turretObserver != NULL) {
			return;
		}
	}

	ManagedReference<TurretObserver*> observer = new TurretObserver();

	installation->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
}

void TurretZoneComponent::notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry) const {
	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if (!sceneObject->isTurret() || target == NULL || !target->isPlayerCreature())
		return;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(sceneObject);
	TurretDataComponent* turretData = cast<TurretDataComponent*>(sceneObject->getDataObjectComponent()->get());
	CreatureObject* player = target.castTo<CreatureObject*>();

	if (turret == NULL || turretData == NULL || player == NULL || player->isInvisible())
		return;

	int newValue = (int) turretData->incrementNumberOfPlayersInRange();

	if (newValue == 1) {
		Core::getTaskManager()->executeTask([=] () {
			Locker locker(turret);

			TurretDataComponent* data = cast<TurretDataComponent*>(turret->getDataObjectComponent()->get());

			if (data) {
				data->scheduleFireTask(NULL, NULL, System::random(1000));
			}
		}, "ScheduleTurretFireTaskLambda");
	}
}

void TurretZoneComponent::notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) const {
	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if (!sceneObject->isTurret() || target == NULL || !target->isPlayerCreature())
		return;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(sceneObject);
	TurretDataComponent* turretData = cast<TurretDataComponent*>(sceneObject->getDataObjectComponent()->get());
	CreatureObject* player = target.castTo<CreatureObject*>();

	if (turret == NULL || turretData == NULL || player == NULL || player->isInvisible())
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
