/*
 * InsuranceTerminalMenuComponent.cpp
 *
 *  Created on: 01/12/2012
 *      Author: Elvaron
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "InsuranceTerminalMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/sui/callbacks/InsuranceMenuSuiCallback.h"
#include "server/zone/managers/player/PlayerManager.h"

void InsuranceTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int InsuranceTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if(selectedID == 20) {

		/*inline void setInsured(bool insure) {
			if (insure) {
				optionsBitmask |= OPTIONS_INSURED;
			} else {
				optionsBitmask &= ~OPTIONS_INSURED;
			}
		}*/

		// open insurance menu

		ManagedReference<SuiListBox*> suiInsuranceMenuBox = new SuiListBox(player, SuiWindowType::INSURANCE_MENU, SuiListBox::HANDLETHREEBUTTON);

		suiInsuranceMenuBox->setPromptTitle("@sui:mnu_insure");
		suiInsuranceMenuBox->setPromptText("Select which items you would like to buy insurance for from the list below.");

		bool found = false;

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

		Vector<ManagedReference<SceneObject*> > insurableItems = playerManager->getInsurableItems(player);

		if (insurableItems.size() == 0) {
			player->sendSystemMessage("@terminal_ui:no_insurable_items");
			return 0;
		}

		suiInsuranceMenuBox->setCallback(new InsuranceMenuSuiCallback(player->getZoneServer()));

		for (int i = 0; i < insurableItems.size(); i++) {
			SceneObject* item = insurableItems.get(i);

			if (item != NULL)
				suiInsuranceMenuBox->addMenuItem(item->getDisplayedName(), item->getObjectID());
		}

		suiInsuranceMenuBox->setCancelButton(true, "Cancel");
		suiInsuranceMenuBox->setOtherButton(true, "@sui:mnu_insure_all");
		suiInsuranceMenuBox->setUsingObject(sceneObject);
		suiInsuranceMenuBox->setForceCloseDistance(32.f);

		player->getPlayerObject()->addSuiBox(suiInsuranceMenuBox);
		player->sendMessage(suiInsuranceMenuBox->generateMessage());

		return 0;
	} else
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

	return 0;
}

