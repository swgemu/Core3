/*
 * VendorZoneComponent.h
 *
 *  Created on: Jul 24, 2012
 *      Author: kyle
 */

#ifndef VENDORZONECOMPONENT_H_
#define VENDORZONECOMPONENT_H_

#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/QuadTreeEntry.h"

class VendorZoneComponent : public ZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) const {
		ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

		if (target == NULL || !target->isPlayerCreature())
			return;

		VendorDataComponent* data = cast<VendorDataComponent*>(sceneObject->getDataObjectComponent()->get());

		if (data == NULL || !data->isAdBarkingEnabled())
			return;

		if (data->hasBarkTarget(target))
			return;

		if (target->getDistanceTo(sceneObject) <= VendorDataComponent::BARKRANGE) {
			if (data->canBark()) {
				data->performVendorBark(target);
			} else {
				data->addBarkTarget(target);
			}
		}
	}
};

#endif /* VENDORZONECOMPONENT_H_ */
