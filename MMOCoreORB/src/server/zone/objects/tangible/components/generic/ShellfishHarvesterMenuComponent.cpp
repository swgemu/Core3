/*
 * ShellfishHarvesterMenuComponent.cpp
 *
 *  Created on: 3/11/2012
 *      Author: TragD
 */

#include <stddef.h>

#include "ShellfishHarvesterMenuComponent.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/minigames/ForageManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/components/generic/../TangibleObjectMenuComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
class TangibleObject;
}  // namespace tangible
}  // namespace objects
namespace packets {
namespace object {
class ObjectMenuResponse;
}  // namespace object
}  // namespace packets
}  // namespace zone
}  // namespace server

void ShellfishHarvesterMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}

int ShellfishHarvesterMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (!sceneObject->isTangibleObject())
		return 0;

	if(selectedID == 20) {
		ForageManager* forageManager = player->getZoneProcessServer()->getForageManager();
		forageManager->startForaging(player, ForageManager::SHELLFISH);
		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

