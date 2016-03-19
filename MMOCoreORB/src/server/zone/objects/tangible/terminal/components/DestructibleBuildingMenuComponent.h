#ifndef DESTRUCTIBLEBUILDINGMENUCOMPONENT_H_
#define DESTRUCTIBLEBUILDINGMENUCOMPONENT_H_


#include "engine/engine.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/building/BuildingObject.h"

class DestructibleBuildingMenuComponent : public ObjectMenuComponent {

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

	virtual int sendSelfDestructMessage(BuildingObject* building, const String& message) const;

};

#endif /* DESTRUCTIBLEBUILDINGMENUCOMPONENT_H_ */
