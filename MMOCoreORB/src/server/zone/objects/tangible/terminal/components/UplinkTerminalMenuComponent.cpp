/*
 * UplinkTerminalMenuComponent.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: root
 */

#include "UplinkTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/structure/StructureObject.h"
//#include "server/zone/objects/tangible/terminal/Terminal.h"
//#include "server/zone/managers/structure/StructureManager.h"
//#include "server/zone/objects/player/sessions/StructureSetAccessFeeSession.h"
#include "server/zone/objects/building/BuildingObject.h"
//#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"
//#include "server/zone/objects/cell/CellObject.h"

void UplinkTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());
	ManagedReference<PlayerObject*> thisPlayer = player->getPlayerObject();

	if ( thisPlayer == NULL || building == NULL)
		return;


	Zone* zone = building->getZone();

	if(zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	// if the base is vulnerable and the uplink hasn't been jammed
	//info("Building faction = " + String::valueOf(building->getFaction()) + " player = " + String::valueOf(player->getFaction()),true);
	if(building->getFaction() != player->getFaction()) {
		if( gcwMan->isBaseVulnerable(building) && !gcwMan->isUplinkJammed(building)) {
			menuResponse->addRadialMenuItem(227, 3, "@hq:mnu_jam");
		}
	}

}

int UplinkTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL)
		return 0;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	if (ghost == NULL)
		return 1;

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	Zone* zone = building->getZone();

	if(zone == NULL)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if(gcwMan == NULL)
		return 1;

	if ( selectedID == 227 || selectedID == 20) {
		if(player->getFaction() != building->getFaction()) {

			if(ghost->getFactionStatus() != FactionStatus::OVERT )
				player->sendSystemMessage("@faction/faction_hq/faction_hq_response:declared_personnel_only"); // Only Special Forces personnel may access this terminal
			else
				gcwMan->sendJamUplinkMenu(player, building);
		}

	}

	return 0;
}


