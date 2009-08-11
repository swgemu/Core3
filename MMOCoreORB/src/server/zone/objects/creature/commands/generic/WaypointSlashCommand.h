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

#ifndef WAYPOINTSLASHCOMMAND_H_

#define WAYPOINTSLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"
//#include "../../../waypoint/WaypointObject.h"

class WaypointSlashCommand : public QueueCommand {
public:

	WaypointSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	bool doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return false;

		if (!checkInvalidPostures(creature))
			return false;
		/*
		int counter = 0;
		String dummy;

		packet->shiftOffset(8);

		String usageError = "Usage: /waypoint X Y <name> or /waypoint <name>";

		UnicodeString rawWaypoint;
		packet->parseUnicode(rawWaypoint);
		String waypointData = rawWaypoint.toString();

		String waypointName = "New Waypoint";
		String planet = Planet::getPlanetName(player->getZoneID());
		float x = player->getPositionX();
		float y = player->getPositionY();
		float z = 0.0f;

		SceneObject* parentObject = player->getParent();

		if (parentObject != NULL) {
			if (parentObject->isCell()) {
				SceneObject* grandParentObject = parentObject->getParent();

				if (grandParentObject != NULL) {
					x = grandParentObject->getPositionX();
					y = grandParentObject->getPositionY();
				}
			}
		}

		StringTokenizer tokenizer(waypointData);
		tokenizer.setDelimeter(" ");

		if (tokenizer.hasMoreTokens()) {

			String arg1;
			tokenizer.getStringToken(arg1);

			if (tokenizer.hasMoreTokens()) {
				if (isalpha(arg1[0]) == 0) {
					//A waypoint in the form of /waypoint X Y <name>
					x = atof(arg1.toCharArray());

					if (tokenizer.hasMoreTokens()) {
						String temp;
						tokenizer.getStringToken(temp);
						if (isalpha(temp[0]) == 0) {
							y = atof(temp.toCharArray());
						} else {
							player->sendSystemMessage(usageError);
							return false;
						}
					}

					StringBuffer newWaypointName;

					while (tokenizer.hasMoreTokens()) {
						String name;
						tokenizer.getStringToken(name);
						newWaypointName << name << " ";
					}

					*//*if (!newWaypointName.isEmpty())
					 newWaypointName.deleteRange(0, 1);*/// ????
					/*
					waypointName = newWaypointName.toString();
				} else {
					//A waypoint in the form of /waypoint planet X Z Y - Planetary Map
					planet = arg1;

					if (Planet::getPlanetID(planet) < 0) { //Not a valid planet name - malformed command
						player->sendSystemMessage(usageError);
						return false;
					}

					if (tokenizer.hasMoreTokens()) {
						String temp;
						tokenizer.getStringToken(temp);

						if (!Character::isLetterOrDigit(temp.charAt(0))) {
							x = Float::valueOf(temp);
						} else {
							player->sendSystemMessage(usageError);
							return false;
						}
					}

					if (tokenizer.hasMoreTokens()) {
						String temp;
						tokenizer.getStringToken(temp);

						if (!Character::isLetterOrDigit(temp.charAt(0))) {
							z = Float::valueOf(temp);
						} else {
							player->sendSystemMessage(usageError);
							return false;
						}
					}

					if (tokenizer.hasMoreTokens()) {
						String temp;
						tokenizer.getStringToken(temp);

						if (!Character::isLetterOrDigit(temp.charAt(0))) {
							y = Float::valueOf(temp);
						} else {
							player->sendSystemMessage(usageError);
							return false;
						}
					}
				}
			} else {
				//A waypoint in the form of /waypoint <name>
				waypointName = arg1;
			}
		}

		x = (x < -8192) ? -8192 : x;
		x = (x > 8192) ? 8192 : x;

		y = (y < -8192) ? -8192 : y;
		y = (y > 8192) ? 8192 : y;

		//Create our waypoint
		WaypointObject* waypoint = new WaypointObject(player->getNewItemID());
		waypoint->setPlanetName(planet);
		waypoint->setPosition(x, z, y);
		waypoint->setCustomName(waypointName);
		waypoint->setActivated(true);

		player->addWaypoint(waypoint);*/
		return true;
	}

};

#endif //WAYPOINTSLASHCOMMAND_H_

