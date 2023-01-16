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

		if (ship->getComponentObject(Components::BOOSTER) == nullptr) {
			creature->sendSystemMessage("@space_interactions:no_booster");
			return GENERALERROR;
		}

		Locker slock(ship, creature);

		ship->removeComponentFlag(Components::BOOSTER, ShipComponentFlag::DISABLED, true);

		return SUCCESS;
	}

};

#endif //BOOSTEROFF_H_
