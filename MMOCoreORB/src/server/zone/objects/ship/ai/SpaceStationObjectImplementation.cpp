/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/ai/SpaceStationObject.h"
#include "server/zone/ZoneServer.h"

float SpaceStationObjectImplementation::getOutOfRangeDistance() const {
	return ZoneServer::SPACESTATIONRANGE;
}
