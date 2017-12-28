/*
 * PlacableLootContainerComponent.h
 *
 *  Created on: Mar 13, 2013
 *      Author: root
 */

#ifndef PLACEABLELOOTCONTAINERCOMPONENT_H_
#define PLACEABLELOOTCONTAINERCOMPONENT_H_
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

class PlaceableLootContainerComponent: public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const;
};

#endif /* PLACEABLELOOTCONTAINERCOMPONENT_H_ */
