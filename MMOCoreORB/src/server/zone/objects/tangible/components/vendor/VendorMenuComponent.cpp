/*
 * VendorMenuComponent.cpp
 *
 *  Created on: 5/27/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "VendorMenuComponent.h"
#include "server/zone/objects/scene/components/DataObjectComponentReference.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sessions/vendor/VendorAdBarkingSession.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/ZoneProcessServer.h"

void VendorMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if(!sceneObject->isVendor())
		return;

	if(sceneObject->isASubChildOf(player)) {
		menuResponse->addRadialMenuItem(14, 3, "@ui:destroy");
		return;
	}

	PlayerObject* playerObject = player->getPlayerObject();

	if (playerObject == NULL)
		return;

	DataObjectComponentReference* data = sceneObject->getDataObjectComponent();
	if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
		return;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
	if(vendorData == NULL) {
		return;
	}

	bool owner = vendorData->getOwnerId() == player->getObjectID();

	if(!owner && !playerObject->isPrivileged())
		return;

	menuResponse->addRadialMenuItem(70, 3, "@player_structure:vendor_control");

	if (!owner) {
		if (vendorData->isInitialized()) {
			menuResponse->addRadialMenuItemToRadialID(70, 71, 3, "@player_structure:vendor_status");
			menuResponse->addRadialMenuItemToRadialID(70, 72, 3, "@player_structure:change_name");
		}

		return;
	}

	if (!vendorData->isInitialized()) {

		menuResponse->addRadialMenuItemToRadialID(70, 79, 3, "@player_structure:vendor_init");

		menuResponse->addRadialMenuItem(10, 3, "@ui_radial:item_pickup");

		menuResponse->addRadialMenuItem(51, 1, "@ui_radial:item_rotate"); //Rotate
		menuResponse->addRadialMenuItemToRadialID(51, 52, 3, "@ui_radial:item_rotate_left"); //Rotate Left
		menuResponse->addRadialMenuItemToRadialID(51, 53, 3, "@ui_radial:item_rotate_right"); //Rotate Right

	} else {

		menuResponse->addRadialMenuItemToRadialID(70, 71, 3, "@player_structure:vendor_status");

		menuResponse->addRadialMenuItemToRadialID(70, 73, 3, "@player_structure:pay_vendor_t");
		menuResponse->addRadialMenuItemToRadialID(70, 74, 3, "@player_structure:withdraw_vendor_t");

		if (vendorData->isVendorSearchEnabled())
			menuResponse->addRadialMenuItemToRadialID(70, 75, 3, "@player_structure:disable_vendor_search");
		else if (!vendorData->isOnStrike())
			menuResponse->addRadialMenuItemToRadialID(70, 75, 3, "@player_structure:enable_vendor_search");

		if (player->hasSkill("crafting_merchant_advertising_03")) {
			if (vendorData->isRegistered())
				menuResponse->addRadialMenuItemToRadialID(70, 76, 3, "@player_structure:unregister_vendor");
			else if (!vendorData->isOnStrike())
				menuResponse->addRadialMenuItemToRadialID(70, 76, 3, "@player_structure:register_vendor");
		}

		if (player->hasSkill("crafting_merchant_advertising_01") && sceneObject->isCreatureObject()) {
			if (!vendorData->isAdBarkingEnabled())
				menuResponse->addRadialMenuItemToRadialID(70, 77, 3, "@player_structure:vendor_areabarks_on");
			else
				menuResponse->addRadialMenuItemToRadialID(70, 77, 3, "@player_structure:vendor_areabarks_off");
		}
	}

	menuResponse->addRadialMenuItemToRadialID(70, 78, 3, "@player_structure:remove_vendor");
}

int VendorMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) const {

	if (!sceneObject->isVendor())
		return 0;

	DataObjectComponentReference* data = sceneObject->getDataObjectComponent();
	if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
		return 0;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
	if(vendorData == NULL) {
		return 0;
	}

	ManagedReference<TangibleObject*> vendor = cast<TangibleObject*>(sceneObject);
	if(vendor == NULL)
		return 0;

	bool owner = vendorData->getOwnerId() == player->getObjectID();

	if(!owner) {
		if (player->getPlayerObject()->isPrivileged()) {
			if (selectedID == 71) {
				VendorManager::instance()->handleDisplayStatus(player, vendor);
				return 0;
			} else if (selectedID == 72) {
				VendorManager::instance()->promptRenameVendorTo(player, vendor);
				return 0;
			}
		}

		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
	}

	switch (selectedID) {
	case 71: {
		VendorManager::instance()->handleDisplayStatus(player, vendor);
		return 0;
	}

	case 73: {
		vendorData->payMaintanence();
		return 0;
	}

	case 74: {
		vendorData->withdrawMaintanence();
		return 0;
	}

	case 75: {
		if (vendorData->isVendorSearchEnabled()) {
			vendorData->setVendorSearchEnabled(false);
			player->sendSystemMessage("@player_structure:vendor_search_disabled");
		} else if (!vendorData->isOnStrike()) {
			vendorData->setVendorSearchEnabled(true);
			player->sendSystemMessage("@player_structure:vendor_search_enabled");
		}

		return 0;
	}

	case 76: {
		if(player->hasSkill("crafting_merchant_advertising_03")) {
			if (vendorData->isRegistered())
				VendorManager::instance()->handleUnregisterVendor(player, vendor);
			else if (!vendorData->isOnStrike())
				VendorManager::instance()->sendRegisterVendorTo(player, vendor);
		}
		return 0;
	}

	case 77: {
		if(player->hasSkill("crafting_merchant_advertising_01") && vendor->isCreatureObject()) {
			if (!vendorData->isAdBarkingEnabled()) {

				if (player->containsActiveSession(SessionFacadeType::VENDORADBARKING)) {
					return 0;
				}

				ManagedReference<VendorAdBarkingSession*> session = new VendorAdBarkingSession(player, sceneObject);
				session->initializeSession();

			} else {
				vendorData->setAdBarking(false);
				player->sendSystemMessage("@player_structure:areabarks_disabled");
			}
		}
		return 0;
	}

	case 78: {
		VendorManager::instance()->promptDestroyVendor(player, vendor);
		return 0;
	}


	case 79: {
		if (player->getRootParent() != vendor->getRootParent()) {
			player->sendSystemMessage("@player_structure:vendor_not_in_same_building");
			return 0;
		}

		if (vendorData->isInitialized()) {
			player->sendSystemMessage("@player_structure:vendor_already_initialized");
			return 0;
		}

		player->sendSystemMessage("@player_structure:vendor_initialized");
		vendorData->setInitialized(true);
		vendorData->setEmpty();
		vendorData->scheduleVendorCheckTask(VendorDataComponent::VENDORCHECKINTERVAL);
		return 0;
	}

	default:
		return 0;
	};

	return 0;
}
