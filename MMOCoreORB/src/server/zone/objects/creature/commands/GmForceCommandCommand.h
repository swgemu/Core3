/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GMFORCECOMMANDCOMMAND_H_
#define GMFORCECOMMANDCOMMAND_H_

class GmForceCommandCommand : public QueueCommand {
public:

	GmForceCommandCommand(const String& name, ZoneProcessServer* server)
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

#endif //GMFORCECOMMANDCOMMAND_H_
