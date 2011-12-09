/*
 Copyright (C) 2007 <SWGEmu>

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
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

class MeditateTask: public Task {
	ManagedReference<CreatureObject*> player;
	String moodString;

public:
	MeditateTask(CreatureObject* pl) {
		player = pl;
	}

	void setMoodString(const String& ms) {
		moodString = ms;
	}

	String getMoodString() {
		return moodString;
	}

	void run() {
		Locker playerLocker(player);

		try {
			Reference<MeditateTask*> meditateTask = dynamic_cast<MeditateTask*>(player->getPendingTask("meditate"));
			int meditateMod = player->getSkillMod("meditate"); // get Meditate Skill Mod

			if (!player->isMeditating())
				return;

			if (player->isBleeding() || player->isPoisoned() || player->isDiseased()) {
				if (player->isBleeding() && meditateMod >= 15)
					player->healDot(CreatureState::BLEEDING, (15 + (meditateMod / 3)));
				else if (player->isPoisoned() && meditateMod >= 30)
					player->healDot(CreatureState::POISONED, (15 + (meditateMod / 3)));
				else if (player->isDiseased() && meditateMod >= 45)
					player->healDot(CreatureState::DISEASED, (15 + (meditateMod / 3)));

			} else if (meditateMod >= 75) { // Meditate SkillMod +75 for wound Healing..

				StringIdChatParameter healParams;

				//Here we are checking to see which pools have wounds, and we add them to a vector...
				Vector<uint8> woundedPools;
				for (uint8 i = 0; i < 9; ++i) {
					if (player->getWounds(i) > 0)
						woundedPools.add(i);
				}

				//Return without rescheduling because everything that can be healed has been?
				if (woundedPools.size() <= 0)
					return;

				int heal = 20 + System::random(10);

				if (meditateMod >= 100)
					heal = 30 + System::random(20);

				// Select a random Attribute that has wounds...
				uint8 pool = woundedPools.get(System::random(woundedPools.size() - 1));

				int wounds = player->getWounds(pool);

				//Cap the heal at the amount of wounds the creature has.
				heal = MIN(wounds, heal);

				player->addWounds(pool, -heal, true);

				// Sending System healing Message (wounds)
				healParams.setStringId("teraskasi", "prose_curewound"); // [meditation] Your %TO wounds heal by %DI points.
				healParams.setTO(CreatureAttribute::getName(pool));
				healParams.setDI(heal);
				player->sendSystemMessage(healParams);
			}

			if (meditateTask != NULL)
				meditateTask->reschedule(5000);
			else
				meditateTask->schedule(5000);

		} catch (Exception& e) {
			player->error("unreported exception caught in MeditateTask::activate");
		}
	}

};

#endif /* MEDITATETASK_H_ */
