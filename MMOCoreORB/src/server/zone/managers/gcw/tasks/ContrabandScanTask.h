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
	const unsigned int SCANINITIATECHANCE = 8; // 1/8 chance to initiate scan - 12.5 % chance.
	const unsigned int INITIATEDELAY = 500; // 0.5 s delay.
	const unsigned int PLAYERSCANCOOLDOWN = 30 * 1000; // 30 s cooldown

	ManagedWeakReference<AiAgent*> weakScanner;
	ManagedWeakReference<CreatureObject*> weakPlayer;

	enum ScanState {
		SCANCHANCE,
		INITIATESCAN
	};

	ScanState scanState;

	String getFactionStringId(AiAgent* scanner, String imperial, String rebel) {
		const String stringId = "@imperial_presence/contraband_search:";
		if (scanner->getFaction() == Factions::FACTIONIMPERIAL) {
			return stringId + imperial;
		} else {
			return stringId + rebel;
		}
	}

	bool scanPrerequisitesMet(AiAgent* scanner, CreatureObject* player) {
		return scanner != NULL && player != NULL;
	}

	void scanChance(CreatureObject* player) {
		if (System::random(SCANINITIATECHANCE) >= SCANINITIATECHANCE - 1) {
			this->reschedule(INITIATEDELAY);
			scanState = INITIATESCAN;
			player->updateCooldownTimer("crackdown_scan", PLAYERSCANCOOLDOWN);
		}
	}

	void dismountPlayer(AiAgent* scanner, CreatureObject* player) {
		if (player->isRidingMount()) {
			player->dismount();
			StringIdChatParameter dismoutFaction;
			dismoutFaction.setStringId(getFactionStringId(scanner, "dismount_imperial", "dismount_rebel"));
			player->sendSystemMessage(dismoutFaction);

			StringIdChatParameter dismount;
			dismount.setStringId("@imperial_presence/contraband_search:dismount");
			player->sendSystemMessage(dismount);
		}

	}

	void initiateScan(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		dismountPlayer(scanner, player);
		StringIdChatParameter chat;
		chat.setStringId(getFactionStringId(scanner, "scan_greeting_imperial", "scan_greeting_rebel"));
		zone->getZoneServer()->getChatManager()->broadcastChatMessage(scanner, chat, player->getObjectID(), 0, 0);

		StringIdChatParameter systemMessage;
		systemMessage.setStringId("@imperial_presence/contraband_search:contraband_scan_imperial");
		player->sendSystemMessage(systemMessage);
	}

public:
	ContrabandScanTask(AiAgent* scanner, CreatureObject* player){
		weakScanner = scanner;
		weakPlayer = player;
		scanState = SCANCHANCE;
	}

	void run() {
		ManagedReference<AiAgent*> scanner = weakScanner.get();
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (!scanPrerequisitesMet(scanner, player)){
			return;
		}

		Locker locker(player);
		Locker crossLocker(scanner, player);

		ManagedReference<Zone* > zone = scanner->getZone();

		if (zone == NULL) {
			return;
		}

		switch (scanState) {
		case SCANCHANCE:
			scanChance(player);
			break;
		case INITIATESCAN:
			initiateScan(zone, scanner, player);
			break;
		default:
			break;
		}
	}
};

#endif /* CONTRABANDSCANTASK_H_ */
