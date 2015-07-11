#include "server/zone/objects/tangible/components/FlagGameMenuComponent.h"
#include "server/zone/objects/tangible/components/FlagGameDataComponent.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/objects/tangible/components/EventPerkMenuComponent.h"
#include "server/zone/templates/tangible/EventPerkDeedTemplate.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/tangible/eventperk/FlagGame.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/chat/StringIdChatParameter.h"

void FlagGameMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	FlagGameDataComponent* data = cast<FlagGameDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == NULL) {
		player->sendSystemMessage("Error: no dataObjectComponent.");
		return;
	}

	FlagGame* flagGame = data->getFlagGame();

	if (flagGame == NULL)
		return;

	EventPerkDataComponent* gameData = cast<EventPerkDataComponent*>(flagGame->getDataObjectComponent()->get());

	if (gameData == NULL) {
		player->sendSystemMessage("Error: no dataObjectComponent.");
		return;
	}

	EventPerkDeed* deed = gameData->getDeed();

	if (deed == NULL) {
		player->sendSystemMessage("Error: deed is NULL.");
		return;
	}

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	if (flagGame->isGameStarted()) {
		if (flagGame->canUseFlag(player)) {
			menuResponse->addRadialMenuItem(75, 3, "@event_perk:flag_game_capture_flag");
		}
	} else {
		if (owner != NULL && owner == player) {
			menuResponse->addRadialMenuItem(68, 3, "@event_perk:flag_game_set_time_root");
			menuResponse->addRadialMenuItemToRadialID(68, 69, 3, "@event_perk:flag_game_set_time_10");
			menuResponse->addRadialMenuItemToRadialID(68, 70, 3, "@event_perk:flag_game_set_time_20");
			menuResponse->addRadialMenuItemToRadialID(68, 71, 3, "@event_perk:flag_game_set_time_30");
			menuResponse->addRadialMenuItemToRadialID(68, 72, 3, "@event_perk:flag_game_set_time_45");
			menuResponse->addRadialMenuItemToRadialID(68, 73, 3, "@event_perk:flag_game_set_time_60");
			menuResponse->addRadialMenuItemToRadialID(68, 74, 3, "@event_perk:flag_game_start");
			menuResponse->addRadialMenuItem(132, 3, "@event_perk:mnu_show_exp_time"); // Show Expiration Time
			menuResponse->addRadialMenuItem(128, 3, "@event_perk:mnu_redeed"); // Reclaim Rental Deed
		}
	}
	if (flagGame->isGameEnded()) {
		menuResponse->addRadialMenuItem(76, 3, "@event_perk:flag_game_show_scores");
	}
}

int FlagGameMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

	FlagGameDataComponent* data = cast<FlagGameDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == NULL) {
		player->sendSystemMessage("Error: no dataObjectComponent.");
		return 1;
	}

	FlagGame* flagGame = data->getFlagGame();

	if (flagGame == NULL)
		return 1;

	EventPerkDataComponent* gameData = cast<EventPerkDataComponent*>(flagGame->getDataObjectComponent()->get());

	if (gameData == NULL) {
		player->sendSystemMessage("Error: no dataObjectComponent.");
		return 1;
	}

	EventPerkDeed* deed = gameData->getDeed();

	if (deed == NULL) {
		player->sendSystemMessage("Error: deed is NULL.");
		return 1;
	}

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	Locker locker(flagGame);

	if (player == owner) {
		switch (selectedID) {
		case 74:
			flagGame->startGame();
			return 0;
		case 69:
			flagGame->setTimeLimit(10 * 60 * 1000); // 10 Minutes
			player->sendSystemMessage("@event_perk:flag_game_set_time_10");
			return 0;
		case 70:
			flagGame->setTimeLimit(20 * 60 * 1000); // 20 Minutes
			player->sendSystemMessage("@event_perk:flag_game_set_time_20");
			return 0;
		case 71:
			flagGame->setTimeLimit(30 * 60 * 1000); // 30 Minutes
			player->sendSystemMessage("@event_perk:flag_game_set_time_30");
			return 0;
		case 72:
			flagGame->setTimeLimit(45 * 60 * 1000); // 45 Minutes
			player->sendSystemMessage("@event_perk:flag_game_set_time_45");
			return 0;
		case 73:
			flagGame->setTimeLimit(60 * 60 * 1000); // 60 Minutes
			player->sendSystemMessage("@event_perk:flag_game_set_time_60");
			return 0;
		default:
			break;
		}
	}

	if (selectedID == 75) {
		flagGame->tryFlagChange(player);
		return 0;
	} else if (selectedID == 76) {
		flagGame->showScores(player);
		return 0;
	} else if (selectedID == 132) {
		Time currentTime;
		uint32 timeDelta = currentTime.getMiliTime() - deed->getPurchaseTime()->getMiliTime();
		uint32 minutes = (EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta) / 60000;

		StringIdChatParameter params("event_perk", "show_exp_time"); // This rental will expire in approximately %DI minutes.
		params.setDI(minutes);
		player->sendSystemMessage(params);
		return 0;
	} else if (selectedID == 128) {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		PlayerObject* ghost = player->getPlayerObject();

		if (inventory == NULL || inventory->isContainerFull()) {
			player->sendSystemMessage("@event_perk:redeed_failed"); // The rental could not be re-deeded.
			return 1;
		}

		if (ghost == NULL || ghost->getEventPerkCount() > 5) {
			player->sendSystemMessage("@event_perk:redeed_too_many_deeds"); // You have too many rental deeds in your possession and cannot redeed this rental.
			return 1;
		}

		flagGame->destroyObjectFromWorld(true);
		locker.release();

		Locker deedLocker(deed);
		deed->sendTo(player, true);
		inventory->transferObject(deed, -1, true);
		deed->setGenerated(false);

		player->sendSystemMessage("@event_perk:redeed_success"); // Your Rental has been removed and the deed reclaimed.
		return 0;
	}

	return 0;
}
