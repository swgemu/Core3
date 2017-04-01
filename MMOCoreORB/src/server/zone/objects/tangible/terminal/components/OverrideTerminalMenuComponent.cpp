/*
 * OverrideTerminalMenuComponent.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: root
 */

#include "OverrideTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

void OverrideTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();

	if (building == NULL)
		return;

	if (player  == NULL || player->isDead() || player->isIncapacitated())
			return;

	Zone* zone = building->getZone();

	if (zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return;

	if (!gcwMan->isBaseVulnerable(building))
		return;

	menuResponse->addRadialMenuItem(20, 3, "@hq:mnu_dna"); // Provide DNA Profile

}

int OverrideTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (player->isDead() || player->isIncapacitated() || selectedID != 20)
		return 1;

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
	ManagedReference<TangibleObject*> overrideTerminal = cast<TangibleObject*>(sceneObject);

	if (building == NULL)
		return 1;

	Zone* zone = building->getZone();

	if (zone == NULL)
		return 1;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return 1;

	if (!gcwMan->isBaseVulnerable(building))
		return 1;

	// Most of the string rows for these errors did not exist in 14.1, pulled string text from a different patch
	if (!gcwMan->areOpposingFactions(player->getFaction(), building->getFaction())) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_tamper"); // You are not an enemy of this structure. Why would you want to tamper?
		return 1;
	} else if (gcwMan->isDNASampled(building)) {
		player->sendSystemMessage("You stop sequencing as the fail-safe sequence has already been overridden.");
		return 1;
	} else if (!gcwMan->isSecurityTermSliced(building))	{
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:other_objectives"); // Other objectives must be disabled prior to gaining access to this one.
		return 1;
	} else if (player->isInCombat()) {
		player->sendSystemMessage("You cannot DNA sequence while you are in combat!");
		return 1;
	} else if (overrideTerminal->getParentID() != player->getParentID()) {
		player->sendSystemMessage("You cannot sequence DNA from the terminal if you are not even in the same room!");
		return 1;
	} else if (overrideTerminal->getDistanceTo(player) > 15) {
		player->sendSystemMessage("You are too far away from the override terminal to continue sequencing!");
		return 1;
	} else if (!player->hasSkill("outdoors_bio_engineer_novice")) {
		player->sendSystemMessage("Only a bio-engineer could expect to forge a suitable DNA sequence.");
		return 1;
	}

	player->sendSystemMessage("\"Retrieving new DNA sample...\"");
	Reference<CreatureObject*> playerRef = player;

	Core::getTaskManager()->executeTask([=] () {
		Locker locker(playerRef);
		Locker clocker(building, playerRef);

		gcwMan->sendDNASampleMenu(playerRef, building, overrideTerminal);
	}, "SendDNASampleMenuLambda");

	return 0;
}
