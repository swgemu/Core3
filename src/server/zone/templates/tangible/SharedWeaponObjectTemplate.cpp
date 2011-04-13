/*
 * SharedWeaponObjectTemplate.cpp
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#include "SharedWeaponObjectTemplate.h"

void SharedWeaponObjectTemplate::readObject(LuaObject* templateData) {
	SharedTangibleObjectTemplate::readObject(templateData);

	weaponEffect = templateData->getStringField("weaponEffect");
	weaponEffectIndex = templateData->getIntField("weaponEffectIndex");
	attackType = templateData->getIntField("attackType");

	xpType = templateData->getStringField("xpType");

	damageType = templateData->getIntField("damageType");

	LuaObject certifications = templateData->getObjectField("certificationsRequired");

	for (int i = 1; i <= certifications.getTableSize(); ++i) {
		certificationsRequired.add(certifications.getStringAt(i));
	}

	certifications.pop();

	LuaObject accMods = templateData->getObjectField("creatureAccuracyModifiers");

	for (int i = 1; i <= accMods.getTableSize(); ++i) {
		creatureAccuracyModifiers.add(accMods.getStringAt(i));
	}

	accMods.pop();

	LuaObject defMods = templateData->getObjectField("defenderDefenseModifiers");

	for (int i = 1; i <= defMods.getTableSize(); ++i) {
		defenderDefenseModifiers.add(defMods.getStringAt(i));
	}

	defMods.pop();

	LuaObject dmgMods = templateData->getObjectField("damageModifiers");

	for (int i = 1; i <= dmgMods.getTableSize(); ++i) {
		damageModifiers.add(dmgMods.getStringAt(i));
	}

	dmgMods.pop();

	LuaObject speedMods = templateData->getObjectField("speedModifiers");

	for (int i = 1; i <= speedMods.getTableSize(); ++i) {
		speedModifiers.add(speedMods.getStringAt(i));
	}

	speedMods.pop();

	LuaObject secMods = templateData->getObjectField("defenderSecondaryDefenseModifiers");

	for (int i = 1; i <= secMods.getTableSize(); ++i)
		defenderSecondaryDefenseModifiers.add(secMods.getStringAt(i));

	secMods.pop();

	armorPiercing = templateData->getIntField("armorPiercing");

	healthAttackCost = templateData->getIntField("healthAttackCost");
	actionAttackCost = templateData->getIntField("actionAttackCost");
	mindAttackCost = templateData->getIntField("mindAttackCost");
	forceCost = templateData->getIntField("forceCost");

	pointBlankAccuracy = templateData->getIntField("pointBlankAccuracy");
	pointBlankRange = templateData->getIntField("pointBlankRange");

	idealRange = templateData->getIntField("idealRange");
	idealAccuracy = templateData->getIntField("idealAccuracy");

	maxRange = templateData->getIntField("maxRange");
	maxRangeAccuracy = templateData->getIntField("maxRangeAccuracy");

	minDamage = templateData->getIntField("minDamage");
	maxDamage = templateData->getIntField("maxDamage");

	woundsRatio = templateData->getFloatField("woundsRatio");

	area = templateData->getIntField("area");

	attackSpeed = templateData->getFloatField("attackSpeed");
}
