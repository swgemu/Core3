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

#ifndef VOLLEYFIREGROUPSKILL_H_
#define VOLLEYFIREGROUPSKILL_H_

#include "../GroupSkill.h"
#include "../../CreatureObjectImplementation.h"

class VolleyFireGroupSkill : public GroupSkill {
protected:

	uint32 defaultAttackActionCRC;
	StfParameter* param;

public:
	VolleyFireGroupSkill(const String& Name, const char* effect, ZoneProcessServerImplementation* serv) : GroupSkill(Name, effect, OTHER, serv) {
		defaultAttackActionCRC = 0;
		param = new StfParameter();
		String sName("Volley Fire");
		param->addTO(sName);

	}

	~VolleyFireGroupSkill() {
		delete param;
	}

	void doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if(creature->isPlayer()) {
			Player* squadLeader = (Player*)creature;
			GroupObject* group = squadLeader->getGroupObject();

			CombatManager* cm = squadLeader->getZoneProcessServer()->getCombatManager();

			group->wlock();

			int squadLeaderZoneID = squadLeader->getZoneID();

			for(int i = 0; i < group->getGroupSize(); i++) {
				CreatureObject* groupMember = (CreatureObject*)group->getGroupMember(i);

				if(groupMember->getZoneID() == squadLeaderZoneID) {
					if(groupMember->isPlayer()) {
						Player* player = (Player*) groupMember;

						player->doInstantAction(target->getObjectID(), defaultAttackActionCRC, 0, modifier);

						player->sendSystemMessage("cbt_spam", combatSpam);

						player->sendCombatSpam(groupMember, NULL, 0, combatSpam, false);
					}
				}
			}

			group->unlock();

			squadLeader->changeHealthBar(-healthCost, true);
			squadLeader->changeActionBar(-actionCost, true);
			squadLeader->changeMindBar(-mindCost, true);

			squadLeader->addCooldown(skillName, cooldownTime);
		} else {
			// should never get here unless we allow non players to be squad leaders
		}
	}

	void doAnimations(CreatureObject* creature) {

	}

	void sendInvalidTarget(CreatureObject* creature) {
		if(creature->isPlayer()) {
			Player* player = (Player*)creature;
			player->sendSystemMessage("cmd_err", "target_type_prose", param);
		}
	}

	// This method checks to see if the cooldown time has elasped
	virtual bool derivedCanBePerformed(CreatureObject* creature, SceneObject* target) {
		if(target == NULL || !target->isAttackableBy(creature)) {
			sendInvalidTarget(creature);
			return false;
		}

		if(target->isNonPlayerCreature()) {
			Creature* tar = (Creature*) target;
			if(!tar->isAttackable()) {
				sendInvalidTarget(creature);
				return false;
			}
		} else if(target->isPlayer()){
			Player* tar = (Player*) target;
			if(!tar->isAttackable()) {
				sendInvalidTarget(creature);
				return false;
			}
		}

		if(!creature->hasCooldownExpired(skillName)) {
			int timeRemaining = creature->getCooldownTimeRemaining(skillName);
			StringBuffer message;
			message << "You must wait " << timeRemaining << " seconds to perform Volley Fire.";
			creature->sendSystemMessage(message.toString());
			return false;
		}

		return true;
	}

	void setDefaultAttack(const String& defaultAttack) {
		defaultAttackActionCRC = defaultAttack.hashCode();
	}
};

#endif /*VOLLEYFIREGROUPSKILL_H_*/
