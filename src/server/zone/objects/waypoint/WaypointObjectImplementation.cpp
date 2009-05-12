/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "WaypointObjectImplementation.h"

WaypointObjectImplementation::WaypointObjectImplementation(uint64 objid)
		: WaypointObjectServant(objid, WAYPOINT) {
	init();
}

WaypointObjectImplementation::WaypointObjectImplementation(uint64 objid, SceneObject* obj)
		: WaypointObjectServant(objid, WAYPOINT) {
	init();

	//TODO: Change this when we swap Y to height and Z to depth.
	setPosition(obj->getPositionX(), 0.0f, obj->getPositionY());
	setPlanetName(Planet::getPlanetName(obj->getZoneID()));
}

void WaypointObjectImplementation::init() {
	//Setup Logging Information.
	StringBuffer loggingname;
	loggingname << "WaypointObject :" << getObjectID();
	setLoggingName(loggingname.toString());
	setLogging(false);
	setGlobalLogging(true);

	setWaypointType(WAYPOINT_NORMAL);
	setPlanetName("naboo");
	setInternalNote("EMPTY");
	setActivated(false);
}

/**
 * Updates the waypoint with a new custom name.
 * \param player The player updating the waypoints custom name.
 * \param value The value to update the waypoint to.
 */
void WaypointObjectImplementation::updateCustomName(Player* player, const String& value) {
	setCustomName(value);

	updateWaypoint(player);
}

void WaypointObjectImplementation::insertToZone(Zone* zone) {
	SceneObjectImplementation::insertToZone(zone);
}

/**
 * Send deltas to the player who is receiving the updated waypoint.
 * \param player The player whos waypoint is being updated.
 */
void WaypointObjectImplementation::updateWaypoint(Player* player) {
	if (!player->hasWaypoint(getObjectID()))
		player->addWaypoint(_this);

	player->updateWaypoint(_this);
}

/**
 * Activates the waypoint object, sending the appropriate packets.
 * \param player The player who activated the waypoint object.
 * \note Player should be locked prior to this call.
 */
void WaypointObjectImplementation::activate(Player* player) {
	setActivated(true);

	updateWaypoint(player);
}

/**
 * Deactivates the waypoint object, sending the appropriate packets.
 * \param player The player who deactivated the waypoint object.
 */
void WaypointObjectImplementation::deactivate(Player* player) {
	setActivated(false);

	updateWaypoint(player);
}
