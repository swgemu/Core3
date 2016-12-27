/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REMOVEIGNORECOMMAND_H_
#define REMOVEIGNORECOMMAND_H_

class RemoveIgnoreCommand : public QueueCommand {
public:

	RemoveIgnoreCommand(const String& name, ZoneProcessServer* server)
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
		ghost->removeIgnore(arguments.toString());

		return SUCCESS;
	}

};

#endif //REMOVEIGNORECOMMAND_H_
