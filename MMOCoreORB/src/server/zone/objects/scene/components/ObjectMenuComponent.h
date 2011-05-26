/*
 * ObjectMenuComponent.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef OBJECTMENUCOMPONENT_H_
#define OBJECTMENUCOMPONENT_H_

#include "SceneObjectComponent.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
    class SceneObject;
   }

   namespace player {
    class PlayerCreature;
   }
  }

  namespace packets {
   namespace object {
    class ObjectMenuResponse;
   }
  }

  class Zone;
 }
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::player;
using namespace server::zone::packets::object;


class ObjectMenuComponent : public SceneObjectComponent, public Logger {
public:

	/**
	 * Fills the radial options, needs to be overriden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, PlayerCreature* player);

	/**
	 * Handles the radial selection sent by the client, must be overriden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successfull
	 */
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, PlayerCreature* player, byte selectedID);

};

#endif /* OBJECTMENUCOMPONENT_H_ */
