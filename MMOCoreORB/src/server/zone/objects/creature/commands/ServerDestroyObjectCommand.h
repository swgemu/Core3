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

#ifndef SERVERDESTROYOBJECTCOMMAND_H_
#define SERVERDESTROYOBJECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"


class ServerDestroyObjectCommand : public QueueCommand {
public:

	ServerDestroyObjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		//creature->info("serverdestroy arguments: " + arguments.toString(), true);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL)
			return GENERALERROR;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (object->canBeDestroyed((CreatureObject*) creature) != 0)
			return GENERALERROR;

		// need to add checks.. inventory, datapad, bank, waypoint

		if (object->isWaypointObject()) {
			PlayerObject* playerObject = (PlayerObject*) creature->getSlottedObject("ghost");

			if (playerObject != NULL)
				playerObject->removeWaypoint(target);

			// delete from database
			object->destroyObjectFromDatabase(true);

			return SUCCESS;
		}

		SceneObject* inventory = creature->getSlottedObject("inventory");
		SceneObject* datapad = creature->getSlottedObject("datapad");
		SceneObject* bank = creature->getSlottedObject("bank");

		if (object->isASubChildOf(inventory) || object->isASubChildOf(datapad) || object->isASubChildOf(bank)) {
			destroyObject(object, creature);
		} else if (object->isASubChildOf(creature)) {
			for (int i = 0; i < object->getArrangementDescriptorSize(); ++i) {
				String descriptor = object->getArrangementDescriptor(i);

				if (descriptor == "inventory" || descriptor == "datapad" || descriptor == "default_weapon"
						|| descriptor == "mission_bag" || descriptor == "ghost" || descriptor == "bank" || descriptor == "hair")
					return GENERALERROR;
			}

			destroyObject(object, creature);
		}

		return SUCCESS;
	}

	void destroyObject(SceneObject* object, CreatureObject* creature) {
		ManagedReference<SceneObject*> parent = object->getParent();

		parent->removeObject(object);

		if (parent == creature)
			creature->broadcastDestroy(object, true);
		else
			object->sendDestroyTo(creature);

		object->destroyObjectFromDatabase(true);
	}

};

#endif //SERVERDESTROYOBJECTCOMMAND_H_
