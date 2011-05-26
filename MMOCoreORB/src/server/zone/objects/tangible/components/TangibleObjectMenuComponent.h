/*
 * TangibleObjectMenuComponent.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef TANGIBLEOBJECTMENUCOMPONENT_H_
#define TANGIBLEOBJECTMENUCOMPONENT_H_

#include "server/zone/objects/scene/components/ObjectMenuComponent.h"

class TangibleObjectMenuComponent : public ObjectMenuComponent {
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


#endif /* TANGIBLEOBJECTMENUCOMPONENT_H_ */
