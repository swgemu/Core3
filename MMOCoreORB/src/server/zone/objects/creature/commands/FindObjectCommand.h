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
#include "server/zone/objects/player/sui/callbacks/FindObjectSuiCallback.h"

class FindObjectCommand : public QueueCommand {
public:

	FindObjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		try {
			StringTokenizer tokenizer(arguments.toString());

			Reference<SceneObject*> targetObject = NULL;
			Reference<PlayerObject*> ghost = creature->getSlottedObject("ghost").castTo<PlayerObject*>();

			if (!tokenizer.hasMoreTokens()) {
				targetObject = server->getZoneServer()->getObject(creature->getTargetID());

				if (targetObject != NULL) {
					Locker crossLocker(targetObject, creature);

					Vector3 worldPosition = targetObject->getWorldPosition();

					ManagedReference<WaypointObject*> obj = server->getZoneServer()->createObject(0xc456e788, 1).castTo<WaypointObject*>();
					obj->setPlanetCRC(targetObject->getPlanetCRC());
					obj->setPosition(worldPosition.getX(), 0, worldPosition.getY());

					obj->setActive(true);

					ghost->addWaypoint(obj, false, true);
					return SUCCESS;
				}
			}

			Zone* zone = creature->getZone();
			if(zone == NULL)
				return GENERALERROR;

			String objectFilter;
			float range = zone->getMaxX() * 2;

			tokenizer.getStringToken(objectFilter);

			if (tokenizer.hasMoreTokens())
				range = tokenizer.getFloatToken();

			ManagedReference<SuiListBox*> findResults = new SuiListBox(creature, SuiWindowType::ADMIN_FIND_OBJECT);
			findResults->setCallback(new FindObjectSuiCallback(server->getZoneServer()));
			findResults->setPromptTitle("Find Object");
			findResults->setPromptText("Here are the objects that match your search:");
			findResults->setCancelButton(true, "");
			findResults->setOkButton(true, "@treasure_map/treasure_map:store_waypoint");
			findResults->setOtherButton(true, "@go");

			StringBuffer results;

			SortedVector<ManagedReference<QuadTreeEntry*> > objects(512, 512);
			zone->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), range, &objects, true);

			for (int i = 0; i < objects.size(); ++i) {
				ManagedReference<SceneObject*> object = cast<SceneObject*>(objects.get(i).get());

				if (object == NULL)
					continue;

				if(object == creature)
					continue;

				results.deleteAll();

				Locker crlocker(object, creature);

				String name = object->getDisplayedName();

				if (objectFilter == "-p") {
					if (!object->isPlayerCreature())
						continue;
				} else if (!name.toLowerCase().contains(objectFilter.toLowerCase()))
					continue;

				results << name;
				results << " (" << String::valueOf(object->getWorldPositionX());
				results << ", " << String::valueOf(object->getWorldPositionY()) << ")";

				findResults->addMenuItem(results.toString(), object->getObjectID());
			}

			if (findResults->getMenuSize() < 1) {
				creature->sendSystemMessage("No objects were found that matched that filter.");
				return SUCCESS;
			}

			ghost->addSuiBox(findResults);
			creature->sendMessage(findResults->generateMessage());

		} catch (Exception& e) {
			creature->sendSystemMessage("Syntax: /findobject <string filter> <range>");
		}

		return SUCCESS;
	}

};

#endif //FINDOBJECTCOMMAND_H_
