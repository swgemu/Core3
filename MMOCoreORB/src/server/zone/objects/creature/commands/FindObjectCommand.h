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

#ifndef FINDOBJECTCOMMAND_H_
#define FINDOBJECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/packets/ui/DestroyClientPathMessage.h"

class FindObjectCommand : public QueueCommand {
public:

	FindObjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		Reference<SceneObject*> targetObject = server->getZoneServer()->getObject(creature->getTargetID());

		if (targetObject == NULL) {
			creature->info("invalid targetObject 0x" + String::hexvalueOf((int64)target), true);
			return INVALIDTARGET;
		}

		PathFinderManager* manager = PathFinderManager::instance();

		Vector<WorldCoordinates>* path = manager->findPath(creature, targetObject.get());

		if (path == NULL || path->size() == 0) {
			creature->info("path NULL ||�size == 0", true);
			return GENERALERROR;
		}

		//if (path-)

		//creature->sendMessage(new DestroyClientPathMessage());

		//CreateClientPathMessage* msg = new CreateClientPathMessage();

		PlayerObject* ghost = (PlayerObject*) creature->getSlottedObject("ghost");

		for (int i = 0; i < path->size(); ++i) {
			WorldCoordinates* coord = &path->get(i);
			Vector3 worldPosition = coord->getWorldPosition();

			//msg->addCoordinate(worldPosition.getX(), worldPosition.getZ(), worldPosition.getY());

			ManagedReference<WaypointObject*> obj = (WaypointObject*) server->getZoneServer()->createObject(0xc456e788, 1);
			obj->setPlanetCRC(targetObject->getPlanetCRC());
			obj->setPosition(worldPosition.getX(), 0, worldPosition.getY());

			if (coord->getCell() != NULL) {
				CellObject* cell = (CellObject*) coord->getCell();
				obj->setCellID(cell->getCellNumber());
			}

			obj->setActive(true);

			ghost->addWaypoint(obj, false, true);

			/*if (coord->getCell() != NULL)
				obj->setUnknown(coord->getCell()->getObjectID());*/

			//obj->setActive(true);


			//ghost->addWaypoint("tatooine", worldPosition.getX(), worldPosition.getY(), true);

			StringBuffer objectFoorBar;
			objectFoorBar << "path node point x:" << worldPosition.getX() << " z:" << worldPosition.getZ() << " y:" << worldPosition.getY();
			creature->info(objectFoorBar.toString(), true);
		}

		//creature->sendMessage(msg);

		delete path;

		return SUCCESS;
	}

};

#endif //FINDOBJECTCOMMAND_H_
