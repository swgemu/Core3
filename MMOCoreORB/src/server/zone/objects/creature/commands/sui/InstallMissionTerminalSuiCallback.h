/*
 * InstallMissionTerminalSuiCallback.h
 *
 *  Created on: Apr 25, 2012
 *      Author: TragD
 */

#ifndef INSTALLMISSIONTERMINALCALLBACK_H_
#define INSTALLMISSIONTERMINALCALLBACK_H_


#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"

class InstallMissionTerminalSuiCallback : public SuiCallback {
public:
	InstallMissionTerminalSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed)
			return;

		if (args->size() < 1)
			return;

		if (player->getParent() != NULL)
					return;

		ManagedReference<CityRegion*> city = player->getCityRegion();

		if (city->getMissionTerminalCount() >= (int) city->getCityRank() * 3){
					player->sendSystemMessage("@city/city:no_more_mt");
					return;
		}

		Zone* zone = player->getZone();

		PlayerObject* ghost = player->getPlayerObject();

		int option = Integer::valueOf(args->get(0).toString());

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
		}

		if (terminalTemplatePath != ""){

			ManagedReference<SceneObject*> sceneObject = ObjectManager::instance()->createObject(terminalTemplatePath.hashCode(), 1, "sceneobjects");

			sceneObject->initializePosition(player->getWorldPositionX(), player->getWorldPositionZ(),player->getWorldPositionY());
			sceneObject->rotate(player->getDirectionAngle());
			zone->transferObject(sceneObject, -1, true);
			city->addMissionTerminal(sceneObject);
			city->subtractFromCityTreasury(1000);

		}

	}
};

#endif /* INSTALLMISSIONTERMINALCALLBACK_H_ */
