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

#ifndef OPENCONTAINERCOMMAND_H_
#define OPENCONTAINERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/RelockLootContainerEvent.h"

class OpenContainerCommand : public QueueCommand {
public:

	OpenContainerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		//creature->info("OpenContainerCommand", true);

		ManagedReference<SceneObject*> objectToOpen = NULL;

		StringTokenizer args(arguments.toString());

		int counter = 0;
		if(args.hasMoreTokens())
			counter = args.getIntToken();

		objectToOpen = server->getZoneServer()->getObject(target);

		if (objectToOpen == NULL)
			return GENERALERROR;

		/// This is weird, when you select a schematic and the crafting station has a
		/// Hopper the client requests to open the hopper container to the player
		/// Which isn't supposed to happen
		if(objectToOpen->getParent() != NULL && objectToOpen->getParent().get()->isCraftingStation())
			return GENERALERROR;

		Locker clocker(objectToOpen, creature);

/*
		ManagedReference<SceneObject*> objectsParent = objectToOpen->getParent();

		if (objectsParent != NULL && objectsParent->isCellObject()) {
			ManagedReference<BuildingObject*> building = cast<BuildingObject*>( objectsParent->getParent());

			if (!building->isOnAdminList(creature->getFirstName())) {
				//info("not on admin list", true);
				return GENERALERROR;
			}
		} else if (!objectToOpen->isASubChildOf(creature)) {
			return GENERALERROR;
		}*/

	/*	if (objectToOpen->isContainerObject()) {
			ManagedReference<Container*> container = cast<Container*>(objectToOpen.get());
			Zone* zone = creature->getZone();
			if (zone->getZoneName() != "tutorial" && (container->checkPermission(creature) == 0))
				return GENERALERROR;
		}

*/

		ManagedReference<Container*> container = objectToOpen.castTo<Container*>();
		if(container != NULL && container->isContainerLocked()) {
			creature->sendSystemMessage("@slicing/slicing:locked");
			return SUCCESS;
		}


		if (objectToOpen->checkContainerPermission(creature, ContainerPermissions::OPEN)) {

			if(objectToOpen->getGameObjectType() == SceneObjectType::STATICLOOTCONTAINER) {
				if(container != NULL && container->isRelocking() == false) {
					Reference<RelockLootContainerEvent*> relockEvent = new RelockLootContainerEvent(container);
					relockEvent->schedule(container->getLockTime());
				}
			}

			objectToOpen->openContainerTo(creature);

			objectToOpen->notifyObservers(ObserverEventType::OPENCONTAINER, creature);
		} else {
			//You do not have permission to access this container.
			creature->sendSystemMessage("@error_message:perm_no_open");
		}

		return SUCCESS;
	}

};

#endif //OPENCONTAINERCOMMAND_H_
