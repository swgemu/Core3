/*
 * GCWBaseContainerComponent.h
 *
 *  Created on: Dec 6, 2012
 *      Author: root
 */

#ifndef GCWBASECONTAINERCOMPONENT_H_
#define GCWBASECONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "GCWBaseContainerComponent.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"
#include "server/zone/objects/player/FactionStatus.h"
class GCWBaseContainerComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission){

		if(ContainerPermissions::WALKIN){
			BuildingObject* building = dynamic_cast<BuildingObject*>(sceneObject);

			if(building == NULL){
				return false;
			}

			if(building->getPvpStatusBitmask() & CreatureFlag::OVERT){
				return checkPVPPermission( building,  creature,  permission);
			} else {
				return checkPVEPermission(building, creature, permission);
			}
		}

		return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);


	}

	bool checkPVPPermission(BuildingObject* building, CreatureObject* creature, uint16 permission){
		PlayerObject* player = creature->getPlayerObject();

		if(player == NULL){
			return false;
		}

		if(creature->getFaction() == 0){
			creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:youre_neutral_excluded"); // This is a restricted acces military structure, and yo uhaven't aligned
			return false;
		}

		if(player->getFactionStatus() <= FactionStatus::COVERT){
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

		// if the base is not vulnerable.  allow a warrant officer rank of opposite faction enter the base
		if(!baseData->isVulnerable() && creature->getFaction() >= 9)
			return true;

		if(!baseData->isVulnerable()){
			creature->sendSystemMessage("Base is not vulnerable.  You must be Warrant Officer I to enter at this time.");
			return false;
		}

		if(!baseData->hasDefense()){
			return true;
		} else{
			creature->sendSystemMessage("@faction_perk:destroy_turrets"); // You cannot enter this HQ until all TUrrets have been destroyed
			return false;
		}

		creature->sendSystemMessage("unkown reason for entry denial");


		return false;
	}

	bool checkPVEPermission(BuildingObject* building, CreatureObject* creature, uint16 permission){
		Logger::Logger tlog("cont");
		tlog.info("checking pve permissions",true);
		PlayerObject* player = creature->getPlayerObject();

		if(player == NULL){
			return false;
		}

		if(creature->getFaction() == 0){
			creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:youre_neutral_excluded"); // This is a restricted acces military structure, and yo uhaven't aligned
			return false;
		}

		if(player->getFactionStatus() < FactionStatus::COVERT){
			creature->sendSystemMessage("You must be at least a combatatant");
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

		// if the base is not vulnerable.  allow a warrant officer rank of opposite faction enter the base
		if(!baseData->isVulnerable() && creature->getFaction() >= 9)
			return true;

		if(!baseData->isVulnerable()){
			creature->sendSystemMessage("Base is not vulnerable.  You must be Warrant Officer I to enter at this time.");
			return false;
		}

		if(!baseData->hasDefense()){
			return true;
		} else{
			creature->sendSystemMessage("@faction_perk:destroy_turrets"); // You cannot enter this HQ until all TUrrets have been destroyed
			return false;
		}
		creature->sendSystemMessage("unkown reason for entry denial");
		return false;
	}

};

#endif /* GCWBASECONTAINERCOMPONENT_H_ */
