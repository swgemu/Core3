/*
 * ChannelForceRegenTask.h
 *
 *  Created on: Aug 18, 2011
 *      Author: swgemu
 */

#ifndef CHANNELFORCEREGENTASK_H_
#define CHANNELFORCEREGENTASK_H_


#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class ChannelForceRegenTask : public Task {
	ManagedReference<CreatureObject*> creature;
	int theBonus;
	int tickAmount;
public:

	ChannelForceRegenTask(CreatureObject* creo, int bonus, int tickAmt) {
		creature = creo;
		theBonus = bonus;
		tickAmount = tickAmt;
	}

	void run() {
		if(creature != NULL) {
			Locker locker(creature);

			for (int i=0; i < 9; ++i) {
				int baseHAM = creature->getBaseHAM(i);
				int maxHAM = creature->getMaxHAM(i);

				int calculated = baseHAM + theBonus;

				if (calculated != maxHAM && calculated > 1) {
					if (creature->getHAM(i) > calculated) {
						creature->setHAM(i, calculated / tickAmount, true);
					}

					creature->setMaxHAM(i, calculated / tickAmount, true);
				}
			}
		}
	}
};

}
}
}
}
}


#endif /* CHANNELFORCEREGENTASK_H_ */
