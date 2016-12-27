/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTCHARACTERSHEETINFOCOMMAND_H_
#define REQUESTCHARACTERSHEETINFOCOMMAND_H_

#include "server/zone/packets/player/CharacterSheetResponseMessage.h"

class RequestCharacterSheetInfoCommand : public QueueCommand {
public:

	RequestCharacterSheetInfoCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		BaseMessage* message = new CharacterSheetResponseMessage(creature);
		creature->sendMessage(message);

		return SUCCESS;
	}

};

#endif //REQUESTCHARACTERSHEETINFOCOMMAND_H_
