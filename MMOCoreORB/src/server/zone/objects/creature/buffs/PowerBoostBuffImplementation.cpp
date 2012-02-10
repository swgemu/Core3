/*
 * PowerboostBuffImplementation.cpp
 *
 *  Created on: 18/08/2010
 *      Author: polonel
 */

#include "PowerBoostBuff.h"
#include "PowerBoostBuffDurationEvent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

void PowerBoostBuffImplementation::initializeTransientMembers() {
	BuffImplementation::initializeTransientMembers();

	if (pbBuffEvent != NULL)
			return;

		if (nextTickTime.isPast()) {
			pbBuffEvent = new PowerBoostBuffDurationEvent(creature, _this);
			pbBuffEvent->schedule(50);
		} else {
			pbBuffEvent = new PowerBoostBuffDurationEvent(creature, _this);
			pbBuffEvent->schedule(nextTickTime);
		}
}

void PowerBoostBuffImplementation::activate(bool applyModifiers) {
	if(creature != NULL) {
		if(counter == 0) {
			BuffImplementation::activate(false);

			creature->addMaxHAM(CreatureAttribute::MIND, -(pbTick*20), true);
			creature->sendSystemMessage("@teraskasi:powerboost_begin"); // [meditation] You focus your mental energies into your physical form.

			// DurationEvent to handle calling the deactivate() when the timer expires.
			pbBuffEvent = new PowerBoostBuffDurationEvent(creature, _this);
			//nextTickTime = pbBuffEvent->getNextExecutionTime();
			Core::getTaskManager()->getNextExecutionTime(pbBuffEvent, nextTickTime);

			counter++;
			pbBuffEvent->schedule(3000);

		} else if(counter <= 20) {
			doHealthAndActionTick(true); // 1-20
			doMindTick(true);

			counter++;
			pbBuffEvent->reschedule(3000); // counter is not 20 ... reschedule

		} else if(counter > 20 && counter <= 40) {
			doMindTick(true); // 20-40
			counter++;
			pbBuffEvent->reschedule(3000);

		} else if(counter == 41) {
			counter = 45; // increase counter to 45 (to tick Down)..
			pbBuffEvent->reschedule(time - (183 * 1000)); // schedule for duration of the buff. (minus the tick time);

		} else if(counter >= 45 && counter < 65) {
			doHealthAndActionTick(false);
			doMindTick(false);
			counter++;
			pbBuffEvent->reschedule(3000);
		}
	}
}

void PowerBoostBuffImplementation::deactivate(bool removeModifiers) {
	if(creature != NULL) {
		if(counter <= 41) {
			activate(false);
		} else if(counter >= 45 && counter < 65) {
			if(counter == 45)
				creature->sendSystemMessage("@teraskasi:powerboost_wane"); // [meditation] You feel the effects of your mental focus begin to wane.
			activate(false);
		} else if(counter >= 65) {
			creature->sendSystemMessage("@teraskasi:powerboost_end"); // [meditation] You feel the effects of mental focus come to an end.
			clearBuffEvent();
			BuffImplementation::deactivate(false);
		}
	}
}

void PowerBoostBuffImplementation::doHealthAndActionTick(bool up) {
	if(up) {
		creature->addMaxHAM(CreatureAttribute::HEALTH, pbTick ,true);
		creature->addMaxHAM(CreatureAttribute::ACTION, pbTick ,true);
	} else {
		creature->addMaxHAM(CreatureAttribute::HEALTH, -pbTick ,true);
		creature->addMaxHAM(CreatureAttribute::ACTION, -pbTick ,true);
	}
}

void PowerBoostBuffImplementation::doMindTick(bool up) {
	if(up) {
		creature->addMaxHAM(CreatureAttribute::MIND, pbTick ,true);
	} else {
		creature->addMaxHAM(CreatureAttribute::MIND, -pbTick ,true);
	}
}

void PowerBoostBuffImplementation::clearBuffEvent() {
	if (pbBuffEvent != NULL) {
		if (pbBuffEvent->isScheduled())
			pbBuffEvent->cancel();
		pbBuffEvent->setBuffObject(NULL);
		pbBuffEvent = NULL;
		nextTickTime.updateToCurrentTime();
	}
}
