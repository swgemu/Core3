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
	Locker _lock(sceneObject);

	// just exit if we dont' have any mines
	if(sceneObject->getContainerObjectsSize() == 0)
		return;

	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);
	if(!sceneObject->isTangibleObject() || target == NULL){
		return;
	}

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);


	DataObjectComponentReference* ref = sceneObject->getDataObjectComponent();
	if(ref == NULL){
		info("dataobjectcomponent is null",true);
		return;
	}

	MinefieldDataComponent* mineData = cast<MinefieldDataComponent*>(ref->get());

	if(mineData == NULL || !mineData->canExplode())
		return;

	try {
		if (sceneObject->isMinefield() && target->isPlayerCreature() && sceneObject->isInRange(target,mineData->getMaxRange())){
			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(entry);
			if(player == NULL)
				return;

			ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();

			if(playerObject == NULL)
				return;


			if(tano->getFaction() != player->getFaction() && player->getFaction() != 0 && sceneObject->getContainerObjectsSize() > 0){
				ManagedReference<SceneObject*> obj = sceneObject->getContainerObject(0);
				if(obj == NULL){
					info("container object isnull",true);
					return;
				}

				ManagedReference<WeaponObject*> weapon = obj.castTo<WeaponObject*>();

				if(obj->getGameObjectType() == SceneObjectType::MINE) {
					Reference<MinefieldAttackTask*> task = new MinefieldAttackTask(sceneObject, player, weapon);
					task->execute();

					if(sceneObject->getContainerObjectsSize() > 0){
						ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject->getContainerObject(0));
						if(weapon != NULL){
							mineData->updateCooldown(weapon->getAttackSpeed());
							mineData->setMaxRange(weapon->getMaxRange());
						}
					}
				}
			}

		}
	} catch (Exception& e) {

	}

	return;
}





