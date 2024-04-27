
#include "server/zone/objects/tangible/components/EventPerkMenuComponent.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/EventPerkDeedTemplate.h"
#include "server/chat/StringIdChatParameter.h"

void EventPerkMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (sceneObject->getGameObjectType() == SceneObjectType::EVENTPERK || data == nullptr) {
		auto permissions = sceneObject->getContainerPermissions();
		uint64 objectID = permissions->getOwnerID();

		Reference<SceneObject*> owner = Core::getObjectBroker()->lookUp(objectID).castTo<SceneObject*>();

		if (owner == nullptr) {
			error() << "Event Perk Owner is nullptr, destroying EventPerk ID: " << sceneObject->getObjectID();
			destroyEventPerk(sceneObject);

			return;
		}

		data = cast<EventPerkDataComponent*>(owner->getDataObjectComponent()->get());
	}

	if (data == nullptr) {
		error() << "Event Perk EventPerkDataComponent is nullptr, destroying EventPerk ID: " << sceneObject->getObjectID();
		destroyEventPerk(sceneObject);

		return;
	}

	EventPerkDeed* deed = data->getDeed();

	if (deed == nullptr) {
		error() << "Event Perk Deed is nullptr, destroying EventPerk ID: " << sceneObject->getObjectID();
		destroyEventPerk(sceneObject);

		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return;
	}

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	if (owner == nullptr) {
		return;
	}

	bool privilegedAccess = ghost->isPrivileged();

	if (!privilegedAccess && owner->getObjectID() != player->getObjectID()) {
		return;
	}

	menuResponse->addRadialMenuItem(RadialOptions::SERVER_MENU1, 3, "@event_perk:mnu_show_exp_time"); // Show Expiration Time
	menuResponse->addRadialMenuItem(RadialOptions::SERVER_MENU2, 3, "@event_perk:mnu_redeed"); // Reclaim Rental Deed

	if (deed->getPerkType() != EventPerkDeedTemplate::HONORGUARD && deed->getPerkType() != EventPerkDeedTemplate::RECRUITER) {
		menuResponse->addRadialMenuItem(RadialOptions::ITEM_ROTATE, 1, "@event_perk:mnu_rotate"); // Rotate
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::ITEM_ROTATE, RadialOptions::ITEM_ROTATE_RIGHT, 3, "@event_perk:mnu_rot_right"); // Rotate Right
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::ITEM_ROTATE, RadialOptions::ITEM_ROTATE_LEFT, 3, "@event_perk:mnu_rot_left"); // Rotate Left
	}
}

int EventPerkMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (sceneObject->getGameObjectType() == SceneObjectType::EVENTPERK || data == nullptr) {
		auto permissions = sceneObject->getContainerPermissions();
		uint64 objectID = permissions->getOwnerID();

		Reference<SceneObject*> owner = Core::getObjectBroker()->lookUp(objectID).castTo<SceneObject*>();

		data = cast<EventPerkDataComponent*>(owner->getDataObjectComponent()->get());
	}

	if (data == nullptr) {
		error() << "Event Perk EventPerkDataComponent is nullptr, destroying EventPerk ID: " << sceneObject->getObjectID();
		destroyEventPerk(sceneObject);

		return 1;
	}

	EventPerkDeed* deed = data->getDeed();

	if (deed == nullptr) {
		error() << "Event Perk Deed is nullptr, destroying EventPerk ID: " << sceneObject->getObjectID();
		destroyEventPerk(sceneObject);

		return 1;
	}

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return 1;
	}

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	if (owner != player && !ghost->isPrivileged()) {
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
	}

	if (selectedID == RadialOptions::SERVER_MENU1) {
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

	// Reclaim Deed
	if (selectedID == RadialOptions::SERVER_MENU2) {
		if (sceneObject->getGameObjectType() == SceneObjectType::SCAVENGERCHEST && sceneObject->getContainerObjectsSize() > 0) {
			player->sendSystemMessage("@event_perk:redeed_remove_items"); // The chest still contains items. You must empty the chest before it can be redeeded.
			return 1;
		}
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		PlayerObject* ghost = player->getPlayerObject();

		if (inventory == nullptr || inventory->isContainerFullRecursive()) {
			player->sendSystemMessage("@event_perk:redeed_failed"); // The rental could not be re-deeded.
			return 1;
		}

		if (ghost == nullptr || (!ghost->isPrivileged() && ghost->getEventPerkCount() > 5)) {
			player->sendSystemMessage("@event_perk:redeed_too_many_deeds"); // You have too many rental deeds in your possession and cannot redeed this rental.
			return 1;
		}

		deed->sendTo(player, true);
		inventory->transferObject(deed, -1, true);
		deed->setGenerated(false);

		ManagedReference<TangibleObject*> perkTano = deed->getGeneratedObject().get();

		if (perkTano != nullptr) {
			Locker perkLock(perkTano);

			perkTano->destroyChildObjects();
			perkTano->destroyObjectFromWorld(true);
		}

		player->sendSystemMessage("@event_perk:redeed_success"); // Your Rental has been removed and the deed reclaimed.

		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

void EventPerkMenuComponent::destroyEventPerk(SceneObject* sceneObject) const {
	sceneObject->destroyObjectFromWorld(true);
	sceneObject->destroyObjectFromDatabase(true);
}
