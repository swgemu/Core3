/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDSTIMPACKTASK_H_
#define DROIDSTIMPACKTASK_H_

#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidStimpackModuleDataComponent.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidStimpackTask : public Task {

	ManagedReference<DroidObject*> droid;
	ManagedReference<CreatureObject*> target;
	String droidName;

public:
	DroidStimpackTask(DroidObject* droid, CreatureObject* player,String droidName) : Task() {
		this->droid = droid;
		this->target = player;
		this->droidName = droidName;
	}

	void run() {
		Locker lock(droid);
		Locker crosslocker(target, droid);

		droid->removePendingTask("droid_request_stimpack");
		if (droid == NULL) {
			return;
		}

		auto module = droid->getModule("stimpack_module").castTo<DroidStimpackModuleDataComponent*>();
		if (module == NULL) {
			target->sendSystemMessage("@pet/droid_modules:not_stimpack_droid");
			return;
		}

		DroidComponent* droidComponent = cast<DroidComponent*>(module->getParent());

		if (droidComponent == NULL) {
			target->sendSystemMessage("@pet/droid_modules:stimpack_error");
			return;
		}

		// Check if droid is spawned
		if (droid->getLocalZone() == NULL) {  // Not outdoors
			ManagedReference<SceneObject*> parent = droid->getParent().get();

			if (parent == NULL || !parent->isCellObject()) { // Not indoors either
				return;
			}
		}

		// Check droid states
		if (droid->isDead() || droid->isIncapacitated() || target->isDead()) {
			return;
		}

		// Droid must have power
		if (!droid->hasPower()) {
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return;
		}

		// target must be in range
		if (!target->isInRange(droid, 20)) {
			// 20 meter range same as max possible range stim
			target->sendSystemMessage("@pet/droid_modules:stimpack_too_far_away");
			return;
		}

		// target must be the owner or in the owners group
		ManagedReference<GroupObject*> group = target->getGroup();
		bool groupMember = false;

		if (group != NULL) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				ManagedReference<CreatureObject*> member = group->getGroupMember(i);

				if (member->isPlayerCreature() && member == target) {
					groupMember = true;
				}
			}
		}

		if (droid->getLinkedCreature() != target) {
			if (!groupMember) {
				target->sendSystemMessage("@pet/droid_modules:stimpack_cant_use_droid");
				return;
			}
		}

		StimPack* stimpack = module->findStimPack();

		// droid has to have a stimpack to give
		if (stimpack == NULL) {
			target->sendSystemMessage("@pet/droid_modules:stimpack_supply_empty");
			return;
		}

		// target must need healing
		Vector<byte> atts = stimpack->getAttributes();
		bool needsHeals = false;

		for (int i = 0; i < atts.size(); i++) {
			if (target->hasDamage(atts.get(i)))
					needsHeals = true;
		}

		if (!needsHeals) {
			target->sendSystemMessage("@pet/droid_modules:stimpack_no_damage");
			return;
		}

		// check droid cooldown on dispensing
		if (droid->getCooldownTimerMap()->isPast("RequestStimpack")) {
			Locker locker(stimpack);

			// use the stim pack
			target->playEffect("clienteffect/healing_healdamage.cef", "");
			droid->doAnimation("heal_other");

			uint32 stimPower = stimpack->calculatePower(droid, target);

			int healthHealed = 0, actionHealed = 0, mindHealed = 0;
			bool notifyObservers = true;


			if (atts.contains(CreatureAttribute::HEALTH)) {
				healthHealed = target->healDamage(droid, CreatureAttribute::HEALTH, stimPower);
				notifyObservers = false;
			}

			if (atts.contains(CreatureAttribute::ACTION)) {
				if (notifyObservers) {
					actionHealed = target->healDamage(droid, CreatureAttribute::ACTION, stimPower);
					notifyObservers = false;
				} else {
					actionHealed = target->healDamage(droid, CreatureAttribute::ACTION, stimPower, true, false);
				}
			}

			if (atts.contains(CreatureAttribute::MIND)) {
				if (notifyObservers) {
					mindHealed = target->healDamage(droid, CreatureAttribute::MIND, stimPower);
				} else {
					mindHealed = target->healDamage(droid, CreatureAttribute::MIND, stimPower, true, false);
				}
			}

			stimpack->decreaseUseCount();
			droid->getCooldownTimerMap()->updateToCurrentAndAddMili("RequestStimpack",module->rate);

			// send heal message
			StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

			if (healthHealed > 0 && actionHealed > 0 && mindHealed > 0) {
				msgBody << healthHealed << " health, " << actionHealed << " action, and " << mindHealed << "mind";
			} else if (healthHealed > 0 && actionHealed > 0) {
				msgBody << healthHealed << " health and " << actionHealed << " action";
			} else if (healthHealed > 0 && mindHealed > 0) {
				msgBody << healthHealed << " health and " << mindHealed << " mind";
			} else if (actionHealed > 0 && mindHealed > 0) {
				msgBody << actionHealed << " action and " << mindHealed << " mind";
			} else if (healthHealed > 0) {
				msgBody << healthHealed << " health";
			} else if (actionHealed > 0) {
				msgBody << actionHealed << " action";
			} else if (mindHealed > 0) {
				msgBody << mindHealed << " mind";
			}

			msgTail << " damage.";
			msgTarget << droidName << " heals you for " << msgBody.toString() << msgTail.toString();

			target->sendSystemMessage(msgTarget.toString());
			droid->usePower(1);
			return;
		} else {
			target->sendSystemMessage("@pet/droid_modules:stimpack_not_ready");
			return;
		}
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDSTIMPACKTASK_H_*/
