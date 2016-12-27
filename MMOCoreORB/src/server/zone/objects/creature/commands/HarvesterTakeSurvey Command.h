/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERTAKESURVEYCOMMAND_H_
#define HARVESTERTAKESURVEYCOMMAND_H_

class HarvesterTakeSurveyCommand : public QueueCommand {
public:

	HarvesterTakeSurveyCommand(const String& name, ZoneProcessServer* server)
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

#endif //HARVESTERTAKESURVEY COMMAND_H_

