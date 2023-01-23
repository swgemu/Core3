/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BOOSTERON_H_
#define BOOSTERON_H_

#include "QueueCommand.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"

class BoosterOnCommand : public QueueCommand {
public:

	BoosterOnCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPilotingShip()) {
			return INVALIDSTATE;
		}

		SceneObject* rootParent = creature->getRootParent();

		if (rootParent == nullptr || !rootParent->isShipObject())
			return GENERALERROR;

		ManagedReference<ShipObject*> ship = rootParent->asShipObject();

		if (ship == nullptr)
			return GENERALERROR;

		StringIdChatParameter param;

		if (ship->getComponentObject(Components::BOOSTER) == nullptr) {
			param.setStringId("@space/space_interaction:no_booster");
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		if (ship->getBoosterEnergy() < ship->getBoosterRechargeRate()) {
			param.setStringId("@space/space_interaction:booster_low_energy");
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		if (!ship->isReadyToBoost()) {
			param.setStringId("@space/space_interaction:booster_not_ready");
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		Locker slock(ship, creature);

		ship->addComponentFlag(Components::BOOSTER, ShipComponentFlag::ACTIVE, true);
		ship->restartBooster();

		return SUCCESS;
	}

};

#endif //BOOSTERON_H_
