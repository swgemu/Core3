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
	int forceFeedback;
	int forceAbsorb;
	int psgMitigation;
	int armorMitigation;
	Vector<int> poolsToWound;

public:
	DefenderHitList() {
		defender = nullptr;
		hit = 0;
		hitLocation = 0;
		animationCRC = 0;
		initialDamage = 0;
		damageMultiplier = 0;
		foodMitigation = 0;
		jediMitigation = 0;
		forceFeedback = 0;
		forceAbsorb = 0;
		psgMitigation = 0;
		armorMitigation = 0;
	}

	~DefenderHitList() {
	}

	void setDefender(TangibleObject* tano) {
		defender = tano;
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

	void setForceFeedback(int feedbackDam) {
		forceFeedback = feedbackDam;
	}

	void setForceAbsorb(int amountAbsorbed) {
		forceAbsorb = amountAbsorbed;
	}

	void setPsgMitigation(int psgMit) {
		psgMitigation = psgMit;
	}

	void setArmorMitigation(int armorMit) {
		armorMitigation = armorMit;
	}

	void setPoolsToWound(const Vector<int>& woundPools) {
		poolsToWound = woundPools;
	}

	ManagedReference<TangibleObject*> getDefender() {
		return defender.get();
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

	inline int getForceFeedback() {
		return forceFeedback;
	}

	inline int getForceAbsorb () {
		return forceAbsorb;
	}

	inline int getPsgMitigation() {
		return psgMitigation;
	}

	inline int getArmorMitigation() {
		return armorMitigation;
	}

	const Vector<int>& getPoolsToWound() {
		return poolsToWound;
	}
};

#endif /* DEFENDERHITLIST_H_ */