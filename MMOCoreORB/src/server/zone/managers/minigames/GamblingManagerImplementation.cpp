/*
 * GamblingManagerImplementation.cpp
 *
 *  Created on: Apr 11, 2010
 *      Author: swgemu
 */

#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/StringIdChatParameter.h"
#include "system/util/Vector.h"
#include "system/util/VectorMap.h"
#include "server/zone/managers/minigames/events/GamblingEvent.h"
#include "server/zone/objects/player/sui/slotmachinebox/SuiSlotMachineBox.h"
#include "server/zone/objects/player/sui/callbacks/GamblingSlotSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/GamblingRouletteSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/GamblingSlotPayoutSuiCallback.h"
#include "server/zone/managers/minigames/GamblingBet.h"
#include "server/zone/objects/transaction/TransactionLog.h"

// #define DEBUG_GAMBLING

void GamblingManagerImplementation::registerPlayer(GamblingTerminal* terminal, CreatureObject* player) {
	if (terminal == nullptr || player == nullptr)
		return;

	Locker lock(_this.getReferenceUnsafeStaticCast());

	switch (terminal->getMachineType()) {
		case GamblingTerminal::SLOTMACHINE: {
			slotGames.put(player, terminal);
			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			rouletteGames.put(player, terminal);
			break;
		}
	}
}

uint32 GamblingManagerImplementation::createWindow(GamblingTerminal* terminal, CreatureObject* player) {
	if (terminal == nullptr || player == nullptr)
		return 0;

	uint32 boxID = 0;

	switch (terminal->getMachineType()) {
		case GamblingTerminal::SLOTMACHINE: {
			createPayoutWindow(player);
			boxID = createSlotWindow(player, boxID);

			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			boxID = createRouletteWindow(player);

			break;
		}
	}

	return boxID;
}

uint32 GamblingManagerImplementation::createSlotWindow(CreatureObject* player, uint32 payoutBoxID) {
	if (player == nullptr)
		return 0;

	ManagedReference<GamblingTerminal*> terminal = slotGames.get(player);
	ZoneServer* server = player->getZoneServer();

	if (terminal == nullptr)
		return 0;

	String prompt = "Press the button corresponding to the desired action.";

	int amount = 0;

	bool quit = true;

	if (!terminal->getBets()->isEmpty()) {
		amount = terminal->getBets()->get(0)->getAmount();
		quit = false;
	}

	// create new window
	ManagedReference<SuiSlotMachineBox*> box = new SuiSlotMachineBox(player, SuiWindowType::GAMBLING_SLOT, payoutBoxID, 3);

	box->setUsingObject(terminal);

	box->setPromptTitle("@gambling/game_n:slot_standard");
	box->setPromptText(prompt);

	box->addMenuItem("Current Bet: " + String::valueOf(amount), 0);
	box->addMenuItem("Max Bet: " + String::valueOf(terminal->getMaxBet()), 1);
	box->addMenuItem("Cash Balance: " + String::valueOf(player->getCashCredits()), 2);
	box->addMenuItem("Bank Balance: " + String::valueOf(player->getBankCredits()), 3);
	box->addMenuItem("Total Money: " + String::valueOf(player->getCashCredits() + player->getBankCredits()), 4);

	if (quit)
		box->setCancelButton(true, "@ui:quit");
	else
		box->setCancelButton(true, "@ui:spin");

	box->setOtherButton(true, "@ui:bet_one");
	box->setOkButton(true, "@ui:bet_max");

	box->setForceCloseDistance(32.f);
	box->setCallback(new GamblingSlotSuiCallback(server));

	player->getPlayerObject()->addSuiBox(box);
	player->sendMessage(box->generateMessage());

	return box->getBoxID();
}

uint32 GamblingManagerImplementation::createRouletteWindow(CreatureObject* player) {
	if (player == nullptr)
		return 0;

	int totalBet = 0;

	String prompt = "The following is a summary of your current bets...\n\nUse /bet <amount> <1-36,0,00,red,black,odd,even,high,low> to wager.\nExample: '/bet 5 black' to wager 5 credits on black\n\nCash : " + String::valueOf(player->getCashCredits()) + "\nBank : " + String::valueOf(player->getBankCredits()) +
					"\nTotal: " + String::valueOf(player->getCashCredits() + player->getBankCredits()) + "\n\nNOTE: If you leave the table after placing a bet, all of your outstanding bets will be forfeit.";

	// create new window
	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::GAMBLING_ROULETTE, 2);
	box->setPromptTitle("@gambling/game_n:roulette");
	box->setPromptText(prompt);

	ManagedReference<GamblingTerminal*> terminal = rouletteGames.get(player);

	if (terminal == nullptr) {
		return 0;
	}

	box->setUsingObject(terminal);

	if (terminal->getBets()->size() != 0) {
		for (int i = 0; i < terminal->getBets()->size(); ++i) {
			if (terminal->getBets()->get(i)->getPlayer() == player) {
				totalBet += terminal->getBets()->get(i)->getAmount();
				String target = terminal->getBets()->get(i)->getTarget();
				target[0] = toupper(target[0]);
				box->addMenuItem(target + ": " + String::valueOf(terminal->getBets()->get(i)->getAmount()), i);
			}
		}
	}

	if (totalBet == 0) {
		box->addMenuItem("Total Bet : 0", 0);
	} else {
		box->addMenuItem(" ", -2);
		box->addMenuItem("Total Bet : " + String::valueOf(totalBet), -3);
	}

	box->setCancelButton(true, "@ui:leave_game");
	box->setOtherButton(false, "");
	box->setOkButton(true, "@ui:refresh");

	box->setForceCloseDistance(32.f);

	ZoneServer* server = player->getZoneServer();

	box->setCallback(new GamblingRouletteSuiCallback(server));

	player->getPlayerObject()->addSuiBox(box);

	player->sendMessage(box->generateMessage());

	return box->getBoxID();
}

uint32 GamblingManagerImplementation::createPayoutWindow(CreatureObject* player) {
	if (player == nullptr)
		return 0;

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return 0;
	}

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr) {
		return 0;
	}

	if (ghost->hasSuiBoxWindowType(SuiWindowType::GAMBLING_SLOT_PAYOUT)) {
		ghost->closeSuiWindowType(SuiWindowType::GAMBLING_SLOT_PAYOUT);
	}

	String prompt = "The following is the payout schedule for this slot machine.\n \nLegend:\nXXX: denotes any 3 of the same number\n*X|Y|Z: denotes any combination of the 3 numbers";

	// create new window
	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::GAMBLING_SLOT_PAYOUT, 1);
	box->setPromptTitle("PAYOUT SCHEDULE");
	box->setPromptText(prompt);
	box->addMenuItem("*1|2|3 -> base:2 max:6", 0);
	box->addMenuItem("000 -> base:4 max:12", 1);
	box->addMenuItem("111 -> base:50 max:150", 2);
	box->addMenuItem("222 -> base:75 max:225", 3);
	box->addMenuItem("333 -> base:100 max:300", 3);
	box->addMenuItem("444 -> base:250 max:750", 3);
	box->addMenuItem("555 -> base:500 max:1500", 3);
	box->addMenuItem("666 -> base:1000 max:3000", 3);
	box->addMenuItem("777 -> base:1500 max:5000", 3);
	box->setCancelButton(false, "");
	box->setOtherButton(false, "");
	box->setOkButton(true, "@ui:ok");

	box->setCallback(new GamblingSlotPayoutSuiCallback(zoneServer));

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());

	return box->getBoxID();
}

void GamblingManagerImplementation::refreshRouletteMenu(CreatureObject* player) {
	if (player == nullptr)
		return;

	ManagedReference<GamblingTerminal*> terminal = rouletteGames.get(player);

	if (terminal == nullptr)
		return;

	terminal->closeMenu(player, false);

	terminal->removePlayer(player);
	terminal->addPlayerWindow(player, createRouletteWindow(player));
}

void GamblingManagerImplementation::refreshSlotMenu(CreatureObject* player, GamblingTerminal* terminal) {
	if (player == nullptr || terminal == nullptr)
		return;

	terminal->closeMenu(player, false);

	terminal->removePlayer(player);

	uint32 boxID = createWindow(terminal, player);
	terminal->addPlayerWindow(player, boxID);
}

void GamblingManagerImplementation::removeOutOfRangePlayers(GamblingTerminal* terminal) {
	if (terminal == nullptr) {
		return;
	}

	Locker lock(_this.getReferenceUnsafeStaticCast());

	auto games = slotGames;

	switch (terminal->getMachineType()) {
		case GamblingTerminal::SLOTMACHINE: {
			games = slotGames;
			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			games = rouletteGames;
			break;
		}
	}

	for (const auto& entry : games) {
		if (entry.getValue()->getObjectID() == terminal->getObjectID()) {
			auto player = entry.getKey();
			if (player != nullptr && (!player->isInRange(terminal, 20.0f) || !player->isOnline())) {
				leaveTerminal(player, terminal->getMachineType());
			}
		}
	}
}

void GamblingManagerImplementation::initializeSlotWeights() {
	slotWeights.add(79);
	slotWeights.add(22);
	slotWeights.add(18);
	slotWeights.add(16);
	slotWeights.add(10);
	slotWeights.add(7);
	slotWeights.add(5);
	slotWeights.add(4);

	slotWeightsTotal = -1;
	for (int i = 0; i < slotWeights.size(); i++) {
		slotWeightsTotal += slotWeights.get(i);
	}
}

int GamblingManagerImplementation::rollSlotDigit() {
	int rolledWeight = System::random(slotWeightsTotal);

	int value = 0;
	while (rolledWeight > slotWeights.get(value) && value < slotWeights.size()) {
		rolledWeight -= slotWeights.get(value);
		value++;
	}

	return value;
}

void GamblingManagerImplementation::handleSlot(CreatureObject* player, bool cancel, bool other) {
	if (player == nullptr)
		return;

	ManagedReference<GamblingTerminal*> terminal = slotGames.get(player);

	if (terminal == nullptr) {
		return;
	}

	bool hasBets = !terminal->getBets()->isEmpty();

#ifdef DEBUG_GAMBLING
	info(true) << "handleSlot for player: " << player->getDisplayedName() << " ID: " << player->getObjectID() << " Cancel: " << (cancel ? "TRUE" : "FALSE") << " Other: " << (other ? "TRUE" : "FALSE");
#endif

	if (cancel) {
		if (hasBets)
			startGame(player, GamblingTerminal::SLOTMACHINE);
		else
			leaveTerminal(player, GamblingTerminal::SLOTMACHINE);
	} else if (other) {
		bet(terminal, player, 1, 0);
	} else {
		if (hasBets)
			bet(terminal, player, terminal->getMaxBet() - terminal->getBets()->get(0)->getAmount(), 0);
		else
			bet(terminal, player, 3, 0);
	}
}

int GamblingManagerImplementation::getMaximumAllowedBet(GamblingTerminal* terminal, CreatureObject* player, int target) {
	if (player == nullptr || terminal == nullptr) {
		return 0;
	}

#ifdef DEBUG_GAMBLING
	info(true) << "GamblingManagerImplementation::getMaximumAllowedBet - target: " << target;
#endif

	int maximumBet = terminal->getMaxBet();

	if (!terminal->getBets()->isEmpty()) {
		auto bets = terminal->getBets();

		for (int i = 0; i < bets->size(); i++) {
			if (bets->get(i)->getPlayer()->getObjectID() == player->getObjectID() && bets->get(i)->getTarget() == roulette.get(target)) {
				maximumBet -= bets->get(i)->getAmount();
			}
		}
	}
	if (maximumBet < 0) {
		player->error("Player has been able to bet more than the maximum allowed amount.");
		maximumBet = 0;
	}

	return maximumBet;
}

void GamblingManagerImplementation::bet(CreatureObject* player, int amount, int target, int machineType) {
	if (player == nullptr)
		return;

#ifdef DEBUG_GAMBLING
	info(true) << "GamblingManagerImplementation::bet1 - amount: " << amount << " target: " << target << " machineType: " << machineType;
#endif

	if (machineType == GamblingTerminal::ROULETTEMACHINE) {
		bet(rouletteGames.get(player), player, amount, target);
	} else if (machineType == GamblingTerminal::SLOTMACHINE) {
		bet(slotGames.get(player), player, amount, target);
	}
}

void GamblingManagerImplementation::bet(GamblingTerminal* terminal, CreatureObject* player, int amount, int target) {
	if (player == nullptr || terminal == nullptr)
		return;

	Locker lock(terminal, player);

	int machineType = terminal->getMachineType();

#ifdef DEBUG_GAMBLING
	info(true) << "GamblingManagerImplementation::bet2 - amount: " << amount << " target: " << target << " machineType: " << machineType;
#endif

	switch (machineType) {
		case GamblingTerminal::SLOTMACHINE: {
			if (amount > terminal->getMaxBet()) {
				StringIdChatParameter body("gambling/default_interface", "bet_above_max");
				body.setDI(terminal->getMaxBet());

				player->sendSystemMessage(body);
			} else if (player->getCashCredits() < amount) {
				player->sendSystemMessage("@gambling/default_interface:player_broke");
			} else if (!player->isInRange(terminal, 25.0)) {
				player->sendSystemMessage("@gambling/default_interface:bet_failed_distance");
			} else if (amount < terminal->getMinBet()) {
				StringIdChatParameter body("gambling/default_interface", "bet_below_min");
				body.setDI(terminal->getMinBet());

				player->sendSystemMessage(body);
			} else {
				Vector<Reference<GamblingBet*>>* terminalBets = terminal->getBets();

				if (terminalBets == nullptr) {
					return;
				}

				{
					TransactionLog trx(player, TrxCode::GAMBLINGSLOTSTANDARD, amount, true);
					player->subtractCashCredits(amount);
				}

				StringIdChatParameter textPlayer("base_player", "prose_pay_success");
				textPlayer.setDI(amount);

				String terminalName;
				terminal->getObjectName()->getFullPath(terminalName);
				textPlayer.setTT(terminalName);

				player->sendSystemMessage(textPlayer);

				if (!terminalBets->isEmpty()) {
					auto oldBet = terminalBets->get(0);

					if (oldBet != nullptr) {
						amount += oldBet->getAmount();
					}

					terminalBets->removeAll();
				}

				terminalBets->add(new GamblingBet(player, amount));

#ifdef DEBUG_GAMBLING
				info(true) << "bet2 - hit else maxBet: " << terminal->getMaxBet() << " Amount: " << amount;
#endif

				if (amount >= terminal->getMaxBet()) {
					startGame(player, GamblingTerminal::SLOTMACHINE);
				} else {
					refreshSlotMenu(player, terminal);
				}
			}
			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			if (amount > getMaximumAllowedBet(terminal, player, target)) {
				StringIdChatParameter body("gambling/default_interface", "bet_above_max");
				body.setDI(terminal->getMaxBet());

				player->sendSystemMessage(body);
			} else if (player->getCashCredits() < amount) {
				player->sendSystemMessage("@gambling/default_interface:player_broke");

			} else if (!player->isInRange(terminal, 25.0)) {
				player->sendSystemMessage("@gambling/default_interface:bet_failed_distance");

			} else if (amount < terminal->getMinBet()) {
				StringIdChatParameter body("gambling/default_interface", "bet_below_min");
				body.setDI(terminal->getMinBet());

				player->sendSystemMessage(body);
			} else {
				Locker _locker(terminal);

				{
					TransactionLog trx(player, TrxCode::GAMBLINGROULETTE, amount, true);
					player->subtractCashCredits(amount);
				}

				terminal->getBets()->add(new GamblingBet(player, amount, roulette.get(target)));

				StringIdChatParameter textPlayer("gambling/default_interface", "prose_bet_placed");
				textPlayer.setDI(amount);
				player->sendSystemMessage(textPlayer);

				refreshRouletteMenu(player);
			}
			break;
		}
	}
}

void GamblingManagerImplementation::createGamblingEvent(GamblingTerminal* terminal, uint32 time) {
	if (terminal == nullptr)
		return;

#ifdef DEBUG_GAMBLING
	info(true) << "createGamblingEvent called -- Time: " << time;
#endif

	GamblingEvent* gamblingEvent = new GamblingEvent(terminal, terminal->getGameCount());

	if (gamblingEvent != nullptr)
		gamblingEvent->schedule(time);
}

void GamblingManagerImplementation::startGame(CreatureObject* player, int machineType) {
	if (player == nullptr)
		return;

#ifdef DEBUG_GAMBLING
	info(true) << "GamblingManagerImplementation::startGame1 - machineType: " << machineType;
#endif

	switch (machineType) {
		case GamblingTerminal::SLOTMACHINE: {
			startGame(slotGames.get(player));
			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			startGame(rouletteGames.get(player));
			break;
		}
	}
}

void GamblingManagerImplementation::startGame(GamblingTerminal* terminal) {
	if (terminal == nullptr)
		return;

	Locker lock(terminal);

	int machineType = terminal->getMachineType();
	uint32 time = 6000;

#ifdef DEBUG_GAMBLING
	info(true) << "startGame2 - machineType: " << machineType;
#endif

	switch (machineType) {
		case GamblingTerminal::SLOTMACHINE: {
			terminal->setState(GamblingTerminal::GAMESTARTED);
			terminal->statusUpdate(GamblingTerminal::GAMESTARTED);

			time = slotTimer.get(GamblingTerminal::GAMESTARTED - 2) * 1000;
			createGamblingEvent(terminal, time);

			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			terminal->statusUpdate(terminal->getState());

			time = rouletteTimer.get(terminal->getState() - 1) * 1000;
			createGamblingEvent(terminal, time);

			break;
		}
	}
}

void GamblingManagerImplementation::continueGame(GamblingTerminal* terminal) {
	if (terminal == nullptr)
		return;

	Locker lock(terminal);

	VectorMap<ManagedReference<CreatureObject*>, uint32>* playerWindows = terminal->getPlayersWindows();

	if (playerWindows == nullptr)
		return;

	int windowsSize = playerWindows->size();

	if (windowsSize <= 0)
		return;

	int machineType = terminal->getMachineType();
	int state = terminal->getState();

#ifdef DEBUG_GAMBLING
	info(true) << "continueGame - machineType: " << machineType << " state: " << state;
#endif

	uint32 time = 6000;

	switch (terminal->getMachineType()) {
		case GamblingTerminal::SLOTMACHINE: {
			if (state == GamblingTerminal::SLOTGAMEENDED) {
				// createNextRound
				terminal->joinTerminal(playerWindows->elementAt(0).getKey());
			} else {
				if (state == GamblingTerminal::END) {
					stopGame(terminal, false);
				} else {
					state += 1;

					terminal->setState(state);
					terminal->statusUpdate(state);

					time = slotTimer.get(state - 2) * 1000;
					createGamblingEvent(terminal, time);
				}
			}

			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			if (state == GamblingTerminal::WHEELPAYOUT) {
				stopGame(terminal, false);
			} else {
				terminal->setState(state + 1);
				terminal->statusUpdate(state);

				time = rouletteTimer.get(state - 1) * 1000;
				createGamblingEvent(terminal, time);
			}

			break;
		}
	}
}

// Terminal is locked
void GamblingManagerImplementation::stopGame(GamblingTerminal* terminal, bool cancel) {
	if (terminal == nullptr)
		return;

	int machineType = terminal->getMachineType();

#ifdef DEBUG_GAMBLING
	info(true) << "stopGame - machineType: " << machineType << " cancel: " << (cancel ? "TRUE" : "FALSE");
#endif

	switch (machineType) {
		case GamblingTerminal::SLOTMACHINE: {
			if (!cancel) {
				calculateOutcome(terminal);

				terminal->closeAllMenus();

				terminal->setState(GamblingTerminal::SLOTGAMEENDED);
				terminal->statusUpdate(terminal->getState());

				terminal->getBets()->removeAll();

				createGamblingEvent(terminal, (terminal->getState() - 2) * 1000);
			} else {
				terminal->closeAllMenus();

				if ((terminal->getEvent() != nullptr) && (terminal->getState() >= GamblingTerminal::GAMESTARTED)) {
					terminal->getEvent()->cancel();
				}

				terminal->reset();
			}

			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			if (!cancel) {
				calculateOutcome(terminal);

				terminal->closeAllMenus();

				terminal->reset();
			} else {
				terminal->closeAllMenus();

				if (terminal->getEvent() != nullptr) {
					terminal->getEvent()->cancel();
				}

				terminal->reset();
			}
			break;
		}
	}

	removeOutOfRangePlayers(terminal);
}

void GamblingManagerImplementation::calculateOutcome(GamblingTerminal* terminal) {
	if (terminal == nullptr)
		return;

	Locker locker(terminal);

	int machineType = terminal->getMachineType();

#ifdef DEBUG_GAMBLING
	info(true) << "GamblingManagerImplementation::calculateOutcome - machineType: " << machineType;
#endif

	switch (machineType) {
		case GamblingTerminal::SLOTMACHINE: {
			GamblingBet* bet = terminal->getBets()->get(0);

			ManagedReference<CreatureObject*> player = terminal->getPlayersWindows()->elementAt(0).getKey();

			if ((bet != nullptr) && (player != nullptr)) {
				if (terminal->getFirst() == terminal->getSecond() && terminal->getSecond() == terminal->getThird()) {
					Locker _locker(player);

					int win = bet->getAmount() * slot.get(terminal->getFirst());
					if (win == 4500) {
						win += 500; // 500 extra credits for betting 3 credits and getting 777.
					}

					StringIdChatParameter textPlayer("gambling/default_interface", "winner_to_winner");
					textPlayer.setDI(win);
					player->sendSystemMessage(textPlayer);

					{
						TransactionLog trx(TrxCode::GAMBLINGSLOTSTANDARD, player, win, true);
						player->addCashCredits(win, true);
					}

				} else if ((0 < terminal->getFirst() && terminal->getFirst() < 4) && (0 < terminal->getSecond() && terminal->getSecond() < 4) && (0 < terminal->getThird() && terminal->getThird() < 4)) {
					Locker _locker(player);

					int win = bet->getAmount() * 2;

					StringIdChatParameter textPlayer("gambling/default_interface", "winner_to_winner");
					textPlayer.setDI(win);
					player->sendSystemMessage(textPlayer);

					{
						TransactionLog trx(TrxCode::GAMBLINGSLOTSTANDARD, player, win, true);
						player->addCashCredits(win, true);
					}
				} else {
					player->sendSystemMessage("Sorry, you did not win this round. Please try again.");
				}
			}

			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			VectorMap<ManagedReference<CreatureObject*>, int>* winnings = terminal->getWinnings();

			auto bets = terminal->getBets();

			int tempReward;
			String tempTarget;

			for (int i = 0; i < bets->size(); ++i) {
				tempTarget = bets->get(i)->getTarget();

				if (tempTarget == "odd") {
					// odd
					if (isOdd(terminal->getFirst())) {
						tempReward = (bets->get(i)->getAmount() * 2);

						if (winnings->contains(bets->get(i)->getPlayer())) {
							tempReward += winnings->get(bets->get(i)->getPlayer());

							winnings->drop(bets->get(i)->getPlayer());
						}

						winnings->put(bets->get(i)->getPlayer(), tempReward);
					}
				} else if (tempTarget == "even") {
					// even
					if (isEven(terminal->getFirst())) {
						tempReward = (bets->get(i)->getAmount() * 2);

						if (winnings->contains(bets->get(i)->getPlayer())) {
							tempReward += winnings->get(bets->get(i)->getPlayer());

							winnings->drop(bets->get(i)->getPlayer());
						}

						winnings->put(bets->get(i)->getPlayer(), tempReward);
					}
				} else if (tempTarget == "high") {
					// high
					if (isHigh(terminal->getFirst())) {
						tempReward = (bets->get(i)->getAmount() * 2);

						if (winnings->contains(bets->get(i)->getPlayer())) {
							tempReward += winnings->get(bets->get(i)->getPlayer());

							winnings->drop(bets->get(i)->getPlayer());
						}

						winnings->put(bets->get(i)->getPlayer(), tempReward);
					}
				} else if (tempTarget == "low") {
					// low
					if (isLow(terminal->getFirst())) {
						tempReward = (bets->get(i)->getAmount() * 2);

						if (winnings->contains(bets->get(i)->getPlayer())) {
							tempReward += winnings->get(bets->get(i)->getPlayer());

							winnings->drop(bets->get(i)->getPlayer());
						}

						winnings->put(bets->get(i)->getPlayer(), tempReward);
					}
				} else if (tempTarget == "red") {
					// red
					if (isRed(terminal->getFirst())) {
						tempReward = (bets->get(i)->getAmount() * 2);

						if (winnings->contains(bets->get(i)->getPlayer())) {
							tempReward += winnings->get(bets->get(i)->getPlayer());

							winnings->drop(bets->get(i)->getPlayer());
						}

						winnings->put(bets->get(i)->getPlayer(), tempReward);
					}
				} else if (tempTarget == "black") {
					// black
					if (isBlack(terminal->getFirst())) {
						tempReward = (bets->get(i)->getAmount() * 2);

						if (winnings->contains(bets->get(i)->getPlayer())) {
							tempReward += winnings->get(bets->get(i)->getPlayer());

							winnings->drop(bets->get(i)->getPlayer());
						}

						winnings->put(bets->get(i)->getPlayer(), tempReward);
					}
				} else {
					// single number: 0,00,1-36

					if (tempTarget == roulette.get(terminal->getFirst())) {
						tempReward = (bets->get(i)->getAmount() * 35);

						if (winnings->contains(bets->get(i)->getPlayer())) {
							tempReward += winnings->get(bets->get(i)->getPlayer());

							winnings->drop(bets->get(i)->getPlayer());
						}

						winnings->put(bets->get(i)->getPlayer(), tempReward);
					}
				}
			}

			for (int i = 0; i < winnings->size(); ++i) { // send money and messages to players
				if (winnings->get(i) == 0) {
					winnings->elementAt(i).getKey()->sendSystemMessage("You don't win anything");
				} else {
					CreatureObject* player = winnings->elementAt(i).getKey();

					if (player != nullptr) {
						Locker _locker(player);

						// Send message to others
						StringIdChatParameter textOther("gambling/default_interface", "winner_to_other");
						textOther.setDI(winnings->get(i));
						textOther.setTO(player->getFirstName());
						textOther.setTO(player->getObjectID());
						terminal->notifyOthers(player, &textOther);

						StringIdChatParameter textPlayer("gambling/default_interface", "winner_to_winner");
						textPlayer.setDI(winnings->get(i));
						player->sendSystemMessage(textPlayer);

						{
							TransactionLog trx(TrxCode::GAMBLINGROULETTE, player, winnings->get(i), true);
							player->addCashCredits(winnings->get(i), true);
						}
					}
				}
			}

			break;
		}
	}
}

void GamblingManagerImplementation::leaveTerminal(CreatureObject* player, int machineType) {
	if (player == nullptr)
		return;

	switch (machineType) {
		case GamblingTerminal::SLOTMACHINE: {
			ManagedReference<GamblingTerminal*> terminal = slotGames.get(player);

			if (terminal != nullptr) {
				Locker locker(terminal);

				if (terminal->getPlayersWindows()->contains(player)) {
					terminal->leaveTerminal(player);
					slotGames.drop(player);
				}
			}

			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			ManagedReference<GamblingTerminal*> terminal = rouletteGames.get(player);

			if (terminal != nullptr) {
				Locker locker(terminal);

				if (terminal->getPlayersWindows()->contains(player)) {
					terminal->leaveTerminal(player);
					rouletteGames.drop(player);
				}
			}

			break;
		}
	}
}

void GamblingManagerImplementation::removeGambler(CreatureObject* player, int machineType) {
	Locker _locker(_this.getReferenceUnsafeStaticCast());

	if (machineType == GamblingTerminal::SLOTMACHINE) {
		slotGames.drop(player);
	} else if (machineType == GamblingTerminal::ROULETTEMACHINE) {
		rouletteGames.drop(player);
	}
}
