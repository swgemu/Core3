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

	Vector<String> damageModifiers;
	Vector<String> speedModifiers;
	Vector<String> creatureAccuracyModifiers;
	Vector<String> defenderDefenseModifiers;
	Vector<String> certificationsRequired;
	Vector<String> defenderSecondaryDefenseModifiers;

public:
	SharedWeaponObjectTemplate() {

	}

	~SharedWeaponObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	Vector<String> getCertificationsRequired() const {
		return certificationsRequired;
	}

	Vector<String> getCreatureAccuracyModifiers() const {
		return creatureAccuracyModifiers;
	}

	Vector<String> getDamageModifiers() const {
		return damageModifiers;
	}

	int getDamageType() const {
		return damageType;
	}

	Vector<String> getDefenderDefenseModifiers() const {
		return defenderDefenseModifiers;
	}

	Vector<String> getDefenderSecondaryDefenseModifiers() const {
		return defenderSecondaryDefenseModifiers;
	}

	Vector<String> getSpeedModifiers() const {
		return speedModifiers;
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

	int getAttackType() const {
		return attackType;
	}

	String getWeaponEffect() const {
		return weaponEffect;
	}

	int getWeaponEffectIndex() const {
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
