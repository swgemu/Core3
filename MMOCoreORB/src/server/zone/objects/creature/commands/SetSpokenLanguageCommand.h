/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETSPOKENLANGUAGECOMMAND_H_
#define SETSPOKENLANGUAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetSpokenLanguageCommand : public QueueCommand {
public:

	SetSpokenLanguageCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		Reference<PlayerObject*> ghost = creature->getSlottedObject("ghost").castTo<PlayerObject*>();

		String lang = arguments.toString();

		int langID = Integer::valueOf(lang);

		if (langID > 0 && langID < 12)
			ghost->setLanguageID((uint8)langID, true);

		return SUCCESS;
	}

};

#endif //SETSPOKENLANGUAGECOMMAND_H_
