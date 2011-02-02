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
#include "../CreatureObject.h"
#include "DamageOverTime.h"
#include "../../player/PlayerCreature.h"
#include "../../../packets/object/CombatSpam.h"

DamageOverTime::DamageOverTime() {
	setType(CreatureState::BLEEDING);
	setAttribute(CreatureAttribute::HEALTH);
	strength = 0;
	setDuration(0);
	setPotency(0.0f);
	setExpires(0);

	addSerializableVariables();
}

DamageOverTime::DamageOverTime(uint64 tp, uint8 attrib, uint32 str, uint32 dur, float potency) {
	setType(tp);
	setAttribute(attrib);
	strength = str;
	setDuration(dur);
	setPotency(potency);
	activate();

	addSerializableVariables();
}

DamageOverTime::DamageOverTime(const DamageOverTime& dot) : Object(), Serializable() {
	addSerializableVariables();

	type = dot.type;
	attribute = dot.attribute;
	strength = dot.strength;
	duration = dot.duration;
	potency = dot.potency;
	expires = dot.expires;
	nextTick = dot.nextTick;
}

DamageOverTime& DamageOverTime::operator=(const DamageOverTime& dot) {
	if (this == &dot)
		return *this;

	type = dot.type;
	attribute = dot.attribute;
	strength = dot.strength;
	duration = dot.duration;
	potency = dot.potency;
	expires = dot.expires;
	nextTick = dot.nextTick;

	return *this;
}

void DamageOverTime::addSerializableVariables() {
	addSerializableVariable("type", &type);
	addSerializableVariable("attribute", &attribute);
	addSerializableVariable("strength", &strength);
	addSerializableVariable("duration", &duration);
	addSerializableVariable("potency", &potency);
	addSerializableVariable("expires", &expires);
	addSerializableVariable("nextTick", &nextTick);
}

/*bool DamageOverTime::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeLong(type);
	stream->writeByte(attribute);
}

bool DamageOverTime::parseFromBinaryStream(ObjectInputStream* stream) {

}*/

void DamageOverTime::activate() {
	expires.updateToCurrentTime();
	expires.addMiliTime(duration * 1000);
}

uint32 DamageOverTime::applyDot(CreatureObject* victim) {
	uint32 power = 0;

	switch(type) {
	case CreatureState::BLEEDING:
		if (expires.isPast()) {
			return 0;
		}
		else if (nextTick.isPast()){
			power = doBleedingTick(victim);

			nextTick.updateToCurrentTime();
			nextTick.addMiliTime(9000);
		}
		break;
	case CreatureState::POISONED:
		if (expires.isPast()) {
			return 0;
		}
		else if (nextTick.isPast()) {
			power = doPoisonTick(victim);

			nextTick.updateToCurrentTime();
			nextTick.addMiliTime(9000);
		}
		break;
	case CreatureState::DISEASED:
		if (expires.isPast()) {
			return 0;
		}
		else if (nextTick.isPast()) {
			power = doDiseaseTick(victim);

			nextTick.updateToCurrentTime();
			nextTick.addMiliTime(19000);
		}
		break;
	case CreatureState::ONFIRE:
		if (expires.isPast()) {
			return 0;
		}
		else if (nextTick.isPast()) {
			power = doFireTick(victim);

			nextTick.updateToCurrentTime();
			nextTick.addMiliTime(9000);
		}
		break;
	}

	return power;
}

uint32 DamageOverTime::initDot(CreatureObject* victim) {
	uint32 power = 0;

	switch(type) {
	case CreatureState::BLEEDING:
	case CreatureState::POISONED:
	case CreatureState::ONFIRE:
		//System::out << "init dot\n";
		nextTick.updateToCurrentTime();
		nextTick.addMiliTime(9000);
		power = strength;
		break;
	case CreatureState::DISEASED:
		nextTick.updateToCurrentTime();
		nextTick.addMiliTime(19000);
		uint32 shockWounds = (uint32) victim->getShockWounds();
		power = strength + (shockWounds * strength / 500);
		break;
	}

	//victim->addDamage(attacker,1);

	return power;
}

uint32 DamageOverTime::doBleedingTick(CreatureObject* victim) {
	uint32 strengthToApply = strength;
	uint32 attr = victim->getHAM(attribute);

	if (attr < strengthToApply) {
		//System::out << "setting strength to " << attr -1 << endl;
		strengthToApply = attr - 1;
	}

	victim->inflictDamage(victim, attribute, strengthToApply, false);

	victim->playEffect("clienteffect/dot_bleeding.cef","");

	return strengthToApply;
}

uint32 DamageOverTime::doFireTick(CreatureObject* victim) {
	uint32 attr = victim->getHAM(attribute);
	uint32 strengthToApply = strength;

	victim->addWounds(attribute, strength, true);

	if (attr < strengthToApply)
		strengthToApply = attr - 1;

	victim->inflictDamage(victim, attribute, strengthToApply, true);

	victim->playEffect("clienteffect/dot_fire.cef","");

	return strengthToApply;
}

uint32 DamageOverTime::doPoisonTick(CreatureObject* victim) {
	uint32 attr = victim->getHAM(attribute);
	uint32 strengthToApply = strength;

	if (attr < strengthToApply)
		strengthToApply = attr - 1;

	victim->inflictDamage(victim, attribute, strengthToApply, false);

	victim->playEffect("clienteffect/dot_poisoned.cef","");

	return strengthToApply;
}

uint32 DamageOverTime::doDiseaseTick(CreatureObject* victim) {
	uint32 shockWounds = (uint32) victim->getShockWounds();
	uint32 power = strength + (shockWounds * strength / 500);

	victim->addWounds(attribute, power);

	//victim->addDamage(attacker,power);

	victim->addShockWounds((int)(strength * 0.75f));

	victim->playEffect("clienteffect/dot_diseased.cef","");

	return power;
}

float DamageOverTime::reduceTick(float reduction) {
	//System::out << "reducing tick with reduction " << reduction << endl;
	//System::out << "reducing tick with reduction " << reduction << endl;
	if (reduction < 0)
		return reduction;

	float effReduction = (potency - (float)reduction);
	float reductionLeft = (float)reduction - potency;

	if (reductionLeft >= 0.0f) {
		expires.updateToCurrentTime();
	} else {
		float dotReduction = effReduction / potency;
		//System::out << "strength before dotRed " << strength << endl;
		strength *= (int)dotReduction;
		//System::out << "strength after dotRed " << strength << endl;
		potency -= reduction;
	}

	return reductionLeft;
}
