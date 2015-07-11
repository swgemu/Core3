/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETFIRSTNAMECOMMAND_H_
#define SETFIRSTNAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetFirstNameCommand : public QueueCommand {
public:

	SetFirstNameCommand(const String& name, ZoneProcessServer* server)
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

		int result = nameManager->validateFirstName(newName, targetCreature->getSpecies());

		switch (result) {
		case NameManagerResult::ACCEPTED:
			break;
		case NameManagerResult::DECLINED_EMPTY:
			creature->sendSystemMessage("First names may not be empty.");
			return INVALIDPARAMETERS;
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

		PlayerManager* playerManager = zoneServer->getPlayerManager();

		if (playerManager->existsName(newName)) {
			creature->sendSystemMessage("That name is already in use");
			return GENERALERROR;
		}

		String oldFirstName = targetCreature->getFirstName();
		String oldLastName = targetCreature->getLastName();

		String newFullName;
		if (oldLastName.isEmpty()) {
			newFullName = newName;
		} else {
			newFullName = newName + " " + oldLastName;
		}

		targetCreature->setCustomObjectName(newFullName, true);

		ChatManager* chatManager = zoneServer->getChatManager();
		chatManager->removePlayer(oldFirstName);
		chatManager->addPlayer(targetCreature);

		playerManager->removePlayer(oldFirstName);
		playerManager->addPlayer(targetCreature);

		// Remove the old name from other people's friends lists
		PlayerObject* targetGhost = targetCreature->getPlayerObject();
		targetGhost->removeAllReverseFriends(oldFirstName);

		String creatureFirstName = targetCreature->getFirstName();
		Database::escapeString(creatureFirstName);

		int galaxyID = zoneServer->getGalaxyID();

		StringBuffer charDirtyQuery;
		charDirtyQuery
				<< "UPDATE `characters_dirty` SET `firstname` = '"  << creatureFirstName
				<< "' WHERE `character_oid` = '" << targetCreature->getObjectID()
				<< "' AND `galaxy_id` = '" << galaxyID << "'";

		ServerDatabase::instance()->executeStatement(charDirtyQuery);

		StringBuffer charQuery;
		charQuery
				<< "UPDATE `characters` SET `firstname` = '"  << creatureFirstName
				<< "' WHERE `character_oid` = '" << targetCreature->getObjectID()
				<< "' AND `galaxy_id` = '" << galaxyID << "'";

		ServerDatabase::instance()->executeStatement(charQuery);

		creature->sendSystemMessage("First name changed from '" + oldFirstName + "' to '" + newName + "'");

		return SUCCESS;
	}

};

#endif //SETFIRSTNAMECOMMAND_H_
