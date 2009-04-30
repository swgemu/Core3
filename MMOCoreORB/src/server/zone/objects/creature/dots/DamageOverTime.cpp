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

#include "DamageOverTime.h"
#include "../CreatureAttribute.h"
#include "../CreatureState.h"
#include "../CreatureImplementation.h"
#include "../../player/Player.h"
#include "../../../packets/object/CombatSpam.h"

DamageOverTime::DamageOverTime() {
	setType(CreatureState::BLEEDING);
	setAttribute(CreatureAttribute::HEALTH);
	setStrength(0);
	setDuration(0);
	setPotency(0.0f);
	setExpires(0);
}

DamageOverTime::DamageOverTime(uint64 tp, uint8 attrib, uint32 str, uint32 dur, float potency) {
	setType(tp);
	setAttribute(attrib);
	setStrength(str);
	setDuration(dur);
	setPotency(potency);
	activate();
}

void DamageOverTime::activate() {
		expires.update();
		expires.addMiliTime(duration * 1000);
}

uint32 DamageOverTime::applyDot(CreatureObject* attacker, CreatureObject* victim) {
	uint32 power = 0;
	switch(type) {
		case CreatureState::BLEEDING:
			if (expires.isPast()) {
				return 0;
			}
			else if (nextTick.isPast()){
				power = doBleedingTick(attacker,victim);

				nextTick.update();
				nextTick.addMiliTime(9000);
			}
		break;
		case CreatureState::POISONED:
			if (expires.isPast()) {
				return 0;
			}
			else if (nextTick.isPast()) {
				power = doPoisonTick(attacker,victim);

				nextTick.update();
				nextTick.addMiliTime(9000);
			}
		break;
		case CreatureState::DISEASED:
			if (expires.isPast()) {
				return 0;
			}
			else if (nextTick.isPast()) {
				power = doDiseaseTick(attacker,victim);

				nextTick.update();
				nextTick.addMiliTime(19000);
			}
		break;
		case CreatureState::ONFIRE:
			if (expires.isPast()) {
				return 0;
			}
			else if (nextTick.isPast()) {
				power = doFireTick(attacker,victim);

				nextTick.update();
				nextTick.addMiliTime(9000);
			}
		break;
	}

	return power;
}

uint32 DamageOverTime::initDot(CreatureObject* attacker, CreatureObject* victim) {
	uint32 power = 0;
	switch(type) {
		case CreatureState::BLEEDING:
		case CreatureState::POISONED:
		case CreatureState::ONFIRE:
			//System::out << "init dot\n";
			nextTick.update();
			nextTick.addMiliTime(9000);
			power = strength;
		break;
		case CreatureState::DISEASED:
			nextTick.update();
			nextTick.addMiliTime(19000);
			uint32 shockWounds = victim->getShockWounds();
			power = strength + (shockWounds * strength / 500);
		break;
	}
	victim->addDamage(attacker,1);

	return power;
}

uint32 DamageOverTime::doBleedingTick(CreatureObject* attacker, CreatureObject* victim) {
		uint32 attr = victim->getAttribute(attribute);

		if (attr < strength)
			strength = attr - 1;

		attacker->inflictDamage(victim,attribute,strength);

		victim->playEffect("clienteffect/dot_bleeding.cef","");

		return strength;
}

uint32 DamageOverTime::doFireTick(CreatureObject* attacker, CreatureObject* victim) {
		uint32 shockWounds = victim->getShockWounds();

		uint32 attr = victim->getAttribute(attribute);
		uint32 woundDmg = (strength * (shockWounds + 100) / 500);

		victim->changeWoundsBar(attribute,woundDmg,false);

		victim->changeShockWounds((int)(woundDmg / 3 ));

		if (attr < strength)
			strength = attr - 1;


		attacker->inflictDamage(victim,attribute,strength);

		victim->playEffect("clienteffect/dot_fire.cef","");

		return strength;
}

uint32 DamageOverTime::doPoisonTick(CreatureObject* attacker, CreatureObject* victim) {
		uint32 attr = victim->getAttribute(attribute);

		if (attr < strength)
			strength = attr - 1;

		attacker->inflictDamage(victim,attribute,strength);

		victim->playEffect("clienteffect/dot_poisoned.cef","");

		return strength;
}

uint32 DamageOverTime::doDiseaseTick(CreatureObject* attacker, CreatureObject* victim) {
		uint32 shockWounds = victim->getShockWounds();
		uint32 power = strength + (shockWounds * strength / 500);

		switch (attribute) {
			case CreatureAttribute::HEALTH:
				victim->changeHealthWoundsBar(power, false);
				break;
			case CreatureAttribute::STRENGTH:
				victim->changeStrengthWoundsBar(power, false);
				break;
			case CreatureAttribute::CONSTITUTION:
				victim->changeConstitutionWoundsBar(power, false);
				break;
			case CreatureAttribute::ACTION:
				victim->changeActionWoundsBar(power, false);
				break;
			case CreatureAttribute::QUICKNESS:
				victim->changeQuicknessWoundsBar(power, false);
				break;
			case CreatureAttribute::STAMINA:
				victim->changeStaminaWoundsBar(power, false);
				break;
			case CreatureAttribute::MIND:
				victim->changeMindWoundsBar(power, false);
				break;
			case CreatureAttribute::FOCUS:
				victim->changeFocusWoundsBar(power, false);
				break;
			case CreatureAttribute::WILLPOWER:
				victim->changeWillpowerWoundsBar(power,false);
				break;

		}

		victim->addDamage(attacker,power);
		victim->changeShockWounds((int)(strength * 0.75f));

		victim->playEffect("clienteffect/dot_diseased.cef","");

		return power;
}

float DamageOverTime::reduceTick(float reduction) {
	if (reduction < 0)
		return reduction;

	float eff_reduction = (potency - (float)reduction);
	float reductionLeft = (float)reduction - potency;

	if (reductionLeft >= 0.0f) {
		expires.update();
	} else {
		float dot_reduction = eff_reduction / potency;
		strength *= (int)dot_reduction;
		potency -= reduction;
	}

	return reductionLeft;
}
