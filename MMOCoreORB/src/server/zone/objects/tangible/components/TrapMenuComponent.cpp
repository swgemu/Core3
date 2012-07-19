/*
 * TrapMenuComponent.cpp
 *
 *  Created on: 10/30/2011
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "TrapMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/TrapTemplate.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

void TrapMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}

int TrapMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

	if(!sceneObject->isASubChildOf(player))
		return 0;

	if (!sceneObject->isTangibleObject())
		return 0;

	if (!sceneObject->isASubChildOf(player))
			return 0;

	if(selectedID == 20) {
		ManagedReference<ZoneServer*> server = player->getZoneServer();
		if(server == NULL)
			return 0;

		String args = String::valueOf(sceneObject->getObjectID());
		String action = "/throwtrap ";
		String command = action + args;


		player->sendExecuteConsoleCommand(command);

		return 1;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

