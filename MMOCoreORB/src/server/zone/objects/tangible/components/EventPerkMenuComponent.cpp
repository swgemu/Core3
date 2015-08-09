
#include "server/zone/objects/tangible/components/EventPerkMenuComponent.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/EventPerkDeedTemplate.h"
#include "server/chat/StringIdChatParameter.h"

void EventPerkMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == NULL) {
		player->sendSystemMessage("Error: no dataObjectComponent.");
		return;
	}

	EventPerkDeed* deed = data->getDeed();

	if (deed == NULL) {
		player->sendSystemMessage("Error: deed is NULL.");
		return;
	}

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	if (owner == player) {
		menuResponse->addRadialMenuItem(132, 3, "@event_perk:mnu_show_exp_time"); // Show Expiration Time
		menuResponse->addRadialMenuItem(128, 3, "@event_perk:mnu_redeed"); // Reclaim Rental Deed

		menuResponse->addRadialMenuItem(51, 1, "@event_perk:mnu_rotate"); // Rotate
		menuResponse->addRadialMenuItemToRadialID(51, 52, 3, "@event_perk:mnu_rot_left"); // Rotate Left
		menuResponse->addRadialMenuItemToRadialID(51, 53, 3, "@event_perk:mnu_rot_right"); // Rotate Right
	} else if (player->getPlayerObject() != NULL && player->getPlayerObject()->isPrivileged()) {
		menuResponse->addRadialMenuItem(132, 3, "@event_perk:mnu_show_exp_time"); // Show Expiration Time
	}
}

int EventPerkMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == NULL) {
		player->sendSystemMessage("Error: no dataObjectComponent.");
		return 1;
	}

	EventPerkDeed* deed = data->getDeed();

	if (deed == NULL) {
		player->sendSystemMessage("Error: deed is NULL.");
		return 1;
	}

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL) {
		return 1;
	}

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	if (owner != player && !ghost->isPrivileged()) {
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
	}

	if (selectedID == 132) {
		Time currentTime;
		uint32 timeDelta = currentTime.getMiliTime() - deed->getPurchaseTime()->getMiliTime();
		uint32 minutes = (EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta) / 60000;

		StringIdChatParameter params("event_perk", "show_exp_time"); // This rental will expire in approximately %DI minutes.
		params.setDI(minutes);
		player->sendSystemMessage(params);
		return 0;
	}

	if (owner != player) {
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
	}

	if (selectedID == 128) {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		PlayerObject* ghost = player->getPlayerObject();

		if (inventory == NULL || inventory->isContainerFullRecursive()) {
			player->sendSystemMessage("@event_perk:redeed_failed"); // The rental could not be re-deeded.
			return 1;
		}

		if (ghost == NULL || ghost->getEventPerkCount() > 5) {
			player->sendSystemMessage("@event_perk:redeed_too_many_deeds"); // You have too many rental deeds in your possession and cannot redeed this rental.
			return 1;
		}

		deed->sendTo(player, true);
		inventory->transferObject(deed, -1, true);
		deed->setGenerated(false);
		sceneObject->destroyObjectFromWorld(true);

		player->sendSystemMessage("@event_perk:redeed_success"); // Your Rental has been removed and the deed reclaimed.
		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
