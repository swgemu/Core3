/*
 * DroidCustomKitObjectMenuComponent.h
 *
 *  Created on: 11/29/2013
 *      Author: Klivian
 */

#include "DroidCustomKitObjectMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/ZoneServer.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/CustomDroidSuiCallback.h"

void DroidCustomKitObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if(!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == nullptr)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int DroidCustomKitObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {

	if (player == nullptr)
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (selectedID != 20)
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

	if(!sceneObject->isTangibleObject())
		return 0;

	ManagedReference<TangibleObject*> kitTano = cast<TangibleObject*>(sceneObject);

	if (kitTano == nullptr)
		return 0;

	uint64 targetID = player->getTargetID();
	ZoneServer* server = player->getZoneServer();

	if (server == nullptr)
		return 0;

	ManagedReference<TangibleObject*> target = server->getObject(targetID, true).castTo<TangibleObject*>();

	if (target == nullptr || !target->isDroidObject()) {
		player->sendSystemMessage("@tool/customizer:droid_pet_only"); // You may only use this tool to customize droid pets.
		return 0;
	}

	//permission check
	CreatureObject* droid = cast<CreatureObject*>(target.get());
	uint64 ownerID = droid->getCreatureLinkID();

	if (ownerID != player->getObjectID()){
		bool hasConsent = false;

		ManagedReference<CreatureObject*> targetOwner = server->getObject(ownerID, true).castTo<CreatureObject*>();

		if (targetOwner != nullptr) {
			Locker crossLock(targetOwner, player);
			ManagedReference<PlayerObject*> ghostOwner = targetOwner->getPlayerObject();

			if (ghostOwner != nullptr) {
				for (int i = 0; i < ghostOwner->getConsentListSize(); ++i) {
					String entryName = ghostOwner->getConsentName(i);

					if (!entryName.isEmpty()){
						if (entryName == player->getFirstName().toLowerCase()){
							hasConsent = true;
						}
					}
				}
			}
		}

		if (!hasConsent){
			player->sendSystemMessage("@tool/customizer:need_consent"); // You require consent to customize another player's droid.
			return 0;
		}
	}
	//end permission check

	Locker clocker(droid, player);

	String appearanceFilename = target->getObjectTemplate()->getAppearanceFilename();
	VectorMap<String, Reference<CustomizationVariable*> > variables;
	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, true);
	int totalPalettes = 0;

	for (int i = 0; i< variables.size(); ++i) {
		String varkey = variables.elementAt(i).getKey();

		if (varkey.contains("color")) {
			++totalPalettes;
		}
	}

	if (totalPalettes == 0) {
		StringIdChatParameter noCustom("tool/customizer", "prose_no_customization"); // %TT does not have any customization options available.
		noCustom.setTT(droid->getCustomObjectName());

		player->sendSystemMessage(noCustom.toString());
		return 0;
	}

	ManagedReference<SuiListBox*> frameTrimSelector = new SuiListBox(player, SuiWindowType::CUSTOMIZE_KIT);

	frameTrimSelector->setUsingObject(player);
	frameTrimSelector->setCallback(new CustomDroidSuiCallback(server, totalPalettes, kitTano));
	frameTrimSelector->setUsingObject(target);
	frameTrimSelector->setPromptTitle("@tool/customizer:mnu_customize");
	frameTrimSelector->setPromptText("@tool/customizer:var_select_prompt");

	frameTrimSelector->addMenuItem("@tool/customizer:opt_color_frame");

	if (totalPalettes > 1 ) {
		frameTrimSelector->addMenuItem("@tool/customizer:opt_color_trim");
	}

	frameTrimSelector->setCancelButton(true, "");
	frameTrimSelector->setOkButton(true, "@ok");

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost != nullptr)
		ghost->addSuiBox(frameTrimSelector);

	player->sendMessage(frameTrimSelector->generateMessage());

	return 0;
}
