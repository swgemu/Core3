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
class TurretDataComponent : public DataObjectComponent {

protected:
	int maxrange;
	uint64 nextFireTime;
	int attackSpeed;
	SharedInstallationObjectTemplate* templateData;

	float kinetic;
	/*
	float energy;
	float electricity;
	float stun;
	float blast;
	float heat;
	float cold;
	float acid;
	float lightSaber;
	float chanceHit;
	String weaponString;
	*/



public:
	TurretDataComponent() {
		maxrange = 80;
		nextFireTime = time(0);
		attackSpeed = 5;
		templateData = NULL;
		/*
		kinetic = 0;
		energy = 0;
		electricity = 0;
		stun = 0;
		blast = 0;
		heat = 0;
		cold = 0;
		acid = 0;
		lightSaber = 0;
		chanceHit = .5;
		weaponString = "object/weapon/ranged/rifle/rifle_dlt20.iff";
		*/
		//addSerializableVariables();

	}

	~TurretDataComponent(){

	}

	void initializeTransientMembers();

	bool canFire(){
		return (attackSpeed > 0 && time(0) > nextFireTime);
	}

	void updateCooldown();

	bool isTurretData(){
		return true;
	}

	void setWeapon(WeaponObject* weapon);
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

		//addSerializableVariable("maxrange",&maxrange);
		/*
		addSerializableVariable("kinetic",&kinetic);
		addSerializableVariable("energy",&energy);
		addSerializableVariable("acid",&acid);
		addSerializableVariable("listSaber",&lightSaber);
		addSerializableVariable("cold",&cold);
		addSerializableVariable("blast",&blast);
		addSerializableVariable("stun",&stun);
		addSerializableVariable("heat",&heat);
		addSerializableVariable("electricity",&electricity);
		addSerializableVariable("weaponString",&weaponString);
		addSerializableVariable("chanceHit",&chanceHit);
		*/

	}
};




#endif /* TURRETDATACOMPONENT_H_ */
