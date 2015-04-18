/*
 * VehicleCustomKitObjectMenuComponent.h
 *
 *  Created on: 9/22/2013
 *      Author: Klivian
 */

#include "VehicleCustomKitObjectMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/CustomVehicleSuiCallback.h"

void VehicleCustomKitObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if(!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int VehicleCustomKitObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

	if (player == NULL)
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (selectedID != 20)
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

	if(!sceneObject->isTangibleObject())
		return 0;

	ManagedReference<TangibleObject*> kitTano = cast<TangibleObject*>(sceneObject);
	if(kitTano == NULL)
		return 0;

	uint64 targetID = player->getTargetID();
	ZoneServer* server = player->getZoneServer();
	if (server == NULL)
		return 0;

	ManagedReference<TangibleObject*> target = server->getObject(targetID, true).castTo<TangibleObject*>();
	if (target == NULL || !target->isVehicleObject()) {
		player->sendSystemMessage("You can only use this tool to customize vehicle");
		return 0;
	}

	//permission check
	CreatureObject* vehicle = cast<CreatureObject*>(target.get());
	uint64 ownerID = vehicle->getCreatureLinkID();
	if ( ownerID != player->getObjectID()){
		bool hasConsent = false;

		ManagedReference<CreatureObject*> targetOwner = server->getObject(ownerID, true).castTo<CreatureObject*>();
		if (targetOwner != NULL)
		{
			Locker crossLock(targetOwner, player);
			ManagedReference<PlayerObject*> ghostOwner = targetOwner->getPlayerObject();
			for (int i = 0; i < ghostOwner->getConsentListSize(); ++i) {
				String entryName = ghostOwner->getConsentName(i);
				if (!entryName.isEmpty()){
					if (entryName == player->getFirstName().toLowerCase()){
						hasConsent = true;
					}
				}
			}
		}
		if (!hasConsent){
			player->sendSystemMessage("You require consent to customize another player's vehicle");
			return 0;
		}
	}
	//end permission check

	Locker clocker(vehicle, player);

	String appearanceFilename = target->getObjectTemplate()->getAppearanceFilename();
	VectorMap<String, Reference<CustomizationVariable*> > variables;
	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);
	int numPalette = 0;
	for(int i = 0; i< variables.size(); ++i)
	{
		String varkey = variables.elementAt(i).getKey();
		if (varkey.contains("color"))
		{
			++numPalette;
		}
	}

	if (numPalette == 0) {
		player->sendSystemMessage("No customization options available on this vehicle");//jetpack
		return 0;
	}

	VehicleObject* painted = cast<VehicleObject*>(vehicle);
	if (painted != NULL){
		painted->refreshPaint();
	}

	ManagedReference<SuiListBox*> frameTrimSelector = new SuiListBox(player, SuiWindowType::CUSTOMIZE_KIT);
	frameTrimSelector->setUsingObject(player);
	frameTrimSelector->setCallback(new CustomVehicleSuiCallback(server, numPalette, kitTano ));
	frameTrimSelector->setUsingObject(target);
	frameTrimSelector->setPromptTitle("Customize");
	frameTrimSelector->setPromptText("Please select the customization action you would like to take");

	frameTrimSelector->addMenuItem("Color Frame");
	frameTrimSelector->addMenuItem("Color Trim");
	if (numPalette > 2 ) {
		frameTrimSelector->addMenuItem("Color Extra Trim");
	}

	frameTrimSelector->setCancelButton(true, "");
	frameTrimSelector->setOkButton(true, "@ok");

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	ghost->addSuiBox(frameTrimSelector);
	player->sendMessage(frameTrimSelector->generateMessage());

	return 0;
}
