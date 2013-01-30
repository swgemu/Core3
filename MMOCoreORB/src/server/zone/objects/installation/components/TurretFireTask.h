/*
 * TurretFireTask.h
 *
 *  Created on: 20/12/2012
 *      Author: victor
 */

#ifndef TURRETFIRETASK_H_
#define TURRETFIRETASK_H_

#include "engine/engine.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/creature/commands/TurretFireCommand.h"

class TurretFireTask : public Task {
	ManagedReference<TangibleObject*> sceneObject;
	ManagedReference<SceneObject*> target;

public:
	TurretFireTask(TangibleObject* turret, SceneObject* victim) {
		sceneObject = turret;
		target = victim;
	}

	void run() {
		Locker lock(sceneObject);

		Locker lockv(target, sceneObject);

		if(!CollisionManager::checkLineOfSight(target, sceneObject)){
			return;
		}

		DataObjectComponentReference* data = sceneObject->getDataObjectComponent();

		if(data == NULL)
			return;
		TurretDataComponent* turretData = cast<TurretDataComponent*>(data->get());

		if(sceneObject->getZoneServer() != NULL && turretData->canAutoFire()) {
			ManagedReference<ObjectController*> objectController = sceneObject->getZoneServer()->getObjectController();
			QueueCommand* command = objectController->getQueueCommand(String("turretfire").hashCode());

			if(command != NULL){

				CombatQueueCommand* combatCommand = cast<CombatQueueCommand*>(command);
				if(combatCommand != NULL){
					WeaponObject* weapon = cast<WeaponObject*>(sceneObject->getSlottedObject("hold_r"));
					TangibleObject* defenderObject = cast<TangibleObject*>(target.get());

					CombatManager::instance()->doCombatAction(sceneObject, weapon, defenderObject, combatCommand);
					turretData->updateAutoCooldown(weapon->getAttackSpeed());
					turretData->updateManualCooldown(weapon->getAttackSpeed());

					if(turretData->getController() != NULL){
						PlayerObject* ghost = turretData->getController()->getPlayerObject();
						if(ghost != NULL)
							ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

					}
				}
			}

		}
	}
};

#endif /* TURRETFIRETASK_H_ */
