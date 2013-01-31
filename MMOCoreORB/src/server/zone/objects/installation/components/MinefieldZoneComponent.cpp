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
#include "server/zone/objects/installation/components/TurretObserver.h"

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

			ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

			if(tano == NULL)
				return;

			if(!player->isAttackableBy(tano))
				return;

			Reference<MinefieldAttackTask*> task = new MinefieldAttackTask(sceneObject, player);
			task->execute();
		}
	} catch (Exception& e) {

	}

	return;
}

void MinefieldZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zne){
	if(zne == NULL)
		return;

	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);
	if(installation == NULL)
		return;

	ManagedReference<TurretObserver*> observer = new TurretObserver();
	installation->registerObserver(ObserverEventType::OBJECTDESTRUCTION,observer);

	// TODO: remove.  this is to get the pvpstatus bitmask correct for existing minefields
	uint64 oid = installation->getOwnerObjectID();
	if(oid != 0) {
		ManagedReference<SceneObject*> sceno = zne->getZoneServer()->getObject(oid);
		if(sceno != NULL && sceno->isGCWBase()) {
			ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceno.get());
			if(building != NULL){

				installation->setPvpStatusBitmask(building->getPvpStatusBitmask() | 1);
			}
		}
	}



}

