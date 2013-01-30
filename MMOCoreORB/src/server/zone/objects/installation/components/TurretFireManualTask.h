/*
 * TurretFireManualTask.h
 *
 *  Created on: Jan 27, 2013
 *      Author: root
 */
#ifndef TURRETFIREMANUALTASK_H_
#define TURRETFIREMANUALTASK_H_
#include "engine/engine.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/creature/commands/TurretFireCommand.h"
#include "server/zone/objects/installation/components/TurretDataComponent.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/player/PlayerObject.h"

class TurretFireManualTask : public Task {
	ManagedReference<TangibleObject*> sceneObject;
	ManagedReference<SceneObject*> target;
	ManagedReference<CreatureObject*> attacker;


public:
	TurretFireManualTask(TangibleObject* turret, CreatureObject* attackerCreature, SceneObject* victim) {
		sceneObject = turret;
		target = victim;
		attacker = attackerCreature;

	}

	void run() {
		Locker lock(sceneObject);
		Locker lockv(target, sceneObject);

		String strName;

		CreatureObject* creature = NULL;

		if(target != NULL && target->isPlayerCreature()){
			creature = cast<CreatureObject*>(target.get());
			if(creature == NULL)
				strName = target->getObjectNameStringIdName();
			else
				strName = creature->getFirstName();
		} else
			strName = target->getObjectNameStringIdName();



		DataObjectComponentReference* data = sceneObject->getDataObjectComponent();

		if(data == NULL || creature == NULL)
			return;

		TurretDataComponent* turretData = cast<TurretDataComponent*>(data->get());

		if(turretData == NULL)
			return;

		if(target == NULL || creature->isDead() || creature->isIncapacitated()){
			attacker->sendSystemMessage("@hq:invalid_target"); //"That target has become unavailable. Please refresh terminal for latest target information.
			closeControls(attacker, turretData);
			return;
		}


		if(!CollisionManager::checkLineOfSight(target, sceneObject)){
			attacker->sendSystemMessage("@hq:no_line_of_site"); // The turret does not have line of site with that target and is unable to attack it.
			closeControls(attacker, turretData);
			return;
		}



		if(sceneObject->getZoneServer() != NULL ) {

			ManagedReference<ObjectController*> objectController = sceneObject->getZoneServer()->getObjectController();
			QueueCommand* command = objectController->getQueueCommand(String("turretfiremanual").hashCode());

			if(command != NULL){

				CombatQueueCommand* combatCommand = cast<CombatQueueCommand*>(command);
				if(combatCommand != NULL){
					WeaponObject* weapon = cast<WeaponObject*>(sceneObject->getSlottedObject("hold_r"));

					if(weapon == NULL){
						closeControls(attacker, turretData);
						return;
					}

					if(!sceneObject->isInRange(target,weapon->getMaxRange())){
						attacker->sendSystemMessage("@hq:invalid_target"); //"That target has become unavailable. Please refresh terminal for latest target information.
						closeControls(attacker, turretData);
						return;
					}

					TangibleObject* defenderObject = cast<TangibleObject*>(target.get());
					int result = CombatManager::instance()->doCombatAction(sceneObject, weapon, defenderObject, combatCommand);

					if(attacker != NULL)
						attacker->sendSystemMessage("Turret attacks " + strName + " for " + String::valueOf(result) + " damage.");

					turretData->updateAutoCooldown(GCWManagerImplementation::turretAutoFireTimeout);
					turretData->updateManualCooldown(weapon->getAttackSpeed());
					turretData->rescheduleManualFireTask(weapon->getAttackSpeed());
					return;
				}
			}

		}

		turretData->setManualFireTask(NULL);

	}

private:
	void closeControls(CreatureObject* creature, TurretDataComponent* turretData){
		turretData->setManualTarget(NULL);
		turretData->setManualFireTask(NULL);
		PlayerObject* ghost = attacker->getPlayerObject();
		if(ghost != NULL){
			ghost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);
		}

	}
};




#endif /* TURRETFIREMANUALTASK_H_ */
