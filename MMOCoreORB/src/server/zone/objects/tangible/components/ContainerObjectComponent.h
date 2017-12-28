/*
 * ContainerObjectComponent.h
 *
 *  Created on: 07/02/2012
 *      Author: victor
 */

#ifndef CONTAINEROBJECTCOMPONENT_H_
#define CONTAINEROBJECTCOMPONENT_H_

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

class ContainerObjectComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
};


#endif /* CONTAINEROBJECTCOMPONENT_H_ */
