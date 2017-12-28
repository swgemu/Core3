/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GARAGEZONECOMPONENT_H_
#define GARAGEZONECOMPONENT_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/structure/components/StructureZoneComponent.h"

namespace server {
namespace zone {
class QuadTreeEntry;
namespace objects {
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server

class GarageZoneComponent : public StructureZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) const;
	void notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) const;
};

#endif /* GARAGEZONECOMPONENT_H_ */
