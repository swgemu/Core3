/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */


#include "../CreatureAttribute.h"
#include "../CreatureState.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "DamageOverTime.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "../../../packets/object/CombatSpam.h"

DamageOverTime::DamageOverTime() {
	setAttackerID(0);
	setType(CreatureState::BLEEDING);
	setAttribute(CreatureAttribute::HEALTH);
	strength = 0;
	setDuration(0);
	setExpires(0);
	setSecondaryStrength(0);
	addSerializableVariables();
}

DamageOverTime::DamageOverTime(CreatureObject* attacker, uint64 tp, uint8 attrib, uint32 str, uint32 dur, int secondaryStrength) {

	if (attacker != NULL)
		setAttackerID(attacker->getObjectID());

	setType(tp);
	setAttribute(attrib);
	strength = str;
	setDuration(dur);
	setSecondaryStrength(secondaryStrength);
	applied.updateToCurrentTime();
	activate();

	addSerializableVariables();
}

DamageOverTime::DamageOverTime(const DamageOverTime& dot) : Object(), Serializable() {
	addSerializableVariables();

	attackerID = dot.attackerID;
	type = dot.type;
	attribute = dot.attribute;
	strength = dot.strength;
	duration = dot.duration;
	applied = dot.applied;
	expires = dot.expires;
	nextTick = dot.nextTick;
	secondaryStrength = dot.secondaryStrength;

}

DamageOverTime& DamageOverTime::operator=(const DamageOverTime& dot) {
	if (this == &dot)
		return *this;

	attackerID = dot.attackerID;
	type = dot.type;
	attribute = dot.attribute;
	strength = dot.strength;
	duration = dot.duration;
	applied = dot.applied;
	expires = dot.expires;
	nextTick = dot.nextTick;
	secondaryStrength = dot.secondaryStrength;


	return *this;
}

void DamageOverTime::addSerializableVariables() {
	addSerializableVariable("attackerID", &attackerID);
	addSerializableVariable("type", &type);
	addSerializableVariable("attribute", &attribute);
	addSerializableVariable("strength", &strength);
	addSerializableVariable("duration", &duration);
	addSerializableVariable("applied", &applied);
	addSerializableVariable("expires", &expires);
	addSerializableVariable("nextTick", &nextTick);
	addSerializableVariable("secondaryStrength", &secondaryStrength);

}

void DamageOverTime::activate() {
	expires.updateToCurrentTime();
	expires.addMiliTime(duration * 1000);
}

uint32 DamageOverTime::applyDot(CreatureObject* victim) {
	if (expires.isPast() || !nextTick.isPast())
		return 0;

	nextTick.updateToCurrentTime();
	nextTick.addMiliTime(10000);

	uint32 power = 0;
	ManagedReference<CreatureObject*> attacker = victim->getZoneServer()->getObject(attackerID).castTo<CreatureObject*>();

	if (attacker == NULL)
		attacker = victim;

	switch(type) {
	case CreatureState::BLEEDING:
		power = doBleedingTick(victim, attacker);
		nextTick.addMiliTime(10000);
		break;
	case CreatureState::POISONED:
		power = doPoisonTick(victim, attacker);
		break;
	case CreatureState::DISEASED:
		power = doDiseaseTick(victim);
		nextTick.addMiliTime(30000);
		break;
	case CreatureState::ONFIRE:
		power = doFireTick(victim, attacker);
		break;
	}

	return power;
}

uint32 DamageOverTime::initDot(CreatureObject* victim) {
	uint32 power = 0;
	int absorptionMod = 0;
	nextTick.updateToCurrentTime();
	nextTick.addMiliTime(10000);

	switch(type) {
	case CreatureState::BLEEDING:
		absorptionMod = MIN(0, MAX(50, victim->getSkillMod("absorption_bleeding")));
		nextTick.addMiliTime(10000);
		break;
	case CreatureState::POISONED:
		absorptionMod = MIN(0, MAX(50, victim->getSkillMod("absorption_poison")));
		break;
	case CreatureState::ONFIRE:
		absorptionMod = MIN(0, MAX(50, victim->getSkillMod("absorption_fire")));
		break;
	case CreatureState::DISEASED:
		absorptionMod = MIN(0, MAX(50, victim->getSkillMod("absorption_disease")));
		nextTick.addMiliTime(30000);
		break;
	}

	power = (uint32)(strength * (1.f - absorptionMod / 100.f));

	//victim->addDamage(attacker,1);

	return power;
}

uint32 DamageOverTime::doBleedingTick(CreatureObject* victim, CreatureObject* attacker) {
	// TODO: Do we try to resist again?
	uint32 attr = victim->getHAM(attribute);
	int absorptionMod = MIN(0, MAX(50, victim->getSkillMod("absorption_bleeding")));

	// absorption reduces the strength of a dot by the given %.
	int damage = (int)(strength * (1.f - absorptionMod / 100.f));
	if (attr < damage) {
		//System::out << "setting strength to " << attr -1 << endl;
		damage = attr - 1;
	}

	Reference<CreatureObject*> attackerRef = attacker;
	Reference<CreatureObject*> victimRef = victim;
	uint8 attribute = this->attribute;

	EXECUTE_TASK_4(attackerRef, victimRef, attribute, damage, {
			Locker locker(victimRef_p);

			Locker crossLocker(attackerRef_p, victimRef_p);

			victimRef_p->inflictDamage(attackerRef_p, attribute_p, damage_p, false);

			if (victimRef_p->hasAttackDelay())
				victimRef_p->removeAttackDelay();

			victimRef_p->playEffect("clienteffect/dot_bleeding.cef","");
	});


	return damage;
}

uint32 DamageOverTime::doFireTick(CreatureObject* victim, CreatureObject* attacker) {
	uint32 attr = victim->getHAM(attribute);
	int absorptionMod = MIN(0, MAX(50, victim->getSkillMod("absorption_fire")));

	// absorption reduces the strength of a dot by the given %.
	int damage = (int)(strength * (1.f - absorptionMod / 100.f));
	if (attr < damage) {
		//System::out << "setting strength to " << attr -1 << endl;
		damage = attr - 1;
	}

	int woundsToApply = (int)(secondaryStrength * (1.f + victim->getShockWounds() / 100.0f));

	Reference<CreatureObject*> attackerRef = attacker;
	Reference<CreatureObject*> victimRef = victim;
	uint8 attribute = this->attribute;
	uint32 strength = this->strength;

	EXECUTE_TASK_6(attackerRef, victimRef, attribute, damage, woundsToApply, strength, {
			Locker locker(victimRef_p);

			Locker crossLocker(attackerRef_p, victimRef_p);

			if ((int)strength_p > 0) {
				victimRef_p->addWounds(attribute_p, woundsToApply_p, true, false);
				victimRef_p->addShockWounds((int)(woundsToApply_p * 0.075f));
			}

			victimRef_p->inflictDamage(attackerRef_p, attribute_p, damage_p, true);
			if (victimRef_p->hasAttackDelay())
				victimRef_p->removeAttackDelay();

			victimRef_p->playEffect("clienteffect/dot_fire.cef","");
	});


	return damage;
}

uint32 DamageOverTime::doPoisonTick(CreatureObject* victim, CreatureObject* attacker) {
	uint32 attr = victim->getHAM(attribute);
	int absorptionMod = MIN(0, MAX(50, victim->getSkillMod("absorption_poison")));

	// absorption reduces the strength of a dot by the given %.
	int damage = (int)(strength * (1.f - absorptionMod / 100.f));
	if (attr < damage) {
		//System::out << "setting strength to " << attr -1 << endl;
		damage = attr - 1;
	}

	Reference<CreatureObject*> attackerRef = attacker;
	Reference<CreatureObject*> victimRef = victim;
	uint8 attribute = this->attribute;

	EXECUTE_TASK_4(attackerRef, victimRef, attribute, damage, {
			Locker locker(victimRef_p);

			Locker crossLocker(attackerRef_p, victimRef_p);

			victimRef_p->inflictDamage(attackerRef_p, attribute_p, damage_p, false);
			if (victimRef_p->hasAttackDelay())
				victimRef_p->removeAttackDelay();

			victimRef_p->playEffect("clienteffect/dot_poisoned.cef","");
	});

	return damage;
}

uint32 DamageOverTime::doDiseaseTick(CreatureObject* victim) {
	int absorptionMod = MIN(0, MAX(50, victim->getSkillMod("absorption_disease")));

	// absorption reduces the strength of a dot by the given %.
	// make sure that the CM dots modify the strength
	int damage = (int)(strength * (1.f - absorptionMod / 100.f) * (1.f + victim->getShockWounds() / 100.0f));
	uint8 attribute = this->attribute;
	uint32 strength = this->strength;
	Reference<CreatureObject*> victimRef = victim;

	EXECUTE_TASK_4(attribute, strength, victimRef, damage, {
			Locker locker(victimRef_p);

			if ((int)damage_p > 0) {
				victimRef_p->addWounds(attribute_p, damage_p, true, false);
				if (victimRef_p->hasAttackDelay())
					victimRef_p->removeAttackDelay();
			}

			victimRef_p->addShockWounds((int)(strength_p * 0.075f));

			victimRef_p->playEffect("clienteffect/dot_diseased.cef","");
	});

	return damage;
}

float DamageOverTime::reduceTick(float reduction) {
	//System::out << "reducing tick with reduction " << reduction << endl;
	if (reduction < 0)
		return reduction;

	float effReduction = (strength - (float)reduction);
	float reductionLeft = (float)reduction - strength;

	if (reductionLeft >= 0.0f) {
		expires.updateToCurrentTime();
	} else {
		//System::out << "strength before dotRed " << strength << endl;
		strength = effReduction;
		//System::out << "strength after dotRed " << strength << endl;
	}

	return reductionLeft;
}
