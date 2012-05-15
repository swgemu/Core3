/*
 * GamblingRouletteSuiCallback.h
 *
 *  Created on: 04/29, 2012
 *      Author: Elvaron
 */

#ifndef GAMBLINGROULETTESUICALLBACK_H_
#define GAMBLINGROULETTESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/minigames/GamblingManager.h"

class GamblingRouletteSuiCallback : public SuiCallback {
public:
	GamblingRouletteSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || player == NULL)
			return;

		GamblingManager* manager = player->getZoneProcessServer()->getGamblingManager();

		Locker locker(manager);

		if (cancelPressed)
			manager->leaveTerminal(player, 0);
		else
			manager->refreshRouletteMenu(player);
	}
};

#endif /* GAMBLINGROULETTESUICALLBACK_H_ */
