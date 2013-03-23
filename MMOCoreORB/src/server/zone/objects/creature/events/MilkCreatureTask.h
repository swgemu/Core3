
#ifndef MILKCREATURETASK_H_
#define MILKCREATURETASK_H_

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/engine.h"

class MilkCreatureTask : public Task {

private:
	enum Phase { INITIAL, ONESUCCESS, ONEFAILURE, FINAL} currentPhase;
	ManagedReference<Creature*> creature;
	ManagedReference<CreatureObject*> player;

public:
	MilkCreatureTask(Creature* cre, CreatureObject* playo) : Task() {
		currentPhase = INITIAL;
		creature = cre;
		player = playo;
	}

	void run() {
		if (!creature->isInRange(player, 5.f) || creature->isDead()) {
			updateMilkState(CreatureManager::NOTMILKED);
			player->sendSystemMessage("@skl_use:milk_too_far"); // The creature has moved too far away to continue milking it.
			return;
		}

		if (!player->hasState(CreatureState::MASKSCENT) || player->isInCombat() || creature->isInCombat()) {
			updateMilkState(CreatureManager::NOTMILKED);
			player->sendSystemMessage("@skl_use:milk_not_hidden"); // The creature is spooked and won't let you milk it.
			return;
		}

		float failureChance = 5 + (5 * creature->getFerocity());
		int skill = 100;
		bool success = true;

		skill += (player->getSkillMod("mask_scent") + player->getSkillMod("camouflage"));

		failureChance /= (skill / 100);

		if (System::random(100) < failureChance)
			success = false;

		switch (currentPhase) {
		case INITIAL:
			player->sendSystemMessage("@skl_use:milk_continue"); // You continue to milk the creature.
			if (success) {
				currentPhase = ONESUCCESS;
			} else {
				currentPhase = ONEFAILURE;
			}
			this->reschedule(10000);
			break;
		case ONESUCCESS:
			if (success) {
					player->sendSystemMessage("@skl_use:milk_success"); // You have successfully gathered milk from the creature!
					giveMilkToPlayer();
			} else {
					player->sendSystemMessage("@skl_use:milk_continue"); // You continue to milk the creature.
					currentPhase = FINAL;
					this->reschedule(10000);
			}
			break;
		case ONEFAILURE:
			if (success) {
				player->sendSystemMessage("@skl_use:milk_continue"); // You continue to milk the creature.
				currentPhase = FINAL;
				this->reschedule(10000);
			} else {
				updateMilkState(CreatureManager::NOTMILKED);
				CombatManager::instance()->startCombat(creature, player, true);
			}
			break;
		case FINAL:
			if (success) {
				player->sendSystemMessage("@skl_use:milk_success"); // You have successfully gathered milk from the creature!
				giveMilkToPlayer();
			} else {
				updateMilkState(CreatureManager::NOTMILKED);
				CombatManager::instance()->startCombat(creature, player, true);
			}
			break;
		}

		return;
	}

	void giveMilkToPlayer() {
		ManagedReference<ResourceManager*> resourceManager = player->getZoneServer()->getResourceManager();

		String restype = creature->getMilkType();
		int quantity = creature->getMilk();

		int quantityExtracted = MAX(quantity, 3);

		ManagedReference<ResourceSpawn*> resourceSpawn = resourceManager->getCurrentSpawn(restype, player->getZone()->getZoneName());

		if (resourceSpawn == NULL) {
			player->sendSystemMessage("Error: Server cannot locate a current spawn of " + restype);
			return;
		}

		float density = resourceSpawn->getDensityAt(player->getZone()->getZoneName(), player->getPositionX(), player->getPositionY());

		if (density > 0.80f) {
			quantityExtracted = int(quantityExtracted * 1.25f);
		} else if (density > 0.60f) {
			quantityExtracted = int(quantityExtracted * 1.00f);
		} else if (density > 0.40f) {
			quantityExtracted = int(quantityExtracted * 0.75f);
		} else {
			quantityExtracted = int(quantityExtracted * 0.50f);
		}

		resourceManager->harvestResourceToPlayer(player, resourceSpawn, quantityExtracted);

		updateMilkState(CreatureManager::ALREADYMILKED);
	}

	void updateMilkState(const short milkState) {
		Locker clocker(creature);
		creature->setMilkState(milkState);
	}
};

#endif /* MILKCREATURETASK_H_ */
