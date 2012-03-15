/*
 * ShellfishHarvesterMenuComponent.cpp
 *
 *  Created on: 3/11/2012
 *      Author: TragD
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "ShellfishHarvesterMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/minigames/ForageManager.h"



void ShellfishHarvesterMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}

int ShellfishHarvesterMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	//ManagedReference<ZoneServer*> server = player->getZoneServer();
	//StringBuffer success;
	//int amountHarvested;
	//int mindCost = 200;

	if (!sceneObject->isTangibleObject())
		return 0;

	if(selectedID == 20) {


		//if(server == NULL)
		//	return 0;

		ForageManager* forageManager = player->getZoneProcessServer()->getForageManager();
		forageManager->startForaging(player, ForageManager::SHELLFISH);
		return 0;

		/*
		if (player->isInWater() && !player->isSwimming()){

			if (player->getHAM(CreatureAttribute::MIND) >= mindCost + 1)
					player->inflictDamage(player, CreatureAttribute::MIND, mindCost, false, true);

			else {
					player->sendSystemMessage("You need to rest before you can harvest again"); //"You need to rest before you can forage again."
					return 1;
			}


			if (System::random(100) > 50){

				ManagedReference<Zone*> zone = player->getZone();
				ManagedReference<ResourceManager*> resourceManager = server->getResourceManager();

				if (System::random(100) > 50) {

					ManagedReference<ResourceSpawn*> molluskSpawn = resourceManager->getCurrentSpawn("seafood_mollusk",zone->getZoneName());
					amountHarvested = System::random(25)+ 5;
					resourceManager->harvestResourceToPlayer(player,molluskSpawn,amountHarvested);
					success << "You successfully harvest " << amountHarvested << " units of mollusk meat";
					player->sendSystemMessage(success.toString());
				}
				else {
					ManagedReference<ResourceSpawn*> crustaceanSpawn = resourceManager->getCurrentSpawn("seafood_crustacean",zone->getZoneName());
					amountHarvested = System::random(25)+ 5;
					resourceManager->harvestResourceToPlayer(player,crustaceanSpawn,System::random(25)+ 5);
					success << "You successfully harvest " << amountHarvested << " units of crustacean meat";
					player->sendSystemMessage(success.toString());
				}
			}

			else
				player->sendSystemMessage("You failed to harvest any shellfish");

		}

		else
			player->sendSystemMessage("You must be standing in water to use this tool");

		return 1; */
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

