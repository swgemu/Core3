/*
 * UplinkTerminalMenuComponent.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: root
 */

#include "UplinkTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"

void UplinkTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();

	if (building == NULL || player->isDead() || player->isIncapacitated())
		return;

	Zone* zone = building->getZone();

	if (zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return;

	if (!gcwMan->isBaseVulnerable(building))
		return;

	menuResponse->addRadialMenuItem(20, 3, "@hq:mnu_jam");
}

int UplinkTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL || player->isDead() || player->isIncapacitated() || selectedID != 20)
		return 0;

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
	ManagedReference<TangibleObject*> uplinkTerminal = cast<TangibleObject*>(sceneObject);

	if (building == NULL)
		return 1;

	Zone* zone = sceneObject->getZone();

	if (zone == NULL)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return 1;

	if (!gcwMan->isBaseVulnerable(building))
		return 1;

	// Most of the string rows for these errors did not exist in 14.1, pulled string text from a different patch
	if (!gcwMan->areOpposingFactions(player->getFaction(), building->getFaction())) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_tamper"); // You are not an enemy of this structure. Why would you want to tamper?
		return 1;
	} else if (gcwMan->isUplinkJammed(building)) {
		player->sendSystemMessage("It's no use! The uplink has been jammed.");
		return 1;
	} else if (player->isInCombat()) {
		player->sendSystemMessage("You cannot jam this uplink while you are in combat!");
		return 1;
	} else if (uplinkTerminal->getParentID() != player->getParentID()) {
		player->sendSystemMessage("You cannot jam the uplink if you are not even in the same room!");
		return 1;
	} else if (uplinkTerminal->getDistanceTo(player) > 15) {
		player->sendSystemMessage("You are too far away from the uplink to continue jamming!");
		return 1;
	} else if (!player->hasSkill("combat_bountyhunter_investigation_02")) {
		player->sendSystemMessage("Only a bounty hunter with intermediate surveillance skill could expect to jam this uplink!");
		return 1;
	}

	gcwMan->sendJamUplinkMenu(player, building, uplinkTerminal);

	return 0;
}


