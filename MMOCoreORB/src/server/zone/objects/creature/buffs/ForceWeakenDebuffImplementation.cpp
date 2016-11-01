
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
		if (creature.get()->isIncapacitated() || creature.get()->isDead() || creature.get()->isFeigningDeath()) {
			return;
		}
		if(counter == 0) {
			deBuffAmount=0;
			BuffImplementation::activate(false);
			creature.get()->addMaxHAM(CreatureAttribute::HEALTH, -(fwTick*5), true);
			creature.get()->addMaxHAM(CreatureAttribute::ACTION, -(fwTick*5), true);
			creature.get()->addMaxHAM(CreatureAttribute::MIND, -(fwTick*5), true);
			deBuffAmount=-(fwTick*5);
			counter++;
			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();
			if (weakenCheck == NULL) {
				fwBuffEvent = new ForceWeakenDebuffDurationEvent(creature.get(), _this.getReferenceUnsafeStaticCast());
				creature.get()->addPendingTask("forceWeakenTick", fwBuffEvent, 6000);
			} else {
				return;
			}

		} else if(counter <= 5) {
			doHealthActionMindTick(true); // 1-5
			counter++;
			Reference<ForceWeakenDebuffDurationEvent*> weakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();
			if (weakenCheck != NULL) {
				weakenCheck->reschedule(6000);
			}
		} else if(counter == 11) {
			counter = 15; // increase counter to 15 (to tick Down)..
			Reference<ForceWeakenDebuffDurationEvent*> WeakenCheck = creature.get()->getPendingTask("forceWeakenTick").castTo<ForceWeakenDebuffDurationEvent*>();
			if (WeakenCheck != NULL)
				WeakenCheck->reschedule(time - (85 * 1000)); // schedule for duration of the debuff, minus the tick time
		} else if(counter >= 15 && counter < 35) {
			doHealthActionMindTick(false);
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
			activate(false);
		} else if(counter >= 35) {
			clearBuffEvent();
			BuffImplementation::deactivate(false);
		}
	}
}

void ForceWeakenDebuffImplementation::doHealthActionMindTick(bool weak) {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
	if (!creature.get()->isIncapacitated() && !creature.get()->isDead() && !creature.get()->isFeigningDeath()) {
		if(weak) {
			creature.get()->addMaxHAM(CreatureAttribute::HEALTH, -fwTick ,true);
			creature.get()->addMaxHAM(CreatureAttribute::ACTION, -fwTick ,true);
			creature.get()->addMaxHAM(CreatureAttribute::MIND, -fwTick ,true);
			deBuffAmount-= fwTick;
		} else {
			creature.get()->addMaxHAM(CreatureAttribute::HEALTH, fwTick ,true);
			creature.get()->addMaxHAM(CreatureAttribute::ACTION, fwTick ,true);
			creature.get()->addMaxHAM(CreatureAttribute::MIND, fwTick ,true);
			deBuffAmount+= fwTick;
		}
	}
}

void ForceWeakenDebuffImplementation::clearBuffEvent() {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
	if (fwBuffEvent != NULL) {
		creature.get()->removePendingTask("forceWeakenTick");
	}

	//int hWounds = creature.get()->getWounds(CreatureAttribute::HEALTH);
	//int aWounds = creature.get()->getWounds(CreatureAttribute::ACTION);
	//int mWounds = creature.get()->getWounds(CreatureAttribute::MIND);
	// NEE what about secondary wounds though??
	//int hEncum = creature.get()->getEncumbrance(CreatureAttribute::HEALTH);
	//int aEncum = creature.get()->getEncumbrance(CreatureAttribute::ACTION);
	//int mEncum = creature.get()->getEncumbrance(CreatureAttribute::MIND);
	//NEE again what about secondaries?
	//int currentHealth = creature.get()->getMaxHAM(CreatureAttribute::HEALTH);
	//int currentAction = creature.get()->getMaxHAM(CreatureAttribute::ACTION);
	//int currentMind = creature.get()->getMaxHAM(CreatureAttribute::MIND);
	//NEE secondaries?

	creature.get()->addMaxHAM(CreatureAttribute::HEALTH, deBuffAmount ,true);
	creature.get()->addMaxHAM(CreatureAttribute::ACTION, deBuffAmount ,true);
	creature.get()->addMaxHAM(CreatureAttribute::MIND, deBuffAmount ,true);
	deBuffAmount =0;
	BuffImplementation::clearBuffEvent();
}
