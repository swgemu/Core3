/*
 * CityHallZoneComponent.h
 *
 *  Created on: 31/03/2012
 *      Author: victor
 */

#ifndef CITYHALLZONECOMPONENT_H_
#define CITYHALLZONECOMPONENT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/components/ZoneComponent.h"

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

class CityHallZoneComponent : public ZoneComponent {
public:
	void destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy);
};



#endif /* CITYHALLZONECOMPONENT_H_ */
