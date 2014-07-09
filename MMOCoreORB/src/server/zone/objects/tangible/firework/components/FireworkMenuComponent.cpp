/*
 * CampKitMenuComponent
 *
 *  Created on: 12/1/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "FireworkMenuComponent.h"
#include "server/zone/objects/tangible/firework/FireworkObject.h"

void FireworkMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isFireworkObject())
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject,
			menuResponse, player);

}

int FireworkMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) {
	if (!sceneObject->isFireworkObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if (player->getZone() == NULL)
		return 0;

	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (selectedID == 20) {
		if(player->getParent() != NULL)
			return 0;

		FireworkObject* firework = cast<FireworkObject*>(sceneObject);
		firework->launch(player);

		return 0;
	} else
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject,
				player, selectedID);

	return 0;
}

