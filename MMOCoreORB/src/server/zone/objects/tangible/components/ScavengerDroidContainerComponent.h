#ifndef SCAVENGERDROIDCONTAINERCOMPONENT_H_
#define SCAVENGERDROIDCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

namespace server {
namespace zone {
namespace objects {
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

class ScavengerDroidContainerComponent : public ContainerComponent {
public:
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const;
	bool transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient = false, bool allowOverflow = false, bool notifyRoot = true) const;
};

#endif /* SCAVENGERDROIDCONTAINERCOMPONENT_H_ */
