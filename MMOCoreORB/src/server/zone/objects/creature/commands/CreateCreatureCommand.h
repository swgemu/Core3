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

#ifndef CREATECREATURECOMMAND_H_
#define CREATECREATURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"


class CreateCreatureCommand : public QueueCommand {
public:

	CreateCreatureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		float posX = creature->getPositionX(), posY = creature->getPositionY(), posZ = creature->getPositionZ();
		uint64 parID = creature->getParentID();

		String objName = "", tempName = "object/mobile/boba_fett.iff";

		if (!arguments.isEmpty()) {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.setDelimeter(" ");

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(tempName);

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(objName);

			if (!objName.isEmpty() && objName.indexOf("object") == -1 && objName.length() < 6)
				posX = Float::valueOf(objName);
			else
				if (tokenizer.hasMoreTokens())
					posX = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens())
				posZ = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens())
				posY = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens()) {
				int planet = tokenizer.getIntToken();
				zone = creature->getZoneServer()->getZone(planet);
			}

			if (tokenizer.hasMoreTokens())
				parID = tokenizer.getLongToken();
		}

		CreatureManager* creatureManager = zone->getCreatureManager();

		uint32 templ = tempName.hashCode();
		uint32 objTempl = objName.length() > 0 ? objName.hashCode() : 0;

		CreatureObject* npc = NULL;
		if (tempName.indexOf(".iff") != -1)
			npc = creatureManager->spawnCreature(templ, posX, posZ, posY, parID);
		else
			npc = creatureManager->spawnCreature(templ, objTempl, posX, posZ, posY, parID);

		if (npc == NULL)
			creature->sendSystemMessage("could not spawn " + arguments.toString());

		return SUCCESS;
	}

};

#endif //CREATECREATURECOMMAND_H_
