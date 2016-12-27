/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WAYPOINTDATAPADMENUCOMPONENT_H_
#define WAYPOINTDATAPADMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class WaypointDatapadMenuComponent : public TangibleObjectMenuComponent {
public:

	/**
	 * Fills the radial options, needs to be overridden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param sceneObject the scene object that the radial options should be filled in for.
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 * @param player the player using the object.
	 */
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;

	/**
	 * Handles the radial selection sent by the client, must be overriden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param sceneObject the scene object that the selected radial option should be handled for.
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successful
	 */
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};


#endif /* WAYPOINTDATAPADMENUCOMPONENT_H_ */
