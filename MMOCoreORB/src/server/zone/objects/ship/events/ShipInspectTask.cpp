/*
 *	Copyright <SWGEmu>
 *	See file COPYING for copying conditions.
 *
 *	ShipInspectTask.cpp
 *
 *	Created on: 2025-10-14
 *	Author: Hakry
 */

#include "ShipInspectTask.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

void ShipInspectTask::run() {
	auto player = weakPlayer.get();
	auto targetShip = weakTargetShip.get();

	if (player == nullptr || targetShip == nullptr) {
		return;
	}

	Locker lock(player);

	// Make sure player is either the pilot or in operations
	if (!player->isPilotingShip() && !player->isPobShipOperator()) {
		return;
	}

	auto playerRoot = player->getRootParent();

	if (playerRoot == nullptr || !playerRoot->isShipObject()) {
		return;
	}

	auto playerShip = playerRoot->asShipObject();

	if (playerShip == nullptr) {
		return;
	}

	Locker cLock(targetShip, player);

	auto shipPosition = playerShip->getWorldPosition();

	// Play the effect
	playerShip->sendMembersBaseMessage(new PlayClientEffectLoc("clienteffect/ship_inspect_end.cef", "", shipPosition.getX(), shipPosition.getZ(), shipPosition.getY()), true);

	auto group = player->getGroup();
	const auto cargoString = playerShip->getCargoString();

	// Ship does not have any cargo
	if (cargoString.isEmpty()) {
		player->sendSystemMessage("@space/cargo:nothing");

		if (group != nullptr) {
			StringIdChatParameter noCargoGroup("space/cargo", "report_cargo_group"); // Nothing.

			group->sendSystemMessage(noCargoGroup, player);
		}
	// Ship has cargo
	} else {
		StringIdChatParameter foundCargo("space/cargo", "report_cargo"); // "\\#pconstrast3 Inspection Results: Target Contains [ \\#pconstrast1 %TO \\#pcontrast3 ]"
		foundCargo.setTO(cargoString);

		player->sendSystemMessage(foundCargo);

		if (group != nullptr) {
			StringIdChatParameter foundCargoGroup("space/cargo", "report_cargo_group"); // "\\#pconstrast3 %TO's Inspection Results: Target Contains [ \\#pconstrast1 %TT \\#pcontrast3 ]"
			foundCargoGroup.setTO(cargoString);

			group->sendSystemMessage(foundCargoGroup, player);
		}

		// Notify observer for missions
		player->notifyObservers(ObserverEventType::INSPECTEDSHIP, targetShip, cargoString.hashCode());
	}
}