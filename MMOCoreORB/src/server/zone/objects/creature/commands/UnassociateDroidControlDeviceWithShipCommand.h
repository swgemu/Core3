/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_
#define UNASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_

class UnassociateDroidControlDeviceWithShipCommand : public QueueCommand {
public:

	UnassociateDroidControlDeviceWithShipCommand(const String& name, ZoneProcessServer* server)
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

#endif //UNASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_
