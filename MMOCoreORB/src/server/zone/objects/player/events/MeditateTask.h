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

class MeditateTask : public Task {
	ManagedReference<PlayerCreature*> player;

public:
	MeditateTask(PlayerCreature* pl) {
		player = pl;
	}

	void run() {
		Locker playerLocker(player);

		if (player->getPendingTask("meditate") != NULL) {
			if (player->hasState(CreatureState::ALERT) && player->isMeditating()){
				// Do Healing....
				int heal;
				int healAmt;
				int meditateMod = player->getSkillMod("meditate");
				ParameterizedStringId healParams;
				int healthWounds = player->getWounds(CreatureAttribute::HEALTH);
				int actionWounds = player->getWounds(CreatureAttribute::ACTION);
				int mindWounds = player->getWounds(CreatureAttribute::MIND);

				Vector<uint8> woundedPools;

				for (uint8 i = 0; i < 9; i++){
					int hasWounds = player->getWounds(i);
					if(hasWounds > 0){
						woundedPools.add(i);
					}
				}

				if (woundedPools.size() == 0){
					return;
				}

				if (meditateMod > 0 && meditateMod < 100){
					heal = 20 + System::random(10);
				} else if(meditateMod >= 100){
					heal = 30 + System::random(20);
				} else{
					return;
				}

				uint8 pool = woundedPools.get(System::random(woundedPools.size() -1));

				switch (pool){
				case 1:
					if(healthWounds < heal){
						heal = healthWounds;
					}

					healAmt = healthWounds - heal;
					player->setWounds(CreatureAttribute::HEALTH, healAmt , true);
					healParams.setTO("health");
					break;

				case 2:
					if (actionWounds < heal){
						heal = actionWounds;
					}

					healAmt = actionWounds - heal;
					player->setWounds(CreatureAttribute::ACTION, healAmt , true);
					healParams.setTO("action");
					break;

				case 3:
					if (mindWounds < heal){
						heal = mindWounds;
					}

					healAmt = mindWounds - heal;
					player->setWounds(CreatureAttribute::MIND, healAmt , true);
					healParams.setTO("mind");
					break;

				}

				healParams.setStringId("teraskasi", "prose_curewound");
				healParams.setDI(heal);
				player->sendSystemMessage(healParams);
				/*
				if(healthWounds > 0){
					player->setWounds(CreatureAttribute::HEALTH, 300, true);
					healParams.setStringId("teraskasi", "prose_curewound");
					healParams.setTO("health");
					healParams.setDI(300);
					player->sendSystemMessage(healParams);
				}

				if(actionWounds > 0){
					player->setWounds(CreatureAttribute::ACTION, 300, true);
					healParams.setStringId("teraskasi", "prose_curewound");
					healParams.setTO("action");
					healParams.setDI(300);
					player->sendSystemMessage(healParams);
				}
				 */
				Reference<MeditateTask*> meditateTask = (MeditateTask*) player->getPendingTask("meditate");
				meditateTask->schedule(500);
			} else {
				return;
			}

			return;
		}

		player->removePendingTask("meditate");
	}

};

#endif /* MEDITATETASK_H_ */
