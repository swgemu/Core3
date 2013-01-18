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
#include "server/zone/objects/tangible/tool/smuggler/PrecisionLaserKnife.h"

void SecurityTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if ( building == NULL || player->isDead() || player->isIncapacitated())
			return;

	if(player->getFaction() == 0) {
		player->sendSystemMessage("@faction_recruiter:must_be_declared_use"); // Your faction affiliation must be delcared in order to use that item.
		return;
	}

	Zone* zone = building->getZone();

	if(zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if(!gcwMan->canUseTerminals(player, building, sceneObject))
		return;

	if( gcwMan->isUplinkJammed(building) && !gcwMan->isSecurityTermSliced(building) && player->getFaction() != building->getFaction() ) {
		if (gcwMan->isTerminalDamaged(cast<TangibleObject*>(sceneObject)))
			menuResponse->addRadialMenuItem(229, 3, "@ui:repair");
	}

}

int SecurityTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL || player->isDead() || player->isIncapacitated())
		return 1;

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if(building == NULL)
		return 1;

	Zone* zone = building->getZone();

	if(zone == NULL)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if(gcwMan == NULL)
		return 1;

	if(!gcwMan->canUseTerminals(player, building, sceneObject))
		return 1;

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

	if(player->getFaction() != building->getFaction()) {
		if ( selectedID == 229){
			if(player->hasSkill("combat_smuggler_slicing_01"))
				gcwMan->repairTerminal(player, tano);
			else
				player->sendSystemMessage("Only an experienced Smuggler with Slicing experience could expect to repair the Security Terminal");
		}
	}

	return 0;
}
