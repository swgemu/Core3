/*
 * SkillBuffMenuComponent.h
 *
 *  Created on: 9/20/2013
 *      Author: Klivian
 */

#ifndef SKILLBUFFOBJECTMENUCOMPONENT_H_
#define SKILLBUFFOBJECTMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class SkillBuffObjectMenuComponent : public TangibleObjectMenuComponent {
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


#endif /* SKILLBUFFOBJECTMENUCOMPONENT_H_ */
