/*
 * StarshipPaintKitObjectMenuComponent.h
 *
 *  Created on: 11/2/2024
 *      Author: Halyn
 */

#ifndef STARSHIPPAINTKITOBJECTMENUCOMPONENT_H_
#define STARSHIPPAINTKITOBJECTMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class StarshipPaintKitObjectMenuComponent : public TangibleObjectMenuComponent {
public:

	/**
	 * Fills the radial options, needs to be overridden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;

	/**
	 * Handles the radial selection sent by the client, must be overridden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successful
	 */
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;

};

#endif /* StarshipPaintKitObjectMenuComponent_H_ */

