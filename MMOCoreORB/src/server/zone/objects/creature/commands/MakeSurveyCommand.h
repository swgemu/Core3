/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MAKESURVEYCOMMAND_H_
#define MAKESURVEYCOMMAND_H_

class MakeSurveyCommand : public QueueCommand {
public:

	MakeSurveyCommand(const String& name, ZoneProcessServer* server)
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

#endif //MAKESURVEYCOMMAND_H_

