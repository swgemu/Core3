#ifndef ENCLAVECONTAINERCOMPONENT_H_
#define ENCLAVECONTAINERCOMPONENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/components/StructureContainerComponent.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server

class EnclaveContainerComponent : public StructureContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
	bool checkBuildingPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
	bool checkCellPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
};

#endif /* ENCLAVECONTAINERCOMPONENT_H_ */
