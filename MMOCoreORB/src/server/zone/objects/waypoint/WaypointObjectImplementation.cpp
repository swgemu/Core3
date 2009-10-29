/*
 * WaypointObjectImplementation.cpp
 *
 *  Created on: 29/07/2009
 *      Author: victor
 */

#include "WaypointObject.h"

void WaypointObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("WaypointObject");
}

unsigned int WaypointObjectImplementation::getPlanetCRC() {
	return planetName.hashCode();
}
