/*
 * CityHallZoneComponent.h
 *
 *  Created on: 31/03/2012
 *      Author: victor
 */

#ifndef CITYHALLZONECOMPONENT_H_
#define CITYHALLZONECOMPONENT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/components/GroundZoneComponent.h"

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

class CityHallZoneComponent : public GroundZoneComponent {
public:
	void destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) const;
};



#endif /* CITYHALLZONECOMPONENT_H_ */
