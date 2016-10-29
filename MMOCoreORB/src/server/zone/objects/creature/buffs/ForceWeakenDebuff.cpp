
#include "server/zone/objects/creature/buffs/ForceWeakenDebuff.h"
#include "ForceWeakenDebuffDurationEvent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/creature/CreatureAttribute.h"

void ForceWeakenDebuffImplementation::initializeTransientMembers() {
	BuffImplementation::initializeTransientMembers();
}

void ForceWeakenDebuffImplementation::activate(bool applyModifiers) {
	if(creature.get() != NULL) {
		Locker locker(creature.get());
		Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
		if (creature.get()->isIncapacitated() || creature.get()->isDead()) {
			return;
		}
		if(counter == 0) {
			mindBuffAmount=0;
			haBuffAmount=0;
			BuffImplementation::activate(false);
			creature.get()->addMaxHAM(CreatureAttribute::HEALTH, -(fwTick*5), true);
			creature.get()->addMaxHAM(CreatureAttribute::ACTION, -(fwTick*5), true);
			haBuffAmount=-(fwTick*5);
			creature.get()->addMaxHAM(CreatureAttribute::MIND, -(fwTick*5), true);
			mindBuffAmount=-(fwTick*5);
			creature.get()->sendSystemMessage("TEST is it beginning to TICK?"); //NEE DELETE THIS
			counter++;
			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();
			if (weakenCheck == NULL) {
				fwBuffEvent = new ForceWeakenDebuffDurationEvent(creature.get(), _this.getReferenceUnsafeStaticCast());
				creature.get()->addPendingTask("forceWeakenTick", fwBuffEvent, 6000);
			}else {
				return;
			}

		} else if(counter <= 5) {
			doHealthAndActionTick(true); // 1-5
			doMindTick(true);
			counter++;
			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();
			if (weakenCheck != NULL) {
				weakenCheck->reschedule(6000);
			}
		} else if(counter > 5 && counter <= 10) {
			doMindTick(true); // 5-10
			counter++;
			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();
			if (weakenCheck != NULL)
				weakenCheck->reschedule(6000);
		} else if(counter == 11) {
			counter = 15; // increase counter to 15 (to tick Down)..
			Reference<ForceWeakenDebuffDurationEvent*> WeakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();
			if (WeakenCheck != NULL)
				WeakenCheck->reschedule(time - (85 * 1000)); // schedule for duration of the buff. (minus the tick time);
		} else if(counter >= 15 && counter < 35) {
			doHealthAndActionTick(false);
			doMindTick(false);
			counter++;
			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();
			if (weakenCheck != NULL)
				weakenCheck->reschedule(6000);
		}
	}
}

void ForceWeakenDebuffImplementation::deactivate(bool removeModifiers) {
	if(creature.get() != NULL) {
		Locker locker(creature.get());
		Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
		if(counter <= 11) {
			activate(false);
		} else if(counter >= 15 && counter < 35) {
			if(counter == 15)
				creature.get()->sendSystemMessage("2nd message is it working still?");//NEE DELETE
			activate(false);
		} else if(counter >= 35) {
			creature.get()->sendSystemMessage("third message is it ending now?");// NEE DELETE this
			clearBuffEvent();
			BuffImplementation::deactivate(false);
		}
	}
}

void ForceWeakenDebuffImplementation::doHealthAndActionTick(bool up) {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
	if (!creature.get()->isIncapacitated() && !creature.get()->isDead()) {
		if(up) {
			creature.get()->addMaxHAM(CreatureAttribute::HEALTH, -fwTick ,true);
			creature.get()->addMaxHAM(CreatureAttribute::ACTION, -fwTick ,true);
			haBuffAmount-= fwTick;
		} else {
			creature.get()->addMaxHAM(CreatureAttribute::HEALTH, fwTick ,true);
			creature.get()->addMaxHAM(CreatureAttribute::ACTION, fwTick ,true);
			haBuffAmount+= fwTick;
		}
	}
}

void ForceWeakenDebuffImplementation::doMindTick(bool up) {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
	if (!creature.get()->isIncapacitated() && !creature.get()->isDead()) {
		if(up) {
			creature.get()->addMaxHAM(CreatureAttribute::MIND, -fwTick ,true);
			mindBuffAmount -= fwTick;
		} else {
			creature.get()->addMaxHAM(CreatureAttribute::MIND, fwTick ,true);
			mindBuffAmount += fwTick;
		}
	}
}

void ForceWeakenDebuffImplementation::clearBuffEvent() {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
	if (fwBuffEvent != NULL) {
		creature.get()->removePendingTask("forceWeakenTick");
	}
	creature.get()->addMaxHAM(CreatureAttribute::HEALTH, haBuffAmount ,true);
	creature.get()->addMaxHAM(CreatureAttribute::ACTION, haBuffAmount ,true);
	haBuffAmount =0;
	creature.get()->addMaxHAM(CreatureAttribute::MIND, mindBuffAmount ,true);
	mindBuffAmount=0;
	BuffImplementation::clearBuffEvent();
}
