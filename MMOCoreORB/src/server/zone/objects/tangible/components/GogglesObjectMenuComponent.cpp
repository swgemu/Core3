/*
 * LightsaberObjectMenuComponent.cpp
 *
 *  Created on: 3/11/2012
 *      Author: kyle
 */

#include <stddef.h>
#include <algorithm>

#include "GogglesObjectMenuComponent.h"
#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/components/TangibleObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"
#include "system/util/VectorMap.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "templates/customization/CustomizationVariable.h"

#include "server/zone/objects/player/sui/callbacks/ColorGogglesSuiCallback.h"

namespace server {
namespace zone {
class ZoneServer;
}  // namespace zone
}  // namespace server

void GogglesObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	if (sceneObject->isASubChildOf(player)) {
		menuResponse->addRadialMenuItem(81, 3, "@sui:color_lens");

		if (sceneObject->getObjectTemplate()->getFullTemplateString() == "object/tangible/wearables/goggles/goggles_s01.iff")
			menuResponse->addRadialMenuItem(82, 3, "@sui:color_frame");
	}
}

int GogglesObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;
		
	if (selectedID == 81 || selectedID == 82) {

		ManagedReference<SceneObject*> parent = sceneObject->getParent().get();
		if (parent != NULL && parent->isPlayerCreature()) {
			player->sendSystemMessage("@error_message:equipped_goggles");
			return 0;
		}

		// Handle color change.

		ZoneServer* server = player->getZoneServer();

		if (server != NULL) {

			// The color index.
			String appearanceFilename = sceneObject->getObjectTemplate()->getAppearanceFilename();
			VectorMap<String, Reference<CustomizationVariable*> > variables;
			AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);

			// The Sui Box.
			ManagedReference<SuiColorBox*> cbox = new SuiColorBox(player, SuiWindowType::COLOR_GOGGLES);
			cbox->setCallback(new ColorGogglesSuiCallback(server));
			if (selectedID == 81)
				cbox->setColorPalette(variables.elementAt(1).getKey());
			else
				cbox->setColorPalette(variables.elementAt(0).getKey());
			cbox->setUsingObject(sceneObject);

			// Add to player.
			ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
			ghost->addSuiBox(cbox);
			player->sendMessage(cbox->generateMessage());
		}

	}


	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
