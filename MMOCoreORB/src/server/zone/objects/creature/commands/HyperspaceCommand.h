/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HYPERSPACE_H_
#define HYPERSPACE_H_

#include "CombatQueueCommand.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/packets/object/OrientForHyperspace.h"
#include "server/zone/objects/ship/events/HyperspaceToLocationTask.h"

class HyperspaceCommand : public CombatQueueCommand {
public:

	HyperspaceCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (arguments.isEmpty())
			return GENERALERROR;

		String destName = arguments.toString();
		ShipManager* shipMan = ShipManager::instance();

		if (shipMan == nullptr)
			return GENERALERROR;

		if (!shipMan->hyperspaceLocationExists(destName)) {
			creature->sendSystemMessage("Invalid hyperspace location " + destName);

			return GENERALERROR;
		}

		const String& zone = shipMan->getHyperspaceZone(destName);
		const Vector3& loc = shipMan->getHyperspaceLocation(destName);

		ManagedReference<ShipObject*> ship = cast<ShipObject*>(creature->getRootParent());

		if (ship == nullptr) {
			creature->error("Attempting hyperspace with no ship object");
			return GENERALERROR;
		}

		StringIdChatParameter param;

		if (ship->isHyperspacing()) {
			param.setStringId("@space/space_interaction:hyperspace_in_progress");
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		if (ship->getShipName().toLowerCase().contains("basic")) {
			param.setStringId("@space/space_interaction:no_hyperdrive");
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		uint32 engineBitmask = ship->getComponentOptionsMap()->get(Components::ENGINE);

		if (engineBitmask & ShipComponentFlag::DISABLED) {
			param.setStringId("@space/space_interaction:no_hyperspace_ship_damaged");
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		int delay = ship->getHyperspaceDelay();

		if (delay > 0) {
			param.setStringId("@space/space_interaction:hyperspace_not_ready");
			param.setDI(delay);
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		Locker lock(ship);
		ship->setHyperspacing(true);

		HyperspaceToLocationTask* task = new HyperspaceToLocationTask(creature, ship, zone, loc);
		task->schedule(500);

		return SUCCESS;
	}
};

#endif //HYPERSPACE_H_
