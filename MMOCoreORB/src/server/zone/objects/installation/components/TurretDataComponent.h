/*
 * TurretDataComponent.h
 *
 *  Created on: Nov 24, 2012
 *      Author: root
 */

#ifndef TURRETDATACOMPONENT_H_
#define TURRETDATACOMPONENT_H_
#include "engine/engine.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/templates/tangible/SharedInstallationObjectTemplate.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

class TurretDataComponent : public DataObjectComponent {

protected:
	int maxrange;
	Time nextFireTime;
	Time nextManualFireTime;
	Time controlTimeout;  // when the controller times out from inactivity and someone else can control it
	int attackSpeed;
	SharedInstallationObjectTemplate* templateData;
	ManagedReference<CreatureObject*> controller;
	ManagedReference<CreatureObject*> manualTarget;
	Vector<ManagedReference<CreatureObject*> > availableTargets;
	Reference<Task*> turretFireTask;

public:
	TurretDataComponent() {
		maxrange = 80;
		nextFireTime = Time();
		nextManualFireTime = Time();
		controlTimeout = Time();
		attackSpeed = 5;
		templateData = NULL;
		controller = NULL;
		manualTarget = NULL;
		turretFireTask = NULL;
	}

	~TurretDataComponent() {

	}

	void initializeTransientMembers();
	void setWeapon(WeaponObject* weapon);

	bool canAutoFire() {
		return (attackSpeed > 0 && nextFireTime.isPast()) ;
	}

	bool canManualFire() {
		return (attackSpeed > 0 && nextManualFireTime.isPast());
	}

	void refreshControlTimer(int seconds) {
		controlTimeout = Time();
		controlTimeout.addMiliTime(seconds * 1000);
	}

	bool hasControlTimedOut() {
		return controlTimeout.isPast();
	}

	bool isTurretData() {
		return true;
	}

	void setController(CreatureObject* creature) {
		controller = creature;
	}

	CreatureObject* getController() {
		return controller;
	}

	void setManualTarget(CreatureObject* creature) {
		manualTarget = creature;
	}

	CreatureObject* getManualTarget() {
		return manualTarget;
	}

	int getMaxRange () {
		return maxrange;
	}

	void setFireTask(Task* newTask) {
		turretFireTask = newTask;
	}

	Task* getFireTask() {
		return turretFireTask;
	}

	void addTarget(CreatureObject* creature);
	CreatureObject* selectTarget();
	bool checkTarget(CreatureObject* creature);

	void updateAutoCooldown(float secondsToAdd);
	void updateManualCooldown(float secondsToAdd);

	void rescheduleFireTask(float secondsToWait, bool manual);

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
