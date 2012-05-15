/*
 * CloningTerminalMenuComponent.h
 *
 *  Created on: 01/13/2012
 *      Author: Elvaron
 */

#ifndef CLONINGTERMINALMENUCOMPONENT_H_
#define CLONINGTERMINALMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class CloningTerminalMenuComponent : public TangibleObjectMenuComponent {
public:

	/**
	 * Fills the radial options, needs to be overriden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	/**
	 * Handles the radial selection sent by the client, must be overriden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successfull
	 */
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);

};


#endif /* CloningTerminalMENUCOMPONENT_H_ */
