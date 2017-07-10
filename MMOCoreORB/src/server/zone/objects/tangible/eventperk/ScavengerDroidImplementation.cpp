#include "server/zone/objects/tangible/eventperk/ScavengerDroid.h"
#include "server/zone/Zone.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "templates/tangible/EventPerkDeedTemplate.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"

void ScavengerDroidImplementation::updatePlayerScore(CreatureObject* player) {
	int playerScore = getTurnedInItemListSize(player->getObjectID());

	if (playerScore == getItemListSize()) {
		gameEndTime.updateToCurrentTime();

		currentWinner = player;
		player->sendSystemMessage("@event_perk:scavenger_you_win");
		announceToPlayers("scavenger_winner");
		gameStatus = GAMEENDED;
		return;
	}
	int leaderScore = 0;

	ManagedReference<CreatureObject*> curWinner = currentWinner.get();

	if (curWinner != NULL)
		leaderScore = getTurnedInItemListSize(curWinner->getObjectID());

	if (curWinner == NULL || curWinner == player || playerScore >= leaderScore) {
		player->sendSystemMessage("@event_perk:scavenger_you_lead");
		currentWinner = player;
	} else {
		StringIdChatParameter msg("event_perk", "scavenger_not_leader");
		msg.setTO(curWinner->getDisplayedName());
		player->sendSystemMessage(msg);
	}
}

void ScavengerDroidImplementation::announceToPlayers(const String& message) {
	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	zone->getInRangeObjects(getPositionX(), getPositionY(), 256, &closeObjects,	true);

	for (int i = 0; i < closeObjects.size(); i++) {
		SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());
		if (targetObject != NULL && targetObject->isPlayerCreature()) {
			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(targetObject);

			if (player != NULL)
				player->sendSystemMessage("@event_perk:" + message);
		}
	}
}

void ScavengerDroidImplementation::addToPlayerItemList(uint64 playerID, const String& item) {
	if (!turnedInItemList.contains(playerID))
		turnedInItemList.put(playerID, Vector<String>());

	turnedInItemList.get(playerID).add(item);
}

int ScavengerDroidImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	ManagedReference<CreatureObject*> perkOwner = getDeedOwner();

	bool isOwner = perkOwner != NULL && player == perkOwner;


	if (gameStatus == GAMESETUP && isOwner) {
		if (selectedID == 132) {
			sendSetupInstructionsSUI(player);
		} else if (selectedID == 133) {
			sendItemListSUI(player);
		} else if (selectedID == 134) {
			player->sendSystemMessage("@event_perk:scavenger_list_reset_msg");
			clearItemList();
		} else if (selectedID == 135) {
			startGame(player);
		}
	} else if (gameStatus == GAMESTARTED) {
		if (selectedID == 132) {
			sendGameInstructionsSUI(player);
		} else if (selectedID == 133) {
			sendItemListSUI(player);
		} else if (selectedID == 136) {
			StringIdChatParameter msg("event_perk", "scavenger_show_current_leader");

			ManagedReference<CreatureObject*> curWinner = currentWinner.get();

			if (curWinner == NULL)
				msg.setTO("Nobody");
			else
				msg.setTO(curWinner->getDisplayedName());
			player->sendSystemMessage(msg);
		}
	} else if (gameStatus == GAMEENDED) {
		if (selectedID == 136) {
			StringIdChatParameter msg("event_perk", "scavenger_show_leader");

			ManagedReference<CreatureObject*> curWinner = currentWinner.get();

			int timeMins = (gameEndTime.getMiliTime() - gameStartTime.getMiliTime()) / 60000;

			if (curWinner != NULL)
				msg.setTO(curWinner->getDisplayedName());
			else
				msg.setTO("Unknown");

			msg.setDI(timeMins);
			player->sendSystemMessage(msg);
		}
	}

	if (selectedID == 137 && (isOwner || (player->getPlayerObject() != NULL && player->getPlayerObject()->isPrivileged()))) {
		EventPerkDataComponent* data = cast<EventPerkDataComponent*>(getDataObjectComponent()->get());

		if (data == NULL) {
			player->sendSystemMessage("Error: no dataObjectComponent.");
			return 1;
		}

		EventPerkDeed* deed = data->getDeed();

		if (deed == NULL) {
			player->sendSystemMessage("Error: deed is NULL.");
			return 1;
		}

		Time currentTime;
		uint32 timeDelta = currentTime.getMiliTime() - deed->getPurchaseTime()->getMiliTime();
		uint32 minutes = (EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta) / 60000;

		StringIdChatParameter params("event_perk", "show_exp_time"); // This rental will expire in approximately %DI minutes.
		params.setDI(minutes);
		player->sendSystemMessage(params);
		return 0;
	}

	return 0;
}

void ScavengerDroidImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ManagedReference<CreatureObject*> perkOwner = getDeedOwner();

	if (perkOwner == NULL)
		return;

	if (gameStatus == GAMESETUP && perkOwner == player) {
		menuResponse->addRadialMenuItem(132, 3, "@event_perk:scavenger_instruction"); // Instructions
		menuResponse->addRadialMenuItem(133, 3, "@event_perk:scavenger_list_items"); // View Item List
		menuResponse->addRadialMenuItem(134, 3, "@event_perk:scavenger_reset_list"); // Reset List
		menuResponse->addRadialMenuItem(135, 3, "@event_perk:scavenger_start"); // Start Game
	} else if (gameStatus == GAMESTARTED) {
		menuResponse->addRadialMenuItem(132, 3, "@event_perk:scavenger_instruction"); // Instructions
		menuResponse->addRadialMenuItem(133, 3, "@event_perk:scavenger_list_items"); // View Item List
		menuResponse->addRadialMenuItem(136, 3, "@event_perk:scavenger_list_leader"); // Show Current Leader
	} else if (gameStatus == GAMEENDED) {
		menuResponse->addRadialMenuItem(136, 3, "@event_perk:scavenger_show_winner"); // Display Winner
	}

	if (perkOwner == player || (player->getPlayerObject() != NULL && player->getPlayerObject()->isPrivileged()))
		menuResponse->addRadialMenuItem(137, 3, "@event_perk:mnu_show_exp_time"); // Show Expiration Time
}

void ScavengerDroidImplementation::startGame(CreatureObject* player) {
	if (gameStatus == GAMESTARTED || gameStatus == GAMEENDED)
		return;

	if (getItemListSize() == 0) {
		player->sendSystemMessage("@event_perk:scavenger_no_items");
		return;
	}

	gameStartTime.updateToCurrentTime();
	gameStatus = GAMESTARTED;
	announceToPlayers("scavenger_game_start");
}

void ScavengerDroidImplementation::sendItemListSUI(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (itemList.size() == 0) {
		player->sendSystemMessage("@event_perk:scavenger_no_items");
		return;
	}

	ManagedReference<SuiListBox*> listbox = new SuiListBox(player, SuiWindowType::SCAVENGER_ITEM_LIST);
	listbox->setPromptTitle("@event_perk:scavenger_list_t"); // Scavenger Hunt List
	listbox->setPromptText("@event_perk:scavenger_list_d"); // Below you will find the list of items you need to find for the scavenger hunt. Good luck!
	listbox->setUsingObject(_this.getReferenceUnsafeStaticCast());
	listbox->setForceCloseDistance(32.f);
	listbox->setCancelButton(true, "@cancel");

	for (int i = 0; i < itemList.size(); i++) {
		String itemTemplate = itemList.get(i);
		listbox->addMenuItem(TemplateManager::instance()->getTemplate(itemTemplate.hashCode())->getObjectName());
	}

	ghost->addSuiBox(listbox);
	player->sendMessage(listbox->generateMessage());
}

void ScavengerDroidImplementation::sendSetupInstructionsSUI(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiMessageBox*> msgBox = new SuiMessageBox(player, SuiWindowType::SCAVENGER_INFO);
	msgBox->setPromptTitle("@event_perk:scavenger_instruction"); // Instructions
	msgBox->setPromptText("@event_perk:scavenger_setup_instruction"); // Drag and drop items onto me so I can look at them and I will add them to the scavenger hunt list. You can look at the items you've added by selecting "View List". If you've made a mistake, select "Reset" to start again. When you are ready, choose "Start Game" to begin.
	msgBox->setUsingObject(_this.getReferenceUnsafeStaticCast());
	msgBox->setForceCloseDistance(32.f);

	ghost->addSuiBox(msgBox);
	player->sendMessage(msgBox->generateMessage());
}

void ScavengerDroidImplementation::sendGameInstructionsSUI(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiMessageBox*> msgBox = new SuiMessageBox(player, SuiWindowType::SCAVENGER_INFO);
	msgBox->setPromptTitle("@event_perk:scavenger_instruction"); // Instructions
	msgBox->setPromptText("@event_perk:scavenger_game_instruction"); // Choose "View Item List" to see what items you need to find. As you find items, show me the item by dragging and dropping them onto me. The first person to find all of the items wins!
	msgBox->setUsingObject(_this.getReferenceUnsafeStaticCast());
	msgBox->setForceCloseDistance(32.f);

	ghost->addSuiBox(msgBox);
	player->sendMessage(msgBox->generateMessage());
}

CreatureObject* ScavengerDroidImplementation::getDeedOwner() {
	EventPerkDataComponent* gameData = cast<EventPerkDataComponent*>(getDataObjectComponent()->get());

	if (gameData == NULL) {
		return NULL;
	}

	ManagedReference<EventPerkDeed*> deed = gameData->getDeed();

	if (deed == NULL) {
		return NULL;
	}

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	return owner;
}

bool ScavengerDroidImplementation::hasItemInPlayerItemList(uint64 playerID, const String& item) {
	if (!turnedInItemList.contains(playerID))
		return false;

	return turnedInItemList.get(playerID).contains(item);
}

int ScavengerDroidImplementation::getTurnedInItemListSize(uint64 playerID) {
	if (!turnedInItemList.contains(playerID))
		return 0;

	return turnedInItemList.get(playerID).size();
}
