/*
 * MinefieldZoneComponent.cpp
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#include "MinefieldZoneComponent.h"
#include "MinefieldDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "MinefieldAttackTask.h"
#include "server/zone/objects/installation/components/TurretObserver.h"

void MinefieldZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) const {

	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if(!sceneObject->isMinefield() || target == nullptr){
		return;
	}

	DataObjectComponentReference* ref = sceneObject->getDataObjectComponent();
	if(ref == nullptr){
		info("dataobjectcomponent is null",true);
		return;
	}

	MinefieldDataComponent* mineData = cast<MinefieldDataComponent*>(ref->get());

	if (mineData == nullptr)
		return;

	try {
		if (target->isPlayerCreature()) {

			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(entry);

			if(player == nullptr)
				return;

			uint64 playerObjID = player->getObjectID();

			ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

			if(tano == nullptr)
				return;

			if(!player->isAttackableBy(tano) && !mineData->hasNotifiedPlayer(playerObjID))
				return;

			if (sceneObject->isInRange(target, mineData->getMaxRange())) {

				if (mineData->canExplode() && sceneObject->getContainerObjectsSize() > 0) {
					Reference<MinefieldAttackTask*> task = new MinefieldAttackTask(sceneObject, player);
					task->execute();
				}

				if (!mineData->hasNotifiedPlayer(playerObjID)) {
					mineData->addNotifiedPlayer(playerObjID);
					player->sendSystemMessage("@faction_perk:minefield_near"); //You have breached the perimeter of an enemy minefield.
				}
			}
			else if (mineData->hasNotifiedPlayer(playerObjID)) {
				player->sendSystemMessage("@faction_perk:minefield_exit"); //You have left the perimeter of an enemy minefield.
				mineData->removeNotifiedPlayer(playerObjID);
			}

		}
	} catch (Exception& e) {

	}

	return;
}

void MinefieldZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const {
	if(zne == nullptr)
		return;

	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);
	if(installation == nullptr)
		return;

	ManagedReference<TurretObserver*> observer = new TurretObserver();

	if (observer != nullptr)
		installation->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
}

void MinefieldZoneComponent::notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) const {

	ManagedReference<CreatureObject*> player = cast<CreatureObject*>(entry);

	if (player == nullptr || !player->isPlayerCreature())
		return;

	MinefieldDataComponent* data = cast<MinefieldDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == nullptr)
		return;

	if (data->hasNotifiedPlayer(player->getObjectID())) {
		data->removeNotifiedPlayer(player->getObjectID());
		player->sendSystemMessage("@faction_perk:minefield_exit"); //You have left the perimeter of an enemy minefield.
	}
}
