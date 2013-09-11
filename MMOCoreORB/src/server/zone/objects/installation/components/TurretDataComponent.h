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
	ManagedReference<CreatureObject*> target;
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
		target = NULL;
		turretFireTask = NULL;
	}

	~TurretDataComponent(){

	}

	void initializeTransientMembers();

	bool canAutoFire(){
		return (attackSpeed > 0 && nextFireTime.isPast()) ;
	}

	bool canManualFire(){
		return (attackSpeed > 0 && nextManualFireTime.isPast());
	}

	void refreshControlTimer(int seconds){
		controlTimeout = Time();
		controlTimeout.addMiliTime(seconds * 1000);
	}

	bool hasControlTimedOut(){
		return controlTimeout.isPast();
	}

	void updateAutoCooldown(float secondsToAdd);
	void updateManualCooldown(float secondsToAdd);

	bool isTurretData(){
		return true;
	}


	void setController(CreatureObject* creature){
		controller = creature;
	}

	CreatureObject* getController(){
		return controller;
	}

	void setTarget(CreatureObject* creature){
		target = creature;
	}

	CreatureObject* getTarget(){
		return target;
	}

	void setFireTask(Task* newTask){
		turretFireTask = newTask;
	}

	Task* getFireTask(){
		return turretFireTask;
	}

	void rescheduleManualFireTask(float secondsToWait);
	void rescheduleFireTask(float secondsToWait, bool manual);
	void setWeapon(WeaponObject* weapon);
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

	String getWeaponString();

	void fillAttributeList(AttributeListMessage* alm);


private:
	void addSerializableVariables(){
	}
};




#endif /* TURRETDATACOMPONENT_H_ */
