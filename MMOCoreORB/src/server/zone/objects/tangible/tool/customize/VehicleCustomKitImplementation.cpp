/*
 * VehicleCustomKitImplementation.cpp
 *
 *  Created on: May 1, 2013
 *      Author: Trick77
 */

#include "VehicleCustomKit.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/templates/customization/AssetCustomizationManagerTemplate.h"

#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/CustomVehicleSuiCallback.h"

int VehicleCustomKitImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (player == NULL)
		return 0;
	if (!isASubChildOf(player))
		return 0;
	if (selectedID != 20)
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);

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
		//player->sendSystemMessage("id "+ String::valueOf(ownerID));
		ManagedReference<CreatureObject*> targetOwner = server->getObject(ownerID, true).castTo<CreatureObject*>();
		if (targetOwner != NULL)
		{
			ManagedReference<PlayerObject*> ghostOwner = targetOwner->getPlayerObject();
			for (int i = 0; i < ghostOwner->getConsentListSize(); ++i) {
				String entryName = ghostOwner->getConsentName(i);
				if (!entryName.isEmpty()){
					if (entryName == player->getFirstName().toLowerCase()){
						hasConsent = true;
					}
				}
				//player->sendSystemMessage("names/"+ entryName + "/" + player->getFirstName() + "/" + player->getLastName());
			}
		}
		if (!hasConsent){
			player->sendSystemMessage("You require consent to customize another player's vehicle");
			return 0;
		}
	}
	//end permission check

	String appearanceFilename = target->getObjectTemplate()->getAppearanceFilename();
	VectorMap<String, Reference<CustomizationVariable*> > variables;
	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);
	int numPalette = 0;
	for(int i = 0; i< variables.size(); ++i)
	{
		String varkey = variables.elementAt(i).getKey();
		//String varvalue = variables.elementAt(i).getValue().get()->toString();
		//player->sendSystemMessage(varkey + " "+ varvalue);
		if (varkey.contains("color"))
		{
			++numPalette;
		}
	}

	if (numPalette == 0) {
		player->sendSystemMessage("no customization options avaliable on this vehicle");//jetpack
		return 0;
	}

	decreaseUseCount();
	VehicleObject* painted = cast<VehicleObject*>(vehicle);
	if (painted != NULL){
		painted->refreshPaint();
	}

	ManagedReference<SuiListBox*> frameTrimSelector = new SuiListBox(player, SuiWindowType::CUSTOMIZE_KIT);
	frameTrimSelector->setUsingObject(player);
	frameTrimSelector->setCallback(new CustomVehicleSuiCallback(server, numPalette));
	frameTrimSelector->setUsingObject(target);
	frameTrimSelector->setPromptTitle("Customize");
	frameTrimSelector->setPromptText("Please select the customization action you would like to take");

	frameTrimSelector->addMenuItem("Color Frame");
	frameTrimSelector->addMenuItem("Color Trim");
	if (numPalette > 2 ) {
		frameTrimSelector->addMenuItem("Color extra Trim");
	}

	frameTrimSelector->setCancelButton(true, "");
	frameTrimSelector->setOkButton(true, "@ok");

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	ghost->addSuiBox(frameTrimSelector);
	player->sendMessage(frameTrimSelector->generateMessage());

	return 0;
}

