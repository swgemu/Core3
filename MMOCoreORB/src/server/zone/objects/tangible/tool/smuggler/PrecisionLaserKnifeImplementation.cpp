/*
 * PrecisionLaserKnifeImplementation.cpp
 *
 *  Created on: Mar 8, 2011
 *      Author: polonel
 */

#include "PrecisionLaserKnife.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

int PrecisionLaserKnifeImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20)
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);

	uint32 targetID = player->getTargetID();
	ZoneServer* zs = player->getZoneServer();
	ManagedReference<TangibleObject*> target = dynamic_cast<TangibleObject*>(zs->getObject(targetID, true));

	if (target == NULL || !target->isSliceable()) {
		player->sendSystemMessage("You cannot slice that.");
		return 0;
	}

	if (target->isSliced()) {
		player->sendSystemMessage("@slicing/slicing:already_sliced");
		return 0;
	}

	if (player->containsActiveSession(SessionFacadeType::SLICING)) {
		player->sendSystemMessage("@slicing/slicing:already_slicing");
		return 0;
	}

	if (!player->checkCooldownRecovery("slicing.terminal")) {
		player->sendSystemMessage("@slicing/slicing:not_again");
		return 0;
	}

	//Create Session
	ManagedReference<SlicingSession*> session = new SlicingSession(player);
	session->initalizeSlicingMenu(player, target);

	useCharge(player);

	return 0;
}

void PrecisionLaserKnifeImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
	SlicingToolImplementation::fillAttributeList(msg, object);

	msg->insertAttribute("charges", charges);

}

void PrecisionLaserKnifeImplementation::updateCharges(int val) {
	charges = val;
	AttributeListMessage* msg = new AttributeListMessage(getObjectID());
	msg->insertAttribute("charges", charges);
	broadcastMessage(msg, false);
}
