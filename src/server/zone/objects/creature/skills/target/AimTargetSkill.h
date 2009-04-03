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

#ifndef AIMTARGETSKILL_H_
#define AIMTARGETSKILL_H_

#include "../TargetSkill.h"

class AimTargetSkill : public TargetSkill {

public:
	/*
	 * The constructor.
	 * \param name The skill name
	 * \param serv The ZoneProcessServerImplementation.
	 */
	AimTargetSkill(const String& name, ZoneProcessServerImplementation* serv) : TargetSkill(name, "", ENHANCE, serv) {
		range = 64.0f;
	}


	/*
	 * Activates the target skill (aim).
	 * \param creature The creature, that activates the skill.
	 * \param target The target .
	 * \param modifier The modifiers, not used.
	 */
	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		CreatureObject* targetCreature = (CreatureObject*) target;
		if(creature == NULL || target == NULL || creature->getAimMod() == 0 || targetCreature->isIncapacitated()) {
			if (creature->isPlayer())
				((Player*)creature)->sendSystemMessage("You failed to aim.");

			return 0;
		}

		if (!creature->changeActionBar(-50)) {
			if (creature->isPlayer())
				((Player*)creature)->sendSystemMessage("You are to tired to aim.");

			return 0;
		}

		creature->setAimingState();

		creature->sendCombatSpam((CreatureObject*)target, creature->getWeapon(), 1,getSkillName(),true);

		//if (creature->isPlayer()
		//	((Player*)creature)->sendSystemMessage("cbt_spam", "aim");

		return 0;
	}

	/*
	 * Does the animation.
	 * \param creature The creature The creature, that activates the skill.
	 */
	void doAnimations(CreatureObject* creature) {
	}

	/*
	 * Returns the speed of the skill.
	 * \return creature The creature The creature, that activates the skill.
	 */
	float calculateSpeed(CreatureObject* creature) {
			return 1.0f;
	}

	/*
	 * Checks if the skill can be used
	 * \param creature The creature, that is checked.
	 * \return Returns false if not usefull else true.
	 */
	bool isUseful(CreatureObject* creature) {
		return true;
	}


	/*
	 * Calculates the costs of the skill.
	 * \param creature The creature, that is checked.
	 * \return Returns if costs are applied.
	 */
	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

};

#endif
