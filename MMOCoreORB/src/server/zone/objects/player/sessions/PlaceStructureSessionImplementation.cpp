/*
 * PlaceStructureSessionImplementation.cpp
 *
 *  Created on: Jun 13, 2011
 *      Author: crush
 */

#include "PlaceStructureSession.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/scene/SessionFacadeType.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"

int PlaceStructureSessionImplementation::initializeSession() {
	//Ensure that the deed can be placed in the current position.
	//Send the EnterStructurePlacementModeMessage

	creatureObject->addActiveSession(SessionFacadeType::PLACESTRUCTURE, _this);

	return 0;
}

int PlaceStructureSessionImplementation::constructStructure(float x, float y, int angle) {
	positionX = x;
	positionY = y;
	directionAngle = angle;

	//Check if the deed has a construction barricade.

	//If not skip straight to structure placement.

	return 0;
}
