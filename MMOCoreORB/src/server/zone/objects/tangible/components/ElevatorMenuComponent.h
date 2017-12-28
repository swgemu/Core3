/*
 * ElevatorMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#ifndef ELEVATORMENUCOMPONENT_H_
#define ELEVATORMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"
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

class ElevatorMenuComponent : public TangibleObjectMenuComponent {
protected:
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};

#endif /* ELEVATORMENUCOMPONENT_H_ */
