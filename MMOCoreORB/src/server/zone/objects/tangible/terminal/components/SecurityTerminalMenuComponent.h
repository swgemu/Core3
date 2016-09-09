/*
 * SecurityTerminalMenuComponent.h
 *
 *  Created on: Oct 31, 2012
 *      Author: root
 */

#ifndef SECURITYTERMINALMENUCOMPONENT_H_
#define SECURITYTERMINALMENUCOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"

class SecurityTerminalMenuComponent : public ObjectMenuComponent {
protected:


public:

	/**
	 * Fills the radial options, needs to be overriden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;

	/**
	 * Handles the radial selection sent by the client, must be overriden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successfull
	 */
	int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;


};


#endif /* SECURITYTERMINALMENUCOMPONENT_H_ */
