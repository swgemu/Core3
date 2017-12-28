/*
 * TurretDataComponent.h
 *
 *  Created on: Nov 24, 2012
 *      Author: root
 */

#ifndef TURRETDATACOMPONENT_H_
#define TURRETDATACOMPONENT_H_
#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "engine/core/Task.h"
#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "system/lang/Time.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "system/thread/atomic/AtomicInteger.h"
#include "system/util/Vector.h"
#include "templates/installation/SharedInstallationObjectTemplate.h"

class SharedInstallationObjectTemplate;
namespace server {
namespace zone {
namespace objects {
namespace tangible {
class TangibleObject;
namespace weapon {
class WeaponObject;
}  // namespace weapon
}  // namespace tangible
}  // namespace objects
namespace packets {
namespace scene {
class AttributeListMessage;
}  // namespace scene
}  // namespace packets
}  // namespace zone
}  // namespace server

class TurretDataComponent : public DataObjectComponent {

protected:
	int maxRange;
	float attackSpeed;
	Time nextAutoFireTime;
	SharedInstallationObjectTemplate* templateData;
	ManagedWeakReference<CreatureObject*> controller;
	ManagedWeakReference<CreatureObject*> manualTarget;
	ManagedWeakReference<CreatureObject*> lastAutoTarget;
	Reference<Task*> turretFireTask;
	AtomicInteger numberOfPlayersInRange;

public:
	TurretDataComponent() {
		maxRange = 80;
		attackSpeed = 1;
		nextAutoFireTime = Time();
		templateData = NULL;
		controller = NULL;
		manualTarget = NULL;
		turretFireTask = NULL;
	}

	~TurretDataComponent() {

	}

	void initializeTransientMembers();
	void setWeapon(WeaponObject* weapon);

	int getRescheduleDelay() {
		int delay = 0;

		if (nextAutoFireTime.isFuture())
			delay = Time().miliDifference(nextAutoFireTime);

		return delay;
	}

	bool isTurretData() {
		return true;
	}

	void setController(CreatureObject* creature) {
		controller = creature;
	}

	CreatureObject* getController() {
		return controller.get();
	}

	void setManualTarget(CreatureObject* creature) {
		manualTarget = creature;
	}

	CreatureObject* getManualTarget() {
		return manualTarget.get();
	}

	int getMaxRange () {
		return maxRange;
	}

	float getAttackSpeed() {
		return attackSpeed;
	}

	Task* getFireTask() {
		return turretFireTask;
	}

	Vector<CreatureObject*> getAvailableTargets(bool aggroOnly);
	CreatureObject* selectTarget();
	bool checkTarget(CreatureObject* creature, TangibleObject* turret, bool aggroOnly);

	void updateAutoCooldown(float secondsToAdd);

	void scheduleFireTask(CreatureObject* target, TangibleObject* terminal, int delay = 0);
	void rescheduleFireTask(bool wasManual, bool isManual);
	int getAutoFireTimeout();

	uint32 getNumberOfPlayersInRange() {
		return numberOfPlayersInRange.get();
	}

	uint32 incrementNumberOfPlayersInRange() {
		return numberOfPlayersInRange.increment();
	}

	uint32 decrementNumberOfPlayersInRange() {
		return numberOfPlayersInRange.decrement();
	}

	bool compareAndSetNumberOfPlayersInRange(uint32 oldVal, uint32 newVal) {
		return numberOfPlayersInRange.compareAndSet(oldVal, newVal);
	}
	void fillAttributeList(AttributeListMessage* alm);

	unsigned int getArmorRating();
	float getKinetic();
	float getEnergy();
	float getElectricity();
	float getStun();
	float getBlast();
	float getHeat();
	float getCold();
	float getAcid();
	float getLightSaber();
	float getChanceHit();
};

#endif /* TURRETDATACOMPONENT_H_ */
