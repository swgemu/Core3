/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

/**
 * \file MeditateTask.h
 * \author Polonel
 * \date 08.04.2010
 */

#ifndef MEDITATETASK_H_
#define MEDITATETASK_H_

#include "engine/engine.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/creature/CreatureAttribute.h"

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
			Reference<MeditateTask*> meditateTask = player->getPendingTask("meditate").castTo<MeditateTask*>();
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
				heal = Math::min(wounds, heal);

				player->healWound(player, pool, heal, true, false);

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
