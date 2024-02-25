/*
 * StarshipTextureKitObjectMenuComponent.h
 *
 *  Created on: 6/4/2023
 *      Author: Halyn
 */

#include "StarshipTextureKitObjectMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/ZoneServer.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/ShipTextureSuiCallback.h"

void StarshipTextureKitObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);

	if (tano == nullptr)
		return;

	menuResponse->addRadialMenuItem(20, 3, "@texture_kit:btn_texture");

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int StarshipTextureKitObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {

	if (player == nullptr)
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (selectedID != 20)
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

	if (!sceneObject->isTangibleObject())
		return 0;

	ManagedReference<TangibleObject*> kitTano = cast<TangibleObject*>(sceneObject);

	if (kitTano == nullptr)
		return 0;

	ZoneServer* server = player->getZoneServer();

	if (server != nullptr) {

		//Configure SUI box
		ManagedReference<SuiListBox*> sui = new SuiListBox(player, SuiWindowType::SHIP_TEXTURE_SELECT);
		sui->setCallback(new ShipTextureSuiCallback(server));
		sui->setPromptTitle("@texture_kit:pick_a_ship_title");
		sui->setPromptText("@texture_kit:pick_a_ship");
		sui->setUsingObject(kitTano);
		sui->setOkButton(true, "@ok");

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
