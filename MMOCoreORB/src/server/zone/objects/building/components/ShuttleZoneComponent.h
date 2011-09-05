/*
 * ShuttleZoneComponent.h
 *
 *  Created on: Aug 19, 2011
 *      Author: crush
 */

#ifndef SHUTTLEZONECOMPONENT_H_
#define SHUTTLEZONECOMPONENT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/components/SceneObjectComponent.h"

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

class ShuttleZoneComponent : public ZoneComponent {

public:
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zone);
	void notifyRemoveFromZone(SceneObject* sceneObject);
};

#endif /* SHUTTLEZONECOMPONENT_H_ */
