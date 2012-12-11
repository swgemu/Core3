/*
 * TurretDataComponent.h
 *
 *  Created on: Nov 24, 2012
 *      Author: root
 */

#ifndef TURRETDATACOMPONENT_H_
#define TURRETDATACOMPONENT_H_
#include "server/zone/objects/scene/components/DataObjectComponent.h"

class TurretDataComponent : public DataObjectComponent{
protected:
	int maxrange;
	uint64 nextFireTime;
	const static uint64 fireCooldown = 5;
	Logger::Logger tlog;

public:
	TurretDataComponent()  {
		maxrange = 65;
		nextFireTime = time(0);

	}

	~TurretDataComponent(){

	}

	bool canFire(){
		uint64 rightnow = time(0);
		//info("now is " + String::valueOf(rightnow) + " nextFire is " + String::valueOf(nextFireTime),true);
		return (rightnow > nextFireTime);
	}

	void updateCooldown(){
		nextFireTime = time(0) + fireCooldown;
		//info("setting nextFireTime to " + String::valueOf(nextFireTime),true);
	}

	bool isTurretData(){
		return true;
	}

	int getArmor();
};




#endif /* TURRETDATACOMPONENT_H_ */
