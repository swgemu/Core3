/*
 * TurretDataComponent.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: root
 */

#include "TurretDataComponent.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/installation/components/TurretFireTask.h"
#include "server/zone/Zone.h"

void TurretDataComponent::initializeTransientMembers() {
	ManagedReference<SceneObject*> turret = getParent();

	if (turret == nullptr) {
		return;
	}

	templateData = dynamic_cast<SharedInstallationObjectTemplate*>(turret->getObjectTemplate());
}

Vector<CreatureObject*> TurretDataComponent::getAvailableTargets(bool aggroOnly) {
	Vector<CreatureObject*> targets;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(getParent());

	if (turret == nullptr)
		return targets;

	CloseObjectsVector* vec = (CloseObjectsVector*)turret->getCloseObjects();

	SortedVector<TreeEntry*> closeObjects;

	vec->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);

	int targetTotal = 0;

	for (int i = 0; i < closeObjects.size(); ++i) {
		CreatureObject* creo = cast<CreatureObject*>(closeObjects.get(i));

		if (creo != nullptr && checkTarget(creo, turret, aggroOnly)) {
			targets.add(creo);
		}
	}

	return targets;
}

CreatureObject* TurretDataComponent::selectTarget() {
	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(getParent());

	if (turret == nullptr)
		return nullptr;

	ManagedReference<CreatureObject*> lastTarget = lastAutoTarget.get();

	bool isVillageTurret = turret->getObjectTemplate()->getFullTemplateString().contains("turret_fs_village");

	if (!isVillageTurret || (lastTarget == nullptr || !checkTarget(lastTarget, turret, true))) {
		lastAutoTarget = nullptr;

		Vector<CreatureObject*> targets = getAvailableTargets(true);

		if (targets.size() == 0)
			return nullptr;

		lastTarget = targets.get(System::random(targets.size() - 1));
		lastAutoTarget = lastTarget;
	}

	return lastTarget;
}

bool TurretDataComponent::checkTarget(CreatureObject* creature, TangibleObject* turret, bool aggroOnly) {
	if (creature == nullptr || turret == nullptr)
		return false;

	if (!creature->isAttackableBy(turret) || !turret->isInRange(creature, maxRange))
		return false;

	if (aggroOnly && !turret->hasDefender(creature) && !turret->isAggressiveTo(creature))
		return false;

	if (!CollisionManager::checkLineOfSight(creature, turret))
		return false;

	return true;
}

void TurretDataComponent::updateAutoCooldown(float secondsToAdd) {
	int milisecondsToAdd = secondsToAdd*1000;
	nextAutoFireTime = Time();
	nextAutoFireTime.addMiliTime(milisecondsToAdd);
}

void TurretDataComponent::scheduleFireTask(CreatureObject* target, TangibleObject* terminal, int delay) {
	//PRE: turret is locked

	if (numberOfPlayersInRange.get() < 1) {
		return;
	}

	auto componentParent = getParent();

	if (componentParent == nullptr) {
		return;
	}

	ManagedReference<TurretObject*> turret = cast<TurretObject*>(componentParent);

	if (turret == nullptr) {
		return;
	}

	// Make sure the turret is in the zone
	if (turret->getZone() == nullptr) {
		return;
	}

	// Check for a task, if a pointer for one does not exist, create a new one
	if (turretTask == nullptr) {
		turretTask = new TurretFireTask(turret, terminal, target != nullptr);
	}

	TurretFireTask* turretFireTask = turretTask.castTo<TurretFireTask*>();

	if (turretFireTask == nullptr) {
		return;
	}

	if (target != nullptr) {
		if (turretFireTask->isManualFireTask()) {
			if (target != getManualTarget()) {
				setManualTarget(target);
			}
		} else if (target != getManualTarget()) {
			setManualTarget(target);

			turretFireTask->setManualFireTask(true);
			turretFireTask->setTerminal(terminal);
		}
	}

	if (target == nullptr && !turretFireTask->isManualFireTask()) {
		delay += getRescheduleDelay();
	}

	if (!turretFireTask->isScheduled()) {
		if (delay == 0) {
			turretFireTask->execute();
		} else {
			turretFireTask->schedule(delay);
		}
	} else if (turretFireTask->isManualFireTask()) {
		turretFireTask->reschedule(attackSpeed * 1000);
	}
}

void TurretDataComponent::rescheduleFireTask(bool wasManual, bool isManual) {
	if (numberOfPlayersInRange.get() < 1) {
		return;
	}

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(getParent());

	if (turret == nullptr || turret->getZone() == nullptr)
		return;

	TurretFireTask* task = turretTask.castTo<TurretFireTask*>();

	if (task == nullptr)
		return;

	if (wasManual) {
		updateAutoCooldown(getAutoFireTimeout());
	} else {
		updateAutoCooldown(attackSpeed);
	}

	if (isManual) {
		task->reschedule(attackSpeed * 1000);
	} else {
		setManualTarget(nullptr);

		task->setTerminal(nullptr);
		task->setManualFireTask(false);

		task->reschedule(getRescheduleDelay());
	}
}

int TurretDataComponent::getAutoFireTimeout() {
	int cooldown = 20;

	ManagedReference<InstallationObject*> turret = cast<InstallationObject*>(getParent());

	if (turret != nullptr) {
		Zone* zone = turret->getZone();

		if (zone != nullptr) {
			GCWManager* gcwMan = zone->getGCWManager();

			if (gcwMan != nullptr)
				cooldown = gcwMan->getTurretAutoFireTimeout();
		}
	}

	return cooldown;
}
