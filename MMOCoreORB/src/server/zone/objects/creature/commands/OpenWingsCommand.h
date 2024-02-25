/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OPENWINGS_H_
#define OPENWINGS_H_

#include "QueueCommand.h"

class OpenWingsCommand : public QueueCommand {
public:

	OpenWingsCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->hasState(CreatureState::PILOTINGSHIP) && !creature->hasState(CreatureState::PILOTINGPOBSHIP)) {
			return INVALIDSTATE;
		}

		SceneObject* rootParent = creature->getRootParent();

		if (rootParent == nullptr || !rootParent->isShipObject())
			return GENERALERROR;

		ManagedReference<ShipObject*> ship = rootParent->asShipObject();

		if (ship == nullptr)
			return GENERALERROR;

		uint32 optionsBitmask = ship->getOptionsBitmask();

		if (optionsBitmask & OptionBitmask::WINGS_OPEN)
			return GENERALERROR;

		Locker lock(ship);

		ship->setOptionsBitmask(OptionBitmask::WINGS_OPEN);

		return SUCCESS;
	}

};

#endif //OPENWINGS_H_
