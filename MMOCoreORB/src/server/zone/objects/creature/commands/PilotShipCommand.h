/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PILOTSHIP_H_
#define PILOTSHIP_H_

#include "CombatQueueCommand.h"
#include "templates/params/creature/PlayerArrangement.h"

class PilotShipCommand : public CombatQueueCommand {
public:

	PilotShipCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		auto ship = dynamic_cast<ShipObject*>(creature->getRootParent());
		if (ship == nullptr) {
			return GENERALERROR;
		}

		auto station = ship->getPilotChair().get();
		if (station == nullptr) {
			return GENERALERROR;
		}

		auto pilot = station->getSlottedObject("ship_pilot_pob");
		if (pilot != nullptr) {
			return GENERALERROR;
		}

		Locker clock(station, creature);
		creature->destroyObjectFromWorld(false);
		creature->setMovementCounter(0);
		creature->clearSpaceStates();

		creature->initializePosition(station->getPositionX(), station->getPositionZ(), station->getPositionY());
		creature->setDirection(*station->getDirection());

		if (station->transferObject(creature, PlayerArrangement::SHIP_PILOT_POB, true)) {
			creature->setState(CreatureState::PILOTINGPOBSHIP);
			creature->sendToOwner(true);
		}

		return SUCCESS;
	}

};

#endif //PILOTSHIP_H_
