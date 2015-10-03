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
	ManagedReference<CreatureObject*> target;
	bool isManual;

public:

	TurretFireTask(TangibleObject* turret, CreatureObject* victim, bool isManualFire = false) {
		sceneObject = turret;
		isManual = isManualFire;
		target = victim;
	}


	void run() {
		DataObjectComponentReference* data = sceneObject->getDataObjectComponent();
		if (data == NULL)
			return;

		TurretDataComponent* turretData = cast<TurretDataComponent*>(data->get());

		if (turretData == NULL)
			return;

		Locker lock(sceneObject);

		if (turretData->getTarget() == NULL && target != NULL)
			turretData->setTarget(target);
		else
			target = turretData->getTarget();

		turretData->setFireTask(this);

		if(!checkTarget(turretData)) {
			turretData->setTarget(NULL);
			turretData->setFireTask(NULL);
			return;
		}

		ManagedReference<ObjectController*> objectController = sceneObject->getZoneServer()->getObjectController();

		CombatQueueCommand* command = cast<CombatQueueCommand*>(objectController->getQueueCommand(STRING_HASHCODE("turretfire")));

		if (command != NULL) {
			if((!isManual && !turretData->canAutoFire())) {
				return;
			}

			executeCommand(turretData, command);
			checkTurretController(turretData);
		}
	}

	void executeCommand(TurretDataComponent* turretData, CombatQueueCommand* combatCommand ) {
		ManagedReference<WeaponObject*> weapon = sceneObject->getSlottedObject("hold_r").castTo<WeaponObject*>();

		if (weapon != NULL) {
			int result = CombatManager::instance()->doCombatAction(sceneObject, weapon, target, combatCommand);

			if (isManual) {
				if(turretData->getController() != NULL)
					turretData->getController()->sendSystemMessage("Turret attacks " + getTargetName() + " for " + String::valueOf(result) + " damage.");

				handleManualFire(turretData, weapon);

			} else {
				doAutoFire(turretData, weapon);
			}
		}
	}

	void doAutoFire(TurretDataComponent* turretData, WeaponObject* weapon) {
		turretData->updateAutoCooldown(weapon->getAttackSpeed());
		turretData->updateManualCooldown(weapon->getAttackSpeed());
		turretData->setTarget(target);
		turretData->rescheduleFireTask(weapon->getAttackSpeed(), false);
	}

	void handleManualFire(TurretDataComponent* turretData, WeaponObject* weapon) {
		turretData->updateAutoCooldown(GCWManagerImplementation::turretAutoFireTimeout);
		turretData->updateManualCooldown(weapon->getAttackSpeed());
		turretData->setTarget(target);
		turretData->rescheduleFireTask(weapon->getAttackSpeed(), true);
	}

	void checkTurretController(TurretDataComponent* turretData) {
		ManagedReference<CreatureObject*> attacker = cast<CreatureObject*>(turretData->getController());

		if (turretData->getController() != NULL) {
			PlayerObject* ghost = turretData->getController()->getPlayerObject();

			if(ghost != NULL)
				ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);
		}
	}

	String getTargetName() {
		String strName;

		if (target == NULL) {
			return strName;
		}

		CreatureObject* creature = NULL;

		if (target->isPlayerCreature()) {
			strName = creature->getFirstName();
		} else {
			strName = target->getObjectNameStringIdName();
		}

		return strName;
	}

	void closeControls(CreatureObject* controllerCharacter) {
		if (controllerCharacter == NULL)
			return;

		PlayerObject* ghost = controllerCharacter->getPlayerObject();

		if (ghost != NULL) {
			ghost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);
		}
	}

	bool checkTarget(TurretDataComponent* turretData) {
		ManagedReference<CreatureObject*> attacker = turretData->getController();

		ManagedReference<WeaponObject*> weapon = sceneObject->getSlottedObject("hold_r").castTo<WeaponObject*>();

		if (weapon == NULL || target == NULL)
			return false;


		if (!CollisionManager::checkLineOfSight(target, sceneObject)) {
			closeControls(attacker);

			if (attacker)
				attacker->sendSystemMessage("@hq:no_line_of_site"); // The turret does not have line of site with that target and is unable to attack it.

			return false;

		} else if (target->isDead() || target->isIncapacitated() || !sceneObject->isInRange(target, weapon->getMaxRange(false))) {

			closeControls(attacker);

			if (attacker)
				attacker->sendSystemMessage("@hq:invalid_target"); // That target has become unavailable. Please refresh terminal for latest target information.

			return false;
		}

		return true;
	}

	bool isManualFireTask() {
		return isManual;
	}

	void setManualTask(bool val) {
		isManual = val;
	}

};

#endif /* TURRETFIRETASK_H_ */
