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
#include "TurretDataComponent.h"
//#include "DetectorDataComponent.h"

#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/objects/installation/components/TurretObserver.h"

void TurretZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry){

	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);
	if(!sceneObject->isTangibleObject() || target == NULL){
		return;
	}

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

	if(sceneObject->isTurret() && target->isPlayerCreature() && sceneObject->isInRange(target,65)){

		DataObjectComponentReference* data = sceneObject->getDataObjectComponent();
		if(data == NULL)
			return;
		TurretDataComponent* turretData = cast<TurretDataComponent*>(data->get());

		if(turretData == NULL)
			return;

		if(!turretData->canFire())
			return;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(entry);
		ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();

		bool canFire = false;

		DataObjectComponentReference* ref = sceneObject->getDataObjectComponent();
		if(ref == NULL){
			info("data is null",true);
			return;
		}

		if(tano->getFaction() != player->getFaction() && playerObject->getFactionStatus() == FactionStatus::OVERT ){
			// TODO: call combat manager here to fire actual attack
			CombatAction* combatAction = NULL;
			uint32 animationCRC = String("fire_turret_medium").hashCode();
			uint8 hit = 0x01;
			combatAction = new CombatAction(tano, player, animationCRC, hit, CombatManager::DEFAULTTRAIL);
			tano->broadcastMessage(combatAction,true);
			turretData->updateCooldown();

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
