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
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/PlayerObject.h"

class TurretFireTask : public Task {
	ManagedReference<TangibleObject*> sceneObject;
	ManagedReference<SceneObject*> target;
	bool isManual;

public:

	TurretFireTask(TangibleObject* turret, SceneObject* victim, bool isManualFire = false) {
		sceneObject = turret;
		isManual = isManualFire;
		target = victim;
	}


	void run() {
		DataObjectComponentReference* data = sceneObject->getDataObjectComponent();
		if(data == NULL)
			return;

		TurretDataComponent* turretData = cast<TurretDataComponent*>(data->get());

		if(turretData == NULL)
			return;

		Locker lock(sceneObject);
		Locker lockv(target, sceneObject);

		if(turretData->getTarget() == NULL && target != NULL)
			turretData->setTarget(cast<CreatureObject*>(target.get()));
		else
			target = turretData->getTarget();

		turretData->setFireTask(this);

		if(sceneObject->getZoneServer() != NULL) {

			if(!checkTarget(turretData)) {
				turretData->setTarget(NULL);
				turretData->setFireTask(NULL);
				return;
			}

			ManagedReference<ObjectController*> objectController = sceneObject->getZoneServer()->getObjectController();
			String commandString = (isManual) ? "turretfire" : "turretfire";
			QueueCommand* command = objectController->getQueueCommand(commandString.hashCode());

			if(command != NULL){

				CombatQueueCommand* combatCommand = cast<CombatQueueCommand*>(command);
				if(combatCommand != NULL){
					if((!isManual && !turretData->canAutoFire())) {
						return;
					}

					executeCommand(turretData, combatCommand);
					checkTurretController(turretData);
				}
			}

		}
	}

	void executeCommand(TurretDataComponent* turretData, CombatQueueCommand* combatCommand ){
		WeaponObject* weapon = cast<WeaponObject*>(sceneObject->getSlottedObject("hold_r"));

		if (weapon != NULL) {
			TangibleObject* defenderObject = cast<TangibleObject*>(target.get());
			int result = CombatManager::instance()->doCombatAction(sceneObject, weapon, defenderObject, combatCommand);

			if(isManual){
				if(turretData->getController() != NULL)
					turretData->getController()->sendSystemMessage("Turret attacks " + getTargetName(defenderObject) + " for " + String::valueOf(result) + " damage.");

				handleManualFire(turretData, weapon, defenderObject);

			} else{
				doAutoFire(turretData, weapon, defenderObject);
			}
		} else {
			sceneObject->error("null weapon in TurretFireTask for " + sceneObject->getObjectTemplate()->getTemplateFileName());
		}

	}

	void doAutoFire(TurretDataComponent* turretData, WeaponObject* weapon, SceneObject* defenderObject){
		turretData->updateAutoCooldown(weapon->getAttackSpeed());
		turretData->updateManualCooldown(weapon->getAttackSpeed());
		turretData->setTarget(cast<CreatureObject*>(defenderObject));
		turretData->rescheduleFireTask(weapon->getAttackSpeed(), false);
	}

	void handleManualFire(TurretDataComponent* turretData, WeaponObject* weapon, SceneObject* defenderObject){
		turretData->updateAutoCooldown(GCWManagerImplementation::turretAutoFireTimeout);
		turretData->updateManualCooldown(weapon->getAttackSpeed());
		turretData->setTarget(cast<CreatureObject*>(defenderObject));
		turretData->rescheduleFireTask(weapon->getAttackSpeed(), true);
	}

	void checkTurretController(TurretDataComponent* turretData){
		if(turretData->getController() != NULL){
			PlayerObject* ghost = turretData->getController()->getPlayerObject();

			if(ghost != NULL)
				ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

		}
	}

	String getTargetName(SceneObject* target){

		String strName;
		CreatureObject* creature = NULL;

		if(target != NULL && target->isPlayerCreature()){
			creature = cast<CreatureObject*>(target);
			if(creature == NULL)
				strName = target->getObjectNameStringIdName();
			else
				strName = creature->getFirstName();
		} else
			strName = target->getObjectNameStringIdName();

		return strName;
	}

	void closeControls(CreatureObject* controllerCharacter, TurretDataComponent* turretData){
		if(controllerCharacter == NULL)
			return;

		PlayerObject* ghost = controllerCharacter->getPlayerObject();
		if(ghost != NULL){
			ghost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);
		}

	}

	bool checkTarget(TurretDataComponent* turretData){
		if(turretData->getTarget() == NULL)
			return false;

		ManagedReference<CreatureObject*> targetCreature = cast<CreatureObject*>(turretData->getTarget());
		ManagedReference<CreatureObject*> attacker = cast<CreatureObject*>(turretData->getController());

		ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject->getSlottedObject("hold_r"));

		if(weapon == NULL || targetCreature == NULL)
			return false;


		if(!CollisionManager::checkLineOfSight(target, sceneObject)){
			closeControls(attacker, turretData);

			if(attacker)
				attacker->sendSystemMessage("@hq:no_line_of_site"); // The turret does not have line of site with that target and is unable to attack it.

			return false;
		} else if(targetCreature->isDead() || targetCreature->isIncapacitated() || !sceneObject->isInRange(targetCreature,weapon->getMaxRange(false))){

			closeControls(attacker, turretData);

			if(attacker)
				attacker->sendSystemMessage("@hq:invalid_target"); //"That target has become unavailable. Please refresh terminal for latest target information.

			return false;
		}

		return true;
	}

	bool isManualFireTask(){
		return isManual;
	}

	void setManualTask(bool val){
		isManual = val;
	}

};

#endif /* TURRETFIRETASK_H_ */
