/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
