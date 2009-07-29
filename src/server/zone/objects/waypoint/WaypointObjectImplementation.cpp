/*
 * WaypointObjectImplementation.cpp
 *
 *  Created on: 29/07/2009
 *      Author: victor
 */

#include "WaypointObject.h"

WaypointObjectImplementation::WaypointObjectImplementation(LuaObject* templateData) :
	IntangibleObjectImplementation(templateData) {

	internalNote = "EMPTY";

	//setObjectName("New Waypoint");

}

unsigned int WaypointObjectImplementation::getPlanetCRC() {
	return planetName.hashCode();
}
