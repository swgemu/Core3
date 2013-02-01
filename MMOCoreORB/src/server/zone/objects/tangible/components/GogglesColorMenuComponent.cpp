/*
 * LightsaberObjectMenuComponent.cpp
 *
 *  Created on: 3/11/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"
#include "GogglesColorMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/ColorGogglesSuiCallback.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/templates/customization/AssetCustomizationManagerTemplate.h"

void GogglesColorMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	// Coloring the goggles...

	String text = "Color Change";
	menuResponse->addRadialMenuItem(89, 3, text);

}

int GogglesColorMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	ManagedReference<SceneObject*> parent = sceneObject->getParent();
	if (parent != NULL && parent->isPlayerCreature()) {
		player->sendSystemMessage("@error_message:equipped_goggles");
		return 0;
	}

	// Handle color change.

	if (selectedID == 89) {
		ZoneServer* server = player->getZoneServer();

		if (server != NULL) {

			// The color index.
			String appearanceFilename = sceneObject->getObjectTemplate()->getAppearanceFilename();
			VectorMap<String, Reference<CustomizationVariable*> > variables;
			AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);

			// The Sui Box.
			ManagedReference<SuiColorBox*> cbox = new SuiColorBox(player, SuiWindowType::COLOR_GOGGLES);
			cbox->setCallback(new ColorGogglesSuiCallback(server));
			cbox->setColorPalette(variables.elementAt(1).getKey()); // First one seems to be the frame of it? Skip to 2nd.
			cbox->setUsingObject(sceneObject);

			// Add to player.
			ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
			ghost->addSuiBox(cbox);
			player->sendMessage(cbox->generateMessage());
		}

	}


	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
