#ifndef PERSONNELPERKZONECOMPONENT_H_
#define PERSONNELPERKZONECOMPONENT_H_

#include "server/zone/objects/scene/components/ZoneComponent.h"

namespace server {
namespace zone {
class Zone;
namespace objects {
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server

class PersonnelPerkZoneComponent : public ZoneComponent {

public:
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const;
};


#endif /* PERSONNELPERKZONECOMPONENT_H_ */
