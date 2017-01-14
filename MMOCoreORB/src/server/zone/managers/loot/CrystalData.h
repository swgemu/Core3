#ifndef CRYSTALDATA_H_
#define CRYSTALDATA_H_

#include "engine/engine.h"

class CrystalData : public Object {
	int minDamage;
	int maxDamage;
	int minHitpoints;
	int maxHitpoints;
	int minHealthSac;
	int maxHealthSac;
	int minActionSac;
	int maxActionSac;
	int minMindSac;
	int maxMindSac;
	float minAttackSpeed;
	float maxAttackSpeed;
	float minForceCost;
	float maxForceCost;
	int minWoundChance;
	int maxWoundChance;

public:
	CrystalData() : Object(), minDamage(0), maxDamage(0), minHitpoints(0), maxHitpoints(0), minHealthSac(0), maxHealthSac(0), minActionSac(0), maxActionSac(0),
		minMindSac(0), maxMindSac(0), minAttackSpeed(0.0), maxAttackSpeed(0.0), minForceCost(0.0), maxForceCost(0.0), minWoundChance(0), maxWoundChance(0) {
	}

	CrystalData(const CrystalData& data) : Object() {
		minDamage = data.minDamage;
		maxDamage = data.maxDamage;
		minHitpoints = data.minHitpoints;
		maxHitpoints = data.maxHitpoints;
		minHealthSac = data.minHealthSac;
		maxHealthSac = data.maxHealthSac;
		minActionSac = data.minActionSac;
		maxActionSac = data.maxActionSac;
		minMindSac = data.minMindSac;
		maxMindSac = data.maxMindSac;
		minAttackSpeed = data.minAttackSpeed;
		maxAttackSpeed = data.maxAttackSpeed;
		minForceCost = data.minForceCost;
		maxForceCost = data.maxForceCost;
		minWoundChance = data.minWoundChance;
		maxWoundChance = data.maxWoundChance;
	}

	CrystalData& operator=(const CrystalData& data) {
		if (this == &data)
			return *this;

		minDamage = data.minDamage;
		maxDamage = data.maxDamage;
		minHitpoints = data.minHitpoints;
		maxHitpoints = data.maxHitpoints;
		minHealthSac = data.minHealthSac;
		maxHealthSac = data.maxHealthSac;
		minActionSac = data.minActionSac;
		maxActionSac = data.maxActionSac;
		minMindSac = data.minMindSac;
		maxMindSac = data.maxMindSac;
		minAttackSpeed = data.minAttackSpeed;
		maxAttackSpeed = data.maxAttackSpeed;
		minForceCost = data.minForceCost;
		maxForceCost = data.maxForceCost;
		minWoundChance = data.minWoundChance;
		maxWoundChance = data.maxWoundChance;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		minDamage = luaObject->getIntField("minDamage");
		maxDamage = luaObject->getIntField("maxDamage");
		minHitpoints = luaObject->getIntField("minHitpoints");
		maxHitpoints = luaObject->getIntField("maxHitpoints");
		minHealthSac = luaObject->getIntField("minHealthSac");
		maxHealthSac = luaObject->getIntField("maxHealthSac");
		minActionSac = luaObject->getIntField("minActionSac");
		maxActionSac = luaObject->getIntField("maxActionSac");
		minMindSac = luaObject->getIntField("minMindSac");
		maxMindSac = luaObject->getIntField("maxMindSac");
		minAttackSpeed = luaObject->getFloatField("minAttackSpeed");
		maxAttackSpeed = luaObject->getFloatField("maxAttackSpeed");
		minForceCost = luaObject->getFloatField("minForceCost");
		maxForceCost = luaObject->getFloatField("maxForceCost");
		minWoundChance = luaObject->getIntField("minWoundChance");
		maxWoundChance = luaObject->getIntField("maxWoundChance");
	}

	inline int getMinDamage() {
		return minDamage;
	}

	inline int getMaxDamage() {
		return maxDamage;
	}

	inline int getMinHitpoints() {
		return minHitpoints;
	}

	inline int getMaxHitpoints() {
		return maxHitpoints;
	}

	inline int getMinHealthSac() {
		return minHealthSac;
	}

	inline int getMaxHealthSac() {
		return maxHealthSac;
	}

	inline int getMinActionSac() {
		return minActionSac;
	}

	inline int getMaxActionSac() {
		return maxActionSac;
	}

	inline int getMinMindSac() {
		return minMindSac;
	}

	inline int getMaxMindSac() {
		return maxMindSac;
	}

	inline int getMinWoundChance() {
		return minWoundChance;
	}

	inline float getMinAttackSpeed() {
		return minAttackSpeed;
	}

	inline float getMaxAttackSpeed() {
		return maxAttackSpeed;
	}

	inline float getMinForceCost() {
		return minForceCost;
	}

	inline float getMaxForceCost() {
		return maxForceCost;
	}

	inline int getMaxWoundChance() {
		return maxWoundChance;
	}

};

#endif /* CRYSTALDATA_H_ */
