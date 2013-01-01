/*
 * MinefieldZoneComponent.cpp
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "MinefieldZoneComponent.h"
#include "MinefieldDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/InstallationObject.h"

#include "MinefieldDataComponent.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/combat/CreatureAttackData.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "MinefieldAttackTask.h"

void MinefieldZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) {
	// if we don't have any mines, just exit
	if(sceneObject->getContainerObjectsSize() == 0 )
		return;

	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if(sceneObject == NULL || !sceneObject->isMinefield() || target == NULL){
		return;
	}

	DataObjectComponentReference* ref = sceneObject->getDataObjectComponent();
	if(ref == NULL){
		info("dataobjectcomponent is null",true);
		return;
	}

	MinefieldDataComponent* mineData = cast<MinefieldDataComponent*>(ref->get());

	if(mineData == NULL || !mineData->canExplode())
		return;

	try {
		if (target->isPlayerCreature() && sceneObject->isInRange(target,mineData->getMaxRange())){
			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(entry);

			if(player == NULL)
				return;

			ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();

			if(playerObject == NULL)
				return;

			ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

			if(tano == NULL)
				return;


			if(tano->getFaction() != player->getFaction() && player->getFaction() != 0 ){

					Reference<MinefieldAttackTask*> task = new MinefieldAttackTask(sceneObject, player);
					task->execute();

			}

		}
	} catch (Exception& e) {

	}

	return;
}





