/*
 * SpaceObjectImplementation.cpp
 *
 *  Created on: 2024-11-23
 *  Author: Hakry
 */

#include "server/zone/objects/staticobject/SpaceObject.h"
#include "server/zone/ZoneServer.h"

float SpaceObjectImplementation::getOutOfRangeDistance(uint64 specialRangeID) {
	return ZoneServer::SPACESTATIONRANGE;
}
