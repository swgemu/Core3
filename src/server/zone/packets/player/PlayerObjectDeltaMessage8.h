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

#ifndef PLAYEROBJECTDELTAMESSAGE8_H_
#define PLAYEROBJECTDELTAMESSAGE8_H_

#include "../DeltaMessage.h"

#include "../../objects/player/PlayerObjectImplementation.h"
#include "../../objects/waypoint/WaypointObject.h"

class PlayerObjectDeltaMessage8 : public DeltaMessage {
	PlayerObjectImplementation* play;

public:
	PlayerObjectDeltaMessage8(PlayerObjectImplementation* pl)
			: DeltaMessage(pl->getObjectID(), 0x504C4159, 8) {
		play = pl;
	}

	void startWaypointUpdate() {
		startUpdate(0x01);
		startList(1, play->getNewWaypointListCount(1));
	}

	void addWaypoint(WaypointObject* waypoint) {
		insertByte(0x00);
		insertLong(waypoint->getObjectID());
		insertInt(0); //This can't be cellid can it? An integer as cell id?
		insertFloat(waypoint->getPositionX());
		insertFloat(0.0f); //Z is always 0.0f (unless in space?)
		insertFloat(waypoint->getPositionY());
		insertLong(0); //Unsure of this? Perhaps this is cellid?
		insertInt(waypoint->getPlanetCRC()); //Planet CRC
		insertUnicode(waypoint->getCustomName());
		insertLong(waypoint->getObjectID()); //Objectid again?
		//TODO: Perhaps this is waypoint type.
		insertByte(waypoint->getWaypointType()); //Waypoint text color. Flag  1=Normal WP (light blue)  / 0 = White WP text  / 2 = green WP text
		insertByte((uint8) waypoint->isActivated()); //Waypoint Activated Flag
	}

	void removeWaypoint(WaypointObject* waypoint) {
		insertByte(0x01);
		insertLong(waypoint->getObjectID());
		insertInt(0); //This can't be cellid can it? An integer as cell id?
		insertFloat(waypoint->getPositionX());
		insertFloat(0.0f); //Z is always 0.0f (unless in space?)
		insertFloat(waypoint->getPositionY());
		insertLong(0); //Unsure of this? Perhaps this is cellid?
		insertInt(waypoint->getPlanetCRC()); //Planet CRC
		insertUnicode(waypoint->getCustomName());
		insertLong(waypoint->getObjectID()); //Objectid again?
		//TODO: Perhaps this is waypoint type.
		insertByte(waypoint->getWaypointType()); //What color is the waypoint? Flag  1=Normal WP (light blue)  / 0 = White WP text  / 2 = green WP text
		insertByte((uint8) waypoint->isActivated()); //Waypoint Activated Flag
	}

	void updateForcePower() {
		addIntUpdate(0x02, play->getForcePower());
	}

	void updateForcePowerMax() {
		addIntUpdate(0x03, play->getForcePowerMax());
	}

	void startExperienceUpdate(int typesOfExp) {
		startUpdate(0);
		startList(typesOfExp, play->getNewExperienceListCount(typesOfExp));
	}

	void addExperience(const String& name, int xp) {
		insertByte(0);
		insertAscii(name.toCharArray());
		insertInt(xp);
	}

	void removeExperience(const String& name) {
		insertByte(1);
		insertAscii(name.toCharArray());
		insertInt(0);
	}
};

#endif /*PLAYEROBJECTDELTAMESSAGE8_H_*/
