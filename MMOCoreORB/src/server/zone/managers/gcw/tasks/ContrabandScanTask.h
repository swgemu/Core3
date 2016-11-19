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
#include "server/zone/managers/collision/CollisionManager.h"

class ContrabandScanTask : public Task {
	const unsigned int SCANINITIATECHANCE = 8; // 1/8 chance to initiate scan - 12.5 % chance.
	const unsigned int TASKDELAY = 1000; // 1 s delay.
	const unsigned int PLAYERSCANCOOLDOWN = 30 * 1000; // 30 s cooldown
	const unsigned int SCANTIME = 5; // 5 iterations = 5 s
	const unsigned int TIMETORETURNFORSCAN = 10; // 10 iterations = 10 s
	const float RANAWAYFACTIONFINE = 100;
	const unsigned int RECOGNIZEDFACTIONRANK = 7;
	const unsigned int BASEFACTIONDETECTIONCHANCE = 10; // 10 percent chance to detect opposite faction.
	const unsigned int RANKDETECTIONCHANCEMODIFIER = 1; // Each faction rank increases the chance to detect opposite faction by this amount.
	const unsigned int JEDIMINDTRICKSUCCESSCHANCEBASE = 80; // 80 percent chance to mind trick.

	ManagedWeakReference<AiAgent*> weakScanner;
	ManagedWeakReference<CreatureObject*> weakPlayer;

	enum ScanState {
		SCANCHANCE,
		INITIATESCAN,
		AVOIDINGSCAN,
		FACTIONRANKCHECK,
		JEDIMINDTRICKPLAYERCHAT,
		JEDIMINDTRICKSCANNERTHINK,
		JEDIMINDTRICKSCANNERCHAT,
		SCANDELAY,
		FINISHED
	};

	ScanState scanState;
	ScanState previousScanState;

	int timeLeft;
	int previousTimeLeft;

	String getFactionStringId(AiAgent* scanner, const String& imperial, const String& rebel) {
		const String stringId = "@imperial_presence/contraband_search:";
		if (scanner->getFaction() == Factions::FACTIONIMPERIAL || rebel == "") {
			return stringId + imperial;
		} else {
			return stringId + rebel;
		}
	}

	void sendScannerChatMessage(Zone* zone, AiAgent* scanner, CreatureObject* player, const String& imperial, const String& rebel = "") {
		StringIdChatParameter chatMessage;
		chatMessage.setStringId(getFactionStringId(scanner, imperial, rebel));
		zone->getZoneServer()->getChatManager()->broadcastChatMessage(scanner, chatMessage, player->getObjectID(), 0, 0);
	}

	void sendSystemMessage(AiAgent* scanner, CreatureObject* player, const String& imperial, const String& rebel = "") {
		StringIdChatParameter systemMessage;
		systemMessage.setStringId(getFactionStringId(scanner, imperial, rebel));
		player->sendSystemMessage(systemMessage);
	}

	bool scanPrerequisitesMet(AiAgent* scanner, CreatureObject* player) {
		return scanner != NULL && player != NULL && !scanner->isDead() && !player->isDead() && !player->isFeigningDeath()
				&& !player->isIncapacitated() && !scanner->isInCombat() && !player->isInCombat();
	}

	bool playerTriesToAvoidScan(AiAgent* scanner, CreatureObject* player) {
		return scanState != AVOIDINGSCAN && (!scanner->isInRange(player, 16) || !CollisionManager::checkLineOfSight(scanner, player));
	}

	void scannerRequestsPlayerToReturn(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		previousScanState = scanState;
		scanState = AVOIDINGSCAN;
		previousTimeLeft = timeLeft;
		timeLeft = TIMETORETURNFORSCAN;

		sendScannerChatMessage(zone, scanner, player, "return_request_imperial", "return_request_rebel");
	}

	void checkIfPlayerHasReturned(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		if (scanner->isInRange(player, 16) && CollisionManager::checkLineOfSight(scanner, player)) {
			scanState = previousScanState;
			timeLeft = previousTimeLeft;

			sendScannerChatMessage(zone, scanner, player, "return_thank_imperial", "return_thank_rebel");
		} else if (timeLeft < 0) {
			sendScannerChatMessage(zone, scanner, player, "return_false_imperial", "return_false_rebel");
			sendSystemMessage(scanner, player, "ran_away_imperial", "ran_away_rebel");
			player->getPlayerObject()->decreaseFactionStanding(scanner->getFactionString(), RANAWAYFACTIONFINE);

			scanState = FINISHED;
		}
	}

	void performScan(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		if (timeLeft < 0) {
			sendScannerChatMessage(zone, scanner, player, "clean_target_imperial", "clean_target_rebel");
			sendSystemMessage(scanner, player, "probe_scan_done");

			scanState = FINISHED;
		}
	}

	void checkIfPlayerShouldBeScanned(CreatureObject* player) {
		if (System::random(SCANINITIATECHANCE) >= SCANINITIATECHANCE - 1) { // 1 in SCANINITIATECHANCE chance to initiate the scan.
			scanState = INITIATESCAN;
			player->updateCooldownTimer("crackdown_scan", PLAYERSCANCOOLDOWN);
		} else {
			scanState = FINISHED;
		}
	}

	void initiateScan(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		sendSystemMessage(scanner, player, "dismount_imperial", "dismount_rebel");

		if (player->isRidingMount()) {
			player->dismount();
			sendSystemMessage(scanner, player, "dismount");
		}

		sendScannerChatMessage(zone, scanner, player, "scan_greeting_imperial", "scan_greeting_rebel");

		scanState = FACTIONRANKCHECK;
		timeLeft = SCANTIME;
	}

	void checkPlayerFactionRank(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		scanState = JEDIMINDTRICKPLAYERCHAT;
		if (scanner->getFaction() == player->getFaction()) {
			if (player->getFactionRank() > RECOGNIZEDFACTIONRANK) {
				sendScannerChatMessage(zone, scanner, player, "business_imperial", "business_rebel");
				sendSystemMessage(scanner, player, "probe_scan_done");
				scanState = FINISHED;
			}
		} else if (player->getFaction() != Factions::FACTIONNEUTRAL) {
			unsigned int detectionChance = BASEFACTIONDETECTIONCHANCE + RANKDETECTIONCHANCEMODIFIER * player->getFactionRank();
			if (System::random(100) < detectionChance) {
				sendScannerChatMessage(zone, scanner, player, "discovered_chat_imperial", "discovered_chat_rebel");
				sendSystemMessage(scanner, player, "discovered_imperial", "discovered_rebel");
				player->setFactionStatus(FactionStatus::COVERT);
				scanState = FINISHED;
			}
		}
	}

	String dependingOnJediSkills(CreatureObject* player, const String& novice, const String& lightSide, const String& darkSide) {
		if (player->hasSkill("force_title_jedi_rank_03")) {
			if (player->hasSkill("force_rank_light_novice")) {
				return lightSide;
			} else if (player->hasSkill("force_rank_dark_novice")) {
				return darkSide;
			} else {
				return novice;
			}
		} else {
			return novice;
		}
	}

	void performJediMindTrick(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		if (player->hasSkill("force_title_jedi_rank_02")) { // Jedi Padawan
			ChatManager* chatManager = zone->getZoneServer()->getChatManager();
			String stringId = "@imperial_presence/contraband_search:";
			String mood = dependingOnJediSkills(player, "firm", "confident", "angry");

			stringId += dependingOnJediSkills(player, "jedi_mind_trick_novice", "jedi_mind_trick", "jedi_mind_trick_dark");

			StringIdChatParameter chatMessage;
			chatMessage.setStringId(stringId);
			chatManager->broadcastChatMessage(player, chatMessage, scanner->getObjectID(), 0, chatManager->getMoodType(mood));

			scanState = JEDIMINDTRICKSCANNERTHINK;
		} else {
			scanState = SCANDELAY;
		}
	}

	void reactOnJediMindTrick(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		ChatManager* chatManager = zone->getZoneServer()->getChatManager();
		String stringId = "@imperial_presence/contraband_search:";

		stringId += dependingOnJediSkills(player, "not_search_you_novice", "not_search_you", "not_search_you_dark");

		StringIdChatParameter chatMessage;
		chatMessage.setStringId(stringId);
		chatManager->broadcastChatMessage(scanner, chatMessage, 0, chatManager->getSpatialChatType("think"), chatManager->getMoodType("ambivalent"));

		scanState = JEDIMINDTRICKSCANNERCHAT;
	}

	unsigned int jediMindTrickSuccessChance(CreatureObject* player) {
		unsigned int successChance = JEDIMINDTRICKSUCCESSCHANCEBASE;
		if (player->hasSkill("force_discipline_powers_master")) {
			successChance = 100;
		} else if (player->hasSkill("force_title_jedi_master")) {
			successChance += 15;
		} else if (player->hasSkill("force_title_jedi_rank_04")) {
			successChance += 10;
		} else if (player->hasSkill("force_title_jedi_rank_03")) {
			successChance += 5;
		}
		return successChance;
	}

	void jediMindTrickResult(Zone* zone, AiAgent* scanner, CreatureObject* player) {
		ChatManager* chatManager = zone->getZoneServer()->getChatManager();
		String stringId = "@imperial_presence/contraband_search:";
		String mood;

		if (System::random(100) > jediMindTrickSuccessChance(player)) {
			stringId += "jedi_fail";
			mood = "suspicious";
			scanState = SCANDELAY;
		} else {
			stringId += dependingOnJediSkills(player, "dont_search_you_novice", "dont_search_you", "dont_search_you_dark");
			mood = dependingOnJediSkills(player, "confused", "confident", "scared");
			sendSystemMessage(scanner, player, "probe_scan_done");
			scanState = FINISHED;
		}

		StringIdChatParameter chatMessage;
		chatMessage.setStringId(stringId);
		chatManager->broadcastChatMessage(scanner, chatMessage, player->getObjectID(), 0, chatManager->getMoodType(mood));
	}

public:
	ContrabandScanTask(AiAgent* scanner, CreatureObject* player){
		weakScanner = scanner;
		weakPlayer = player;
		previousScanState = SCANCHANCE;
		scanState = SCANCHANCE;
		previousTimeLeft = 0;
		timeLeft = 0;
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

		if (playerTriesToAvoidScan(scanner, player)) {
			scannerRequestsPlayerToReturn(zone, scanner, player);
		}

		timeLeft--;

		switch (scanState) {
		case SCANCHANCE:
			checkIfPlayerShouldBeScanned(player);
			break;
		case INITIATESCAN:
			initiateScan(zone, scanner, player);
			break;
		case FACTIONRANKCHECK:
			checkPlayerFactionRank(zone, scanner, player);
			break;
		case JEDIMINDTRICKPLAYERCHAT:
			performJediMindTrick(zone, scanner, player);
			break;
		case JEDIMINDTRICKSCANNERTHINK:
			reactOnJediMindTrick(zone, scanner, player);
			break;
		case JEDIMINDTRICKSCANNERCHAT:
			jediMindTrickResult(zone, scanner, player);
			break;
		case SCANDELAY:
			performScan(zone, scanner, player);
			break;
		case AVOIDINGSCAN:
			checkIfPlayerHasReturned(zone, scanner, player);
			break;
		default:
			break;
		}

		if (scanState != FINISHED) {
			this->reschedule(TASKDELAY);
		}
	}
};

#endif /* CONTRABANDSCANTASK_H_ */
