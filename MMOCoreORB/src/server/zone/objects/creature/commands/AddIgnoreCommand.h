/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDIGNORECOMMAND_H_
#define ADDIGNORECOMMAND_H_

#include "server/zone/objects/player/PlayerObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/player/PlayerManager.h"

class AddIgnoreCommand : public QueueCommand {
public:

	AddIgnoreCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		String name = arguments.toString();

		auto ghost = creature->getSlottedObject("ghost").castTo<PlayerObject*>();

		if (ghost->isIgnoring(name)) {
			StringIdChatParameter param("cmnty", "ignore_duplicate");
			param.setTT(name);
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		auto playerManager = server->getPlayerManager();

		bool validName = playerManager->existsName(name);
		validName = validName && (creature->getFirstName().toLowerCase().compareTo(name) != 0);

		if (!validName) {
			StringIdChatParameter param("cmnty", "ignore_not_found");
			param.setTT(name);
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		ghost->addIgnore(name, true);

		return SUCCESS;
	}

};

#endif //ADDIGNORECOMMAND_H_
