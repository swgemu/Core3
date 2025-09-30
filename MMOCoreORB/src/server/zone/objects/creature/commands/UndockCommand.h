/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNDOCK_H_
#define UNDOCK_H_

#include "SpaceQueueCommand.h"

class UndockCommand : public SpaceQueueCommand {
public:

	UndockCommand(const String& name, ZoneProcessServer* server)
		: SpaceQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		auto ship = getPlayerShip(creature);

		if (ship == nullptr || !(ship->getOptionsBitmask() & OptionBitmask::DOCKING)) {
			return GENERALERROR;
		}

		Locker sLock(ship, creature);
		ship->sendShipMembersMessage("@space/cargo:dock_abort");
		ship->clearOptionBit(OptionBitmask::DOCKING, true);

		return SUCCESS;
	}

};

#endif //UNDOCK_H_
