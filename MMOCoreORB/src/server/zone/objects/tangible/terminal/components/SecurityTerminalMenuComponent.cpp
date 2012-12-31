/*
 * SecurityTerminalMenuComponent.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: root
 */

#include "SecurityTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

void SecurityTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());
	ManagedReference<PlayerObject*> thisPlayer = player->getPlayerObject();

	if ( thisPlayer  == NULL || player->isDead() || player->isIncapacitated())
			return;


	if(player->getFaction() == 0)
		player->sendSystemMessage("@faction_recruiter:must_be_declared_use"); // Your faction affiliation must be delcared in order to use that item.

	Zone* zone = building->getZone();

	if(zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if( gcwMan->isUplinkJammed(building) && !gcwMan->isSecurityTermSliced(building) && player->getFaction() != building->getFaction() ) {
		if (gcwMan->isTerminalDamaged(cast<TangibleObject*>(sceneObject)))
			menuResponse->addRadialMenuItem(229, 3, "@ui:repair");
	}

}

int SecurityTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL)
		return 0;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	if (ghost == NULL)
		return 1;

	if(ghost->getFactionStatus() != FactionStatus::OVERT ){
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:declared_personnel_only"); // Only Special Forces personnel may access this terminal
		return 1;
	}
	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if(building == NULL)
		return 1;

	Zone* zone = building->getZone();

	if(zone == NULL)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if(gcwMan == NULL)
		return 1;

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

	if(player->getFaction() != building->getFaction()) {
		if ( selectedID == 229){
			gcwMan->repairTerminal(player, tano);
		}
	}

	return 0;
}
