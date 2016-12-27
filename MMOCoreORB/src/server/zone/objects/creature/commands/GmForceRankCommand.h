/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GMFORCERANKCOMMAND_H_
#define GMFORCERANKCOMMAND_H_

class GmForceRankCommand : public QueueCommand {
public:

	GmForceRankCommand(const String& name, ZoneProcessServer* server)
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

#endif //GMFORCERANKCOMMAND_H_
