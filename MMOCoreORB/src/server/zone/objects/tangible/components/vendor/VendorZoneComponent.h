/*
 * VendorZoneComponent.h
 *
 *  Created on: Jul 24, 2012
 *      Author: kyle
 */

#ifndef VENDORZONECOMPONENT_H_
#define VENDORZONECOMPONENT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/components/SceneObjectComponent.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
    class SceneObject;
   }

   namespace building {
    class BuildingObject;
   }
  }

  class Zone;
 }
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::building;
using namespace server::zone;

#include "engine/util/u3d/QuadTreeEntry.h"

class VendorZoneComponent : public ZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) {


		ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);
		if(target == NULL || !target->isPlayerCreature())
			return;

		VendorDataComponent* terminalData = NULL;
		DataObjectComponentReference* data = sceneObject->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isVendorData())
			terminalData = cast<VendorDataComponent*>(data->get());

		if(terminalData == NULL || !terminalData->isAdBarkingEnabled())
			return;

		if(target->getDistanceTo(sceneObject) > VendorDataComponent::BARKRANGE) {
			Locker locker(sceneObject);
			terminalData->clearVendorBark(target);
			return;
		}

		if(terminalData != NULL) {
			Locker locker(sceneObject);
			terminalData->performVendorBark(target);
		}
	}

};

#endif /* VENDORZONECOMPONENT_H_ */
