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

DamageOverTime::DamageOverTime() {
	setType(CreatureState::BLEEDING);
	setAttribute(CreatureAttribute::HEALTH);
	setStrength(0);
	setDuration(0);
	setPotency(0.0f);
	setExpires(NULL);
}

DamageOverTime::DamageOverTime(uint64 tp, uint8 attrib, uint32 str, uint32 dur, float potency) {
	setType(tp);
	setAttribute(attrib);
	setStrength(str);
	setDuration(dur);
	setPotency(0.0f);
	setExpires(NULL);
	setPotency(potency);
	activate();
}

void DamageOverTime::activate() {
		expires.update();
		expires.addMiliTime(duration * 1000);
}

void DamageOverTime::applyDot(CreatureObject* attacker, CreatureObject* victim) {
	switch(type) {
		case CreatureState::BLEEDING:
			if (expires.isPast()) {
				return;
			}
			else if (nextTick.isPast()){

				doBleedingTick(attacker,victim);

				nextTick.update();
				nextTick.addMiliTime(9000);
			}
		break;
		case CreatureState::POISONED:
			if (expires.isPast()) {
				return;
			}
			else if (nextTick.isPast()) {
				doPoisonTick(attacker,victim);

				nextTick.update();
				nextTick.addMiliTime(9000);
			}
		break;
		case CreatureState::DISEASED:
			if (expires.isPast()) {
				return;
			}
			else if (nextTick.isPast()) {
				doDiseaseTick(attacker,victim);

				nextTick.update();
				nextTick.addMiliTime(19000);
			}
		break;
		case CreatureState::ONFIRE:
			if (expires.isPast()) {
				return;
			}
			else if (nextTick.isPast()) {
				doFireTick(attacker,victim);

				nextTick.update();
				nextTick.addMiliTime(9000);
			}
		break;

	}
//	if (expires.compareTo(nextTick) > 0)
//		expires.update();
	victim->updateStates();
}

void DamageOverTime::doBleedingTick(CreatureObject* attacker, CreatureObject* victim) {
		attacker->inflictDamage(victim,attribute,strength);

		victim->playEffect("clienteffect/dot_bleeding.cef","");
}

void DamageOverTime::doFireTick(CreatureObject* attacker, CreatureObject* victim) {
		attacker->inflictDamage(victim,attribute,strength);

		victim->playEffect("clienteffect/dot_fire.cef","");
}

void DamageOverTime::doPoisonTick(CreatureObject* attacker, CreatureObject* victim) {
		attacker->inflictDamage(victim,attribute,strength);

		victim->playEffect("clienteffect/dot_poisoned.cef","");
}

void DamageOverTime::doDiseaseTick(CreatureObject* attacker, CreatureObject* victim) {
		uint32 shockWounds = victim->getShockWounds();

		switch (attribute) {
			case CreatureAttribute::HEALTH:
				victim->changeHealthWoundsBar(strength + (shockWounds * strength / 500));
				break;
			case CreatureAttribute::STRENGTH:
				victim->changeStrengthWoundsBar(strength + (shockWounds * strength / 500));
				break;
			case CreatureAttribute::CONSTITUTION:
				victim->changeConstitutionWoundsBar(strength + (shockWounds * strength / 500));
				break;
			case CreatureAttribute::ACTION:
				victim->changeActionWoundsBar(strength + (shockWounds * strength / 500));
				break;
			case CreatureAttribute::QUICKNESS:
				victim->changeQuicknessWoundsBar(strength + (shockWounds * strength / 500));
				break;
			case CreatureAttribute::STAMINA:
				victim->changeStaminaWoundsBar(strength + (shockWounds * strength / 500));
				break;
			case CreatureAttribute::MIND:
				victim->changeMindWoundsBar(strength + (shockWounds * strength / 500));
				break;
			case CreatureAttribute::FOCUS:
				victim->changeFocusWoundsBar(strength + (shockWounds * strength / 500));
				break;
			case CreatureAttribute::WILLPOWER:
				victim->changeWillpowerWoundsBar(strength + (shockWounds * strength / 500));
				break;

		}

		victim->playEffect("clienteffect/dot_diseased.cef","");
		StringBuffer msg;
}

int DamageOverTime::reduceTick(int reduction) {
	if (reduction < 0)
		return reduction;

	int eff_reduction = (potency - reduction);
	int reductionLeft = reduction - potency;

	if (reductionLeft >= 0) {
		expires.update();
	} else {
		float dot_reduction = ((float)eff_reduction) / potency;
		strength *= dot_reduction;
		potency -= reduction;
	}

	return reductionLeft;
}
