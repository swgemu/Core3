/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DOCK_H_
#define DOCK_H_

#include "SpaceQueueCommand.h"
#include "server/zone/objects/ship/events/ShipDockingTask.h"

class DockCommand : public SpaceQueueCommand {
private:
	constexpr static float DOCKING_RANGE = 200.f;

public:
	DockCommand(const String& name, ZoneProcessServer* server)
		: SpaceQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!checkSpaceStates(creature))
			return INVALIDSTATE;

		auto ship = getPlayerShip(creature);

		if (ship == nullptr) {
			return GENERALERROR;
		}

		if (ship->isSorosuubSpaceYacht()) {
			creature->sendSystemMessage("@space/cargo:not_in_suub");
			return GENERALERROR;
		}

		if (ship->getOptionsBitmask() & OptionBitmask::DOCKING) {
			creature->sendSystemMessage("@space/cargo:dock_already");
			return GENERALERROR;
		}

		Locker lock(ship, creature);
		auto targetShip = getShipTarget(ship);

		if (targetShip == nullptr) {
			return GENERALERROR;
		}

		if (targetShip->getOptionsBitmask() & OptionBitmask::DOCKING) {
			creature->sendSystemMessage("@space/cargo:dock_target_already");
			return GENERALERROR;
		}

		if (!isInRange(ship, targetShip, DOCKING_RANGE)) {
			creature->sendSystemMessage("@space/cargo:dock_too_far");
			return GENERALERROR;
		}

		if (!getDockingPermission(ship, targetShip)) {
			creature->sendSystemMessage("@space/cargo:dock_cannot");
			return GENERALERROR;
		}

		Locker tLock(targetShip, creature);
		auto task = new ShipDockingTask(ship, targetShip);

		if (task != nullptr) {
			setDocking(ship, targetShip);
			task->execute();
		}

		return SUCCESS;
	}

private:
	bool getDockingPermission(ShipObject* ship, ShipObject* target) const {
		if (!ShipDockingTask::isShipValid(ship) || !ShipDockingTask::isTargetValid(target)) {
			return false;
		}

		auto pilot = ship->getPilot();

		if (pilot == nullptr || !pilot->isPlayerCreature()) {
			return false;
		}

		auto ghost = pilot->getPlayerObject();

		if (ghost != nullptr && ghost->hasGodMode()) { // for testing
			return true;
		}

		return false; // target->getDockingPermission(ship);
	}

	void setDocking(ShipObject* ship, ShipObject* target) const {
		ship->clearOptionBit(OptionBitmask::WINGS_OPEN, true);
		target->clearOptionBit(OptionBitmask::WINGS_OPEN, true);

		ship->setOptionBit(OptionBitmask::DOCKING, true);
		target->setOptionBit(OptionBitmask::DOCKING, true);
	}
};

#endif //DOCK_H_
