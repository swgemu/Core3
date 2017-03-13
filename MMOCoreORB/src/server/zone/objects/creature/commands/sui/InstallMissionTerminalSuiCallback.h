/*
 * InstallMissionTerminalSuiCallback.h
 *
 *  Created on: Apr 25, 2012
 *      Author: TragD
 */

#ifndef INSTALLMISSIONTERMINALCALLBACK_H_
#define INSTALLMISSIONTERMINALCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"

class InstallMissionTerminalSuiCallback : public SuiCallback {
public:
	InstallMissionTerminalSuiCallback(ZoneServer* server)
	: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed)
			return;

		if (args->size() < 1)
			return;

		if (player->getParent() != NULL)
			return;

		ManagedReference<CityRegion*> city = player->getCityRegion().get();
		CityManager* cityManager = player->getZoneServer()->getCityManager();
		if (city == NULL || cityManager == NULL)
			return;

		if (!city->isMayor(player->getObjectID()))
			return;

		if (!cityManager->canSupportMoreMissionTerminals(city)) {
			player->sendSystemMessage("@city/city:no_more_mt"); // Your city can't support any more mission terminals at its current rank!
			return;
		}

		Zone* zone = player->getZone();

		if (zone == NULL)
			return;

		PlayerObject* ghost = player->getPlayerObject();
		if (ghost == NULL)
			return;

		if (!ghost->hasAbility("installmissionterminal"))
			return;

		int option = Integer::valueOf(args->get(0).toString());

		if ((option == 5 || option == 6) && !ghost->hasAbility("place_faction_terminal")) {
			player->sendSystemMessage("@city/city:no_factional"); // You must have Martial Policy IV: Faction to place faction aligned mission terminals.
			return;
		}

		String terminalTemplatePath = "";

		switch (option) {

		case 0: terminalTemplatePath = "object/tangible/terminal/terminal_mission.iff";
		break;

		case 1: terminalTemplatePath = "object/tangible/terminal/terminal_mission_artisan.iff";
		break;

		case 2: terminalTemplatePath = "object/tangible/terminal/terminal_mission_bounty.iff";
		break;

		case 3: terminalTemplatePath = "object/tangible/terminal/terminal_mission_entertainer.iff";
		break;

		case 4: terminalTemplatePath = "object/tangible/terminal/terminal_mission_scout.iff";
		break;

		case 5: terminalTemplatePath = "object/tangible/terminal/terminal_mission_imperial.iff";
		break;

		case 6: terminalTemplatePath = "object/tangible/terminal/terminal_mission_rebel.iff";
		break;
		}

		if (terminalTemplatePath != "") {
			Locker clocker(city, player);

			if(city->getCityTreasury() < 1000){
				StringIdChatParameter msg;
				msg.setStringId("@city/city:action_no_money");
				msg.setDI(1000);
				player->sendSystemMessage(msg); //"The city treasury must have %DI credits in order to perform that action.");
				return;
			}

			StructureObject* cityHall = city->getCityHall();
			if (cityHall == NULL)
				return;

			ManagedReference<SceneObject*> sceneObject = ObjectManager::instance()->createObject(terminalTemplatePath.hashCode(), 1, "sceneobjects");

			city->addMissionTerminal(sceneObject);
			city->subtractFromCityTreasury(1000);

			clocker.release();

			Locker locker(sceneObject);

			sceneObject->initializePosition(player->getWorldPositionX(), player->getWorldPositionZ(),player->getWorldPositionY());
			sceneObject->rotate(player->getDirectionAngle());

			Locker clocker2(cityHall, player);

			cityHall->addChildObject(sceneObject);
			sceneObject->initializeChildObject(cityHall);

			zone->transferObject(sceneObject, -1, true);
		}
	}
};

#endif /* INSTALLMISSIONTERMINALCALLBACK_H_ */
