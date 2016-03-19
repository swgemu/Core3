/*
 * CreatureHabitatMenuComponent
 *
 *  Created on: 3/21/2012
 *      Author: kyle
 */

#ifndef CREATUREHABITATMENUCOMPONENT_H_
#define CREATUREHABITATMENUCOMPONENT_H_

#include "../TangibleObjectMenuComponent.h"


class CreatureHabitatMenuComponent : public TangibleObjectMenuComponent {
public:

	/**
	 * Fills the radial options, needs to be overriden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;

	/**
	 * Handles the radial selection sent by the client, must be overriden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successfull
	 */
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;

private:

	/**
	 * Returns the live creatures stored inside the habitat when it was crafted
	 */
	ManagedReference<TangibleObject*> getLiveCreatures( TangibleObject* creatureHabitat ) const;

};


#endif /* CREATUREHABITATMENUCOMPONENT_H_ */
