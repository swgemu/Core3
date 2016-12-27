/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTRESOURCEWEIGHTSCOMMAND_H_
#define REQUESTRESOURCEWEIGHTSCOMMAND_H_

class RequestResourceWeightsCommand : public QueueCommand {
public:

	RequestResourceWeightsCommand(const String& name, ZoneProcessServer* server)
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

#endif //REQUESTRESOURCEWEIGHTSCOMMAND_H_
