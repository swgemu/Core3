/*
 * CreatureAttackData.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: dannuic
 */

#include "CreatureAttackData.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"

CreatureAttackData::CreatureAttackData(const UnicodeString& dataString, const CombatQueueCommand* base) {
	baseCommand = base;
	fillFromBase();

	StringTokenizer data(dataString.toString());
	data.setDelimeter(";");

	while (data.hasMoreTokens()) {
		String varString;
		data.getStringToken(varString);

		int pos = varString.indexOf("=");

		if (pos == -1)
			continue;

		String key = varString.subString(0,pos);
		String value = varString.subString(pos + 1, varString.length());

		setVariable(key, value);
	}
}

CreatureAttackData::CreatureAttackData(const CreatureAttackData& data) {
	baseCommand = data.baseCommand;

	damageMultiplier = data.damageMultiplier;
	healthDamageMultiplier = data.healthDamageMultiplier;
	actionDamageMultiplier = data.actionDamageMultiplier;
	mindDamageMultiplier = data.mindDamageMultiplier;
	damage = data.damage;
	accuracyBonus = data.accuracyBonus;
	speedMultiplier = data.speedMultiplier;
	poolsToDamage = data.poolsToDamage;

	healthCostMultiplier = data.healthCostMultiplier;
	actionCostMultiplier = data.actionCostMultiplier;
	mindCostMultiplier = data.mindCostMultiplier;
	forceCostMultiplier = data.forceCostMultiplier;

	stateEffects = data.stateEffects;
	dotEffects = data.dotEffects;

	range = data.range;
	coneAngle = data.coneAngle;
	areaRange = data.areaRange;

	animationCRC = data.animationCRC;

	attackType= data.attackType;
	trails = data.trails;

	combatSpam = data.combatSpam;

	stateAccuracyBonus = data.stateAccuracyBonus;
}

void CreatureAttackData::fillFromBase() {
	damageMultiplier = baseCommand->getDamageMultiplier();
	damage = baseCommand->getDamage();
	accuracyBonus = baseCommand->getAccuracyBonus();
	speedMultiplier = baseCommand->getSpeedMultiplier();
	healthCostMultiplier = baseCommand->getHealthCostMultiplier();
	actionCostMultiplier = baseCommand->getActionCostMultiplier();
	mindCostMultiplier = baseCommand->getMindCostMultiplier();
	forceCostMultiplier = baseCommand->getForceCostMultiplier();
	poolsToDamage = baseCommand->getPoolsToDamage();
	stateEffects = baseCommand->getStateEffects();
	dotEffects = baseCommand->getDotEffects();
	coneAngle = baseCommand->getConeAngle();
	range = baseCommand->getRange();
	areaRange = baseCommand->getAreaRange();
	animationCRC = baseCommand->getAnimationCRC();
	attackType = baseCommand->getAttackType();
	trails = baseCommand->getTrails();
	combatSpam = baseCommand->getCombatSpam();

	stateAccuracyBonus = 0;

	healthDamageMultiplier = 1.f;
	actionDamageMultiplier = 1.f;
	mindDamageMultiplier = 1.f;
}

void CreatureAttackData::setVariable(const String& var, const String& val) {
	uint32 crc = var.hashCode();
	switch(crc) {
	case 0x9E64852D: // String::hashCode("damage"):
		damage = Float::valueOf(val);
		break;
	case 0xA82FB287: // String::hashCode("damageMultiplier"):
		damageMultiplier = Float::valueOf(val);
		break;
	case 0xC60F1652: // String::hashCode("healthDamageMultiplier"):
		healthDamageMultiplier = Float::valueOf(val);
		break;
	case 0x77139783: // String::hashCode("actionDamageMultiplier"):
		actionDamageMultiplier = Float::valueOf(val);
		break;
	case 0xD7D06F99: // String::hashCode("mindDamageMultiplier"):
		mindDamageMultiplier = Float::valueOf(val);
		break;
	case 0xC33D0A1B: // String("accuracyBonus").hashcode()
		accuracyBonus = Integer::valueOf(val);
		break;
	case 0x7CA69F2E: // String::hashCode("speedMultiplier")
		speedMultiplier = Float::valueOf(val);
		break;
	case 0x3A1C0159: // String::hashCode("healthCostMultiplier")
		healthCostMultiplier = Float::valueOf(val);
		break;
	case 0x5FFD87F5: // String::hashCode("actionCostMultiplier")
		actionCostMultiplier = Float::valueOf(val);
		break;
	case 0xDF28A3E4: // String::hashCode("mindCostMultiplier")
		mindCostMultiplier = Float::valueOf(val);
		break;
	case 0xA3CB47C4: // String::hashCode("forceCostMultiplier")
		forceCostMultiplier = Float::valueOf(val);
		break;
	case 0xBF4C6ADB: // String::hashCode("poolsToDamage")
		poolsToDamage = Integer::valueOf(val);
		break;
	case 0xD2C29953: // String::hashCode("coneAngle")
		coneAngle = Integer::valueOf(val);
		break;
	case 0xE17D7C71: // String::hashCode("range")
		range = Integer::valueOf(val);
		break;
	case 0xFEC2FA79: // String::hashCode("areaRange")
		areaRange = Integer::valueOf(val);
		break;
	case 0x244FB60D: // String::hashCode("animationCRC")
		animationCRC = Integer::valueOf(val);
		break;
	case 0x708615B8: // String::hashCode("attackType")
		attackType = Integer::valueOf(val);
		break;
	case 0x550ED3F5: // String::hashCode("trails")
		trails = Integer::valueOf(val);
		break;
	case 0xFAFA1475: // String::hashCode("combatSpam")
		combatSpam = val;
		break;
	case 0x97F6A373: // String::hashCode("stateAccuracyBonus")
		stateAccuracyBonus = Integer::valueOf(val);
		break;
	default:
		break;
	}
}

String CreatureAttackData::getCommandName() const {
	return baseCommand->getQueueCommandName();
}

uint32 CreatureAttackData::getCommandCRC() const {
	return baseCommand->getNameCRC();
}
