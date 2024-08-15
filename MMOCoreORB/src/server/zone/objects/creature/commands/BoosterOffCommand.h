/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BOOSTEROFF_H_
#define BOOSTEROFF_H_

#include "QueueCommand.h"

class BoosterOffCommand : public QueueCommand {
public:

	BoosterOffCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		SceneObject* rootParent = creature->getRootParent();

		if (rootParent == nullptr || !rootParent->isShipObject())
			return GENERALERROR;

		ManagedReference<ShipObject*> ship = rootParent->asShipObject();

		if (ship == nullptr || !ship->isBoosterActive())
			return GENERALERROR;

		ManagedReference<CreatureObject*> pilot = ship->getPilot();

		if (pilot == nullptr || pilot != creature) {
			creature->sendSystemMessage("@space/space_interaction:booster_pilot_only");
			return GENERALERROR;
		}

		if (!ship->isComponentInstalled(Components::BOOSTER)) {
			creature->sendSystemMessage("@space/space_interaction:no_booster");
			return GENERALERROR;
		}

		if (!ship->isComponentFunctional(Components::BOOSTER)) {
			creature->sendSystemMessage("@space/space_interaction:booster_disabled");
			return GENERALERROR;
		}

		Locker slock(ship, creature);

		ship->removeComponentFlag(Components::BOOSTER, ShipComponentFlag::ACTIVE, true);
		ship->restartBooster();

		return SUCCESS;
	}

};

#endif //BOOSTEROFF_H_
