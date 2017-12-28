/*
 * StructureContainerComponent.h
 *
 *  Created on: 09/02/2012
 *      Author: victor
 */

#ifndef STRUCTURECONTAINERCOMPONENT_H_
#define STRUCTURECONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"
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

class StructureContainerComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
};

#endif /* STRUCTURECONTAINERCOMPONENT_H_ */
