/*
* EventPerkActorMenuComponent.cpp
*
* 2024-04-23
* By: Hakry
*
*/


#include "server/zone/objects/tangible/components/EventPerkActorMenuComponent.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/EventPerkDeedTemplate.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/player/sessions/vendor/VendorAdBarkingSession.h"

void EventPerkActorMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == nullptr || player == nullptr) {
		return;
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	auto zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	const ContainerPermissions* permissions = sceneObject->getContainerPermissions();

	if (permissions == nullptr) {
		return;
	}

	uint64 parentID = permissions->getOwnerID();
	auto parentPerk = zoneServer->getObject(parentID);

	if (parentPerk == nullptr) {
		return;
	}

	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(parentPerk->getDataObjectComponent()->get());

	if (data == nullptr) {
		return;
	}

	EventPerkDeed* deed = data->getDeed();

	if (deed == nullptr) {
		return;
	}

	auto owner = deed->getOwner().get();

	if (owner == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return;
	}

	bool privilegedAccess = ghost->isPrivileged();

	if (!privilegedAccess && owner->getObjectID() != player->getObjectID()) {
		return;
	}

	// Vendor Data for Performance
	DataObjectComponentReference* vendorDataRef = sceneObject->getDataObjectComponent();

	if (vendorDataRef == nullptr || vendorDataRef->get() == nullptr || !vendorDataRef->get()->isVendorData()) {
		return;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(vendorDataRef->get());

	if (vendorData == nullptr) {
		return;
	}

	// Main Menu
	menuResponse->addRadialMenuItem(RadialOptions::SERVER_MENU1, 3, "@event_perk_npc_actor:actor_control"); // "Control Actor"

	if (!vendorData->isAdBarkingEnabled()) {
		// Enable Actor Performance
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_MENU1, RadialOptions::SERVER_MENU2, 3, "@event_perk_npc_actor:actor_areabarks_on");
	} else {
		// Disable Actor Performance
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_MENU1, RadialOptions::SERVER_MENU2, 3, "@event_perk_npc_actor:actor_areabarks_off");
	}

	// Customize Clothing
	menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_MENU1, RadialOptions::SERVER_MENU3, 3, "@event_perk_npc_actor:customize_actor");

	// Show Expiration Time
	menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_MENU1, RadialOptions::SERVER_MENU4, 3, "@event_perk:mnu_show_exp_time");

	// Reclaim Rental Deed
	menuResponse->addRadialMenuItem(RadialOptions::SERVER_MENU5, 3, "@event_perk:mnu_redeed");

	if (privilegedAccess) {
		menuResponse->addRadialMenuItem(RadialOptions::SERVER_OBSERVE, 3, "Display Perk Component");
	}
}

int EventPerkActorMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || player == nullptr || !sceneObject->isAiAgent()) {
		return 1;
	}

	auto actorAgent = sceneObject->asAiAgent();

	if (actorAgent == nullptr) {
		return 1;
	}

	auto zoneServer = actorAgent->getZoneServer();

	if (zoneServer == nullptr) {
		return 1;
	}

	const ContainerPermissions* permissions = sceneObject->getContainerPermissions();

	if (permissions == nullptr) {
		return 1;
	}

	uint64 parentID = permissions->getOwnerID();

	auto parentPerk = zoneServer->getObject(parentID);

	if (parentPerk == nullptr) {
		return 1;
	}

	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(parentPerk->getDataObjectComponent()->get());

	if (data == nullptr) {
		return 1;
	}

	auto deed = data->getDeed();

	if (deed == nullptr) {
		return 1;
	}

	// Vendor Data for Performance
	DataObjectComponentReference* vendorDataRef = sceneObject->getDataObjectComponent();

	if (vendorDataRef == nullptr || vendorDataRef->get() == nullptr || !vendorDataRef->get()->isVendorData()) {
		return 1;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(vendorDataRef->get());

	if (vendorData == nullptr) {
		return 1;
	}

	// Face the actor to the player
	actorAgent->faceObject(player, true);

	switch(selectedID) {
		// Main Menu
		case(RadialOptions::SERVER_MENU1):
			return 0;
		// Toggle Performance
		case(RadialOptions::SERVER_MENU2): {
			if (vendorData->isAdBarkingEnabled()) {
				vendorData->setAdBarking(false);
				player->sendSystemMessage("@event_perk_npc_actor:areabarks_disabled"); // The actor will no longer perform.
			} else {
				if (player->containsActiveSession(SessionFacadeType::VENDORADBARKING)) {
					return 0;
				}

				ManagedReference<VendorAdBarkingSession*> adBarkSession = new VendorAdBarkingSession(player, actorAgent);

				if (adBarkSession == nullptr) {
					return 0;
				}

				adBarkSession->initializeSession();
			}

			return 0;
		}
		// Request to customize clothing
		case(RadialOptions::SERVER_MENU3): {

			auto chatManager = zoneServer->getChatManager();

			if (chatManager == nullptr) {
				return 1;
			}

			int species = actorAgent->getSpecies();

			if (species == CreatureObject::ITHORIAN) {
				chatManager->broadcastChatMessage(actorAgent, "@event_perk_npc_actor:wear_no_ithorian", 0, 0, chatManager->getMoodID("stubborn"));
				actorAgent->doAnimation("wave_on_dismissing");
			} else {
				chatManager->broadcastChatMessage(actorAgent, "@event_perk_npc_actor:wear_how", 0, 0, chatManager->getMoodID("cheerful"));
				actorAgent->doAnimation("slow_down");
			}

			return 0;
		}
		case(RadialOptions::SERVER_MENU4): {
			Time* purchaseTime = deed->getPurchaseTime();

			if (purchaseTime == nullptr) {
				return 1;
			}

			Time currentTime;
			uint64 timeDelta = currentTime.getMiliTime() - purchaseTime->getMiliTime();

			uint64 minutes = (EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta) / 60000;

			StringIdChatParameter params("event_perk", "show_exp_time"); // This rental will expire in approximately %DI minutes.
			params.setDI(minutes);

			// Send message to player
			player->sendSystemMessage(params);

			return 0;
		}
		// Reclaim Deed
		case(RadialOptions::SERVER_MENU5): {
			ManagedReference<SceneObject*> inventory = player->getInventory();

			if (inventory == nullptr || inventory->isContainerFullRecursive()) {
				player->sendSystemMessage("@event_perk:redeed_failed"); // The rental could not be re-deeded.
				return 1;
			}

			auto ghost = player->getPlayerObject();

			if (ghost == nullptr || (!ghost->isPrivileged() && ghost->getEventPerkCount() > 5)) {
				player->sendSystemMessage("@event_perk:redeed_too_many_deeds"); // You have too many rental deeds in your possession and cannot redeed this rental.
				return 1;
			}

			if (!inventory->transferObject(deed, -1, true)) {
				deed->destroyObjectFromWorld(true);
				deed->destroyObjectFromDatabase(true);
			}

			deed->sendTo(player, true);
			deed->setGenerated(false);

			// Destroy the perk from the zone
			ManagedReference<TangibleObject*> perkTano = deed->getGeneratedObject().get();

			if (perkTano != nullptr) {
				Locker perkLock(perkTano, actorAgent);

				perkTano->destroyChildObjects();
				perkTano->destroyObjectFromWorld(true);
			}

			 // Your Rental has been removed and the deed reclaimed.
			player->sendSystemMessage("@event_perk:redeed_success");

			return 0;
		}
		case (RadialOptions::SERVER_OBSERVE): {
			ManagedReference<TangibleObject*> perkTano = parentPerk->asTangibleObject();

			if (perkTano == nullptr) {
				return 1;
			}

			Locker perClock(perkTano, sceneObject);

			if (!perkTano->isInvisible()) {
				perkTano->setInvisible(true);
				sceneObject->broadcastDestroy(perkTano, false);
			} else {
				perkTano->setInvisible(false);
				sceneObject->broadcastObject(perkTano, false);
			}

			return 0;
		}
		default:
			break;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
