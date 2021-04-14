/*
DefenderHitList.h

Author: Hakry
*/

#ifndef DEFENDERHITLIST_H_
#define DEFENDERHITLIST_H_

#include "server/zone/objects/tangible/TangibleObject.h"

using namespace server::zone::objects::tangible;

class DefenderHitList : public Object {
	ManagedWeakReference<TangibleObject*> defender;

	int hit;
	uint8 hitLocation;
	int initialDamage;
	int foodMitigation;
	int jediArmorMitigation;
	int armorMitigation;
	int finalDamage;

public:
	DefenderHitList() {
		hit = 0;
		hitLocation = 0;
		foodMitigation = 0;
		jediArmorMitigation = 0;
		armorMitigation = 0;
		finalDamage = 0;
	}


	DefenderHitList& operator= (const DefenderHitList& hitList) {
		if (this == &hitList)
			return *this;

		defender = hitList.defender;
		hit = hitList.hit;
		hitLocation = hitList.hitLocation;
		foodMitigation = hitList.foodMitigation;
		jediArmorMitigation = hitList.jediArmorMitigation;
		armorMitigation = hitList.armorMitigation;
		finalDamage = hitList.finalDamage;

		return *this;
	}

	void setDefender(TangibleObject* tanO) {
		defender = tanO;
	}

	void setHit(int val) {
		hit = val;
	}

	void setInitialDamage(int initDam) {
		initialDamage = initDam;
	}

	void setFoodMitigation(int fMit) {
		foodMitigation = fMit;
	}

	void setJediArmorMitigation(int jediArmMit) {
		jediArmorMitigation = jediArmMit;
	}

	void setArmorMitigation(int armorMit) {
		armorMitigation = armorMit;
	}

	void setFinalDamage(int final) {
		finalDamage = final;
	}

	inline int getHit() {
		return hit;
	}

	inline int getInitialDamage() {
		return initialDamage;
	}

	inline int getFoodMitigation() {
		return foodMitigation;
	}

	inline int getJediArmorMitigation() {
		return jediArmorMitigation;
	}

	inline int getArmorMitigation() {
		return armorMitigation;
	}

	inline int getFinalDamage() {
		return finalDamage;
	}
};

#endif /* DEFENDERHITLIST_H_ */
