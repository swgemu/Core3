/*
 * DoorControlTerminalMenuComponent.cpp
 *
 *  Created on: 01/25/2012
 *      Author: Elvaron
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "DoorControlTerminalMenuComponent.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CloningStoreSuiCallback.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

void DoorControlTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
	menuResponse->addRadialMenuItem(20, 3, "@dungeon/death_watch:mnu_open_door");

}

int DoorControlTerminalMenuComponent::handleObjectMenuSelect(SceneObject* droidObject, CreatureObject* player, byte selectedID) {

	return TangibleObjectMenuComponent::handleObjectMenuSelect(droidObject, player, selectedID);
}
