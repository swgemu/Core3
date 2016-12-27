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
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/terminal/components/TurretControlTerminalDataComponent.h"

class TurretFireTask : public Task {
	ManagedWeakReference<TangibleObject*> turretObject;
	ManagedWeakReference<TangibleObject*> terminalObject;
	bool isManual;

public:

	TurretFireTask(TangibleObject* turret, TangibleObject* terminal, bool manual) {
		turretObject = turret;
		terminalObject = terminal;
		isManual = manual;
	}


	void run() {
		ManagedReference<TangibleObject*> turret = turretObject.get();

		if (turret == NULL)
			return;

		TurretDataComponent* turretData = cast<TurretDataComponent*>(turret->getDataObjectComponent()->get());

		if (turretData == NULL)
			return;

		Locker lock(turret);

		ManagedReference<CreatureObject*> target = NULL;

		if (isManual) {
			target = turretData->getManualTarget();

			if(!checkTarget(turret, target)) {
				turretData->rescheduleFireTask(true, false);
				return;
			}
		} else {
			ManagedReference<CreatureObject*> controller = turretData->getController();

			if (controller != NULL) {
				closeControls(controller);
				turretData->setController(NULL);
			}

			target = turretData->selectTarget();

			if (target == NULL) {
				turretData->rescheduleFireTask(false, false);
				return;
			}
		}

		ManagedReference<ObjectController*> objectController = turret->getZoneServer()->getObjectController();

		CombatQueueCommand* command = cast<CombatQueueCommand*>(objectController->getQueueCommand(STRING_HASHCODE("turretfire")));
		ManagedReference<WeaponObject*> weapon = turret->getSlottedObject("hold_r").castTo<WeaponObject*>();

		if (command != NULL && weapon != NULL) {
			CombatManager::instance()->doCombatAction(turret, weapon, target, command);

			if (isManual) {
				if (checkTurretController(turretData))
					turretData->rescheduleFireTask(true, true);
				else
					turretData->rescheduleFireTask(true, false);
			} else {
				turretData->rescheduleFireTask(false, false);
			}
		}
	}

	bool checkTurretController(TurretDataComponent* turretData) {
		ManagedReference<CreatureObject*> attacker = cast<CreatureObject*>(turretData->getController());
		ManagedReference<TangibleObject*> terminal = terminalObject.get();

		if (attacker == NULL || terminal == NULL)
			return false;

		PlayerObject* ghost = attacker->getPlayerObject();

		if (ghost == NULL)
			return false;

		TurretControlTerminalDataComponent* controlData = cast<TurretControlTerminalDataComponent*>(terminal->getDataObjectComponent()->get());

		if (controlData == NULL)
			return false;

		if (!ghost->hasSuiBox(controlData->getSuiBoxID()))
			return false;

		return true;
	}

	void closeControls(CreatureObject* controllerCharacter) {
		if (controllerCharacter == NULL)
			return;

		PlayerObject* ghost = controllerCharacter->getPlayerObject();

		if (ghost != NULL) {
			ghost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);
		}
	}

	bool checkTarget(TangibleObject* turret, CreatureObject* target) {
		if (target == NULL || turret == NULL)
			return false;

		TurretDataComponent* turretData = cast<TurretDataComponent*>(turret->getDataObjectComponent()->get());

		if (turretData == NULL)
			return false;

		ManagedReference<CreatureObject*> attacker = turretData->getController();

		if (!target->isAttackableBy(turret) || !turret->isInRange(target, turretData->getMaxRange())) {

			closeControls(attacker);

			if (attacker)
				attacker->sendSystemMessage("@hq:invalid_target"); // That target has become unavailable. Please refresh terminal for latest target information.

			return false;
		}

		if (!CollisionManager::checkLineOfSight(target, turret)) {
			closeControls(attacker);

			if (attacker)
				attacker->sendSystemMessage("@hq:no_line_of_site"); // The turret does not have line of site with that target and is unable to attack it.

			return false;

		}

		return true;
	}

	bool isManualFireTask() {
		return isManual;
	}

	void setManualFireTask(bool man) {
		isManual = man;
	}

	void setTerminal(TangibleObject* terminal) {
		terminalObject = terminal;
	}
};

#endif /* TURRETFIRETASK_H_ */
