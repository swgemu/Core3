/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "WaypointDatapadMenuComponent.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/jedi/JediManager.h"

void WaypointDatapadMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL) {
		return;
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	if (sceneObject->getObjectTemplate()->getFullTemplateString() == "object/tangible/loot/quest/force_sensitive/waypoint_datapad.iff")
		menuResponse->addRadialMenuItem(6, 3, "@ui_radial:item_activate"); //Activate

	if (sceneObject->getObjectTemplate()->getFullTemplateString() == "object/tangible/loot/quest/force_sensitive/theater_datapad.iff")
		menuResponse->addRadialMenuItem(7, 3, "@ui_radial:item_activate"); //Activate

}

int WaypointDatapadMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (selectedID == 6)
		JediManager::instance()->useItem(sceneObject, JediManager::ITEMWAYPOINTDATAPAD, player);

	if (selectedID == 7)
		JediManager::instance()->useItem(sceneObject, JediManager::ITEMTHEATERDATAPAD, player);

	return 0;
}

