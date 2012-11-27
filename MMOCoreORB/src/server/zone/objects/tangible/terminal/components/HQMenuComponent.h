/*
 * HQMenuComponent.h
 *
 *  Created on: Oct 25, 2012
 *      Author: root
 */

#ifndef HQMENUCOMPONENT_H_
#define HQMENUCOMPONENT_H_
#include "engine/engine.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"

class HQMenuComponent : public ObjectMenuComponent {
protected:

	static const int MAKEREBEL = 222;
	static const int MAKEIMPERIAL = 223;
	// 37 is something in the objectcontroller
	static const int MAKENEUTRAL = 224;
	static const int DESTROY = 225;
	static const int ABORTSHUTDOWN = 226;

	static const int JAMUPLINK = 227;




public:

	/**
	 * Fills the radial options, needs to be overriden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	 void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	/**
	 * Handles the radial selection sent by the client, must be overriden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successfull
	 */
	 int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);


private:
	virtual DestructibleBuildingDataComponent* getDestructibleBuildingDataComponent(BuildingObject* building);
};




#endif /* HQMENUCOMPONENT_H_ */
