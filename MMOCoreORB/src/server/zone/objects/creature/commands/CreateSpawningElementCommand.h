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

#ifndef CREATESPAWNINGELEMENTCOMMAND_H_
#define CREATESPAWNINGELEMENTCOMMAND_H_

#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "../../../managers/player/PlayerManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

class CreateSpawningElementCommand : public QueueCommand {
public:

	CreateSpawningElementCommand(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments)
	{

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());

		ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);

		StringTokenizer args(arguments.toString());

		CreatureObject* player = (CreatureObject*) creature;


		if (player == NULL) {
			creature->sendSystemMessage("Spawn: /createSpawningElement self spawn path/to/object.iff");
			creature->sendSystemMessage("Delete: /createSpawningElement self delete oid");
			return GENERALERROR;
		}

		if (!args.hasMoreTokens()) {
			creature->sendSystemMessage("Spawn: /createSpawningElement self spawn path/to/object.iff");
			creature->sendSystemMessage("Delete: /createSpawningElement self delete oid");
			return INVALIDPARAMETERS;
		}

		String itemtype;
		args.getStringToken(itemtype);

		try
		{
			if (itemtype.toLowerCase() == "spawn")
			{
				ZoneServer* zserv = server->getZoneServer();

				String objectTemplate;
				args.getStringToken(objectTemplate);

				ManagedReference<SceneObject*> object =  zserv->createObject(objectTemplate.hashCode(), 0);

				if (object == NULL)
					return GENERALERROR;

				if (object->isBuildingObject() || object->isIntangibleObject())
					return GENERALERROR;

				float x = creature->getPositionX();
				float y = creature->getPositionY();
				float z = creature->getPositionZ();

				ManagedReference<SceneObject*> parent = creature->getParent();

				if (parent != NULL && parent->isCellObject())
					parent->addObject(object, -1);

				object->initializePosition(x, z, y);
				object->setDirection(creature->getDirectionW(), creature->getDirectionX(), creature->getDirectionY(), creature->getDirectionZ());
				object->insertToZone(creature->getZone());

				uint64 objectID = object->getObjectID();
				creature->sendSystemMessage("oid: " + String::valueOf(objectID));
			}

			else if (itemtype.toLowerCase() == "delete")
			{
				ZoneServer* zserv = server->getZoneServer();

				String chatObjectID;
				args.getStringToken(chatObjectID);
				uint64 oid = UnsignedLong::valueOf(chatObjectID);

				ManagedReference<SceneObject*> object = zserv->getObject(oid);

				if (object == NULL)
				{
					creature->sendSystemMessage("Error: Trying to delete invalid oid.");
					return GENERALERROR;
				}

				object->removeFromZone();

				creature->sendSystemMessage("Object " + chatObjectID + " deleted.");
			}
		}

		catch (Exception& e)
		{
			creature->sendSystemMessage("Spawn: /createSpawningElement self spawn path/to/object.iff");
			creature->sendSystemMessage("Delete: /createSpawningElement self delete oid");
		}

		return SUCCESS;
	}

};

#endif //CREATESPAWNINGELEMENTCOMMAND_H_
