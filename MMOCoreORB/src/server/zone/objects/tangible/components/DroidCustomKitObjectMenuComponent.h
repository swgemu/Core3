/*
 * DroidCustomKitObjectMenuComponent.h
 *
 *  Created on: 11/29/2013
 *      Author: Klivian
 */

#ifndef DROIDCUSTOMKITOBJECTMENUCOMPONENT_H_
#define DROIDCUSTOMKITOBJECTMENUCOMPONENT_H_
 
#include "TangibleObjectMenuComponent.h"

class DroidCustomKitObjectMenuComponent : public TangibleObjectMenuComponent {
public:

	/**
	 * Fills the radial options, needs to be overridden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	/**
	 * Handles the radial selection sent by the client, must be overridden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successful
	 */
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);

};

#endif /* DROIDCUSTOMKITOBJECTMENUCOMPONENT_H_ */

