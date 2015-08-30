/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef COAENCODEDDISKMENUCOMPONENT_H_
#define COAENCODEDDISKMENUCOMPONENT_H_

#include "server/zone/objects/tangible/components/TangibleObjectMenuComponent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class CoaEncodedDiskMenuComponent : public TangibleObjectMenuComponent {
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

private:
	String getFaction(TangibleObject* disk);

	bool isDecoded(TangibleObject* disk);
};


#endif /* COAENCODEDDISKMENUCOMPONENT_H_ */
