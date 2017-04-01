/*
 * TurretControlMenuComponent.cpp
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#include "TurretControlMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

void TurretControlMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
	ManagedReference<PlayerObject*> thisPlayer = player->getPlayerObject();

	if (thisPlayer == NULL || building == NULL || player->isDead() || player->isIncapacitated())
		return;

	if (player->getFaction() == 0) {
		player->sendSystemMessage("@hq:declared_only"); // Only Special Forces personnel may access this terminal!
		return;
	}

	Zone* zone = building->getZone();

	if (zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return;

	if (!gcwMan->canUseTerminals(player, building, sceneObject))
		return;

	if (building->getFaction() == player->getFaction()) {
		menuResponse->addRadialMenuItem(222, 3, "@hq:mnu_turret_control"); // "Turret Control"
	}
}

int TurretControlMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL)
		return 0;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	if (ghost == NULL)
		return 1;

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();

	if (building == NULL)
		return 1;

	Zone* zone = building->getZone();

	if (zone == NULL)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return 1;

	if (!gcwMan->canUseTerminals(player, building, sceneObject))
		return 1;

	if (building->getFaction() != player->getFaction())
		return 1;

	if (selectedID == 222) {
		gcwMan->sendTurretAttackListTo(player,sceneObject);
	}

	return 0;
}
