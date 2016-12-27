/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHOWFACTIONINFORMATIONCOMMAND_H_
#define SHOWFACTIONINFORMATIONCOMMAND_H_

class ShowFactionInformationCommand : public QueueCommand {
public:

	ShowFactionInformationCommand(const String& name, ZoneProcessServer* server)
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

#endif //SHOWFACTIONINFORMATIONCOMMAND_H_
