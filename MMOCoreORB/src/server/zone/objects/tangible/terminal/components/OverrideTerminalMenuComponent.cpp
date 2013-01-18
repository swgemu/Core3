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

	Zone* zone = building->getZone();

	if(zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if(!gcwMan->canUseTerminals(player, building, sceneObject))
		return;

	if( gcwMan->isSecurityTermSliced(building) && !gcwMan->isDNASampled(building) ) {
		menuResponse->addRadialMenuItem(228, 3, "@hq:mnu_dna"); // Slice
	}

}

int OverrideTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (player->isDead() || player->isIncapacitated())
		return 1;

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if (building == NULL)
		return 1;

	Zone* zone = building->getZone();

	if(zone == NULL)
		return 1;

	GCWManager* gcwMan = zone->getGCWManager();

	if(!gcwMan->canUseTerminals(player, building, sceneObject))
		return 1;

	if(player->getFaction() != building->getFaction()) {
		if(selectedID == 228 || selectedID == 20){
			if(player->hasSkill("crafting_droidengineer_novice"))
				gcwMan->sendDNASampleMenu(player, building);
			else
				player->sendSystemMessage("Only an experience Bio Engineer can be expected to access the Override Terminal");
		}
	}
	return 0;
}







