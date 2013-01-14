/*
 * HQMenuComponent.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: root
 */
#include "HQMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/structure/StructureObject.h"

#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/chat/StringIdChatParameter.h"


#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"

#include "server/zone/managers/gcw/GCWManager.h"

void HQMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
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

	if(building->getFaction() == player->getFaction()) {

		menuResponse->addRadialMenuItem(228, 3, "@hq:mnu_defense_status");

		if(gcwMan->isShutdownSequenceStarted(building) && building->getPvpStatusBitmask() && CreatureFlag::OVERT){
			menuResponse->addRadialMenuItem(231, 3, "@hq:mnu_shutdown");  // Shutdown facility
		}

		// donate menus removed
		menuResponse->addRadialMenuItem(37, 3, "@hq:mnu_donate"); // Donate
		//menuResponse->addRadialMenuItemToRadialID(37, 225, 3,  "@hq:mnu_donate_money"); // Donate MOney
		menuResponse->addRadialMenuItemToRadialID(37, 226, 3, "@hq:mnu_donate_deed"); // donate defense

		if(building->getOwnerCreatureObject() == player){
			menuResponse->addRadialMenuItem(38, 3, "@hq:mnu_reset_vulnerability"); // Reset Vulnerability
		}

	} else {

		if(gcwMan->isPowerOverloaded(building) && !gcwMan->isShutdownSequenceStarted(building)){
			menuResponse->addRadialMenuItem(230, 3, "@hq:mnu_overload");  // activate overload
		}
	}

	// Admin menus to test out vulnerability manually
	/*
	if ( player->getPlayerObject()->isPrivileged()) {
		//info("player is privelaged", true);
		menuResponse->addRadialMenuItem(35, 3, "PVP EVENT");
		menuResponse->addRadialMenuItemToRadialID(35, MAKEIMPERIAL, 3, "MAKE VULNERABLE");
		menuResponse->addRadialMenuItemToRadialID(35, MAKENEUTRAL, 3, "MAKE INVULNERABLE");


	}
	*/

	//menuResponse->addRadialMenuItem(229, 3, "@player_structure:permission_destroy"); //Destroy Structure

}

int HQMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (creature->isDead() || creature->isIncapacitated())
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

	if(!gcwMan->canUseTerminals(creature, building, sceneObject))
		return 1;

	if(creature->getFaction() == building->getFaction()) {
		if (selectedID == 20){
			if(creature->getFaction() == building->getFaction())
				gcwMan->sendStatus(building,creature);
			} else if( selectedID == 228 || selectedID == 20){
				gcwMan->sendBaseDefenseStatus(creature, building);
			} else if ( selectedID == 38) {
				gcwMan->sendResetVerification(creature, building);
			} else if(selectedID == 231)
				gcwMan->abortShutdownSequence(creature,building);
			else if (selectedID == 226)
				gcwMan->sendSelectDeedToDonate(building,creature,0);
	} else {
		if ( selectedID == 230 )
			gcwMan->scheduleBaseDestruction(building,creature);
	}

	return 0;
}

