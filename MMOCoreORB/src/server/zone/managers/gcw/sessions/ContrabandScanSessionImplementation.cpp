/*
 * ContrabandScanSessionImplementation.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: loshult
 */

#include "server/zone/managers/gcw/sessions/ContrabandScanSession.h"
#include "server/zone/managers/gcw/tasks/ContrabandScanTask.h"
#include "server/zone/managers/gcw/tasks/LambdaShuttleWithReinforcementsTask.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/tangible/consumable/Consumable.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/managers/gcw/sessions/sui/ContrabandFineSuiCallback.h"
#include "server/zone/objects/player/FactionStatus.h"

int ContrabandScanSessionImplementation::initializeSession() {
	ManagedReference<AiAgent*> scanner = weakScanner.get();
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	if (!scanPrerequisitesMet(scanner, player)) {
		return false;
	}

	checkIfPlayerIsSmuggler(player);

	if (contrabandScanTask == NULL) {
		contrabandScanTask = new ContrabandScanTask(player);
	}
	if (!contrabandScanTask->isScheduled()) {
		contrabandScanTask->schedule(TASKDELAY);
	}

	scanner->updateCooldownTimer("crackdown_scan", CONTRABANDSCANCOOLDOWN);
	player->updateCooldownTimer("crackdown_scan", CONTRABANDSCANCOOLDOWN);

	if (player->getActiveSession(SessionFacadeType::CONTRABANDSCAN) != NULL) {
		player->dropActiveSession(SessionFacadeType::CONTRABANDSCAN);
	}
	player->addActiveSession(SessionFacadeType::CONTRABANDSCAN, _this.getReferenceUnsafeStaticCast());

	return true;
}

int ContrabandScanSessionImplementation::cancelSession() {
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	if(player != NULL) {
		player->dropActiveSession(SessionFacadeType::CONTRABANDSCAN);
	}

	if (contrabandScanTask != NULL) {
		contrabandScanTask->cancel();
	}

	return clearSession();
}

int ContrabandScanSessionImplementation::clearSession() {
	return 0;
}

void ContrabandScanSessionImplementation::runContrabandScan() {
	ManagedReference<AiAgent*> scanner = weakScanner.get();
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	if (!scanPrerequisitesMet(scanner, player)){
		cancelSession();
	}

	Locker locker(player);
	Locker crossLocker(scanner, player);

	ManagedReference<Zone* > zone = scanner->getZone();

	if (zone == NULL) {
		cancelSession();
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
	case WAITFORPAYFINEANSWER:
		waitForPayFineAnswer(zone, scanner, player);
		break;
	case AVOIDINGSCAN:
		checkIfPlayerHasReturned(zone, scanner, player);
		break;
	default:
		break;
	}

	if (scanState != FINISHED) {
		contrabandScanTask->reschedule(TASKDELAY);
	} else {
		cancelSession();
	}
}

String ContrabandScanSessionImplementation::getFactionStringId(AiAgent* scanner, const String& imperial, const String& rebel) {
	const String stringId = "@imperial_presence/contraband_search:";
	if (scanner->getFaction() == Factions::FACTIONIMPERIAL || rebel == "") {
		return stringId + imperial;
	} else {
		return stringId + rebel;
	}
}

void ContrabandScanSessionImplementation::sendScannerChatMessage(Zone* zone, AiAgent* scanner, CreatureObject* player, const String& imperial, const String& rebel = "") {
	StringIdChatParameter chatMessage;
	chatMessage.setStringId(getFactionStringId(scanner, imperial, rebel));
	zone->getZoneServer()->getChatManager()->broadcastChatMessage(scanner, chatMessage, player->getObjectID(), 0, 0);
}

void ContrabandScanSessionImplementation::sendSystemMessage(AiAgent* scanner, CreatureObject* player, const String& imperial, const String& rebel = "") {
	StringIdChatParameter systemMessage;
	systemMessage.setStringId(getFactionStringId(scanner, imperial, rebel));
	player->sendSystemMessage(systemMessage);
}

bool ContrabandScanSessionImplementation::scanPrerequisitesMet(AiAgent* scanner, CreatureObject* player) {
	return scanner != NULL && player != NULL && player->isPlayerCreature() && !scanner->isDead() && !player->isDead()
			&& !player->isFeigningDeath() && !player->isIncapacitated() && !scanner->isInCombat() && !player->isInCombat();
}

bool ContrabandScanSessionImplementation::playerTriesToAvoidScan(AiAgent* scanner, CreatureObject* player) {
	return (scanState != AVOIDINGSCAN && scanState != SCANCHANCE && scanState != INITIATESCAN) && (!scanner->isInRange(player, 16) || !CollisionManager::checkLineOfSight(scanner, player));
}

void ContrabandScanSessionImplementation::scannerRequestsPlayerToReturn(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	previousScanState = scanState;
	scanState = AVOIDINGSCAN;
	if (!alreadyTriedToAvoidScan) {
		previousTimeLeft = timeLeft;
		timeLeft = TIMETORETURNFORSCAN;
		alreadyTriedToAvoidScan = true;
	} else {
		previousTimeLeft = timeLeft;
		timeLeft = 0;
	}

	sendScannerChatMessage(zone, scanner, player, "return_request_imperial", "return_request_rebel");
	scanner->doAnimation("hail");
}

void ContrabandScanSessionImplementation::checkIfPlayerHasReturned(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	if (scanner->isInRange(player, 16) && CollisionManager::checkLineOfSight(scanner, player)) {
		scanState = previousScanState;
		timeLeft = previousTimeLeft;

		sendScannerChatMessage(zone, scanner, player, "return_thank_imperial", "return_thank_rebel");
		scanner->doAnimation("nod_head_once");
	} else if (timeLeft < 0) {
		sendScannerChatMessage(zone, scanner, player, "return_false_imperial", "return_false_rebel");
		sendSystemMessage(scanner, player, "ran_away_imperial", "ran_away_rebel");
		player->getPlayerObject()->decreaseFactionStanding(scanner->getFactionString(), RANAWAYFACTIONFINE);

		scanState = FINISHED;
	}
}

bool ContrabandScanSessionImplementation::isContraband(SceneObject* item) {
	if (item->isTangibleObject()) {
		ManagedReference<TangibleObject*> tangibleItem = item->asTangibleObject();
		if (tangibleItem->isSliced()) {
			return true;
		} else if (tangibleItem->isConsumable()) {
			ManagedReference<Consumable*> consumable = tangibleItem.castTo<Consumable*>();
			if (consumable->isSpice()) {
				return true;
			}
		} else if (tangibleItem->isFactoryCrate()) {
			ManagedReference<FactoryCrate*> crate = tangibleItem.castTo<FactoryCrate*>();
			ManagedReference<TangibleObject*> prototype = crate->getPrototype();
			return isContraband(prototype.castTo<SceneObject*>());
		}
	}
	return false;
}

int ContrabandScanSessionImplementation::countContrabandItemsInContainer(SceneObject* container) {
	int numberOfContrabandItems = 0;
	int containerSize = container->getContainerObjectsSize();
	if (containerSize > 1) {
		for (int i = 0; i < containerSize; i++) {
			numberOfContrabandItems += countContrabandItemsInContainer(container->getContainerObject(i));
		}
	}
	if (isContraband(container)) {
		numberOfContrabandItems++;
	}
	return numberOfContrabandItems;
}

int ContrabandScanSessionImplementation::countContrabandItems(CreatureObject* player) {
	VectorMap<String, ManagedReference<SceneObject*>> slots;
	player->getSlottedObjects(slots);

	int numberOfSlots = slots.size();
	int numberOfContrabandItems = 0;

	for (int i = 0; i < numberOfSlots; i++) {
		VectorMapEntry<String, ManagedReference<SceneObject*>> container = slots.elementAt(i);
		if (container.getKey() != "bank" && container.getKey() != "datapad") {
			numberOfContrabandItems += countContrabandItemsInContainer(container.getValue());
		}
	}

	return numberOfContrabandItems;
}

void ContrabandScanSessionImplementation::sendContrabandFineSuiWindow(Zone* zone, AiAgent* scanner, CreatureObject* player, int numberOfContrabandItems) {
	fineToPay = numberOfContrabandItems * CONTRABANDFINEPERITEM;

	removeFineSuiWindow(player);

	ManagedReference<SuiMessageBox*> suiContrabandFine = new SuiMessageBox(player, SuiWindowType::CONTRABAND_SCAN_FINE);

	suiContrabandFine->setPromptTitle("@imperial_presence/contraband_search:imp_fine_title");
	String text = "@imperial_presence/contraband_search:imp_fine_text " +  String::valueOf(fineToPay);
	if (scanner->getFaction() == Factions::FACTIONIMPERIAL) {
		text += " @imperial_presence/contraband_search:imp_fine_text2_imperial";
	} else {
		text += " @imperial_presence/contraband_search:imp_fine_text2_rebel";
	}
	suiContrabandFine->setPromptText(text);

	suiContrabandFine->setCancelButton(true, "@ui:no");
	suiContrabandFine->setOkButton(true, "@ui:yes");

	suiContrabandFine->setCallback(new ContrabandFineSuiCallback(zone->getZoneServer()));

	player->getPlayerObject()->addSuiBox(suiContrabandFine);
	player->sendMessage(suiContrabandFine->generateMessage());
}

void ContrabandScanSessionImplementation::performScan(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	if (timeLeft < 0) {
		int numberOfContrabandItems = countContrabandItems(player);
		if (numberOfContrabandItems > 0 && !smugglerAvoidedScan) {
			sendScannerChatMessage(zone, scanner, player, "fined_imperial", "fined_rebel");
			sendSystemMessage(scanner, player, "probe_scan_positive");
			scanner->doAnimation("wave_finger_warning");
			sendContrabandFineSuiWindow(zone, scanner, player, numberOfContrabandItems);
			scanState = WAITFORPAYFINEANSWER;
			timeLeft = WAITFORPAYFINEANSWERTIMEOUT;
		} else {
			sendScannerChatMessage(zone, scanner, player, "clean_target_imperial", "clean_target_rebel");
			sendSystemMessage(scanner, player, "probe_scan_negative");
			scanner->doAnimation("wave_on_directing");
			scanState = FINISHED;
		}
	}
}

void ContrabandScanSessionImplementation::checkIfPlayerShouldBeScanned(CreatureObject* player) {
	if (System::random(SCANINITIATECHANCE) >= SCANINITIATECHANCE - 1) { // 1 in SCANINITIATECHANCE chance to initiate the scan.
		scanState = INITIATESCAN;
		player->updateCooldownTimer("crackdown_scan", PLAYERSCANCOOLDOWN);
	} else {
		scanState = FINISHED;
	}
}

void ContrabandScanSessionImplementation::initiateScan(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	sendSystemMessage(scanner, player, "dismount_imperial", "dismount_rebel");

	if (player->isRidingMount()) {
		player->dismount();
		sendSystemMessage(scanner, player, "dismount");
	}

	sendScannerChatMessage(zone, scanner, player, "scan_greeting_imperial", "scan_greeting_rebel");
	scanner->doAnimation("stop");

	scanState = FACTIONRANKCHECK;
	timeLeft = SCANTIME;
}

void ContrabandScanSessionImplementation::checkPlayerFactionRank(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	scanState = JEDIMINDTRICKPLAYERCHAT;
	if (scanner->getFaction() == player->getFaction()) {
		if (player->getFactionRank() > RECOGNIZEDFACTIONRANK) {
			sendScannerChatMessage(zone, scanner, player, "business_imperial", "business_rebel");
			sendSystemMessage(scanner, player, "probe_scan_done");
			scanner->doAnimation("wave_on_directing");
			scanState = FINISHED;
		}
	} else if (player->getFaction() != Factions::FACTIONNEUTRAL) {
		unsigned int detectionChance = BASEFACTIONDETECTIONCHANCE + RANKDETECTIONCHANCEMODIFIER * player->getFactionRank();
		if (System::random(100) < detectionChance && !smugglerAvoidedScan) {
			sendScannerChatMessage(zone, scanner, player, "discovered_chat_imperial", "discovered_chat_rebel");
			sendSystemMessage(scanner, player, "discovered_imperial", "discovered_rebel");
			scanner->doAnimation("point_accusingly");
			player->setFactionStatus(FactionStatus::COVERT);

			Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(player, scanner->getFaction(), player->getFactionRank());
			lambdaTask->schedule(TASKDELAY);

			scanState = FINISHED;
		}
	}
}

String ContrabandScanSessionImplementation::dependingOnJediSkills(CreatureObject* player, const String& novice, const String& lightSide, const String& darkSide) {
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

void ContrabandScanSessionImplementation::performJediMindTrick(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	if (player->hasSkill("force_title_jedi_rank_02") && !smugglerAvoidedScan) { // Jedi Padawan
		ChatManager* chatManager = zone->getZoneServer()->getChatManager();
		String stringId = "@imperial_presence/contraband_search:";
		String mood = dependingOnJediSkills(player, "firm", "confident", "angry");

		stringId += dependingOnJediSkills(player, "jedi_mind_trick_novice", "jedi_mind_trick", "jedi_mind_trick_dark");

		StringIdChatParameter chatMessage;
		chatMessage.setStringId(stringId);
		chatManager->broadcastChatMessage(player, chatMessage, scanner->getObjectID(), 0, chatManager->getMoodID(mood));
		player->doAnimation("force_persuasion");

		scanState = JEDIMINDTRICKSCANNERTHINK;
	} else {
		scanState = SCANDELAY;
	}
}

void ContrabandScanSessionImplementation::reactOnJediMindTrick(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	ChatManager* chatManager = zone->getZoneServer()->getChatManager();
	String stringId = "@imperial_presence/contraband_search:";

	stringId += dependingOnJediSkills(player, "not_search_you_novice", "not_search_you", "not_search_you_dark");

	StringIdChatParameter chatMessage;
	chatMessage.setStringId(stringId);
	chatManager->broadcastChatMessage(scanner, chatMessage, 0, chatManager->getSpatialChatType("think"), chatManager->getMoodID("ambivalent"));

	scanState = JEDIMINDTRICKSCANNERCHAT;
}

unsigned int ContrabandScanSessionImplementation::jediMindTrickSuccessChance(CreatureObject* player) {
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

void ContrabandScanSessionImplementation::jediMindTrickResult(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	ChatManager* chatManager = zone->getZoneServer()->getChatManager();
	String stringId = "@imperial_presence/contraband_search:";
	String mood;

	if (System::random(100) > jediMindTrickSuccessChance(player)) {
		stringId += "jedi_fail";
		mood = "suspicious";
		scanState = SCANDELAY;
		scanner->doAnimation("wave_finger_warning");
	} else {
		stringId += dependingOnJediSkills(player, "dont_search_novice", "dont_search", "dont_search_dark");
		mood = dependingOnJediSkills(player, "confused", "confident", "scared");
		sendSystemMessage(scanner, player, "probe_scan_done");
		scanner->doAnimation("wave_on_directing");
		scanState = FINISHED;
	}

	StringIdChatParameter chatMessage;
	chatMessage.setStringId(stringId);
	chatManager->broadcastChatMessage(scanner, chatMessage, player->getObjectID(), 0, chatManager->getMoodID(mood));
}

void ContrabandScanSessionImplementation::waitForPayFineAnswer(Zone* zone, AiAgent* scanner, CreatureObject* player) {
	if (timeLeft < 0) {
		removeFineSuiWindow(player);
		sendSystemMessage(scanner, player, "ran_away_imperial", "ran_away_rebel");
		player->getPlayerObject()->decreaseFactionStanding(scanner->getFactionString(), RANAWAYFACTIONFINE);
		scanState = FINISHED;
	} else if (fineAnswerGiven) {
		if (acceptedFine) {
			if (player->getCashCredits() + player->getBankCredits() >= fineToPay) {
				sendScannerChatMessage(zone, scanner, player, "warning_imperial", "warning_rebel");
				scanner->doAnimation("wave_on_directing");
				if (fineToPay <= player->getCashCredits()) {
					player->subtractCashCredits(fineToPay);
				} else {
					fineToPay -= player->getCashCredits();
					player->subtractCashCredits(player->getCashCredits());
					player->subtractBankCredits(fineToPay);
				}
			} else {
				sendScannerChatMessage(zone, scanner, player, "failure_to_pay_imperial", "failure_to_pay_rebel");
				scanner->doAnimation("wave_finger_warning");
			}
		} else {
			sendScannerChatMessage(zone, scanner, player, "punish_imperial", "punish_rebel");
			scanner->doAnimation("wave_finger_warning");
			player->getPlayerObject()->decreaseFactionStanding(scanner->getFactionString(), RANAWAYFACTIONFINE);
		}
		scanState = FINISHED;
	}
}

void ContrabandScanSessionImplementation::removeFineSuiWindow(CreatureObject* player) {
	if (player->getPlayerObject()->hasSuiBoxWindowType(SuiWindowType::CONTRABAND_SCAN_FINE)) {
		player->getPlayerObject()->removeSuiBoxType(SuiWindowType::CONTRABAND_SCAN_FINE);
	}
}

void ContrabandScanSessionImplementation::checkIfPlayerIsSmuggler(CreatureObject* player) {
	if (player->hasSkill("combat_smuggler_novice") && (System::random(100) > SMUGGLERAVOIDSCANCHANCE)) {
		smugglerAvoidedScan = true;
	}
}
