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
	uint32 animationCRC;
	int initialDamage;
	float damageMultiplier;
	int foodMitigation;
	int jediMitigation;
	int jediFeedback;
	int psgMitigation;
	int armorMitigation;
	Vector<int> poolsToWound;
	int finalDamage;

public:
	DefenderHitList() {
		hit = 0;
		hitLocation = 0;
		animationCRC = 0;
		initialDamage = 0;
		damageMultiplier = 0;
		foodMitigation = 0;
		jediMitigation = 0;
		jediFeedback = 0;
		psgMitigation = 0;
		armorMitigation = 0;
		poolsToWound;
		finalDamage = 0;
	}


	DefenderHitList& operator= (const DefenderHitList& hitList) {
		if (this == &hitList)
			return *this;

		hit = hitList.hit;
		hitLocation = hitList.hitLocation;
		animationCRC = hitList.animationCRC;
		initialDamage = hitList.initialDamage;
		damageMultiplier = hitList.damageMultiplier;
		foodMitigation = hitList.foodMitigation;
		jediMitigation = hitList.jediMitigation;
		jediFeedback = hitList.jediFeedback;
		psgMitigation = hitList.psgMitigation;
		armorMitigation = hitList.armorMitigation;
		poolsToWound = hitList.poolsToWound;
		finalDamage = hitList.finalDamage;

		return *this;
	}

	void setHit(int val) {
		hit = val;
	}

	void setHitLocation(int val) {
		hitLocation = val;
	}

	void setAnimationCRC(uint32 val) {
		animationCRC = val;
	}

	void setInitialDamage(int initDam) {
		initialDamage = initDam;
	}

	void setDamageMultiplier(float damageMulti) {
		damageMultiplier = damageMulti;
	}

	void setFoodMitigation(int fMit) {
		foodMitigation = fMit;
	}

	void setJediMitigation(int jediArmMit) {
		jediMitigation = jediArmMit;
	}

	void setJediFeedback(int feedbackDam) {
		jediFeedback = feedbackDam;
	}

	void setPsgMitigation(int psgMit) {
		psgMitigation = psgMit;
	}

	void setArmorMitigation(int armorMit) {
		armorMitigation = armorMit;
	}

	void setPoolsToWound(Vector<int> woundPools) {
		poolsToWound = woundPools;
	}

	void setFinalDamage(int final) {
		finalDamage = final;
	}

	inline int getHit() {
		return hit;
	}

	inline int getHitLocation() {
		return hitLocation;
	}

	inline uint32 getAnimationCRC() {
		return animationCRC;
	}

	inline int getInitialDamage() {
		return initialDamage;
	}

	inline float getDamageMultiplier() {
		return damageMultiplier;
	}

	inline int getFoodMitigation() {
		return foodMitigation;
	}

	inline int getJediMitigation() {
		return jediMitigation;
	}

	inline int getJediFeedback() {
		return jediFeedback;
	}

	inline int getPsgMitigation() {
		return psgMitigation;
	}

	inline int getArmorMitigation() {
		return armorMitigation;
	}

	Vector<int> getPoolsToWound() {
		return poolsToWound;
	}

	inline int getFinalDamage() {
		return finalDamage;
	}
};

#endif /* DEFENDERHITLIST_H_ */
