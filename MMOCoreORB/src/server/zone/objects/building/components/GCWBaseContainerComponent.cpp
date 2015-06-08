/*
 * GCWBaseContainerComponent.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: root
 */

#include "GCWBaseContainerComponent.h"
#include "server/zone/objects/creature/CreatureFlag.h"

bool GCWBaseContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission){

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject);

	if(building == NULL)
		return false;

	return checkContainerPermission(building, creature, permission, false);


}
bool GCWBaseContainerComponent::checkContainerPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage){
	if(permission == ContainerPermissions::WALKIN){

		if(building == NULL){
			return false;
		}

		if (creature->isPlayerCreature() && creature->getPlayerObject()->isPrivileged())
			return true;

		if(building->getPvpStatusBitmask() & CreatureFlag::OVERT){
			return checkPVPPermission( building,  creature,  permission, sendMessage);
		} else {
			return checkPVEPermission(building, creature, permission, sendMessage);
		}
	}

	return StructureContainerComponent::checkContainerPermission(building, creature, permission);
}


bool GCWBaseContainerComponent::checkPVPPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage){

	PlayerObject* player = creature->getPlayerObject();
	if(player == NULL){
		return false;
	}

	if(creature->getFaction() == 0){
		if(sendMessage)
			creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:youre_neutral_excluded"); // This is a restricted acces military structure, and yo uhaven't aligned

		return false;
	}

	if(player->getFactionStatus() != FactionStatus::OVERT){
		if(sendMessage)
			creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:youre_covert_excluded"); // You must be a member of special forces to enter

		return false;
	}

	if(creature->getFaction() == building->getFaction()) {
		return true;
	}

	DataObjectComponentReference* data = building->getDataObjectComponent();
	DestructibleBuildingDataComponent* baseData = NULL;

	if(data != NULL){
		baseData = cast<DestructibleBuildingDataComponent*>(data->get());
	}

	if(baseData == NULL)
		return false;

	if(!baseData->hasDefense()){
		return true;
	} else{
		if(sendMessage)
			creature->sendSystemMessage("@faction_perk:destroy_turrets"); // You cannot enter this HQ until all TUrrets have been destroyed

		return false;
	}
}

bool GCWBaseContainerComponent::checkPVEPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage){
	PlayerObject* player = creature->getPlayerObject();

	if(player == NULL){
		return false;
	}

	if(creature->getFaction() == 0){
		if(sendMessage)
			creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:youre_neutral_excluded"); // This is a restricted acces military structure, and yo uhaven't aligned

		return false;
	}

	if((player->getFactionStatus() != FactionStatus::COVERT && player->getFactionStatus() != FactionStatus::OVERT)){

		if(sendMessage)
			creature->sendSystemMessage("You must be at least a combatant to enter");

		return false;
	}

	if(creature->getFaction() == building->getFaction()) {
		return true;
	}

	DataObjectComponentReference* data = building->getDataObjectComponent();
	DestructibleBuildingDataComponent* baseData = NULL;


	if(data != NULL){
		baseData = cast<DestructibleBuildingDataComponent*>(data->get());
	}

	if(baseData == NULL)
		return false;

	if(!baseData->hasDefense()){
		return true;
	} else{
		if(sendMessage)
			creature->sendSystemMessage("@faction_perk:destroy_turrets"); // You cannot enter this HQ until all TUrrets have been destroyed

		return false;
	}
}

