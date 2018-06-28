#include "ForceWeakenDebuffDurationEvent.h"
#include "server/zone/objects/creature/buffs/ForceWeakenDebuff.h"
#include "templates/params/creature/CreatureAttribute.h"

void ForceWeakenDebuffImplementation::initializeTransientMembers() {
	BuffImplementation::initializeTransientMembers();
}

void ForceWeakenDebuffImplementation::activate(bool applyModifiers) {
	if (creature.get() != NULL) {
		Locker locker(creature.get());
		Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());

		if (creature.get()->isIncapacitated() || creature.get()->isDead()) {
			return;
		}

		if (counter == 0) {
			BuffImplementation::activate(false);

			doHealthActionMindTick(true);

			counter++;

			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();

			if (weakenCheck == NULL) {
				fwBuffEvent = new ForceWeakenDebuffDurationEvent(creature.get(), _this.getReferenceUnsafeStaticCast());
				creature.get()->addPendingTask("forceWeakenTick", fwBuffEvent, FORCE_WEAKEN_TICK_SECONDS * 1000);
			}
		} else if (counter < FORCE_WEAKEN_TICK_COUNT) { //Ramp up weaken effect
			doHealthActionMindTick(true);

			counter++;

			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();

			if (weakenCheck != NULL) {
				weakenCheck->reschedule(FORCE_WEAKEN_TICK_SECONDS * 1000);
			}
		} else if (counter == FORCE_WEAKEN_TICK_COUNT) {
			counter++;

			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();

			if (weakenCheck != NULL) {
				//Schedule for start of ramp down period, considering time already taken
				weakenCheck->reschedule(time - (FORCE_WEAKEN_RAMP_SECONDS * 1000) - (FORCE_WEAKEN_TICK_COUNT * FORCE_WEAKEN_TICK_SECONDS * 1000));
			}
		} else if (counter <= FORCE_WEAKEN_TICK_COUNT*2) { //Ramp down weaken effect
			doHealthActionMindTick(false);

			counter++;

			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();

			if (weakenCheck != NULL) {
				weakenCheck->reschedule(FORCE_WEAKEN_TICK_SECONDS * 1000);
			}
		}
	}
}

void ForceWeakenDebuffImplementation::deactivate(bool removeModifiers) {
	BuffImplementation::deactivate(false);
}

void ForceWeakenDebuffImplementation::doHealthActionMindTick(bool weaken) {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());

	if (!creature.get()->isIncapacitated() && !creature.get()->isDead()) {
		int tickDebuffAmount = 0;

		//Determine random weakening (or restoring) amount for this tick based on range
		if (creature.get()->isKnockedDown() || creature.get()->isProne()) {
			tickDebuffAmount = ((fwKdMaxAmount - FORCE_WEAKEN_RAND_SCALE) + System::random(FORCE_WEAKEN_RAND_SCALE)) / FORCE_WEAKEN_TICK_COUNT;
		} else {
			tickDebuffAmount = ((fwStdMaxAmount - FORCE_WEAKEN_RAND_SCALE) + System::random(FORCE_WEAKEN_RAND_SCALE)) / FORCE_WEAKEN_TICK_COUNT;
		}

		for (int i = 0; i < hamDebuffAmount.size(); ++i) {
			VectorMapEntry<int, int> currentAttribute = hamDebuffAmount.elementAt(i);

			if (weaken) { //Weakening
				int currentMaxValue = creature.get()->getMaxHAM(currentAttribute.getKey());
				int currentWounds = creature.get()->getWounds(currentAttribute.getKey());

				//Prevent weakening below 1
				if (currentMaxValue - currentWounds - tickDebuffAmount < 1) {
					creature.get()->addMaxHAM(currentAttribute.getKey(), -(currentMaxValue - currentWounds - 1) ,true);

					hamDebuffAmount.put(currentAttribute.getKey(), currentAttribute.getValue() - (currentMaxValue - currentWounds - 1));
				} else {
					creature.get()->addMaxHAM(currentAttribute.getKey(), -tickDebuffAmount ,true);

					hamDebuffAmount.put(currentAttribute.getKey(), currentAttribute.getValue() - tickDebuffAmount);
				}
			} else if (hamDebuffAmount.elementAt(i).getValue() < 0) { //Restoring
				if (-currentAttribute.getValue() < tickDebuffAmount) {
					tickDebuffAmount = -currentAttribute.getValue();
				}

				creature.get()->addMaxHAM(currentAttribute.getKey(), tickDebuffAmount ,true);

				hamDebuffAmount.put(currentAttribute.getKey(), currentAttribute.getValue() + tickDebuffAmount);
			}
		}
	}
}

void ForceWeakenDebuffImplementation::clearBuffEvent() {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());

	if (fwBuffEvent != NULL) {
		creature.get()->removePendingTask("forceWeakenTick");

		if (fwBuffEvent->isScheduled())
			fwBuffEvent->cancel();
	}

	for (int i = 0; i < hamDebuffAmount.size(); ++i) {
		creature.get()->addMaxHAM(hamDebuffAmount.elementAt(i).getKey(), -hamDebuffAmount.elementAt(i).getValue(), true);

		hamDebuffAmount.put(hamDebuffAmount.elementAt(i).getKey(), 0);
	}

	BuffImplementation::clearBuffEvent();
}
