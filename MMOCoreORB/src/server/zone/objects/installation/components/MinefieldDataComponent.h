/*
 * MinefieldDataComponent.h
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#ifndef MINEFIELDDATACOMPONENT_H_
#define MINEFIELDDATACOMPONENT_H_
#include "engine/engine.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "templates/installation/SharedInstallationObjectTemplate.h"

class MinefieldDataComponent : public DataObjectComponent {
protected:
	uint64 nextExplodeTime;
	int attackSpeed;
	const static int CAPACITY = 20;
	Vector<WeaponObject*> mines;
	SharedInstallationObjectTemplate* templateData;
	int maxRange;
public:
	MinefieldDataComponent() {
		attackSpeed = 5;
		templateData = NULL;
		nextExplodeTime = time(0);
		maxRange = 5;
		addSerializableVariables();
	}


	~MinefieldDataComponent(){

	}

	void initializeTransientMembers(){
		//Logger::Logger tlog("minefieldata");
		//tlog.info("initializing minefield transients",true);
		if(getParent() != NULL){
			templateData = dynamic_cast<SharedInstallationObjectTemplate*>(getParent()->getObjectTemplate());
			attackSpeed = 5;
		}
	}

	bool isMinefieldData(){
		return true;
	}

	bool canExplode(){
		return (time(0) > nextExplodeTime);
	}

	int getCapacity(){
		return CAPACITY;
	}

	void updateCooldown(int cooldown){
		//Logger::Logger tlog("minefieldata");
		//tlog.info("updating cooldown on minefield to " + String::valueOf(cooldown),true);
		nextExplodeTime = time(0) + cooldown;
	}

	void addMine(WeaponObject* weapon){
		mines.add(weapon);
	}

	WeaponObject* getMine(int indx){
		return mines.get(indx);
	}

	WeaponObject* removeMine(int indx){
		return mines.remove(indx);
	}

	int getMineCapacity(){
		return CAPACITY;
	}

	int getMineCount(){
		return mines.size();
	}

	void setMaxRange(int val){
		maxRange = val;
	}

	int getMaxRange(){
		return maxRange;
	}





private:
	void addSerializableVariables(){
		addSerializableVariable("mines",&mines);
	}



};




#endif /* MINEFIELDDATACOMPONENT_H_ */
