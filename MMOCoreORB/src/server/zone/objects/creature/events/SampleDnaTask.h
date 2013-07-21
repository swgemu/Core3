#ifndef SAMPLEDNATASK_H_
#define SAMPLEDNATASK_H_

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "engine/engine.h"

class SampleDnaTask : public Task {

private:
	enum Phase { BEGIN, RUN, END} currentPhase;
	ManagedReference<Creature*> creature;
	ManagedReference<CreatureObject*> player;
public:

	SampleDnaTask(Creature* cre, CreatureObject* playo) : Task() {
		currentPhase = BEGIN;
		creature = cre;
		player = playo;
	}

	void run() {
		Locker locker(player);
		Locker crosslocker(creature,player);
		player->removePendingTask("sampledna");
		if (!creature->isInRange(player, 16.f) ) {
			updateDnaState(CreatureManager::HASDNA);
			player->sendSystemMessage("@bio_engineer:harvest_dna_out_of_range"); // The creature has moved too far away to continue milking it.
			return;
		}
		if (creature->isDead()) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_target_corpse");
			return;
		}
		if (creature->isInCombat()) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_creature_in_combat");
			return;
		}
		if (!creature->hasDNA()){
			player->sendSystemMessage("@bio_engineer:harvest_dna_cant_harvest");
			return;
		}
		int mindCost = player->calculateCostAdjustment(CreatureAttribute::FOCUS, 200);
		switch(currentPhase){
			case BEGIN:
				// We should be good to go now and try the sample
				if (player->getHAM(CreatureAttribute::MIND) < mindCost) {
					player->sendSystemMessage("@bio_engineer:harvest_dna_attrib_to_low");
				} else {
					player->inflictDamage(player, CreatureAttribute::MIND, mindCost, false, true);
					player->sendSystemMessage("@bio_engineer:harvest_dna_begin_harvest");
					currentPhase = RUN;
					player->addPendingTask("sampledna",this,5000);
				}
				player->doAnimation("heal_other");
				break;
			case RUN:
				currentPhase = END;
				player->addPendingTask("sampledna",this,5000);
				break;
			case END:
				player->sendSystemMessage("@bio_engineer:harvest_dna_failed");
				break;
		}
		return;
	}
	void updateDnaState(const short state) {
		Locker clocker(creature);
		creature->setDnaState(state);
	}
};
#endif //SAMPLEDNATASK_H_
