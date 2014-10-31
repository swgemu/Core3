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

#ifndef TELEPORTTARGETCOMMAND_H_
#define TELEPORTTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"

class TeleportTargetCommand : public QueueCommand {
public:

	TeleportTargetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Zone*> targetZone = creature->getZone();

		if (targetZone == NULL)
			return GENERALERROR; //Creature must be in a valid zone to use the command...

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == creature)
			obj = NULL; //In case the player has himself targeted with the command.

		String targetName = "";
		String planetName = targetZone->getZoneName();
		float x = creature->getPositionX();
		float y = creature->getPositionY();
		float z = creature->getPositionZ();
		uint64 parentID = creature->getParentID();

		ManagedReference<CreatureObject*> targetCreature = NULL;
		UnicodeTokenizer tokenizer(arguments);

		try {
			tokenizer.getStringToken(targetName);
		} catch (Exception& e) {
			targetCreature = cast<CreatureObject*>(obj.get());
		}

		try {

			if (tokenizer.hasMoreTokens()) {

				x = tokenizer.getFloatToken();
				y = tokenizer.getFloatToken();

				if(tokenizer.hasMoreTokens()) {
					tokenizer.getStringToken(planetName);
					planetName = planetName.toLowerCase();
				}

				targetZone = targetZone->getZoneServer()->getZone(planetName);

				if (targetZone == NULL)
					throw Exception();

				z = targetZone->getHeight(x, y);
			}

			if (tokenizer.hasMoreTokens())
				z = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens())
				parentID = tokenizer.getLongToken();

		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /teleportTarget [<name>] -- Bring target to you");
			creature->sendSystemMessage("SYNTAX: /teleportTarget [<name>] <x> <y> [<planet>] [<z> <parentID>]");
			return INVALIDPARAMETERS;
		}

		if (!targetName.isEmpty()) {
			ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
			targetCreature = playerManager->getPlayer(targetName);
		}

		if (targetCreature == NULL) {
			creature->sendSystemMessage("The specified player does not exist.");
			return GENERALERROR;
		}

		Locker _lock(targetCreature, creature);

		targetCreature->switchZone(planetName, x, z, y, parentID);

		return SUCCESS;
	}

};

#endif //TELEPORTTARGETCOMMAND_H_
