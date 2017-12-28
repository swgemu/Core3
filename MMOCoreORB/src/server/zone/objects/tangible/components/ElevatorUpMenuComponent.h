/*
 * ElevatorUpMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#ifndef ELEVATORUPMENUCOMPONENT_H_
#define ELEVATORUPMENUCOMPONENT_H_

#include "ElevatorMenuComponent.h"
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

class ElevatorUpMenuComponent : public ElevatorMenuComponent {
protected:
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};

#endif /* ELEVATORUPMENUCOMPONENT_H_ */
