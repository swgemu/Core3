/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SURVEYCOMMAND_H_
#define SURVEYCOMMAND_H_

class SurveyCommand : public QueueCommand {
public:

	SurveyCommand(const String& name, ZoneProcessServer* server)
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

#endif //SURVEYCOMMAND_H_
