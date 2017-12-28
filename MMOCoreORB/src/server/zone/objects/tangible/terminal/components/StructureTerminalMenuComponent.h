/*
 * StructureTerminalMenuComponent.h
 *
 *  Created on: Feb 26, 2012
 *      Author: swgemu
 */

#ifndef STRUCTURETERMINALMENUCOMPONENT_H_
#define STRUCTURETERMINALMENUCOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
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
namespace packets {
namespace object {
class ObjectMenuResponse;
}  // namespace object
}  // namespace packets
}  // namespace zone
}  // namespace server

class StructureTerminalMenuComponent : public ObjectMenuComponent {
public:
	void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) const;
	int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) const;
};

#endif /* STRUCTURETERMINALMENUCOMPONENT_H_ */
