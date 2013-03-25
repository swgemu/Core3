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

#ifndef PLACESTRUCTURECOMMAND_H_
#define PLACESTRUCTURECOMMAND_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"

class PlaceStructureCommand : public QueueCommand {
public:

	PlaceStructureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (creature->isRidingCreature() || creature->isRidingMount()) {
			creature->sendSystemMessage("@player_structure:cant_place_mounted");
			return INVALIDLOCOMOTION;
		}

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getParent() != NULL) {
			creature->sendSystemMessage("@player_structure:not_inside"); //You can not place a structure while you are inside a building.
			return GENERALERROR;
		}

		uint64 deedID;
		float x, y;
		int angle;

		try {
			UnicodeTokenizer tokenizer(arguments);

			deedID = tokenizer.getLongToken();
			x = tokenizer.getFloatToken();
			y = tokenizer.getFloatToken();
			angle = tokenizer.getIntToken() * 90;

			// Validate player position -vs- attemped placement
			Zone* zone = creature->getZone();

			if (zone == NULL)
				return GENERALERROR;

			Vector3 position(x, y, zone->getHeight(x, y));
			Vector3 playerPosition = creature->getPosition();
			float distance = position.distanceTo(playerPosition);

			// Client will only scoll about 100m from the placement start position
			if (distance > 100.0f) {
				CreatureObject* player = cast<CreatureObject*>(creature);

				player->sendSystemMessage("@system_msg:out_of_range");

				player->error(player->getFirstName()
					+ " attemped invalid placeStructure on "
					+ zone->getZoneName()
					+ " @ x: " + String::valueOf(x)
					+ ", y: " + String::valueOf(y)
					+ ", z: " + String::valueOf(zone->getHeight(x, y))
					+ " while player @ x: " + String::valueOf(playerPosition.getX())
					+ ", y: " + String::valueOf(playerPosition.getY())
					+ ", z: " + String::valueOf(playerPosition.getZ())
					+ " range: " + String::valueOf(position.distanceTo(playerPosition)) + "m"
				);

				return GENERALERROR;
			}
		} catch (Exception& e) {
			info(e.getMessage());
			return INVALIDPARAMETERS;
		}

		//We want to begin the session here.

		ManagedReference<StructureDeed*> deed = dynamic_cast<StructureDeed*>(server->getZoneServer()->getObject(deedID));

		if (deed != NULL)
			deed->placeStructure(creature, x, y, angle);

		return SUCCESS;
	}

};

#endif //PLACESTRUCTURECOMMAND_H_
