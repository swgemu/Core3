/*
 * CampTerminalMenuComponent
 *
 *  Created on: 1/1/2012
 *      Author: kyle
 */

#ifndef CAMPTERMINALMENUCOMPONENT_H_
#define CAMPTERMINALMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"
#include "server/zone/objects/area/CampSiteActiveArea.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
class CampSiteActiveArea;
}  // namespace area
namespace creature {
class CreatureObject;
}  // namespace creature
namespace player {
class PlayerObject;
}  // namespace player
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

class CampTerminalMenuComponent : public TangibleObjectMenuComponent {
public:

	/**
	 * Fills the radial options, needs to be overriden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	virtual void fillObjectMenuResponse(server::zone::objects::scene::SceneObject* sceneObject, server::zone::packets::object::ObjectMenuResponse* menuResponse, server::zone::objects::creature::CreatureObject* player) const;

	/**
	 * Handles the radial selection sent by the client, must be overriden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successfull
	 */
	virtual int handleObjectMenuSelect(server::zone::objects::scene::SceneObject* sceneObject, server::zone::objects::creature::CreatureObject* player, byte selectedID) const;

	void disbandCamp(server::zone::objects::scene::SceneObject* sceneObject, server::zone::objects::creature::CreatureObject* player) const;

	void assumeCampOwnership(server::zone::objects::scene::SceneObject* sceneObject, server::zone::objects::creature::CreatureObject* player) const;

	void showCampStatus(server::zone::objects::scene::SceneObject* sceneObject, server::zone::objects::creature::CreatureObject* player) const;

	void awardCampExperience(server::zone::objects::player::PlayerObject* ghost, server::zone::objects::area::CampSiteActiveArea* campArea) const;
};


#endif /* CAMPTERMINALMENUCOMPONENT_H_ */
