/*
 * CampKitMenuComponent
 *
 *  Created on: 1/1/2012
 *      Author: kyle
 */

#ifndef FIREWORKSHOWMENUCOMPONENT_H_
#define FIREWORKSHOWMENUCOMPONENT_H_

#include "server/zone/objects/tangible/components/TangibleObjectMenuComponent.h"
#include "server/zone/objects/tangible/firework/FireworkObject.h"

class FireworkShowMenuComponent : public TangibleObjectMenuComponent {
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

private:

	void startShow(CreatureObject* player, FireworkObject* firework);

	void addEvent(CreatureObject* player, FireworkObject* firework);

};


#endif /* FIREWORKSHOWMENUCOMPONENT_H_ */
