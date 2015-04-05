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

#ifndef SETLASTNAMECOMMAND_H_
#define SETLASTNAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetLastNameCommand : public QueueCommand {
public:

	SetLastNameCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = server->getZoneServer();

		Reference<SceneObject*> targetObj = zoneServer->getObject(target);

		if(targetObj == NULL || !targetObj->isPlayerCreature()) {
			creature->sendSystemMessage("Invalid target. This command only works on players");
			return INVALIDTARGET;
		}

		Locker clocker(targetObj, creature);

		String newName = arguments.toString();

		CreatureObject* targetCreature = targetObj.castTo<CreatureObject*>();

		NameManager* nameManager = server->getNameManager();

		int result = nameManager->validateLastName(newName, targetCreature->getSpecies());

		switch (result) {
		case NameManagerResult::ACCEPTED:
			break;
		case NameManagerResult::DECLINED_RACE_INAPP:
			creature->sendSystemMessage("That name is inappropriate for the player's species.");
			return INVALIDPARAMETERS;
			break;
		case NameManagerResult::DECLINED_PROFANE:
			creature->sendSystemMessage("That name is profane.");
			return INVALIDPARAMETERS;
			break;
		case NameManagerResult::DECLINED_DEVELOPER:
			creature->sendSystemMessage("That is a developer's name.");
			return INVALIDPARAMETERS;
			break;
		case NameManagerResult::DECLINED_FICT_RESERVED:
			creature->sendSystemMessage("That name is a reserved fictional name.");
			return INVALIDPARAMETERS;
			break;
		case NameManagerResult::DECLINED_RESERVED:
			creature->sendSystemMessage("That name is reserved.");
			return INVALIDPARAMETERS;
			break;
		case NameManagerResult::DECLINED_SYNTAX:
			creature->sendSystemMessage("That name contains invalid syntax.");
			return INVALIDPARAMETERS;
			break;
		}

		String oldFirstName = targetCreature->getFirstName();
		String oldLastName = targetCreature->getLastName();

		String newFullName;
		if (newName.isEmpty()) {
			newFullName = oldFirstName;
		} else {
			newFullName = oldFirstName + " " + newName;
		}

		targetCreature->setCustomObjectName(newFullName, true);

		String creatureLastName = targetCreature->getLastName();
		Database::escapeString(creatureLastName);

		int galaxyID = zoneServer->getGalaxyID();

		StringBuffer charDirtyQuery;
		charDirtyQuery
				<< "UPDATE `characters_dirty` SET `surname` = '"  << creatureLastName
				<< "' WHERE `character_oid` = '" << targetCreature->getObjectID()
				<< "' AND `galaxy_id` = '" << galaxyID << "'";

		ServerDatabase::instance()->executeStatement(charDirtyQuery);

		StringBuffer charQuery;
		charQuery
				<< "UPDATE `characters` SET `surname` = '"  << creatureLastName
				<< "' WHERE `character_oid` = '" << targetCreature->getObjectID()
				<< "' AND `galaxy_id` = '" << galaxyID << "'";

		ServerDatabase::instance()->executeStatement(charQuery);

		creature->sendSystemMessage("Last name changed from '" + oldLastName + "' to '" + newName + "'");

		PlayerObject* targetGhost = targetCreature->getPlayerObject();
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (targetGhost != NULL && targetGhost->isPrivileged() && playerManager != NULL) {
			playerManager->updatePermissionName(targetCreature, targetGhost->getAdminLevel());
		}

		return SUCCESS;
	}

};

#endif //SETLASTNAMECOMMAND_H_
