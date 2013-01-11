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
		BuildingObject* building = dynamic_cast<BuildingObject*>(sceneObject);

		//Logger::Logger tlog("gcwperm");
		if(building == NULL){
			return false;
		}

		PlayerObject* player = creature->getPlayerObject();

			if(player == NULL){
				return false;
			}

		if(permission == ContainerPermissions::WALKIN) {

			if(player->getFactionStatus() == 0){
				creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:youre_neutral_excluded"); // This is a restricted acces military structure, and yo uhaven't aligned
				return false;
			}

			if(player->getFactionStatus() == FactionStatus::COVERT && creature->getFaction() != building->getFaction()){
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

			if(!baseData->isVulnerable()){
				creature->sendSystemMessage("Base is not vulnerable");
				return false;
			}

			// @faction_perk:destroy_turrets
			if(!baseData->hasDefense()){
			//	tlog.info("no defenses on base",true);
				return true;
			}
			else{
			//	tlog.info("base still has defenses",true);
				creature->sendSystemMessage("@faction_perk:destroy_turrets"); // You cannot enter this HQ until all TUrrets have been destroyed
				return false;
			}


			creature->sendSystemMessage("unkown reason for entry denial");

			return false;
		}

		return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
	}

};

#endif /* GCWBASECONTAINERCOMPONENT_H_ */
