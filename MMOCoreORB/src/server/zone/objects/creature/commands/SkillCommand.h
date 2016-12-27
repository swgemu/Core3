/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SKILLCOMMAND_H_
#define SKILLCOMMAND_H_

class SkillCommand : public QueueCommand {
public:

	SkillCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //SKILLCOMMAND_H_
