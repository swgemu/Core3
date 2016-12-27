/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REPAIRSHIPCOMPONENTINSLOTCOMMAND_H_
#define REPAIRSHIPCOMPONENTINSLOTCOMMAND_H_

class RepairShipComponentInSlotCommand : public QueueCommand {
public:

	RepairShipComponentInSlotCommand(const String& name, ZoneProcessServer* server)
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

#endif //REPAIRSHIPCOMPONENTINSLOTCOMMAND_H_
