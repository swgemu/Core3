/*
 * OverrideTerminalMenuComponent.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: root
 */

#include "OverrideTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/structure/StructureObject.h"

#include "server/zone/objects/building/BuildingObject.h"

#include "server/zone/managers/gcw/GCWManager.h"


void OverrideTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if (building == NULL)
		return;

	if ( player  == NULL || player->isDead() || player->isIncapacitated())
			return;

	if(player->getFaction() == 0) {
		player->sendSystemMessage("@faction_recruiter:must_be_declared_use"); // Your faction affiliation must be delcared in order to use that item.
		return;
	}

	Zone* zone = building->getZone();

	if(zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if( gcwMan->isSecurityTermSliced(building) && !gcwMan->isDNASampled(building) ) {
		menuResponse->addRadialMenuItem(228, 3, "@hq:mnu_dna"); // Slice
	}

}

int OverrideTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL || player->isDead() || player->isIncapacitated())
			return 1;

	// Make sure the player is in the same cell
	ValidatedPosition* validPosition = ghost->getLastValidatedPosition();
	uint64 parentid = validPosition->getParent();

	if (parentid != sceneObject->getParentID()) {
		player->sendSystemMessage("@pvp_rating:ch_terminal_too_far");  // you are too far away from the terminal to use it
		return 1;
	}

	if(ghost->getFactionStatus() != FactionStatus::OVERT ){
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:declared_personnel_only"); // Only Special Forces personnel may access this terminal
		return 1;
	}

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if (building == NULL)
		return 1;


	Zone* zone = building->getZone();

	if(zone == NULL)
		return 1;

	GCWManager* gcwMan = zone->getGCWManager();
	if(player->getFaction() != building->getFaction()) {
		if(selectedID == 228 || selectedID == 20){
			gcwMan->sendDNASampleMenu(player, building);
		}
	}
	return 0;
}







