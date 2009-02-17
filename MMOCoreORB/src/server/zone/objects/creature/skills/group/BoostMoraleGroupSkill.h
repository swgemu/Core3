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

#ifndef BOOSTMORALEGROUPSKILL_H_
#define BOOSTMORALEGROUPSKILL_H_

#include "../GroupSkill.h"
#include "../../CreatureObjectImplementation.h"

class BoostMoraleGroupSkill : public GroupSkill {
protected:

public:
	BoostMoraleGroupSkill(const String& Name, const char* effect, ZoneProcessServerImplementation* serv) : GroupSkill(Name, effect, OTHER, serv) {

	}

	virtual void doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if(creature->isPlayer()) {
			Player* squadLeader = (Player*)creature;
			GroupObject* group = squadLeader->getGroupObject();

			if (group == NULL)
				return;

			int totalWounds = 0;
			int groupWoundsAverage = 0;
			uint8 size = creature->getWoundsArraySize();

			if (target != creature)
				target->unlock();

			squadLeader->unlock();

			group->wlock();

			int squadLeaderZoneID = squadLeader->getZoneID();

			Vector<ManagedReference<CreatureObject> > groupMembers;

			for(int i = 0; i < group->getGroupSize(); i++) {
				CreatureObject* groupMember = (CreatureObject*)group->getGroupMember(i);
				if(groupMember->getZoneID() == squadLeaderZoneID) {
					if(groupMember->isPlayer()) {
						// Find average of group member's wounds
						for(uint8 i = 0; i < size; i++) {
							int woundAmount = groupMember->getWounds(i);
							totalWounds += woundAmount;
						}
						groupMembers.add(groupMember);
					}
				}
			}

			groupWoundsAverage = totalWounds / (group->getGroupSize() * size);

			group->unlock();

			for(int i = 0; i < groupMembers.size(); i++) {
				CreatureObject* groupMember = groupMembers.get(i);

				groupMember->wlock();

				for(uint8 i = 0; i < size; i++) {
					int currentWounds = groupMember->getWounds(i);
					int maxWounds = groupMember->getBaseAttribute(i) - 1;
					int amountToChange = 0;

					if(groupWoundsAverage > maxWounds)
						amountToChange = maxWounds - currentWounds;
					else
						amountToChange = groupWoundsAverage - currentWounds;

					groupMember->changeWoundsBar(i, amountToChange, true);
				}

				groupMember->sendSystemMessage("cbt_spam", combatSpam);
				groupMember->sendCombatSpam(groupMember, NULL, 0, combatSpam, false);

				groupMember->unlock();
			}

			squadLeader->wlock();

			squadLeader->changeHealthBar(-healthCost, true);
			squadLeader->changeActionBar(-actionCost, true);
			squadLeader->changeMindBar(-mindCost, true);

			squadLeader->addCooldown(skillName, cooldownTime);

			if (target != squadLeader)
				target->wlock(squadLeader);
		} else {
			// should never get here unless we allow non players to be squad leaders
		}
	}

	void doAnimations(CreatureObject* creature) {

	}

	// This method checks to see if the cooldown time has elasped
	virtual bool derivedCanBePerformed(CreatureObject* creature, SceneObject* target) {
		if(creature->hasCooldownExpired(skillName)) {
			return true;
		} else {
			int timeRemaining = creature->getCooldownTimeRemaining(skillName);
			StringBuffer message;
			message << "You must wait " << timeRemaining << " seconds to perform Boost Morale.";
			creature->sendSystemMessage(message.toString());
			return false;
		}
	}
};

#endif /*BOOSTMORALEGROUPSKILL_H_*/
