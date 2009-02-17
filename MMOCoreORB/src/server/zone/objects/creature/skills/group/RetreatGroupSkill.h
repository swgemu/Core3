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

#ifndef RETREATGROUPSKILL_H_
#define RETREATGROUPSKILL_H_

#include "../SelfSkill.h"

class RetreatGroupSkill : public GroupSkill {
protected:

	bool buffSL;
	String effect;

public:
	RetreatGroupSkill(const String& Name, const char* eff, const char* anim, ZoneProcessServerImplementation* serv) : GroupSkill(Name, eff, OTHER, serv) {
		buffSL = false; //replaced by lua value.
		effect = eff;
	}

	void doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if (!creature->isPlayer()) {
			return;
		}

		Player* squadLeader = (Player*)creature;
		GroupObject* group = squadLeader->getGroupObject();

		if (group == NULL)
			return;

		//Deduct HAM costs from the Squad Leader.
		squadLeader->changeHealthBar(-healthCost, false);
		squadLeader->changeActionBar(-actionCost, false);
		squadLeader->changeMindBar(-mindCost, false);

		squadLeader->sendSystemMessage("You have ordered a retreat!");

		if (target != creature)
			target->unlock();

		squadLeader->unlock();

		try {
			group->wlock();

			for(int i = 0; i < group->getGroupSize(); i++) {
				CreatureObject* groupMember = (CreatureObject*)group->getGroupMember(i);

				try {
					groupMember->wlock(group);
					//System message and combat spam.
					if (groupMember != squadLeader) {
						groupMember->sendCombatSpam(groupMember, NULL, 0, combatSpam, false);
						groupMember->sendSystemMessage("cbt_spam", "retreat_buff"); //"Your squad leader has ordered a retreat!"
					}

					//Effect and buff.
					if (groupMember != squadLeader || buffSL) {
						groupMember->playEffect(effect, "");
						groupMember->activateBurstRun(true);
					}

					groupMember->unlock();
				} catch (...) {
					groupMember->unlock();
				}
			}

			group->unlock();

		} catch (...) {
			group->unlock();
			System::out << "Exception in RetreatGroupSkill::doSkill()\n";
		}

		squadLeader->wlock();

		if (target != squadLeader)
			target->wlock(squadLeader);

		//Add cooldown.
		squadLeader->addCooldown(skillName, cooldownTime);

	}

	void setBuffSL(bool value) {
		buffSL = value;
	}

	// This method checks to see if the cool down time has elapsed.
	virtual bool derivedCanBePerformed(CreatureObject* creature, SceneObject* target) {
		if(creature->hasCooldownExpired(skillName)) {
			return true;
		} else {
			int timeRemaining = creature->getCooldownTimeRemaining(skillName);
			StringBuffer message;
			message << "You must wait " << timeRemaining << " seconds to perform Retreat.";
			creature->sendSystemMessage(message.toString());
			return false;
		}
	}
};

#endif /*RETREATGROUPSKILL_H_*/
