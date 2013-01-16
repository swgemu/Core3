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

	if (building == NULL || player->isDead() || player->isIncapacitated())
		return;

	Zone* zone = building->getZone();

	if(zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if(!gcwMan->canUseTerminals(player, building, sceneObject))
		return;

	if(building->getFaction() != player->getFaction()) {
		if( gcwMan->isBaseVulnerable(building) && !gcwMan->isUplinkJammed(building)) {
			menuResponse->addRadialMenuItem(227, 3, "@hq:mnu_jam");
		}
	}

}

int UplinkTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (player->isDead() || player->isIncapacitated())
		return 1;

	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL || player->isDead() || player->isIncapacitated())
		return 0;

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if(building == NULL)
		return 1;

	Zone* zone = sceneObject->getZone();

	if(zone == NULL)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if(gcwMan == NULL)
		return 1;

	if(!gcwMan->canUseTerminals(player, building, sceneObject))
		return 1;

	if ( selectedID == 227 || selectedID == 20) {
		if(player->getFaction() != building->getFaction()) {
			gcwMan->sendJamUplinkMenu(player, building);
		}

	}

	return 0;
}


