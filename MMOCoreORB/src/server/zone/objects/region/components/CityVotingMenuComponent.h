/*
 * CityVotingMenuComponent.h
 *
 *  Created on: Feb 12, 2012
 *      Author: xyborn
 */

#ifndef CITYVOTINGMENUCOMPONENT_H_
#define CITYVOTINGMENUCOMPONENT_H_

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

class CityVotingMenuComponent : public ObjectMenuComponent {
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};

#endif /* CITYVOTINGMENUCOMPONENT_H_ */
