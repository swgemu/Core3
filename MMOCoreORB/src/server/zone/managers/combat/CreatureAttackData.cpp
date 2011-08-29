/*
 * CreatureAttackData.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: dannuic
 */

#include "CreatureAttackData.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"

CreatureAttackData::CreatureAttackData(const UnicodeString& dataString, CombatQueueCommand* base) {
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
	speedMultiplier = data.speedMultiplier;
	poolsToDamage = data.poolsToDamage;

	healthCostMultiplier = data.healthCostMultiplier;
	actionCostMultiplier = data.actionCostMultiplier;
	mindCostMultiplier = data.mindCostMultiplier;
	forceCostMultiplier = data.forceCostMultiplier;

	knockdownStateChance = data.knockdownStateChance;
	postureDownStateChance = data.postureDownStateChance;
	postureUpStateChance = data.postureUpStateChance;

	dizzyStateChance = data.dizzyStateChance;
	blindStateChance = data.blindStateChance;
	stunStateChance = data.stunStateChance;
	intimidateStateChance = data.intimidateStateChance;
	nextAttackDelayChance = data.nextAttackDelayChance;
	durationStateTime = data.durationStateTime;

	dotDuration = data.dotDuration;
	dotType = data.dotType;
	dotPool = data.dotPool;
	dotStrength = data.dotStrength;
	dotPotency = data.dotPotency;

	range = data.range;
	coneAngle = data.coneAngle;
	areaRange = data.areaRange;

	animationCRC = data.animationCRC;
}

void CreatureAttackData::fillFromBase() {
	damageMultiplier = baseCommand->getDamageMultiplier();
	speedMultiplier = baseCommand->getSpeedMultiplier();
	healthCostMultiplier = baseCommand->getHealthCostMultiplier();
	actionCostMultiplier = baseCommand->getActionCostMultiplier();
	mindCostMultiplier = baseCommand->getMindCostMultiplier();
	forceCostMultiplier = baseCommand->getForceCostMultiplier();
	poolsToDamage = baseCommand->getPoolsToDamage();
	knockdownStateChance = baseCommand->getKnockdownChance();
	postureDownStateChance = baseCommand->getPostureDownChance();
	postureUpStateChance = baseCommand->getPostureUpChance();
	dizzyStateChance = baseCommand->getDizzyChance();
	blindStateChance = baseCommand->getBlindChance();
	stunStateChance = baseCommand->getStunChance();
	intimidateStateChance = baseCommand->getIntimidateChance();
	nextAttackDelayChance = baseCommand->getNextAttackDelayChance();
	durationStateTime = baseCommand->getDurationStateTime();
	dotDuration = baseCommand->getDotDuration();
	dotType = baseCommand->getDotType();
	dotPool = baseCommand->getDotPool();
	dotStrength = baseCommand->getDotStrength();
	dotPotency = baseCommand->getDotPotency();
	coneAngle = baseCommand->getConeAngle();
	range = baseCommand->getRange();
	areaRange = baseCommand->getAreaRange();
	animationCRC = baseCommand->getAnimationCRC();
}

void CreatureAttackData::setVariable(const String& var, const String& val) {
	uint32 crc = var.hashCode();
	switch(crc) {
	case 0xA82FB287: // String("damageMultiplier").hashCode()
		damageMultiplier = Float::valueOf(val);
		break;
	case 0x7CA69F2E: // String("speedMultiplier").hashCode()
		speedMultiplier = Float::valueOf(val);
		break;
	case 0x3A1C0159: // String("healthCostMultiplier").hashCode()
		healthCostMultiplier = Float::valueOf(val);
		break;
	case 0x5FFD87F5: // String("actionCostMultiplier").hashCode()
		actionCostMultiplier = Float::valueOf(val);
		break;
	case 0xDF28A3E4: // String("mindCostMultiplier").hashCode()
		mindCostMultiplier = Float::valueOf(val);
		break;
	case 0xA3CB47C4: // String("forceCostMultiplier").hashCode()
		forceCostMultiplier = Float::valueOf(val);
		break;
	case 0xBF4C6ADB: // String("poolsToDamage").hashCode()
		poolsToDamage = Integer::valueOf(val);
		break;
	case 0x86F5204F: // String("knockdownChance").hashCode()
		knockdownStateChance = Integer::valueOf(val);
		break;
	case 0x32D82404: // String("postureDownChance").hashCode()
		postureDownStateChance = Integer::valueOf(val);
		break;
	case 0x63EC0BD7: // String("postureUpChance").hashCode()
		postureUpStateChance = Integer::valueOf(val);
		break;
	case 0x5434D0A0: // String("dizzyChance").hashCode()
		dizzyStateChance = Integer::valueOf(val);
		break;
	case 0xED968963: // String("blindChance").hashCode()
		blindStateChance = Integer::valueOf(val);
		break;
	case 0xEE92d66E: // String("stunChance").hashCode()
		stunStateChance = Integer::valueOf(val);
		break;
	case 0x8CC100F4: // String("intimidateChance").hashCode()
		intimidateStateChance = Integer::valueOf(val);
		break;
	case 0xB8BC4726: // String("nextAttackDelayChance").hashCode()
		nextAttackDelayChance = Integer::valueOf(val);
		break;
	case 0x91E2CE2E: // String("durationStateTime").hashCode()
		durationStateTime = Integer::valueOf(val);
		break;
	case 0x3B3CF0ED: // String("dotDuration").hashCode()
		dotDuration = (uint32)Long::valueOf(val);
		break;
	case 0x5292F0A8: // String("dotType").hashCode()
		dotType = UnsignedLong::valueOf(val);
		break;
	case 0xB821C9FB: // String("dotPool").hashCode()
		dotPool = (uint8)Integer::valueOf(val);
		break;
	case 0x35656F0F: // String("dotStrength").hashCode()
		dotStrength = (uint32)Long::valueOf(val);
		break;
	case 0x509E1FC0: // String("dotPotency").hashCode()
		dotPotency = Float::valueOf(val);
		break;
	case 0xD2C29953: // String("coneAngle").hashCode()
		coneAngle = Integer::valueOf(val);
		break;
	case 0xE17D7C71: // String("range").hashCode()
		range = Integer::valueOf(val);
		break;
	case 0xFEC2FA79: // String("areaRange").hashCode()
		areaRange = Integer::valueOf(val);
		break;
	case 0x244FB60D: // String("animationCRC").hashCode()
		animationCRC = Integer::valueOf(val);
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
