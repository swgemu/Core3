/*
 * LightsaberObjectMenuComponent.cpp
 *
 *  Created on: 3/11/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "LightsaberObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/scene/AttributeListMessage.h"

void LightsaberObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);
	if(weapon == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	// TODO: Add Opening Lightsabers.

	String text = "@jedi_spam:open_saber";
	menuResponse->addRadialMenuItem(89, 3, text);

	// menuResponse->addRadialMenuItem(71, 3, "Randomize Blade Color"); // Randomize Color (until crystals are implemented.)

}

int LightsaberObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);
	if (weapon == NULL)
		return 1;

	// Handle opening sabers

	if (selectedID == 89) {

		ManagedReference<SceneObject*> parent = weapon->getParent();
		if (parent != NULL && parent->isPlayerCreature()){
			player->sendSystemMessage("@jedi_spam:saber_not_while_equpped");
			return 0;
		}

		weapon->sendContainerTo(player);
	}


	/*// Handle blade color change:

	if(selectedID == 71) {
			int color = (System::random(29) + 1); // Randomize color until crystals are implemented.
			weapon->setBladeColor(color);
			byte bvalue = (byte)color;
			weapon->setCustomizationVariable("/private/index_color_blade", bvalue, true);
	}*/


	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
