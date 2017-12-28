/*
 * ElevatorUpMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#include "ElevatorUpMenuComponent.h"

#include "server/zone/objects/tangible/components/ElevatorMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

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

void ElevatorUpMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) const {
	menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up");
}

int ElevatorUpMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) const {
	if (selectedID != 198)
		return 0;

	return ElevatorMenuComponent::handleObjectMenuSelect(sceneObject, creature, selectedID);
}
