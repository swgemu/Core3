/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTSTATMIGRATIONSTOPCOMMAND_H_
#define REQUESTSTATMIGRATIONSTOPCOMMAND_H_

class RequestStatMigrationStopCommand : public QueueCommand {
public:

	RequestStatMigrationStopCommand(const String& name, ZoneProcessServer* server)
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

#endif //REQUESTSTATMIGRATIONSTOPCOMMAND_H_
