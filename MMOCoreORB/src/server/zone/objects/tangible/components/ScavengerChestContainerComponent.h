#ifndef SCAVENGERCHESTCONTAINERCOMPONENT_H_
#define SCAVENGERCHESTCONTAINERCOMPONENT_H_
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
namespace sys {
namespace lang {
class String;
}  // namespace lang
}  // namespace sys

class ScavengerChestContainerComponent: public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* container, CreatureObject* creature, uint16 permission) const;
	int notifyObjectRemoved(SceneObject* container, SceneObject*, SceneObject* destination) const;
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const;
};

#endif /* SCAVENGERCHESTCONTAINERCOMPONENT_H_ */
