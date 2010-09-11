/*
 * InformantCreatureImplementation.cpp
 *
 *  Created on: Sep 6, 2010
 *      Author: da
 */

#include "InformantCreature.h"
#include "server/zone/objects/player/PlayerCreature.h"

void InformantCreatureImplementation::sendConversationStartTo(SceneObject* player) {
	if (!player->isPlayerCreature())
		return;

	PlayerCreature* playerCreature = (PlayerCreature*)player;

	if (playerCreature->getObserverCount(ObserverEventType::CONVERSE) <= 0)
		sendDefaultConversationTo(player);
	else
		playerCreature->notifyObservers(ObserverEventType::CONVERSE, _this);
}
