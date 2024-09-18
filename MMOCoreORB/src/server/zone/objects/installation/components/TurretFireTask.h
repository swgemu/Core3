/*
 * TurretFireTask.h
 *
 *  Created on: 20/12/2012
 *      Author: victor
 */

#ifndef TURRETFIRETASK_H_
#define TURRETFIRETASK_H_

#include "engine/engine.h"
#include "server/zone/objects/installation/TurretObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/terminal/components/TurretControlTerminalDataComponent.h"

class TurretFireTask : public Task {
	ManagedWeakReference<TurretObject*> weakTurret;
	ManagedWeakReference<TangibleObject*> weakTerminal;
	bool isManual;

public:
	TurretFireTask(TurretObject* turret, TangibleObject* terminal, bool manual) {
		weakTurret = turret;
		weakTerminal = terminal;
		isManual = manual;
	}

	void run() {
		ManagedReference<TurretObject*> turret = weakTurret.get();

		if (turret == nullptr) {
			return;
		}

		TurretDataComponent* turretData = cast<TurretDataComponent*>(turret->getDataObjectComponent()->get());

		if (turretData == nullptr) {
			return;
		}

		auto zoneServer = turret->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		Locker lock(turret);

		ManagedReference<CreatureObject*> target = nullptr;

		turret->removeDefenders();

		if (isManual) {
			target = turretData->getManualTarget();

			if(!checkTarget(turret, target)) {
				turretData->rescheduleFireTask(true, false);
				return;
			}
		} else {
			ManagedReference<CreatureObject*> controller = turretData->getController();

			if (controller != nullptr) {
				closeControls(controller);
				turretData->setController(nullptr);
			}

			target = turretData->selectTarget();

			if (target == nullptr) {
				turretData->rescheduleFireTask(false, false);
				return;
			}
		}

		ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();

		if (objectController == nullptr) {
			return;
		}

		ManagedReference<WeaponObject*> turretWeapon = turret->getTurretWeapon();

		if (turretWeapon == nullptr) {
			return;
		}

		const CombatQueueCommand* command = cast<const CombatQueueCommand*>(objectController->getQueueCommand(STRING_HASHCODE("turretfire")));

		if (command == nullptr) {
			return;
		}

		Locker clocker(target, turret);

		turret->setDefender(target);
		target->setCombatState();

		CombatManager::instance()->doCombatAction(turret, turretWeapon, target, command);

		if (isManual) {
			if (checkTurretController(turretData))
				turretData->rescheduleFireTask(true, true);
			else
				turretData->rescheduleFireTask(true, false);
		} else {
			turretData->rescheduleFireTask(false, false);
		}
	}

	bool checkTurretController(TurretDataComponent* turretData) {
		ManagedReference<CreatureObject*> attacker = cast<CreatureObject*>(turretData->getController());
		ManagedReference<TangibleObject*> terminal = weakTerminal.get();

		if (attacker == nullptr || terminal == nullptr) {
			return false;
		}

		PlayerObject* ghost = attacker->getPlayerObject();

		if (ghost == nullptr)
			return false;

		TurretControlTerminalDataComponent* controlData = cast<TurretControlTerminalDataComponent*>(terminal->getDataObjectComponent()->get());

		if (controlData == nullptr)
			return false;

		if (!ghost->hasSuiBox(controlData->getSuiBoxID()))
			return false;

		return true;
	}

	void closeControls(CreatureObject* controllerCharacter) {
		if (controllerCharacter == nullptr)
			return;

		PlayerObject* ghost = controllerCharacter->getPlayerObject();

		if (ghost != nullptr) {
			ghost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);
		}
	}

	bool checkTarget(TangibleObject* turret, CreatureObject* target) {
		if (target == nullptr || turret == nullptr)
			return false;

		TurretDataComponent* turretData = cast<TurretDataComponent*>(turret->getDataObjectComponent()->get());

		if (turretData == nullptr)
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
		weakTerminal = terminal;
	}
};

#endif /* TURRETFIRETASK_H_ */
