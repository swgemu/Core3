/*
 * ContrabandScanTask.h
 *
 *  Created on: Nov 3, 2016
 *      Author: vagrant
 */

#ifndef CONTRABANDSCANTASK_H_
#define CONTRABANDSCANTASK_H_
#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

class ContrabandScanTask : public Task {
	ManagedWeakReference<AiAgent*> weakScanner;
	ManagedWeakReference<CreatureObject*> weakPlayer;

public:
	ContrabandScanTask(AiAgent* scanner, CreatureObject* player){
		weakScanner = scanner;
		weakPlayer = player;
	}

	void run() {
		ManagedReference<AiAgent*> scanner = weakScanner.get();
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (scanner == NULL || player == NULL){
			return;
		}

		Locker locker(player);
		Locker crossLocker(scanner, player);

		ManagedReference<Zone* > zone = scanner->getZone();

		if (zone == NULL) {
			return;
		}

		StringIdChatParameter chat;
		chat.setStringId("@imperial_presence/contraband_search:scan_greeting_imperial");
		zone->getZoneServer()->getChatManager()->broadcastChatMessage(scanner, chat, player->getObjectID(), 0, 0);

		StringIdChatParameter systemMessage;
		systemMessage.setStringId("@imperial_presence/contraband_search:contraband_scan_imperial");
		player->sendSystemMessage(systemMessage);
	}
};

#endif /* CONTRABANDSCANTASK_H_ */
