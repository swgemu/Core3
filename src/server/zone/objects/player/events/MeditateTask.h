/*
 Copyright (C) 2010 <SWGEmu>

 This File is part of Core3.

 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 3 of the License,
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

/**
 * \file MeditateTask.h
 * \author Polonel
 * \date 08.04.2010
 */

#ifndef MEDITATETASK_H_
#define MEDITATETASK_H_

#include "engine/engine.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/scene/variables/ParameterizedStringId.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

class MeditateTask: public Task {
	ManagedReference<PlayerCreature*> player;
	String moodString;

public:
	MeditateTask(PlayerCreature* pl) {
		player = pl;
	}

	void setMoodString(String ms) {
		moodString = ms;
	}

	String getMoodString() {
		return moodString;
	}

	void run() {
		Locker playerLocker(player);
		try {
			Reference<MeditateTask*> meditateTask = (MeditateTask*) player->getPendingTask("meditate");
			int meditateMod = player->getSkillMod("meditate"); // get Meditate Skill Mod
			if (player->hasState(CreatureState::ALERT) && player->isMeditating()) { // Check player state.
				int heal; // Healing Amount
				int woundAmt; // new Amount of Wounds

				ParameterizedStringId HealParams;

				if (player->isBleeding() || player->isPoisoned() || player->isDiseased()) {
					if (player->isBleeding() && meditateMod >= 15)
						player->healDot(CreatureState::BLEEDING, (15 + (meditateMod / 3)));
					else if (player->isPoisoned() && meditateMod >= 30)
						player->healDot(CreatureState::POISONED, (15 + (meditateMod / 3)));
					else if (player->isDiseased() && meditateMod >= 45)
						player->healDot(CreatureState::DISEASED, (15 + (meditateMod / 3)));

				} else if (meditateMod >= 75) { // Meditate SkillMod +75 for wound Healing..
					// Get Wounds for each Attribute...
					int healthWounds = player->getWounds(CreatureAttribute::HEALTH);
					int strWounds = player->getWounds(CreatureAttribute::STRENGTH);
					int conWounds = player->getWounds(CreatureAttribute::CONSTITUTION);
					int actionWounds = player->getWounds(CreatureAttribute::ACTION);
					int quiWounds = player->getWounds(CreatureAttribute::QUICKNESS);
					int stamWounds = player->getWounds(CreatureAttribute::STAMINA);
					int mindWounds = player->getWounds(CreatureAttribute::MIND);
					int focusWounds = player->getWounds(CreatureAttribute::FOCUS);
					int willWounds = player->getWounds(CreatureAttribute::WILLPOWER);

					Vector < uint8 > woundedPools;
					for (uint8 i = 1; i < 10; i++) {
						uint8 wounds = i - 1;
						int hasWounds = player->getWounds(wounds);
						if (hasWounds > 0 && hasWounds != 0)
							woundedPools.add(i);
					}

					if (woundedPools.size() == 0) {
						if (meditateTask != NULL)
							meditateTask->reschedule(5000);
						else
							meditateTask->schedule(5000);
						return;
					}

					if (meditateMod > 0 && meditateMod < 100)
						heal = 20 + System::random(10);
					else if (meditateMod >= 100)
						heal = 30 + System::random(20);
					else
						return;

					// Select a random Attribute that has wounds...
					uint8 pool = woundedPools.get(System::random(woundedPools.size() - 1));

					switch (pool) {
					case 1:
						if (healthWounds < heal)
							heal = healthWounds;

						woundAmt = healthWounds - heal;
						player->setWounds(CreatureAttribute::HEALTH, woundAmt, true);
						HealParams.setTO("health");
						break;

					case 2:
						if (strWounds < heal)
							heal = strWounds;

						woundAmt = strWounds - heal;
						player->setWounds(CreatureAttribute::STRENGTH, woundAmt, true);
						HealParams.setTO("strength");
						break;

					case 3:
						if (conWounds < heal)
							heal = conWounds;

						woundAmt = conWounds - heal;
						player->setWounds(CreatureAttribute::CONSTITUTION, woundAmt, true);
						HealParams.setTO("constitution");
						break;

					case 4:
						if (actionWounds < heal)
							heal = actionWounds;

						woundAmt = actionWounds - heal;
						player->setWounds(CreatureAttribute::ACTION, woundAmt, true);
						HealParams.setTO("action");
						break;

					case 5:
						if (quiWounds < heal)
							heal = quiWounds;

						woundAmt = quiWounds - heal;
						player->setWounds(CreatureAttribute::QUICKNESS, woundAmt, true);
						HealParams.setTO("quickness");
						break;

					case 6:
						if (stamWounds < heal)
							heal = stamWounds;

						woundAmt = stamWounds - heal;
						player->setWounds(CreatureAttribute::STAMINA, woundAmt, true);
						HealParams.setTO("stamina");
						break;

					case 7:
						if (mindWounds < heal)
							heal = mindWounds;

						woundAmt = mindWounds - heal;
						player->setWounds(CreatureAttribute::MIND, woundAmt, true);
						HealParams.setTO("mind");
						break;

					case 8:
						if (focusWounds < heal)
							heal = focusWounds;

						woundAmt = focusWounds - heal;
						player->setWounds(CreatureAttribute::FOCUS, woundAmt, true);
						HealParams.setTO("focus");
						break;

					case 9:
						if (willWounds < heal)
							heal = willWounds;

						woundAmt = willWounds - heal;
						player->setWounds(CreatureAttribute::WILLPOWER, woundAmt, true);
						HealParams.setTO("willpower");
						break;

					}
					// Sending System healing Message (wounds)
					HealParams.setStringId("teraskasi", "prose_curewound");
					HealParams.setDI(heal);
					player->sendSystemMessage(HealParams);
				}// End Wounds

				if (meditateTask != NULL)
					meditateTask->reschedule(5000);
				else
					meditateTask->schedule(5000);
			}

			return;

		} catch (...) {
			player->error("unreported exception caught in MeditateTask::activate");
		}
	}

};

#endif /* MEDITATETASK_H_ */
