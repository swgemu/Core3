/*
 * MissionManagerImplementation.cpp
 *
 *  Created on: 21/06/2010
 *      Author: victor
 */

#include "MissionManager.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/mission/MissionObject.h"

void MissionManagerImplementation::handleMissionListRequest(MissionTerminal* missionTerminal, PlayerCreature* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");

	while (missionBag->getContainerObjectsSize() < 6) {
		SceneObject* mission = server->createObject(3741732474UL, 0); // empty mission
		missionBag->addObject(mission, -1, true);
		mission->sendTo(player, true);
	}

	if (missionTerminal->isGeneralTerminal()) {
		populateGeneralMissionList(missionTerminal, player, counter);
	} else if (missionTerminal->isArtisanTerminal()) {
		populateArtisanMissionList(missionTerminal, player, counter);
	}
}

void MissionManagerImplementation::populateGeneralMissionList(MissionTerminal* missionTerminal, PlayerCreature* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");

	for (int i = 0; i < missionBag->getContainerObjectsSize(); ++i) {
		MissionObject* mission = (MissionObject*) missionBag->getContainerObject(i);
		mission->setTypeCRC(0x74EF9BE3, true);
		mission->setRefreshCounter(counter, true);
	}
}

void MissionManagerImplementation::populateArtisanMissionList(MissionTerminal* missionTerminal, PlayerCreature* player, int counter) {
	SceneObject* missionBag = player->getSlottedObject("mission_bag");

	for (int i = 0; i < missionBag->getContainerObjectsSize(); ++i) {
		MissionObject* mission = (MissionObject*) missionBag->getContainerObject(i);
		mission->setTypeCRC(0x19C9FAC1, true);
		mission->setRefreshCounter(counter, true);
	}
}
