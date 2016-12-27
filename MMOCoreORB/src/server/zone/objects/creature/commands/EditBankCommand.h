/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EDITBANKCOMMAND_H_
#define EDITBANKCOMMAND_H_

class EditBankCommand : public QueueCommand {
public:

	EditBankCommand(const String& name, ZoneProcessServer* server)
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

#endif //EDITBANKCOMMAND_H_
