/*
 * PrecisionLaserKnifeImplementation.cpp
 *
 *  Created on: Mar 8, 2011
 *      Author: polonel
 */

#include "server/zone/objects/tangible/tool/smuggler/PrecisionLaserKnife.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/Zone.h"

int PrecisionLaserKnifeImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (!isASubChildOf(player))
		return 0;

	if(!player->hasSkill("combat_smuggler_novice")){
		player->sendSystemMessage("You must be at least a Novice Smuggler to use this tool.");
		return 0;
	}

	if (selectedID != 20)
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);

	uint64 targetID = player->getTargetID();
	ZoneServer* zs = player->getZoneServer();
	ManagedReference<TangibleObject*> target = zs->getObject(targetID, true).castTo<TangibleObject*>();

	if (target == NULL || (!target->isSliceable() && !target->isSecurityTerminal())) {
		player->sendSystemMessage("You cannot slice that.");
		return 0;
	}

	if (target->isMissionTerminal()) {
		if (!player->hasSkill("combat_smuggler_slicing_01")) {
			return 0;
		}

		ManagedReference<CityRegion*> city = player->getCityRegion();
		if (city != NULL && !city->isClientRegion() && city->isBanned(player->getObjectID())) {
			player->sendSystemMessage("@city/city:banned_services"); // You are banned from using this city's services.
			return 0;
		}

	} else if (target->isWeaponObject() && !player->hasSkill("combat_smuggler_slicing_02")) {
		return 0;
	} else if (target->isArmorObject() && !player->hasSkill("combat_smuggler_slicing_03")) {
		return 0;
	} else if (target->isSecurityTerminal()) {
		if (!player->hasSkill("combat_smuggler_slicing_01"))
			return 0;

		Zone* zone = target->getZone();
		if(zone == NULL)
			return 0;

		GCWManager* gcwMan = zone->getGCWManager();
		if(gcwMan == NULL)
			return 0;

		if(!gcwMan->canStartSlice(player, target))
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

	if(target->isSecurityTerminal())
		session->setBaseSlice(true);

	session->initalizeSlicingMenu(player, target);

	//useCharge(player);

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
