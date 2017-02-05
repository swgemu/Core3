/*
 * CreatureAttackData.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: dannuic
 */

#include "CreatureAttackData.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"

CreatureAttackData::CreatureAttackData(const UnicodeString& dataString, const CombatQueueCommand* base, uint64 target) {
	targetID = target;
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
	targetID = data.targetID;

	damageMultiplier = data.damageMultiplier;
	healthDamageMultiplier = data.healthDamageMultiplier;
	actionDamageMultiplier = data.actionDamageMultiplier;
	mindDamageMultiplier = data.mindDamageMultiplier;
	minDamage = data.minDamage;
	maxDamage = data.maxDamage;
	damageType = data.damageType;
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
	coneRange = data.coneRange;
	areaRange = data.areaRange;

	splashDamage = data.splashDamage;
	hitIncapTarget = data.hitIncapTarget;

	forceAttack = data.forceAttack;
	trails = data.trails;

	combatSpam = data.combatSpam;

	stateAccuracyBonus = data.stateAccuracyBonus;
}

void CreatureAttackData::fillFromBase() {
	damageMultiplier = baseCommand->getDamageMultiplier();
	minDamage = baseCommand->getMinDamage();
	maxDamage = baseCommand->getMaxDamage();
	damageType = baseCommand->getDamageType();
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
	coneRange = baseCommand->getConeRange();
	range = baseCommand->getRange();
	areaRange = baseCommand->getAreaRange();
	forceAttack = baseCommand->isForceAttack();
	trails = baseCommand->getTrails();
	combatSpam = baseCommand->getCombatSpam();
	splashDamage = baseCommand->isSplashDamage();

	stateAccuracyBonus = 0;

	healthDamageMultiplier = 1.f;
	actionDamageMultiplier = 1.f;
	mindDamageMultiplier = 1.f;

	hitIncapTarget = false;
}

void CreatureAttackData::setVariable(const String& var, const String& val) {
	uint32 crc = var.hashCode();
	switch(crc) {
	case 0x480C4BA4: // STRING_HASHCODE("minDamage"):
		minDamage = Float::valueOf(val);
		break;
	case 0xDDC00C87: // STRING_HASHCODE("maxDamage"):
		maxDamage = Float::valueOf(val);
		break;
	case 0x6980E997: // STRING_HASHCODE("damageType"):
		damageType = Integer::valueOf(val);
		break;
	case 0xA82FB287: // STRING_HASHCODE("damageMultiplier"):
		damageMultiplier = Float::valueOf(val);
		break;
	case 0xC60F1652: // STRING_HASHCODE("healthDamageMultiplier"):
		healthDamageMultiplier = Float::valueOf(val);
		break;
	case 0x77139783: // STRING_HASHCODE("actionDamageMultiplier"):
		actionDamageMultiplier = Float::valueOf(val);
		break;
	case 0xD7D06F99: // STRING_HASHCODE("mindDamageMultiplier"):
		mindDamageMultiplier = Float::valueOf(val);
		break;
	case 0xC33D0A1B: // String("accuracyBonus").hashcode()
		accuracyBonus = Integer::valueOf(val);
		break;
	case 0x7CA69F2E: // STRING_HASHCODE("speedMultiplier")
		speedMultiplier = Float::valueOf(val);
		break;
	case 0x3A1C0159: // STRING_HASHCODE("healthCostMultiplier")
		healthCostMultiplier = Float::valueOf(val);
		break;
	case 0x5FFD87F5: // STRING_HASHCODE("actionCostMultiplier")
		actionCostMultiplier = Float::valueOf(val);
		break;
	case 0xDF28A3E4: // STRING_HASHCODE("mindCostMultiplier")
		mindCostMultiplier = Float::valueOf(val);
		break;
	case 0xA3CB47C4: // STRING_HASHCODE("forceCostMultiplier")
		forceCostMultiplier = Float::valueOf(val);
		break;
	case 0xBF4C6ADB: // STRING_HASHCODE("poolsToDamage")
		poolsToDamage = Integer::valueOf(val);
		break;
	case 0xD2C29953: // STRING_HASHCODE("coneAngle")
		coneAngle = Integer::valueOf(val);
		break;
	case 0xE17D7C71: // STRING_HASHCODE("range")
		range = Integer::valueOf(val);
		break;
	case 0xFEC2FA79: // STRING_HASHCODE("areaRange")
		areaRange = Integer::valueOf(val);
		break;
	case STRING_HASHCODE("forceAttack"):
		forceAttack = (bool)Integer::valueOf(val);
		break;
	case 0x550ED3F5: // STRING_HASHCODE("trails")
		trails = Integer::valueOf(val);
		break;
	case 0xFAFA1475: // STRING_HASHCODE("combatSpam")
		combatSpam = val;
		break;
	case 0x97F6A373: // STRING_HASHCODE("stateAccuracyBonus")
		stateAccuracyBonus = Integer::valueOf(val);
		break;
	case 0xBD39E628: // STRING_HASHCODE("hitIncapTarget")
		hitIncapTarget = (bool)Integer::valueOf(val);
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

bool CreatureAttackData::changesDefenderPosture() const {
	if(stateEffects == NULL)
		return false;

	for(int i=0; i<stateEffects->size(); i++) {
		switch(stateEffects->get(i).getEffectType()) {
		case CommandEffect::KNOCKDOWN:
		case CommandEffect::POSTUREUP:
		case CommandEffect::POSTUREDOWN:
			return true;
		}
	}

	return false;
}

bool CreatureAttackData::changesAttackerPosture() const {
	if(stateEffects == NULL)
		return false;

	for(int i=0; i<stateEffects->size(); i++) {
		switch(stateEffects->get(i).getEffectType()) {
		case CommandEffect::ATTACKER_FORCE_STAND:
		case CommandEffect::ATTACKER_FORCE_CROUCH:
		case CommandEffect::ATTACKER_FORCE_PRONE:
			return true;
		}
	}
	return false;
}
