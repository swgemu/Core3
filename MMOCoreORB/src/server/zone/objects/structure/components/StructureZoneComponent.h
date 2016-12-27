/*
 * StructureZoneComponent.h
 *
 *  Created on: Apr 15, 2012
 *      Author: TragD
 */

#ifndef STRUCTUREZONECOMPONENT_H_
#define STRUCTUREZONECOMPONENT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/components/ZoneComponent.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
    class SceneObject;
   }

   namespace structure {
    class StructureObject;
   }
  }

  class Zone;
 }
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::structure;
using namespace server::zone;

class StructureZoneComponent : public ZoneComponent {

public:
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zone) const;
	void notifyRemoveFromZone(SceneObject* sceneObject) const;
};

#endif /* STRUCTUREZONECOMPONENT_H_ */
