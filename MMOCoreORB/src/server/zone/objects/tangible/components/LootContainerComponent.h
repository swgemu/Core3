/*
 * LootContainerComponent.h
 *
 *  Created on: Jan 24, 2012
 *      Author: xyborn
 */

#ifndef LOOTCONTAINERCOMPONENT_H_
#define LOOTCONTAINERCOMPONENT_H_

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

class LootContainerComponent: public ContainerComponent {
public:
	int notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) const;
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const;
};

#endif /* LOOTCONTAINERCOMPONENT_H_ */
