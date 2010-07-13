/*
 * SharedWeaponObjectTemplate.h
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#ifndef SHAREDWEAPONOBJECTTEMPLATE_H_
#define SHAREDWEAPONOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedWeaponObjectTemplate: public SharedTangibleObjectTemplate {
protected:
	String weaponEffect;
	int weaponEffectIndex;
	int attackType;

	int damageType;

	int armorPiercing;

	int healthAttackCost;
	int actionAttackCost;
	int mindAttackCost;
	int forceCost;

	int pointBlankAccuracy;
	int pointBlankRange;

	int idealRange;
	int idealAccuracy;

	int maxRange;
	int maxRangeAccuracy;

	int minDamage;
	int maxDamage;

	float woundsRatio;

	int area;

	float attackSpeed;

	Vector<String> damageModifiers;
	Vector<String> speedModifiers;
	Vector<String> creatureAccuracyModifiers;
	Vector<String> defenderDefenseModifiers;
	Vector<String> certificationsRequired;
	Vector<String> defenderSecondaryDefenseModifiers;

	String xpType;

public:
	SharedWeaponObjectTemplate() {

	}

	~SharedWeaponObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	inline String getXpType() const {
		return xpType;
	}

	inline int getActionAttackCost() const {
		return actionAttackCost;
	}

	inline int getArea() const {
		return area;
	}

	inline int getArmorPiercing() const {
		return armorPiercing;
	}

	float getAttackSpeed() const {
		return attackSpeed;
	}

	inline int getForceCost() const {
		return forceCost;
	}

	inline int getHealthAttackCost() const {
		return healthAttackCost;
	}

	inline int getIdealAccuracy() const {
		return idealAccuracy;
	}

	inline int getIdealRange() const {
		return idealRange;
	}

	inline int getMaxDamage() const {
		return maxDamage;
	}

	inline int getMaxRange() const {
		return maxRange;
	}

	inline int getMaxRangeAccuracy() const {
		return maxRangeAccuracy;
	}

	inline int getMinDamage() const {
		return minDamage;
	}

	inline int getMindAttackCost() const {
		return mindAttackCost;
	}

	inline int getPointBlankAccuracy() const {
		return pointBlankAccuracy;
	}

	inline int getPointBlankRange() const {
		return pointBlankRange;
	}

	float getWoundsRatio() const {
		return woundsRatio;
	}

	void setActionAttackCost(int actionAttackCost) {
		this->actionAttackCost = actionAttackCost;
	}

	void setArea(int area) {
		this->area = area;
	}

	void setArmorPiercing(int armorPiercing) {
		this->armorPiercing = armorPiercing;
	}

	void setAttackSpeed(float attackSpeed) {
		this->attackSpeed = attackSpeed;
	}

	void setForceCost(int forceCost) {
		this->forceCost = forceCost;
	}

	void setHealthAttackCost(int healthAttackCost) {
		this->healthAttackCost = healthAttackCost;
	}

	void setIdealAccuracy(int idealAccuracy) {
		this->idealAccuracy = idealAccuracy;
	}

	void setIdealRange(int idealRange) {
		this->idealRange = idealRange;
	}

	void setMaxDamage(int maxDamage) {
		this->maxDamage = maxDamage;
	}

	void setMaxRange(int maxRange) {
		this->maxRange = maxRange;
	}

	void setMaxRangeAccuracy(int maxRangeAccuracy) {
		this->maxRangeAccuracy = maxRangeAccuracy;
	}

	void setMinDamage(int minDamage) {
		this->minDamage = minDamage;
	}

	void setMindAttackCost(int mindAttackCost) {
		this->mindAttackCost = mindAttackCost;
	}

	void setPointBlankAccuracy(int pointBlankAccuracy) {
		this->pointBlankAccuracy = pointBlankAccuracy;
	}

	void setPointBlankRange(int pointBlankRange) {
		this->pointBlankRange = pointBlankRange;
	}

	void setWoundsRatio(float woundsRatio) {
		this->woundsRatio = woundsRatio;
	}

	Vector<String>* getCertificationsRequired() {
		return &certificationsRequired;
	}

	Vector<String>* getCreatureAccuracyModifiers() {
		return &creatureAccuracyModifiers;
	}

	Vector<String>* getDamageModifiers() {
		return &damageModifiers;
	}

	inline int getDamageType() const {
		return damageType;
	}

	Vector<String>* getDefenderDefenseModifiers() {
		return &defenderDefenseModifiers;
	}

	Vector<String>* getDefenderSecondaryDefenseModifiers() {
		return &defenderSecondaryDefenseModifiers;
	}

	Vector<String>* getSpeedModifiers() {
		return &speedModifiers;
	}

	void setCertificationsRequired(Vector<String> certificationsRequired) {
		this->certificationsRequired = certificationsRequired;
	}

	void setCreatureAccuracyModifiers(Vector<String> creatureAccuracyModifiers) {
		this->creatureAccuracyModifiers = creatureAccuracyModifiers;
	}

	void setDamageModifiers(Vector<String> damageModifiers) {
		this->damageModifiers = damageModifiers;
	}

	void setDamageType(int damageType) {
		this->damageType = damageType;
	}

	void setDefenderDefenseModifiers(Vector<String> defenderDefenseModifiers) {
		this->defenderDefenseModifiers = defenderDefenseModifiers;
	}

	void setDefenderSecondaryDefenseModifiers(
			Vector<String> defenderSecondaryDefenseModifiers) {
		this->defenderSecondaryDefenseModifiers
				= defenderSecondaryDefenseModifiers;
	}

	void setSpeedModifiers(Vector<String> speedModifiers) {
		this->speedModifiers = speedModifiers;
	}

	inline int getAttackType() const {
		return attackType;
	}

	String getWeaponEffect() const {
		return weaponEffect;
	}

	inline int getWeaponEffectIndex() const {
		return weaponEffectIndex;
	}

	void setAttackType(int attackType) {
		this->attackType = attackType;
	}

	void setWeaponEffect(String weaponEffect) {
		this->weaponEffect = weaponEffect;
	}

	void setWeaponEffectIndex(int weaponEffectIndex) {
		this->weaponEffectIndex = weaponEffectIndex;
	}

};

#endif /* SHAREDWEAPONOBJECTTEMPLATE_H_ */
