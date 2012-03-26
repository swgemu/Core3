/*
 * CampKitMenuComponent
 *
 *  Created on: 12/1/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "DiceMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/components/DataObjectComponentReference.h"
#include "server/zone/objects/tangible/components/generic/DiceDataComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

void DiceMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isDiceObject())
		return;

	Reference<DiceTemplate*> diceTemplate = cast<DiceTemplate*>(sceneObject->getObjectTemplate());
	if (diceTemplate == NULL) {
		error("No DiceTemplate for: " + String::valueOf(sceneObject->getServerObjectCRC()));
		return;
	}

	/// Basic single roll
	menuResponse->addRadialMenuItem(172,3,"@dice/dice:dice_roll_single");

	/// configurable die
	if(diceTemplate->isConfigurable()) {
		menuResponse->addRadialMenuItem(164, 3,"@dice/dice_details:eqp_dice_configure");
		menuResponse->addRadialMenuItemToRadialID(164, 165, 3,"@dice/dice:dice_two_single");
		menuResponse->addRadialMenuItemToRadialID(164, 166, 3,"@dice/dice:dice_three_single");
		menuResponse->addRadialMenuItemToRadialID(164, 167, 3,"@dice/dice:dice_four_single");
		menuResponse->addRadialMenuItemToRadialID(164, 168, 3,"@dice/dice:dice_five_single");
		menuResponse->addRadialMenuItemToRadialID(164, 169, 3,"@dice/dice:dice_six_single");
		menuResponse->addRadialMenuItemToRadialID(164, 170, 3,"@dice/dice:dice_seven_single");
		menuResponse->addRadialMenuItemToRadialID(164, 171, 3,"@dice/dice:dice_eight_single");
	}

	if (!diceTemplate->isConfigurable() && !diceTemplate->isChanceCube()) {
		menuResponse->addRadialMenuItem(172, 3, "@dice/dice:dice_roll_one_single");
		menuResponse->addRadialMenuItem(173, 3, "@dice/dice:dice_roll_two_single");
		menuResponse->addRadialMenuItem(174, 3, "@dice/dice:dice_roll_three_single");
		menuResponse->addRadialMenuItem(175, 3, "@dice/dice:dice_roll_four_single");
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject,
			menuResponse, player);
}

int DiceMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) {
	if (!sceneObject->isDiceObject())
		return 0;

	TangibleObject* dice = cast<TangibleObject*>(sceneObject);
	if (dice == NULL)
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if (player->getZone() == NULL)
		return 0;

	/// Get Dice Template
	Reference<DiceTemplate*> diceTemplate = cast<DiceTemplate*>(sceneObject->getObjectTemplate());
	if (diceTemplate == NULL) {
		error("No DiceTemplate for: " + String::valueOf(sceneObject->getServerObjectCRC()));
		return 0;
	}

	DiceDataComponent* diceData = NULL;
	/// Get sides count
	byte sides = diceTemplate->getSides();
	DataObjectComponent* data = dice->getDataObjectComponent()->get();
	if(data != NULL && data->isDiceData()) {
		diceData = cast<DiceDataComponent*>(data);
		sides = diceData->getSides();
	}

	if((selectedID > 171 && selectedID < 176) && sides == 0) {
		player->sendSystemMessage("@dice/dice:dice_configure_msg");
		return 0;
	}

	switch(selectedID) {
	case 175:
		/// 4 Roll
		doRoll(player, diceTemplate, sides, diceTemplate->getSidesText(), 4);
		break;
	case 174:
		/// 3 Roll
		doRoll(player, diceTemplate, sides, diceTemplate->getSidesText(), 3);
		break;
	case 173:
		/// 2 Roll
		doRoll(player, diceTemplate, sides, diceTemplate->getSidesText(), 2);
		break;
	case 172:
		/// 1 Roll
		doRoll(player, diceTemplate, sides, diceTemplate->getSidesText(), 1);
		break;
	case 171:
		/// 8 sides
		if(diceData != NULL)
			diceData->setSides(8);
		break;
	case 170:
		/// 7 sides
		if(diceData != NULL)
			diceData->setSides(7);
		break;
	case 169:
		/// 6 sides
		if(diceData != NULL)
			diceData->setSides(6);
		break;
	case 168:
		/// 5 sides
		if(diceData != NULL)
			diceData->setSides(5);
		break;
	case 167:
		/// 4 sides
		if(diceData != NULL)
			diceData->setSides(4);
		break;
	case 166:
		/// 3 sides
		if(diceData != NULL)
			diceData->setSides(3);
		break;
	case 165:
		/// 2 sides
		if(diceData != NULL)
			diceData->setSides(2);
		break;
	default:
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject,
				player, selectedID);
	}

	return 0;
}

void DiceMenuComponent::doRoll(CreatureObject* player, DiceTemplate* diceTemplate, int sides, const String& sidesText, int numRoll) {

	StringIdChatParameter self("dice/dice", diceTemplate->getSelfSingleResult());
	StringIdChatParameter others("dice/dice", diceTemplate->getOthersSingleResult());

	others.setTU(player->getFirstName());

	if (diceTemplate->isChanceCube()) {
		if (System::random(1) == 1) {
			self.setTO("red");
			others.setTO("red");
		} else {
			self.setTO("blue");
			others.setTO("blue");
		}
		others.setTT(player->getFirstName());
	} else {

		StringBuffer rolled;

		for(int i = 0; i < numRoll; ++i) {
			if(i != 0)
				rolled << ",";
			rolled << " " << System::random(sides - 1) + 1;
		}

		self.setDI(sides);
		others.setDI(sides);
		self.setTT(sidesText);
		others.setTT(sidesText);
		self.setTO(rolled.toString());
		others.setTO(rolled.toString());
	}

	ChatSystemMessage* msg = new ChatSystemMessage(others,
			ChatSystemMessage::DISPLAY_CHATANDSCREEN);

	player->broadcastMessage(msg, false);
	player->sendSystemMessage(self);
}

