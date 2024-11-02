/*
 * StarshipPaintKitObjectMenuComponent.h
 *
 *  Created on: 11/2/2024
 *      Author: Halyn
 */

#include "StarshipPaintKitObjectMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/ZoneServer.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/ShipPrimaryPaintSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/ShipSecondaryPaintSuiCallback.h"

void StarshipPaintKitObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);

	if (tano == nullptr)
		return;

	if (sceneObject->isASubChildOf(player)) {
		menuResponse->addRadialMenuItem(RadialOptions::SERVER_MENU1, 3, "@sui:set_color");
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_MENU1, RadialOptions::SERVER_MENU2, 3, "@sui:color_ship_one");
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_MENU1, RadialOptions::SERVER_MENU3, 3, "@sui:color_ship_two");
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int StarshipPaintKitObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {

	if (player == nullptr)
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (!sceneObject->isTangibleObject())
		return 0;

	if ((selectedID != RadialOptions::SERVER_MENU2) && (selectedID != RadialOptions::SERVER_MENU3))
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

	ManagedReference<TangibleObject*> kitTano = cast<TangibleObject*>(sceneObject);

	if (kitTano == nullptr)
		return 0;

	ZoneServer* server = player->getZoneServer();

	if (server != nullptr) {

		//Configure SUI box
		ManagedReference<SuiListBox*> sui = new SuiListBox(player, SuiWindowType::SHIP_TEXTURE_SELECT);

		if (selectedID == RadialOptions::SERVER_MENU2)
			sui->setCallback(new ShipPrimaryPaintSuiCallback(server));
		else
			sui->setCallback(new ShipSecondaryPaintSuiCallback(server));

		sui->setPromptTitle("@color_kit:pick_a_ship_title");
		sui->setPromptText("@color_kit:pick_a_ship");
		sui->setUsingObject(kitTano);
		sui->setOkButton(true, "@color_kit:btn_color");

		//Populate SUI box with listed ships
		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

		if (datapad == nullptr)
			return 0;

		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();
			if (obj == nullptr || !obj->isShipControlDevice())
				continue;

			ShipControlDevice* controlDevice = cast<ShipControlDevice*>(obj.get());
			if (controlDevice == nullptr)
				continue;

			Reference<SceneObject*> ship = controlDevice->getControlledObject();
			if (ship == nullptr || !ship->isShipObject())
				continue;

			sui->addMenuItem(obj->getDisplayedName(), ship->getObjectID());
		}

		//Send to player.
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost != nullptr) {
			ghost->addSuiBox(sui);
			player->sendMessage(sui->generateMessage());
		}
	}
	return 0;
}
