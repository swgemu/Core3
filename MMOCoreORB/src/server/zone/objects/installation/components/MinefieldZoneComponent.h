/*
 * MinefieldZoneComponent.h
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#ifndef MINEFIELDZONECOMPONENT_H_
#define MINEFIELDZONECOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/QuadTreeEntry.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/components/ZoneComponent.h"

namespace server {
namespace zone {
class QuadTreeEntry;
class Zone;
namespace objects {
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server

class MinefieldZoneComponent : public ZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) const;
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const;
};


#endif /* MINEFIELDZONECOMPONENT_H_ */
