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

#include "CombatAI.h"

#include "../CreatureObjectImplementation.h"
#include "../Creature.h"
#include "../skills/skills.h"

CombatAI::CombatAI() {
}

CombatAI::~CombatAI() {

}

void CombatAI::init() {
}

Skill* CombatAI::selectAttackSkill(CreatureObject* attacker,CreatureObject* target) {
	Skill* skill = NULL;
	if (System::random(2) == 0) {

		int skills = attacker->getCreatureSkillsSize();
		if (skills != 0) {
			int rand = System::random(skills - 1);
			skill = attacker->getSkillAt(rand);
			if(!shouldUseSkill(target,skill)) {
				skill = NULL;
			}

		}

	}

	if (skill == NULL) {
		skill = attacker->getDefaultSkill();
	}
	return skill;
}

bool CombatAI::shouldUseSkill(CreatureObject* target, Skill* skill) {
	if (skill->isAttackSkill()) {
		AttackTargetSkill* attack = (AttackTargetSkill*) skill;

		if (attack->isStateAttack() > 0) {
			if ((attack->getKnockdownChance() > 0) && !target->isKnockedDown()) {
				return true;
			}
			else if ((attack->getStunChance() > 0) && !target->isStunned()) {
				return true;
			}
			else if ((attack->getDizzyChance() > 0) && !target->isDizzied()) {
				return true;
			}
			else if ((attack->getIntimidateChance() > 0) && !target->isIntimidated()) {
				return true;
			}
			else if ((attack->getBlindChance() > 0) && !target->isBlinded()) {
				return true;
			} else {
				return false;
			}
		}
	}
	return true;
}


bool CombatAI::shouldRunAway(CreatureObject* creature,CreatureObject* target) {
	if ((System::random(1) == 0) &&((creature->getHealth() < creature->getHealthMax() / 4) ||
			(creature->getAction() < creature->getActionMax() / 4) ||
			(creature->getMind() < creature->getMindMax() / 4))) {

		if (target->isPlayer()) {
			Player* pl = (Player*) target;
			SceneObject* scno = pl->getTarget();
			if (scno != creature) {
				return true;
			} else {
				return false;
			}
		}
	}

	return false;
}
