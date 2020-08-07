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

		String destName = arguments.toString();
		ShipManager* sman = ShipManager::instance();
		if (!sman->hyperspaceLocationExists(destName)) {
			creature->sendSystemMessage("Invalid hyperspace location " + destName);
		}

		const String& zone = sman->getHyperspaceZone(destName);
		const Vector3& loc = sman->getHyperspaceLocation(destName);
        ManagedReference<ShipObject*> ship = cast<ShipObject*>(creature->getRootParent());
        if (ship == nullptr) {
            creature->error("Attempting hyperspace with no ship object");
        }
        HyperspaceToLocationTask *task = new HyperspaceToLocationTask(creature, ship, zone, loc);
        task->execute();

		return SUCCESS;
	}

};

#endif //HYPERSPACE_H_
