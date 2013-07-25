#ifndef SAMPLEDNATASK_H_
#define SAMPLEDNATASK_H_

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "engine/engine.h"

class SampleDnaTask : public Task {

private:
	enum Phase { BEGIN, SAMPLING, END} currentPhase;
	int waitCount;
	ManagedReference<Creature*> creature;
	ManagedReference<CreatureObject*> player;
public:

	SampleDnaTask(Creature* cre, CreatureObject* playo) : Task() {
		currentPhase = BEGIN;
		waitCount = 0;
		creature = cre;
		player = playo;
	}
	void run() {
		Locker locker(player);
		Locker crosslocker(creature,player);
		player->removePendingTask("sampledna");
		if (!creature->isInRange(player, 16.f) ) {
			updateDnaState(CreatureManager::HASDNA);
			player->sendSystemMessage("@bio_engineer:harvest_dna_out_of_range");
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
		int skillMod = player->getSkillMod("dna_harvesting");
		int cl = creature->getLevel();
		switch(currentPhase){
			case BEGIN:
				// We should be good to go now and try the sample
				if (player->getHAM(CreatureAttribute::MIND) < mindCost) {
					player->sendSystemMessage("@bio_engineer:harvest_dna_attrib_too_low");
				} else {
					player->inflictDamage(player, CreatureAttribute::MIND, mindCost, false, true);
					player->sendSystemMessage("@bio_engineer:harvest_dna_begin_harvest");
					currentPhase = SAMPLING;
					player->addPendingTask("sampledna",this,1000);
				}
				player->doAnimation("heal_other");
				break;
			case SAMPLING:
				if (waitCount == 9) {
					currentPhase = END;
				}else {
					waitCount++;
				}
				player->addPendingTask("sampledna",this,1000);
				break;
			case END:
				bool success = false;
				bool aggro = false;
				bool killCreature = false;
				int health = creature->getMaxHAM(CreatureAttribute::HEALTH);
				int mind = creature->getMaxHAM(CreatureAttribute::MIND);
				int action = creature->getMaxHAM(CreatureAttribute::ACTION);
				bool tooBig = action > 13000 || health > 13000 || mind > 13000;
				float sampleChance = 5;
				if (!tooBig) {
					if (skillMod < cl) {
						sampleChance += 45 - (cl - skillMod);
					} else {
						sampleChance += 45 + (skillMod - cl);
					}
				}
				int roll = System::random(100);
				if (roll <= sampleChance) {
					success = true;
				}
				if (creature->getDnaSampleCount() > ceil(skillMod/20) || creature->getDnaSampleCount() > 5) {
					updateDnaState(CreatureManager::DNASAMPLED);
					player->sendSystemMessage("@bio_engineer:harvest_dna_cant_harvest");
				} else {
					// lets say 35% chance to aggro the targer - 1/5 of your skill * 2 so max skill this is 10
					// always a 5% chance to aggro
					int aggroModifier = 35;
					if (skillMod > cl) {
						aggroModifier -= (skillMod - cl);
					} else {
						aggroModifier += (cl - skillMod);
					}
					if (aggroModifier < 5) {
						aggroModifier = 5;
					}
					aggro = System::random(100) < aggroModifier;
					killCreature = System::random(100) < 15*creature->getDnaSampleCount();
					// did it aggro?
					if (aggro){
						success = false;
						CombatManager::instance()->startCombat(creature,player,true);
					} else if (killCreature) {
						updateDnaState(CreatureManager::DNADEATH);
					}
				}
				// calc xp
				if (success) {
					int xp = DnaManager::instance()->generateXp(cl);
					ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();
					if(creature->getDnaState() == CreatureManager::DNADEATH) {
						// kill the creature off and provide the sample
						int dam = 9999999;
						creature->inflictDamage(player, 0, dam, true, false);
						creature->inflictDamage(player, 3, dam, true, false);
						creature->inflictDamage(player, 6, dam, true, false);
						StringIdChatParameter str("@bio_engineer:harvest_dna_creature_killed");
						str.setTT(creature->getObjectID());
						player->sendSystemMessage(str);
					}else {
						creature->incDnaSampleCount();
						// just increment the count
						player->sendSystemMessage("@bio_engineer:harvest_dna_succeed");
					}
					if(playerManager != NULL)
						playerManager->awardExperience(player, "bio_engineer_dna_harvesting", xp, true);
					// Grant Sample
					if (tooBig) {
						cl = 70;
					}
					generateSample(cl,5);
				}else {
					if (!aggro)
						player->sendSystemMessage("@bio_engineer:harvest_dna_failed");
				}
				break;
		}
		return;
	}
	void updateDnaState(const short state) {
		Locker clocker(creature);
		creature->setDnaState(state);
	}
	void generateSample(int cl,int quality) {

		CreatureTemplate* creatureTemplate = dynamic_cast<CreatureTemplate*>(creature->getCreatureTemplate());
		int ferocity = creatureTemplate->getFerocity();
		CreatureAttackMap* attackMap = creatureTemplate->getAttacks();
		bool ranged = creatureTemplate->getWeapons().size() > 0;
		int cle = DnaManager::instance()->generateScoreFor(DnaManager::CLEVERNESS,cl,quality);
		int cou = DnaManager::instance()->generateScoreFor(DnaManager::COURAGE,cl,quality);
		int dep = DnaManager::instance()->generateScoreFor(DnaManager::DEPENDABILITY,cl,quality);
		int dex = DnaManager::instance()->generateScoreFor(DnaManager::DEXTERITY,cl,quality);
		int end = DnaManager::instance()->generateScoreFor(DnaManager::ENDURANCE,cl,quality);
		int fie = DnaManager::instance()->generateScoreFor(DnaManager::FIERCENESS,ferocity,quality);
		int frt = DnaManager::instance()->generateScoreFor(DnaManager::FORTITUDE,cl,quality);
		int har = DnaManager::instance()->generateScoreFor(DnaManager::HARDINESS,cl,quality);
		int ite = DnaManager::instance()->generateScoreFor(DnaManager::INTELLIGENCE,cl,quality);
		int pow = DnaManager::instance()->generateScoreFor(DnaManager::POWER,cl,quality);
		// We should now have enough to generate a sample
		ManagedReference<SceneObject*> item = player->getZoneServer()->createObject(String("object/tangible/component/dna/dna_sample_above_average.iff").hashCode(), 1);
		Locker clocker(item);

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory->hasFullContainerObjects()) {
			StringIdChatParameter err("survey", "no_inv_space");
			player->sendSystemMessage(err);
			player->setPosture(CreaturePosture::UPRIGHT, true);
			return;
		}

		Locker locker(inventory);
		inventory->transferObject(item, -1, true,false);
		inventory->broadcastObject(item, true);
	}
};
#endif //SAMPLEDNATASK_H_
