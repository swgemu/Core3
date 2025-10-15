/*
 *	Copyright <SWGEmu>
 *	See file COPYING for copying conditions.
 *
 *	InspectCommand.h
 *
 *	Created on: 2025-10-14
 *	Author: Hakry
 *
*/

#ifndef INSPECT_H_
#define INSPECT_H_

#include "SpaceQueueCommand.h"
#include "server/zone/objects/ship/events/ShipInspectTask.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

class InspectCommand : public SpaceQueueCommand {
	constexpr static float INSPECT_RANGE = 150.f;
	constexpr static uint32 INSPECT_COOLDOWN = 5000;

public:
	InspectCommand(const String& name, ZoneProcessServer* server) : SpaceQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature)) {
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			return INVALIDLOCOMOTION;
		}

		if (!checkSpaceStates(creature)) {
			return INVALIDSTATE;
		}

		auto ship = getPlayerShip(creature);

		if (ship == nullptr) {
			return GENERALERROR;
		}

		if (ship->isSorosuubSpaceYacht()) {
			creature->sendSystemMessage("@space/cargo:not_in_suub");
			return GENERALERROR;
		}

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> targetSceneO = zoneServer->getObject(target);

		if (targetSceneO == nullptr || !targetSceneO->isShipObject() || targetSceneO->getObjectID() == ship->getObjectID()) {
			return INVALIDTARGET;
		}

		auto targetShip = targetSceneO->asShipObject();

		if (targetShip == nullptr) {
			return INVALIDTARGET;
		}

		Locker cLock(targetShip, creature);

		// Check target ship is in range
		if (!targetShip->isInRange3d(ship, INSPECT_RANGE)) {
			creature->sendSystemMessage("@space/cargo:inspect_too_far");
			return TOOFAR;
		}

		// Make sure player is not already inspecting another ship
		if (!creature->checkCooldownRecovery("inspect_ship")) {
			creature->sendSystemMessage("@space/cargo:inspect_already");
			return GENERALERROR;
		}

		// Update the inspect cooldown
		creature->updateCooldownTimer("inspect_ship", INSPECT_COOLDOWN);

		auto inspectTask = new ShipInspectTask(creature, targetShip);

		if (inspectTask == nullptr) {
			return GENERALERROR;
		}

		// Schedule the task
		inspectTask->schedule(INSPECT_COOLDOWN);

		auto shipPosition = ship->getWorldPosition();

		// Play the effect
		ship->sendMembersBaseMessage(new PlayClientEffectLoc("clienteffect/ship_inspect_begin.cef", "", shipPosition.getX(), shipPosition.getZ(), shipPosition.getY()), true);

		// Send player system message
		ship->sendShipMembersMessage("@space/cargo:inspecting");

		return SUCCESS;
	}
};

#endif // INSPECT_H_
