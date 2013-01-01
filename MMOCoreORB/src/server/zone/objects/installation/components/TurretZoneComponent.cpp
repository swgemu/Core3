/*
 * TurretZoneComponent.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: root
 */

#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "TurretZoneComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "TurretDataComponent.h"

#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/objects/installation/components/TurretObserver.h"

#include "server/zone/managers/combat/CreatureAttackData.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "TurretFireTask.h"

void TurretZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry){

	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if(!sceneObject->isTangibleObject() || !sceneObject->isTurret() || target == NULL){
		return;
	}

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

	DataObjectComponentReference* data = sceneObject->getDataObjectComponent();

	if(data == NULL)
		return;

	TurretDataComponent* turretData = cast<TurretDataComponent*>(data->get());

	if(turretData == NULL || !turretData->canFire())
		return;

	if(target->isPlayerCreature() && sceneObject->isInRange(target,65)){

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(entry);
		ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();

		bool canFire = false;

		DataObjectComponentReference* ref = sceneObject->getDataObjectComponent();
		if(ref == NULL){
			info("data is null",true);
			return;
		}

		if(tano->getFaction() != player->getFaction() && playerObject->getFactionStatus() == FactionStatus::OVERT && tano->getFaction() != 0){
			Reference<TurretFireTask*> task = new TurretFireTask(tano, player);
			task->execute();
		}
	}

}

void TurretZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zne){
	if(zne == NULL)
		return;

	ManagedReference<TurretObserver*> observer = new TurretObserver();
	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);
	installation->registerObserver(ObserverEventType::OBJECTDESTRUCTION,observer);

}
