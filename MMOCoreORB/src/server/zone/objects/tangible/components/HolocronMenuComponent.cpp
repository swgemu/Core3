/*
 * HolocronMenuComponent.cpp
 *
 *  Created on: 01/23/2012
 *      Author: xyborn
 */

#include "HolocronMenuComponent.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/jedi/JediManager.h"

int HolocronMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (selectedID != 20)
		return 0;

	if (!sceneObject->isASubChildOf(creature))
		return 0;

	JediManager::instance()->useItem(sceneObject, JediManager::ITEMHOLOCRON, creature);

	return 0;
}

