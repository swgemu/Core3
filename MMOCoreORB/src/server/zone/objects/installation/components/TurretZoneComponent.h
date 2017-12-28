/*
 * TurretZoneComponent.h
 *
 *  Created on: Nov 20, 2012
 *      Author: root
 */

#ifndef TURRETZONECOMPONENT_H_
#define TURRETZONECOMPONENT_H_

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

class TurretZoneComponent : public ZoneComponent {

public:
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const;

	void notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry) const;

	void notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) const;
};

#endif /* TURRETZONECOMPONENT_H_ */
