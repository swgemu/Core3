/*
 * GCWBaseContainerComponent.h
 *
 *  Created on: Dec 6, 2012
 *      Author: root
 */

#ifndef GCWBASECONTAINERCOMPONENT_H_
#define GCWBASECONTAINERCOMPONENT_H_

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/components/StructureContainerComponent.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace building {
class BuildingObject;
}  // namespace building
namespace creature {
class CreatureObject;
}  // namespace creature
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server

class GCWBaseContainerComponent : public StructureContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;

	bool checkContainerPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage) const;

	bool checkPVPPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage) const;

	bool checkPVEPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage) const;

};

#endif /* GCWBASECONTAINERCOMPONENT_H_ */
