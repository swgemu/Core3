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


	Zone* zone = building->getZone();

	if(zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();



	ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();
	if(playerObject == NULL)
		return;

	if(building->getFaction() == player->getFaction()) {

		menuResponse->addRadialMenuItem(228, 3, "@hq:mnu_defense_status");

		if(gcwMan->isShutdownSequenceStarted(building)){
			menuResponse->addRadialMenuItem(231, 3, "@hq:mnu_shutdown");  // Shutdown facility
		}

		if(building->getOwnerCreatureObject() == player){
			menuResponse->addRadialMenuItem(38, 3, "@hq:mnu_reset_vulnerability"); // Reset Vulnerability
		}


	} else {

		if(playerObject->getFactionStatus() == FactionStatus::OVERT) {

			menuResponse->addRadialMenuItem(228, 3, "@hq:mnu_defense_status");

			if(gcwMan->isPowerOverloaded(building) && !gcwMan->isShutdownSequenceStarted(building)){
				menuResponse->addRadialMenuItem(230, 3, "@hq:mnu_overload");  // activate overload
			}
		}
	}


	//if(true){





	// donate menus removed
	//menuResponse->addRadialMenuItem(37, 3, "@hq:mnu_donate"); // Donate
	//menuResponse->addRadialMenuItemToRadialID(37, 225, 3,  "@hq:mnu_donate_money"); // Donate MOney
	//menuResponse->addRadialMenuItemToRadialID(37, 226, 3, "@hq:mnu_donate_deed"); // donate defense
	//menuResponse->addRadialMenuItemToRadialID(37, 227, 3, "@hq:mnu_donate_resource"); // donate resource




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
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
	if (ghost == NULL)
		return 1;




	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());
	if(building == NULL)
		return 1;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingDataComponent(building);

	if(baseData == NULL)
		return 1;

	Zone* zone = building->getZone();

	if(zone == NULL)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if(gcwMan == NULL)
		return 1;

	if ( selectedID == 228 || selectedID == 20){

		if(ghost->getFactionStatus() != FactionStatus::OVERT && creature->getFaction() != building->getFaction()){
				creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:declared_personnel_only"); // Only Special Forces personnel may access this terminal
				return 1;
		}

		gcwMan->sendBaseDefenseStatus(creature, building);
	} else if ( selectedID == 38) {
		gcwMan->sendResetVerification(creature, building);
	} else if ( selectedID == 229) {
		//info("Destroy base here",true);
		gcwMan->doBaseDestruction(building);
	} else if ( selectedID == 230 ) {
		creature->sendSystemMessage("BASE WILL BE DESTROYED UNLESS IT IS STOPPED");

		gcwMan->scheduleBaseDestruction(building);
	} else if (selectedID == 231) {
		//info("abort shutdown",true);
		gcwMan->abortShutdownSequence(creature,building);

	}
	return 0;
}

DestructibleBuildingDataComponent* HQMenuComponent::getDestructibleBuildingDataComponent(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = NULL;

	if (building != NULL){
		if(building->isGCWBase()){
			DataObjectComponentReference* data = building->getDataObjectComponent();

			if(data != NULL)
				baseData = cast<DestructibleBuildingDataComponent*>(data->get());

		}
	}

		return baseData;
}
