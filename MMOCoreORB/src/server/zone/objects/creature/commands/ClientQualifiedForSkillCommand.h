/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTQUALIFIEDFORSKILLCOMMAND_H_
#define CLIENTQUALIFIEDFORSKILLCOMMAND_H_

class ClientQualifiedForSkillCommand : public QueueCommand {
public:

	ClientQualifiedForSkillCommand(const String& name, ZoneProcessServer* server)
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

#endif //CLIENTQUALIFIEDFORSKILLCOMMAND_H_
