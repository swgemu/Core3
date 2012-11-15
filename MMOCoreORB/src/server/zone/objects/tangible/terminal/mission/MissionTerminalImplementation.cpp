/*
 * MissionTerminalImplementation.cpp
 *
 *  Created on: 03/05/11
 *      Author: polonel
 */

#include "MissionTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/region/CityRegion.h"

#include "server/zone/objects/player/sessions/SlicingSession.h"

void MissionTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {

	ManagedReference<CityRegion*> city = player->getCityRegion();

	if(city != NULL && city->isMayor(player->getObjectID())){

		menuResponse->addRadialMenuItem(72, 3, "Remove");

	}
}

int MissionTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 69 && player->hasSkill("combat_smuggler_slicing_01")) {

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
		session->initalizeSlicingMenu(player, _this.get());

		return 0;

	}

	if (selectedID == 72) {

		ManagedReference<CityRegion*> city = player->getCityRegion();

		if (city != NULL)
			city->removeMissionTerminal(_this.get());

		destroyObjectFromWorld(true);
		destroyObjectFromDatabase(false);

		return 0;
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

String MissionTerminalImplementation::getTerminalName() {
	String name = "@terminal_name:terminal_mission";

	if (terminalType == "artisan" || terminalType == "entertainer" || terminalType == "bounty" || terminalType == "imperial" || terminalType == "rebel" || terminalType == "scout")
		name = name + "_" + terminalType;

	return name;
}
