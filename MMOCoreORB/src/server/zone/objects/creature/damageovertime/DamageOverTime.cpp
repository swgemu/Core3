/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
 */


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
