/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/sui/slotmachinebox/SuiSlotMachineBox.h"
#include "server/zone/managers/minigames/events/GamblingEvent.h"

int GamblingTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 245 || selectedID == 20) {
		if (playersWindows.contains(player)) {
			ManagedReference<GamblingManager*> gamblingManager = server->getGamblingManager();

			if (gamblingManager == nullptr) {
				return 0;
			}
			gamblingManager->leaveTerminal(player, getMachineType());
		} else {
			joinTerminal(player);
		}
	}

	return 0;
}

void GamblingTerminalImplementation::setEvent(GamblingEvent* event) {
	this->event = event;
}

bool GamblingTerminalImplementation::invalidPosture(CreatureObject* player) {
	if (player->isIncapacitated() || player->isInCombat() || player->isSwimming() || player->isRidingMount() || player->isDead() || player->isMeditating())
		return true;
	return false;
}

bool GamblingTerminalImplementation::checkJoin(CreatureObject* player) {
	ManagedReference<GamblingManager*> gamblingManager = server->getGamblingManager();

	if (gamblingManager == nullptr) {
		return false;
	}

	if (gamblingManager->isPlaying(player)) {
		player->sendSystemMessage("You are already playing at a gambling terminal.");
		return false;
	}

	bool returnValue = true;
	switch (machineType) {
		case SLOTMACHINE: {
			if (playersWindows.size() > 0) {

				returnValue = false;

				StringIdChatParameter textPlayer("gambling/default_interface","prose_station_full");
				textPlayer.setTT(getMachineTypeText());
				player->sendSystemMessage(textPlayer);

			} else if (!player->isInRange(_this.getReferenceUnsafeStaticCast(), 20.0)) {
				returnValue = false;

				StringIdChatParameter textPlayer("ui","radial_out_of_range_prose");
				textPlayer.setTT(getMachineTypeText());
				textPlayer.setTO("@gambling/default_interface:mnu_join");
				player->sendSystemMessage(textPlayer);

				info(String::valueOf(machineType),true);
				info(String::valueOf(getObjectID()),true);
			} else if (invalidPosture(player)) {
				player->sendSystemMessage("@error_message:wrong_state");
				returnValue = false;
			}

			break;
		}
		case ROULETTEMACHINE: {

			if (playersWindows.size() >= 4) {

				returnValue = false;

				StringIdChatParameter textPlayer("gambling/default_interface","prose_station_full");
				textPlayer.setTT(getMachineTypeText());
				player->sendSystemMessage(textPlayer);

			} else if (!player->isInRange(_this.getReferenceUnsafeStaticCast(), 20.0)) {
				returnValue = false;

				StringIdChatParameter textPlayer("ui","radial_out_of_range_prose");
				textPlayer.setTT(getMachineTypeText());
				textPlayer.setTO("@gambling/default_interface:mnu_join");
				player->sendSystemMessage(textPlayer);

				info(String::valueOf(machineType),true);
				info(String::valueOf(getObjectID()),true);
			}

			break;
		}
	}
	return returnValue;
}

void GamblingTerminalImplementation::joinTerminal(CreatureObject* player) {
	ManagedReference<GamblingManager*> gamblingManager = server->getGamblingManager();

	if (gamblingManager == nullptr) {
		return;
	}

	Locker _locker(_this.getReferenceUnsafeStaticCast());

	gamblingManager->removeOutOfRangePlayers(_this.getReferenceUnsafeStaticCast());

	switch (machineType) {
		case SLOTMACHINE: {
			if (state == SLOTGAMEENDED) {//begin new round

				setState(GAMESTARTING);
				incGameCount();

				playersWindows.drop(player);

				addPlayerWindow(player, gamblingManager->createSlotWindow(player, 0));

			} else {
				if (checkJoin(player)) {

					setState(GAMESTARTING);
					incGameCount();

					gamblingManager->registerPlayer(_this.getReferenceUnsafeStaticCast(), player);

					addPlayerWindow(player, gamblingManager->createWindow(_this.getReferenceUnsafeStaticCast(), player));

					statusUpdate(player, JOINTERMINAL);

				}
			}

			break;
		}
		case ROULETTEMACHINE: {
			if (checkJoin(player)) {

				winnings.put(player, 0);

				gamblingManager->registerPlayer(_this.getReferenceUnsafeStaticCast(), player);

				addPlayerWindow(player, gamblingManager->createWindow(_this.getReferenceUnsafeStaticCast(), player));

				statusUpdate(player, JOINTERMINAL);

				if(!gameRunning()) {
					setState(GAMESTARTING);
					incGameCount();

					gamblingManager->startGame(_this.getReferenceUnsafeStaticCast());
				}

			}

			break;
		}

	}
}

void GamblingTerminalImplementation::closeMenu(CreatureObject* player, bool payout) {
	if (player == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	uint32 boxID = playersWindows.get(player);

	if (ghost->hasSuiBox(boxID)) {
		ManagedReference<SuiSlotMachineBox*> box = ghost->getSuiBox(boxID).castTo<SuiSlotMachineBox*>();

		if (payout && box != nullptr) {
			uint32 payoutBoxID = box->getPayoutBoxID();

			if (payoutBoxID > 0) {
				ghost->removeSuiBox(payoutBoxID, true);
			}
		}

		ghost->removeSuiBox(boxID, true);
	}
}

void GamblingTerminalImplementation::closeAllMenus() {
	ManagedReference<GamblingManager*> gamblingManager = server->getGamblingManager();

	switch (machineType) {
		case SLOTMACHINE: {
			if (playersWindows.size() > 0)
				closeMenu(playersWindows.elementAt(0).getKey(),true);

			break;
		}
		case ROULETTEMACHINE: {
			for (int i = 0; i < playersWindows.size(); i++) {
				CreatureObject* player = playersWindows.elementAt(i).getKey();

				if (player == nullptr)
					continue;

				closeMenu(player, false);

				// drop gambler here
				if (gamblingManager != nullptr)
					gamblingManager->removeGambler(player, machineType);
			}

			break;
		}
	}
}

void GamblingTerminalImplementation::leaveTerminal(CreatureObject* player) {
	ManagedReference<GamblingManager*> gamblingManager = server->getGamblingManager();

	Locker _locker(_this.getReferenceUnsafeStaticCast());
	switch (machineType) {
		case SLOTMACHINE: {
			closeMenu(player, true);

			statusUpdate(player, LEAVETERMINAL);

			removePlayer(player);
			gamblingManager->stopGame(_this.getReferenceUnsafeStaticCast(), true);

			break;
		}
		case ROULETTEMACHINE: {
			closeMenu(player, false);

			statusUpdate(player, LEAVETERMINAL);
			removePlayer(player);

			winnings.drop(player);

			if (playersWindows.size() == 0) {
				gamblingManager->stopGame(_this.getReferenceUnsafeStaticCast(), true);
			}

			break;
		}
	}

}

void GamblingTerminalImplementation::statusUpdate(int event) {
	switch (machineType) {
		case SLOTMACHINE: {

			statusUpdate(playersWindows.elementAt(0).getKey(), event);

			break;
		}
		case ROULETTEMACHINE: {

			statusUpdate(nullptr, event);

			break;
		}
	}
}

void GamblingTerminalImplementation::statusUpdate(CreatureObject* player, int event) {
	ManagedReference<GamblingManager*> gamblingManager = server->getGamblingManager();

	if (gamblingManager == nullptr) {
		return;
	}

	switch (machineType) {
		case SLOTMACHINE: {

			switch (event) {
				case JOINTERMINAL: {

					if (player != nullptr) {

						StringIdChatParameter textPlayer("gambling/default_interface","prose_player_join");
						textPlayer.setTO(getMachineTypeText());
						player->sendSystemMessage(textPlayer);
					}

					break;
				}
				case LEAVETERMINAL: {

					if (player != nullptr) {
						StringIdChatParameter textPlayer("gambling/default_interface","prose_player_leave");
						textPlayer.setTO(getMachineTypeText());
						player->sendSystemMessage(textPlayer);
					}

					break;
				}
				case GAMESTARTED: {

					if (player != nullptr) {
						player->sendSystemMessage("@gambling/default_interface:wheel_spin");
					}

					break;
				}
				case TWOLEFT: {
					first = gamblingManager->rollSlotDigit();

					if (player != nullptr) {
						player->sendSystemMessage("Slot Machine Pay Line");
						player->sendSystemMessage("-- | " + String::valueOf(first) + " | | Rolling... | | Rolling... | --");
					}

					break;
				}
				case ONELEFT: {
					second = gamblingManager->rollSlotDigit();

					if (player != nullptr) {
						player->sendSystemMessage("Slot Machine Pay Line");
						player->sendSystemMessage("-- | " + String::valueOf(first) + " | | " + String::valueOf(second) + " | | Rolling... | --");
					}

					break;
				}
				case END: {
					third = gamblingManager->rollSlotDigit();

					if (player != nullptr) {
						player->sendSystemMessage("Slot Machine Pay Line");
						player->sendSystemMessage("-- | " + String::valueOf(first) + " | | " + String::valueOf(second) + " | | " + String::valueOf(third) + " | --");
					}

					break;
				}
			}

			break;
		}
		case ROULETTEMACHINE: {

			switch (event) {
				case JOINTERMINAL: {

					StringIdChatParameter textOthers("gambling/default_interface","prose_player_join_other");

					if (player != nullptr) {
						StringIdChatParameter textPlayer("gambling/default_interface","prose_player_join");
						textPlayer.setTO(getMachineTypeText());
						player->sendSystemMessage(textPlayer);

						textOthers.setTT(player->getFirstName());
					}

					notifyOthers(player, &textOthers);

					break;
				}
				case LEAVETERMINAL: {

					StringIdChatParameter textOthers("gambling/default_interface","prose_player_leave_other");

					if (player != nullptr) {
						StringIdChatParameter textPlayer("gambling/default_interface","prose_player_leave");
						textPlayer.setTO(getMachineTypeText());
						player->sendSystemMessage(textPlayer);

						textOthers.setTT(player->getFirstName());
					}

					notifyOthers(player, &textOthers);

					break;
				}
				case GAMESTARTING: {

					StringIdChatParameter body("gambling/default_interface","prose_starting_in");
					body.setDI(120);

					notifyAll(&body);

					break;
				}
				case NINETY: {

					StringIdChatParameter body("gambling/default_interface","prose_starting_in");
					body.setDI(90);

					notifyAll(&body);

					break;
				}
				case SIXTY: {

					StringIdChatParameter body("gambling/default_interface","prose_starting_in");
					body.setDI(60);

					notifyAll(&body);

					break;
				}
				case THIRTY: {

					StringIdChatParameter body("gambling/default_interface","prose_starting_in");
					body.setDI(30);

					notifyAll(&body);

					break;
				}
				case TWENTY: {

					StringIdChatParameter body("gambling/default_interface","prose_starting_in");
					body.setDI(20);

					notifyAll(&body);

					break;
				}
				case FIFTEEN: {

					StringIdChatParameter body("gambling/default_interface","prose_starting_in");
					body.setDI(15);

					notifyAll(&body);

					break;
				}
				case TEN: {

					StringIdChatParameter body("gambling/default_interface","prose_starting_in");
					body.setDI(10);

					notifyAll(&body);

					break;
				}
				case FIVE: {

					StringIdChatParameter body("gambling/default_interface","prose_starting_in");
					body.setDI(5);

					notifyAll(&body);

					break;
				}
				case WHEELSTART: {

					StringIdChatParameter body("gambling/default_interface","wheel_spin");
					notifyAll(&body);

					break;
				}
				case WHEELBEGINSLOW: {

					StringIdChatParameter body("gambling/default_interface","wheel_begin_slow");
					notifyAll(&body);

					break;
				}
				case WHEELSLOW: {

					first = System::random(37);

					StringIdChatParameter body("gambling/default_interface","prose_wheel_slow");
					body.setTT(gamblingManager->getRoulette()->get(first));

					String terminalName;
					_this.getReferenceUnsafeStaticCast()->getObjectName()->getFullPath(terminalName);
					body.setTO(terminalName);

					notifyAll(&body);

					break;
				}
				case WHEELSTOP: {

					int random = System::random(1);

					if (random == 0) {

						StringIdChatParameter body("gambling/default_interface","prose_result_same");
						body.setTT(gamblingManager->getRoulette()->get(first));

						String terminalName;
						_this.getReferenceUnsafeStaticCast()->getObjectName()->getFullPath(terminalName);

						body.setTO(terminalName);

						notifyAll(&body);

					} else {

						first = System::random(37);

						StringIdChatParameter body("gambling/default_interface","prose_result_change");
						body.setTT(gamblingManager->getRoulette()->get(first));

						String terminalName;
						_this.getReferenceUnsafeStaticCast()->getObjectName()->getFullPath(terminalName);

						body.setTO(terminalName);

						notifyAll(&body);
					}

					break;
				}
			}

			break;
		}
	}
}

void GamblingTerminalImplementation::notifyAll(StringIdChatParameter* text) {
	for (int i = 0; i < playersWindows.size(); ++i) {
		playersWindows.elementAt(i).getKey()->sendSystemMessage(*text);
	}
}

void GamblingTerminalImplementation::notifyOthers(CreatureObject* player, StringIdChatParameter* text) {
	if (player != nullptr) {
		for (int i = 0; i < playersWindows.size(); ++i) {
			if (playersWindows.elementAt(i).getKey() != player) {
				playersWindows.elementAt(i).getKey()->sendSystemMessage(*text);
			}
		}
	} else {
		notifyAll(text);
	}
}
